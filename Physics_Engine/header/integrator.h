#pragma once
#include <glm/glm.hpp>
namespace Engine::Math {
	template <typename ode>
	void step(
		RigidBody& object,
		float dt,
		ode&& dxdy
	)
	{
		/*
			The Runge-Kutta method has been show their ability of how steady it's when calculate the "the might the next position" of the function. But it has the
			down side since the method is not conserves the linear momentum itself. Hence cause the energy to be bursted or loss by time. We're using Velocity Verlet
			instead.
		*/
		
/*		size_t n = arraySize;

		dxdy(t, y0, k1);

		for (size_t i = 0; i < n; i++) {
			y_temp[i] = y0[i] + k1[i] * (dt * 0.5f);
		}

		dxdy(t + (dt * 0.5f), y_temp, k2);

		for (size_t i = 0; i < n; i++) {
			y_temp[i] = y0[i] + k2[i] * (dt * 0.5f);
		}

		dxdy(t + (dt * 0.5f), y_temp, k3);

		for (size_t i = 0; i < n; i++) {
			y_temp[i] = y0[i] + k3[i] * dt;
		}

		dxdy(t + dt, y_temp, k4);

		float dt6 = dt / 6.0f;
		for (size_t i = 0; i < n; i++) {
			yend[i] = y0[i] + dt6 * (k1[i] + 2 * k2[i] + 2 * k3[i] + k4[i]);
		}*/

		object.linearMomentum += object.Force * (0.5f * dt);
		object.angularMomentum += object.Torque * (0.5f * dt);

		glm::vec2 objVelocity = object.linearMomentum * object.inverseMass;

		object.Position += objVelocity * dt;

		object.Force = glm::vec2(0.0f, 0.0f);
		object.Torque = 0.0f;

		dxdy(object);

		object.linearMomentum += object.Force * (0.5f * dt);
		object.angularMomentum += object.Torque * (0.5f * dt);

	}
}
