#ifndef TAGOBJECTINFOREFERENCE_H
#define TAGOBJECTINFOREFERENCE_H

#include <string>

#include "universalobjectinterface.h"

namespace SpriterEngine
{

	class TagList;
	class TagObjectInfoReference : public UniversalObjectInterface
	{
	public:
		TagObjectInfoReference();

		bool tagIsActive(std::string tagToCheck) const override;

		void setTagList(TagList *newTagList) override;

	private:
		const TagList *tagList;
	};

}

#endif // TAGOBJECTINFOREFERENCE_H
