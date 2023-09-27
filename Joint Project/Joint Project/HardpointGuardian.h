#pragma once
#include "Globals.h"
#include "LizardParticles.h"

class HardpointGuardian {
public:
	HardpointGuardian();
	void update(sf::Vector2f t_playerPos);
	void init();
	void draw(sf::RenderWindow& window);
	void placeEnemy(sf::Vector2f t_placeHere);
	void animate();
	sf::Sprite getSprite();
	enum Direction
	{
		Up,
		Down,
		Left,
		Right
	} m_direction;

	enum AnimationState
	{
		Idle,
		Walking,
		Attacking
	} m_animationState;
	int health = 40;
	thor::Timer particlesTimer;
private:
	sf::Sprite guardianSprite;
	sf::Texture guardianTexture;

	LizardParticles myParticles;
	bool showParticles;
	
	sf::Vector2f deadPos;

	int frameTimer = 0;
	bool changeFrame = false;
	int currentFrame = 0;

};