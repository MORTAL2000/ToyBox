
#include "toy/File.hpp"
#include "toy/Image.hpp"
#include "toy/file/loader/Png.hpp"
#include <SFML/Window.hpp>
#include "Render.hpp"


static int LoadImage(std::string file,toy::Image *image)
{
	toy::File       dev;

	if ( !dev.open(file) )
	{
		toy::Log("Image file not find!\n");
		return 0;
	}

	if ( ! toy::file::loader::Png::Load(&dev,image) )
	{
		toy::Log("Image load failed!\n");
	}

	if ( image->getData() )
	{
		toy::Log("Image load success!\n");
	}
	else
	{
		toy::Log("Image load nothing!\n");
		return 0;
	}

	return 1;
}

static void HandleEvent(std::shared_ptr<sf::Window> window)
{
	sf::Event event;

	while ( window->pollEvent(event) )
	{
		switch ( event.type )
		{
			case sf::Event::Closed:

				window->close();
				break;

			case sf::Event::KeyPressed:

				if ( event.key.code == sf::Keyboard::Escape )
				{
					window->close();
				}
				break;

			case sf::Event::Resized:

				Render::Resize(event.size.width, event.size.height);
				break;

			default:
				break;
		}
	}
}

static sf::String ConvertFromUtf8ToUtf32(std::string str)
{
	return sf::String::fromUtf8(str.begin(),str.end());
}

static std::shared_ptr<sf::Window> CreateWindowS()
{
	sf::ContextSettings      contextSettings;
	contextSettings.depthBits = 24;

	sf::String    title = ConvertFromUtf8ToUtf32("ToyBox;玩具箱;おもちゃ箱;장난감 상자;खिलौनो का बक्सा");

	auto    window = std::make_shared<sf::Window>(
		sf::VideoMode(800, 600),
		title.getData(),
		sf::Style::Default,
		contextSettings);

	return window;
}

int main()
{
	std::string   path(TOY_RESOURCE_PATH);

	toy::Image     image;

	if ( ! LoadImage(path+"/002.png",&image) )
	{
		return EXIT_FAILURE;
	}

	auto    window = CreateWindowS();

	window->setActive();

	Render::AddImage(image);

	while ( window->isOpen() )
	{
		HandleEvent(window);
		Render::DrawImage();
		window->display();
	}

	return EXIT_SUCCESS;
}
