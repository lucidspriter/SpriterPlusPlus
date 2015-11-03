#include "timeline.h"

#include "timelineinstance.h"

namespace SpriterEngine
{

	Timeline::Timeline(int initialObjectId):
		objectId(initialObjectId)
	{
	}

	Timeline::~Timeline()
	{
		while (keys.size())
		{
			delete keys.back();
			keys.pop_back();
		}
	}

	int Timeline::getObjectId()
	{
		return objectId;
	}

	TimelineKey *Timeline::pushBackKey(TimeInfo *initialTimeInfo, UniversalObjectInterface *initialObjectInfo)
	{
		keys.push_back(new TimelineKey(initialTimeInfo, initialObjectInfo));
		return keys.back();
	}

	TimelineKey *Timeline::pushFrontProxyKey(real initialTime, real initialNextTime, bool isLooping)
	{
		if (keys.size())
		{
			if (isLooping)
			{
				keys.insert(keys.begin(), keys.back()->newProxyKey(initialTime, initialNextTime, false));
			}
			else
			{
				keys.insert(keys.begin(), keys.front()->newProxyKey(initialTime, initialNextTime, true));
			}
			return keys.front();
		}
		else
		{
			// error
			return 0;
		}
	}

	TimelineKey *Timeline::getKey(int keyIndex)
	{
		if (keyIndex < keys.size())
		{
			return keys.at(keyIndex);
		}
		else
		{
			// error
			return 0;
		}
	}

	TimelineKey *Timeline::getLastKey()
	{
		if (keys.size())
		{
			return keys.back();
		}
		else
		{
			return 0;
		}
	}

	void Timeline::setupTimelineInstance(TimelineKeyVector **keyInstances)
	{
		*keyInstances = &keys;
	}

}
