#include <random>
#include <iostream>
#include <string>
#include <ostream>
#include <algorithm>
#include <array>
#include <sstream>
#include <conio.h>

#include "Game.h"
#include "Arrow.h"
#include "Bat.h"
#include "Pit.h"
#include "Player.h"
#include "Wampus.h"
#include "Utilities.h"
#include "Properties.h"

Game::Game()
{
    Self = this;

    // SetUp callbacks
    GUI->callback(CbKeyboardHit);
    GUI->QuitBtn->callback(CbClickQuit);

    GUI->InfoDiag->OkBtn->callback(CbClickInfoDiagOk);

    GUI->Tunnel1->callback(CbClickTunnel, GUI->Tunnel1->TunnelNum);
    GUI->Tunnel2->callback(CbClickTunnel, GUI->Tunnel2->TunnelNum);
    GUI->Tunnel3->callback(CbClickTunnel, GUI->Tunnel3->TunnelNum);

    GUI->ShootDiag->EraseBtn->callback(CbClickSDErase);
    for (CaveNumberWidget* Widget : GUI->ShootDiag->CaveNumberButtons)
    {
        Widget->callback(CbClickSDCaveNumberButton);
    }
    GUI->ShootDiag->BowBtn->callback(CbClickBow);
}


void Game::CbIdle(void* Data)
{
    
}

void Game::PrapareGame()
{
    //Fl::add_idle(CbIdle);

    SP->Play(SoundName::BACKGROUND);
    InitRandom();
    LinkCaves();
    PlaceUnits();

    PlayerMove(PlayerPtr->CavePtr->Num);
}


void Game::MoveUnit(Unit* TargetUnitPtr, Cave* FromCavePtr, Cave* ToCavePtr)
{
    if (FromCavePtr == ToCavePtr)
    {
        return;
    }
    // add unit to units in new cave
    ToCavePtr->Units.push_back(TargetUnitPtr);

    // update unit cave
    TargetUnitPtr->CavePtr = ToCavePtr;

    // delete unit from units in old cave  
    std::vector<Unit*>::iterator Iter = std::find(FromCavePtr->Units.begin(), FromCavePtr->Units.end(), TargetUnitPtr);
    FromCavePtr->Units.erase(Iter);
}

void Game::EndGame(bool IsWin)
{
    exit(0);
}

void Game::CbKeyboardHit(Fl_Widget* Widget)
{
    if (Fl::event() == FL_SHORTCUT && Fl::event_key() == FL_Escape)
    {
        return; // ignore Escape
    }
}

void Game::CbClickQuit(Fl_Widget* Widget)
{
    if (Fl::event() == FL_SHORTCUT && Fl::event_key() == FL_Escape)
    {
        return; // ignore Escape
    }
    Self->SP->Engine.stopAll();
	exit(0); 
}

void Game::CbClickTunnel(Fl_Widget* Widget, void* TunnelNumber)
{
    if (Self->IsDialogOpen()) return;
    Self->SP->FadeOutAllExceptBackground(2);
    Self->SP->Play(SoundName::PLAYER_WALK);
    Self->PlayerMove(*static_cast<int*>(TunnelNumber));
}

void Game::CbClickBow(Fl_Widget* Widget)
{
    if (Self->IsDialogOpen()) return;
    Self->PlayerShoot();
}

void Game::CbClickSDErase(Fl_Widget* Widget)
{
    if (Self->IsDialogOpen()) return;

    Self->GUI->ShootDiag->PathOut->EraseLast();
    int CaveNum{0};
    if (Self->GUI->ShootDiag->PathOut->CaveNumbersInPath.empty())
    {
        CaveNum = Self->PlayerPtr->CavePtr->Num;
    }
    else
    {
        CaveNum = Self->GUI->ShootDiag->PathOut->CaveNumbersInPath.back();
    }

    // redraw available numbers for shoot
    CaveWidget* CaveW = Self->GUI->Map->CaveWidgets[CaveNum];
    if (CaveW->VisibleTunnels)
    {
        Self->GUI->ShootDiag->ShowCaveNumbers(
            {
                Self->Caves[CaveNum]->AdjCaveNumbers[0],
                Self->Caves[CaveNum]->AdjCaveNumbers[1],
                Self->Caves[CaveNum]->AdjCaveNumbers[2]
            }
        );
    }
    else
    {
        Self->GUI->ShootDiag->ShowAllExceptCaveNumbers(
            {
                CaveNum
            }
        );

    }
}

