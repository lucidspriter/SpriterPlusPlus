#include "boxobjectinfo.h"

namespace SpriterEngine
{

	BoxObjectInfo::BoxObjectInfo()
	{
	}

	point BoxObjectInfo::getPosition()
	{
		return position;
	}

	real BoxObjectInfo::getAngle()
	{
		return angle.angle;
	}

	point BoxObjectInfo::getScale()
	{
		return scale;
	}

	real BoxObjectInfo::getAlpha()
	{
		return alpha;
	}

	point BoxObjectInfo::getPivot()
	{
		return pivot;
	}

	void BoxObjectInfo::setPosition(const point &newPosition)
	{
		position = newPosition;
	}

	void BoxObjectInfo::setAngle(real newAngle)
	{
		angle.angle = newAngle;
	}

	void BoxObjectInfo::setScale(const point &newScale)
	{
		scale = newScale;
	}

	void BoxObjectInfo::setAlpha(real newAlpha)
	{
		alpha = newAlpha;
	}

	void BoxObjectInfo::setPivot(const point &newPivot)
	{
		pivot = newPivot;
	}

	void BoxObjectInfo::setSpin(int newSpin)
	{
		angle.spinDirection = newSpin;
	}

	void BoxObjectInfo::setObjectTolinear(UniversalObjectInterface *bObject, real t, UniversalObjectInterface *resultObject)
	{
		resultObject->setAngle(angle.angleLinear(bObject->getAngle(), t));
		resultObject->setPosition(linear(position, bObject->getPosition(), t));
		resultObject->setScale(linear(scale, bObject->getScale(), t));
		resultObject->setPivot(pivot);
	}

}
