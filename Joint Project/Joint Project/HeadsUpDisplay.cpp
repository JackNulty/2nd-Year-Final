#include "HeadsUpDisplay.h"

HUD::HUD()
{
	init();
}

void HUD::init()
{
	if (!m_heartTexture.loadFromFile("ASSETS/HUD/Heart.png"))
	{
		std::cout << "error loading hearts\n";
	}
	for (int i = 0; i < MAX_HEARTS; i++)
	{
		m_heartSprite[i].setTexture(m_heartTexture);
		m_heartSprite[i].setPosition((48 * (i + 1)) - 32, 8);//place the sprites in a row
		m_heartSprite[i].setScale(SCALE, SCALE);
		m_heartSprite[i].setTextureRect(sf::IntRect(0, 0, 16, 16));
	}
	if (!m_compassBackTex.loadFromFile("ASSETS/HUD/CompassBG.png"))
	{
		std::cout << "error loading compass background\n";
	}
	if (!m_compassNeedleTex.loadFromFile("ASSETS/HUD/CompassNeedle.png"))
	{
		std::cout << "error loading compass needle\n";
	}
	m_compassBackSp.setTexture(m_compassBackTex);
	m_compassNeedleSp.setTexture(m_compassNeedleTex);
	m_compassBackSp.setOrigin(0,0);
	m_compassNeedleSp.setOrigin(8, 8);

	m_compassBackSp.setScale(5,5);
	m_compassNeedleSp.setScale(5, 5);

	m_compassBackSp.setPosition(935, 680);
	m_compassNeedleSp.setPosition(976, 720);

	if (!m_winMessage.loadFromFile("ASSETS/HUD/Dialog/WIN.png"))
	{
		std::cout << "error loading win message\n";
	}
	if (!m_loseMessage.loadFromFile("ASSETS/HUD/Dialog/LOSE.png"))
	{
		std::cout << "error loading lose message\n";
	}
	m_fadeOutScreen.setSize(sf::Vector2f(1200, 800));
	m_fadeOutScreen.setFillColor(sf::Color(0, 0, 0, 0));
	m_endMessage.setScale(2, 2);
	m_endMessage.setPosition(200, 300);
	m_endMessage.setColor(sf::Color(0, 0, 0, 0));
}

void HUD::update()
{
	//m_compassNeedleSp.rotate(4);//testing
}

void HUD::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < MAX_HEARTS; i++)
	{
		window.draw(m_heartSprite[i]);
	}
	window.draw(m_compassBackSp);
	window.draw(m_compassNeedleSp);
	if (gameOver == true)
	{
		window.draw(m_fadeOutScreen);
		fadeAmount++;
		if (fadeAmount > 255)
		{
			fadeAmount = 255;
		}
		m_fadeOutScreen.setFillColor(sf::Color(0, 0, 0, fadeAmount));//fade from no colour to full colour
		m_endMessage.setColor(sf::Color(255,255,255, fadeAmount));
		if (gameWon == true)
		{
			m_endMessage.setTexture(m_winMessage);
		}
		else m_endMessage.setTexture(m_loseMessage);
		window.draw(m_endMessage);
	}
}

void HUD::handleHearts(int t_hitsTaken)
{
	if (t_hitsTaken <= 4)//if hits taken is less than or equal to 4
	{
		m_heartSprite[2].setTextureRect(sf::IntRect(16*t_hitsTaken, 0, 16, 16));//cycle through spritesheet
		m_heartSprite[1].setTextureRect(sf::IntRect(0, 0, 16, 16));
		m_heartSprite[0].setTextureRect(sf::IntRect(0, 0, 16, 16));
	}
	if (t_hitsTaken <= 8 && t_hitsTaken > 4)
	{
		m_heartSprite[1].setTextureRect(sf::IntRect(16 * (t_hitsTaken-4), 0, 16, 16));
		m_heartSprite[0].setTextureRect(sf::IntRect(0, 0, 16, 16));
	}
	if (t_hitsTaken <= 12 && t_hitsTaken > 8)
	{
		m_heartSprite[0].setTextureRect(sf::IntRect(16 * (t_hitsTaken-8), 0, 16, 16));
	}
}

void HUD::handleCompass(sf::Vector2f t_nearestObjective, sf::Vector2f t_playerPos)
{
	sf::Vector2f m_direction = t_nearestObjective - t_playerPos;//get direction

	float m_distance = std::sqrt(m_direction.x * m_direction.x + m_direction.y * m_direction.y);//get distance
	m_direction /= m_distance;
	float angleRadians = std::atan2(m_direction.y, m_direction.x);
	float angleDegrees = angleRadians * 180 / thor::Pi;

	m_compassNeedleSp.setRotation(angleDegrees+90);//set to face closest objective
}

void HUD::dashCooldownIcon()
{
}
