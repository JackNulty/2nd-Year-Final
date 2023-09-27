#include "Globals.h"

class Hardpoint {
public:
	Hardpoint();
	void update();
	void init();
	void draw(sf::RenderWindow& window);
	sf::RectangleShape getSprite();
	void beginTimer();
	void placeHardpoint(sf::Vector2f t_position);
	void abandonedHardpoint();
	thor::Timer defendTimer;

	sf::Vector2f getCenter();

	bool defenceWon = false;

	bool allowHealth = true;
private:
	sf::RectangleShape hardpointBounds;

	sf::Sprite m_flagSprite;
	sf::Texture m_flagTexture;

	sf::Sprite m_timeBarBack;
	sf::Texture m_timeBarBackTex;
	sf::Sprite m_timeBarProgress;
	sf::Texture m_timeBarProgTex;

	int frameTimer = 0;
	int currentFrame = 0;
	bool changeFrame = false;

	bool defenceBegan = false;

	sf::SoundBuffer m_completed;
	sf::Sound m_sfx;
};