#include "Animals.h"
using namespace animals;

void Animal::Action(int worldWidth, int worldHeight) {
    int newX, newY;
    do {
        newX = Organism::GetPosition().x + (rand() % 3 - 1);
        newY = Organism::GetPosition().y + (rand() % 3 - 1);
    } while(newX < 0 || newX >= worldWidth || newY < 0 || newY >= worldHeight);
    Organism::Move(position(newX, newY));
}

void Animal::Collision(Organism* otherOrganism) {
    // jesli zwierzeta sa tego samego rodzaju - rozmnoz je
    if(this->GetName() == otherOrganism->GetName()) {
        this->MoveBack();
        if(Organism::GetRoundsOld() > MIN_ANIMAL_AGE_TO_MULTIPLY)
            this->Multiply(Organism::GetWorldReference());
    } 
    // jesli inny organizm jest roslina, zolwiem lub antylopa - niech to on obsluzy kolizje
    else if(!otherOrganism->IsAnimal() || dynamic_cast<Turtle*>(otherOrganism) != nullptr ||
        dynamic_cast<Antelope*>(otherOrganism) != nullptr) {
        otherOrganism->Collision(this);
    } 
    // stocz pojedynek i zdecyduj kto wygral
    else {
        if(Organism::GetPower() >= otherOrganism->GetPower())
            Organism::ReportAboutOrganismDeath(this, otherOrganism);
        else
            Organism::ReportAboutOrganismDeath(otherOrganism, this);
    }
}

void Fox::Action(int worldWidth, int worldHeight) {
    int newX, newY;
    bool isStrongerEnemyStandingHere;

    do {
        isStrongerEnemyStandingHere = false;
        newX = Organism::GetPosition().x + (rand() % 3 - 1);
        newY = Organism::GetPosition().y + (rand() % 3 - 1);

        Organism* potentialEnemy = Organism::GetWorldReference()->FindWhoStandsOnThisPosition(position(newX, newY));
        if(potentialEnemy != nullptr && potentialEnemy->GetPower() > Organism::GetPower())
            isStrongerEnemyStandingHere = true;
    } while(newX < 0 || newX >= worldWidth || newY < 0 || newY >= worldHeight || isStrongerEnemyStandingHere);
    Organism::Move(position(newX, newY));
}

void Turtle::Action(int worldWidth, int worldHeight) {
    int num = rand() % 4;
    if(num == 0)
        Animal::Action(worldWidth, worldHeight);
}

void Turtle::Collision(Organism* otherOrganism) {
    if(otherOrganism->GetPower() < 5)
        otherOrganism->MoveBack();
    else
        Animal::Collision(otherOrganism);
}

void Antelope::Action(int worldWidth, int worldHeight) {
    int newX, newY;
    do {
        newX = Organism::GetPosition().x + ((rand() % 3 - 1)*2);
        newY = Organism::GetPosition().y + ((rand() % 3 - 1)*2);
    } while(newX < 0 || newX >= worldWidth || newY < 0 || newY >= worldHeight);
    Organism::Move(position(newX, newY));
}

void Antelope::Collision(Organism* otherOrganism) {
    int num = rand() % 2;
    World* world = Organism::GetWorldReference();
    if(num == 0)
        Antelope::Action(world->GetWorldWidth(), world->GetWorldHeight());
    else 
        Animal::Collision(otherOrganism);
}

void Human::Action(int worldWidth, int worldHeight) {
    int newX = Organism::GetPosition().x, newY = Organism::GetPosition().y;
    int userMove = Organism::GetWorldReference()->GetUserLastMove();
    roundsSinceSuperPowerActivation++;

    switch(userMove) {
        case KEY_UP: newY -= 1; break;
        case KEY_DOWN: newY += 1; break;
        case KEY_LEFT: newX -= 1; break;
        case KEY_RIGHT: newX += 1; break;
        case KEY_SUPER_POWER:
            if(roundsSinceSuperPowerActivation > 10)
                roundsSinceSuperPowerActivation = 0;
            break;
    }

    if(newX >= 0 && newX < worldWidth && newY >= 0 && newY < worldHeight)
        Organism::Move(position(newX, newY));

    if(roundsSinceSuperPowerActivation <= 5)
        UseSuperPower();
}

void Human::UseSuperPower() {
    position humanPosition = Organism::GetPosition();
    World* world = Organism::GetWorldReference();

    int positionsAroundHuman[FIELDS_AROUND_ORGANISM][2] = {
        {-1,1},{0,1},{1,1},{1,0},{1,-1},{0,-1},{-1,-1},{-1,0}
        };
    
    for(int i = 0; i < FIELDS_AROUND_ORGANISM; i++) {
        position checkedPosition = position(
            humanPosition.x + positionsAroundHuman[i][0], humanPosition.y + positionsAroundHuman[i][1]);
        Organism* potentialEnemy = world->FindWhoStandsOnThisPosition(checkedPosition);
        if(potentialEnemy != nullptr)
            world->ReportAboutOrganismDeath(this, potentialEnemy);
    }
}