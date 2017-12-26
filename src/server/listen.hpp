#ifndef LISTEN_HPP
#define LISTEN_HPP

#include <iostream>
#include <microhttpd.h>
#include <string.h>

#include "server.h"
#include "engine/Engine.h"

namespace listenn {
    class Request {
        public:
            struct MHD_PostProcessor *pp = nullptr;
            std::string data;
            ~Request() {
                if (pp) MHD_destroy_post_processor (pp);
            }
    };
    
    void listen_Test(int port);
}

#endif /* LISTEN_HPP */

