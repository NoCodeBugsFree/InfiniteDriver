// Only 3dMotive and Crocopede has permission to redistribuite this project and all of its contents.

#include "TruckWheelBack.h"


UTruckWheelBack::UTruckWheelBack()
{
	ShapeRadius = 63.f;
	ShapeWidth = 90.f;
	Mass = 5.f;
	SteerAngle = 0.f;
	bAffectedByHandbrake = true;
	MaxBrakeTorque = 9000.f;
	MaxHandBrakeTorque = 9000.f;
}
