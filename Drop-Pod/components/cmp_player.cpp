// Player component C++ file
#include "cmp_player.h"
#include <SFML/Window.hpp>
#include "cmp_powerup.h"
#include "cmp_sprite.h"
#include "../powerkraft.h"

using namespace std;
using namespace sf;

int _health;

static bool wasNum1Pressed = false;
static bool wasNum2Pressed = false;
static bool wasNum3Pressed = false;
static bool wasNum4Pressed = false;

//Constructor
PlayerComponent::PlayerComponent(Entity* p) : ActorMovementComponent(p) {
	_health = 100;
	_numPickups = 0;
}

void PlayerComponent::setHealth(int health)
{
	if(health > 100) {
		_health = 100;
	} else {
		_health = health;
	}
}

int PlayerComponent::getHealth()
{
	return _health;
}

void PlayerComponent::setNumPickups(int numPickups) {
    _numPickups = numPickups;
}

int PlayerComponent::getNumPickups() {
    return _numPickups;
}

void PlayerComponent::update(const double dt)
{
	if (_health <= 0)
	{
		_parent->setAlive(false);
	}

	if(_parent->GetCompatibleComponent<PowerupComponent>().empty()) {
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {
			if(!wasNum1Pressed) {
				if(getNumPickups() >= 1) {
					setNumPickups(getNumPickups() - 1);
					_parent->addComponent<SpeedPowerupComponent>();
					soundPowerup_buffer = Resources::get<SoundBuffer>("powerup.wav");
					soundPowerup = make_shared<Sound>(*soundPowerup_buffer);
					soundPowerup->setVolume(volume);
					soundPowerup->play();
				}
			}
			wasNum1Pressed = true;
		} else {
			wasNum1Pressed = false;
		}

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {
			if(!wasNum2Pressed) {
				if(getNumPickups() >= 2) {
					setNumPickups(getNumPickups() - 2);
					_parent->addComponent<ReloadPowerupComponent>();
					soundPowerup_buffer = Resources::get<SoundBuffer>("powerup.wav");
					soundPowerup = make_shared<Sound>(*soundPowerup_buffer);
					soundPowerup->setVolume(volume);
					soundPowerup->play();
				}
			}
			wasNum2Pressed = true;
		} else {
			wasNum2Pressed = false;
		}

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) {
			if(!wasNum3Pressed) {
				if(getNumPickups() >= 3) {
					setNumPickups(getNumPickups() - 3);
					_parent->addComponent<InstakillPowerupComponent>();
					soundPowerup_buffer = Resources::get<SoundBuffer>("powerup.wav");
					soundPowerup = make_shared<Sound>(*soundPowerup_buffer);
					soundPowerup->setVolume(volume);
					soundPowerup->play();
				}
			}
			wasNum3Pressed = true;
		} else {
			wasNum3Pressed = false;
		}
	}
	if(getHealth() < 100) {
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num4)) {
			if(!wasNum4Pressed) {
				if(getNumPickups() >= 5) {
					setNumPickups(getNumPickups() - 5);
					setHealth(getHealth() + 20);
					soundPowerup_buffer = Resources::get<SoundBuffer>("powerup.wav");
					soundPowerup = make_shared<Sound>(*soundPowerup_buffer);
					soundPowerup->setVolume(volume);
					soundPowerup->play();
				}
			}
			wasNum4Pressed = true;
		} else {
			wasNum4Pressed = false;
		}
	}

	float directX = 0.f;
	float directY = 0.f;

	//Checks which control scheme is used and checks if a movement key is being pressed
	switch (switchState) {
	case WSAD:

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			directX--;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			directX++;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			directY--;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			directY++;
		break;

	case Arrows:

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			directX--;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			directX++;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			directY--;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			directY++;
		break;
	}

	// Check if the player is moving.
	if (directX != 0 || directY != 0)
	{
		_parent->GetCompatibleComponent<ActorMovementComponent>()[0]->setMoving(true);
	}
	else
	{
		_parent->GetCompatibleComponent<ActorMovementComponent>()[0]->setMoving(false);
	}

	// Check the direction of the player.
	if (directX < 0)
	{
		_parent->GetCompatibleComponent<ActorMovementComponent>()[0]->setDirection(true);
	}
	else
	{
		_parent->GetCompatibleComponent<ActorMovementComponent>()[0]->setDirection(false);
	}

	auto speed = _parent->GetCompatibleComponent<ActorMovementComponent>()[0]->getSpeed();
	_parent->GetCompatibleComponent<ActorMovementComponent>()[0]->move(Vector2f(directX * speed * dt, directY * speed * dt));

	// Switch between idle and moving animation for player moving.
	if (!_parent->GetCompatibleComponent<ActorMovementComponent>()[0]->getMoving())
	{
		IntRect playerRect = { Vector2i(0, 0), Vector2i(150, 150) };
		_parent->GetCompatibleComponent<AnimationComponent>()[0]->setAnimation(8, 0.1, Resources::get<Texture>("Idle.png"), playerRect);
	}
	else
	{
		IntRect playerRect = { Vector2i(0, 0), Vector2i(150, 150) };
		_parent->GetCompatibleComponent<AnimationComponent>()[0]->setAnimation(8, 0.1, Resources::get<Texture>("Run.png"), playerRect);
	}

	// Flip the sprite if moving left.
	if (_parent->GetCompatibleComponent<ActorMovementComponent>()[0]->getDirection())
	{
		auto& p = _parent->GetCompatibleComponent<SpriteComponent>()[0]->getSprite();
		_parent->GetCompatibleComponent<SpriteComponent>()[0]->getSprite().setOrigin(p.getLocalBounds().width * 0.5, p.getLocalBounds().height * 0.5);
		_parent->GetCompatibleComponent<SpriteComponent>()[0]->getSprite().setScale(-2.f, 2.f);
	}
	else
	{
		auto& p = _parent->GetCompatibleComponent<SpriteComponent>()[0]->getSprite();
		_parent->GetCompatibleComponent<SpriteComponent>()[0]->getSprite().setOrigin(p.getLocalBounds().width * 0.5, p.getLocalBounds().height * 0.5);
		_parent->GetCompatibleComponent<SpriteComponent>()[0]->getSprite().setScale(2.f, 2.f);
	}
}

void PlayerComponent::render() {}