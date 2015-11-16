#include "soundobjectinforeference.h"

#include "../file/filereference.h"

namespace SpriterEngine
{

	SoundObjectInfoReference::SoundObjectInfoReference()
	{
	}

	int SoundObjectInfoReference::getTriggerCount()
	{
		return triggerCount;
	}

	real SoundObjectInfoReference::getVolume()
	{
		return volume;
	}

	real SoundObjectInfoReference::getPanning()
	{
		return panning;
	}

	void SoundObjectInfoReference::setTriggerCount(int newTriggerCount)
	{
		triggerCount = newTriggerCount;
	}

	void SoundObjectInfoReference::setVolume(real newVolume)
	{
		volume = newVolume;
		setPlaybackVolume();
	}

	void SoundObjectInfoReference::setPanning(real newPanning)
	{
		panning = newPanning;
		setPlaybackPanning();
	}

	void SoundObjectInfoReference::setPlaybackVolume()
	{
		// TODO: override and add code to adjust current playback volume using getVolume() here
	}

	void SoundObjectInfoReference::setPlaybackPanning()
	{
		// TODO: override and add code to adjust current playback panning using getPanning() here
	}

	void SoundObjectInfoReference::setToBlendedLinear(UniversalObjectInterface *aObject, UniversalObjectInterface *bObject, real t, real blendRatio, ObjectRefInstance *blendedRefInstance)
	{
		real tempPanning = panning;
		real tempVolume = volume;

		aObject->setObjectToLinear(bObject, t, this);

		setPanning(linear(tempPanning, panning, blendRatio));
		setVolume(linear(tempVolume, volume, blendRatio));
	}

}
