#include "cmp_pickup.h"

#include "cmp_player.h"
#include "SFML/Graphics/RenderWindow.hpp"

using namespace std;
using namespace sf;

PickupComponent::PickupComponent(Entity *p, shared_ptr<Entity> player) : Component(p), _player(player) {
	timer = 0.f;
}

void PickupComponent::update(const double dt) {
	timer += dt;

    auto& playerPos = _player->getPosition();
    auto& enemyPos = _parent->getPosition();
    float xDistance = playerPos.x - enemyPos.x;
    float yDistance = playerPos.y - enemyPos.y;
    auto distance = (xDistance * xDistance) + (yDistance * yDistance);

	if(timer > 10.f) {
		_parent->setPosition(Vector2f(-100, -100));
	}
	if(distance < 3500.f) {
	    _parent->setPosition(Vector2f(-100, -100));
	    auto cmp = _player->GetCompatibleComponent<PlayerComponent>()[0];
	    cmp->setNumPickups(cmp->getNumPickups() + 1);
		std::cout << cmp->getNumPickups() << std::endl;
	}
}

void PickupComponent::render() {}