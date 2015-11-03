#ifndef FILEFACTORY_H
#define FILEFACTORY_H

#include <string>

#include "../global/global.h"

namespace SpriterEngine
{

	class ImageFile;
	class SoundFile;
	class SpriterFileLoader;

	class FileFactory
	{
	public:
		FileFactory();

		virtual ImageFile *newImageFile(const std::string &initialFilePath, point initialDefaultPivot);
		virtual SoundFile *newSoundFile(const std::string &initialFilePath);

		virtual SpriterFileLoader *newScmlLoader();
		virtual SpriterFileLoader *newSconLoader();
	};

}

#endif // FILEFACTORY_H
