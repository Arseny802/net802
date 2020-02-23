//
// Created by arseny on 04/02/2020.
//

#ifndef HTTP_READER_HTTPSTATUSCODES_H
#define HTTP_READER_HTTPSTATUSCODES_H

namespace http::codes {
enum HttpStatusCodes : int {
  Success = 200,
  Moved = 301
};
}

#endif //HTTP_READER_HTTPSTATUSCODES_H
