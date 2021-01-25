#include <iostream>
#include <GLAD/glad.h>

#include "Application.h"
#include "Log.h"
#include "Time.h"
#include "../Rendering/Renderer.h"
#include "../Audio/AudioSystem.h"

Application* Application::Instance;
ResourcesManager* resources;
Scene* scene;

Application::Application(ApplicationSettings settings)
{
    state = ApplicationStates::Initializing;
    Init(settings);

    Instance = this;
}

void Application::Init(ApplicationSettings settings)
{
    Screen::Init(settings.ScreenWidth, settings.ScreenHeight, settings.ScreenColor, settings.Fullscreen);

    gladLoadGL();

    resources = new ResourcesManager();
    scene = new Scene();

    Renderer::Init(scene->MainCamera);
    AudioSystem::Init(scene->MainCamera->ParentObject);

    Log::LogInfo("Application initialized");
}

void Application::Run()
{
    Log::LogInfo("Running application");

    isRunning = true;

    float timer = 0;
    int counter = 0;

    while (isRunning)
    {
        Input::PollEvents();

        Renderer::Clear(Screen::Color());
        Renderer::OnBeforeRender();

        // Update and render objects in scene
        state = ApplicationStates::OnUpdate;
        auto objects = std::vector<Object*>(scene->Objects);
        for (auto &object : objects)
        {
            for (auto &component : object->Components())
            {
                try
                {
                    component->OnUpdate();
                }
                catch (const std::exception& ex)
                {
                    Log::LogError("Error in update: " + std::string(ex.what()));
                }
            }
            object->OnUpdate();
        }
        state = ApplicationStates::OnLateUpdate;
        for (auto &object : objects)
        {
            for (auto &component : object->Components())
            {
                try
                {
                    component->OnLateUpdate();
                }
                catch (const std::exception& ex)
                {
                    Log::LogError("Error in late update: " + std::string(ex.what()));
                }
            }
            object->OnLateUpdate();
        }

        state = ApplicationStates::OnRender;
        for (auto &object : objects)
        {
            for (auto &component : object->Components())
            {
                try
                {
                    // TODO: change to render calls and do depth sorting
                    component->OnRender();
                }
                catch (const std::exception& ex)
                {
                    Log::LogError("Error in render: " + std::string(ex.what()));
                }
            }
        }
        objects.clear();

        //Update scene
        state = ApplicationStates::CleaningDestroyedObjects;
        scene->CleanDestroyedObjects();

        Screen::SwapBuffers();

        Time::Update();

        if (Screen::WindowShouldClose())
            isRunning = false;

        // TODO: testing fps
        counter ++;
        timer += Time::DeltaTime();
        if (timer > 1.0f)
        {
            Log::LogInfo("FPS " + std::to_string(counter));
            Log::LogInfo("Objects in scene " + std::to_string(scene->Objects.size()));
            timer = 0;
            counter = 0;
        }
    }

    Terminate();
}

void Application::Terminate()
{
    scene->CleanAllObjects();
    delete scene;

    delete resources;

    AudioSystem::Terminate();
    Renderer::Terminate();
    Screen::Terminate();
}

void Application::Quit()
{
    isRunning = false;
}

ApplicationStates::ApplicationState Application::State()
{
    return state;
}

ResourcesManager *Application::GetResourcesManager()
{
    return resources;
}

Scene* Application::GetCurrentScene()
{
    return scene;
}
