#include <cstdlib>
#include <cstring>
#include "toy/Image.hpp"
#include "toy/file/File.hpp"
#include "toy/file/loader/Image.hpp"

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "toy/file/loader/stb/stb_image.h"
#include "toy/file/loader/stb/stb_image_write.h"


namespace toy{
namespace file{


static int ReadImage(void *user,char *data,int size)
{
	auto   dev = static_cast<File*>(user);
	return dev->read(data,size);
}

static void SkipImage(void *user,int n)
{
	auto   dev = static_cast<File*>(user);

	dev->seek(File::CUR,n);
}

static int EndOfFile(void *user)
{
	auto   dev = static_cast<File*>(user);

	return dev->isEnd();
}

bool loader::Load(File *f,Image *map)
{
	auto   io = static_cast<void*>(f);

	int32_t      width  = 0;
	int32_t      height = 0;
	int32_t      pixel  = 0;

	stbi_io_callbacks    callback;

	callback.read = ReadImage;
	callback.skip = SkipImage;
	callback.eof  = EndOfFile;

	stbi_set_flip_vertically_on_load(1);    //upside down

	auto   data = stbi_load_from_callbacks( &callback, io, &width, &height, &pixel, STBI_rgb_alpha );

	if ( pixel != 4 )
	{
		toy::Oops(TOY_MARK);
		stbi_image_free(data);
		return 0;
	}

	*map = image::Create(width,height,data);

	stbi_image_free(data);

	return 1;
}

bool loader::Save(std::string filename,Image *map)
{
	stbi_write_tga(filename.c_str(), map->width(), map->height(), 4, map->data());
	return 1;
}

}//namespace file
}//namespace toy
