#include "Projectile.h"

Projectile::Projectile()
{
	init();
}

void Projectile::init()
{
	//load image and set parameters for the sprite 
	if (!m_arrowTexture.loadFromFile("ASSETS/Items/Weapons/Bow2/Arrow.png"))
	{
		std::cout << "error loading Arrow";
	}
	m_arrowSprite.setTexture(m_arrowTexture);
	m_arrowSprite.setScale(2, 2);
	m_arrowSprite.setOrigin(-2, 2.5);

	m_arrowSprite.setPosition(-200000, -200000);
	if (!m_arrow.loadFromFile("ASSETS/Sounds/Game/Magic1.wav"))
	{
		std::cout << "error loading arrow sound\n";
	}
	m_firing.setBuffer(m_arrow);
}

void Projectile::update()
{	
	m_arrowSprite.move(m_velocity); // move the arrow based on a velocity
	particleSystem.update(m_arrowSprite.getPosition(), m_direction); // update the particle system that follows the arrow
}

void Projectile::draw(sf::RenderWindow& window)
{
	window.draw(m_arrowSprite); //draw sprite

	m_mousePosition = sf::Mouse::getPosition(window); // get mouse pos
	m_trueMousePos = window.mapPixelToCoords(m_mousePosition); //  get more accurate mos pos
	particleSystem.render(window); // draw particles
}

sf::Sprite Projectile::getSprite() const
{
	return m_arrowSprite; // return arrow sprite
}

void Projectile::setPos(sf::Vector2f t_newPos)
{
	m_arrowSprite.setPosition(t_newPos); // set arrow pos
}

void Projectile::createProjectile(sf::Vector2f t_playerPos)
{
	m_arrowSprite.setPosition(t_playerPos.x,t_playerPos.y); // set arrow pos

	m_direction = sf::Vector2f(m_trueMousePos) - t_playerPos; // get the direction the arrow is to go

	m_distance = std::sqrt(m_direction.x * m_direction.x + m_direction.y * m_direction.y); // get distance 
	m_direction /= m_distance;

	m_velocity = m_direction * m_speed; // get the velocity 

	// Calculate the angle between the direction vector and the positive x-axis in radians
	float angleRadians = std::atan2(m_direction.y, m_direction.x);

	// Convert the angle from radians to degrees
	float angleDegrees = angleRadians * 180 / thor::Pi;

	// Set the rotation of the sprite to face the mouse cursor
	m_arrowSprite.setRotation(angleDegrees);

	m_firing.play();
}


