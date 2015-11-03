#include "boneinstanceinfo.h"

namespace SpriterEngine
{

	BoneInstanceInfo::BoneInstanceInfo(point initialSize) :
		scale(1, 1),
		alpha(1),
		size(initialSize)
	{
	}

	point BoneInstanceInfo::getPosition()
	{
		return position;
	}

	real BoneInstanceInfo::getAngle()
	{
		return angle.angle;
	}

	point BoneInstanceInfo::getScale()
	{
		return scale;
	}

	real BoneInstanceInfo::getAlpha()
	{
		return alpha;
	}

	point BoneInstanceInfo::getSize()
	{
		return size;
	}


	void BoneInstanceInfo::setPosition(const point &newPosition)
	{
		position = newPosition;
	}

	void BoneInstanceInfo::setAngle(real newAngle)
	{
		angle.angle = newAngle;
	}

	void BoneInstanceInfo::setScale(const point &newScale)
	{
		scale = newScale;
	}

	void BoneInstanceInfo::setAlpha(real newAlpha)
	{
		alpha = newAlpha;
	}

	void BoneInstanceInfo::setObjectTolinear(UniversalObjectInterface *bObject, real t, UniversalObjectInterface *resultObject)
	{
		resultObject->setAngle(angle.angleLinear(bObject->getAngle(), t));
		resultObject->setPosition(linear(position, bObject->getPosition(), t));
		resultObject->setScale(linear(scale, bObject->getScale(), t));
		resultObject->setAlpha(linear(alpha, bObject->getAlpha(), t));
	}

	void BoneInstanceInfo::render()
	{
		// TODO: override and add drawing code here to enable bone debug rendering

		// getPosition()
		// getAngle();
		// getScale();
		// getPivot().x * getSize().x;
	}

}
