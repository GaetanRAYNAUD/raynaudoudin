#include "Board.h"

namespace state {
    
    Board::Board(int width, int height) {
        this->width = width;
        this->height = height;
    }
        
    Board::Board(const Board& board) {

    }
            
    Board& Board::operator=(const Board& board) {

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
       std::map<int, std::unique_ptr<Terrain>>::iterator it;
        
        for (auto const& it : terrains) {
            if (it.second->getPositionX() == positionX) {
                if (it.second->getPositionY() == positionY) {
                    return it.second.get();
                }
            }
        }
    }

    Unit* Board::findUnit(int id) const {
        return units.find(id)->second.get();
    }

    std::vector<Unit*> Board::findUnitAround(int positionX, int positionY) {

    }

    Unit* Board::findUnitOnPosition(int positionX, int positionY) const {

    }

    int Board::getHeight() const {
        return height;
    }

    int Board::getWidth() const {
        return width;
    }

    Board::~Board() {
        //Erase all maps
    }

}