void Game::CbClickSDCaveNumberButton(Fl_Widget* Widget)
{
    if (Self->IsDialogOpen()) return;

    if (Self->GUI->ShootDiag->PathOut->CaveNumbersInPath.size() == 5)
    {
        return; // just in case situation. There should be no such situation.
    }

    if (Self->GUI->ShootDiag->PathOut->CaveNumbersInPath.empty())
    {
        Self->SP->Play(SoundName::BOW_READY);

    }
       
    CaveNumberWidget* CaveNumW = static_cast<CaveNumberWidget*>(Widget);

    // update outout path
    Self->GUI->ShootDiag->PathOut->Add(CaveNumW->Number);

    // hide if max path (5)
    if (Self->GUI->ShootDiag->PathOut->CaveNumbersInPath.size() == 5)
    {
        Self->GUI->ShootDiag->HideCaveNumbers();
        return;
    }

    // redraw available numbers for shoot
    CaveWidget* CaveW = Self->GUI->Map->CaveWidgets[CaveNumW->Number];
    if (CaveW->VisibleTunnels)
    {
        Self->GUI->ShootDiag->ShowCaveNumbers(
            {
                Self->Caves[CaveNumW->Number]->AdjCaveNumbers[0],
                Self->Caves[CaveNumW->Number]->AdjCaveNumbers[1],
                Self->Caves[CaveNumW->Number]->AdjCaveNumbers[2]
            }
        );
    }
    else
    {
        Self->GUI->ShootDiag->ShowAllExceptCaveNumbers(
            {
                CaveNumW->Number
            }
        );

    }

}

void Game::CbClickInfoDiagOk(Fl_Widget* Widget)
{
    Self->GUI->InfoDiag->hide();
}


void Game::_DebugPrintCavesUnits()
{   
    for(Cave* CavePtr: Caves)
    {
        std::wcout << L"// Cave " << CavePtr->Num << L": ";
        for(Unit* UnitPtr: CavePtr->Units)
        {
            std::wcout << typeid(*UnitPtr).name() << L", ";
        }
        std::wcout << L'\n';
    }
}

Game::~Game()
{
    for (Cave* Cave: Caves)
    {
        delete Cave;
    }
    Caves.clear();
    
    for (Unit* Unit: Units)
    {
        delete Unit;
    }
    Units.clear();
}

void Game::LinkCaves()
{
    for (int i = 0; i < 21; ++i)
    {
        Caves.push_back(new Cave {Props::CavesList[i]});
    }

    for (int i = 0; i < 21; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            Caves[i]->AdjacentCaves.push_back(Caves[Caves[i]->AdjCaveNumbers[j]]);
        }
    }
}

template <typename UnitType>
Unit* Game::UnitFactory()
{
    Unit* UnitPtr = new UnitType();
    Cave* CavePtr = GetRandomEmptyCave();
    UnitPtr->CavePtr = CavePtr;
    CavePtr->Units.push_back(UnitPtr);
    Units.push_back(UnitPtr);
    return UnitPtr;
}

template<typename UnitType>
Unit* Game::UnitFactory(Cave* CavePtr)
{
    Unit* UnitPtr = new UnitType();
    UnitPtr->CavePtr = CavePtr;
    CavePtr->Units.push_back(UnitPtr);
    Units.push_back(UnitPtr);
    return UnitPtr;
}


void Game::PlaceUnits()
{   
    PlayerPtr = static_cast<Player*>(UnitFactory<Player>());
    WampusPtr = static_cast<Wampus*>(UnitFactory<Wampus>());
    UnitFactory<Bat>();
    UnitFactory<Bat>();
    UnitFactory<Pit>();
    UnitFactory<Pit>();
}

Cave* Game::GetRandomEmptyCave()
{
    Cave* Cave;
    while(true)
    {
        Cave = Caves[roll_d20()];
        if (Cave->Units.empty())
            return Cave;
    }
}

void Game::DestroyUnit(Unit* TargetUnitPtr)
{
    // check caves for ptr
    for (Cave* CavePtr : Caves)
    {
        if (!CavePtr->Units.empty())
        {
            std::vector<Unit*>::iterator Iter = std::find(CavePtr->Units.begin(), CavePtr->Units.end(), TargetUnitPtr);
            if (Iter != CavePtr->Units.end())
            {
                CavePtr->Units.erase(Iter);
            }
        }
    }

    // delete from game units
    std::vector<Unit*>::iterator Iter = std::find(Units.begin(), Units.end(), TargetUnitPtr);
    if (!(Iter == Units.end()))
    {
        Units.erase(Iter);
    }

}


