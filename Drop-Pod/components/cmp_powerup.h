#pragma once
#include "ecm.h"

class PowerupComponent : public Component {
protected:
	float timer;
	float maxTimer;
public:
	explicit PowerupComponent(Entity* p, float maxTimer);
	PowerupComponent() = delete;
	~PowerupComponent() override = default;

	void update(double dt) override;
	virtual void render() override;
	float getRemainingTime() const;
	float getMaxTimer() const;
};

class SpeedPowerupComponent : public PowerupComponent {
public:
	explicit SpeedPowerupComponent(Entity* p);
	~SpeedPowerupComponent() override = default;

	void update(double dt) override;
};

class ReloadPowerupComponent : public PowerupComponent {
public:
	explicit ReloadPowerupComponent(Entity* p);
	~ReloadPowerupComponent() override = default;

	void update(double dt) override;
};

class InstakillPowerupComponent : public PowerupComponent {
public:
	explicit InstakillPowerupComponent(Entity* p);
	~InstakillPowerupComponent() override = default;

	void update(double dt) override;
};