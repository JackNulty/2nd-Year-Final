#include "Globals.h"

class HUD {
public:
	HUD();

	void init();
	void update();
	void draw(sf::RenderWindow& window);
	void handleHearts(int t_hitsTaken);
	void handleCompass(sf::Vector2f t_nearestObjective,sf::Vector2f t_playerPos);
	void dashCooldownIcon();

	bool gameOver = false;
	bool gameWon = false;
private:
	sf::Sprite m_heartSprite[MAX_HEARTS];
	sf::Texture m_heartTexture;

	sf::Sprite m_compassBackSp;
	sf::Texture m_compassBackTex;

	sf::Sprite m_compassNeedleSp;
	sf::Texture m_compassNeedleTex;

	sf::Sprite m_dashIconSprite;
	sf::Texture m_dashIconTexture;

	sf::RectangleShape m_fadeOutScreen;
	sf::Sprite m_endMessage;
	sf::Texture m_winMessage;
	sf::Texture m_loseMessage;

	int fadeAmount = 0;
};