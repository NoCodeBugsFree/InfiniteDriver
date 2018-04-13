// Only 3dMotive and Crocopede has permission to redistribuite this project and all of its contents.

#include "TruckWheelFront.h"

UTruckWheelFront::UTruckWheelFront()
{
	ShapeRadius = 63.f;
	ShapeWidth = 90.f;
	Mass = 5.f;
	SteerAngle = 60.f;
	bAffectedByHandbrake = false;
	MaxBrakeTorque = 9000.f;
	MaxHandBrakeTorque = 9000.f;
}
