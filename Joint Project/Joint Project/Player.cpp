#include "Player.h"

Player::Player()
{
	init();
}

void Player::init()
{
	// load all the player sprite options
	if (!playerSpritesheet.loadFromFile("ASSETS/Actor/Characters/MaskFrog/SpriteSheet.png"))
	{
		std::cout << "player spritesheet did not load" << "\n";
	}
	if (!blueNinjaSpritesheet.loadFromFile("ASSETS/Actor/Characters/BlueNinja/SpriteSheet.png"))
	{
		std::cout << "blue ninja spritesheet did not load" << "\n";
	}
	if (!cavemanSpritesheet.loadFromFile("ASSETS/Actor/Characters/Caveman/SpriteSheet.png"))
	{
		std::cout << "caveman spritesheet did not load" << "\n";
	}
	if (!greyNinjaSpritesheet.loadFromFile("ASSETS/Actor/Characters/GrayNinja/SpriteSheet.png"))
	{
		std::cout << "grey ninja spritesheet did not load" << "\n";
	}
	if (!knightSpritesheet.loadFromFile("ASSETS/Actor/Characters/Knight/SpriteSheet.png"))
	{
		std::cout << "knight spritesheet did not load" << "\n";
	}
	if (!redNinjaSpritesheet.loadFromFile("ASSETS/Actor/Characters/RedNinja/SpriteSheet.png"))
	{
		std::cout << "red ninja spritesheet did not load" << "\n";
	}

	// set the parameters for the sprite
	playerSprite.setTexture(playerSpritesheet);
	playerSprite.setTextureRect(sf::IntRect(0, 0, 16, 16));
	playerSprite.setPosition(playerPos);
	playerSprite.setOrigin(8, 8);
	playerSprite.setScale(SCALE,SCALE);
	myWeapon.init();

	if (!m_footStepSound.loadFromFile("ASSETS/Sounds/Game/Run.wav"))
	{
		std::cout << "error loading footStep sound\n";
	}
	m_stompers.setBuffer(m_footStepSound);
	m_stompers.setVolume(60);
}

void Player::render(sf::RenderWindow & window)
{
	// draw player 
	if (m_animationState == Walking)
		myParticles.render(window);
	window.draw(playerSprite);
	//myWeapon.draw(window);


	if (bowGone.isExpired())
	{
		myWeapon.draw(window);
	}
	myWeapon.drawProjectiles(window);
}

void Player::update(double dt)
{
	// check the key presses
	checkKeyPresses();
	if (attack == true)
	{
		m_animationState = Attacking; // start attack animation if your attacking
	}
	playAnimation(); // play animations
	playerSprite.setPosition(playerPos); // set pos
	dash(); // check for dash
	cooldown--;
	if (cooldown <= 0)
	{
		cooldown = 0; // cooldown for dash
	}
	//update weapon obj for player
	if (bowGone.isExpired())
	{
		myWeapon.update(dt);
		myWeapon.setPos(playerPos);
	}
	myWeapon.updateProjectiles();
	
}

