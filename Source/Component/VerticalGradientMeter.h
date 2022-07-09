/*
  ==============================================================================

    VerticalGradientMeter.h
    Created: 9 Jul 2022 6:13:06pm
    Author:  wangb

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

namespace GUI
{
	class VerticalGradientMeter :public Component, public Timer
	{
	public:
		VerticalGradientMeter(std::function<float()>&& valueFuncion) : valueSupplier(std::move(valueFuncion))
		{
			startTimerHz(24);
		}
		void paint(Graphics& g) override
		{
			const auto level = valueSupplier();

			auto bounds = getLocalBounds().toFloat();

			g.setColour(Colours::black);
			g.fillRect(bounds);

			g.setGradientFill(gradient);
			auto scaledY = jmap(level ,-60.f, 6.f, 0.f, static_cast<float>(getHeight()));
			g.fillRect(bounds.removeFromBottom(scaledY));
		}

		void resized() override
		{
			const auto bounds = getLocalBounds().toFloat();
			gradient = ColourGradient{
			Colours::green,
			bounds.getBottomLeft(),
			Colours::red,
			bounds.getTopLeft(),
			false
			};
			gradient.addColour(0.5, Colours::yellow);
		}

		void timerCallback() override
		{
			repaint();
		}
	private:
		std::function<float()> valueSupplier;
		ColourGradient gradient;
	};
}