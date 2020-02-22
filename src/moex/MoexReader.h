//
// Created by arseny on 31/01/2020.
//

#ifndef HTTP_READER_MOEXREADER_H
#define HTTP_READER_MOEXREADER_H


#include <Base/BaseHttp.h>
#include <memory>

class MoexReader {
public:
	MoexReader(bool tls = false);
	~MoexReader();
	
    bool ReadSome();
    
    void SetTls(bool tls = true);
    bool UsingTls() const;
    
private:
	std::shared_ptr<BaseHttp> _reader;
	bool _tls;
};


#endif //HTTP_READER_MOEXREADER_H
