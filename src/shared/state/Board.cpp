#include <fstream>
#include <iostream>
//#include <algorithm>

#include "Board.h"
#include "Default.h"
#include "House.h"
#include "Castle.h"
#include "Orientation.h"
#include "Wall.h"
#include "Leader.h"
#include "Swordman.h"
#include "Bowman.h"
#include "Sword.h"

namespace state {
    int Board::idTeam = 0;
    int Board::idTerrain = 0;
    int Board::idUnit = 0;
    
    Board::Board(int width, int height) {
        idTeam = 0;
        idTerrain = 0;
        idUnit = 0;
        this->width = width;
        this->height = height;
        Unit* unit = nullptr;
        Team* team = nullptr;
        
        unit = new Leader(1, 3, 2, RaceTypeId::HUMAN);
        addUnit(unit);
        
        unit = new Leader(2, 18, 6, RaceTypeId::ORC);
        addUnit(unit);
        
        team = new Team();
        addTeam(team);
        
        team = new Team();
        addTeam(team);
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
        team->setId(idTeam);
        teams.insert(std::make_pair(team->getId(), std::unique_ptr<Team>(team)));
        
        idTeam++;
    }

    void Board::addTerrain(Terrain* terrain) {
        terrain->setId(idTerrain);
        if(findTerrainOnPosition(terrain->getPositionX(), terrain->getPositionY()) == nullptr) {
            terrains.insert(std::make_pair(terrain->getId(), std::unique_ptr<Terrain>(terrain)));
        }
        
        idTerrain++;
    }

    void Board::addUnit(Unit* unit) {
        unit->setId(idUnit);
        if(findUnitOnPosition(unit->getPositionX(), unit->getPositionY()) == nullptr) {
            units.insert(std::make_pair(unit->getId(), std::unique_ptr<Unit> (unit)));
        }
        
        idUnit++;
    }
    
    void Board::createNewUnit(UnitTypeId unitTypeId, int team, int x, int y) {
        Unit* newUnit;
        
        switch(unitTypeId) {
            case UnitTypeId::BOWMAN:
                newUnit = new Bowman(team, x, y);
                addUnit(newUnit);
                break;
                
            case UnitTypeId::SWORDMAN:
                newUnit = new Swordman(team, x, y);
                addUnit(newUnit);
                break;
                
            default:
                break;                
        }
    }

    void Board::deleteUnit(int id) {       
        units.erase(units.find(id));
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
    
    bool Board::isUnitOnPosition(int x, int y) const {
        if (findUnitOnPosition(x, y) == nullptr) {   
            return false;
        } else {
            return true;
        }    
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
        if(positionX < 0 || positionY < 0 || positionX > width || positionY > height) {
            return nullptr;
        } else {
            for (auto& it : terrains) {
                if (it.second->getPositionX() == positionX) {
                    if (it.second->getPositionY() == positionY) {
                        return it.second.get();
                    }
                }
            }
            
            return nullptr;
        }
    }
        
    std::vector<int> Board::findTerrainAround(int id) {
        std::vector<int> listIdTerrainArround;
        Terrain* terrain = findTerrain(id);
        Terrain* terrainAround = nullptr;
        
        terrainAround = findTerrainOnPosition(terrain->getPositionX() - 1, terrain->getPositionY() - 1);
        if (terrainAround != nullptr) {
            listIdTerrainArround.push_back(terrainAround->getId());
        }
        terrainAround = findTerrainOnPosition(terrain->getPositionX() - 1, terrain->getPositionY());
        if (terrainAround != nullptr) {
            listIdTerrainArround.push_back(terrainAround->getId());
        }     
        terrainAround = findTerrainOnPosition(terrain->getPositionX(), terrain->getPositionY() - 1);
        if (terrainAround != nullptr) {
            listIdTerrainArround.push_back(terrainAround->getId());
        }
        terrainAround = findTerrainOnPosition(terrain->getPositionX(), terrain->getPositionY() + 1);
        if (terrainAround != nullptr) {
            listIdTerrainArround.push_back(terrainAround->getId());
        }
        terrainAround = findTerrainOnPosition(terrain->getPositionX() + 1, terrain->getPositionY() - 1);
        if (terrainAround != nullptr) {
            listIdTerrainArround.push_back(terrainAround->getId());
        }
        terrainAround = findTerrainOnPosition(terrain->getPositionX() + 1, terrain->getPositionY());
        if (terrainAround != nullptr) {
            listIdTerrainArround.push_back(terrainAround->getId());
        }
        
        return listIdTerrainArround;
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
        if(positionX < 0 || positionY < 0 || positionX > width || positionY > height) {
            return nullptr;
        } else {
            for (auto& it : units) {
                if (it.second->getPositionX() == positionX) {
                    if (it.second->getPositionY() == positionY) {
                        return it.second.get();
                    }
                }
            }
            
            return nullptr;
        }
    }
        
    void Board::moveUnit(int id, Direction direction) {
        
    }
        
    std::vector<Direction> Board::directionAvailable(int unitId) {
        std::vector<Direction> directionAvailable;
        std::vector<int> terrainsAround = findTerrainAround(findTerrainOnPosition(findUnit(unitId)->getPositionX(), findUnit(unitId)->getPositionY()));
        
        if(findUnit(unitId)->getSpeed() > terrainsAround.at(0)) {
            //directionAvailable.push_back();
        }            
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
                    terrainToAdd = new Default(TerrainTypeId::GRASS, 1, i % width, i / width);
                    addTerrain(terrainToAdd);
                    break;
                case '1' :  //Forest
                    terrainToAdd = new Default(TerrainTypeId::FOREST, 2, i % width, i / width);
                    addTerrain(terrainToAdd);
                    break;
                case '2' :  //Water
                    terrainToAdd = new Default(TerrainTypeId::WATER, 5, i % width, i / width);
                    addTerrain(terrainToAdd);
                    break;
                case '3' :  //House
                    terrainToAdd = new House(i % width, i / width);
                    addTerrain(terrainToAdd);
                    break;
                case '4' :  //Castle
                    terrainToAdd = new Castle(i % width, i / width);
                    addTerrain(terrainToAdd);
                    break;
                case '5' :  //Wall left
                    terrainToAdd = new Wall(Orientation::LEFT, i % width, i / width);
                    addTerrain(terrainToAdd);
                    break;
                case '6' :  //Wall top
                    terrainToAdd = new Wall(Orientation::UP, i % width, i / width);
                    addTerrain(terrainToAdd);
                    break;
                case '7' :  //Wall right
                    terrainToAdd = new Wall(Orientation::RIGHT, i % width, i / width);
                    addTerrain(terrainToAdd);
                    break;
                default :
                    std::cerr << "Le type du terrain en (" << i % width << "," << i / width << ") n'est pas reconnu" << std::endl;
            }
        }
    }


}