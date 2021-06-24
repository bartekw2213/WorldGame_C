#pragma once
#include "Organism.h"
#include "World.h"

namespace plants {
    static const int PLANT_TYPES_NUM = 5;

    class Plant : public Organism {
        public:
            Plant(World* worldReference, const position& position, const std::string symbol, const int power, 
                const int initiative) : Organism(worldReference, position, symbol, power, initiative) { }
            void Action(int worldWidth, int worldHeight) override;
            void Collision(Organism* otherOrganism) override;
            bool IsAnimal() const override { return false; }
    };

    class Grass : public Plant {
        public:
            Grass(World* worldReference, const position& position) : 
            Plant(worldReference, position, GRASS_SYMBOL, 0, 0) { }
            std::string GetName() const override { return "Trawa"; }
            void Multiply(World* world) override { 
                return world->ReportAboutNewOrganism<Grass>(Organism::GetPosition(), "Trawa", false);
            };
    };

    // Mlecz
    class Sonchus : public Plant {
        public:
            Sonchus(World* worldReference, const position& position) : 
            Plant(worldReference, position, SONCHUS_SYMBOL, 0, 0) { }
            void Action(int worldWidth, int worldHeight) override;
            std::string GetName() const override { return "Mlecz"; }
            void Multiply(World* world) override {
                return world->ReportAboutNewOrganism<Sonchus>(Organism::GetPosition(), "Mlecz", false);
            };
    };

    class Guarana : public Plant {
        public:
            Guarana(World* worldReference, const position& position) : 
            Plant(worldReference, position, GUARANA_SYMBOL, 0, 0) { }
            void Collision(Organism* otherOrganism) override;
            std::string GetName() const override { return "Guarana"; }
            void Multiply(World* world) override {
                return world->ReportAboutNewOrganism<Guarana>(Organism::GetPosition(), "Guarana", false);
            };
    };

    // Wilcza Jagoda
    class Berries : public Plant {
        public:
            Berries(World* worldReference, const position& position) : 
            Plant(worldReference, position, BERRIES_SYMBOL, 99, 0) { }
            void Collision(Organism* otherOrganism) override;
            std::string GetName() const override { return "Wilcza Jagoda"; }
            void Multiply(World* world) override { 
                return world->ReportAboutNewOrganism<Berries>(Organism::GetPosition(), "Wilcza Jagoda", false);
            };
    };

    class SosnowskiBorsch : public Plant {
        public:
            SosnowskiBorsch(World* worldReference, const position& position) : 
            Plant(worldReference, position, SOSNOWSKI_BARSCH_SYMBOL, 10, 0) { }
            void Action(int worldWidth, int worldHeight) override;
            void Collision(Organism* otherOrganism) override;
            std::string GetName() const override { return "Barszcz Sosnowskiego"; }
            void Multiply(World* world) override { };
    };

}
