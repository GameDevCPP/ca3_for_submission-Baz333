#include "cmp_powerup.h"

using namespace std;
using namespace sf;

PowerupComponent::PowerupComponent(Entity *p, float maxTimer)
	: Component(p), maxTimer(maxTimer), timer(maxTimer) {

}

void PowerupComponent::update(const double dt) {
	timer -= dt;
	if(timer <= 0) {
		_parent->removeComponent<PowerupComponent>();
	}
}

float PowerupComponent::getRemainingTime() const {
	return timer;
}

float PowerupComponent::getMaxTimer() const {
	return maxTimer;
}

void PowerupComponent::render() {

}

SpeedPowerupComponent::SpeedPowerupComponent(Entity *p)
	:PowerupComponent(p,20.f) {

}

ReloadPowerupComponent::ReloadPowerupComponent(Entity *p)
	:PowerupComponent(p, 15.f) {

}

InstakillPowerupComponent::InstakillPowerupComponent(Entity *p)
	:PowerupComponent(p, 10.f) {

}