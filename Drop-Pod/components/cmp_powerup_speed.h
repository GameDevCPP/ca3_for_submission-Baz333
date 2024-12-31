#pragma once
#include "ecm.h"

class SpeedPowerupComponent: public Component {
protected:
	float timer;
	float maxTimer = 20.f;
public:
	void update(double dt) override;
	void render() override;
	explicit SpeedPowerupComponent(Entity* p);
	SpeedPowerupComponent() = delete;
	~SpeedPowerupComponent() override = default;

	float getRemainingTime() const;
	float getMaxTimer() const;
};
