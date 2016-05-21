
#pragma once


#include <cstdio>
#include "toy/file/io/Base.hpp"
#include "contrib/minizip/unzip.h"   // It's come from zlib.

namespace toy{
namespace file{
namespace io{


class Zlib : public Base
{
	public:

		Zlib(){}
		virtual ~Zlib(){close();}

		virtual bool    openDir(std::string path);
		virtual bool    open(std::string filepath);
		virtual int     read(void *file,uint32_t size);     // Not finish yet.
		virtual bool    write(void *file,uint32_t size);
		virtual bool    seek(enum Base::Option option,int32_t offset);
		virtual void    close();
		virtual bool    isEnd(){return 1;}     // Implement it later.
		virtual bool    isEmpty();
		virtual void*   getFilePointer();    // prohibit

	private:

		unzFile            _handle = nullptr;
		unz_global_info    _info = {0,0};
		int                _isFileOpened = 0;

};


}//namespace io
}//namespace file
}//namespace toy
