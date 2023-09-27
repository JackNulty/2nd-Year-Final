#include "Globals.h"
#include "Projectile.h"

class Weapon {
public:
	Projectile myProjectile[MAX_PROJECTILES];

	enum type
	{
		NONE,
		BOW,
		FORK,
		SHURIKEN
	}m_weaponType;

	thor::Timer swapCooldown;
	thor::Timer bulletCooldown;

	int m_currentWeapon = NONE;

	void init();
	void update(double dt);
	void draw(sf::RenderWindow& window);
	void updateProjectiles();
	void drawProjectiles(sf::RenderWindow& window);
	void generateBullet(sf::Vector2f t_playerPos);
	void setPos(sf::Vector2f t_newPos);

	void changeWeapon();

	int handleCollisions(sf::Sprite t_enemySprite);

	int m_bulletCooldown = 20;
	int m_currentBullet = 0;

private:	
	sf::Vector2i mousePosition;
	sf::Vector2f mousePosRelative;

	sf::Sprite m_bowSprite;
	sf::Texture m_bowTexture;

	sf::Sprite m_shurikenSprite;
	sf::Texture m_shurikenTexture;

	sf::Texture m_forkinHandTexture;
	sf::Texture m_forkTexture;
	sf::Sprite m_forkSprite;
};