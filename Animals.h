#pragma once
#include "World.h"
#include "Organism.h"

namespace animals {
    static const int ANIMAL_TYPES_NUM = 5;

    class Animal : public Organism {
        public:
            Animal(World* worldReference, const position& position, const std::string symbol, const int power, 
                const int initiative) : Organism(worldReference, position, symbol, power, initiative) { }
            void Action(int worldWidth, int worldHeight) override;
            void Collision(Organism* otherOrganism) override;
            bool IsAnimal() const override { return true; }
    };

    class Wolf : public Animal {
        public:
            Wolf(World* worldReference, const position& position) : 
            Animal(worldReference, position, WOLF_SYMBOL, 9, 5) { }
            std::string GetName() const override { return "Wilk"; }
            void Multiply(World* world) override {
                return world->ReportAboutNewOrganism<Wolf>(Organism::GetPosition(), "Wilk", true);
            };
    };

    class Sheep : public Animal {
        public:
            Sheep(World* worldReference, const position& position) : 
            Animal(worldReference, position, SHEEP_SYMBOL, 4, 4) { }
            std::string GetName() const override { return "Owca"; }
            void Multiply(World* world) override {
                return world->ReportAboutNewOrganism<Sheep>(Organism::GetPosition(), "Owca", true);
            };
    };

    class Fox : public Animal {
        public:
            Fox(World* worldReference, const position& position) : 
            Animal(worldReference, position, FOX_SYMBOL, 3, 7) { }
            void Action(int worldWidth, int worldHeight) override;
            std::string GetName() const override { return "Lis"; }
            void Multiply(World* world) override {
                return world->ReportAboutNewOrganism<Fox>(Organism::GetPosition(), "Lis", true);
            };
    };

    class Turtle : public Animal {
        public:
            Turtle(World* worldReference, const position& position) : 
            Animal(worldReference, position, TURTLE_SYMBOL, 2, 1) { }
            void Action(int worldWidth, int worldHeight) override;
            void Collision(Organism* otherOrganism) override;
            std::string GetName() const override { return "Zolw"; }
            void Multiply(World* world) override {
                return world->ReportAboutNewOrganism<Turtle>(Organism::GetPosition(), "Zolw", true);
            };
    };

    class Antelope : public Animal {
        public:
            Antelope(World* worldReference, const position& position) : 
            Animal(worldReference, position, ANTELOPE_SYMBOL, 4, 4) { }
            void Action(int worldWidth, int worldHeight) override;
            void Collision(Organism* otherOrganism) override;
            std::string GetName() const override { return "Antelopa"; }
            void Multiply(World* world) override {
                return world->ReportAboutNewOrganism<Antelope>(Organism::GetPosition(), "Antelopa", true);
            };
    };

    class Human : public Animal {
        private:
            int roundsSinceSuperPowerActivation;
        public:
            Human(World* worldReference, const position& position) : 
            Animal(worldReference, position, HUMAN_SYMBOL, 5, 4), roundsSinceSuperPowerActivation(1000) { }
            void Action(int worldWidth, int worldHeight) override;
            std::string GetName() const override { return "Czlowiek"; }
            void Multiply(World* world) override { };
        private:
            void UseSuperPower();
    };
}
