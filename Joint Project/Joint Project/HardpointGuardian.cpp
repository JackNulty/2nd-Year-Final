#include "HardpointGuardian.h"

HardpointGuardian::HardpointGuardian()
{
	init();
}

void HardpointGuardian::update(sf::Vector2f t_playerPos)
{
	sf::Vector2f m_direction = t_playerPos - guardianSprite.getPosition();
	float m_distance = std::sqrt(m_direction.x * m_direction.x + m_direction.y * m_direction.y);
	m_direction /= m_distance;
	sf::Vector2f m_velocity = m_direction * 2.0f;


	guardianSprite.move(m_velocity);
	animate();
	if (particlesTimer.isExpired())// remove particles
	{
		deadPos = sf::Vector2f(-2000, -2000);
	}
	myParticles.update(deadPos);
	
}

void HardpointGuardian::init()
{
	if (!guardianTexture.loadFromFile("ASSETS/Actor/Monsters/Skull/Spritesheet.png"))
	{
		"error loading guardian texture\n";
	}
	guardianSprite.setTexture(guardianTexture);
	guardianSprite.setScale(SCALE, SCALE);
	guardianSprite.setOrigin(8, 8);

	m_animationState = Walking;
	m_direction = Down;

	//particlesTimer.reset(sf::seconds(3));
}

void HardpointGuardian::draw(sf::RenderWindow& window)
{
	myParticles.render(window);
	window.draw(guardianSprite);
	

	if (health <= 25)
	{
		deadPos = guardianSprite.getPosition();
		particlesTimer.restart(sf::seconds(0.2));
	}
		
}

void HardpointGuardian::placeEnemy(sf::Vector2f t_placeHere)
{
	//deadPos = guardianSprite.getPosition();
	guardianSprite.setPosition(t_placeHere);
}

void HardpointGuardian::animate()
{
	frameTimer++; // timer for walking animation
	if (frameTimer >= 7)
	{
		changeFrame = true;
	}
	if (m_animationState == Idle)
	{
		if (m_direction == Up)
			guardianSprite.setTextureRect(sf::IntRect(16, 0, 16, 16));
		else if (m_direction == Down)
			guardianSprite.setTextureRect(sf::IntRect(0, 0, 16, 16));
		else if (m_direction == Left)
			guardianSprite.setTextureRect(sf::IntRect(32, 0, 16, 16));
		else if (m_direction == Right)
			guardianSprite.setTextureRect(sf::IntRect(48, 0, 16, 16));
	} // if idle then stay still based on last direction 
	else if (m_animationState == Walking)
	{
		//m_direction = Down;
		if (m_direction == Up)
		{
			if (changeFrame == true)
			{
				guardianSprite.setTextureRect(sf::IntRect(16, (16 * currentFrame), 16, 16));
				changeFrame = false;
				frameTimer = 0;
				currentFrame++;
				if (currentFrame > 3)
				{
					currentFrame = 0;
				}
			}
		}
		else if (m_direction == Down)
		{
			if (changeFrame == true)
			{
				guardianSprite.setTextureRect(sf::IntRect(0, (16 * currentFrame), 16, 16));
				changeFrame = false;
				frameTimer = 0;
				currentFrame++;
				if (currentFrame > 3)
				{
					currentFrame = 0;
				}
			}
		}
		else if (m_direction == Left)
		{
			if (changeFrame == true)
			{
				guardianSprite.setTextureRect(sf::IntRect(32, (16 * currentFrame), 16, 16));
				changeFrame = false;
				frameTimer = 0;
				currentFrame++;
				if (currentFrame > 3)
				{
					currentFrame = 0;
				}
			}

		}
		else if (m_direction == Right)
		{
			if (changeFrame == true)
			{
				guardianSprite.setTextureRect(sf::IntRect(48, (16 * currentFrame), 16, 16));
				changeFrame = false;
				frameTimer = 0;
				currentFrame++;
				if (currentFrame > 3)
				{
					currentFrame = 0;
				}
			}
		}
	}
}

sf::Sprite HardpointGuardian::getSprite()
{
	return guardianSprite;
}
