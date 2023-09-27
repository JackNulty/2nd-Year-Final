#pragma once
#include "Globals.h"
#include <Thor/Particles.hpp>

class Particles {
public:
	Particles();
	void update(sf::Vector2f t_pos, sf::Vector2f& t_direction);
	void render(sf::RenderWindow& window);
private:
	sf::Texture m_particleTexture;
	thor::ParticleSystem mParticleSystem;
	thor::UniversalEmitter emitter;

};


