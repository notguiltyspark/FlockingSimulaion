#pragma once

#ifndef BOID_PARAMETERS_H
#define BOID_PARAMETERS_H


class BoidParameters{
public:
	float maxSpeed = 2.8;
	float maxForce = 0.09;

	float desiredSeparation = 10; //constexpr or input?
	float visionRadius      = 15;

	float alignCoef    = 0.9;
	float coheseCoef   = 0.4;
	float separateCoef = 0.9;

	BoidParameters() {}
   ~BoidParameters() {}
};

#endif
