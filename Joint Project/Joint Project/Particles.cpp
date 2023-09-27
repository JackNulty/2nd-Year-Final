#include "Particles.h"



Particles::Particles()
{
	// load particles 
	if (!m_particleTexture.loadFromFile("ASSETS/FX/Particle/Spark.png"))
	{
		std::cout << "error loading particle\n";
	}
	// set the texture and rect of the particles
	mParticleSystem.setTexture(m_particleTexture);
	mParticleSystem.addTextureRect(sf::IntRect(0, 0, 9, 8));
	// set the parameters for the emitter 
	emitter.setEmissionRate(30);
	emitter.setParticleLifetime(thor::Distributions::uniform(sf::milliseconds(100), sf::milliseconds(200)));
	emitter.setParticleTextureIndex(0);
	emitter.setParticleScale(sf::Vector2f(2,2));
}

void Particles::update(sf::Vector2f t_pos, sf::Vector2f& t_direction)
{
	sf::Time timePerFrame = sf::seconds(1.0f / 60); // 60 fps
	emitter.setParticlePosition(thor::Distributions::circle(t_pos,3.0f)); // emit in a circle at the t_pos with a radius of 3.0f
	emitter.setParticleVelocity(thor::Distributions::deflect(t_direction, 15.f)); // Emit towards direction with deviation of 15°
	emitter.setParticleRotation(thor::Distributions::uniform(0.f, 360.f));      // Rotate randomly
	mParticleSystem.addEmitter(emitter,sf::milliseconds(100)); // each particle lasts 100 milliseconds
	mParticleSystem.update(timePerFrame); // 60 fps);
}

void Particles::render(sf::RenderWindow& window)
{
	window.draw(mParticleSystem); // draw particle system
}
