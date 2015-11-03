#include "file.h"

namespace SpriterEngine
{

	File::File(std::string initialFilePath) :
		filePath(initialFilePath)
	{

	}

	ImageFile *File::imageFile()
	{
		return 0;
	}

	SoundFile *File::soundFile()
	{
		return 0;
	}

	std::string File::path()
	{
		return filePath;
	}

}
