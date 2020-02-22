//
// Created by arseny on 31/01/2020.
//

#ifndef HTTP_READER_MOEXREADER_H
#define HTTP_READER_MOEXREADER_H

#include <Base/IClientHttp.h>
#include <memory>
#include <src/BaseHttp/HttpClient.h>

class MoexReader {
 public:
  MoexReader();
  ~MoexReader();

  bool GetInfo();
 private:
  Http::HttpClient _reader;
};

#endif //HTTP_READER_MOEXREADER_H
