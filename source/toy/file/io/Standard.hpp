
#pragma once

#include <cstdio>
#include "toy/file/io/Base.hpp"

namespace toy{
namespace file{
namespace io{


class Standard : public Base
{
	public:

		Standard(){}
		virtual ~Standard(){close();}

		virtual bool    openDir(std::string path);
		virtual bool    open(std::string filepath);
		virtual int     read(void *file,uint32_t size);
		virtual bool    write(void *file,uint32_t size);
		virtual bool    seek(enum Base::Option option,int32_t offset);
		virtual void    close();
		virtual bool    isEnd();
		virtual bool    isEmpty();

	private:

		FILE*        _file = nullptr;
		std::string  _path;
};


}//namespace io
}//namespace file
}//namespace toy
