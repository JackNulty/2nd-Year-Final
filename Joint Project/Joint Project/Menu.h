#include "Globals.h"

class Menu {
public:
	Menu();

	void init();
	void update();
	void draw(sf::RenderWindow& window);

	int m_buttonSelection = 0;
	bool m_menuOpen = true;

	int m_characterNum = 0;
private:

	//  small circle to follow mouse pos 
	sf::CircleShape mousePosCircle;
	sf::Vector2i m_mousePos;
	sf::Vector2f m_accurateMousePos;

	sf::Sprite m_menuButton;
	sf::Texture m_menuTexture;

	sf::Sprite m_quitButton;
	sf::Texture m_quitTexture;

	sf::Sprite m_characterButton;
	sf::Texture m_characterTexture;

	sf::RectangleShape m_greyOut;

	thor::Timer m_swapCooldown;

	
	bool m_characterOpen = false;

	bool m_close = false;

	sf::Sprite m_redNinja;
	sf::Texture m_redNinjaTex;

	sf::Sprite m_frog;
	sf::Texture m_frogTex;

	sf::Sprite m_greyNinja;
	sf::Texture m_greyNinjaTex;

	sf::Sprite m_blueNinja;
	sf::Texture m_blueNinjaTex;

	sf::Sprite m_knight;
	sf::Texture m_knightTex;

	sf::Sprite m_caveman;
	sf::Texture m_cavemanTex;

	sf::Sprite m_tutorialCard;
	sf::Texture m_walk;
	sf::Texture m_menu;
	//sf::Texture m_controller1;
	//sf::Texture m_controller2;
	sf::Texture m_compass;
	sf::Texture m_sprint;

	int tutorialCounter = 0;
	thor::Timer tutorialTimer;
};