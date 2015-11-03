#ifndef EXAMPLEOBJECTFACTORY_H
#define EXAMPLEOBJECTFACTORY_H

#include "SFML/Graphics/RenderWindow.hpp"

#include "../../spriterengine/override/objectfactory.h"

namespace SpriterEngine
{

	class ExampleObjectFactory : public ObjectFactory
	{
	public:
		ExampleObjectFactory(sf::RenderWindow *validRenderWindow);
		
		PointObjectInfo *newPointObjectInfo() override;

		BoxInstanceInfo *newBoxInstanceInfo(point size) override;

	private:
		sf::RenderWindow *renderWindow;
	};

}

#endif // EXAMPLEOBJECTFACTORY_H
