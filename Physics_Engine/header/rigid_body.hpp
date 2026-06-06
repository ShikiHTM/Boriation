#pragma once
#include <glm/glm.hpp>
#include <vector>

struct RigidBody {
	glm::vec2 Position; // x(t)
	float Theta; // R(t)
	glm::vec2 linearMomentum; // P(t)
	float angularMomentum; // L(t)

	float inverseMass;
	float inverseInertia;

	glm::vec2 Force;
	float Torque;

	glm::vec2 getLinearVelocity() const {
		return linearMomentum * inverseMass;
	}

	float getAngularVelocity() const {
		return angularMomentum * inverseInertia;
	}
};
