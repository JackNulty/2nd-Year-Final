#include "Hardpoint.h"

Hardpoint::Hardpoint()
{
	init();
}

void Hardpoint::update()
{
	if (defendTimer.isRunning())
	{
		hardpointBounds.setFillColor(sf::Color(0, 0, 255, 100));//for testing
	}
	if (defendTimer.isExpired() && defenceBegan == true && defenceWon == false)
	{
		hardpointBounds.setFillColor(sf::Color(255, 0, 0, 100));
		defenceWon = true;
		m_sfx.play();
	}
	if (defenceWon == true)
	{
		hardpointBounds.setFillColor(sf::Color(0, 255, 255, 100));//for testing
	}

	frameTimer++;
	if (frameTimer >= 15)//used to animate flag
	{
		changeFrame = true;
	}

	if (changeFrame == true)
	{
		m_flagSprite.setTextureRect(sf::IntRect((16 * currentFrame),0, 16, 16));//cycle spritesheet
		changeFrame = false;
		frameTimer = 0;
		currentFrame++;
		if (currentFrame == 3)
		{
			currentFrame = 0;
		}
	}

	int num = defendTimer.getRemainingTime().asSeconds();
	if (defendTimer.isRunning())
	{
		m_timeBarProgress.setTextureRect(sf::IntRect(0, 0, (1 * defendTimer.getRemainingTime().asSeconds()) + 2, 6));//display time left as a progress bar
	}
}

void Hardpoint::init()
{
	hardpointBounds.setSize(sf::Vector2f(384, 240));
	hardpointBounds.setFillColor(sf::Color(0, 255, 0, 100));
	//hardpointBounds.setPosition(64, 64);
	if (!m_flagTexture.loadFromFile("ASSETS/Backgrounds/Animated/Flag/SpriteSheet16x16.png"))
	{
		std::cout << "error loading flag\n";
	}
	m_flagSprite.setTexture(m_flagTexture);
	m_flagSprite.setScale(SCALE, SCALE);
	m_flagSprite.setOrigin(8, 16);
	m_flagSprite.setTextureRect(sf::IntRect(0, 0, 16, 16));

	if (!m_timeBarBackTex.loadFromFile("ASSETS/HUD/TimeBarUnder.png"))
	{
		std::cout << "time bar under failed to load\n";
	}
	m_timeBarBack.setTexture(m_timeBarBackTex);
	m_timeBarBack.setOrigin(32, 3);
	m_timeBarBack.setScale(SCALE, SCALE);
	

	if (!m_timeBarProgTex.loadFromFile("ASSETS/HUD/TimeBarProgress.png"))
	{
		std::cout << "time bar under failed to load\n";
	}
	m_timeBarProgress.setTexture(m_timeBarProgTex);
	m_timeBarProgress.setOrigin(32, 3);
	m_timeBarProgress.setScale(SCALE, SCALE);
	
	if(!m_completed.loadFromFile("ASSETS/Sounds/Game/Success3.wav"))
	{
		std::cout << "error loading sucess sound\n";
	}
	m_sfx.setBuffer(m_completed);
}

void Hardpoint::draw(sf::RenderWindow& window)
{
	//window.draw(hardpointBounds);
	window.draw(m_flagSprite);

	if (defendTimer.isRunning())//show progress bar if player is in zone
	{
		window.draw(m_timeBarBack);
		window.draw(m_timeBarProgress);
	}
}

sf::RectangleShape Hardpoint::getSprite()
{
	return hardpointBounds;
}

void Hardpoint::beginTimer()
{
	if (defenceBegan == false && defenceWon == false)//if player is in zone AND hardpoint hasnt been completed
	{
		if (defendTimer.isExpired())
		{
			defenceBegan = true;
			defendTimer.restart(sf::seconds(30));//start the countdown
		}
	}
}

void Hardpoint::placeHardpoint(sf::Vector2f t_position)
{
	hardpointBounds.setPosition(t_position);
	m_flagSprite.setPosition(t_position.x + 192, t_position.y + 130);

	m_timeBarBack.setPosition(t_position.x + 240, t_position.y + 60);
	m_timeBarProgress.setPosition(t_position.x + 240, t_position.y + 60);
}

void Hardpoint::abandonedHardpoint()
{
	if (defenceBegan == true && defenceWon == false)//if defence was started but not completed
	{
		defenceBegan = false;//reset hardpoint
		defendTimer.restart(sf::seconds(0.01));
		hardpointBounds.setFillColor(sf::Color(0, 255, 0, 100));
	}
}

sf::Vector2f Hardpoint::getCenter()
{
	return m_flagSprite.getPosition();
}
