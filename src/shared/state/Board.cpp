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
#include "Direction.h"

#include <fstream>
#include <iostream>

namespace state {
    
    Board::Board(int width, int height) {
        idTerrain = 0;
        idUnit = 0;
        this->width = width;
        this->height = height;
        
        addTeam(new Team(TeamId::TEAM_1, RaceTypeId::HUMAN));
        addTeam(new Team(TeamId::TEAM_2, RaceTypeId::ORC));
        
        addUnit(new Leader(TeamId::TEAM_1, 3, 4, findTeam(TeamId::TEAM_1)->getRace()));
        addUnit(new Leader(TeamId::TEAM_2, width - 4, 2 * height - 3, findTeam(TeamId::TEAM_2)->getRace()));
    }
        
    Board::Board(const Board& other) {
        height = other.height;
        width = other.width;
        idTerrain = other.idTerrain;
        idUnit = other.idUnit;
        
        for(auto& t : other.teams) {
            teams.insert(std::make_pair(t.first, std::unique_ptr<Team>(t.second->clone())));
        }
        
        for(auto& t : other.terrains) {
            terrains.insert(std::make_pair(t.first, std::shared_ptr<Terrain>(t.second->clone())));
        }
        
        for(auto& t : other.terrainsWithPos) {
            terrainsWithPos.insert(std::make_pair(t.first, std::shared_ptr<Terrain>(terrains.at(t.second->getId()))));
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
            terrains.insert(std::make_pair(t.first, std::shared_ptr<Terrain>(t.second->clone())));
        }
        
        for(auto& t : other.terrainsWithPos) {
            terrainsWithPos.insert(std::make_pair(t.first, std::shared_ptr<Terrain>(terrains.at(t.second->getId()))));
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
            terrains.insert(std::make_pair(terrain->getId(), std::shared_ptr<Terrain>(terrain)));
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
    
    void Board::addUnit(std::unique_ptr<Unit> unit, int idUnit) {
        units[idUnit] = std::move(unit);
    }    
    
    void Board::createNewUnit(UnitTypeId unitTypeId, TeamId team, int x, int y) {        
        switch(unitTypeId) {
            case UnitTypeId::BOWMAN:
                addUnit(new Bowman(team, x, y, findTeam(team)->getRace()));
                break;
                
            case UnitTypeId::SWORDMAN:
                addUnit(new Swordman(team, x, y, findTeam(team)->getRace()));
                break;
                
            default:
                break;
        }
    }

    void Board::deleteUnit(int id) {       
        units.erase(units.find(id));
    }
    
    bool Board::isLeaderNotAlive(TeamId teamId) const {
        for(auto& u : units) {
            if (u.second->getTypeId() == UnitTypeId::LEADER  && u.second->getTeam() == teamId) {
                return false;
            }
        }
        
        return true;
    }

    bool Board::isUnitAround(int idAttacker, int idDefender) const {
        std::vector<int> listIdUnitArround = findIdUnitsAround(idAttacker);

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
            auto ite = terrainsWithPos.find(std::make_pair(positionX, positionY));

            if (ite == terrainsWithPos.cend()) {
                return nullptr;
            }

            return ite->second.get();
        }
    }

    Terrain* Board::findTerrainOnPosition(int positionX, int positionY, Direction direction) const {
        switch (direction) {
            case Direction::TOP:
                return findTerrainOnPosition(positionX, positionY - 2);
            case Direction::TOP_RIGHT:
                return findTerrainOnPosition(positionX + 1, positionY - 1);
            case Direction::BOT_RIGHT:
                return findTerrainOnPosition(positionX + 1, positionY + 1);
            case Direction::BOT:
                return findTerrainOnPosition(positionX, positionY + 2);
            case Direction::BOT_LEFT:
                return findTerrainOnPosition(positionX - 1, positionY + 1);
            case Direction::TOP_LEFT:
                return findTerrainOnPosition(positionX - 1, positionY - 1);
            default:
                return nullptr;
        }
        
        return nullptr;
    }
    
    std::vector<Terrain*> Board::findTerrainsAround(int id) const {
        std::vector<Terrain*> listTerrainArround;
        Terrain* terrain = findTerrain(id);
        Terrain* terrainAround = nullptr;
        
        terrainAround = findTerrainOnPosition(terrain->getPositionX(), terrain->getPositionY() - 2);
        if (terrainAround != nullptr) {
            listTerrainArround.push_back(terrainAround);
        }
        
        terrainAround = findTerrainOnPosition(terrain->getPositionX() + 1, terrain->getPositionY() - 1);
        if (terrainAround != nullptr) {
            listTerrainArround.push_back(terrainAround);
        }
        
        terrainAround = findTerrainOnPosition(terrain->getPositionX() + 1, terrain->getPositionY() + 1);
        if (terrainAround != nullptr) {
            listTerrainArround.push_back(terrainAround);
        }
        
        terrainAround = findTerrainOnPosition(terrain->getPositionX(), terrain->getPositionY() + 2);
        if (terrainAround != nullptr) {
            listTerrainArround.push_back(terrainAround);
        }
        
        terrainAround = findTerrainOnPosition(terrain->getPositionX() - 1, terrain->getPositionY() + 1);
        if (terrainAround != nullptr) {
            listTerrainArround.push_back(terrainAround);
        }
        
        terrainAround = findTerrainOnPosition(terrain->getPositionX() - 1, terrain->getPositionY() - 1);
        if (terrainAround != nullptr) {
            listTerrainArround.push_back(terrainAround);
        }

        return listTerrainArround;
    }

    std::vector<int> Board::findIdUnitsAround(int id) const {
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
    
    std::vector<Unit*> Board::findUnitsAround(int id) {
        std::vector<Unit*> listUnitArround;
        Unit* unit = findUnit(id);
        Unit* unitAround = nullptr;
        
        unitAround = findUnitOnPosition(unit->getPositionX(), unit->getPositionY() - 2);
        if (unitAround != nullptr) {
            listUnitArround.push_back(unitAround);
        }
        unitAround = findUnitOnPosition(unit->getPositionX() + 1, unit->getPositionY() - 1);
        if (unitAround != nullptr) {
            listUnitArround.push_back(unitAround);
        }     
        unitAround = findUnitOnPosition(unit->getPositionX() + 1, unit->getPositionY() + 1);
        if (unitAround != nullptr) {
            listUnitArround.push_back(unitAround);
        }
        unitAround = findUnitOnPosition(unit->getPositionX(), unit->getPositionY() + 2);
        if (unitAround != nullptr) {
            listUnitArround.push_back(unitAround);
        }
        unitAround = findUnitOnPosition(unit->getPositionX() - 1, unit->getPositionY() + 1);
        if (unitAround != nullptr) {
            listUnitArround.push_back(unitAround);
        }
        unitAround = findUnitOnPosition(unit->getPositionX() - 1, unit->getPositionY() - 1);
        if (unitAround != nullptr) {
            listUnitArround.push_back(unitAround);
        }

        return listUnitArround;
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

    Direction Board::getDirectionFromTerrains(Terrain* startingTerrain, Terrain* targetTerrain) const {
        if(targetTerrain->getPositionY() == startingTerrain->getPositionY() - 2 && targetTerrain->getPositionX() == startingTerrain->getPositionX()) {
            return Direction::TOP;
            
        } else if(targetTerrain->getPositionX() == startingTerrain->getPositionX() + 1 && targetTerrain->getPositionY() == startingTerrain->getPositionY() - 1) {
            return Direction::TOP_RIGHT;
            
        } else if(targetTerrain->getPositionX() == startingTerrain->getPositionX() + 1 && targetTerrain->getPositionY() == startingTerrain->getPositionY() + 1) {
            return Direction::BOT_RIGHT;
            
        } else if(targetTerrain->getPositionY() == startingTerrain->getPositionY() + 2 && targetTerrain->getPositionX() == startingTerrain->getPositionX()) {
            return Direction::BOT;
            
        } else if(targetTerrain->getPositionX() == startingTerrain->getPositionX() - 1 && targetTerrain->getPositionY() == startingTerrain->getPositionY() + 1) {
            return Direction::BOT_LEFT;
            
        } else if(targetTerrain->getPositionX() == startingTerrain->getPositionX() - 1 && targetTerrain->getPositionY() == startingTerrain->getPositionY() - 1) {
            return Direction::TOP_LEFT;
        }
        
        return Direction::INVALID_DIRECTION;
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
                    default:
                        break;
                }
            }
        }
        
        claimHouse(unit->getTeam(), unit->getPositionX(), unit->getPositionY());
    }
        
