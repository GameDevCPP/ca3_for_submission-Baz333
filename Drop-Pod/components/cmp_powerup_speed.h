#pragma once
#include "ecm.h"

class SpeedPowerupComponent: public Component {
protected:
	float timer;
public:
	void update(double dt) override;
	void render() override;
	explicit SpeedPowerupComponent(Entity* p);
	SpeedPowerupComponent() = delete;
	~SpeedPowerupComponent() override = default;
};
