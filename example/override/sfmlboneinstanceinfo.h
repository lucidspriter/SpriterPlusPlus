#ifndef SFMLBONEINSTANCEINFO_H
#define SFMLBONEINSTANCEINFO_H

#include "SFML/Graphics/RenderWindow.hpp"

#include "SFML/Graphics/ConvexShape.hpp"

#include "../../spriterengine/objectinfo/boneinstanceinfo.h"

namespace SpriterEngine
{

	class SfmlBoneInstanceInfo : public BoneInstanceInfo
	{
	public:
		SfmlBoneInstanceInfo(point initialSize, sf::RenderWindow *validRenderWindow);

		void render(const EntityInstance* instance) override;

	private:
		sf::RenderWindow *renderWindow;

		sf::ConvexShape boneShape;
	};

}

#endif // SFMLBONEINSTANCEINFO_H
