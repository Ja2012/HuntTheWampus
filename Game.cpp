// License file: COPYING.WTFPL. Author: diego1812@gmail.com
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

    GUI->HelpBtn->callback(CbClickHelpBtn);
    GUI->HelpWin->OkBtn->callback(CbClickHelpWinOk);

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
    _DebugPrintCavesUnits();
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

void Game::EndGame(SoundName SN, InfoDialog::Type T)
{
    Self->SP->FadeOutAllExceptBackground(1);
    Sleep(1000);
    SP->Play(SN);
    GUI->InfoDiag->ShowInfo(T);
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


void Game::CbClickHelpBtn(Fl_Widget* Widget)
{
    Self->GUI->HelpWin->show();
}

void Game::CbClickHelpWinOk(Fl_Widget* Widget)
{
    Self->GUI->HelpWin->hide();
}



void Game::_DebugPrintCavesUnits()
{   
    std::cout << "\v\v";
    for(Cave* CavePtr: Caves)
    {
        std::cout << "// Cave " << CavePtr->Num << ": ";
        for(Unit* UnitPtr: CavePtr->Units)
        {
            std::wcout << typeid(*UnitPtr).name() << ", ";
        }
        std::cout << '\n';
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
Unit* Game::UnitFactory(bool IsPlayer)
{
    Unit* UnitPtr = new UnitType();

    Cave* CavePtr;
    if (IsPlayer)
    {
        while (true)
        {
            CavePtr = GetRandomEmptyCave();
            if (std::all_of(CavePtr->AdjacentCaves.begin(), CavePtr->AdjacentCaves.end(),
                [](Cave* C) {return C->Units.empty(); }))
            {
                break;
            }
        }
    }
    else CavePtr = GetRandomEmptyCave();

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
    WampusPtr = static_cast<Wampus*>(UnitFactory<Wampus>());
    UnitFactory<Bat>();
    UnitFactory<Bat>();
    UnitFactory<Pit>();
    UnitFactory<Pit>();
    // player last, to ensure that adjacent caves are empty (too difficult to start with something around)
    PlayerPtr = static_cast<Player*>(UnitFactory<Player>(true));

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

    SP->FadeOutAllExceptBackground(0.5);
    for (Cave* CavePtr : ShuffledCaves)
    {
        for (Unit* UnitPtr : CavePtr->Units)
        {
            if (typeid(*UnitPtr) == typeid(Wampus))
            {
                if (static_cast<Wampus*>(UnitPtr)->IsAwake)
                {
                    SP->PlayFadeIn(SoundName::NEAR_WAMPUS_AWAKE, 4);
                }
                else
                {
                    SP->PlayFadeIn(SoundName::NEAR_WAMPUS_SLEEP, 4);
                }
            }
            else if (typeid(*UnitPtr) == typeid(Bat))
            {
                SP->PlayFadeIn(SoundName::NEAR_BATS, 4);
            }
            else if (typeid(*UnitPtr) == typeid(Pit))
            {
                SP->PlayFadeIn(SoundName::NEAR_PIT, 4);
            }
        }
    }

}

void Game::PlayerMove(int TunnelNumber)
{
    Sleep(800);

    // move player map mark and update player pos
    GUI->Map->UnsetPlayerCaveMark(PlayerPtr->CavePtr->Num);
    MoveUnit(PlayerPtr, PlayerPtr->CavePtr, Caves[TunnelNumber]);
    GUI->Map->SetPlayerCaveMark(TunnelNumber);
    
    // show adjancent caves on map
    GUI->Map->ShowCave(TunnelNumber);
    for (int CaveNumber : PlayerPtr->CavePtr->AdjCaveNumbers)
    {
        GUI->Map->ShowCave(CaveNumber);
    }

    // update tunnels numbers
    GUI->Tunnel1->SetLabel(PlayerPtr->CavePtr->AdjCaveNumbers[0]);
    GUI->Tunnel2->SetLabel(PlayerPtr->CavePtr->AdjCaveNumbers[1]);
    GUI->Tunnel3->SetLabel(PlayerPtr->CavePtr->AdjCaveNumbers[2]);

    GUI->Map->redraw();

    // clean shooting path and update options where to shoot
    GUI->ShootDiag->PathOut->Clear();
    GUI->ShootDiag->ShowCaveNumbers(
        {
            PlayerPtr->CavePtr->AdjCaveNumbers[0],
            PlayerPtr->CavePtr->AdjCaveNumbers[1],
            PlayerPtr->CavePtr->AdjCaveNumbers[2]
        }
    );
    WampusWanders();
    ResolveCollision(PlayerPtr->CavePtr);
    PlayerListen();
    _DebugPrintCavesUnits();



}

void Game::WampusWanders()
{
    // if wampus in awake - he move in random cave
    if (WampusPtr->IsAwake)
    {
        if (roll_d100() <= 75)
        {
            MoveUnit(WampusPtr, WampusPtr->CavePtr, WampusPtr->CavePtr->AdjacentCaves[roll_d3() - 1]);
            if (WampusPtr->CavePtr == PlayerPtr->CavePtr)
            {
                EndGame(SoundName::PLAYER_DIE, GUI->InfoDiag->GAMEOVER_WAMPUS_WALK_IN_SAME_CAVE);
            }
        }
    }

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

        if (
            WampusPtr->CavePtr == PlayerPtr->CavePtr->AdjacentCaves[0] ||
            WampusPtr->CavePtr == PlayerPtr->CavePtr->AdjacentCaves[1] ||
            WampusPtr->CavePtr == PlayerPtr->CavePtr->AdjacentCaves[2]
            )
        {
            SP->PlayFadeOut(SoundName::NEAR_WAMPUS_SLEEP, 0.2);
            Sleep(500);
            SP->Play(SoundName::WAMPUS_WAKE_UP);
            Sleep(500);
            SP->PlayFadeIn(SoundName::NEAR_WAMPUS_AWAKE, 0.5);

        }
        else
        {
            SP->Play(SoundName::WAMPUS_WAKE_UP);

        }
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

        if (!BadTrajectory && CurrentCaveOrder < ShootTrajectory.size() - 1)
        {
            ++CurrentCaveOrder;
            TargetCavePtr = ShootTrajectory[CurrentCaveOrder];
        }
    }

    if (!PlayerPtr->ArrowsCount)
    {
        EndGame(SoundName::SAD_TROMBONE, GUI->InfoDiag->GAMEOVER_NO_ARROWS);
    }

    WampusWanders();
    if (
        WampusPtr->CavePtr == PlayerPtr->CavePtr->AdjacentCaves[0] ||
        WampusPtr->CavePtr == PlayerPtr->CavePtr->AdjacentCaves[1] ||
        WampusPtr->CavePtr == PlayerPtr->CavePtr->AdjacentCaves[2]
        )
    {
        SP->PlayFadeIn(SoundName::NEAR_WAMPUS_AWAKE, 0.5);

    }
    else
    {
        SP->PlayFadeOut(SoundName::NEAR_WAMPUS_AWAKE, 0.5);

    }

    _DebugPrintCavesUnits();

    // clean shooting path and update options where to shoot
    GUI->ShootDiag->PathOut->Clear();
    GUI->ShootDiag->ShowCaveNumbers(
        {
            PlayerPtr->CavePtr->AdjCaveNumbers[0],
            PlayerPtr->CavePtr->AdjCaveNumbers[1],
            PlayerPtr->CavePtr->AdjCaveNumbers[2]
        }
    );

}


void Game::ResolveCollision(Cave* CavePtr)
{

    if (CavePtr->Units.size() < 2)
    {
        return;
    }

    bool ArrowInCave{ false };
    bool BatsInCave{ false };
    bool PitInCave{ false };
    bool WampusInCave{ false };
    bool PlayerInCave{ false };
    for (Unit* UnitPtr : CavePtr->Units)
    {
        const std::type_info& UnitType = typeid(*UnitPtr);
        if (UnitType == typeid(Arrow)) ArrowInCave = true;
        else if (UnitType == typeid(Bat)) BatsInCave = true;
        else if (UnitType == typeid(Pit)) PitInCave = true;
        else if (UnitType == typeid(Wampus)) WampusInCave = true;
        else if (UnitType == typeid(Player)) PlayerInCave = true;
    }

    if (ArrowInCave && WampusInCave) EndGame(SoundName::WAMPUS_DIE, GUI->InfoDiag->YOUWIN);

    if (ArrowInCave && PlayerInCave) EndGame(SoundName::PLAYER_DIE, GUI->InfoDiag->GAMEOVER_ARROW);

    if (BatsInCave && PlayerInCave)
    {
        int RandomCaveNum{};
        while (true)
        {
            RandomCaveNum = roll_d20();
            if (RandomCaveNum != PlayerPtr->CavePtr->Num)
            {
                break;
            }
        }
        Self->SP->FadeOutAllExceptBackground(1);
        Sleep(1000);
        SP->Play(SoundName::BATS_IN_FACE);
        GUI->InfoDiag->ShowInfo(GUI->InfoDiag->BATS);
        PlayerMove(RandomCaveNum);
        ResolveCollision(Caves[RandomCaveNum]);
    }

    if (PitInCave && PlayerInCave) EndGame(SoundName::PLAYER_FALL, GUI->InfoDiag->GAMEOVER_PIT);

    if (WampusInCave && PlayerInCave)
    {
        if (WampusPtr->IsAwake)
        {
            EndGame(SoundName::PLAYER_DIE, GUI->InfoDiag->GAMEOVER_WAMPUS);
        }
        else
        {
            WampusPtr->IsAwake = true;
            SP->PlayFadeOut(SoundName::NEAR_WAMPUS_SLEEP, 0.2);
            if (roll_d100() > 75)
            {
                // Wampus stay in same room and kill player
                EndGame(SoundName::WAMPUS_WAKE_UP, GUI->InfoDiag->GAMEOVER_WOKE_UP_WAMPUS);
            }
            else
            {
                // Wampus left the room
                GUI->InfoDiag->ShowInfo(GUI->InfoDiag->WAMPUS_RUN);
                MoveUnit(WampusPtr, WampusPtr->CavePtr, WampusPtr->CavePtr->AdjacentCaves[roll_d3() - 1]);            
            }
        }
    }
}

bool Game::IsDialogOpen()
{
    return bool(GUI->InfoDiag->visible() || GUI->HelpWin->visible());
}

void Game::InitRandom()
{
    RandomEngine = std::default_random_engine(RandomDevice());
}
