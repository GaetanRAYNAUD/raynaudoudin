#ifndef NETWORK_HPP
#define NETWORK_HPP

#include <iostream>
#include <unistd.h>
#include <microhttpd.h>

#include "server.h"

namespace server {
    void network_Test(int port, std::string name);    
}

#endif /* NETWORK_HPP */

