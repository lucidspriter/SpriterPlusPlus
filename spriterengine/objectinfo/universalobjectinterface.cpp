#include "universalobjectinterface.h"

namespace SpriterEngine
{

	UniversalObjectInterface::UniversalObjectInterface()
	{
	}

	UniversalObjectInterface::~UniversalObjectInterface()
	{
	}

	point UniversalObjectInterface::getPosition()
	{
		// error
		return point();
	}

	real UniversalObjectInterface::getAngle()
	{
		// error
		return 0;
	}

	point UniversalObjectInterface::getScale()
	{
		// error
		return point(1, 1);
	}

	point UniversalObjectInterface::getPivot()
	{
		// error
		return point();
	}

	real UniversalObjectInterface::getAlpha()
	{
		// error
		return 1;
	}

	point UniversalObjectInterface::getSize()
	{
		// error
		return point();
	}


	ImageFile *UniversalObjectInterface::getImage()
	{
		// error
		return 0;
	}

	EntityInstanceData * UniversalObjectInterface::getEntity(int entityId)
	{
		// error
		return 0;
	}

	real UniversalObjectInterface::getCurrentTime()
	{
		// error
		return 0;
	}

	real UniversalObjectInterface::getTimeRatio()
	{
		// error
		return 0;
	}

	void UniversalObjectInterface::reprocessCurrentTime()
	{
		// error
	}

	ObjectInterfaceVector * UniversalObjectInterface::getZOrder()
	{
		// error
		return 0;
	}

	real UniversalObjectInterface::getRealValue()
	{
		// error
		return 0;
	}

	int UniversalObjectInterface::getIntValue()
	{
		// error
		return 0;
	}

	std::string UniversalObjectInterface::getStringValue()
	{
		// error
		return "";
	}

	int UniversalObjectInterface::getTriggerCount()
	{
		// error
		return 0;
	}

	real UniversalObjectInterface::getVolume()
	{
		// error
		return 1;
	}

	real UniversalObjectInterface::getPanning()
	{
		// error
		return 0;
	}

	VariableInstanceNameAndIdMap *UniversalObjectInterface::getVariables()
	{
		// error
		return 0;
	}

	UniversalObjectInterface *UniversalObjectInterface::getTags() const
	{
		// error
		return 0;
	}

	bool UniversalObjectInterface::tagIsActive(std::string tagToCheck) const
	{
		// error
		return false;
	}


	void UniversalObjectInterface::setPosition(const point &newPosition)
	{
		// error
	}

	void UniversalObjectInterface::setAngle(real newAngle)
	{
		// error
	}

	void UniversalObjectInterface::setScale(const point &newScale)
	{
		// error
	}

	void UniversalObjectInterface::setPivot(const point &newPivot)
	{
		// error
	}

	void UniversalObjectInterface::setAlpha(real newAlpha)
	{
		// error
	}

	void UniversalObjectInterface::setSpin(int newSpin)
	{
		// error
	}


	void UniversalObjectInterface::setImage(ImageFile *newImageFile)
	{
		// error
	}


	void UniversalObjectInterface::setCurrentEntity(int newEntityId)
	{
		// error
	}

	void UniversalObjectInterface::setCurrentEntity(EntityInstanceData * newCurrentEntity)
	{
		// error
	}

	void UniversalObjectInterface::setCurrentAnimation(int newAnimationIndex)
	{
		// error
	}

	void UniversalObjectInterface::setCurrentAnimation(AnimationInstance * newCurrentAnimation)
	{
		// error
	}

	void UniversalObjectInterface::setTimeRatio(real newCurrentTimeRatio)
	{
		// error
	}

	void UniversalObjectInterface::setRealValue(real newValue)
	{
		// error
	}

	void UniversalObjectInterface::setIntValue(int newValue)
	{
		// error
	}

	void UniversalObjectInterface::setStringValue(std::string newValue)
	{
		// error
	}

	void UniversalObjectInterface::setStringValue(std::string *newValue)
	{
		// error
	}

	void UniversalObjectInterface::setTriggerCount(int newTriggerCount)
	{
		// error
	}

	void UniversalObjectInterface::setVolume(real newVolume)
	{
		// error
	}

	void UniversalObjectInterface::setPanning(real newPanning)
	{
		// error
	}

	void UniversalObjectInterface::setSound(SoundFile *newSoundFile)
	{
		// error
	}

	void UniversalObjectInterface::setTagList(TagList *newTagList)
	{
		// error
	}

	void UniversalObjectInterface::setObjectTolinear(UniversalObjectInterface *bObject, real t, UniversalObjectInterface *resultObject)
	{
		// error
	}

	void UniversalObjectInterface::render()
	{
		// error
	}

	void UniversalObjectInterface::playTrigger()
	{
		// error
	}

}
