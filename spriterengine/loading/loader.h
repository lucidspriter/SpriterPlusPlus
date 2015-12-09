#ifndef LOADER_H
#define LOADER_H

#include <string>

#include "spriterdocumentloader.h"

namespace SpriterEngine
{

	class SpriterFileDocumentWrapper;
	class SpriterModel;

	class Loader
	{
	public:
		Loader(SpriterFileDocumentWrapper *newScmlDocumentWrapper, SpriterFileDocumentWrapper *newSconDocumentWrapper);
		~Loader();

		void loadFile(SpriterModel *model, const std::string &fileName);

	private:
		enum SpriterFileType
		{
			SPRITERFILETYPE_NONE,
			SPRITERFILETYPE_SCML,
			SPRITERFILETYPE_SCON
		};
		
		SpriterDocumentLoader spriterDocumentLoader;

		SpriterFileDocumentWrapper *scmlDocumentWrapper;
		SpriterFileDocumentWrapper *sconDocumentWrapper;

		SpriterFileType extractFileTypeFromFileName(const std::string &fileName);
	};
}

#endif // LOADER_H
