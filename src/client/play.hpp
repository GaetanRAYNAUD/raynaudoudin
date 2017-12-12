#ifndef PLAY_HPP
#define PLAY_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>

#include "render.h"
#include "engine.h"

namespace play {
    void play_Test();
    void readCommandJson(Json::Value& jsonValue, engine::Engine& engine);
}

#endif /* PLAY_HPP */

