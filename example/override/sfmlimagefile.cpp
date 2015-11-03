#include "sfmlimagefile.h"

#include "../../spriterengine/objectinfo/universalobjectinterface.h"

namespace SpriterEngine
{

	SfmlImageFile::SfmlImageFile(std::string initialFilePath, point initialDefaultPivot, sf::RenderWindow *validRenderWindow) :
		ImageFile(initialFilePath,initialDefaultPivot),
		renderWindow(validRenderWindow)
	{
		initializeFile();
	}

	void SfmlImageFile::initializeFile()
	{
		if (texture.loadFromFile(path()))
		{
			// texture.setSmooth(true);
			sprite.setTexture(texture);
		}
		else
		{
			// error
		}
	}

	void SfmlImageFile::renderSprite(UniversalObjectInterface * spriteInfo)
	{
		sprite.setColor(sf::Color(255, 255, 255, 255 * spriteInfo->getAlpha()));
		sprite.setPosition(spriteInfo->getPosition().x, spriteInfo->getPosition().y);
		sprite.setRotation(toDegrees(spriteInfo->getAngle()));
		sprite.setScale(spriteInfo->getScale().x, spriteInfo->getScale().y);
		sprite.setOrigin(spriteInfo->getPivot().x*texture.getSize().x, spriteInfo->getPivot().y*texture.getSize().y);
		renderWindow->draw(sprite);
	}

}
