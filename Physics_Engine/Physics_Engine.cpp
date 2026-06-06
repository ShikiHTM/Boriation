// Physics_Engine.cpp : Defines the entry point for the application.
//

#include "Physics_Engine.h"
#include "header/physics_world.hpp"
#include "raylib.h"
#include <math.h>
#include <stdio.h>

constexpr float METERS_TO_PIXERLS = 100.0f;
constexpr Vector2 ORIGIN_SCREEN = { 400.0f, 100.0f };
constexpr std::string_view ODE_FUNCTION = "Velocity Verlet";

Vector2 PhysToScreen(glm::vec2 physPos) {
	return {
		ORIGIN_SCREEN.x + physPos.x * METERS_TO_PIXERLS,
		ORIGIN_SCREEN.y - physPos.y * METERS_TO_PIXERLS
	};
}

int main()
{
	InitWindow(800, 600, ODE_FUNCTION.data());
	SetTargetFPS(60);

	PhysicsWorld world;

	RigidBody bob;
	bob.Position = glm::vec2(2.0f, 0.0f);
	bob.Theta = 0.0f;
	bob.linearMomentum = glm::vec2(0.0f, 0.0f);
	bob.angularMomentum = 0.0f;
	bob.inverseMass = 1.0f / 2.0; // Mass is 2kg
	bob.inverseInertia = 1.0f;

	world.addObject(bob);

	glm::vec2 pivotPhys(0.0f, 0.0f);

	while (!WindowShouldClose()) {
		float dt = 1.0f / 60.0f;
		world.simulate(dt, [](RigidBody& obj) {
			glm::vec2 gravity = glm::vec2(0.0f, -9.81f);
			float mass = 1 / obj.inverseMass;
			const float stiffness = 5000;

			obj.Force += gravity * mass;

			//spring force
			glm::vec2 pivotPos = glm::vec2(0.0f, 0.0f);
			
			glm::vec2 stringVec = pivotPos - obj.Position;
			float stringLength = glm::length(stringVec);
			glm::vec2 dir = stringVec / stringLength;

			float forcePullingOut = glm::dot(obj.Force, -dir);

			const float restLength = 2.0f;
			glm::vec2 velocity = obj.linearMomentum * obj.inverseMass;
			float vSquare = glm::dot(velocity, velocity);
			float centripetalForce = mass * (vSquare / restLength);

			float stringForce = stiffness * (stringLength - restLength);
			float tensionMagnitude = forcePullingOut + centripetalForce + stringForce;

			glm::vec2 tensionVector = dir * tensionMagnitude;
			obj.Force += tensionVector;
			});

		BeginDrawing();
		ClearBackground(WHITE);

		const std::vector<RigidBody>& objects = world.getObjects();
		glm::vec2 bobPhysPos = objects[0].Position;

		Vector2 screenPivot = PhysToScreen(pivotPhys);
		Vector2 screenBob = PhysToScreen(bobPhysPos);

		DrawLineEx(screenPivot, screenBob, 2.0f, DARKGRAY);
        DrawCircleV(screenPivot, 5.0f, BLACK);
        DrawCircleV(screenBob, 20.0f, RED);

        DrawText(TextFormat("Phys X: %.2f m", bobPhysPos.x), 10, 10, 20, DARKGRAY);
        DrawText(TextFormat("Phys Y: %.2f m", bobPhysPos.y), 10, 30, 20, DARKGRAY);
        
        EndDrawing();
	}
	
	CloseWindow();
	return 0;
}
