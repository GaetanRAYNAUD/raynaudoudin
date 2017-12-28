#include "NetworkClient.h"

namespace client {

    NetworkClient::NetworkClient(const std::string& url, int port, state::TeamId player) : url(url), port(port), player(player) {

    }

    std::string NetworkClient::getGameStatus() {

    }

    bool NetworkClient::getServerCommands(Json::Value& out) {

    }

    void NetworkClient::putServerCommand(engine::Command* command) {

    }

    void NetworkClient::run() {

    }

}