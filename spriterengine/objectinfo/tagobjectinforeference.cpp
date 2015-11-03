#include "tagobjectinforeference.h"

#include "taglist.h"

namespace SpriterEngine
{

	TagObjectInfoReference::TagObjectInfoReference() :
		tagList(0)
	{
	}

	bool TagObjectInfoReference::tagIsActive(std::string tagToCheck) const
	{
		if (tagList)
		{
			return tagList->tagIsActive(tagToCheck);
		}
		else
		{
			return false;
		}
	}

	void TagObjectInfoReference::setTagList(TagList *newTagList)
	{
		tagList = newTagList;
	}

}
