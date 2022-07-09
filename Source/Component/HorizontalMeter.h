/*
  ==============================================================================

    HorizontalMeter.h
    Created: 9 Jul 2022 4:14:48pm
    Author:  wangb

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

namespace GUI
{
	class HorizontalMeter : public Component
	{
	public:
		void paint(Graphics& g) override
		{
			auto bounds = getLocalBounds().toFloat();

			g.setColour(Colours::white.withBrightness(0.4));
			g.fillRoundedRectangle(bounds, 5.f);

			g.setColour(Colours::white);
			auto scaledX = jmap(level, -60.f, 6.f, 0.f, static_cast<float>(getWidth()));
			g.fillRoundedRectangle(bounds.removeFromLeft(scaledX),5.f);
		}


		void setLevel(int value) { level = value; }
	private:
		float level = -60.f;
	};
}