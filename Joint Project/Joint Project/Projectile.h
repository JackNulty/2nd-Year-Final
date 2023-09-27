#include "Globals.h"
#include <Thor/Particles.hpp>
#include "Particles.h"


class Projectile {
public:

	Projectile();

	Particles particleSystem;

	void init();
	void update();
	void draw(sf::RenderWindow& window);

	sf::Vector2i m_mousePosition = {0,0};
	sf::Vector2f m_trueMousePos;
	sf::Vector2f m_direction = {0.0f,0.0f};
	float m_distance = 0.0f;
	sf::Vector2f m_velocity = { 0,0 };
	float m_speed = 12;

	sf::Sprite getSprite() const;
	void setPos(sf::Vector2f t_newPos);
	void createProjectile(sf::Vector2f t_playerPos);
private:
	sf::Sprite m_arrowSprite;
	sf::Texture m_arrowTexture;

	sf::SoundBuffer m_arrow;
	sf::Sound m_firing;
};