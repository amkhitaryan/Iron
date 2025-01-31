#include <mono/jit/jit.h>

#include "EntityInternalCalls.h"
#include "../Core/Application.h"
#include "../Core/Log.h"
#include "../Scene/SceneHelper.h"
#include "../Scene/NameComponent.h"

EntityID EntityInternalCalls::Entity_CreateNewEntity()
{
    return Application::Instance->GetCurrentScene()->CreateEntity();
}

EntityID EntityInternalCalls::Entity_CreateNewEntity2(MonoString* name)
{
    return Application::Instance->GetCurrentScene()->CreateEntity(mono_string_to_utf8(name), NULL_ENTITY);
}

EntityID EntityInternalCalls::Entity_CreateNewEntity3(MonoString* name, EntityID parentEntityID)
{
    return Application::Instance->GetCurrentScene()->CreateEntity(mono_string_to_utf8(name), parentEntityID);
}

bool EntityInternalCalls::Entity_DestroyEntity(EntityID id)
{
    Application::Instance->GetCurrentScene()->DestroyEntity(id);
    return true;
}

bool EntityInternalCalls::Entity_AddComponent(EntityID id, void* type)
{
    if (!Application::Instance->GetCurrentScene()->GetEntitiesRegistry()->EntityExists(id))
    {
        Log::LogError("Error getting entity by ID " + std::to_string(id));
        return false;
    }

    MonoType* monoType = mono_reflection_type_get_type((MonoReflectionType*)type);
    if (monoType == nullptr)
    {
        Log::LogError("Error getting mono type for entity ID " + std::to_string(id));
        return false;
    }

    MonoClass* monoClass = mono_class_from_mono_type(monoType);
    if (monoClass == nullptr)
    {
        Log::LogError("Error converting mono type to mono class: " + std::string(mono_type_get_name(monoType)));
        return false;
    }

    bool success = false;
    auto& component = ScriptingCore::AddComponentFromMonoClass(id, monoClass, success);
    if (!success)
    {
        Log::LogError("Error adding component " + std::string(mono_type_get_name(monoType)));
        return false;
    }

    return true;
}

bool EntityInternalCalls::Entity_AddScriptComponent(EntityID id, void* type, ScriptPointer scriptPointer)
{
    if (HasComponentS<ScriptComponent>(id))
        return false;

    MonoType* monoType = mono_reflection_type_get_type((MonoReflectionType*)type);
    auto& scriptComponent = AddComponentS<ScriptComponent>(id);
    scriptComponent.Init(mono_type_get_name(monoType), scriptPointer);

    return true;
}

bool EntityInternalCalls::Entity_HasComponent(EntityID id, void* type)
{
    MonoType* monoType = mono_reflection_type_get_type((MonoReflectionType*)type);
    if (monoType == nullptr)
    {
        Log::LogError("Error getting mono type for entity ID " + std::to_string(id));
        return false;
    }

    MonoClass* monoClass = mono_class_from_mono_type(monoType);
    if (monoClass == nullptr)
    {
        Log::LogError("Error converting mono type to mono class: " + std::string(mono_type_get_name(monoType)));
        return false;
    }

    return ScriptingCore::HasComponentFromMonoClass(id, monoClass);
}

ScriptPointer EntityInternalCalls::Entity_GetScriptComponent(EntityID id, void* type)
{
    if (!HasComponentS<ScriptComponent>(id))
        return NULL;

    //MonoType* monoType = mono_reflection_type_get_type((MonoReflectionType*)type);
    // TODO: won't work for multiple scripts

    auto& scriptComponent = GetComponentS<ScriptComponent>(id);

    return scriptComponent.GetScriptPointer();
}

bool EntityInternalCalls::Entity_RemoveComponent(EntityID id, void* type)
{
    MonoType* monoType = mono_reflection_type_get_type((MonoReflectionType*)type);
    if (monoType == nullptr)
    {
        Log::LogError("Error getting mono type for entity ID " + std::to_string(id));
        return false;
    }

    MonoClass* monoClass = mono_class_from_mono_type(monoType);
    if (monoClass == nullptr)
    {
        Log::LogError("Error converting mono type to mono class: " + std::string(mono_type_get_name(monoType)));
        return false;
    }

    return ScriptingCore::RemoveComponentFromMonoClass(id, monoClass);
}

ScriptPointer EntityInternalCalls::Entity_RemoveScriptComponent(EntityID id, void* type)
{
    if (!HasComponentS<ScriptComponent>(id))
        return NULL;

    //MonoType* monoType = mono_reflection_type_get_type((MonoReflectionType*)type);
    // TODO: won't work for multiple scripts

    ScriptPointer scriptPointer = GetComponentS<ScriptComponent>(id).GetScriptPointer();
    RemoveComponentS<ScriptComponent>(id);

    return scriptPointer;
}

bool EntityInternalCalls::Entity_GetIsActive(EntityID entityID)
{
    auto registry = Application::Instance->GetCurrentScene()->GetEntitiesRegistry();
    return registry->EntityGetState(entityID) & EntityStates::IsActive;
}

bool EntityInternalCalls::Entity_GetIsActiveSelf(EntityID entityID)
{
    auto registry = Application::Instance->GetCurrentScene()->GetEntitiesRegistry();
    return registry->EntityGetState(entityID) & EntityStates::IsActiveSelf;
}

void EntityInternalCalls::Entity_SetIsActiveSelf(EntityID entityID, bool isActiveSelf)
{
    auto registry = Application::Instance->GetCurrentScene()->GetEntitiesRegistry();
    registry->EntitySetActive(entityID, isActiveSelf, true);
}

bool EntityInternalCalls::Entity_IsDestroyed(EntityID entityID)
{
    return !Application::Instance->GetCurrentScene()->GetEntitiesRegistry()->EntityExists(entityID);
}

MonoString* EntityInternalCalls::Entity_GetName(EntityID id)
{
    if (!HasComponentS<NameComponent>(id))
        return nullptr;

    return mono_string_new(mono_domain_get(), GetComponentS<NameComponent>(id).Name);
}

void EntityInternalCalls::Entity_SetName(EntityID id, MonoString* name)
{
    AddComponentS<NameComponent>(id).Name = mono_string_to_utf8(name);
}

MonoArray* EntityInternalCalls::Component_FindAllOfType(void* type)
{
    MonoType* monoType = mono_reflection_type_get_type((MonoReflectionType*)type);
    if (monoType == nullptr)
    {
        Log::LogError("Error getting mono type for find");
        return nullptr;
    }

    MonoClass* monoClass = mono_class_from_mono_type(monoType);
    if (monoClass == nullptr)
    {
        Log::LogError("Error converting mono type to mono class: " + std::string(mono_type_get_name(monoType)));
        return nullptr;
    }

    return ScriptingCore::ToMonoUInt32Array(ScriptingCore::ComponentOwnersFromMonoClass(monoClass));
}

MonoArray* EntityInternalCalls::Component_FindAllScriptsOfType(EntityID id, void* type)
{
    // TODO: not implemented
    Log::LogWarning("Finding all components of ScriptComponent type is not supported yet");

    return nullptr;
}
