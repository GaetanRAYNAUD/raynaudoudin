#include "VersionService.h"

namespace server {
    VersionService::VersionService () : AbstractService("/version") {

    }

    HttpStatus VersionService::get (Json::Value& jsonOut, int id) const {
        jsonOut["major"] = 1;
        jsonOut["minor"] = 0;

        return HttpStatus::OK;
    }
}