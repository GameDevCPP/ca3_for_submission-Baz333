#include "engine.h"
#include "maths.h"
#include "system_physics.h"
#include "system_renderer.h"
#include "system_resources.h"
#include <SFML/Graphics.hpp>
#include <future>
#include <iostream>

using namespace sf;
using namespace std;
Scene* Engine::_activeScene = nullptr;
std::string Engine::_gameName;

static bool loading = false;
static float loadingspinner = 0.f;
static float loadingTime;
static RenderWindow* _window;

void Loading_update(float dt, const Scene* const scn) {
    //  cout << "Eng: Loading Screen\n";
    if (scn->isLoaded()) {
        cout << "Eng: Exiting Loading Screen\n";
        loading = false;
    }
    else {
        loadingspinner += 400.0f * dt;
        loadingTime += dt;
    }
}
void Loading_render() {
    // cout << "Eng: Loading Screen Render\n";

    static Sprite background;
    auto backTexture = Resources::get<Texture>("Space_Background.png");
    background.setTexture(*backTexture);

    static CircleShape octagon(100);
    octagon.setOrigin(Vector2f(100, 100));
    octagon.setRotation(deg2rad(loadingspinner));
    octagon.setPosition(Vcast<float>(Engine::getWindowSize()) * .5f);
    //auto tex = new Texture();
    auto tex = std::make_shared<sf::Texture>();
    tex->loadFromFile("res/img/Terran.png");
    octagon.setFillColor(Color(255, 255, 255, min(255.f, 40.f * loadingTime)));
    octagon.setTexture(tex.get());

    static Text t("Loading", *Resources::get<sf::Font>("RobotoMono-Regular.ttf"));
    t.setFillColor(Color(255, 255, 255, min(255.f, 40.f * loadingTime)));
    t.setOutlineThickness(2);
    t.setPosition(Vcast<float>(Engine::getWindowSize()) * Vector2f(0.5f, 0.3f));
    t.setOrigin(t.getLocalBounds().left + t.getLocalBounds().width / 2.0f,
                t.getLocalBounds().top + t.getLocalBounds().height / 2.0f);
    Renderer::queue(&background);
    Renderer::queue(&t);
    Renderer::queue(&octagon);
}

float frametimes[256] = {};
uint8_t ftc = 0;

void Engine::Update() {
    static sf::Clock clock;
    float dt = clock.restart().asSeconds();
    {
        frametimes[++ftc] = dt;
        static string avg = _gameName + " FPS:";
        if (ftc % 60 == 0) {
            double davg = 0;
            for (const auto t : frametimes) {
                davg += t;
            }
            davg = 1.0 / (davg / 255.0);
            _window->setTitle(avg + toStrDecPt(2, davg));
        }
    }

    if (loading) {
        Loading_update(dt, _activeScene);
    }
    else if (_activeScene != nullptr) {
        Physics::update(dt);
        _activeScene->Update(dt);
    }
}

void Engine::Render(RenderWindow& window) {
    if (loading) {
        Loading_render();
    }
    else if (_activeScene != nullptr) {
        _activeScene->Render();
    }

    Renderer::render();
}

void Engine::Start(unsigned int width, unsigned int height,
                   const std::string& gameName, Scene* scn) {
    RenderWindow window(VideoMode(width, height), gameName);
    //window.setVerticalSyncEnabled(true);
    _gameName = gameName;
    _window = &window;
    Renderer::initialise(window);
    Physics::initialise();
    ChangeScene(scn);
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
        }
        if (Keyboard::isKeyPressed(Keyboard::Escape)) {
            window.close();
        }

        window.clear();
        Update();
        Render(window);
        window.display();
    }
    if (_activeScene != nullptr) {
        _activeScene->UnLoad();
        _activeScene = nullptr;
    }
    window.close();
    Physics::shutdown();
    // Render::shutdown();
}

std::shared_ptr<Entity> Scene::makeEntity() {
    auto e = make_shared<Entity>(this);
    ents.list.push_back(e);
    return std::move(e);
}

//void Scene::addEntity(shared_ptr<Entity> entity) {
//	ents.list.push_back(entity);
//}

void Engine::setVsync(bool b) { _window->setVerticalSyncEnabled(b); }

void Engine::setView(View v) { _window->setView(v); }

void Engine::moveView(Vector2f movement) {
    View tempview = _window->getView();
    tempview.move(movement);
    Engine::setView(tempview);
}

// CHANGE RES PART
void Engine::changeResolution(int x, int y)
{
    Vector2f _newResolution(x, y);
    _window->create(VideoMode(_newResolution.x, _newResolution.y), "PowerKraft");
}

