#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include "../shared/state.h"
#include "render.h"
#include "../shared/engine.h"
#include "state/Board.h"
#include "render/Scene.h"
#include "engine/Engine.h"

namespace engine {
    void engineTest();
    void test_spawnUnit(Engine* engine);
    void test_moveUnit1(Engine* engine);
    void test_moveUnit2(Engine* engine);
    void test_moveUnit3(Engine* engine);
    void test_attackUnit(Engine* engine);
}

#endif /* ENGINE_HPP */