    std::vector<Direction> Board::directionAvailable(int unitId) const {
        std::vector<Direction> directionAvailable;
        Unit* unit = findUnit(unitId);
        std::vector<Terrain*> terrainsAround = findTerrainsAround(findTerrainOnPosition(unit->getPositionX(), unit->getPositionY())->getId());

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

        terrainsAround.clear();
        return directionAvailable;
    }
    
    std::vector<Direction> Board::directionAvailable(int x, int y) const {
        std::vector<Direction> directionAvailable;
        Terrain* terrain = findTerrainOnPosition(x, y);
        std::vector<Terrain*> terrainsAround = findTerrainsAround(terrain->getId());

        for (Terrain* t : terrainsAround) {
            directionAvailable.push_back(getDirectionFromTerrains(terrain, t));
        }
        
        terrainsAround.clear();
        return directionAvailable;
    }    

    void Board::claimHouse(TeamId teamId, int x, int y) {
        House* tmpHouse = nullptr;
        
        if(findTerrainOnPosition(x, y)->getTypeId() == TerrainTypeId::HOUSE) {
            tmpHouse = (House*)findTerrainOnPosition(x, y);
            if(tmpHouse->getTeamId() != teamId) {
                if(tmpHouse->getTeamId() != TeamId::INVALID_TEAM) {
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
        int posX, posY;
        
        for(int i = 0; i < width * height; i++) {
            posX = 2 * (i % (width / 2));
            posY = i / (width / 2);
            
            if(!(posY % 2)) {
                posX = posX + 1;
            }
            
            switch (terrainsTmp.at(i)) {
                case 'G' :
                    terrainToAdd = new Default(TerrainTypeId::GRASS, 1, posX, posY);
                    break;

                case 'F' :
                    terrainToAdd = new Default(TerrainTypeId::FOREST, 2, posX, posY);
                    break;

                case 'W' :
                    terrainToAdd = new Default(TerrainTypeId::WATER, 5, posX, posY);
                    break;

                case 'H' :
                    terrainToAdd = new House(posX, posY);
                    break;

                case 'C' :
                    terrainToAdd = new Castle(posX, posY);
                    break;

                case 'L' :
                    terrainToAdd = new Wall(Orientation::LEFT, posX, posY);
                    break;

                case 'T' :
                    terrainToAdd = new Wall(Orientation::UP, posX, posY);
                    break;

                case 'R' :
                    terrainToAdd = new Wall(Orientation::RIGHT, posX, posY);
                    break;

                default :
                    std::cerr << "Le type du terrain en (" << posX << "," << posY << ") n'est pas reconnu" << std::endl;
                    break;
            }
            
            if(terrainToAdd != nullptr) {               
                addTerrain(terrainToAdd);
                terrainsWithPos.insert(std::make_pair(std::make_pair(posX, posY), std::shared_ptr<Terrain>(terrains.at(terrainToAdd->getId()))));
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

    const std::map<int, std::shared_ptr<Terrain> >& Board::getTerrains() const {
        return terrains;
    }

    const std::map<int, std::unique_ptr<Unit> >& Board::getUnits() const {
        return units;
    }
    
    int Board::getIdUnit() const {
        return idUnit;
    }

    void Board::setIdUnit(int idUnit) {
        this->idUnit = idUnit;
    }

    bool Board::equals(const Board& other) const {
        if(height != other.height) {
            return false;
        }
        
        if(width != other.width) {           
            return false;
        }
        
        if(idUnit != other.idUnit) {
            return false;
        }
        
        if(idTerrain != other.idTerrain) {           
            return false;
        }
        
        if(units.size() != other.units.size()) {
            return false;
        }
        
        if(teams.size() != other.teams.size()) {           
            return false;
        }

        if(terrains.size() != other.terrains.size()) {           
            return false;
        }
        
        for(auto& u : units) {
            if(u.second->equals(*other.units.at(u.second->getId())->clone()) == false) {
                return false;
            }
        }

        for(auto& t : terrains) {
            if(t.second->equals(*other.terrains.at(t.second->getId())->clone()) == false) {
                return false;
            }
        }
        
        for(auto& t : terrainsWithPos) {
            if(t.second->equals(*other.terrains.at(t.second->getId())->clone()) == false) {
                return false;
            }
        }        

        if(teams.at(TeamId::TEAM_1)->equals(*other.teams.at(TEAM_1)->clone()) == false) {
            return false;
        }  
        
        if(teams.at(TeamId::TEAM_2)->equals(*other.teams.at(TEAM_2)->clone()) == false) {
            return false;
        }   
        
        return true;
    }
}