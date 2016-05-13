
#pragma once


#include "toy/Exception.hpp"
#include "toy/CompilerConfig.hpp"


namespace toy{

void TOY_API Log(const char *fmt, ... );
void TOY_API Log(const wchar_t *fmt, ... );
void TOY_API Log(Exception);

#if TOY_OPTION_CHECK
	inline void Oops(const char *file,int line){ toy::Log("%s:%d\n",file,line); }
#else
	inline void Oops(const char*,int){}
#endif


}//namespace toy