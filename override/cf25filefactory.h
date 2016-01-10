#ifndef CF25FILEFACTORY_H
#define CF25FILEFACTORY_H

#include "spriterengine/override/filefactory.h"

#include "Common.h"

namespace SpriterEngine
{

	class Cf25FileFactory : public FileFactory
	{
	public:
		Cf25FileFactory(LPRDATA rdPTr, Extension *ext);
		
		ImageFile *newImageFile(const std::string &initialFilePath, point initialDefaultPivot) override;

		SoundFile *newSoundFile(const std::string &initialFilePath) override;

		SpriterFileDocumentWrapper *newScmlDocumentWrapper() override;

	private:
		LPRDATA rdPtr;
		Extension *ext;
	};

}

#endif // CF25FILEFACTORY_H
