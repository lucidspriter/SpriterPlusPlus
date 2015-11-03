#ifndef EXAMPLEFILEFACTORY_H
#define EXAMPLEFILEFACTORY_H

#include "../../spriterengine/override/filefactory.h"

#include "SFML/Graphics.hpp"

namespace SpriterEngine
{

	class ImageFile;
	class SoundFile;
	class SpriterFileLoader;
	class ExampleFileFactory : public FileFactory
	{
	public:
		ExampleFileFactory(sf::RenderWindow *validRenderWindow);
		
		ImageFile *newImageFile(const std::string &initialFilePath, point initialDefaultPivot) override;

		SoundFile *newSoundFile(const std::string &initialFilePath) override;

		SpriterFileLoader *newScmlLoader() override;

	private:
		sf::RenderWindow *renderWindow;
	};

}

#endif // EXAMPLEFILEFACTORY_H