void Game::PlayerListen()
{
    Cave* AdjacentCave1 = PlayerPtr->CavePtr->AdjacentCaves[0];
    Cave* AdjacentCave2 = PlayerPtr->CavePtr->AdjacentCaves[1];
    Cave* AdjacentCave3 = PlayerPtr->CavePtr->AdjacentCaves[2];

    std::vector<Cave*> ShuffledCaves {AdjacentCave1, AdjacentCave2, AdjacentCave3};
    std::shuffle(ShuffledCaves.begin(), ShuffledCaves.end(), RandomEngine);

    SoLoud::handle SoundHandle;
    for (Cave* CavePtr : ShuffledCaves)
    {
        for (Unit* UnitPtr : CavePtr->Units)
        {
            if (typeid(*UnitPtr) == typeid(Wampus))
            {
                if (static_cast<Wampus*>(UnitPtr)->IsAwake)
                {
                    SoundHandle = SP->PlayFadeIn(SoundName::NEAR_WAMPUS_AWAKE, 4);
                }
                else
                {
                    SoundHandle = SP->PlayFadeIn(SoundName::NEAR_WAMPUS_SLEEP, 4);
                }
            }
            else if (typeid(*UnitPtr) == typeid(Bat))
            {
                SoundHandle = SP->PlayFadeIn(SoundName::NEAR_BATS, 4);
            }
            else if (typeid(*UnitPtr) == typeid(Pit))
            {
                SoundHandle = SP->PlayFadeIn(SoundName::NEAR_PIT, 4);
            }
        }
    }

}

void Game::PlayerMove(int TunnelNumber)
{
    Sleep(800);
    GUI->Map->UnsetPlayerCaveMark(PlayerPtr->CavePtr->Num);
    MoveUnit(PlayerPtr, PlayerPtr->CavePtr, Caves[TunnelNumber]);
    GUI->Map->SetPlayerCaveMark(TunnelNumber);
    
    GUI->Map->ShowCave(TunnelNumber);
    for (int CaveNumber : PlayerPtr->CavePtr->AdjCaveNumbers)
    {
        GUI->Map->ShowCave(CaveNumber);
    }

    GUI->Tunnel1->SetLabel(PlayerPtr->CavePtr->AdjCaveNumbers[0]);
    GUI->Tunnel2->SetLabel(PlayerPtr->CavePtr->AdjCaveNumbers[1]);
    GUI->Tunnel3->SetLabel(PlayerPtr->CavePtr->AdjCaveNumbers[2]);

    GUI->Map->redraw();

    GUI->ShootDiag->PathOut->Clear();
    GUI->ShootDiag->ShowCaveNumbers(
        {
            PlayerPtr->CavePtr->AdjCaveNumbers[0],
            PlayerPtr->CavePtr->AdjCaveNumbers[1],
            PlayerPtr->CavePtr->AdjCaveNumbers[2]
        }
    );

    // if wampus in awake - he move in random cave
    if (WampusPtr->IsAwake)
    {
        if (roll_d100() <= 75)
        {
            MoveUnit(WampusPtr, WampusPtr->CavePtr, WampusPtr->CavePtr->AdjacentCaves[roll_d3() - 1]);
            if (WampusPtr->CavePtr == PlayerPtr->CavePtr)
            {
                SP->Play(SoundName::PLAYER_DIE);
                GUI->InfoDiag->ShowInfo(GUI->InfoDiag->GAMEOVER_WAMPUS_WALK_IN_SAME_CAVE);
                while (GUI->InfoDiag->shown()) Fl::wait();
                EndGame(false);
            }
        }
    }

    PlayerListen();

    ResolveCollision(PlayerPtr->CavePtr);

}

