#include "ComponentsInternalCalls.h"
#include "InternalCallsCommon.h"
#include "../Animation/Animator.h"
#include "../Audio/AudioSource.h"
#include "../Audio/AudioListener.h"
#include "../Core/Application.h"
#include "../Physics/BoxCollider.h"
#include "../Physics/CircleCollider.h"
#include "../Rendering/SpriteRenderer.h"
#include "../Rendering/Camera.h"
#include "../Scene/Hierarchy.h"
#include "../Scene/HierarchyNode.h"
#include "../Scene/Transformation.h"
#include "../Scene/SceneHelper.h"
#include "../Scripting/ScriptingCore.h"

glm::vec3 ComponentsInternalCalls::Transformation_GetPosition(EntityID entityID)
{
    GET_COMPONENT_OR_RETURN(Transformation, glm::vec3(0.0f))

    return component.GetPosition();
}

void ComponentsInternalCalls::Transformation_SetPosition(EntityID entityID, glm::vec3 position)
{
    GET_COMPONENT_OR_RETURN(Transformation, )

    component.SetPosition(position);
}

glm::vec3 ComponentsInternalCalls::Transformation_GetRotation(EntityID entityID)
{
    GET_COMPONENT_OR_RETURN(Transformation, glm::vec3(0.0f))

    return component.GetRotation();
}

void ComponentsInternalCalls::Transformation_SetRotation(EntityID entityID, glm::vec3 rotation)
{
    GET_COMPONENT_OR_RETURN(Transformation, )

    component.SetRotation(rotation);
}

glm::vec3 ComponentsInternalCalls::Transformation_GetScale(EntityID entityID)
{
    GET_COMPONENT_OR_RETURN(Transformation, glm::vec3(0.0f))

    return component.GetScale();
}

void ComponentsInternalCalls::Transformation_SetScale(EntityID entityID, glm::vec3 scale)
{
    GET_COMPONENT_OR_RETURN(Transformation, )

    component.SetScale(scale);
}

EntityID ComponentsInternalCalls::HierarchyNode_GetParent(EntityID entityID)
{
    GET_COMPONENT_OR_RETURN(HierarchyNode, NULL_ENTITY)

    return component.ParentNode;
}

void ComponentsInternalCalls::HierarchyNode_SetParent(EntityID entityID, EntityID parentEntityID)
{
    auto registry = Application::Instance->GetCurrentScene()->GetEntitiesRegistry();
    LinkChildToParent(registry, entityID, parentEntityID);
}

MonoArray* ComponentsInternalCalls::HierarchyNode_GetChildren(EntityID entityID)
{
    auto registry = Application::Instance->GetCurrentScene()->GetEntitiesRegistry();
    return ScriptingCore::ToMonoUInt32Array(GetAllChildren(registry, entityID));
}

float ComponentsInternalCalls::AudioListener_GetVolume(EntityID entityID)
{
    GET_COMPONENT_OR_RETURN(AudioListener, 0.0f)

    return component.GetVolume();
}

void ComponentsInternalCalls::AudioListener_SetVolume(EntityID entityID, float volume)
{
    GET_COMPONENT_OR_RETURN(AudioListener, )

    component.SetVolume(volume);
}

float ComponentsInternalCalls::AudioSource_GetVolume(EntityID entityID)
{
    GET_COMPONENT_OR_RETURN(AudioSource, 0.0f)

    return component.GetVolume();
}

void ComponentsInternalCalls::AudioSource_SetVolume(EntityID entityID, float volume)
{
    GET_COMPONENT_OR_RETURN(AudioSource, )

    component.SetVolume(volume);
}

bool ComponentsInternalCalls::AudioSource_GetLoop(EntityID entityID)
{
    GET_COMPONENT_OR_RETURN(AudioSource, false)

    return component.GetIsLoop();
}

void ComponentsInternalCalls::AudioSource_SetLoop(EntityID entityID, bool loop)
{
    GET_COMPONENT_OR_RETURN(AudioSource, )

    component.SetIsLoop(loop);
}

void ComponentsInternalCalls::AudioSource_Play(EntityID entityID, ResourceID audioTrackID)
{
    GET_COMPONENT_OR_RETURN(AudioSource, )

    component.Play(Application::Instance->GetResourcesManager()->GetAudioTrack(audioTrackID));
}

void ComponentsInternalCalls::AudioSource_Stop(EntityID entityID)
{
    GET_COMPONENT_OR_RETURN(AudioSource, )

    component.Stop();
}

ResourceID ComponentsInternalCalls::SpriteRenderer_GetSprite(EntityID entityID)
{
    GET_COMPONENT_OR_RETURN(SpriteRenderer, NULL_RESOURCE)
    auto image = component.GetImage();

    return image == nullptr ? 0 : image->ID;
}

void ComponentsInternalCalls::SpriteRenderer_SetSprite(EntityID entityID, ResourceID spriteID)
{
    GET_COMPONENT_OR_RETURN(SpriteRenderer, )

    component.SetImage(Application::Instance->GetResourcesManager()->GetImage(spriteID));
}

void ComponentsInternalCalls::Animator_PlayAnimation(EntityID entityID, ResourceID animationID)
{
    GET_COMPONENT_OR_RETURN(Animator, )

    auto animation = Application::Instance->GetResourcesManager()->GetAnimation(animationID);
    if (animation == nullptr)
    {
        Log::LogError("Animation does not exist");
        return;
    }

    // TODO: rework API
    component.Animations.resize(1);
    component.Animations[0] = animation;
    component.Play(0);
}

