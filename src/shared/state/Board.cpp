#include <fstream>
#include <iostream>

#include "Board.h"
#include "Default.h"
#include "House.h"
#include "Castle.h"
#include "Orientation.h"
#include "Wall.h"

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
        
        return *this;
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
    
    void Board::addUnit(UnitTypeId unit, RaceTypeId race) {

    }

    void Board::deleteUnit(int id) {

    }

    bool Board::isUnitAround(int idAttacker, int idDefender) {
        std::vector<int> listIdUnitArround = findUnitAround(idAttacker);      

        for (int unitId : listIdUnitArround) {
            if (unitId == idDefender) {
                return true;
            }
        }
        
        return false;
    }
    
    Unit* Board::findUnit(int id) const {
        return units.find(id)->second.get();
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
        
        return nullptr;
    }

    std::vector<int> Board::findUnitAround(int id) {
        std::vector<int> listIdUnitArround;
        Unit* unit = findUnit(id);
        Unit* unitAround = nullptr;
        
        unitAround = findUnitOnPosition(unit->getPositionX() - 1, unit->getPositionY() - 1);
        if (unitAround != nullptr) {
            listIdUnitArround.push_back(unitAround->getId());
        }
        unitAround = findUnitOnPosition(unit->getPositionX() - 1, unit->getPositionY());
        if (unitAround != nullptr) {
            listIdUnitArround.push_back(unitAround->getId());
        }     
        unitAround = findUnitOnPosition(unit->getPositionX(), unit->getPositionY() - 1);
        if (unitAround != nullptr) {
            listIdUnitArround.push_back(unitAround->getId());
        }
        unitAround = findUnitOnPosition(unit->getPositionX(), unit->getPositionY() + 1);
        if (unitAround != nullptr) {
            listIdUnitArround.push_back(unitAround->getId());
        }
        unitAround = findUnitOnPosition(unit->getPositionX() + 1, unit->getPositionY() - 1);
        if (unitAround != nullptr) {
            listIdUnitArround.push_back(unitAround->getId());
        }
        unitAround = findUnitOnPosition(unit->getPositionX() + 1, unit->getPositionY());
        if (unitAround != nullptr) {
            listIdUnitArround.push_back(unitAround->getId());
        }
        
        return listIdUnitArround;
    }


    Unit* Board::findUnitOnPosition(int positionX, int positionY) const {
        for (auto& it : units) {
            if (it.second->getPositionX() == positionX) {
                if (it.second->getPositionY() == positionY) {
                    return it.second.get();
                }
            }
        }
        return nullptr;
    }

    int Board::getHeight() const {
        return height;
    }

    int Board::getWidth() const {
        return width;
    }

    const std::map<int, std::unique_ptr<Team> >& Board::getTeams() const {      
        return teams;
    }

    const std::map<int, std::unique_ptr<Terrain> >& Board::getTerrains() const {
        return terrains;
    }

    const std::map<int, std::unique_ptr<Unit> >& Board::getUnits() const {
        return units;
    }

    Board::~Board() {
        teams.clear();
        terrains.clear();
        units.clear();
    }

    void Board::loadTerrainsFromFile(std::string path) {
        std::vector<char> terrainsTmp;
        std::ifstream file;
        file.open(path, std::ios::in);    
        std::string line;
            
        while(!file.eof()){
            std::getline(file, line);
                
            for(auto l : line) {
                terrainsTmp.push_back(l);
            }
        }
        
        file.close();
        
        Terrain* terrainToAdd = nullptr;
        for(int i = 0; i < width * height; i++) {
            switch (terrainsTmp.at(i)) {
                case '0' :  //Grass
                    terrainToAdd = new Default(i, TerrainTypeId::GRASS, 1, i % width, i / width);
                    addTerrain(terrainToAdd);
                    break;
                case '1' :  //Forest
                    terrainToAdd = new Default(i, TerrainTypeId::FOREST, 2, i % width, i / width);
                    addTerrain(terrainToAdd);
                    break;
                case '2' :  //Water
                    terrainToAdd = new Default(i, TerrainTypeId::WATER, 5, i % width, i / width);
                    addTerrain(terrainToAdd);
                    break;
                case '3' :  //House
                    terrainToAdd = new House(i, i % width, i / width);
                    addTerrain(terrainToAdd);
                    break;
                case '4' :  //Castle
                    terrainToAdd = new Castle(i, i % width, i / width);
                    addTerrain(terrainToAdd);
                    break;
                case '5' :  //Wall left
                    terrainToAdd = new Wall(i, Orientation::LEFT, i % width, i / width);
                    addTerrain(terrainToAdd);
                    break;
                case '6' :  //Wall top
                    terrainToAdd = new Wall(i, Orientation::TOP, i % width, i / width);
                    addTerrain(terrainToAdd);
                    break;
                case '7' :  //Wall right
                    terrainToAdd = new Wall(i, Orientation::RIGHT, i % width, i / width);
                    addTerrain(terrainToAdd);
                    break;
                default :
                    std::cerr << "Type de terrain inconnu" << std::endl;
            }
        }
    }


}