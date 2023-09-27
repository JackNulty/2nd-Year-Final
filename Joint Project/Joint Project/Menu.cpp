#include "Menu.h"

Menu::Menu()
{
	init();
}

void Menu::init()
{
	if (!m_compass.loadFromFile("ASSETS/HUD/DIALOG/compass.png"))
	{
		std::cout << "error loading compass tutorial\n";
	}
	if (!m_walk.loadFromFile("ASSETS/HUD/DIALOG/walkTutorial.png"))
	{
		std::cout << "error loading walk tutorial\n";
	}
	if (!m_menu.loadFromFile("ASSETS/HUD/DIALOG/menuTutorial.png"))
	{
		std::cout << "error loading menu tutorial\n";
	}
	//if (!m_controller1.loadFromFile("ASSETS/HUD/DIALOG/controllerTutorial1.png"))
	//{
	//	std::cout << "error loading controller 1 tutorial\n";
	//}
	//if (!m_controller2.loadFromFile("ASSETS/HUD/DIALOG/controllerTutorial2.png"))
	//{
	//	std::cout << "error loading controller 2 tutorial\n";
	//}
	if (!m_sprint.loadFromFile("ASSETS/HUD/DIALOG/sprint.png"))
	{
		std::cout << "error loading controller 2 tutorial\n";
	}
	m_tutorialCard.setTexture(m_menu);
	m_tutorialCard.setScale(2, 2);
	m_tutorialCard.setPosition(0, 650);

	if (!m_menuTexture.loadFromFile("ASSETS/HUD/Dialog/START.png"))
	{
		std::cout << "error loading menu button\n";
	}
	m_menuButton.setTexture(m_menuTexture);
	m_menuButton.setOrigin(32, 10);
	m_menuButton.setScale(SCALE, SCALE);
	m_menuButton.setPosition(500, 300);

	if (!m_characterTexture.loadFromFile("ASSETS/HUD/Dialog/CHARACTER.png"))
	{
		std::cout << "error loading character button\n";
	}
	m_characterButton.setTexture(m_characterTexture);
	m_characterButton.setOrigin(34, 10);
	m_characterButton.setScale(SCALE, SCALE);
	m_characterButton.setPosition(500, 400);

	if (!m_quitTexture.loadFromFile("ASSETS/HUD/Dialog/QUIT.png"))
	{
		std::cout << "error loading quit button\n";
	}
	m_quitButton.setTexture(m_quitTexture);
	m_quitButton.setOrigin(32, 10);
	m_quitButton.setScale(SCALE, SCALE);
	m_quitButton.setPosition(500, 500);


	m_greyOut.setSize(sf::Vector2f(1200, 800));
	m_greyOut.setFillColor(sf::Color(0, 0, 0, 200));


	if (!m_blueNinjaTex.loadFromFile("ASSETS/HUD/BlueNinjaBox.png"))
	{
		std::cout << "error loading blueNinjaBox\n";
	}
	if (!m_redNinjaTex.loadFromFile("ASSETS/HUD/RedNinjaBox.png"))
	{
		std::cout << "error loading blueNinjaBox\n";
	}
	if (!m_greyNinjaTex.loadFromFile("ASSETS/HUD/GreyNinjaBox.png"))
	{
		std::cout << "error loading blueNinjaBox\n";
	}
	if (!m_knightTex.loadFromFile("ASSETS/HUD/KnightBox.png"))
	{
		std::cout << "error loading blueNinjaBox\n";
	}
	if (!m_frogTex.loadFromFile("ASSETS/HUD/FrogBox.png"))
	{
		std::cout << "error loading blueNinjaBox\n";
	}
	if (!m_cavemanTex.loadFromFile("ASSETS/HUD/CavemanBox.png"))
	{
		std::cout << "error loading blueNinjaBox\n";
	}
	m_blueNinja.setTexture(m_blueNinjaTex);
	m_redNinja.setTexture(m_redNinjaTex);
	m_greyNinja.setTexture(m_greyNinjaTex);
	m_caveman.setTexture(m_cavemanTex);
	m_frog.setTexture(m_frogTex);
	m_knight.setTexture(m_knightTex);

	m_blueNinja.setOrigin(24,24);
	m_redNinja.setOrigin(24, 24);
	m_greyNinja.setOrigin(24, 24);
	m_caveman.setOrigin(24, 24);
	m_frog.setOrigin(24, 24);
	m_knight.setOrigin(24, 24);

	m_blueNinja.setScale(SCALE, SCALE);
	m_redNinja.setScale(SCALE, SCALE);
	m_greyNinja.setScale(SCALE, SCALE);
	m_caveman.setScale(SCALE, SCALE);
	m_frog.setScale(SCALE, SCALE);
	m_knight.setScale(SCALE, SCALE);

	m_blueNinja.setPosition(400, 400);
	m_redNinja.setPosition(400, 200);
	m_greyNinja.setPosition(400, 600);
	m_caveman.setPosition(600, 400);
	m_frog.setPosition(600, 200);
	m_knight.setPosition(600, 600);

	mousePosCircle.setRadius(2.0f);
	mousePosCircle.setFillColor(sf::Color::Red);
}

