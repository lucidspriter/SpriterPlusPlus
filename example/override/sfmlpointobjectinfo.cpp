#include "sfmlpointobjectinfo.h"

namespace SpriterEngine
{

	SfmlPointObjectInfo::SfmlPointObjectInfo(sf::RenderWindow *validRenderWindow) :
		renderWindow(validRenderWindow),
		circle(10)
	{
		circle.setFillColor(sf::Color::Red);
		circle.setOrigin(5, 5);
	}

	void SfmlPointObjectInfo::render()
	{
		circle.setPosition(getPosition().x, getPosition().y);
		circle.setRotation(toDegrees(getAngle()));
		circle.setScale(getScale().x, getScale().y);
		renderWindow->draw(circle);
	}

}
