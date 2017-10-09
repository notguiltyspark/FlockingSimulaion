#pragma once

#ifndef BOID_PARAMETERS_H
#define BOID_PARAMETERS_H


class BoidParameters{
public:
	float maxSpeed;
	float maxForce;

	float desiredSeparation;
	float visionRadius;

	float alignCoef;
	float coheseCoef;
	float separateCoef;

	BoidParameters() {}
   ~BoidParameters() {}
};

#endif
