
macro(toy_StdReady)
	if(APPLE)
		add_definitions(-O2 -g -Wall -Wextra -Werror -Qunused-arguments -std=c++11)
	elseif(MINGW)
		add_definitions(-O2 -g -Wall -Wextra -Werror -std=c++11)
	elseif(UNIX)
		add_definitions(-O2 -g -Wall -Wextra -Werror -std=c++11)

		include_directories(/usr/include)

		if(CMAKE_SIZEOF_VOID_P EQUAL 8)
			link_directories(/usr/lib/x86_64-linux-gnu)
		else()
			link_directories(/usr/lib)
		endif()
	endif()
endmacro(toy_StdReady)

# For C language
macro(toy_StdReadyC)
	if(APPLE)
		add_definitions(-O2 -g -Wall -Wextra -Werror -Qunused-arguments)
	elseif(MINGW)
		add_definitions(-O2 -g -Wall -Wextra -Werror)
	elseif(UNIX)
		add_definitions(-O2 -g -Wall -Wextra -Werror)

		include_directories(/usr/include)

		if(CMAKE_SIZEOF_VOID_P EQUAL 8)
			link_directories(/usr/lib/x86_64-linux-gnu)
		else()
			link_directories(/usr/lib)
		endif()
	endif()
endmacro(toy_StdReadyC)

macro(toy_ProcessArguments _sourcesArgs _includeDirsArgs _libDirsArgs _linkLibsArgs _outputDirsArgs _linkFlagsArgs _cFlagsArgs _otherArgs)
	set(${_sourcesArgs})
	set(${_includeDirsArgs})
	set(${_libDirsArgs})
	set(${_linkLibsArgs})
	set(${_linkFlagsArgs})
	set(${_cFlagsArgs})
	set(${_otherArgs})
	set(_currentDest ${_otherArgs})
	foreach(_arg ${ARGN})
		if(_arg STREQUAL "SOURCES")
			set(_currentDest ${_sourcesArgs})
		elseif(_arg STREQUAL "INCLUDEDIRS")
			set(_currentDest ${_includeDirsArgs})
		elseif(_arg STREQUAL "LIBDIRS")
			set(_currentDest ${_libDirsArgs})
		elseif(_arg STREQUAL "LINKLIBS")
			set(_currentDest ${_linkLibsArgs})
		elseif(_arg STREQUAL "OUTPUTDIRS")
			set(_currentDest ${_outputDirsArgs})
		elseif(_arg STREQUAL "LINKFLAGS")
			set(_currentDest ${_linkFlagsArgs})
		elseif(_arg STREQUAL "CFLAGS")
			set(_currentDest ${_cFlagsArgs})
		else()
			list(APPEND ${_currentDest} ${_arg})
		endif()
	endforeach()
endmacro(toy_ProcessArguments)

macro(toy_BuildLib _name)

	toy_ProcessArguments(_srcs _includeDirs _libDirs _linkLibs _outputDirs _linkFlags _cFlags _junk ${ARGN})

	if(_junk)
		message(STATUS "WARNING: unkeyworded arguments : ${_junk}")
	endif()

	include_directories(${TOY_DEFAULT_INCLUDE_DIR})

	if(_includeDirs)
		include_directories(${_includeDirs})
	endif()

	if(_outputDirs)
		set(TOY_OUTPUT_PATH ${_outputDirs})
	else()
		set(TOY_OUTPUT_PATH ${TOY_ROOT_BINARY_DIR}/lib)
	endif()
	set(LIBRARY_OUTPUT_PATH ${TOY_OUTPUT_PATH})

	link_directories(${TOY_DEFAULT_LINK_DIR})

	if(_libDirs)
		link_directories(${_libDirs})
	endif()

	add_library(${_name} ${TOY_LIB_TYPE} ${_srcs})

	if(_linkLibs)
		target_link_libraries(${_name} ${_linkLibs})
	endif()

	if(MSVC)
		set_target_properties(${_name} PROPERTIES
			LIBRARY_OUTPUT_DIRECTORY            ${TOY_OUTPUT_PATH}
			LIBRARY_OUTPUT_DIRECTORY_DEBUG      ${TOY_OUTPUT_PATH}
			LIBRARY_OUTPUT_DIRECTORY_RELEASE    ${TOY_OUTPUT_PATH}
			RUNTIME_OUTPUT_DIRECTORY            ${TOY_OUTPUT_PATH}
			RUNTIME_OUTPUT_DIRECTORY_DEBUG      ${TOY_OUTPUT_PATH}
			RUNTIME_OUTPUT_DIRECTORY_RELEASE    ${TOY_OUTPUT_PATH}
			ARCHIVE_OUTPUT_DIRECTORY            ${TOY_OUTPUT_PATH}
			ARCHIVE_OUTPUT_DIRECTORY_DEBUG      ${TOY_OUTPUT_PATH}
			ARCHIVE_OUTPUT_DIRECTORY_RELEASE    ${TOY_OUTPUT_PATH}
		)
	endif()

endmacro(toy_BuildLib)


macro(toy_BuildExe _name)

	toy_ProcessArguments(_srcs _includeDirs _libDirs _linkLibs _outputDirs _linkFlags _cFlags _junk ${ARGN})

	if(_junk)
		message(STATUS "WARNING: unkeyworded arguments : ${_junk}")
	endif()

	include_directories(${TOY_DEFAULT_INCLUDE_DIR})
	link_directories(${TOY_DEFAULT_LINK_DIR})

	if(_includeDirs)
		include_directories(${_includeDirs})
	endif()

	if(_libDirs)
		link_directories(${_libDirs})
	endif()

	if(_outputDirs)
		set(TOY_OUTPUT_PATH ${_outputDirs})
	else()
		set(TOY_OUTPUT_PATH ${TOY_ROOT_BINARY_DIR}/bin)
	endif()
	set(EXECUTABLE_OUTPUT_PATH ${TOY_OUTPUT_PATH})

	add_executable(${_name} ${_srcs})

	if(_linkLibs)
		target_link_libraries(${_name} ${_linkLibs})
	endif()

	if(MSVC)
		set_target_properties(${_name} PROPERTIES
			RUNTIME_OUTPUT_DIRECTORY            ${TOY_OUTPUT_PATH}
			RUNTIME_OUTPUT_DIRECTORY_DEBUG      ${TOY_OUTPUT_PATH}
			RUNTIME_OUTPUT_DIRECTORY_RELEASE    ${TOY_OUTPUT_PATH}
			ARCHIVE_OUTPUT_DIRECTORY            ${TOY_OUTPUT_PATH}
			ARCHIVE_OUTPUT_DIRECTORY_DEBUG      ${TOY_OUTPUT_PATH}
			ARCHIVE_OUTPUT_DIRECTORY_RELEASE    ${TOY_OUTPUT_PATH}
		)
	endif()

endmacro(toy_BuildExe)