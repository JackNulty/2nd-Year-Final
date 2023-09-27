#pragma once
#include "Globals.h"
#include <Thor/Particles.hpp>

class PlayerParticles {
public:
	PlayerParticles();
	void update(sf::Vector2f t_pos);
	void render(sf::RenderWindow& window);

private:
	sf::Texture m_particleTexture;
	thor::ParticleSystem mParticleSystem;
	thor::UniversalEmitter emitter;

};
