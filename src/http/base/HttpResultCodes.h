//
// Created by arseny on 04/02/2020.
//

#ifndef HTTP_READER_HTTPRESULTCODES_H
#define HTTP_READER_HTTPRESULTCODES_H

namespace http::base {
enum HttpResultCodes : int {
  Ok = 0,
  InvalidRequest_host = 1,
  InvalidResponse = 2,
  ProcessingError = 3,
  ProcessingException = 4,
  ResponseError = 5,
  MovedWithNoLocation = 6
};
}

#endif //HTTP_READER_HTTPRESULTCODES_H
