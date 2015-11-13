#include "loader.h"

#include "../global/settings.h"

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
				Settings::error("Loader::loadFile - attempting to load scml file \"" + fileName + "\" : no scml document wrapper found");
			}
			break;

		case SPRITERFILETYPE_SCON:
			if (sconDocumentWrapper)
			{
				spriterDocumentLoader.loadFile(model, sconDocumentWrapper, fileName);
			}
			else
			{
				Settings::error("Loader::loadFile - attempting to load scon file \"" + fileName + "\" : no scon document wrapper found");
			}
			break;

		default:
			Settings::error("Loader::loadFile - attempting to load file \"" + fileName + "\" : unrecognized file type");
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
			else
			{
				Settings::error("Loader::extractFileTypeFromFileName - file \"" + fileName + "\" : unrecognized file type");
			}
		}
		else
		{
			Settings::error("Loader::extractFileTypeFromFileName - file \"" + fileName + "\" : unable to extract extension from file name");
		}
		return SPRITERFILETYPE_NONE;
	}
}


