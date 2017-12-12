#ifndef THREAD_HPP
#define THREAD_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include "../shared/state.h"
#include "state/Board.h"
#include "render/Scene.h"
#include "render.h"
#include "../shared/engine.h"
#include "engine/Engine.h"
#include "../shared/ai.h"
#include "../client/client.h"

namespace thread {
    void thread_aiTest();
}

#endif /* THREAD_HPP */
