#ifndef FILE_H
#define FILE_H

#include <string>

namespace SpriterEngine
{

	class ImageFile;
	class SoundFile;

	class File
	{
	public:
		File(std::string initialFilePath);
		virtual ~File() {}

		virtual ImageFile *imageFile();
		virtual SoundFile *soundFile();

	protected:
		std::string path();

	private:
		std::string filePath;
	};

}

#endif // FILE_H
