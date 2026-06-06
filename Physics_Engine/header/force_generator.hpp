#pragma once

#include "rigid_body.hpp"

class IForceGenerator {
public:
	virtual void updateForce(RigidBody& body, float dt) = 0;
};