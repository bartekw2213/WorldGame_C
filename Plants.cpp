#include <iostream>
#include "Plants.h"
using namespace plants;

void Plant::Action(int worldWidth, int worldHeight) {
    int number = (rand() % 100) + 1;
    if(number <= PERCENTAGE_CHANCE_PLANT_WILL_SPREAD && Organism::GetRoundsOld() > MIN_PLANT_AGE_TO_MULTIPLY)
        this->Multiply(Organism::GetWorldReference());
}

void Plant::Collision(Organism* otherOrganism) {
    if(Organism::GetPower() > otherOrganism->GetPower())
        Organism::ReportAboutOrganismDeath(this, otherOrganism);
    else
        Organism::ReportAboutOrganismDeath(otherOrganism, this);
}

void Sonchus::Action(int worldWidth, int worldHeight) {
    for(int i = 0; i < 3; i++)
        Plant::Action(worldWidth, worldHeight);
}

void Guarana::Collision(Organism* otherOrganism) {
    Organism::ReportAboutOrganismDeath(otherOrganism, this);
    otherOrganism->IncrementPower(3);
}

void Berries::Collision(Organism* otherOrganism) {
    Organism::ReportAboutOrganismDeath(this, otherOrganism);
}

void SosnowskiBorsch::Action(int worldWidth, int worldHeight) {
    position borschPosition = Organism::GetPosition();
    World* world = Organism::GetWorldReference();

    int positionsAroundBorsch[FIELDS_AROUND_ORGANISM][2] = {
        {-1,1},{0,1},{1,1},{1,0},{1,-1},{0,-1},{-1,-1},{-1,0}
        };
    
    for(int i = 0; i < FIELDS_AROUND_ORGANISM; i++) {
        position checkedPosition = position(
            borschPosition.x + positionsAroundBorsch[i][0], borschPosition.y + positionsAroundBorsch[i][1]);
        Organism* potentialEnemy = world->FindWhoStandsOnThisPosition(checkedPosition);
        if(potentialEnemy != nullptr && potentialEnemy->IsAnimal())
            world->ReportAboutOrganismDeath(this, potentialEnemy);
    }
}

void SosnowskiBorsch::Collision(Organism* otherOrganism) {
    Organism::ReportAboutOrganismDeath(this, otherOrganism);
}