#pragma once
#include "GameUtils.h"
#include "Input.h"
#include "World.h"

class Game {
    private:
        World gameWorld;
        Input input;
        int userMove;
    public:
        Game() : gameWorld(), input(), userMove(NO_PROPER_KEY) { }
        void StartGame();
    private:
        void PlayRounds();
        void GetUserMove();
        void CreateWorld();
        void PrintLegend() const;
        void LogEvents(const std::string events) const;
        void PrintAuthor() const;
        void InitWordlDimensions();
        void ClearTerminal() const;
        void InitOrganisms();
        void InitSrand() const;
};