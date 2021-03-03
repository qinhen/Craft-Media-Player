#define CRAFT_ENGINE_GUI_APPLICATION
#include "MyMainWindow.h"

int main()
{
	using namespace CraftEngine;

	core::setUtf8();
	openal::OpenALSystem::init();


	gui::Application app;

	auto main_window = new MyMainWindow();


	main_window->setUpdateEveryFrame(true);

	auto palette = main_window->getPalette();
	palette.setBackgroundImage(gui::GuiRenderSystem::createImage("img.png"));
	main_window->setPalette(palette);


	main_window->exec();

	openal::OpenALSystem::close();
	return 0;
}

