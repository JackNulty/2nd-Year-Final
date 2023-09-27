#include "Weapon.h"

void Weapon::init()
{
	m_weaponType = NONE;// No weapon in hand
	if (!m_bowTexture.loadFromFile("ASSETS/Items/Weapons/Bow2/Sprite.png"))
	{
		std::cout << "error loading bow\n";
	}
	m_bowSprite.setTexture(m_bowTexture);
	m_bowSprite.setScale(2.5,2.5);
	m_bowSprite.setRotation(0);
	m_bowSprite.setOrigin(7.5, -5);

	if (!m_shurikenTexture.loadFromFile("ASSETS/FX/Projectile/Shuriken.png"))
	{
		std::cout << "error loading shuriken\n";
	}
	m_shurikenSprite.setTexture(m_shurikenTexture);
	m_shurikenSprite.setScale(SCALE, SCALE);

	if (!m_forkinHandTexture.loadFromFile("ASSETS/Items/Weapons/Fork/SpriteInHand.png"))
	{
		std::cout << "fork in hand failed to load\n";
	}
	if (!m_forkTexture.loadFromFile("ASSETS/Items/Weapons/Fork/Sprite.png"))
	{
		std::cout << "fork failed to load\n";
	}
	m_forkSprite.setTexture(m_forkinHandTexture);
	m_forkSprite.setOrigin(3.5, 0);
	m_forkSprite.setScale(SCALE, SCALE);
	m_forkSprite.setRotation(270);
}

void Weapon::update(double dt)
{
	sf::Vector2f spritePosition = m_bowSprite.getPosition();

	sf::Vector2f direction = sf::Vector2f(mousePosRelative) - spritePosition;//direction is the mouse position relative to the view less the sprites position
	float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);//the distance between the mouse and sprite
	direction /= distance;

	float angleRadians = std::atan2(direction.y, direction.x);//get the angle in radians

	float angleDegrees = angleRadians * 180 / thor::Pi;//convert to degrees

	m_bowSprite.setRotation(angleDegrees - 90);//rotate the bow to face the mouses position

	

}

void Weapon::draw(sf::RenderWindow& window)
{
	mousePosition = sf::Mouse::getPosition(window);//get the mouses potition
	mousePosRelative = window.mapPixelToCoords(mousePosition);//change the coords to be relative to the screen



	if (m_weaponType == BOW)
	{
		window.draw(m_bowSprite);
	}
	if (m_weaponType == SHURIKEN)
	{
		window.draw(m_shurikenSprite);
	}
	if (m_weaponType == FORK)
	{
		window.draw(m_forkSprite);
	}
}

void Weapon::updateProjectiles()
{
	for (int i = 0; i < MAX_PROJECTILES; i++)
	{
		myProjectile[i].update();
	}
}

void Weapon::drawProjectiles(sf::RenderWindow& window)
{
	for (int i = 0; i < MAX_PROJECTILES; i++)
	{
		myProjectile[i].draw(window);
	}
}



void Weapon::generateBullet(sf::Vector2f t_playerPos)
{
	if (m_weaponType == BOW)
	{
		if (bulletCooldown.isExpired())
		{
			bulletCooldown.reset(sf::seconds(0.3));
			bulletCooldown.start();
			m_currentBullet++;
			if (m_currentBullet > MAX_PROJECTILES - 1)
			{
				m_currentBullet = 0;
			}
			myProjectile[m_currentBullet].createProjectile(t_playerPos);//create a bullet on the players pos
		}
	}
}

void Weapon::setPos(sf::Vector2f t_newPos)
{
	m_bowSprite.setPosition(t_newPos.x,t_newPos.y);
	m_shurikenSprite.setPosition(t_newPos);
	m_forkSprite.setPosition(t_newPos.x + 10,t_newPos.y + 12);
}

void Weapon::changeWeapon()
{
	if (swapCooldown.isExpired())
	{
		swapCooldown.restart(sf::seconds(0.4));
		if (m_weaponType == NONE)
		{
			m_weaponType = BOW;
		}
		//else if (m_weaponType == BOW)
		//{
		//	m_weaponType = FORK;
		//}
		else m_weaponType = NONE;
	}
}

int Weapon::handleCollisions(sf::Sprite t_enemySprite)
{
	for (int i = 0; i < MAX_PROJECTILES; i++)
	{
		if (t_enemySprite.getGlobalBounds().intersects(myProjectile[i].getSprite().getGlobalBounds()))
		{
			myProjectile[i].setPos(sf::Vector2f(2000000, 200000));
			return 20;
		}
	}
	return 0;
}