void Engine::ChangeScene(Scene* s) {
    cout << "Eng: changing scene: " << s << endl;
    auto old = _activeScene;
    _activeScene = s;

    if (old != nullptr) {
        old->UnLoad(); // todo: Unload Async
    }

    if (!s->isLoaded()) {
        cout << "Eng: Entering Loading Screen\n";
        loadingTime = 0;
        //_activeScene->LoadAsync();
        _activeScene->Load();
        loading = true;
    }
}

sf::Vector2f Engine::flocking(Entity* thisEnemy, Vector2f toPlayer)
{
    //shared_ptr<Entity> choosenEnemy = make_shared<Entity>(thisEnemy);
    Vector2f movement = Vector2f(0, 0);
    Vector2f alignment = Vector2f(0, 0);
    Vector2f cohesion = Vector2f(0, 0);
    Vector2f separation = Vector2f(0, 0);
    int neighborCount = 0;

    auto ecm = _activeScene->getEcm();
    auto enemies = ecm.find("enemy");

    for (shared_ptr<Entity>& enemy : enemies)
    {
        Entity* rawEnemy = enemy.get();
        if (rawEnemy != thisEnemy)
        {
            float xDistance = enemy->getPosition().x - thisEnemy->getPosition().x;
            float yDistance = enemy->getPosition().y - thisEnemy->getPosition().y;

            auto distance = (xDistance * xDistance) + (yDistance * yDistance);

            if (distance < 3000)
            {
                alignment.x += toPlayer.x;
                alignment.y += toPlayer.y;
                neighborCount++;
            }
        }
    }

    if (neighborCount == 0)
    {
        return alignment;
    }

    alignment.x /= neighborCount;
    alignment.y /= neighborCount;
    alignment = normalize(alignment);

    // Cohesion ----------------------------------------------------------------------------------------------
    for (shared_ptr<Entity>& enemy : enemies)
    {
        Entity* rawEnemy = enemy.get();
        if (rawEnemy != thisEnemy)
        {
            float xDistance = enemy->getPosition().x - thisEnemy->getPosition().x;
            float yDistance = enemy->getPosition().y - thisEnemy->getPosition().y;

            auto distance = (xDistance * xDistance) + (yDistance * yDistance);

            if (distance < 3000)
            {
                cohesion.x += enemy->getPosition().x;
                cohesion.y += enemy->getPosition().y;
            }
        }
    }

    cohesion.x /= neighborCount;
    cohesion.y /= neighborCount;

    cohesion = Vector2f(cohesion.x - thisEnemy->getPosition().x, cohesion.y - thisEnemy->getPosition().y);
    cohesion = normalize(cohesion);

    // Separation -------------------------------------------------------------------------------------------
    for (shared_ptr<Entity>& enemy : enemies)
    {
        Entity* rawEnemy = enemy.get();
        if (rawEnemy != thisEnemy)
        {
            float xDistance = enemy->getPosition().x - thisEnemy->getPosition().x;
            float yDistance = enemy->getPosition().y - thisEnemy->getPosition().y;

            auto distance = (xDistance * xDistance) + (yDistance * yDistance);

            if (distance < 3000)
            {
                separation.x += enemy->getPosition().x - thisEnemy->getPosition().x;
                separation.y += enemy->getPosition().y - thisEnemy->getPosition().y;
            }
        }
    }

    separation.x *= -1;
    separation.y *= -1;

    movement.x = toPlayer.x + alignment.x + cohesion.x + separation.x;
    movement.y = toPlayer.y + alignment.y + cohesion.y + separation.y;

    movement = normalize(movement);
    return movement;
}

void Scene::Update(const double& dt) { ents.update(dt); }

void Scene::Render() { ents.render(); }

EntityManager Scene::getEcm() { return ents; }

bool Scene::isLoaded() const {
    {
        std::lock_guard<std::mutex> lck(_loaded_mtx);
        // Are we already loading asynchronously?
        if (_loaded_future.valid() // yes
            &&                     // Has it finished?
            _loaded_future.wait_for(chrono::seconds(0)) ==
            future_status::ready) {
            // Yes
            _loaded_future.get();
            _loaded = true;
        }
        return _loaded;
    }
}
void Scene::setLoaded(bool b) {
    {
        std::lock_guard<std::mutex> lck(_loaded_mtx);
        _loaded = b;
    }
}

void Scene::UnLoad() {
    ents.list.clear();
    setLoaded(false);
}

void Scene::LoadAsync() { _loaded_future = std::async(&Scene::Load, this); }

sf::Vector2u Engine::getWindowSize() { return _window->getSize(); }

sf::RenderWindow& Engine::GetWindow() { return *_window; }

namespace timing {
    // Return time since Epoc
    long long now() {
        return std::chrono::high_resolution_clock::now()
                .time_since_epoch()
                .count();
    }
    // Return time since last() was last called.
    long long last() {
        auto n = now();
        static auto then = now();
        auto dt = n - then;
        then = n;
        return dt;
    }
} // namespace timing

Scene::~Scene() { UnLoad(); }