#include "scene_menu.h"
#include "../components/cmp_text.h"
#include "../powerkraft.h"
#include "LevelSystem.h"
#include <iostream>
#include"../components/cmp_button.h"
#include "engine.h"
#include <SFML/Audio.hpp>
#include <iostream>

using namespace std;
using namespace sf;

View menuView;

sf::Music music;

shared_ptr<Entity> btnExit;
shared_ptr<Entity> btnSetting;
shared_ptr<Entity> btnStart;

Sprite background;

void MenuScene::Load() {
    cout << "Menu Load \n";

    menuView.reset(FloatRect(0, 0, resolution.x, resolution.y));
    RenderWindow& window = Engine::GetWindow();
    Vector2u windowSize = window.getSize();

    // set background
    try {
        auto backTexture = Resources::get<Texture>("Space_Background.png");
        background.setTexture(*backTexture);
    }
    catch (const std::runtime_error& e) {
        std::cerr << "Resource error: " << e.what() << std::endl;
        // Fallback: Use a default texture or skip rendering
        // e.g., `background.setTexture(defaultTexture);`
    }

    auto txt = makeEntity();
    auto pos = Vector2f(menuView.getSize().x / 2.0f, menuView.getSize().y / 5.0f);
    auto t = txt->addComponent<TextComponent>(menuView.getSize().x / 2.0f, menuView.getSize().y / 5.0f, "PowerKraft");

    btnExit = makeEntity();
    auto btnPos = Vector2f(menuView.getSize().x / 2.0f, menuView.getSize().y / 1.5f);
    auto button = btnExit->addComponent<Button>(btnPos, "Exit", sf::Color::White, sf::Color::Green, sf::Color::Red);

    btnSetting = makeEntity();
    auto btn2Pos = Vector2f(menuView.getSize().x / 2.0f, menuView.getSize().y / 2.f);
    auto button2 = btnSetting->addComponent<Button>(btn2Pos, "Setting", sf::Color::White, sf::Color::Green, sf::Color::Red);

    btnStart = makeEntity();
    auto btn3Pos = Vector2f(menuView.getSize().x / 2.0f, menuView.getSize().y / 3.f);
    auto button3 = btnStart->addComponent<Button>(btn3Pos, "Play", sf::Color::White, sf::Color::Green, sf::Color::Red);

    auto musicstatus = music.getStatus();
    if (musicstatus == SoundSource::Stopped || musicstatus == SoundSource::Paused)
    {
        //A more typical and better approach to just simply print an error message might be to use a try-catch block.
        if (!music.openFromFile("res/sound/Clair_de_lune.ogg")) //How can We Ensure that we alway load the correct asset without having to recompile?? DF.
            std::cerr << "music broken" <<std::endl; // DF. error message logging is preferred
        music.setVolume(volume);
        music.setLoop(true);
        music.play();
    }

    setLoaded(true);
}

void MenuScene::Update(const double& dt) {
    if (btnStart->GetCompatibleComponent<Button>()[0]->isPressed())
    {
        Engine::ChangeScene(&planetLevel);
        ls::setTextureMap("res/img/grass.png");
        music.stop();
    }
    else if (btnSetting->GetCompatibleComponent<Button>()[0]->isPressed())
    {
        Engine::ChangeScene(&settings);
    }
    else if (btnExit->GetCompatibleComponent<Button>()[0]->isPressed())
    {
        Engine::GetWindow().close();
    }

    if (!sf::Mouse::isButtonPressed(Mouse::Button::Left))
        Button::_mouseState = BUTTON_IDLE;

    Scene::Update(dt);
}

void MenuScene::Render()
{
    Renderer::queue(&background);
    Engine::setView(menuView);
    Scene::Render();
}