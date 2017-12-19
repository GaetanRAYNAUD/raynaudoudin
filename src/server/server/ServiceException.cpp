#include "ServiceException.h"

namespace server {
    ServiceException::ServiceException (HttpStatus httpStatus, std::string msg) : msg(msg), httpStatus(httpStatus) {
        
    }

    HttpStatus ServiceException::status() const {
        return httpStatus;
    }

    const char* ServiceException::what() const {
        return msg.c_str();
    }
}