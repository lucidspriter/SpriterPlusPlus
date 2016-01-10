#ifndef CF25SOUNDOBJECTINFOREFERENCE_H
#define CF25SOUNDOBJECTINFOREFERENCE_H

#include "spriterengine/override/soundobjectinforeference.h"

#include "Common.h"

namespace SpriterEngine
{
	

	class Cf25SoundObjectInfoReference : public SoundObjectInfoReference
	{
	public:
		Cf25SoundObjectInfoReference(Extension* ext, LPRDATA rdPtr, string name, UINT SoundId);

		void playTrigger() override;

	private:
		void setPlaybackVolume() override;
		void setPlaybackPanning() override;

		Extension* ext;
		LPRDATA rdPtr;
		string name;
		UINT soundId;
	};

}

#endif // CF25SOUNDOBJECTINFOREFERENCE_H
