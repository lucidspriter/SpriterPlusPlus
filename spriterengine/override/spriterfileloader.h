#ifndef SPRITERFILELOADER_H
#define SPRITERFILELOADER_H

#include <string>

namespace SpriterEngine
{
	class SpriterModel;

	class SpriterFileLoader
	{
	public:
		SpriterFileLoader();

		virtual void loadFile(SpriterModel *model, const std::string &fileName);
	};
}

#endif // SPRITERFILELOADER_H