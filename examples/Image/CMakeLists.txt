project(Image)

toy_StdReady()

add_definitions(-DTOY_RESOURCE_PATH="${TOY_RESOURCE_PATH}")

set(LIBS
	toy
	toy_file
	toy_photo
	toy_canvas
	${TOY_libname_sfml_system}
	${TOY_libname_sfml_window}
)

include_directories(${TOY_ROOT_SOURCE_DIR}/examples/common)

if(TOY_USE_GLEW)
	if(NOT TOY_ENABLE_SHARED_LIBS)
		add_definitions(-DGLEW_STATIC)
	endif()

	include_directories(${TOY_include_glew})
	link_directories(${TOY_library_glew})
	list(APPEND LIBS ${TOY_libname_glew})
endif()

if(APPLE)
	find_library(TOY_FW_OpenGL OpenGL)
	list(APPEND LIBS ${TOY_FW_OpenGL})
elseif(UNIX)
	list(APPEND LIBS GL GLU X11)
elseif(WIN32)
	list(APPEND LIBS opengl32 glu32 gdi32)
endif()

set(SOURCE
	main.cpp
)

toy_BuildExe(ImageTag
	SOURCES     ${SOURCE}
	LINKLIBS    ${LIBS}
)

set_target_properties(ImageTag PROPERTIES OUTPUT_NAME Image)
