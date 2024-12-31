#include "cmp_powerup_speed.h"

using namespace std;
using namespace sf;

SpeedPowerupComponent::SpeedPowerupComponent(Entity *p) : Component(p) {
	timer = maxTimer;
}

void SpeedPowerupComponent::update(const double dt) {
	timer -= dt;
	if (timer <= 0) {
		_parent->removeComponent<SpeedPowerupComponent>();
	}
}

float SpeedPowerupComponent::getRemainingTime() const {
	return timer;
}

float SpeedPowerupComponent::getMaxTimer() const {
	return maxTimer;
}



void SpeedPowerupComponent::render() {}