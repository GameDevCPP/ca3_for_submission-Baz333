#include "cmp_powerup_speed.h"

using namespace std;
using namespace sf;

SpeedPowerupComponent::SpeedPowerupComponent(Entity *p) : Component(p) {
	timer = 20.f;
}

void SpeedPowerupComponent::update(const double dt) {
	timer -= dt;
	if (timer <= 0) {
		_parent->removeComponent<SpeedPowerupComponent>();
	}
}

void SpeedPowerupComponent::render() {}