void Player::checkKeyPresses()
{
	//player is moving up
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		playerPos.y -= 3;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) // run faster with Lshift
		{
			playerPos.y -= 4;
		}
		m_direction = Up;
		m_animationState = Walking;
		if (m_footStepTimer.isExpired())
		{
			m_stompers.play();
			m_footStepTimer.restart(sf::seconds(m_walkTimer));
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		playerPos.y += 3;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
		{
			playerPos.y += 4;
		}
		m_direction = Down;
		m_animationState = Walking;
		if (m_footStepTimer.isExpired())
		{
			m_stompers.play();
			m_footStepTimer.restart(sf::seconds(m_walkTimer));
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		playerPos.x += 3;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
		{
			playerPos.x += 4;
		}
		m_direction = Right;
		m_animationState = Walking;
		if (m_footStepTimer.isExpired())
		{
			m_stompers.play();
			m_footStepTimer.restart(sf::seconds(m_walkTimer));
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		playerPos.x -= 3;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
		{
			playerPos.x -= 4;
		}
		m_direction = Left;
		m_animationState = Walking;
		if (m_footStepTimer.isExpired())
		{
			m_stompers.play();
			m_footStepTimer.restart(sf::seconds(m_walkTimer));
		}
	}
	else {
		m_animationState = Idle; // be idle if not moving 
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
	{
		myWeapon.changeWeapon();
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) // left mouse button to fire
	{
		if (bowGone.isExpired())
		{
			myWeapon.generateBullet(playerPos);
			if (myWeapon.m_weaponType == myWeapon.FORK)
			{
				attack = true;
			}
		}

	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) // space to dash
	{
		if (dashTimer.isExpired() && dashCooldown.isExpired())
		{
			isDashing = true;
			dashTimer.restart(sf::seconds(0.3));
			dashCooldown.restart(sf::seconds(3));
		}
	}
}

void Player::playAnimation()
{
	frameTimer++; // timer for walking animation
	attackTimer++; // timer for attacking animation
	if (frameTimer >= 10)
	{
		changeFrame = true;
	}
	if (attackTimer >= 30)
	{
		changeAttackFrame = true;
	}
	if (m_animationState == Idle)
	{
		if (m_direction == Up)
			playerSprite.setTextureRect(sf::IntRect(16, 0, 16, 16));
		else if(m_direction == Down)
			playerSprite.setTextureRect(sf::IntRect(0, 0, 16, 16));
		else if(m_direction == Left)
			playerSprite.setTextureRect(sf::IntRect(32, 0, 16, 16));
		else if(m_direction == Right)
			playerSprite.setTextureRect(sf::IntRect(48, 0, 16, 16));
	} // if idle then stay still based on last direction 
	else if (m_animationState == Walking)
	{
		if (m_direction == Up)
		{
			//particles update
			myParticles.update(sf::Vector2f(playerSprite.getPosition().x, playerSprite.getPosition().y + 12));
			if (changeFrame == true)
			{
				playerSprite.setTextureRect(sf::IntRect(16, (16 * currentFrame), 16, 16));
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
			//particles update
			myParticles.update(sf::Vector2f(playerSprite.getPosition().x, playerSprite.getPosition().y + 24));
			if (changeFrame == true)
			{
				playerSprite.setTextureRect(sf::IntRect(0, (16 * currentFrame), 16, 16));
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
			//particles update
			myParticles.update(sf::Vector2f(playerSprite.getPosition().x, playerSprite.getPosition().y + 24));
			if (changeFrame == true)
			{
				playerSprite.setTextureRect(sf::IntRect(32, (16 * currentFrame), 16, 16));
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
			//particles update
			myParticles.update(sf::Vector2f(playerSprite.getPosition().x, playerSprite.getPosition().y + 24));
			if (changeFrame == true)
			{
				playerSprite.setTextureRect(sf::IntRect(48, (16 * currentFrame), 16, 16));
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
	else if (m_animationState == Attacking) // if the player is attacking then play relevent animation
	{
		if (m_direction == Up)
		{
			if (changeAttackFrame == true)
			{
				playerSprite.setTextureRect(sf::IntRect(16, (16 * (currentAttackFrame + 4)), 16, 16));
				changeAttackFrame = false; // cant change frame
				attackTimer = 0; // reset timer 
				currentAttackFrame++; // checks what number frame the attack is on
				attack = false; // animation done so set attack to fasle 
				if (currentAttackFrame == 1)
				{
					currentAttackFrame = 0;
				}
			}
		}
		else if (m_direction == Down)
		{
			if (changeAttackFrame == true)
			{
				playerSprite.setTextureRect(sf::IntRect(0, (16 * (currentAttackFrame + 4)), 16, 16));
				changeAttackFrame = false;
				attackTimer = 0;
				currentAttackFrame++;
				attack = false;
				if (currentAttackFrame == 1)
				{
					currentAttackFrame = 0;
				}
			}
		}
		else if (m_direction == Left)
		{
			if (changeAttackFrame == true)
			{
				playerSprite.setTextureRect(sf::IntRect(32, (16 * (currentAttackFrame + 4)), 16, 16));
				changeAttackFrame = false;
				attackTimer = 0;
				currentAttackFrame++;
				attack = false;
				if (currentAttackFrame == 1)
				{
					currentAttackFrame = 0;
				}
			}
		}
		else if (m_direction == Right)
		{
			if (changeAttackFrame == true)
			{
				playerSprite.setTextureRect(sf::IntRect(48, (16 * (currentAttackFrame + 4)), 16, 16));
				changeAttackFrame = false;
				attackTimer = 0;
				currentAttackFrame++;
				attack = false;
				if (currentAttackFrame == 1)
				{
					currentAttackFrame = 0;
				}
			}
		}
	}

}

void Player::dash()
{
	if (isDashing == true) // must be able to dash and cooldown is over 
	{
		// checks direction of dash
		if (m_direction == Up)
			playerPos.y -= 10;
		else if (m_direction == Down)
			playerPos.y += 10;
		else if (m_direction == Left)
			playerPos.x -= 10;
		else if(m_direction == Right)
			playerPos.x += 10;
		m_animationState = Walking;
		if (dashTimer.isExpired())
		{
			isDashing=false;
		}
	}
}

sf::Sprite Player::getSprite()
{
	return playerSprite; // gets player sprite
}

sf::Vector2f Player::getPos()
{
	return playerPos; // gets player pos
}

void Player::swapCharacter(int t_characterNum)
{
	if (t_characterNum == 0)
	{
		playerSprite.setTexture(redNinjaSpritesheet);
	}
	if (t_characterNum == 1)
	{
		playerSprite.setTexture(blueNinjaSpritesheet);
	}
	if (t_characterNum == 2)
	{
		playerSprite.setTexture(greyNinjaSpritesheet);
	}
	if (t_characterNum == 3)
	{
		playerSprite.setTexture(playerSpritesheet);
	}
	if (t_characterNum == 4)
	{
		playerSprite.setTexture(cavemanSpritesheet);
	}
	if (t_characterNum == 5)
	{
		playerSprite.setTexture(knightSpritesheet);
	}
}

int Player::passSprite(sf::Sprite t_enemy)
{
	return myWeapon.handleCollisions(t_enemy);
}