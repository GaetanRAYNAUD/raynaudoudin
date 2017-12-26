#include "ServicesManager.h"
#include "ServiceException.h"

#include <algorithm>
#include <iostream>

namespace server {
    void ServicesManager::registerService(std::unique_ptr<AbstractService> service) {   
        services.push_back(std::move(service));
    }

    AbstractService* ServicesManager::findService(const std::string& url) const {
        std::string req;
        
        if(std::count(url.begin(), url.end(), '/') == 1) {
            req = url.substr(1);
        } else {
            req = url.substr(1, url.find("/", 2) - 1);
        }

        if(req == "version") {
            for(auto& s : services) {
                if(s->getPattern() == "/version") {              
                    return s.get();
                }
            }

            return nullptr;

        } else if(req == "player") {
            for(auto& s : services) {
                if(s->getPattern() == "/player") {
                    return s.get();
                }
            }

            return nullptr;
            
        } else if(req == "game") {
            for(auto& s : services) {
                if(s->getPattern() == "/game") {
                    return s.get();
                }
            }

            return nullptr;        
            
        } else if(req == "command") {
            for(auto& s : services) {
                if(s->getPattern() == "/command") {
                    return s.get();
                }
            }

            return nullptr;
            
        } else {
            throw ServiceException(HttpStatus::BAD_REQUEST,"Page inexistante");
            return nullptr;
        }
    }

    HttpStatus ServicesManager::queryService(std::string& out, const std::string& in, const std::string& url, const std::string& method) {
        int id;
        HttpStatus status = HttpStatus::SERVER_ERROR;

        if(url.find("/", 1) == std::string::npos) {
            id = 0;
        } else {            
            id = stoi(url.substr(url.find_first_of("/", 1) + 1, url.npos));
        }

        if(method == "GET") {
            Json::Value jsonOut;

            status = findService(url)->get(jsonOut, id);
            out = jsonOut.toStyledString();

            return status;

        } else if(method == "POST") {
            Json::Reader jsonReader;
            Json::Value jsonValue;

            if (!(jsonReader.parse(in, jsonValue, false))) {
                std::cout << jsonReader.getFormattedErrorMessages() << std::endl;
            }

            status = findService(url)->post(jsonValue, id);

            return status;

        } else if(method == "PUT") {
            Json::Reader jsonReader;
            Json::Value jsonIn;
            Json::Value jsonOut;

            if (!(jsonReader.parse(in, jsonIn, false))) {
                std::cout << jsonReader.getFormattedErrorMessages() << std::endl;
            }

            status = findService(url)->put(jsonOut, jsonIn);
            if(status == HttpStatus::CREATED) {
                out = jsonOut.toStyledString();
            }

            return status;

        } else if(method == "DELETE") {
            status = findService(url)->remove(id);

            return status;

        } else {
            throw ServiceException(HttpStatus::BAD_REQUEST,"Bad request");

            return HttpStatus::BAD_REQUEST;
        }

    }
}

