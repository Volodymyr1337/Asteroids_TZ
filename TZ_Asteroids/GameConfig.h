#pragma once
#include "Framework.h"
#include "vec2.h"

enum class RENDER_QUEUE {
	BACKGROUND,
	PROJECTILE,
	ABILITIES,
	ASTEROID,
	SPACESHIP,
	AIM
};

enum class ABILITY_TYPE {
	HOMING_MISSILE,
	POWER_SHIELD,	// TODO
	AUTOSHOOTING	// TODO
};

class GameConfig
{
public:
	static GameConfig& Instance()
	{
		static GameConfig _instance;
		return _instance;
	}

	vec2f asteroidSpeed;	// x - min / y - max
	int windowWidth;
	int windowHeight;
	int mapWidth;
	int mapHeight;
	int numAmmo;
	int numAsteroids;
	float abilityProbability;
	float spaceshipAcceleration;
	float bulletSpeed;
	int homingMissileSpeed;

	void Initialize(int argc, char *argv[]);

private:
	GameConfig() {
		windowWidth = 800;
		windowHeight = 600;
		mapWidth = 1000;
		mapHeight = 1000;
		numAmmo = 3;
		numAsteroids = 5;

		abilityProbability = 0.3f;
		asteroidSpeed = vec2f(40.f, 60.f);
		spaceshipAcceleration = 2;
		bulletSpeed = 500;
		homingMissileSpeed = 200;
	};
	~GameConfig() {};

	GameConfig(GameConfig const&) = delete;
	GameConfig& operator= (GameConfig const&) = delete;
	
};
