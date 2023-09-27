#include "BonePerson.h"

BonePerson::BonePerson()
{
	init();
}

void BonePerson::init()
{
	// load the textures for the ememys and set the parameters for the sprite
	if (!m_bonePersonTexture.loadFromFile("ASSETS/Actor/Characters/Skeleton/SpriteSheet.png"))
	{
		std::cout << "skeleton failed to load from file\n";
	}
	m_enemySprite.setTexture(m_bonePersonTexture);
	m_enemySprite.setTextureRect(sf::IntRect(0, 0, 16, 16));
	m_enemySprite.setOrigin(8, 8);
	m_enemySprite.setScale(SCALE, SCALE);
	m_enemySprite.setPosition(m_enemyPos);

	if (!m_healthBarProgTex.loadFromFile("ASSETS/HUD/LifeBarMiniProgress.png"))
	{
		std::cout << "error loading healthbar front\n";
	}
	if (!m_healthBarUnderTex.loadFromFile("ASSETS/HUD/LifeBarMiniUnder.png"))
	{
		std::cout << "error loading healthbar front\n";
	}
	m_healthBarProgress.setTexture(m_healthBarProgTex);
	m_healthBarUnder.setTexture(m_healthBarUnderTex);

	m_healthBarProgress.setOrigin(9, 2);
	m_healthBarUnder.setOrigin(9, 2);
	m_healthBarProgress.setScale(SCALE, SCALE);
	m_healthBarUnder.setScale(SCALE, SCALE);
}

void BonePerson::update()
{	
	// update enemy health bar 
	m_healthBarProgress.setTextureRect(sf::IntRect(0, 0, (0.17 * health) + 1, 4));
	m_healthBarUnder.setPosition(m_enemyPos.x, m_enemyPos.y - 32);
	m_healthBarProgress.setPosition(m_enemyPos.x, m_enemyPos.y - 32);

	// check health values
	if (health < 0)
	{
		alive = false;
		health = 0;
	}
}

void BonePerson::render(sf::RenderWindow& window)
{
	window.draw(m_enemySprite);
	window.draw(m_healthBarUnder);
	window.draw(m_healthBarProgress);
}

sf::Sprite BonePerson::getSprite() const
{
	return m_enemySprite; // get the enemy sprite
}

sf::Vector2f BonePerson::getPos()
{
	return m_enemySprite.getPosition();
}

void BonePerson::moveToNextCell(sf::Vector2f t_nextPos)//take in coordinate relative to cell
{
	m_direction = t_nextPos - m_enemySprite.getPosition();
	m_distance = std::sqrt(m_direction.x * m_direction.x + m_direction.y * m_direction.y);
	m_direction /= m_distance;
	m_velocity = m_direction * 2.0f;

	m_enemySprite.move(m_velocity);//move to middle of cell
}

void BonePerson::dealDamage(int t_damage)
{
	health -= t_damage;
}
