#include <iostream>
#include <algorithm>
#include "World.h"
#include "Animals.h"
#include "Plants.h"

World::World() : allOrganisms(), eventsThatHappenedInRound(), wordlHeight(0), 
    worldWidth(), userLastMove(NO_PROPER_KEY) { }

World::~World() {
    for(Organism* organism : allOrganisms)
        delete organism;
}

void World::PrintWorld() const {
    for(int i = 0; i < worldWidth + 2; i++)
        std::cout << DIVIDER_BLOCK;
    std::cout << "\n";

    for(int i = 0; i < wordlHeight; i++) {
        std::cout << DIVIDER_BLOCK;
        for(int j = 0; j < worldWidth; j++) {
            Organism* foundOrganism = FindWhoStandsOnThisPosition(position(j,i));

            if(foundOrganism != nullptr) {
                foundOrganism->Draw();
            } else 
                std::cout << "  ";
        }
        std::cout << DIVIDER_BLOCK << "\n";
    }
    
    for(int i = 0; i < worldWidth + 2; i++)
        std::cout << DIVIDER_BLOCK;
    std::cout << "\n";
}

void World::InitDimensions(const int width, const int height) {
    worldWidth = width;
    wordlHeight = height;
}

void World::InitOrganisms(int organismsNum) {
    if(organismsNum >= (worldWidth * wordlHeight))
        throw "Za duzo organizmow";

    int humanNum = 1;
    int animalsNum = (int)((organismsNum - humanNum) * HOW_MANY_PERCENTAGE_OF_ORGANISMS_ARE_ANIMALS/100);
    int plantsNum = organismsNum - humanNum - animalsNum;

    allOrganisms.reserve(worldWidth*wordlHeight);
    CreateAnimals(animalsNum);
    CreatePlants(plantsNum);
    CreateHuman();
}

void World::CreateAnimals(const int animalsNum) {
    using namespace animals;

    for(int i = 0; i < animalsNum; i++) {
        int animalTypeNum = rand() % ANIMAL_TYPES_NUM;

        switch (animalTypeNum) {
            case 0: CreateOrganism<Wolf>(); break;
            case 1: CreateOrganism<Sheep>(); break;
            case 2: CreateOrganism<Fox>(); break;
            case 3: CreateOrganism<Turtle>(); break;
            case 4: CreateOrganism<Antelope>(); break;
        }
    }
}

void World::CreatePlants(const int plantsNum) {
    using namespace plants;
    
    for(int i = 0; i < plantsNum; i++) {
        int plantTypeNum = rand() % PLANT_TYPES_NUM;

        switch (plantTypeNum) {
            case 0: CreateOrganism<Grass>(); break;
            case 1: CreateOrganism<Sonchus>(); break;
            case 2: CreateOrganism<Guarana>(); break;
            case 3: CreateOrganism<Berries>(); break;
            case 4: CreateOrganism<SosnowskiBorsch>(); break;
        }
    }
}

void World::CreateHuman() {
    CreateOrganism<animals::Human>();
}

template<typename T>
void World::CreateOrganism() {
    position freePosition;

    do {
        freePosition.x = rand() % worldWidth;
        freePosition.y = rand() % wordlHeight;
    } while(FindWhoStandsOnThisPosition(freePosition) != nullptr);

    allOrganisms.push_back(new T(this, freePosition));
}

Organism* World::FindWhoStandsOnThisPosition(const position& checkedPosition, Organism* organismToIgnore) const {
    Organism* foundOrganism = nullptr;
    
    for(Organism* organism : allOrganisms)
        if(organism->IsStandingHere(checkedPosition) && organism != organismToIgnore) {
            foundOrganism = organism;
            break;
        }

    return foundOrganism;
}

void World::MakeMove(const int userMove) {
    SortOrganisms();
    userLastMove = userMove;
    for(int i = 0; i < allOrganisms.size(); i++) {
        allOrganisms[i]->IncrementAge();
        allOrganisms[i]->Action(worldWidth, wordlHeight);
    }
}

void World::SortOrganisms() {
    std::sort(allOrganisms.begin(), allOrganisms.end(), [](Organism* a, Organism* b) -> bool {
        return (*b) < (*a);
    });
}

void World::ReportAboutOrganismNewPosition(Organism* movedOrganism) {
    Organism* otherOrganism = FindWhoStandsOnThisPosition(movedOrganism->GetPosition(), movedOrganism);
    if(otherOrganism != nullptr)
        movedOrganism->Collision(otherOrganism);
}

void World::ReportAboutOrganismDeath(Organism* killer, Organism* deadOrganism) {
    std::vector<Organism*>::iterator position = std::find(allOrganisms.begin(), allOrganisms.end(), deadOrganism);
    if (position != allOrganisms.end()) {
        if(deadOrganism->IsAnimal())
            eventsThatHappenedInRound += (deadOrganism->GetName() + " zostal/a zabity/a przez " + killer->GetName() + "\n");
        allOrganisms.erase(position);
    }
    delete deadOrganism;
}

std::string World::GetEventsFromLastRound() {
    std::string events = eventsThatHappenedInRound;
    eventsThatHappenedInRound = "";
    return events;
}