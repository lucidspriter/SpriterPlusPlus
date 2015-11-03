#include "loader.h"

#include "../override/spriterfileloader.h"

namespace SpriterEngine
{
	Loader::Loader(SpriterFileLoader * newScmlLoader, SpriterFileLoader * newSconLoader) :
		scmlLoader(newScmlLoader),
		sconLoader(newSconLoader)
	{
	}

	void Loader::loadFile(SpriterModel * model, const std::string &fileName)
	{

		SpriterFileType fileType = extractFileTypeFromFileName(fileName);
		switch (fileType)
		{
		case SPRITERFILETYPE_SCML:
			scmlLoader->loadFile(model, fileName);
			break;

		case SPRITERFILETYPE_SCON:
			sconLoader->loadFile(model, fileName);
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
		return SPRITERFILETYPE_NONE;
	}
}


