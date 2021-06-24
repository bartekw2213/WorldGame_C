#pragma once
#include <vector>
#include "Organism.h"
#include "GameUtils.h"

class Organism;

class World {
    private:
        std::vector<Organism*> allOrganisms;
        std::string eventsThatHappenedInRound;
        int worldWidth;
        int wordlHeight;
        int userLastMove;
    public:
        World();
        ~World();
        void PrintWorld() const;
        void InitDimensions(const int width, const int height);
        void InitOrganisms(const int organismsNum);
        void MakeMove(const int userMove);
        void ReportAboutOrganismNewPosition(Organism* movedOrganism);
        void ReportAboutOrganismDeath(Organism* killer, Organism* deadOrganism);
        template <class T> void ReportAboutNewOrganism(position parentPosition, std::string name, bool isAnimal);
        int GetUserLastMove() const { return userLastMove; }
        int GetWorldWidth() const { return worldWidth; }
        int GetWorldHeight() const { return wordlHeight; }
        std::string GetEventsFromLastRound();
        Organism* FindWhoStandsOnThisPosition(const position& checkedPosition, 
            Organism* organismToIgnore = nullptr) const;
    private:
        void CreateAnimals(const int animalsNum);
        void CreatePlants(const int plantsNum);
        void CreateHuman();
        template<class T> void CreateOrganism();
        void SortOrganisms();
};

template<class T> void World::ReportAboutNewOrganism(position parentPosition, std::string name, bool isAnimal) {
    int positionsAroundParent[FIELDS_AROUND_ORGANISM][2] = {
        {-1,1},{0,1},{1,1},{1,0},{1,-1},{0,-1},{-1,-1},{-1,0}
        };

    for(int i = 0; i < FIELDS_AROUND_ORGANISM; i++) {
        int checkedX = parentPosition.x + positionsAroundParent[i][0];
        int checkedY = parentPosition.y + positionsAroundParent[i][1];

        if(checkedX >= 0 && checkedX < worldWidth && checkedY >= 0 && checkedY < wordlHeight &&
        FindWhoStandsOnThisPosition(position(checkedX, checkedY)) == nullptr) {
            allOrganisms.push_back(new T(this, position(checkedX, checkedY)));
            if(isAnimal)
                eventsThatHappenedInRound += ("Urodzil/a się nowy/a " + name + "\n");
            break;
        }
    }
}