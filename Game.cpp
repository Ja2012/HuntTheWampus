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
    GUI->callback(CallbackKeyboardHit);
    GUI->QuitBtn->callback(CallbackClickQuit);
    GUI->Tunnel1->callback(CallbackClickTunnel, GUI->Tunnel1->TunnelNum);
    GUI->Tunnel2->callback(CallbackClickTunnel, GUI->Tunnel2->TunnelNum);
    GUI->Tunnel3->callback(CallbackClickTunnel, GUI->Tunnel3->TunnelNum);
    GUI->BowBtn->callback(CallbackClickBow);
}

void Game::MainLoop()
{
    int TurnNumber = 1;
    while (true)
    {
        std::wcout << L"\n-------- Ход " << TurnNumber << " --------\n";
        //_DebugPrintCavesUnits();
        PrintInfo();

        PlayerAnswer PlayerDesicion = AskWhatPlayerWantToDo();
        if (PlayerDesicion == PlayerAnswer::Move)
        {
            //PlayerMove();
        }
        else if (PlayerDesicion == PlayerAnswer::Shoot)
        {
            PlayerShoot();
        }
        
        if (WampusPtr->IsAwake)
        {
            if (roll_d100() <= 75)
            {
                MoveUnit(WampusPtr, WampusPtr->CavePtr, WampusPtr->CavePtr->AdjacentCaves[roll_d3()-1]);
                if (WampusPtr->CavePtr == PlayerPtr->CavePtr)
                {
                    std::wcout << L"Одновременно с вами в пещеру " << PlayerPtr->CavePtr->Num << L" заходит Вампус!\n";
                }
            }
        }

        ResolveCollision(PlayerPtr->CavePtr);

        ++TurnNumber;
    }

}

void Game::PrapareGame()
{
    InitRandom();
    LinkCaves();
    PlaceUnits();

    PlayerMove(PlayerPtr->CavePtr->Num);
}

void Game::Start()
{   
    PrapareGame();

    std::wcout << L"Здравствуйте. Добро пожаловать в игру \"Убей Вампуса\".\n" 
        << L"Цель игры - убить монстра из лука в тёмной системе пещер.\n" 
        << L"---\n" 
        << L"У вас есть 5 стрел. Стрелы необычные,\n" 
        << L"так как они могут лететь по заданному вами маршруту.\n" 
        << L"Для этого, после команды стрелять нужно ввести последовательность\n" 
        << L"пролёта пещер. Например: 5 3 20. До 5 пещер включительно.\n" 
        << L"Если пещера указана неправильно, стрела полетит случайно и может убить Вас.\n" 
        << L"---\n" 
        << L"Также в пещерах есть другие существа и препятствия.\n" 
        << L"Ваш тонкий слух поможет ориентироваться\n" 
        << L"Начнём!\n\n";

    MainLoop();

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
    if (IsWin)
    {
        std::wcout << L"\n\n\n********\nВы прошли игру! Поздравляем!\n********\n\n\n";
    } 
    WaitForKey();
    exit(0);

    //std::wcout << L"Попробовать ещё раз?\n";
    //if (AskYesNo() == PlayerAnswer::Yes)
    //{
    //    //TODO 
    //    exit(0);
    //}
    //else
    //{
    //    //TODO
    //    exit(0);
    //}
}

void Game::WaitForKey()
{
    std::wcout << L"(нажмите любую кнопку чтобы продолжить)\n";
    while(!_kbhit()) { }
    _getch();
}

void Game::CallbackKeyboardHit(Fl_Widget* Widget)
{
    if (Fl::event() == FL_SHORTCUT && Fl::event_key() == FL_Escape)
    {
        return; // ignore Escape
    }
}

void Game::CallbackClickQuit(Fl_Widget* Widget)
{
    if (Fl::event() == FL_SHORTCUT && Fl::event_key() == FL_Escape)
    {
        return; // ignore Escape
    }
	exit(0); 
}

void Game::CallbackClickTunnel(Fl_Widget* Widget, void* TunnelNumber)
{
    std::cout << *static_cast<int*>(TunnelNumber) << '\n';
    Self->SP->Play(SoundName::WALK);
    Self->PlayerMove(*static_cast<int*>(TunnelNumber));
}

