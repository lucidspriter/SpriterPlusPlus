#include "cf25soundobjectinforeference.h"

namespace SpriterEngine
{

	Cf25SoundObjectInfoReference::Cf25SoundObjectInfoReference(Extension* ext, LPRDATA rdPtr, string name, int soundId):
		ext(ext), rdPtr(rdPtr), name(name), soundId(soundId)
	{
	}

	void Cf25SoundObjectInfoReference::playTrigger()
	{
		if (getTriggerCount() && soundId>0)
		{
			LPRH rhPtr = rdPtr->rHo.hoAdRunHeader;
			PlaySnd(rhPtr->rh4.rh4Mv->mvSndMgr, rhPtr->rhIdAppli, soundId, rhPtr->rhHMainWin, PS_LOOP, 0, 1);
			ext->SoundEvent[name] += 1;
		}
	}

	void Cf25SoundObjectInfoReference::setPlaybackVolume()
	{
		LPRH rhPtr = rdPtr->rHo.hoAdRunHeader;
		SetSndChannelVolume(rhPtr->rhIdAppli, 1, 100 * getVolume());
	}

	void Cf25SoundObjectInfoReference::setPlaybackPanning()
	{
		LPRH rhPtr = rdPtr->rHo.hoAdRunHeader;
		SetSndChannelPan(rhPtr->rhIdAppli, 1, 100 * getPanning());
	}

}
