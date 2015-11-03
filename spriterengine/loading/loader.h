#ifndef LOADER_H
#define LOADER_H

#include <string>

namespace SpriterEngine
{

	class SpriterFileLoader;
	class SpriterModel;

	class Loader
	{
	public:
		Loader(SpriterFileLoader *newScmlLoader, SpriterFileLoader *newSconLoader);

		void loadFile(SpriterModel *model, const std::string &fileName);

	private:
		enum SpriterFileType
		{
			SPRITERFILETYPE_NONE,
			SPRITERFILETYPE_SCML,
			SPRITERFILETYPE_SCON
		};

		SpriterFileLoader *scmlLoader;
		SpriterFileLoader *sconLoader;

		SpriterFileType extractFileTypeFromFileName(const std::string &fileName);
	};
}

#endif // LOADER_H