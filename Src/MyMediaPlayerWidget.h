#pragma once
#include "MediaControlerWidget.h"

class MyMediaPlayerWidget : public gui::MediaPlayerWidget {
private:

	MediaControlerWidget* m_mediaControlerWidget;

public:

	MyMediaPlayerWidget(MediaPlayerWidget* parent) : MediaPlayerWidget(parent)
	{
		m_mediaControlerWidget = new MediaControlerWidget(this);


		m_mediaControlerWidget->setButtonCallback(0, std::function<void(void)>([this]() {
			if (mediaIsPlaying())
			{
				mediaSetPaused();
			}
			else
			{		
				mediaSetPlay();
			}
		}));


		m_mediaControlerWidget->setButtonCallback(1, std::function<void(void)>([this]() {
			mediaSetStop();
		}));

		m_mediaControlerWidget->setSeekBarCallback(std::function<void(double)>([this](double progress) {
			mediaSeekFrame(progress * mediaGetDuration());
		}));


		craft_engine_gui_connect_v2(this, mediaPlay, [this]() {
			m_mediaControlerWidget->setPlayButton(false);
		});
		craft_engine_gui_connect_v2(this, mediaPause, [this]() {
			m_mediaControlerWidget->setPlayButton(true);
		});
		craft_engine_gui_connect_v2(this, mediaStop, [this]() {
			m_mediaControlerWidget->setPlayButton(true);
		});
	}

private:
	virtual void onResizeEvent(const ResizeEvent& resizeEvent) override
	{
		m_mediaControlerWidget->setRect(Rect(0, getHeight() - 54, getWidth(), 54));
	}


	virtual void onPaintEvent() override
	{
		m_mediaControlerWidget->setProgress(mediaGetTimestamp() / mediaGetDuration());
		MediaPlayerWidget::onPaintEvent();
	}
};