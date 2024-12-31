//Player component header file
#pragma once

#include "cmp_actor_movement.h"
#include <ecm.h>

#include "SFML/Audio/SoundBuffer.hpp"

enum move_states { WSAD, Arrows };

class PlayerComponent : public ActorMovementComponent {
public:

	PlayerComponent() = delete;
	explicit PlayerComponent(Entity* p);

	void update(double dt) override;
	void render() override;
	~PlayerComponent() override = default;

	void setHealth(int health);
	int getHealth();

	void setNumPickups(int numPickups);
	int getNumPickups();

	//void move(const double dt, const float dir_x, const float dir_y);

protected:

	int _health;
	int _numPickups;

	std::shared_ptr<sf::SoundBuffer> soundPowerup_buffer;
	std::shared_ptr<sf::Sound> soundPowerup;
};