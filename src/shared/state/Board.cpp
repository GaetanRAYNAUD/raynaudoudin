#include <fstream>
#include <iostream>

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
    int Board::idTerrain = 0;
    int Board::idUnit = 0;
    
    Board::Board(int width, int height) {
        idTerrain = 0;
        idUnit = 0;
        this->width = width;
        this->height = height;
        Unit* unit = nullptr;
        
        addTeam(new Team(TeamId::TEAM_1, RaceTypeId::HUMAN));
        addTeam(new Team(TeamId::TEAM_2, RaceTypeId::ORC));
        
        unit = new Leader(TeamId::TEAM_1, 3, 4, findTeam(TeamId::TEAM_1)->getRace());
        addUnit(unit);
        
        unit = new Leader(TeamId::TEAM_2, 18, 13, findTeam(TeamId::TEAM_2)->getRace());
        addUnit(unit);
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
    
    void Board::createNewUnit(UnitTypeId unitTypeId, TeamId team, int x, int y) {
        Unit* newUnit;
        
        switch(unitTypeId) {
            case UnitTypeId::BOWMAN:
                newUnit = new Bowman(team, x, y, findTeam(team)->getRace());
                addUnit(newUnit);
                break;
                
            case UnitTypeId::SWORDMAN:
                newUnit = new Swordman(team, x, y, findTeam(team)->getRace());
                addUnit(newUnit);
                break;
                
            default:
                break;
        }
    }

    void Board::deleteUnit(int id) {       
        units.erase(units.find(id));
    }
    
    bool Board::isLeaderNotAlive(TeamId teamId) {
        for(auto& u : units) {
            if (u.second->getTypeId() == UnitTypeId::LEADER  && u.second->getTeam() == teamId) {
                return false;
            }
        }
        
        return true;
    }

    bool Board::isUnitAround(int idAttacker, int idDefender) const {
        std::vector<int> listIdUnitArround = findIdUnitAround(idAttacker);

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

    Team* Board::findTeam(TeamId id) const {
        return teams.find(id)->second.get();
    }

    Terrain* Board::findTerrain(int id) const {
        return terrains.find(id)->second.get();
    }

    Terrain* Board::findTerrainOnPosition(int positionX, int positionY) const {
        if(positionX < 0 || positionY < 0 || positionX > width || positionY > 2 * height) {
            return nullptr;
        } else {
            for (auto& t : terrains) {
                if (t.second->getPositionX() == positionX) {
                    if (t.second->getPositionY() == positionY) {
                        return t.second.get();
                    }
                }
            }
            
            return nullptr;
        }
    }
        
    std::vector<int> Board::findIdTerrainAround(int id) const {
        std::vector<int> listIdTerrainArround;
        Terrain* terrain = findTerrain(id);
        Terrain* terrainAround = nullptr;
        
        terrainAround = findTerrainOnPosition(terrain->getPositionX(), terrain->getPositionY() - 2);
        if (terrainAround != nullptr) {
            listIdTerrainArround.push_back(terrainAround->getId());
        }
        terrainAround = findTerrainOnPosition(terrain->getPositionX() + 1, terrain->getPositionY() - 1);
        if (terrainAround != nullptr) {
            listIdTerrainArround.push_back(terrainAround->getId());
        }     
        terrainAround = findTerrainOnPosition(terrain->getPositionX() + 1, terrain->getPositionY() + 1);
        if (terrainAround != nullptr) {
            listIdTerrainArround.push_back(terrainAround->getId());
        }
        terrainAround = findTerrainOnPosition(terrain->getPositionX(), terrain->getPositionY() + 2);
        if (terrainAround != nullptr) {
            listIdTerrainArround.push_back(terrainAround->getId());
        }
        terrainAround = findTerrainOnPosition(terrain->getPositionX() - 1, terrain->getPositionY() + 1);
        if (terrainAround != nullptr) {
            listIdTerrainArround.push_back(terrainAround->getId());
        }
        terrainAround = findTerrainOnPosition(terrain->getPositionX() - 1, terrain->getPositionY() - 1);
        if (terrainAround != nullptr) {
            listIdTerrainArround.push_back(terrainAround->getId());
        }
        
        return listIdTerrainArround;
    }
    
    std::vector<Terrain*> Board::findTerrainAround(int id) const {
        std::vector<Terrain*> listIdTerrainArround;
        Terrain* terrain = findTerrain(id);
        Terrain* terrainAround = nullptr;
        
        terrainAround = findTerrainOnPosition(terrain->getPositionX(), terrain->getPositionY() - 2);
        if (terrainAround != nullptr) {
            listIdTerrainArround.push_back(terrainAround);
        }
        terrainAround = findTerrainOnPosition(terrain->getPositionX() + 1, terrain->getPositionY() - 1);
        if (terrainAround != nullptr) {
            listIdTerrainArround.push_back(terrainAround);
        }     
        terrainAround = findTerrainOnPosition(terrain->getPositionX() + 1, terrain->getPositionY() + 1);
        if (terrainAround != nullptr) {
            listIdTerrainArround.push_back(terrainAround);
        }
        terrainAround = findTerrainOnPosition(terrain->getPositionX(), terrain->getPositionY() + 2);
        if (terrainAround != nullptr) {
            listIdTerrainArround.push_back(terrainAround);
        }
        terrainAround = findTerrainOnPosition(terrain->getPositionX() - 1, terrain->getPositionY() + 1);
        if (terrainAround != nullptr) {
            listIdTerrainArround.push_back(terrainAround);
        }
        terrainAround = findTerrainOnPosition(terrain->getPositionX() - 1, terrain->getPositionY() - 1);
        if (terrainAround != nullptr) {
            listIdTerrainArround.push_back(terrainAround);
        }
        
        return listIdTerrainArround;
    }

    std::vector<int> Board::findIdUnitAround(int id) const {
        std::vector<int> listIdUnitArround;
        Unit* unit = findUnit(id);
        Unit* unitAround = nullptr;
        
        unitAround = findUnitOnPosition(unit->getPositionX(), unit->getPositionY() - 2);
        if (unitAround != nullptr) {
            listIdUnitArround.push_back(unitAround->getId());
        }
        unitAround = findUnitOnPosition(unit->getPositionX() + 1, unit->getPositionY() - 1);
        if (unitAround != nullptr) {
            listIdUnitArround.push_back(unitAround->getId());
        }     
        unitAround = findUnitOnPosition(unit->getPositionX() + 1, unit->getPositionY() + 1);
        if (unitAround != nullptr) {
            listIdUnitArround.push_back(unitAround->getId());
        }
        unitAround = findUnitOnPosition(unit->getPositionX(), unit->getPositionY() + 2);
        if (unitAround != nullptr) {
            listIdUnitArround.push_back(unitAround->getId());
        }
        unitAround = findUnitOnPosition(unit->getPositionX() - 1, unit->getPositionY() + 1);
        if (unitAround != nullptr) {
            listIdUnitArround.push_back(unitAround->getId());
        }
        unitAround = findUnitOnPosition(unit->getPositionX() - 1, unit->getPositionY() - 1);
        if (unitAround != nullptr) {
            listIdUnitArround.push_back(unitAround->getId());
        }
        
        return listIdUnitArround;
    }


    Unit* Board::findUnitOnPosition(int positionX, int positionY) const {
        if(positionX < 0 || positionY < 0 || positionX > width || positionY > 2 * height) {
            return nullptr;
        } else {
            for (auto& u : units) {
                if (u.second->getPositionX() == positionX) {
                    if (u.second->getPositionY() == positionY) {
                        return u.second.get();
                    }
                }
            }
            
            return nullptr;
        }
    }
        
    void Board::moveUnit(int id, Direction direction) {
        Unit* unit = findUnit(id);
        std::vector<Direction> directionsAvailable = directionAvailable(id);
        
        for (Direction d : directionsAvailable) {
            if (d == direction) {
                switch (direction) {
                    case Direction::TOP:
                        unit->setPositionY(unit->getPositionY() - 2);
                        unit->setSpeed(unit->getSpeed() - findTerrainOnPosition(unit->getPositionX(), unit->getPositionY())->getMovementCost());
                        break;
                    case Direction::TOP_RIGHT:
                        unit->setPositionX(unit->getPositionX() + 1);
                        unit->setPositionY(unit->getPositionY() - 1);
                        unit->setSpeed(unit->getSpeed() - findTerrainOnPosition(unit->getPositionX(), unit->getPositionY())->getMovementCost());
                        break;
                    case Direction::BOT_RIGHT:
                        unit->setPositionX(unit->getPositionX() + 1);
                        unit->setPositionY(unit->getPositionY() + 1);
                        unit->setSpeed(unit->getSpeed() - findTerrainOnPosition(unit->getPositionX(), unit->getPositionY())->getMovementCost());
                        break;
                    case Direction::BOT:
                        unit->setPositionY(unit->getPositionY() + 2);
                        unit->setSpeed(unit->getSpeed() - findTerrainOnPosition(unit->getPositionX(), unit->getPositionY())->getMovementCost());
                        break;
                    case Direction::BOT_LEFT:
                        unit->setPositionX(unit->getPositionX() - 1);
                        unit->setPositionY(unit->getPositionY() + 1);
                        unit->setSpeed(unit->getSpeed() - findTerrainOnPosition(unit->getPositionX(), unit->getPositionY())->getMovementCost());
                        break;
                    case Direction::TOP_LEFT:
                        unit->setPositionX(unit->getPositionX() - 1);
                        unit->setPositionY(unit->getPositionY() - 1);
                        unit->setSpeed(unit->getSpeed() - findTerrainOnPosition(unit->getPositionX(), unit->getPositionY())->getMovementCost());
                        break;
                }
            }
        }
        
        claimHouse(unit->getTeam(), unit->getPositionX(), unit->getPositionY());
    }
        
    std::vector<Direction> Board::directionAvailable(int unitId) const {
        std::vector<Direction> directionAvailable;
        Unit* unit = findUnit(unitId);
        std::vector<Terrain*> terrainsAround = findTerrainAround(
            findTerrainOnPosition(unit->getPositionX(), unit->getPositionY())->getId());

        for (Terrain* t : terrainsAround) {
            if (t->getMovementCost() <= unit->getSpeed()) {
                if(t->getPositionY() == unit->getPositionY() - 2 && findUnitOnPosition(t->getPositionX(), t->getPositionY()) == nullptr) {
                    directionAvailable.push_back(Direction::TOP);
                } else if(t->getPositionX() == unit->getPositionX() + 1 && t->getPositionY() == unit->getPositionY() - 1 && findUnitOnPosition(t->getPositionX(), t->getPositionY()) == nullptr) {
                    directionAvailable.push_back(Direction::TOP_RIGHT);
                } else if(t->getPositionX() == unit->getPositionX() + 1 && t->getPositionY() == unit->getPositionY() + 1 && findUnitOnPosition(t->getPositionX(), t->getPositionY()) == nullptr) {
                    directionAvailable.push_back(Direction::BOT_RIGHT);
                } else if(t->getPositionY() == unit->getPositionY() + 2 && findUnitOnPosition(t->getPositionX(), t->getPositionY()) == nullptr) {
                    directionAvailable.push_back(Direction::BOT);
                } else if(t->getPositionX() == unit->getPositionX() - 1 && t->getPositionY() == unit->getPositionY() + 1 && findUnitOnPosition(t->getPositionX(), t->getPositionY()) == nullptr) {
                    directionAvailable.push_back(Direction::BOT_LEFT);
                } else if(t->getPositionX() == unit->getPositionX() - 1 && t->getPositionY() == unit->getPositionY() - 1 && findUnitOnPosition(t->getPositionX(), t->getPositionY()) == nullptr) {
                    directionAvailable.push_back(Direction::TOP_LEFT);
                }
            }
        }

        return directionAvailable;
    }

    void Board::claimHouse(TeamId teamId, int x, int y) {
        House* tmpHouse;
        
        if(findTerrainOnPosition(x, y)->getTypeId() == TerrainTypeId::HOUSE) {
            tmpHouse = (House*)findTerrainOnPosition(x, y);
            if(tmpHouse->getTeamId() != teamId) {
                if(tmpHouse->getTeamId() != TeamId::INVALIDTEAM) {
                    findTeam(tmpHouse->getTeamId())->removeHouse();
                }
                
                tmpHouse->claim(teamId);
                findTeam(teamId)->addHouse();
            }
        }   
    }
    
    
    void Board::endTurn(TeamId currentTeam) {
        for(auto& u : units) {
            u.second.get()->setSpeed(5);
        }
        
        findTeam(currentTeam)->generateGold();
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
            if((i / (width / 2)) % 2) {
                switch (terrainsTmp.at(i)) {
                    case 'G' :  //Grass
                        terrainToAdd = new Default(TerrainTypeId::GRASS, 1, 2 * (i % (width / 2)), i / (width / 2));
                        addTerrain(terrainToAdd);
                        break;
                    case 'F' :  //Forest
                        terrainToAdd = new Default(TerrainTypeId::FOREST, 2, 2 * (i % (width / 2)), i / (width / 2));
                        addTerrain(terrainToAdd);
                        break;
                    case 'W' :  //Water
                        terrainToAdd = new Default(TerrainTypeId::WATER, 5, 2 * (i % (width / 2)), i / (width / 2));
                        addTerrain(terrainToAdd);
                        break;
                    case 'H' :  //House
                        terrainToAdd = new House(2 * (i % (width / 2)), i / (width / 2));
                        addTerrain(terrainToAdd);
                        break;
                    case 'C' :  //Castle
                        terrainToAdd = new Castle(2 * (i % (width / 2)), i / (width / 2));
                        addTerrain(terrainToAdd);
                        break;
                    case 'L' :  //Wall left
                        terrainToAdd = new Wall(Orientation::LEFT, 2 * (i % (width / 2)), i / (width / 2));
                        addTerrain(terrainToAdd);
                        break;
                    case 'T' :  //Wall top
                        terrainToAdd = new Wall(Orientation::UP, 2 * (i % (width / 2)), i / (width / 2));
                        addTerrain(terrainToAdd);
                        break;
                    case 'R' :  //Wall right
                        terrainToAdd = new Wall(Orientation::RIGHT, 2 * (i % (width / 2)), i / (width / 2));
                        addTerrain(terrainToAdd);
                        break;
                    default :
                        std::cerr << "Le type du terrain en (" << 2 * (i % (width / 2)) << "," << i / (width / 2) << ") n'est pas reconnu" << std::endl;
                }
            } else {
                switch (terrainsTmp.at(i)) {
                    case 'G' :  //Grass
                        terrainToAdd = new Default(TerrainTypeId::GRASS, 1, 2 * (i % (width / 2)) + 1, i / (width / 2));
                        addTerrain(terrainToAdd);
                        break;
                    case 'F' :  //Forest
                        terrainToAdd = new Default(TerrainTypeId::FOREST, 2, 2 * (i % (width / 2)) + 1, i / (width / 2));
                        addTerrain(terrainToAdd);
                        break;
                    case 'W' :  //Water
                        terrainToAdd = new Default(TerrainTypeId::WATER, 5, 2 * (i % (width / 2)) + 1, i / (width / 2));
                        addTerrain(terrainToAdd);
                        break;
                    case 'H' :  //House
                        terrainToAdd = new House(2 * (i % (width / 2)) + 1, i / (width / 2));
                        addTerrain(terrainToAdd);
                        break;
                    case 'C' :  //Castle
                        terrainToAdd = new Castle(2 * (i % (width / 2)) + 1, i / (width / 2));
                        addTerrain(terrainToAdd);
                        break;
                    case 'L' :  //Wall left
                        terrainToAdd = new Wall(Orientation::LEFT, 2 * (i % (width / 2)) + 1, i / (width / 2));
                        addTerrain(terrainToAdd);
                        break;
                    case 'T' :  //Wall top
                        terrainToAdd = new Wall(Orientation::UP, 2 * (i % (width / 2)) + 1, i / (width / 2));
                        addTerrain(terrainToAdd);
                        break;
                    case 'R' :  //Wall right
                        terrainToAdd = new Wall(Orientation::RIGHT, 2 * (i % (width / 2)) + 1, i / (width / 2));
                        addTerrain(terrainToAdd);
                        break;
                    default :
                        std::cerr << "Le type du terrain en (" << 2 * (i % (width / 2)) + 1 << "," << i / (width / 2) << ") n'est pas reconnu" << std::endl;
                }
            }
        }
    }
    

    int Board::getHeight() const {
        return height;
    }

    int Board::getWidth() const {
        return width;
    }

    const std::map<TeamId, std::unique_ptr<Team> >& Board::getTeams() const {      
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

}