void Menu::update()
{
	if (tutorialTimer.isExpired())
	{
		tutorialCounter++;
		if (tutorialCounter > 3)
		{
			tutorialCounter = 0;
		}
		tutorialTimer.restart(sf::seconds(3));
	}
	if (tutorialCounter == 0)
	{
		m_tutorialCard.setTexture(m_menu);
	}
	if (tutorialCounter == 1)
	{
		m_tutorialCard.setTexture(m_walk);
	}
	if (tutorialCounter == 2)
	{
		m_tutorialCard.setTexture(m_compass);
	}
	//if (tutorialCounter == 3)
	//{
	//	//m_tutorialCard.setTexture(m_controller1);
	//}
	//if (tutorialCounter == 4)
	//{
	//	//m_tutorialCard.setTexture(m_controller2);
	//}
	if (tutorialCounter == 3)
	{
		m_tutorialCard.setTexture(m_sprint);
	}
	// set the little circle to the mouse pos
	mousePosCircle.setPosition(m_accurateMousePos);

		if (m_characterOpen == false)//if not in character selection
		{
			if (m_swapCooldown.isExpired())//slow down rate at which buttons can be activated
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
				{
					m_buttonSelection++;
					if (m_buttonSelection > 2)
					{
						m_buttonSelection = 0;
					}
					m_swapCooldown.restart(sf::seconds(0.2));
				}

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
				{
					m_buttonSelection--;
					if (m_buttonSelection < 0)
					{
						m_buttonSelection = 2;
					}
					m_swapCooldown.restart(sf::seconds(0.2));
				}


				if (m_buttonSelection == 0)//if on menu button
				{
					m_menuButton.setScale(SCALE + 1, SCALE + 1);
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
					{
						m_menuOpen = false;//close menu
					}
					if ((mousePosCircle.getGlobalBounds().intersects(m_menuButton.getGlobalBounds()) && sf::Mouse::isButtonPressed(sf::Mouse::Left)))
					{
						m_menuOpen = false;
					}
				}
				else m_menuButton.setScale(SCALE, SCALE);

				if (m_buttonSelection == 1)//if on character selection
				{
					m_characterButton.setScale(SCALE + 1, SCALE + 1);
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
					{
						m_characterOpen = true;//open character selection menu
						m_swapCooldown.restart(sf::seconds(0.2));
					}
					if ((mousePosCircle.getGlobalBounds().intersects(m_characterButton.getGlobalBounds()) && sf::Mouse::isButtonPressed(sf::Mouse::Left)))
					{
						m_characterOpen = true;
						m_swapCooldown.restart(sf::seconds(0.2));
					}
				}
				else m_characterButton.setScale(SCALE, SCALE);

				if (m_buttonSelection == 2)//if on quit
				{
					m_quitButton.setScale(SCALE + 1, SCALE + 1);
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
					{
						m_close = true;//allow window to close
					}
					if ((mousePosCircle.getGlobalBounds().intersects(m_quitButton.getGlobalBounds()) && sf::Mouse::isButtonPressed(sf::Mouse::Left)))
					{
						m_close = true;
					}
				}
				else m_quitButton.setScale(SCALE, SCALE);
			}
		}

		if (m_characterOpen == false)//if on character selection screen
		{
			if (mousePosCircle.getGlobalBounds().intersects(m_menuButton.getGlobalBounds()))
			{
				m_buttonSelection = 0;
			}
			if (mousePosCircle.getGlobalBounds().intersects(m_characterButton.getGlobalBounds()))
			{
				m_buttonSelection = 1;
			}
			if (mousePosCircle.getGlobalBounds().intersects(m_quitButton.getGlobalBounds()))
			{
				m_buttonSelection = 2;
			}

		}

		if (m_characterOpen == true)//if on character selection screen
		{
			if (m_swapCooldown.isExpired())
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || mousePosCircle.getGlobalBounds().intersects(m_menuButton.getGlobalBounds()))
				{
					m_characterNum++;
					if (m_characterNum > 5)
					{
						m_characterNum = 0;
					}
					m_swapCooldown.restart(sf::seconds(0.2));
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || mousePosCircle.getGlobalBounds().intersects(m_menuButton.getGlobalBounds()))
				{
					m_characterNum--;
					if (m_characterNum < 0)
					{
						m_characterNum = 5;
					}
					m_swapCooldown.restart(sf::seconds(0.2));
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
				{
					m_characterOpen = false;//go back to menu screen
					m_swapCooldown.restart(sf::seconds(0.2));
				}
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					m_characterOpen = false;
					m_swapCooldown.restart(sf::seconds(0.2));
				}
			}
		}

		if (m_characterOpen == true)//if on character selection screen
		{
			if (mousePosCircle.getGlobalBounds().intersects(m_redNinja.getGlobalBounds()))
			{
				m_characterNum = 0;
			}
			if (mousePosCircle.getGlobalBounds().intersects(m_blueNinja.getGlobalBounds()))
			{
				m_characterNum = 1;
			}
			if (mousePosCircle.getGlobalBounds().intersects(m_greyNinja.getGlobalBounds()))
			{
				m_characterNum = 2;
			}
			if (mousePosCircle.getGlobalBounds().intersects(m_frog.getGlobalBounds()))
			{
				m_characterNum = 3;
			}
			if (mousePosCircle.getGlobalBounds().intersects(m_caveman.getGlobalBounds()))
			{
				m_characterNum = 4;
			}
			if (mousePosCircle.getGlobalBounds().intersects(m_knight.getGlobalBounds()))
			{
				m_characterNum = 5;
			}
		}


		if (m_characterNum == 0)
		{
			m_redNinja.setScale(SCALE + 1, SCALE + 1);
		}
		else m_redNinja.setScale(SCALE, SCALE);

		if (m_characterNum == 1)
		{
			m_blueNinja.setScale(SCALE + 1, SCALE + 1);
		}
		else m_blueNinja.setScale(SCALE, SCALE);

		if (m_characterNum == 2)
		{
			m_greyNinja.setScale(SCALE + 1, SCALE + 1);
		}
		else m_greyNinja.setScale(SCALE, SCALE);

		if (m_characterNum == 3)
		{
			m_frog.setScale(SCALE + 1, SCALE + 1);
		}
		else m_frog.setScale(SCALE, SCALE);

		if (m_characterNum == 4)
		{
			m_caveman.setScale(SCALE + 1, SCALE + 1);
		}
		else m_caveman.setScale(SCALE, SCALE);

		if (m_characterNum == 5)
		{
			m_knight.setScale(SCALE + 1, SCALE + 1);
		}
		else m_knight.setScale(SCALE, SCALE);
}


void Menu::draw(sf::RenderWindow& window)
{
	if (m_menuOpen == true)//only render while menu is open
	{
		window.draw(m_greyOut);//darken screen
		window.draw(m_tutorialCard);
		if (m_characterOpen == false)//draw if character selection is NOT open
		{
			window.draw(m_menuButton);
			window.draw(m_characterButton);
			window.draw(m_quitButton);
			if (m_close == true)//close the window if quit was called
			{
				window.close();
			}
		}
		if (m_characterOpen == true)// draw if character selection is open
		{
			window.draw(m_redNinja);
			window.draw(m_blueNinja);
			window.draw(m_greyNinja);
			window.draw(m_frog);
			window.draw(m_knight);
			window.draw(m_caveman);
		}
	}
	m_mousePos = sf::Mouse::getPosition(window);
	m_accurateMousePos = window.mapPixelToCoords(m_mousePos);
	//window.draw(mousePosCircle);
}