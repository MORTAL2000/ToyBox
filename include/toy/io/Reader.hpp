
#pragma once

/*
 * 1:Use standard library to read file.
 * 0:Support to read file with unicode name on Windows.
 */
#define TOY_OPTION_USE_STD_TEXT_INPUT_STREAM 0

#if TOY_OPTION_USE_STD_TEXT_INPUT_STREAM
	#include <fstream>
	#include <iostream>
	#include <sstream>
	namespace toy{
	namespace io{
		class Stream;
	}}
#else
	#include "toy/io/Stream.hpp"
	#define TOY_TEXT_FILE_READER_BUFFER_SIZE 128
#endif

#include "toy/Standard.hpp"

namespace toy{
namespace io{

template<typename T=toy::io::Stream>
class Reader
{
	public:

		Reader(){}
		Reader(std::string filename)
		{
			if ( ! open(filename) )
			{
				toy::Oops(TOY_MARK);
			}
		}
		~Reader(){}

		inline bool open(std::string filename);
		inline bool nextLine(std::string *str);

	private:

		#if TOY_OPTION_USE_STD_TEXT_INPUT_STREAM
			std::ifstream   _file;
		#else
			T               _file;
			uint32_t        _strHead = TOY_TEXT_FILE_READER_BUFFER_SIZE;
			char            _buffer[TOY_TEXT_FILE_READER_BUFFER_SIZE] = {0};
			bool            _cr = false;
		#endif
};

#if TOY_OPTION_USE_STD_TEXT_INPUT_STREAM

template<typename T>
bool Reader<T>::open(std::string filename)
{
	if ( !boost::filesystem::exists( filename ) )
	{
		// Can't find my file!
		toy::Oops(TOY_MARK);
		return false;
	}

	_file.close();
	_file.open(filename,std::ifstream::in);

	return true;
}

template<typename T>
bool Reader<T>::nextLine(std::string *str)
{
	if ( ! _file.good() )
	{
		toy::Oops(TOY_MARK);
		return false;
	}

	if ( std::getline(_file,*str,'\n') )
	{
		return true;
	}
	else
	{
		return false;  // return false, if no next line.
	}
}

#else

inline bool _IsFileExist(const std::string &filename)
{
	#ifdef TOY_WINDOWS
		return boost::filesystem::exists( toy::utf::UTF8ToWChar(filename) );
	#else
		return boost::filesystem::exists( filename );
	#endif
}

template<typename T>
bool Reader<T>::open(std::string filename)
{
	if ( ! toy::io::_IsFileExist( filename ) )
	{
		// File not found!
		toy::Oops(TOY_MARK);
		return false;
	}

	_file.close();
	return _file.open(filename,"rb+");
}

/*
 * Find out the index of next string.
 * return [index]
 * return TOY_TEXT_FILE_READER_BUFFER_SIZE   :Could not find new line character.
 * return TOY_TEXT_FILE_READER_BUFFER_SIZE-1 :There is no more data need to read in the buffer.
 */
inline uint32_t _GetNewLineIndex(uint32_t head, char *str,bool *cr,const uint32_t BUFFER_SIZE)
{
	for ( uint32_t i=head ; i<BUFFER_SIZE-1 ; i++ )
	{
		if ( str[i]=='\r' )
		{
			str[i] = '\0';

			if ( str[i+1]=='\n' )
			{
				if ( str[i+2]=='\0' )
				{
					return BUFFER_SIZE-1;
				}
				else
				{
					return i+2;
				}
			}
			else if ( str[i+1]=='\0' )
			{
				*cr = true;
				return BUFFER_SIZE-1;
			}
			else
			{
				return i+1;
			}
		}
		else if ( str[i]=='\n' )
		{
			str[i] = '\0';

			if ( str[i+1]=='\0' )
			{
				return BUFFER_SIZE-1;
			}
			else
			{
				return i+1;
			}
		}
		else if ( str[i]=='\0' )
		{
			return BUFFER_SIZE-1;
		}
	}

	return BUFFER_SIZE;
}

static bool _OutputStringLine(toy::io::Stream *file,uint32_t *head,char *buffer,std::string *str,bool *cr,const uint32_t BUFFER_SIZE)
{
	uint32_t  locat = BUFFER_SIZE;

	if ( *head==BUFFER_SIZE )
	{
		locat = file->read(buffer,BUFFER_SIZE-1);
		buffer[locat] = '\0';   // It's mean no more data after here.
		*head = 0;

		if ( *cr==true )
		{
			*cr = false;
			if ( buffer[0]=='\n' )
			{
				*head = 1;
			}
		}
	}

	auto   index = toy::io::_GetNewLineIndex(*head,buffer,cr,BUFFER_SIZE);

	if ( index==BUFFER_SIZE )
	{
		*str += buffer + *head;
		*head = BUFFER_SIZE;
	}
	else if ( index==BUFFER_SIZE-1 )
	{
		*str += buffer + *head;
		*head = BUFFER_SIZE;
		return false;
	}
	else if ( index==*head )
	{
		return false;
	}
	else
	{
		*str += buffer + *head;
		*head = index;
		return false;
	}

	if ( file->isEnd() )
	{
		toy::Oops(TOY_MARK);
		return false;
	}

	return true;
}

template<typename T>
bool Reader<T>::nextLine(std::string *str)
{
	if ( ! _file.good() )
	{
		toy::Oops(TOY_MARK);
		return false;
	}

	if ( _file.isEnd() )
	{
		if ( _strHead==TOY_TEXT_FILE_READER_BUFFER_SIZE )
		{
			// No more data could output.
			return false;
		}
	}

	str->clear();

	while ( toy::io::_OutputStringLine(&_file,&_strHead,_buffer,str,&_cr,TOY_TEXT_FILE_READER_BUFFER_SIZE) )
	{}

	return true;
}

#endif

}//namespace io
}//namespace toy

#if ! TOY_OPTION_USE_STD_TEXT_INPUT_STREAM
	#undef TOY_TEXT_FILE_READER_BUFFER_SIZE
#endif

#undef TOY_OPTION_USE_STD_TEXT_INPUT_STREAM
