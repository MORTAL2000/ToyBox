
macro(toy_SetThirdPartyLibraryPath)

	if(WIN32)
		set(TOY_SDK_PATH        "D:/sdk" )
	elseif(UNIX)
		set(TOY_SDK_PATH        "~/sdk" )
	endif()


	set(TOY_include_boost       "${TOY_SDK_PATH}/boost" )
	set(TOY_library_boost       "${TOY_ROOT_BINARY_DIR}/third-party/boost" )


	set(TOY_include_sfml        "${TOY_SDK_PATH}/SFML/include" )
	set(TOY_library_sfml        "${TOY_SDK_PATH}/SFML/lib" )
	set(TOY_libname_sfml_main       "sfml-main" )
	set(TOY_libname_sfml_system     "sfml-system" )
	set(TOY_libname_sfml_window     "sfml-window" )
	set(TOY_libname_sfml_graphics   "sfml-graphics" )
	set(TOY_libname_sfml_audio      "sfml-audio" )
	set(TOY_libname_sfml_network    "sfml-network" )


	set(TOY_include_freetype    "${TOY_SDK_PATH}/freetype" )
	set(TOY_library_freetype    "${TOY_SDK_PATH}/freetype" )
	set(TOY_libname_freetype    "freetype" )


	set(TOY_include_lua         "${TOY_ROOT_SOURCE_DIR}/third-party/lua" )
	set(TOY_library_lua         "${TOY_ROOT_BINARY_DIR}/third-party/lua" )
	set(TOY_libname_lua         "lua" )


	set(TOY_include_zlib        "${TOY_ROOT_SOURCE_DIR}/third-party/zlib" "${TOY_ROOT_BINARY_DIR}/third-party/zlib" )
	set(TOY_library_zlib        "${TOY_ROOT_BINARY_DIR}/third-party/zlib" )
	set(TOY_libname_zlib        "zlib" )


	set(TOY_include_libpng      "${TOY_ROOT_SOURCE_DIR}/third-party/libpng" "${TOY_ROOT_BINARY_DIR}/third-party/libpng" )
	set(TOY_library_libpng      "${TOY_ROOT_BINARY_DIR}/third-party/libpng" )
	set(TOY_libname_libpng      "png" )


	if(UNIX)
	set(TOY_include_7zip        "${TOY_ROOT_SOURCE_DIR}/third-party/p7zip" )
	set(TOY_library_7zip        "${TOY_ROOT_BINARY_DIR}/third-party/p7zip" )
	set(TOY_libname_7zip        "p7zip" )
	else()
	set(TOY_include_7zip        "${TOY_ROOT_SOURCE_DIR}/third-party/7zip" )
	set(TOY_library_7zip        "${TOY_ROOT_BINARY_DIR}/third-party/7zip" )
	set(TOY_libname_7zip        "7zip" )
	endif()


	set(TOY_include_glew        "${TOY_ROOT_SOURCE_DIR}/third-party/glew/include" )
	set(TOY_library_glew        "${TOY_ROOT_BINARY_DIR}/third-party/glew" )
	set(TOY_libname_glew        "glew" )


	set(TOY_include_glm         "${TOY_ROOT_SOURCE_DIR}/third-party/glm" )

endmacro(toy_SetThirdPartyLibraryPath)
