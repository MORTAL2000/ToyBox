
#include <lua.hpp>
#include <toy/Version.hpp>
#include <toy/Log.hpp>
#include <toy/Utf.hpp>

static int ToyBoxIsUTF8(lua_State* L)
{
	std::string    str;

	if ( lua_type(L, -1)==LUA_TSTRING )
	{
		str = lua_tostring(L,-1);
	}
	else
	{
		toy::Logger << "warning:toy.logger can't check non-string variable!" << toy::NextLine;
	}

	lua_pop(L,1);

	auto  result = toy::utf::IsUtf8(str);

	lua_pushboolean(L,(int)result);

	return 1;
}

inline static void PrintString(lua_State* L)
{
	if ( lua_type(L, -1)==LUA_TSTRING )
	{
		toy::Logger<<lua_tostring(L,-1);
	//	toy::Logger<<luaL_checkstring(L,-1);
	}
	else
	{
		toy::Logger << "warning:toy.logger can't print non-string variable!" << toy::NextLine;
	}

	lua_pop(L,1);
}

static int ToyBoxLogger(lua_State* L)
{
	PrintString(L);
	return 1;
}

static int ToyBoxLoggerWithNewLine(lua_State* L)
{
	PrintString(L);
	toy::Logger<<toy::NextLine;
	return 1;
}

static int ToyBoxLoggerVersion(lua_State* L)
{
	auto   setValue = [L](const char* key,lua_Integer value)
	{
		lua_pushstring(L, key);      // ... [T] [key]
		lua_pushinteger(L, value);   // ... [T] [key] [value]
		lua_settable(L,-3);          // ... [T]
	};

	                    // ...
	lua_newtable(L);    // ... [T]

	setValue("major",toy::GetMajorVersion());
	setValue("minor",toy::GetMinorVersion());
	setValue("patch",toy::GetPatchVersion());

	                    // ... [T]
	return 1;
}

#if defined(_WIN32)
	#define MY_DLL_API __declspec(dllexport)
#else
	#define MY_DLL_API
#endif

extern "C" MY_DLL_API int luaopen_toy_logger(lua_State* L)
{
	luaL_Reg   reg[5];

	reg[0].name = "printf";
	reg[0].func = ToyBoxLogger;
	reg[1].name = "print";
	reg[1].func = ToyBoxLoggerWithNewLine;
	reg[2].name = "isUTF8";
	reg[2].func = ToyBoxIsUTF8;
	reg[3].name = "version";
	reg[3].func = ToyBoxLoggerVersion;
	reg[4].name = nullptr;
	reg[4].func = nullptr;

	luaL_newlib(L,reg);

	return 1;
}
