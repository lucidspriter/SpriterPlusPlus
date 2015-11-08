#include "loader.h"

#include "../override/spriterfiledocumentwrapper.h"

namespace SpriterEngine
{
	Loader::Loader(SpriterFileDocumentWrapper * newScmlDocumentWrapper, SpriterFileDocumentWrapper * newSconDocumentWrapper) :
		scmlDocumentWrapper(newScmlDocumentWrapper),
		sconDocumentWrapper(newSconDocumentWrapper)
	{
	}

	void Loader::loadFile(SpriterModel * model, const std::string &fileName)
	{

		SpriterFileType fileType = extractFileTypeFromFileName(fileName);
		switch (fileType)
		{
		case SPRITERFILETYPE_SCML:
			if (scmlDocumentWrapper)
			{
				spriterDocumentLoader.loadFile(model, scmlDocumentWrapper, fileName);
			}
			else
			{
				// error
			}
			break;

		case SPRITERFILETYPE_SCON:
			if (sconDocumentWrapper)
			{
				spriterDocumentLoader.loadFile(model, sconDocumentWrapper, fileName);
			}
			else
			{
				// error
			}
			break;

		default:
			// error;
			break;
		}
	}

	Loader::SpriterFileType Loader::extractFileTypeFromFileName(const std::string &fileName)
	{
		size_t lastDot = fileName.find_last_of(".");
		if (lastDot != std::string::npos)
		{
			std::string extension = fileName.substr(lastDot + 1, std::string::npos);

			if (extension == "scml")
			{
				return SPRITERFILETYPE_SCML;
			}
			else if (extension == "scon")
			{
				return SPRITERFILETYPE_SCON;
			}
		}
		// error
		return SPRITERFILETYPE_NONE;
	}
}


