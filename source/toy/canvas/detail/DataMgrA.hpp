
#pragma once

#include "toy/Standard.hpp"
#include "toy/canvas/Standard.hpp"
#include "toy/math/Matrix4.hpp"

namespace toy{
namespace canvas{
namespace _detail{

class Brush;
class Geometry;
class Image;

/*
 * For OpenGL 3.0+
 */
class DataMgrA
{
	public:

		DataMgrA();
		~DataMgrA();

		void render(toy::canvas::Brush *brush,float diff);

		void add(toy::canvas::Geometry*);
		void del(toy::canvas::Geometry*);
		void add(toy::canvas::Image*);
		void del(toy::canvas::Image*);

	private:

		std::vector<toy::canvas::Geometry*>      _geometryList;
		std::vector<toy::canvas::Image*>         _imageList;
};

}}}
