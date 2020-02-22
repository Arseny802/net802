//
// Created by arseny on 31/01/2020.
//

#ifndef HTTP_READER_MOEXREADER_H
#define HTTP_READER_MOEXREADER_H

#include <base/IClientHttp.h>
#include <memory>
#include <HttpClient.h>

class MoexReader {
 public:
  MoexReader();
  ~MoexReader();

  bool GetInfo();
 private:
  http::HttpClient _reader;
};

#endif //HTTP_READER_MOEXREADER_H
