#pragma once
#include "ecm.h"

class PickupComponent : public Component {
protected:
	float timer;
	std::shared_ptr<Entity> _player;
public:
	void update(double dt) override;
	void render() override;
	explicit PickupComponent(Entity* p, std::shared_ptr<Entity> player);
	PickupComponent() = delete;
	~PickupComponent() override = default;
};
