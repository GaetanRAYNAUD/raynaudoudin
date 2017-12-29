#ifndef NETWORK_HPP
#define NETWORK_HPP

#include <iostream>
#include <unistd.h>
#include <SFML/Network/Http.hpp>

#include "json/json.h"
#include "client/NetworkClient.h"

namespace network {
    void network_Test(int port, std::string name);   
    void network_Test2(int port, std::string name);   
}

#endif /* NETWORK_HPP */

