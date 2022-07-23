#pragma once
#include <iostream>
#include <thread>
#include <vector>
#include "BaseD.h"

void inline sleep(uint32_t ms) {
	std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}



int main()
{
	using namespace csgoBased;
	const uint16_t maxPlayers = 10;
	const float smoothing = 1.f;
	const float minFov = 10.f;

	if (!csgoBased::init()) {
		std::cout << "An error occured. Error: " << GetLastError() << std::endl;
	}


	Player player;
	player.getPlayer();

	std::vector<Entity> entities;
	entities.reserve(maxPlayers);


	for (int i = 0; i < maxPlayers; i++) {
		entities.emplace_back(Entity(i));
	}

	float bestFov;
	float deltaFov;
	float currentFov;

	vec3 angleDelta;
	vec3 playerPos;
	vec3 currentAngle;
	vec3 offsetAngle;
	vec3 aimPunch;


	while (true) {
		sleep(16);

		bestFov = minFov;
		offsetAngle = {0,0,0};


		playerPos = player.getEyePosition();
		currentAngle = player.getViewAngles();
		aimPunch = player.getAimPunch();
		for (auto& entity : entities) {
			if (entity.getTeam() == player.getTeam())
				continue;
			if (entity.isDormant()) 
				continue;
			if (entity.isDead())
				continue;
			if (!entity.isVisible())
				continue;

			// Get angle delta in degrees between the crosshair and the enetity's head (ie : how much to move to get to head)
			angleDelta = (entity.getHeadPosition() - player.getEyePosition()).toAngle() - currentAngle + aimPunch;

			// Calculate the distance between the crosshair and head in degrees (fov distance)
			deltaFov = std::hypot(angleDelta.x, angleDelta.y);

			// Select smallest fov
			if (deltaFov < bestFov) {
				deltaFov = bestFov;
				offsetAngle = angleDelta;
			}

		}

		// Move crosshair by smallest fov
		player.setViewAngles(currentAngle + offsetAngle / smoothing );
	}
}
