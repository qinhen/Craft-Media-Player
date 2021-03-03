#pragma once
#include "Global.h"
#include "Resources.h"
class MediaControlerWidget: public gui::Widget
{
private:
	gui::HSeekBar* m_seekBar;
	gui::PushButton* m_buttons[4];
	using ButtonCallback = core::Callback<void(void)>;
	ButtonCallback   m_buffonCallbacks[4];
	using SeekBarCallback = core::Callback<void(double)>;
	SeekBarCallback  m_seekBarCallback;
	gui::HandleImage m_icons[5];
	int m_curAlpha;
public:
	MediaControlerWidget(Widget* parent) : Widget(parent)
	{
		loadIcon((void**)m_icons);
		getPalette().mFillMode = gui::Palette::eFillMode_Color;
		m_buttons[0] = new gui::PushButton(this); // play/pause
		m_buttons[1] = new gui::PushButton(this); // stop
		m_buttons[2] = new gui::PushButton(this); // last(left) / move back(right)
		m_buttons[3] = new gui::PushButton(this); // next(left) / move forward(right)
		m_buttons[0]->setIcon(m_icons[3]);
		m_buttons[1]->setIcon(m_icons[4]);
		m_buttons[2]->setIcon(m_icons[0]);
		m_buttons[3]->setIcon(m_icons[1]);
		for (int i = 0; i < 4; i++)
		{
			//m_buttons[i]->getPalette().mFrameMode = gui::Palette::eFrameMode_Surround;
			craft_engine_gui_connect_v2(m_buttons[i], clicked, [=]() {
				m_buffonCallbacks[i].call();
			});
		}

		m_seekBar = new gui::HSeekBar(this);
		craft_engine_gui_connect_v2(m_seekBar, slid, [=](double progress) {
			this->m_seekBarCallback.call(progress);
		});
	}

	void setButtonCallback(int index, ButtonCallback callback)
	{
		m_buffonCallbacks[index] = callback;
	}
	void setSeekBarCallback(SeekBarCallback callback)
	{
		m_seekBarCallback = callback;
	}

	void setPlayButton(bool enable)
	{
		if (enable)
			m_buttons[0]->setIcon(m_icons[3]);
		else
			m_buttons[0]->setIcon(m_icons[2]);
	}

	void setProgress(double progress)
	{
		m_seekBar->setPercentage(progress);
	}
private:
	virtual void onResizeEvent(const ResizeEvent& resizeEvent) override
	{
		m_seekBar->setRect(Rect(0, 0, getWidth(), 12));
		int button_h = getHeight() - 15;
		int button_w = button_h / 0.618f;
		int button_x_step = button_w + 3;

		for (int i = 0; i < 4; i++)
		{
			m_buttons[i]->setRect(Rect(i * button_x_step + 1, 14, button_w, button_h));
		}
	}
	virtual void onPaintEvent()
	{	
		Widget::onPaintEvent();

		for (auto c : getChildrenWidgets())
		{
			if (c->isHighlight())
			{
				return;
			}
		}

		if (!isHighlight())
			m_curAlpha = math::clamp(m_curAlpha - 1, 0, 255);
		setAlpha(m_curAlpha);
	}
	virtual void onMoveIn(const MouseEvent&)override
	{
		m_curAlpha = 500;
	}
};