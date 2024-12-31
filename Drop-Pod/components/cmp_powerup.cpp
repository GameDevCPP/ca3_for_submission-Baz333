#include "cmp_powerup.h"

using namespace std;
using namespace sf;

PowerupComponent::PowerupComponent(Entity *p, float maxTimer)
	: Component(p), maxTimer(maxTimer), timer(maxTimer) {

}

void PowerupComponent::update(const double dt) {

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

void SpeedPowerupComponent::update(const double dt) {
	timer -= dt;
	if(timer <= 0) {
		_parent->removeComponent<SpeedPowerupComponent>();
	}
}

ReloadPowerupComponent::ReloadPowerupComponent(Entity *p)
	:PowerupComponent(p, 15.f) {

}

void ReloadPowerupComponent::update(const double dt) {
	timer -= dt;
	if(timer <= 0) {
		_parent->removeComponent<ReloadPowerupComponent>();
	}
}

InstakillPowerupComponent::InstakillPowerupComponent(Entity *p)
	:PowerupComponent(p, 10.f) {

}

void InstakillPowerupComponent::update(const double dt) {
	timer -= dt;
	if(timer <= 0) {
		_parent->removeComponent<InstakillPowerupComponent>();
	}
}