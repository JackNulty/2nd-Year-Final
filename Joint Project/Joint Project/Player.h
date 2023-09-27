#pragma once
#include "Globals.h"
#include <iostream>
#include "Weapon.h"
#include "RunningParticles.h"


class Player {
public:
	Player();
	void init();
	void render(sf::RenderWindow & window);
	void update(double dt);
	void checkKeyPresses();
	void playAnimation();
	void dash();
	sf::Sprite getSprite();
	sf::Vector2f getPos();

	void swapCharacter(int t_characterNum);
	int passSprite(sf::Sprite t_enemy);
	enum AnimationState
	{
		Idle,
		Walking,
		Attacking
	} m_animationState;

	int m_hitsTaken = 0;

	enum Direction
	{
		Up,
		Down,
		Left,
		Right
	} m_direction;

	sf::Vector2f playerPos = { 696 * SCALE,456 * SCALE };
	thor::Timer bowGone;
private:
	Weapon myWeapon;

	PlayerParticles myParticles;
	sf::Vector2f m_directionParticles = {0,0};

	sf::Texture playerSpritesheet;
	sf::Sprite playerSprite;
	sf::Texture blueNinjaSpritesheet;
	sf::Texture redNinjaSpritesheet;
	sf::Texture greyNinjaSpritesheet;
	sf::Texture cavemanSpritesheet;
	sf::Texture knightSpritesheet;

	int frameTimer = 0;
	int attackTimer = 0;
	bool changeAttackFrame = false;
	bool changeFrame = false;
	int currentFrame = 0;
	int currentAttackFrame = 0;
	bool attack = false;

	//dash variables
	bool isDashing = false;
	int dashTime = 10;
	int cooldown = 120;

	thor::Timer m_footStepTimer;
	sf::SoundBuffer m_footStepSound;
	sf::Sound m_stompers;
	float m_walkTimer = 0.25;
	thor::Timer dashTimer;
	thor::Timer dashCooldown;
	
};