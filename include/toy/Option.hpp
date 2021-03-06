
#pragma once

namespace toy{

enum Option:int
{
	_OPTION_START_OR_BEGIN = 0,
	NOTHING,
	DEFAULT,
	WHATEVER,   // Let system decide.
	SPECIAL,
	VERTEX_SHADER,
	FRAGMENT_SHADER,
	FORWARD,
	BACKWARD,
	RIGHTWARD,
	LEFTWARD,
	TOPWARD,
	DOWNWARD,
	VERTICAL,
	HORIZONTAL,
	GL_1_1,
	GL_1_2,
	GL_1_3,
	GL_1_4,
	GL_1_5,
	GL_2_0,    // toy::graph::Brush supported.
	GL_2_1,
	GL_3_0,    // toy::graph::Brush supported.
	GL_3_1,
	GL_3_2,
	GL_3_3,
	GL_4_0,
	GL_4_1,
	GL_4_2,
	GL_4_3,
	GL_4_4,
	GL_4_5,
	GREY,        // 1 byte
	GREY_ALPHA,  // 2 byte
	RGB,         // 3 byte
	BGR,         // 3 byte
	RGBA,        // 4 byte
	DIRECTORY,
	ZIP,          // zip
	SEVEN_ZIP,    // 7zip
	READ_ONLY,
	_OPTION_END,
};

}
