#include "Scene.h"

namespace render {

    Scene::Scene(const state::State& state) : state(state), terrainLayer(state.getBoard()), unitLayer(state.getBoard()), stateLayer(state) {
        terrainLayer.initSurface();
        unitLayer.initSurface();       
        stateLayer.initSurface();
    }

    void Scene::draw(sf::RenderWindow& window) {
        window.clear();
        window.draw(*(terrainLayer.getSurface()));       
        window.draw(*(unitLayer.getSurface()));
        window.draw(*(stateLayer.getSurface()));
    }

    int Scene::getHeigh() const {
        return heigh;
    }

    int Scene::getWidth() const {
        return width;
    }

    void Scene::stateChanged(const state::Event& event) {

    }

}