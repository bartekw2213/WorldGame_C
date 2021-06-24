#include <iostream>
#include <ctime>
#include "Game.h"

void Game::StartGame() {
    CreateWorld();
    PlayRounds();
}

void Game::CreateWorld() {
    InitSrand();
    InitWordlDimensions();
    InitOrganisms();
}

void Game::PlayRounds() {
    while(userMove != KEY_QUIT) {
        ClearTerminal();
        PrintAuthor();
        gameWorld.PrintWorld();
        PrintLegend();
        LogEvents(gameWorld.GetEventsFromLastRound());
        GetUserMove();
        gameWorld.MakeMove(userMove);
    }
}

void Game::InitWordlDimensions() {
    unsigned int width = 0, height = 0;
    while(width <= 0 && height <= 0) {
        std::cout << "Wprowadz szerokosc swiata: ";
        std::cin >> width;
        std::cout << "Wprowadz wysokosc swiata: ";
        std::cin >> height;
    }
    gameWorld.InitDimensions(width, height);
}

void Game::InitSrand() const {
    srand(time(NULL));
}

void Game::InitOrganisms() {
    unsigned int organismsNum = 0;
    while(organismsNum <= 0) {
        std::cout << "Wprowadz ilosc organizmow: ";
        std::cin >> organismsNum;
    }
    try {
        gameWorld.InitOrganisms(organismsNum);
    } catch (const char* error) {
        std::cout << error << std::endl;
        InitOrganisms();
    }
}

void Game::ClearTerminal() const {
    // system("CLS");      // Windows
    system("clear");    // Linux
}

void Game::PrintAuthor() const {
    std::cout << '\t' << "Bartlomiej" << " " << "Wilczynski" << " nr 184899" << '\n';
}

void Game::PrintLegend() const {
    std::cout << "\n" << WOLF_SYMBOL << " wilk  " << SHEEP_SYMBOL << " owca " << FOX_SYMBOL << " lis  " 
        << TURTLE_SYMBOL << " zolw  " << ANTELOPE_SYMBOL << " antylopa  " << HUMAN_SYMBOL << " gracz  " 
        << GRASS_SYMBOL << " trawa\n" << SONCHUS_SYMBOL << " mlecz  " << GUARANA_SYMBOL << " guarana  "
        << BERRIES_SYMBOL << " jagody  " << SOSNOWSKI_BARSCH_SYMBOL << " barszcz  \n"
        << "Q - wyjście\tS - Supermoc\n\n";
}

void Game::LogEvents(const std::string events) const {
    std::cout << events;
}

void Game::GetUserMove() {
    do {
        userMove = input.GetGameKeyPresses();
    } while(userMove == NO_PROPER_KEY);
}