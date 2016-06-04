
macro(toy_CheckEnvironment)

	if(NOT (MINGW OR MSVC OR UNIX OR TOY_ANDROID))
		message(SEND_ERROR "ToyBox:Sorry, this compiler haven't been tested.")
	endif()

endmacro(toy_CheckEnvironment)
