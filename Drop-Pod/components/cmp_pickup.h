#pragma once
#include "ecm.h"
#include "SFML/Audio/SoundBuffer.hpp"

class PickupComponent : public Component {
protected:
	float timer;
	std::shared_ptr<Entity> _player;

	std::shared_ptr<sf::SoundBuffer> soundPickup_buffer;
	std::shared_ptr<sf::Sound> soundPickup;
public:
	void update(double dt) override;
	void render() override;
	explicit PickupComponent(Entity* p, std::shared_ptr<Entity> player);
	PickupComponent() = delete;
	~PickupComponent() override = default;
};