void Game::PlayerShoot()
{
    // if no arrows - impossible situation, but
    if (PlayerPtr->ArrowsCount == 0)
    {
        return;
    }

    SP->Play(SoundName::BOW_STRING);

    std::vector<Cave*> ShootTrajectory;
    for (int CaveNum : GUI->ShootDiag->PathOut->CaveNumbersInPath)
    {
        ShootTrajectory.push_back(Caves[CaveNum]);
    }

    if (ShootTrajectory.empty())
    {
        return;
    }

    // Shoot
    Arrow* ArrowPtr = static_cast<Arrow*>(UnitFactory<Arrow>(PlayerPtr->CavePtr));
    ArrowPtr->Energy = ShootTrajectory.size(); // player shoot with less power == less caves
    PlayerPtr->ArrowsCount--;
    GUI->HideOneArrow();
    if (!WampusPtr->IsAwake)
    {
        WampusPtr->IsAwake = true;
        Sleep(700);
        SP->Play(SoundName::WAMPUS_WAKE_UP);
    }
    bool BadTrajectory = false;
    Cave* CurrentCavePtr = ShootTrajectory[0];
    Cave* TargetCavePtr = ShootTrajectory[0];
    int CurrentCaveOrder{};
    while (true)
    {
        if (ArrowPtr->Energy < 1)
        {
            DestroyUnit(ArrowPtr);
            break;
        }

        if (!BadTrajectory && std::find(ArrowPtr->CavePtr->AdjacentCaves.begin(), ArrowPtr->CavePtr->AdjacentCaves.end(), TargetCavePtr) == ArrowPtr->CavePtr->AdjacentCaves.end())
        {
            BadTrajectory = true;
        }

        if (BadTrajectory)
        {
            TargetCavePtr = CurrentCavePtr->AdjacentCaves[roll_d3() - 1];
        }

        SP->Play(SoundName::ARROW_WHOOSH);
        Sleep(200);

        MoveUnit(ArrowPtr, ArrowPtr->CavePtr, TargetCavePtr);
        CurrentCavePtr = TargetCavePtr;
        --ArrowPtr->Energy;

        ResolveCollision(CurrentCavePtr);

        if (!BadTrajectory && CurrentCaveOrder < ShootTrajectory.size()-1)
        {
            ++CurrentCaveOrder;
            TargetCavePtr = ShootTrajectory[CurrentCaveOrder];
        }

    if (!PlayerPtr->ArrowsCount)
    {
        GUI->InfoDiag->ShowInfo(GUI->InfoDiag->GAMEOVER_NO_ARROWS);
        SP->Play(SoundName::PLAYER_DIE);
        EndGame(false);
        return;
    }

    }
}


void Game::ResolveCollision(Cave* CavePtr)
{

    if (CavePtr->Units.size() < 2)
    {
        return;
    }

    // arrow in cave
    if (std::find_if(CavePtr->Units.begin(), CavePtr->Units.end(), [](Unit* UnitPtr) {return typeid(Arrow) == typeid(*UnitPtr); }) != CavePtr->Units.end())
    {
        // player killed wampus
        if (std::find_if(CavePtr->Units.begin(), CavePtr->Units.end(), [this](Unit* UnitPtr) {return WampusPtr == UnitPtr; }) != CavePtr->Units.end())
        {
            SP->Play(SoundName::WAMPUS_DIE);
            GUI->InfoDiag->ShowInfo(GUI->InfoDiag->YOUWIN);
            EndGame(true);
        }
        // arrow killed player
        if (std::find_if(CavePtr->Units.begin(), CavePtr->Units.end(), [this](Unit* UnitPtr) {return PlayerPtr == UnitPtr; }) != CavePtr->Units.end())
        {
            SP->Play(SoundName::PLAYER_DIE);
            GUI->InfoDiag->ShowInfo(GUI->InfoDiag->GAMEOVER_ARROW);
            EndGame(false);
        }
        return;
    }

    for (Unit* UnitPtr : CavePtr->Units)
    {
        // bats
        if (typeid(*UnitPtr) == typeid(Bat))
        {
            // lets fly!
            int RandomCaveNum{};
            while (true)
            {
                RandomCaveNum = roll_d20();
                if (RandomCaveNum != PlayerPtr->CavePtr->Num)
                {
                    break;
                }
            }
            SP->Play(SoundName::PLAYER_DIE);
            GUI->InfoDiag->ShowInfo(GUI->InfoDiag->BATS);
            Self->SP->FadeOutAllExceptBackground(2);
            PlayerMove(RandomCaveNum);
            break;
        }

        // Pit
        if (typeid(*UnitPtr) == typeid(Pit))
        {
            SP->Play(SoundName::PLAYER_FALL);
            GUI->InfoDiag->ShowInfo(GUI->InfoDiag->GAMEOVER_PIT);
            EndGame(false);
        }

        // Wampus
        if (UnitPtr == WampusPtr)
        {
            if (WampusPtr->IsAwake)
            {
                SP->Play(SoundName::PLAYER_DIE);
                GUI->InfoDiag->ShowInfo(GUI->InfoDiag->GAMEOVER_WAMPUS);
                EndGame(false);
            }
            else
            {
                WampusPtr->IsAwake = true;
                if (roll_d100() > 75)
                {
                    // Wampus stay in same room
                    ResolveCollision(PlayerPtr->CavePtr);
                }
                else
                {
                    // Wampus left the room
                    MoveUnit(WampusPtr, WampusPtr->CavePtr, WampusPtr->CavePtr->AdjacentCaves[roll_d3()-1]);
                }
            }
        }
    }
    

}

bool Game::IsDialogOpen()
{
    return bool(GUI->InfoDiag->visible());
}

void Game::InitRandom()
{
    RandomEngine = std::default_random_engine(RandomDevice());
}
