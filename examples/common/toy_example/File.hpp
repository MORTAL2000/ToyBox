
#pragma once

#include <toy/File.hpp>
#include <toy/ImageBuffer.hpp>

namespace toy{
namespace example{

static inline bool LoadImage( const std::string& folder,
                              const std::string& file,
                              toy::ImageBuffer*  image,
                              enum toy::Option   mode = toy::DIRECTORY)
{
	toy::File       dev(mode);

	dev.openDir(folder);

	if ( ! dev.open(file) )
	{
		toy::Logger << "Image file not find!" << toy::NewLine;
	}
	else if ( ! toy::file::loader::Load(&dev,image) )
	{
		toy::Logger << "Image load failed!" << toy::NewLine;
	}
	else if ( image->data()==nullptr )
	{
		toy::Logger << "Image load nothing!" << toy::NewLine;
	}
	else
	{
		toy::Logger << "Image load success!" << toy::NewLine;
		return true;
	}

	return false;
}

}}
