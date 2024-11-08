// License file: COPYING.WTFPL. Author: diego1812@gmail.com
#pragma once

#include <vector>
#include <random>

#include "Cave.h"
#include "Unit.h"
#include "Wampus.h"
#include "Player.h"
#include "GameWindow.h"
#include "SoundPlayer.h"

enum class PlayerAnswer {Move, Shoot, Yes, No};

class Game
{
public:
    Game();
    ~Game();

    void _DebugPrintCavesUnits();
    void PrapareGame();

    static inline Game* Self;

private:
    // GUI - graphical user interface
    GameWindow* GUI = new GameWindow{};
    bool IsDialogOpen();

    // sound
    SoundPlayer* SP = new SoundPlayer{};

    // prep & backwork
    void InitRandom();
    void LinkCaves();
    void PlaceUnits();
    Cave* GetRandomEmptyCave();
    template<typename T> Unit* UnitFactory(bool IsPlayer = false);
    template<typename T> Unit* UnitFactory(Cave* CavePtr);
    void DestroyUnit(Unit* TargetUnitPtr);
    
    // game logic
    void ResolveCollision(Cave* CavePtr);
    void PlayerMove(int TunnelNumber);
    void PlayerShoot();
    void PlayerListen();
    void MoveUnit(Unit* TargetUnit, Cave* FromCave, Cave* ToCave);
    void EndGame(SoundName, InfoDialog::Type);
    void WampusWanders();

    // fields
    std::vector<Cave*> Caves;
    std::vector<Unit*> Units;
    Wampus* WampusPtr;
    Player* PlayerPtr;

    // random
    std::random_device RandomDevice;
    std::default_random_engine RandomEngine;
    int roll_d3() {return std::uniform_int<int> {1, 3} (RandomEngine);}
    int roll_d20() {return std::uniform_int<int> {1, 20} (RandomEngine);}
    int roll_d100() {return std::uniform_int<int> {1, 100} (RandomEngine);}

    // callbacks
    static void CbIdle(void* Data);
    static void CbKeyboardHit(Fl_Widget* Widget);
    static void CbClickQuit(Fl_Widget* Widget);
    static void CbClickTunnel(Fl_Widget* Widget, void* TunnelNumber);
    static void CbClickBow(Fl_Widget* Widget);
    static void CbClickSDErase(Fl_Widget* Widget);
    static void CbClickSDCaveNumberButton(Fl_Widget* Widget);
    static void CbClickInfoDiagOk(Fl_Widget* Widget);
    static void CbClickMapCave(Fl_Widget* Widget);

    static void CbClickHelpWinOk(Fl_Widget* Widget);
    static void CbClickHelpBtn(Fl_Widget* Widget);
};
