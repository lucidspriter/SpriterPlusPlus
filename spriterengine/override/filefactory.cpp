#include "filefactory.h"

#include "imagefile.h"
#include "soundfile.h"

#include "spriterfileloader.h"

namespace SpriterEngine
{

	FileFactory::FileFactory()
	{
	}

	ImageFile * FileFactory::newImageFile(const std::string &initialFilePath, point initialDefaultPivot)
	{
		return new ImageFile(initialFilePath, initialDefaultPivot);
	}

	SoundFile * FileFactory::newSoundFile(const std::string &initialFilePath)
	{
		return new SoundFile(initialFilePath);
	}

	SpriterFileLoader * FileFactory::newScmlLoader()
	{
		return new SpriterFileLoader();
	}

	SpriterFileLoader * FileFactory::newSconLoader()
	{
		return new SpriterFileLoader();
	}

}