#pragma once
#include "Global.h"
#include "MyMediaPlayerWidget.h"

namespace UI
{
	const char* languagePackData =
		"File\n""文件\n"
		"Edit\n""编辑\n"
		"View\n""视图\n"
		"Tool\n""工具\n"
		;
	const wchar_t* languagePackDataW = L""
		"File\n""文件(F)\n"
		"Edit\n""编辑(E)\n"
		"View\n""视图(V)\n"
		"Tool\n""工具(T)\n"
		;


	gui::Translator translator;
	gui::MenuBar* menuBar;
	gui::DockArea* dockArea;
	gui::DockArea* mediaPlayerWidgetDockArea;
	MyMediaPlayerWidget* mediaPlayerWidget;
	gui::Widget* helpWidget;
}



class MyMainWindow : public gui::MainWindow
{
private:





public:


	MyMainWindow()
	{
		setWindowTitle(L"Craft Media Player");

		gui::GuiFontSystem::loadFromFile("sdf.bin", 0);

		UI::menuBar = new gui::MenuBar(this);
		UI::menuBar->addMenu(L"File");
		UI::menuBar->addMenu(L"Edit");
		UI::menuBar->addMenu(L"View");
		UI::menuBar->addMenu(L"Tool");

		craft_engine_gui_connect(this, resized, this, onResized);
		
		UI::mediaPlayerWidget = new MyMediaPlayerWidget(nullptr);
		UI::dockArea = new gui::DockArea(this);
		UI::mediaPlayerWidgetDockArea = UI::dockArea->dockLeft(UI::mediaPlayerWidget).mFirst;

		UI::translator.loadLangPackFromData(UI::languagePackDataW);
		onTranslationChanged();
		onResized(getSize());
	}

	~MyMainWindow()
	{
		delete UI::menuBar;
	}
protected:

	void onResized(const Size&)
	{
		UI::menuBar->setRect(Rect(0, 0, getWidth(), 25));
		UI::dockArea->setRect(Rect(0, 25, getWidth(), getHeight() - 25));
	}


	void onTranslationChanged()
	{
		UI::menuBar->setMenuName(UI::translator[L"File"], 0);
		UI::menuBar->setMenuName(UI::translator[L"Edit"], 1);
		UI::menuBar->setMenuName(UI::translator[L"View"], 2);
		UI::menuBar->setMenuName(UI::translator[L"Tool"], 3);
	}

	virtual void onAcceptFiles(const gui::StringList& filelist) override
	{
		for (auto& it : filelist)
		{
			std::wcout << it << "\n";
		}
		auto file_name = gui::StringTool::toUtf8(filelist.front());

		UI::mediaPlayerWidget->mediaSetFile(file_name);
		UI::mediaPlayerWidget->mediaSetPlay();
		UI::mediaPlayerWidgetDockArea->setTitle(0, filelist.front());
	}




};


