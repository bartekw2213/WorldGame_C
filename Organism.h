#pragma once
#include "World.h"
#include "GameUtils.h"

class World;

class Organism {
    private:
        World* organismWorld;
        const std::string organismSymbol;
        position organismPosition;
        position organismPrevPosition;
        int power;
        int initiative;
        int roundsOld;
    public:
        Organism(World* world, const position& initalPosition, const std::string symbol, const int power, 
            const int initiative) : 
            organismWorld(world), organismPosition(initalPosition), organismPrevPosition(position(0,0)),
            organismSymbol(symbol), power(power), initiative(initiative), roundsOld(0) { }
        virtual void Action(int worldWidth, int worldHeight) = 0;
        virtual void Collision(Organism* otherOrganism) = 0;
        virtual void Multiply(World* worldReference) = 0;
        virtual bool IsAnimal() const = 0;
        virtual std::string GetName() const = 0;
        void Draw() const;
        void IncrementAge() { roundsOld++; };
        void IncrementPower(int increase) { power += increase; };
        int GetPower() const { return power; };
        position GetPosition() const { return organismPosition; };
        bool IsStandingHere(const position& checkedPosition) const;
        bool operator<(const Organism& otherOrganism) const;
        void ReportAboutOrganismDeath(Organism* killer, Organism* deadOrganism) const;
        void Move(const position newPosition);
        void MoveBack();
    protected:
        World* GetWorldReference() const { return organismWorld; };
        int GetRoundsOld() const { return roundsOld; }
};
