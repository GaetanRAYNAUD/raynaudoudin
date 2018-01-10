#include "Scene.h"

namespace render {

    Scene::Scene(const state::State& state) : state(state), terrainLayer(state.getBoard()), unitLayer(state.getBoard()), stateLayer(state), debugLayer(state) {
        terrainLayer.initSurface();
        unitLayer.initSurface();
        stateLayer.initSurface();
    }

    void Scene::draw(sf::RenderWindow& window) {
        window.clear();
        
        if(menu) {
            window.draw(*(menuLayer.getSurface()));
            
        } else {
            window.draw(*(terrainLayer.getSurface()));
            window.draw(*(unitLayer.getSurface()));
            window.draw(*(stateLayer.getSurface()));
            window.draw(*(debugLayer.getSurface()));
        }
    }

    void Scene::stateChanged() {
        if(menu) {
            menuLayer.initSurface();
            
        } else {
            terrainLayer.initSurface();
            unitLayer.initSurface();
            stateLayer.initSurface();
        }
    }
    
    
    DebugLayer& Scene::getDebugLayer() {
        return debugLayer;
    }    

    int Scene::getShiftHeight() const {
        return shiftHeight;
    }

    int Scene::getShiftWidth() const {
        return shiftWidth;
    }

    void Scene::setShiftHeight(int shiftHeight) {
        this->shiftHeight = shiftHeight;
        stateLayer.setShiftHeight(shiftHeight);
        stateLayer.initSurface();
    }

    void Scene::setShiftWidth(int shiftWidth) {
        this->shiftWidth = shiftWidth;
        stateLayer.setShiftWidth(shiftWidth);
        stateLayer.initSurface();
    }

    void Scene::setMenu(bool menu) {
        this->menu = menu;
    }

    bool Scene::getMenu() const {
        return menu;
    }


}