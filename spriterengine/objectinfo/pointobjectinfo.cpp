#include "pointobjectinfo.h"

namespace SpriterEngine
{

	PointObjectInfo::PointObjectInfo()
	{
	}

	point PointObjectInfo::getPosition()
	{
		return position;
	}

	real PointObjectInfo::getAngle()
	{
		return angle.angle;
	}


	void PointObjectInfo::setPosition(const point &newPosition)
	{
		position = newPosition;
	}

	void PointObjectInfo::setAngle(real newAngle)
	{
		angle.angle = newAngle;
	}

	void PointObjectInfo::setSpin(int newSpin)
	{
		angle.spinDirection = newSpin;
	}


	void PointObjectInfo::setObjectTolinear(UniversalObjectInterface *bObject, real t, UniversalObjectInterface *resultObject)
	{
		resultObject->setPosition(linear(position, bObject->getPosition(), t));
		resultObject->setAngle(angle.angleLinear(bObject->getAngle(), t));
		resultObject->setPosition(linear(position, bObject->getPosition(), t));
	}

	void PointObjectInfo::render()
	{
		// if (renderDebugPoints)
		// TODO: override and add drawing code here to enable point debug rendering
	}

}
