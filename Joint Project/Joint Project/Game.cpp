#include "Game.h"


Game::Game():
	m_window(sf::VideoMode(1024, 768, 32), "Joint Project", sf::Style::Default)
{
    init();
}

void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	sf::Time timePerFrame = sf::seconds(1.0f / 60); // 60 fps
	while (m_window.isOpen())
	{
        sf::Event event;
        while (m_window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                m_window.close();
        }

        timeSinceLastUpdate += clock.restart();
        update(timePerFrame.asMilliseconds());

        if (timeSinceLastUpdate > timePerFrame)
        {
            timeSinceLastUpdate = sf::Time::Zero;
        }
        render();
	}
}

void Game::init()
{
    srand(time(NULL));

    int colPlayer = myPlayer.getPos().y / 48;
    int rowPlayer = myPlayer.getPos().x / 48;
    int playerCell = colPlayer * rowPlayer;

    int colEnemy = bonePerson.getPos().y / 48;
    int rowEnemy = bonePerson.getPos().x / 48;
    int enemyCell = colEnemy * rowEnemy;

    myGrid.clearGrid();

    std::vector<int> path = myGrid.bfs(enemyCell, playerCell);

    int nextCell = path.front();
    sf::Vector2f nextCoord;
    nextCoord.y = (nextCell % ROWS) * 48;
    nextCoord.x = (nextCell % COLS) * 48;
    std::cout<< "   " << nextCoord.x << "   " << nextCoord.y << "\n";


    std::cout << "PLayer cell: " << playerCell << "\n";

    m_window.setVerticalSyncEnabled(true);
    m_window.setFramerateLimit(60);

    fixed = m_window.getView(); // The 'fixed' view will never change

    standard = fixed; // The 'standard' view will be the one that gets always displayed



    myPlayer.init();
    if (!backgroundTexture.loadFromFile("ASSETS/Backgrounds/background.png"))
    {
        std::cout << "Background failed to load \n";
    }
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setScale(SCALE, SCALE);
    backgroundSprite.setPosition(0, 0);

    myHardpoint[0].placeHardpoint(sf::Vector2f(288, 288));
    myHardpoint[1].placeHardpoint(sf::Vector2f(128*SCALE, 720*SCALE));
    myHardpoint[2].placeHardpoint(sf::Vector2f(560*SCALE, 64*SCALE));
    myHardpoint[3].placeHardpoint(sf::Vector2f(992*SCALE, 112*SCALE));
    myHardpoint[4].placeHardpoint(sf::Vector2f(896*SCALE, 752*SCALE));


    racoonRobber[1].setPos(sf::Vector2f(32*SCALE, 720*SCALE));
    racoonRobber[2].setPos(sf::Vector2f(560*SCALE,32*SCALE));
    racoonRobber[3].setPos(sf::Vector2f(992*SCALE,60*SCALE));
    racoonRobber[4].setPos(sf::Vector2f(3000,2200));

    for (int i = 0; i < MAX_GUARDIANS; i++)
    {
        myGuardian[i].init();
    }
    for (int cols = 0; cols < COLS; cols++)
    {
        for (int rows = 0; rows < ROWS; rows++)//setup entire grid collisions
        {
            if (GRID[rows][cols] == 0)//if box should be empty
            {
                collisionBox[rows][cols].setSize(sf::Vector2f(CELL_SIZE, CELL_SIZE));
                collisionBox[rows][cols].setPosition(cols * 48, rows * 48);
                collisionBox[rows][cols].setFillColor(sf::Color(0,255,0,100));
            }
            if (GRID[rows][cols] ==2)//if box should have collisions
            {
                collisionBox[rows][cols].setSize(sf::Vector2f(CELL_SIZE, CELL_SIZE));
                collisionBox[rows][cols].setPosition(cols * 48, rows * 48);
                collisionBox[rows][cols].setFillColor(sf::Color(255,0,0,100));
            }
        }
    }
    if (!m_damageSound.loadFromFile("ASSETS/Sounds/Game/Explosion.wav"))
    {
        std::cout << "error loading explosion sound\n";
    }
    m_sfxDamage.setBuffer(m_damageSound);
    if (!m_mainMusic.openFromFile("ASSETS/Musics/Village.ogg"))
    {
        std::cout << "music failed to load\n";
    }
    m_mainMusic.setVolume(40);
    m_mainMusic.play();

    if (!m_goodEnding.openFromFile("ASSETS/Musics/22 - Dream.ogg"))
    {
        std::cout << "good ending music failed to load\n";
    }
    m_goodEnding.setVolume(80);
    if (!m_badEnding.openFromFile("ASSETS/Musics/14 - Curse.ogg"))
    {
        std::cout << "bad ending music failed to load\n";
    }
    m_badEnding.setVolume(40);
}

