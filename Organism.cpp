#include "Organism.h"
#include <iostream>

bool Organism::IsStandingHere(const position& checkedPosition) const {
    return organismPosition == checkedPosition;
}

void Organism::Draw() const {
    std::cout << organismSymbol;
}

bool Organism::operator<(const Organism& otherOrganism) const {
    bool result = this->initiative < otherOrganism.initiative; 
    if(this->initiative == otherOrganism.initiative)
        result = this->roundsOld < otherOrganism.roundsOld;
    return result;
}

void Organism::Move(const position newPosition) {
    organismPrevPosition = organismPosition;
    organismPosition = newPosition;
    organismWorld->ReportAboutOrganismNewPosition(this);
}

void Organism::MoveBack() {
    Organism::Move(organismPrevPosition);
}

void Organism::ReportAboutOrganismDeath(Organism* killer, Organism* deadOrganism) const {
    organismWorld->ReportAboutOrganismDeath(killer, deadOrganism);
}