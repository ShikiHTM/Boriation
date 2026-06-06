#include "physics_world.hpp"
#include "integrator.h"

/*
	Since we're using verlet right now so we don't need to flat the object anymore
*/

//void PhysicsWorld::updateStateArraySize() {
//	const size_t required_floats = objects.size() * STATE_SIZE;
//
//	y0.resize(required_floats);
//	yend.resize(required_floats);
//	y_temp.resize(required_floats);
//	k1.resize(required_floats);
//	k2.resize(required_floats);
//	k3.resize(required_floats);
//	k4.resize(required_floats);
//}

void PhysicsWorld::addObject(const RigidBody& body) {
	objects.push_back(body);
	//updateStateArraySize();
}

//void PhysicsWorld::flattenState(const std::vector<RigidBody>& objects, std::vector<float>& out_array) {
//	out_array.clear();
//	out_array.reserve(objects.size() * 6);
//
//	for (const RigidBody& obj : objects) {
//		out_array.push_back(obj.Position.x);
//		out_array.push_back(obj.Position.y);
//		out_array.push_back(obj.Theta);
//		out_array.push_back(obj.linearMomentum.x);
//		out_array.push_back(obj.linearMomentum.y);
//		out_array.push_back(obj.angularMomentum);
//	}
//};
//
//void PhysicsWorld::unflattenState(std::vector<RigidBody>& objects, const std::vector<float>& in_array) {
//	if (in_array.size() < objects.size() * 6) return;
//
//	for (int i = 0; i < objects.size(); i += 6) {
//		int baseIndex = i * 6;
//		RigidBody& curObj = objects[i];
//		
//		curObj.Position.x = in_array[baseIndex];
//		curObj.Position.y = in_array[baseIndex + 1];
//		curObj.Theta = in_array[baseIndex + 2];
//		curObj.linearMomentum.x = in_array[baseIndex + 3];
//		curObj.linearMomentum.y = in_array[baseIndex + 4];
//		curObj.angularMomentum = in_array[baseIndex + 5];
//	}
//};
