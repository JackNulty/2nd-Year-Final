#pragma once
#include "Globals.h"

class BonePerson {

public:
	BonePerson();
	void init();
	void update();
	void render(sf::RenderWindow& window);
	sf::Sprite getSprite() const;
	sf::Vector2f getPos();

	void moveToNextCell(sf::Vector2f t_nextPos);
	void dealDamage(int t_damage);
private:
	sf::Texture m_bonePersonTexture;
	sf::Sprite m_enemySprite;
	sf::Vector2f m_enemyPos = { 500,600 };

	int health = 100;

	sf::Sprite m_healthBarUnder;
	sf::Texture m_healthBarUnderTex;

	sf::Sprite m_healthBarProgress;
	sf::Texture m_healthBarProgTex;

	bool alive = true;

	sf::Vector2f m_direction;
	sf::Vector2f m_velocity;
	float m_distance;
};