# Boriation

##  What is this?

A 2D Physics Simulation Engine. This is a personal pet project focus on **accurary** and **stability** when running a simulation

## Features

- Rigid Body Dynamics [X]
- Particle Kinematics []
- Collision Detection & Response []
- Constraint []
- Material Properties []

## Stack

- Core: `C++`
- Build: `CMAKE`

## Install 

Please make sure you already installed GCC and CMAKE on your environment

First, clone this repo and moving to the folder

```bash
git clone https://github.com/ShikiHTM/Boriation.git && cd Boriation
```

Build the project

```bash
cmake -S . -B build &
cmake --build build --config Debug # Or Release
```

Run the simulation

```
./build/Debug/<>.exe
```

## Basic Usage

```cpp
#include "raylib.h"
#include "physics_world.hpp"

inline Vector2 toRaylib(const glm::vec2& vec) {
    return Vector2{ vec.x, vec.y };
}

int main() {
    InitWindow(800, 600, "2D Physics Engine");
    SetTargetFPS(60);

    PhysicsWorld world;

    RigidBody box;
    box.Position = glm::vec2(400.0f, 100.0f);
    box.Theta = 0.0f;
    box.linearMomentum = glm::vec2(0.0f, 0.0f);
    box.angularMomentum = 0.0f;
    box.inverseMass = 1.0f / 2.0f; 
    box.inverseInertia = 1.0f; 
    box.Force = glm::vec2(0.0f);
    box.Torque = 0.0f;

    world.addObject(box);

    auto forceGenerator = [](RigidBody& obj) {
        if (obj.inverseMass > 0.0f) {
            float mass = 1.0f / obj.inverseMass;
            // Raylib's Y-axis points downwards
            glm::vec2 gravity(0.0f, 98.0f); 
            obj.Force += gravity * mass;
        }
    };

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();
        
        // Clamp dt to prevent spiral of death during lag spikes
        if (dt > 0.016f) dt = 0.016f; 

        world.simulate(dt, forceGenerator);

        BeginDrawing();
        ClearBackground(RAYWHITE);

        for (const auto& obj : world.getObjects()) {
            float width = 40.0f;
            float height = 40.0f;
            
            Rectangle rect = { obj.Position.x, obj.Position.y, width, height };
            Vector2 origin = { width / 2.0f, height / 2.0f };
            
            DrawRectanglePro(rect, origin, obj.Theta, DARKBLUE);

            DrawLineEx(
                toRaylib(obj.Position), 
                toRaylib(obj.Position + obj.getLinearVelocity()), 
                2.0f, 
                RED
            );
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
```
