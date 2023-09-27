#pragma once
#include "Globals.h"

class Enemy {
public:
	Enemy();
	sf::Vector2f getPos();
	void init();
	void update(sf::Vector2f t_pos);
	void render(sf::RenderWindow & window);
	void stealBow(sf::Vector2f t_pos);
	void resetRacoon(int t_pos);
	sf::Sprite getSprite();
	void applyDamage(int t_damageAmount);
	void setPos(sf::Vector2f t_pos);
	void dealDamage(int t_damage);
	int getHealth();
	thor::Timer raccCooldown;
private:

	enum EnemyType
	{
		BonePerson,
		RobbinRacoon,
		Cyclops,
		Bamboo,
		Axolot
	}m_enemyType;

	thor::Timer racoonSprint;
	float m_racoonSpeed = 7;
	sf::Vector2f m_direction;
	sf::Vector2f m_velocity;
	float m_distance;


	sf::Texture m_racconRobberTexture;

	sf::Sprite m_enemySprite;

	sf::Vector2f m_enemyPos = {500,600};

	sf::Vector2f m_racoonSpawn = { -64,100 };

	int health = 20;
};