void ComponentsInternalCalls::Animator_Play(EntityID entityID)
{
    GET_COMPONENT_OR_RETURN(Animator, )

    component.Play();
}

void ComponentsInternalCalls::Animator_Pause(EntityID entityID)
{
    GET_COMPONENT_OR_RETURN(Animator, )

    component.Pause();
}

void ComponentsInternalCalls::Animator_Stop(EntityID entityID)
{
    GET_COMPONENT_OR_RETURN(Animator, )

    component.Stop();
}

void ComponentsInternalCalls::Animator_Restart(EntityID entityID)
{
    GET_COMPONENT_OR_RETURN(Animator, )

    component.Restart();
}

EntityID ComponentsInternalCalls::Camera_GetEntityWithMainCamera()
{
    return Application::Instance->GetCurrentScene()->GetMainCamera().Owner;
}

float ComponentsInternalCalls::Camera_GetWidth(EntityID entityID)
{
    GET_COMPONENT_OR_RETURN(Camera, 0.0f)

    return component.GetWidth();
}

void ComponentsInternalCalls::Camera_SetWidth(EntityID entityID, float width)
{
    GET_COMPONENT_OR_RETURN(Camera, )

    component.SetWidth(width);
}

float ComponentsInternalCalls::Camera_GetHeight(EntityID entityID)
{
    GET_COMPONENT_OR_RETURN(Camera, 0.0f)

    return component.GetHeight();
}

void ComponentsInternalCalls::Camera_SetHeight(EntityID entityID, float height)
{
    GET_COMPONENT_OR_RETURN(Camera, )

    component.SetHeight(height);
}

float ComponentsInternalCalls::Camera_GetNearClippingPlane(EntityID entityID)
{
    GET_COMPONENT_OR_RETURN(Camera, 0.0f)

    return component.GetNearClippingPlane();
}

void ComponentsInternalCalls::Camera_SetNearClippingPlane(EntityID entityID, float distance)
{
    GET_COMPONENT_OR_RETURN(Camera, )

    component.SetNearClippingPlane(distance);
}

float ComponentsInternalCalls::Camera_GetFarClippingPlane(EntityID entityID)
{
    GET_COMPONENT_OR_RETURN(Camera, 0.0f)

    return component.GetFarClippingPlane();
}

void ComponentsInternalCalls::Camera_SetFarClippingPlane(EntityID entityID, float distance)
{
    GET_COMPONENT_OR_RETURN(Camera, )

    component.SetFarClippingPlane(distance);
}

CameraResizeModes::CameraResizeMode ComponentsInternalCalls::Camera_GetResizingMode(EntityID entityID)
{
    GET_COMPONENT_OR_RETURN(Camera, (CameraResizeModes::CameraResizeMode)0)

    return component.GetResizeMode();
}

void ComponentsInternalCalls::Camera_SetResizingMode(EntityID entityID, CameraResizeModes::CameraResizeMode mode)
{
    GET_COMPONENT_OR_RETURN(Camera, )

    component.SetResizeMode(mode);
}

void ComponentsInternalCalls::Camera_WorldToScreenPoint(EntityID entityID, glm::vec2* worldPoint, glm::vec2* screenPoint)
{
    GET_COMPONENT_OR_RETURN(Camera, )

    glm::vec2 result = component.WorldToScreenPoint(*worldPoint);
    screenPoint->x = result.x;
    screenPoint->y = result.y;
}

void ComponentsInternalCalls::Camera_ScreenToWorldPoint(EntityID entityID, glm::vec2* screenPoint, glm::vec2* worldPoint)
{
    GET_COMPONENT_OR_RETURN(Camera, )

    glm::vec2 result = component.ScreenToWorldPoint(*screenPoint);
    worldPoint->x = result.x;
    worldPoint->y = result.y;
}

float ComponentsInternalCalls::RigidBody_GetMass(EntityID entityID)
{
    GET_COMPONENT_OR_RETURN(RigidBody, 0.0f)

    return component.GetMass();
}

void ComponentsInternalCalls::RigidBody_SetMass(EntityID entityID, float mass)
{
    GET_COMPONENT_OR_RETURN(RigidBody, )

    component.SetMass(mass);
}

RigidBodyTypes::RigidBodyType ComponentsInternalCalls::RigidBody_GetRigidBodyType(EntityID entityID)
{
    GET_COMPONENT_OR_RETURN(RigidBody, (RigidBodyTypes::RigidBodyType)0)

    return component.GetType();
}

void ComponentsInternalCalls::RigidBody_SetRigidBodyType(EntityID entityID, RigidBodyTypes::RigidBodyType type)
{
    GET_COMPONENT_OR_RETURN(RigidBody, )

    component.SetType(type);
}

void ComponentsInternalCalls::BoxCollider_GetSize(EntityID entityID, glm::vec2* size)
{
    GET_COMPONENT_OR_RETURN(BoxCollider, )

    auto s = component.GetSize();
    size->x = s.x;
    size->y = s.y;
}

void ComponentsInternalCalls::BoxCollider_SetSize(EntityID entityID, glm::vec2* size)
{
    GET_COMPONENT_OR_RETURN(BoxCollider, )

    component.SetSize(*size);
}

float ComponentsInternalCalls::CircleCollider_GetRadius(EntityID entityID)
{
    GET_COMPONENT_OR_RETURN(CircleCollider, 0.0f)

    return component.GetRadius();
}

void ComponentsInternalCalls::CircleCollider_SetRadius(EntityID entityID, float radius)
{
    GET_COMPONENT_OR_RETURN(CircleCollider, )

    component.SetRadius(radius);
}
