#pragma once

#include <vector>
#include <glm/glm.hpp>
#include "rigid_body.hpp"
#include "integrator.h"

class PhysicsWorld {
private:
	std::vector<RigidBody> objects;

	//void solveConstraints();
	//void updateStateArraySize();
	//void flattenState(const std::vector<RigidBody>& objects, std::vector<float>& out_array);
	//void unflattenState(std::vector<RigidBody>& objects, const std::vector<float>& in_array);
public:
	void addObject(const RigidBody& body);

	template <typename dxdy>
	void simulate(float dt, dxdy&& func) {
		if (objects.empty()) return;

		for (RigidBody& obj : objects) {
			obj.Force = glm::vec2(0.0f);
			obj.Torque = 0.0f;
		}
		
		for (RigidBody& obj : objects) {
			Engine::Math::step(obj, dt, func);
		}
	};

	const std::vector<RigidBody>& getObjects() const { return objects; }
	//void addConstraint(size_t bodyIndex, glm::vec2 pivot, float length);
	//void addForceGenerator(size_t bodyIndex, IForceGenerator* generator);
};