void Game::render()
{
    sf::View playerView(sf::FloatRect(0.f, 0.f, static_cast<float>(m_window.getSize().x), static_cast<float>(m_window.getSize().y)));//create players camera
    playerView.setViewport(sf::FloatRect(0.f, 0.f, 1, 1));//set view size
    m_windowViewPos = myPlayer.getPos();//place on player
    if (m_windowViewPos.x < 512)//keep camera on map
    {
        m_windowViewPos.x = 512;
    }
    if (m_windowViewPos.x > (1200*SCALE) - 512)
    {
        m_windowViewPos.x = (1200 * SCALE) - 512;
    }
    if (m_windowViewPos.y < 384)
    {
        m_windowViewPos.y = 384;
    }
    if (m_windowViewPos.y > (896*SCALE)-384)
    {
        m_windowViewPos.y = (896 * SCALE) - 384;
    }
    playerView.setCenter(m_windowViewPos);//place camera
    m_window.clear();

    m_window.setView(playerView);

    m_window.draw(backgroundSprite);
    
    if (gameCompleted == false)
    {
        if (playerInHardpoint == true)
        {
            for (int i = 0; i < MAX_GUARDIANS; i++)
            {
                myGuardian[i].draw(m_window);
            }
        }
        bonePerson.render(m_window);
        for (int i = 0; i < 5; i++)
        {
            racoonRobber[i].render(m_window);
        }
    }
   
    for (int i = 0; i < MAX_HARDPOINTS; i++)
    {
        myHardpoint[i].draw(m_window);
    }
    myPlayer.render(m_window);
    //for (int cols = 0; cols < COLS; cols++)
    //{
    //    for (int rows = 0; rows < ROWS; rows++)
    //    {
    //        //m_window.draw(collisionBox[rows][cols]);
    //    }
    //}
    ////m_window.draw(collisionBox[1][0]);

    m_window.setView(fixed); // Draw 'GUI' elements with fixed positions

    myHUD.draw(m_window);
    myMenu.draw(m_window);

    m_window.display();
}

void Game::update(double dt)
{
    float distance[5];
    int closest = 0;
    if (gameCompleted == false)
    {
        //if every hardpoint has been completed
        if (myHardpoint[0].defenceWon == true && myHardpoint[1].defenceWon == true && myHardpoint[2].defenceWon == true && myHardpoint[3].defenceWon == true && myHardpoint[4].defenceWon == true)
        {
            myHUD.gameWon = true;
            myHUD.gameOver = true;
            gameCompleted = true;
        }
        if (myPlayer.m_hitsTaken >= 12)//if player has taken max damage
        {
            myHUD.gameWon = false;
            myHUD.gameOver = true;
            gameCompleted = true;
        }

        for (int i = 0; i < MAX_HARDPOINTS; i++)
        {
            myHardpoint[i].update();
            distance[i] = std::sqrt(std::pow(myHardpoint[i].getCenter().x - myPlayer.getPos().x, 2) + std::pow(myHardpoint[i].getCenter().y - myPlayer.getPos().y, 2));//get distance from player to all hardpoints
            if (myHardpoint[i].defenceWon == true)// if hardpoint is completed, set distance to value that wont be falsely flagged as viable
            {
                distance[i] = 10000;
                if (myHardpoint[i].allowHealth == true)//if player completes hardpoint heal once
                {
                    myHardpoint[i].allowHealth = false;
                    myPlayer.m_hitsTaken -= 4;
                    if (myPlayer.m_hitsTaken < 0)
                    {
                        myPlayer.m_hitsTaken = 0;
                    }
                }
            }
            if (i > 0)
            {
                if (distance[i] < distance[closest])//if current loop hardpoint distance is closer than previous closest
                {
                    closest = i;//set closest to that hardpoint
                }
            }
        }
        if (myMenu.m_menuOpen == false)
        {
            myHUD.handleCompass(myHardpoint[closest].getCenter(), myPlayer.getPos());//send closest hardpoint and player pos
            myHUD.handleHearts(myPlayer.m_hitsTaken);
            playerInHardpoint = false;
            for (int i = 0; i < MAX_HARDPOINTS; i++)
            {
                if (myHardpoint[i].defendTimer.isRunning())
                {
                    for (int i = 0; i < MAX_GUARDIANS; i++)
                    {
                        myGuardian[i].update(myPlayer.getPos());
                    }

                    playerInHardpoint = true;
                }
            }
            if (playerInHardpoint == false)//if player isnt in hardpoint respawn enemy
            {
                for (int i = 0; i < MAX_GUARDIANS; i++)
                {
                    myGuardian[i].placeEnemy(sf::Vector2f(rand() % 3600, (rand() % 600) + 900));
                }
            }
            myPlayer.update(dt);
            bonePerson.update();
            for (int i = 0; i < 5; i++)
            {
                racoonRobber[i].update(myPlayer.getPos());
            }

            collisons();
            myHUD.update();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))//open menu
            {
                myMenu.m_menuOpen = true;
            }
        }
        if (myMenu.m_menuOpen == true)
        {
            myPlayer.swapCharacter(myMenu.m_characterNum);//change the player to currently selected spritesheet
        }
        myMenu.update();
        bonePerson.dealDamage(myPlayer.passSprite(bonePerson.getSprite()));//deal damage and pass damage amount into function
        if (playerInHardpoint == true)//if player is in hardpoint run enemy functions
        {
            for (int i = 0; i < MAX_GUARDIANS; i++)
            {
                myGuardian[i].health = myGuardian[i].health - myPlayer.passSprite(myGuardian[i].getSprite());
                if (myGuardian[i].health <= 0)
                {
                    myGuardian[i].health = 40;
                    myGuardian[i].placeEnemy(sf::Vector2f(rand() % 3600, (rand() % 600) + 900));
                    m_sfxDamage.play();
                }
            }
        }



        for (int i = 0; i < 5; i++)
        {
            racoonRobber[i].dealDamage(myPlayer.passSprite(racoonRobber[i].getSprite()));
            if (racoonRobber[i].getHealth() <= 0 && racoonRobber[i].raccCooldown.isExpired())
            {
                racoonRobber[i].resetRacoon(i);
                m_sfxDamage.play();
            }
        }
        m_mainMusic.setLoop(true);
    }
    else 
    {
        m_mainMusic.stop();
        if (myHUD.gameWon == true)
        {
            if (m_toggleOnce == false)
            {
                m_toggleOnce = true;
                m_goodEnding.play();
            }            
        }
        if (myHUD.gameWon == false)
        {
            if (m_toggleOnce == false)
            {
                m_toggleOnce = true;
                m_badEnding.play();
            }
        }
    }
}

