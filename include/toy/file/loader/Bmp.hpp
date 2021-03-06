
#pragma once

#include "toy/Standard.hpp"
#include "toy/file/Export.hpp"

namespace toy{
class File;
class ImageBuffer;
}

namespace toy{
namespace file{
namespace loader{
namespace bmp{

TOY_API_FILE bool Load(::toy::File *f,::toy::ImageBuffer *m);
TOY_API_FILE bool Save(::toy::File *f,::toy::ImageBuffer *m);   // File mode STD only.
TOY_API_FILE bool Save(::toy::File *f,const ::toy::ImageBuffer *m);   // File mode STD only.

}}}}
