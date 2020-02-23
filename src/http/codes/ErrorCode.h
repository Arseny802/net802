//
// Created by arseny on 22/02/2020.
//

#ifndef NETWORK_MODULES_SRC_BASEHTTP_BASE_ERRORCODE_H_
#define NETWORK_MODULES_SRC_BASEHTTP_BASE_ERRORCODE_H_

#include <boost/system/error_code.hpp>

namespace http::codes {
class ErrorCode : boost::system::error_code {

};
}

#endif //NETWORK_MODULES_SRC_BASEHTTP_BASE_ERRORCODE_H_