void Game::collisons()
{
    for (int i = 0; i < MAX_HARDPOINTS; i++)
    {
        if (myPlayer.getSprite().getGlobalBounds().intersects(myHardpoint[i].getSprite().getGlobalBounds()))
        {
            myHardpoint[i].beginTimer();//start the hardpoiint defence
        }
        else myHardpoint[i].abandonedHardpoint();
    }

    if(myPlayer.getSprite().getGlobalBounds().intersects(bonePerson.getSprite().getGlobalBounds()))
    {
        if (m_hitCooldown.isExpired())
        {
            myPlayer.m_hitsTaken++;
            m_hitCooldown.restart(sf::seconds(0.75));
            m_sfxDamage.play();
        }
    }

    for (int i = 0; i < 5; i++)
    {
        if (myPlayer.getSprite().getGlobalBounds().intersects(racoonRobber[i].getSprite().getGlobalBounds()))
        {
            //racoonRobber[i].raccCooldown.restart(sf::seconds(1));
            myPlayer.m_hitsTaken++;
            m_hitCooldown.restart(sf::seconds(0.75));
            racoonRobber[i].resetRacoon(i);
            m_sfxDamage.play();
            myPlayer.bowGone.restart(sf::seconds(3));
        }
    }

    if (playerInHardpoint == true)
    {
        for (int i = 0; i < MAX_GUARDIANS; i++)
        {
            if (myPlayer.getSprite().getGlobalBounds().intersects(myGuardian[i].getSprite().getGlobalBounds()) && playerInHardpoint == true)
            {
                myPlayer.m_hitsTaken += 1;
                m_sfxDamage.play();
                myGuardian[i].placeEnemy(sf::Vector2f(rand() % 3600, (rand() % 600) + 900));
            }
        }
    }
   

    for (int cols = 0; cols < COLS; cols++)
    {
        for (int rows = 0; rows < ROWS; rows++)
        {
            if (myPlayer.getSprite().getGlobalBounds().intersects(collisionBox[rows][cols].getGlobalBounds()) && collisionBox[rows][cols].getFillColor() == sf::Color(255, 0, 0, 100))//please ignore this
            {
                if (myPlayer.m_direction == myPlayer.Up)//prevent player from moving in the current direction if a collision occurs
                {
                    myPlayer.playerPos.y = collisionBox[rows][cols].getPosition().y + 72;
                   
                }
                else if (myPlayer.m_direction == myPlayer.Down)
                {
                    myPlayer.playerPos.y = collisionBox[rows][cols].getPosition().y - 24;
                    
                }
                else if (myPlayer.m_direction == myPlayer.Left)
                {
                    myPlayer.playerPos.x = collisionBox[rows][cols].getPosition().x + 72;
                    
                }
                else if (myPlayer.m_direction == myPlayer.Right)
                {
                    myPlayer.playerPos.x = collisionBox[rows][cols].getPosition().x-24;
                    
                }
            }
        }
    }   
}