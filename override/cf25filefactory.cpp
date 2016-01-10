#include "cf25filefactory.h"

#include "spriterengine/override/imagefile.h"
#include "spriterengine/override/soundfile.h"

#include "tinyxmlspriterfiledocumentwrapper.h"

#include "cf25imagefile.h"
#include "cf25soundfile.h"

namespace SpriterEngine
{

	Cf25FileFactory::Cf25FileFactory(LPRDATA rdPtr,Extension* ext) :
		rdPtr(rdPtr), ext(ext)
	{
	}

	ImageFile * Cf25FileFactory::newImageFile(const std::string &initialFilePath, point initialDefaultPivot)
	{
		return new Cf25ImageFile(initialFilePath, initialDefaultPivot, rdPtr, ext);
	}

	SoundFile * Cf25FileFactory::newSoundFile(const std::string & initialFilePath)
	{
		return new Cf25SoundFile(initialFilePath,rdPtr, ext);
	}

	SpriterFileDocumentWrapper * Cf25FileFactory::newScmlDocumentWrapper()
	{
		return new TinyXmlSpriterFileDocumentWrapper(ext->scmlFileString);
	}
}
