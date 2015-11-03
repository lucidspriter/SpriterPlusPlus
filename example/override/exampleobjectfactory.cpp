#include "exampleobjectfactory.h"

#include "sfmlpointobjectinfo.h"
#include "sfmlboxinstanceinfo.h"
#include "sfmlsoundobjectinforeference.h"

namespace SpriterEngine
{

	ExampleObjectFactory::ExampleObjectFactory(sf::RenderWindow *validRenderWindow) :
		renderWindow(validRenderWindow)
	{
	}

	PointObjectInfo * ExampleObjectFactory::newPointObjectInfo()
	{
		return new SfmlPointObjectInfo(renderWindow);
	}

	BoxInstanceInfo * ExampleObjectFactory::newBoxInstanceInfo(point size)
	{
		return new SfmlBoxInstanceInfo(size, renderWindow);
	}

}