void Game::CallbackClickBow(Fl_Widget* Widget)
{
    Self->SP->Play(SoundName::BOW_READY);
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


void Game::PrintInfo()
{
    Cave* AdjacentCave1 = PlayerPtr->CavePtr->AdjacentCaves[0];
    Cave* AdjacentCave2 = PlayerPtr->CavePtr->AdjacentCaves[1];
    Cave* AdjacentCave3 = PlayerPtr->CavePtr->AdjacentCaves[2];
    std::wcout << L"Вы в пещере номер " << PlayerPtr->CavePtr->Num
        << L". Туннели ведут в пещеры номер: "
        << AdjacentCave1->Num << L", "
        << AdjacentCave2->Num << L", "
        << AdjacentCave3->Num << L".\n";

    std::vector<Cave*> ShuffledCaves {AdjacentCave1, AdjacentCave2, AdjacentCave3};
    std::shuffle(ShuffledCaves.begin(), ShuffledCaves.end(), RandomEngine);

    for (Cave* CavePtr : ShuffledCaves)
    {
        for (Unit* UnitPtr : CavePtr->Units)
        {
            if (typeid(*UnitPtr) == typeid(Wampus))
            {
                if (static_cast<Wampus*>(UnitPtr)->IsAwake)
                {
                    std::wcout << L"Слышно как кто-то топает\n";
                }
                else
                {
                    std::wcout << L"Слышно как кто-то храпит\n";
                }
            }
            else if (typeid(*UnitPtr) == typeid(Bat))
            {
                std::wcout << L"Слышно хлопот крыльев\n";
            }
            else if (typeid(*UnitPtr) == typeid(Pit))
            {
                std::wcout << L"Слышно завывание ветра\n";
            }
        }
    }

}


inline bool IsNumber(const std::wstring& Str)
{
    return !Str.empty() && std::find_if(Str.begin(), Str.end(), [](wchar_t Char) {return !iswdigit(Char); }) == Str.end();
}


void Game::PlayerMove(int TunnelNumber)
{
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
}

void Game::PlayerShoot()
{
    Cave* AdjacentCave1 = PlayerPtr->CavePtr->AdjacentCaves[0];
    Cave* AdjacentCave2 = PlayerPtr->CavePtr->AdjacentCaves[1];
    Cave* AdjacentCave3 = PlayerPtr->CavePtr->AdjacentCaves[2];

    // Get user input
    std::vector<Cave*> ShootTrajectory;
    std::wstring Input;
    int CaveNumber{0};
    int PreviousCaveNumber{-1};
    std::wistringstream StringStream;
    std::wcin.ignore(10, '\n');
    while (true)
    {   
        Input.clear();
        std::wcout << L"Куда стрелять: ";
        std::getline(std::wcin, Input);
        if (Input.empty())
        {
            continue;
        }
        if (!iswdigit(Input[0]))
        {
            std::wcout << L"Ошибка. Вводите до 5 цифр включительно (от 1 до 20 включительно) через пробел\n";
            continue;
        }

        bool InputError = false;
        StringStream = std::wistringstream{ Input };
        while (StringStream >> CaveNumber)
        {
            if (CaveNumber == PreviousCaveNumber)
            {
                std::wcout << L"Ошибка. Введены подряд одинаковые цифры\n";
                InputError = true;
            }
            PreviousCaveNumber = CaveNumber;

            if (CaveNumber == PlayerPtr->CavePtr->Num)
            {
                std::wcout << L"Ошибка. Вы ввели номер своей пещеры. Хотите убить себя!?\n";
                InputError = true;
            }
            if (!(0 < CaveNumber && CaveNumber < 21))
            {
                std::wcout << L"Ошибка. Вводите до 5 цифр включительно (от 1 до 20 включительно) через пробел\n";
                InputError = true;
            }
            if (ShootTrajectory.size() > 4)
            {
                std::wcout << L"Ошибка. Вы ввели больше 5 цифр\n";
                InputError = true;
            }
            if (InputError)
            {
                InputError = false;
                ShootTrajectory.clear();
                break;
            }

            ShootTrajectory.push_back(Caves[CaveNumber]);
        }

        if (!ShootTrajectory.empty() && !(ShootTrajectory[0] == AdjacentCave1 || ShootTrajectory[0] == AdjacentCave2 || ShootTrajectory[0] == AdjacentCave3))
        {
            std::wcout << L"Ошибка. Первая цифра должна быть: " << AdjacentCave1->Num << L" или " << AdjacentCave2->Num << L" или " << AdjacentCave3->Num << L"\n";
            ShootTrajectory.clear();
            continue;
        }

        if (!ShootTrajectory.empty())
        {
            break;
        }
    }

    // Shoot
    Arrow* ArrowPtr = static_cast<Arrow*>(UnitFactory<Arrow>(PlayerPtr->CavePtr));
    ArrowPtr->Energy = ShootTrajectory.size(); // player shoot with less power == less caves
    PlayerPtr->ArrowsCount--;
    if (!WampusPtr->IsAwake)
    {
        WampusPtr->IsAwake = true;
        std::wcout << L"Ааррр, вы слышите чей-то рёв. Кажется вы кого-то разбудили 0_0\n";
    }
    bool BadTrajectory = false;
    Cave* CurrentCavePtr = ShootTrajectory[0];
    Cave* TargetCavePtr = ShootTrajectory[0];
    int CurrentCaveOrder{};
    while (true)
    {
        if (ArrowPtr->Energy < 1)
        {
            //std::wcout << L"// стрела устала\n";
            DestroyUnit(ArrowPtr);
            break;
        }

        if (!BadTrajectory && std::find(ArrowPtr->CavePtr->AdjacentCaves.begin(), ArrowPtr->CavePtr->AdjacentCaves.end(), TargetCavePtr) == ArrowPtr->CavePtr->AdjacentCaves.end())
        {
            BadTrajectory = true;
            //std::wcout << L"// стрела сбилась - летит случайно\n";
        }

        if (BadTrajectory)
        {
            TargetCavePtr = CurrentCavePtr->AdjacentCaves[roll_d3() - 1];
        }

        // fly fly
        //std::wcout << L"// стрела c энергией " << ArrowPtr->Energy << L" летит в пещеру " << TargetCavePtr->Number << L'\n';
        std::wcout << L"вжууух\n";
        MoveUnit(ArrowPtr, ArrowPtr->CavePtr, TargetCavePtr);
        CurrentCavePtr = TargetCavePtr;
        --ArrowPtr->Energy;

        ResolveCollision(CurrentCavePtr);

        if (!BadTrajectory && CurrentCaveOrder < ShootTrajectory.size()-1)
        {
            ++CurrentCaveOrder;
            TargetCavePtr = ShootTrajectory[CurrentCaveOrder];
        }

    std::wcout << L"тук-тук\n";
    WaitForKey();
    if (!PlayerPtr->ArrowsCount)
    {
        std::wcout << L"Вы промазали и у вас закончились стрелы! В конце концов Вампус нашёл вас и слопал =*(\n";
        WaitForKey();
        EndGame(false);
        return;
    }

    }
}

PlayerAnswer Game::AskWhatPlayerWantToDo()
{
    std::wstring Input;
    while (true)
    {
        std::wcout << L"Чтобы двигаться напишите \"Д\", чтобы стрелять \"С\": ";
        std::wcin >> Input;

        if (Input == L"д" || Input == L"Д")
        {
            return PlayerAnswer::Move;
        }
        else if (Input == L"с" || Input == L"С")
        {
            return PlayerAnswer::Shoot;
        }
     }
 }

PlayerAnswer Game::AskYesNo()
{
    std::wstring Input;
    while (true)
    {
        std::wcout << L"\"да\" или \"нет\": ";
        std::wcin >> Input;

        if (Input == L"да")
        {
            return PlayerAnswer::Yes;
        }
        else if (Input == L"нет")
        {
            return PlayerAnswer::No;
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
        if (std::find_if(CavePtr->Units.begin(), CavePtr->Units.end(), [this](Unit* UnitPtr) {return WampusPtr == UnitPtr; }) != CavePtr->Units.end())
        {
            std::wcout << L"ЧПОНЬК!!! Вы попали в Вампуса. Монстр убит.\n";
            WaitForKey();
            EndGame(true);
        }
        if (std::find_if(CavePtr->Units.begin(), CavePtr->Units.end(), [this](Unit* UnitPtr) {return PlayerPtr == UnitPtr; }) != CavePtr->Units.end())
        {
            std::wcout << L"АЙ!!! Стрела попала в вас. Вы погибли =*(\n";
            WaitForKey();
            EndGame(false);
        }
        return;
    }


    for (Unit* UnitPtr : CavePtr->Units)
    {
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
            MoveUnit(PlayerPtr, PlayerPtr->CavePtr, Caves[RandomCaveNum]);
            std::wcout << L"Вы вспугнули летучих мышей. Они схватили вас и перенесли в другую пещеру\n";
            WaitForKey();
            //std::wcout << L"// Крысы бросают игрока в пещеру номер " << RandomCaveNum << L'\n';
            ResolveCollision(PlayerPtr->CavePtr);
            break;
        }

        // Pit
        if (typeid(*UnitPtr) == typeid(Pit))
        {
            std::wcout << L"УУИИИИ!!! Вы упали в пропасть и разбились =*(\n";
            WaitForKey();
            EndGame(false);
        }

        // Wampus
        if (UnitPtr == WampusPtr)
        {
            if (WampusPtr->IsAwake)
            {
                std::wcout << L"Вампус помахал вам рукой, а потом слопал =*(\n";
                WaitForKey();
                EndGame(false);
            }
            else
            {
                std::wcout << L"Вы разбудили Вампуса. ";
                WaitForKey();
                WampusPtr->IsAwake = true;
                if (roll_d100() > 75)
                {
                    ResolveCollision(PlayerPtr->CavePtr);
                }
                else
                {
                    MoveUnit(WampusPtr, WampusPtr->CavePtr, WampusPtr->CavePtr->AdjacentCaves[roll_d3()-1]);
                    std::wcout << L"Он испугался и убежал\n";
                    WaitForKey();
                }
            }
        }
    }
    

}


void Game::InitRandom()
{
    RandomEngine = std::default_random_engine(RandomDevice());
}
