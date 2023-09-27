#pragma once
#include "Globals.h"
#include "Player.h"
#include <Thor/Time.hpp>
#include "Hardpoint.h"
#include "HeadsUpDisplay.h"
#include "Enemy.h"
#include "BonePerson.h"
#include "Menu.h"
#include "Grid.h"
#include "HardpointGuardian.h"

class Game {
public:
	Game();

	void run();
	void init();
	void render();
	void update(double dt);
	void collisons();

	// main window
	sf::RenderWindow m_window;
	Player myPlayer;
	BonePerson bonePerson;
	Enemy racoonRobber[5];
	Hardpoint myHardpoint[MAX_HARDPOINTS];
	HUD myHUD;
	Menu myMenu;
	Grid myGrid;
	HardpointGuardian myGuardian[MAX_GUARDIANS];
private:
	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite;

	//collions
	sf::RectangleShape collisionBox[ROWS][COLS];

	sf::View fixed;

	sf::View standard;

	sf::Vector2f m_windowViewPos = { 0,0 };

	thor::Timer m_hitCooldown;

	sf::SoundBuffer m_damageSound;
	sf::Sound m_sfxDamage;

	sf::Music m_mainMusic;
	sf::Music m_goodEnding;
	sf::Music m_badEnding;

	bool playerInHardpoint = false;

	bool gameCompleted = false;

	bool m_toggleOnce = false;
};
