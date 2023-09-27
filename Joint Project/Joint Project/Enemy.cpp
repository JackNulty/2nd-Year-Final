#include "Enemy.h"

Enemy::Enemy()
{
	init();
}

void Enemy::init()
{
	
	if (!m_racconRobberTexture.loadFromFile("ASSETS/Actor/Monsters/Racoon/SpriteSheet.png"))
	{
		std::cout << "racoon texture failed to laod\n";
	}
	m_enemySprite.setTexture(m_racconRobberTexture);
	m_enemySprite.setTextureRect(sf::IntRect(0, 0, 16, 16));
	m_enemySprite.setOrigin(8, 8);
	m_enemySprite.setScale(SCALE, SCALE);
	m_enemySprite.setPosition(m_racoonSpawn);
	health = 10;

}

void Enemy::update(sf::Vector2f t_pos)
{
	//m_enemyPos = m_racoonSpawn;
	if (raccCooldown.isExpired())
	{
		stealBow(t_pos);
	}
	if (raccCooldown.isRunning())
	{
		//m_enemySprite.setPosition(sf::Vector2f(-2000, -2000));
	}
}

void Enemy::render(sf::RenderWindow& window)
{
	// draw enemy and health bar
	if (raccCooldown.isExpired())
	{
		window.draw(m_enemySprite);
	}
	//else window.draw(m_enemySprite);
}

int Enemy::getHealth()
{
	return health;
}

void Enemy::stealBow(sf::Vector2f t_pos)
{
	m_direction = t_pos - m_enemySprite.getPosition();
	m_distance = std::sqrt(m_direction.x * m_direction.x + m_direction.y * m_direction.y);
	m_direction /= m_distance;
	m_velocity = m_direction * 3.0f;


	if (m_distance < 900)//if the player is closer than 900 pixels
	{
		m_enemySprite.move(m_velocity);
	}
}

void Enemy::resetRacoon(int t_pos)
{
	raccCooldown.restart(sf::seconds(15));//raccoon is gone for 15 seconds
	if (t_pos == 0)//respawn to predetermined pos
	{
		m_enemySprite.setPosition(m_racoonSpawn);
	}
	else if (t_pos == 1)
	{
		m_enemySprite.setPosition(sf::Vector2f(-(32 * SCALE), 720 * SCALE));
	}
	else if (t_pos == 2)
	{
		m_enemySprite.setPosition(sf::Vector2f(560 * SCALE, -(32 * SCALE)));
	}
	else if (t_pos == 3)
	{
		m_enemySprite.setPosition(sf::Vector2f(992 * SCALE, -(32 * SCALE)));
	}
	else if (t_pos == 4)
	{
		m_enemySprite.setPosition(sf::Vector2f(3000, 2700));
	}
	else {
		std::cout << "index for racoon respawn invalid\n";
	}
	health = 20;//put raccoon on full health
}


sf::Sprite Enemy::getSprite()
{
	return m_enemySprite; // get the enemy sprite
}

void Enemy::applyDamage(int t_damageAmount)
{
	// apply damage to the enemy when the player hits
	health = health - t_damageAmount;

	std::cout << health << "\n";
}

sf::Vector2f Enemy::getPos()
{
	return m_enemySprite.getPosition();
}

void Enemy::setPos(sf::Vector2f t_pos)
{
	m_enemySprite.setPosition(t_pos);
}

void Enemy::dealDamage(int t_damage) 
{
	health -= t_damage;
}
