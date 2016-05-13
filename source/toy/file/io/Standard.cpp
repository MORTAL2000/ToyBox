#include "toy/file/io/Standard.hpp"


using namespace toy;
using namespace file;
using namespace io;

bool Standard::isEmpty()
{
	if ( _file==0 )
		return 1;
	else
		return 0;
}

void Standard::close()
{
	if ( _file )
	{
		fclose(_file);
		_file = 0;
		_path.clear();
	}
}

bool Standard::openDir(std::string path)
{
	_path = path;
	return 1;
}

bool Standard::open(std::string filepath)
{
	close();
	_fileName = filepath;
	std::string   path;

	if ( _path.size()==0 )
	{
		path=_fileName;
	}
	else
	{
		path=_path;
		path+=_fileName;
	}

	_file = fopen(path.c_str(),"rb+");
	if ( _file )
		return 1;
	else
		return 0;
}

bool Standard::read(void *file,uint32_t size)
{
	#if TOY_OPTION_CHECK
	if ( ! file )
	{
		toy::Oops(TOY_MARK);
		return 0;
	}
	#endif
	if ( isEmpty() )
		return 0;

	size_t	result=fread(file,1,size,_file);	// "fread(file,size,1,_file)" was wrong.

	if ( result!=size )
	{
		// fread() has wrong
		Oops(TOY_MARK);
		return 0;
	}

	return 1;
}

bool Standard::write(void *file,uint32_t size)
{
	if ( isEmpty() ) return 0;
	fwrite(file,(size_t)size,1,_file);
	return 1;
}

bool Standard::seek(enum Option option,int32_t offset)
{
	if ( isEmpty() ) return 0;

	switch (option)
	{
		case Base::SET:
			fseek( _file, offset, SEEK_SET );
			break;
		case Base::END:
			fseek( _file, offset, SEEK_END );
			break;
		case Base::CUR:
		default:
			fseek( _file, offset, SEEK_CUR );
			break;
	}
	return 1;
}

void* Standard::getFilePointer()
{
	return (void*)_file;
}