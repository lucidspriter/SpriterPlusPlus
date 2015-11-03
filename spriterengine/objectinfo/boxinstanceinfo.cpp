#include "boxinstanceinfo.h"

namespace SpriterEngine
{

	BoxInstanceInfo::BoxInstanceInfo(point initialSize):
		size(initialSize)
	{
	}

	point BoxInstanceInfo::getPosition()
	{
		return position;
	}

	real BoxInstanceInfo::getAngle()
	{
		return angle.angle;
	}

	point BoxInstanceInfo::getScale()
	{
		return scale;
	}

	point BoxInstanceInfo::getPivot()
	{
		return pivot;
	}

	point BoxInstanceInfo::getSize()
	{
		return size;
	}

	void BoxInstanceInfo::setPosition(const point &newPosition)
	{
		position = newPosition;
	}

	void BoxInstanceInfo::setAngle(real newAngle)
	{
		angle.angle = newAngle;
	}

	void BoxInstanceInfo::setScale(const point &newScale)
	{
		scale = newScale;
	}

	void BoxInstanceInfo::setPivot(const point &newPivot)
	{
		pivot = newPivot;
	}

	void BoxInstanceInfo::setObjectTolinear(UniversalObjectInterface *bObject, real t, UniversalObjectInterface *resultObject)
	{
		resultObject->setAngle(angle.angleLinear(bObject->getAngle(), t));
		resultObject->setPosition(linear(position, bObject->getPosition(), t));
		resultObject->setScale(linear(scale, bObject->getScale(), t));
		resultObject->setPivot(pivot);
	}

	void BoxInstanceInfo::render()
	{
		// TODO: add drawing code here to enable bone debug rendering
	}

}
