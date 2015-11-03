#ifndef GLOBAL_H
#define GLOBAL_H

namespace SpriterEngine
{

	typedef double real;

	static const int THIS_ENTITY = -1;
	static const int OUT_OF_RANGE = - 1;

	static const real ONEEIGHTY_OVER_PI = 57.295779513082320876798154814105;

	static const real MAX_RADIANS = 6.28318530718;

	static real toRadians(real angleInDegrees)
	{
		return angleInDegrees / ONEEIGHTY_OVER_PI;
	}

	static real toDegrees(real angleInRadians)
	{
		return angleInRadians * ONEEIGHTY_OVER_PI;
	}

	static real linear(real a, real b, real t)
	{
		return ((b - a)*t) + a;
	}

	static real inverseLinear(real a, real b, real x)
	{
		return (x - a) / (b - a);
	}

	static real quadratic(real a, real b, real c, real t)
	{
		return linear(linear(a, b, t), linear(b, c, t), t);
	}

	static real cubic(real a, real b, real c, real d, real t)
	{
		return linear(quadratic(a, b, c, t), quadratic(b, c, d, t), t);
	}

	static real quartic(real a, real b, real c, real d, real e, real t)
	{
		return linear(cubic(a, b, c, d, t), cubic(b, c, d, e, t), t);
	}

	static real quintic(real a, real b, real c, real d, real e, real f, real t)
	{
		return linear(quartic(a, b, c, d, e, t), quartic(b, c, d, e, f, t), t);
	}

	struct point
	{
		point(real initialX = 0, real initialY = 0) :
			x(initialX),
			y(initialY)
		{
		}

		real x;
		real y;
	};

	static point linear(const point &a, const point &b, real t)
	{
		return point(linear(a.x, b.x, t), linear(a.y, b.y, t));
	}

	static point add(const point &a, const point &b)
	{
		return point(a.x + b.x, a.y + b.y);
	}

	static point multiply(const point &a, const point &b)
	{
		return point(a.x * b.x, a.y * b.y);
	}

}
#endif // GLOBAL_H
