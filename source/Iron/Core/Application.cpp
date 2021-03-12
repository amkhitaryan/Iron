#include <iostream>
#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#endif
#ifdef __unix__
#include <climits>
#include <unistd.h>
#endif

#include "Application.h"
#include "Input.h"
#include "Log.h"
#include "Time.h"
#include "../Audio/AudioCore.h"
#include "../Physics/Physics.h"
#include "../Rendering/Renderer.h"
#include "../Scripting/ScriptingSystem.h"
#include "../Rendering/SpriteRenderer.h"
#include "../UI/UIRenderer.h"
#include "../Animation/Animator.h"
#include "../Audio/AudioSource.h"
#include "../Audio/AudioListener.h"

Application* Application::Instance;

Application::Application(ApplicationSettings settings)
{
    Instance = this;

    state = ApplicationStates::Initializing;
    Init(settings);
}

void Application::Init(ApplicationSettings settings)
{
    Log::LogInfo("Running in " + GetRuntimePath());

    ScriptingSystem::Init();

    Screen::Init(settings.ScreenWidth, settings.ScreenHeight, settings.ScreenColor, settings.Fullscreen);

    resources = new ResourcesManager();
    scene = new Scene();
    scene->CreateMainCamera();

    Renderer::Init();
    AudioCore::Init(scene->GetMainCamera().Owner);
    Physics::Init();

    Log::LogInfo("Application initialized");
}

void Application::Run()
{
    Log::LogInfo("Running application");

    isRunning = true;

    state = ApplicationStates::EntryPoint;
    ScriptingSystem::CallEntryPoint();

    while (isRunning)
    {
        RunUpdate();
    }

    Terminate();
}

void Application::RunUpdate()
{
    if (!isRunning)
        return; // When updated not from Run()

    state = ApplicationStates::PollEvents;
    Input::PollEvents();

    Screen::UpdateSize();

    Renderer::Clear(Screen::GetColor());

    // Send callbacks for mouse events to affected entities
    Input::SendMouseCallbacks();

    // Update and render objects in scene
    state = ApplicationStates::OnUpdate;

    // Update animations, sound and scripts
    auto animators = scene->GetEntitiesRegistry()->GetComponentIterator<Animator>();
    for (auto& animator : animators)
        animator.OnUpdate();

    auto audioSources = scene->GetEntitiesRegistry()->GetComponentIterator<AudioSource>();
    for (auto& audioSource : audioSources)
        audioSource.OnUpdate();

    auto audioListeners = scene->GetEntitiesRegistry()->GetComponentIterator<AudioListener>();
    for (auto& audioListener : audioListeners)
        audioListener.OnUpdate();

    auto scripts = scene->GetEntitiesRegistry()->GetComponentIterator<ScriptComponent>();
    int size = scripts.Size();
    // Iterating over scripts with index because they can modify components in update
    for (int i = 0; i < size; i++)
        scripts[i].OnUpdate();

    if (Time::FixedUpdate())
    {
        state = ApplicationStates::OnPhysicsUpdate;
        Physics::Simulate(Time::FixedDeltaTime());

        auto rigidBodies = scene->GetEntitiesRegistry()->GetComponentIterator<RigidBody>();
        for (auto& rigidBody : rigidBodies)
            rigidBody.GetPhysicsTransformation();

        for (int i = 0; i < size; i++)
            scripts[i].OnFixedUpdate();
    }

    state = ApplicationStates::OnLateUpdate;

    for (int i = 0; i < size; i++)
        scripts[i].OnLateUpdate();

    // Clean destroyed entities
    state = ApplicationStates::CleaningDestroyedEntities;
    scene->CleanDestroyedEntities();

    Time::Update();

    Renderer::OnBeforeRender(scene->GetMainCamera());

    state = ApplicationStates::OnRender;
    // Draw sprites

    auto spriteRenderers = scene->GetEntitiesRegistry()->GetComponentIterator<SpriteRenderer>();
    for (auto& spriteRenderer : spriteRenderers)
        spriteRenderer.OnRender();

    // Clear depth buffer before rendering UI
    Renderer::PrepareUIRender();
    // Draw UI on top

    auto uiRenderers = scene->GetEntitiesRegistry()->GetComponentIterator<UIRenderer>();
    for (auto& uiRenderer : uiRenderers)
        uiRenderer.OnRender();

    Renderer::OnAfterRender();

    Screen::SwapBuffers();

    if (Screen::WindowShouldClose())
        isRunning = false;

    // TODO: testing fps (will be moved to debug UI)
    fpsCounter ++;
    fpsTimer += Time::DeltaTime();
    if (fpsTimer > 2.0f)
    {
        Log::LogInfo("FPS " + std::to_string(fpsCounter / 2));
        //Log::LogInfo("Entities in scene " + std::to_string(scene->GetEntitiesRegistry().));
        fpsTimer = 0;
        fpsCounter = 0;
    }
}

void Application::Terminate()
{
    Log::LogInfo("Entities was created " + std::to_string(Scene::EntitiesWasCreated));

    delete scene;

    delete resources;

    Physics::Terminate();
    AudioCore::Terminate();
    Renderer::Terminate();
    Screen::Terminate();
    ScriptingSystem::Terminate();
}

void Application::Quit()
{
    isRunning = false;
}

ApplicationStates::ApplicationState Application::State()
{
    return state;
}

ResourcesManager* Application::GetResourcesManager()
{
    return resources;
}

Scene* Application::GetCurrentScene()
{
    return scene;
}

std::string Application::GetRuntimePath()
{
#ifdef __unix__
    char arg1[20];
    char result[PATH_MAX + 1] = {0};

    sprintf(arg1, "/proc/%d/exe", getpid());
    readlink(arg1, result, 1024);
    return std::string(result);
#endif
#if defined(_WIN32) || defined(_WIN64)
    char result[MAX_PATH];
    GetModuleFileName(nullptr, result, MAX_PATH);
    return std::string(result);
#endif
}

std::string Application::GetDataPath()
{
    // TODO
    return GetRuntimePath();
}
