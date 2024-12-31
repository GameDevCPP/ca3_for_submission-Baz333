#include "cmp_pickup.h"
#include "../powerkraft.h"
#include "cmp_player.h"
#include "system_resources.h"
#include "SFML/Graphics/RenderWindow.hpp"

using namespace std;
using namespace sf;

PickupComponent::PickupComponent(Entity *p, shared_ptr<Entity> player) : Component(p), _player(player) {
	timer = 0.f;
}

void PickupComponent::update(const double dt) {
	timer += dt;

    auto& playerPos = _player->getPosition();
    auto& pickupPos = _parent->getPosition();
    float xDistance = playerPos.x - pickupPos.x;
    float yDistance = playerPos.y - pickupPos.y;
    auto distance = (xDistance * xDistance) + (yDistance * yDistance);

	if(timer > 10.f) {
		_parent->setPosition(Vector2f(-1000, -1000));
	}
	if(distance < 3500.f) {
	    _parent->setPosition(Vector2f(-1000, -1000));
	    auto cmp = _player->GetCompatibleComponent<PlayerComponent>()[0];
	    cmp->setNumPickups(cmp->getNumPickups() + 1);
		std::cout << cmp->getNumPickups() << std::endl;

		soundPickup_buffer = Resources::get<SoundBuffer>("pickup.wav");
		soundPickup = make_shared<Sound>(*soundPickup_buffer);
		soundPickup->setVolume(volume);
		soundPickup->play();
	}
}

void PickupComponent::render() {}