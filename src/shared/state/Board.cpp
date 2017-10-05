#include "Board.h"

namespace state {
    
    Board::Board(int width, int height) {
        this->width = width;
        this->height = height;
    }
        
    Board::Board(const Board& other) {
        height = other.height;
        width = other.width;
        
        for(auto& t : other.teams) {
            teams.insert(std::make_pair(t.first, std::unique_ptr<Team>(t.second->clone())));
        }
        
        for(auto& t : other.terrains) {
            terrains.insert(std::make_pair(t.first, std::unique_ptr<Terrain>(t.second->clone())));
        }
        
        for(auto& u : other.units) {
            units.insert(std::make_pair(u.first, std::unique_ptr<Unit>(u.second->clone())));
        }
    }
            
    Board& Board::operator=(const Board& other) {
        teams.clear();
        terrains.clear();
        units.clear();
        
        height = other.height;
        width = other.width;
        
        for(auto& t : other.teams) {
            teams.insert(std::make_pair(t.first, std::unique_ptr<Team>(t.second->clone())));
        }
        
        for(auto& t : other.terrains) {
            terrains.insert(std::make_pair(t.first, std::unique_ptr<Terrain>(t.second->clone())));
        }
        
        for(auto& u : other.units) {
            units.insert(std::make_pair(u.first, std::unique_ptr<Unit>(u.second->clone())));
        }
    }

    void Board::addTeam(Team* team) {
        teams.insert(std::make_pair(team->getId(), std::unique_ptr<Team>(team)));
    }

    void Board::addTerrain(Terrain* terrain) {
        terrains.insert(std::make_pair(terrain->getId(), std::unique_ptr<Terrain>(terrain)));
    }

    void Board::addUnit(Unit* unit) {
        units.insert(std::make_pair(unit->getId(), std::unique_ptr<Unit> (unit)));
    }

    Team* Board::findTeam(int id) const {
        return teams.find(id)->second.get();
    }

    Terrain* Board::findTerrain(int id) const {
        return terrains.find(id)->second.get();
    }

    Terrain* Board::findTerrainOnPosition(int positionX, int positionY) const {
        for (auto& it : terrains) {
            if (it.second->getPositionX() == positionX) {
                if (it.second->getPositionY() == positionY) {
                    return it.second.get();
                }
            }
        }
        
        return NULL;
    }

    Unit* Board::findUnit(int id) const {
        return units.find(id)->second.get();
    }

    std::vector<Unit*> Board::findUnitAround(int positionX, int positionY) {

    }

    Unit* Board::findUnitOnPosition(int positionX, int positionY) const {
        for (auto& it : units) {
            if (it.second->getPositionX() == positionX) {
                if (it.second->getPositionY() == positionY) {
                    return it.second.get();
                }
            }
        }
        
        return NULL;
    }

    const int Board::getHeight() const {
        return height;
    }

    const int Board::getWidth() const {
        return width;
    }

    const std::vector<Team*> Board::getTeams() const {
        std::vector<Team*> tmp;
        
        for (auto& it : teams) {
            tmp.push_back(it.second.get());
        }
        
        return tmp;
    }

    const std::vector<Terrain*> Board::getTerrains() const {
        std::vector<Terrain*> tmp;
        
        for (auto& it : terrains) {
            tmp.push_back(it.second.get());
        }
        
        return tmp;
    }

    const std::vector<Unit*> Board::getUnits() const {
        std::vector<Unit*> tmp;
        
        for (auto& it : units) {
            tmp.push_back(it.second.get());
        }
        
        return tmp;
    }

    Board::~Board() {
        teams.clear();
        terrains.clear();
        units.clear();
    }

}