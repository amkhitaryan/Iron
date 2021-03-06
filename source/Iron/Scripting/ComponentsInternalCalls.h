#pragma once

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include "../Physics/RigidBody.h"

namespace ComponentsInternalCalls
{
    // Transformation
    glm::vec3 Transformation_GetPosition(int64_t entityID);
    void Transformation_SetPosition(int64_t entityID, glm::vec3 position);
    glm::vec3 Transformation_GetRotation(int64_t entityID);
    void Transformation_SetRotation(int64_t entityID, glm::vec3 rotation);
    glm::vec3 Transformation_GetScale(int64_t entityID);
    void Transformation_SetScale(int64_t entityID, glm::vec3 scale);

    // Audio
    float AudioListener_GetVolume(int64_t entityID);
    void AudioListener_SetVolume(int64_t entityID, float volume);
    float AudioSource_GetVolume(int64_t entityID);
    void AudioSource_SetVolume(int64_t entityID, float volume);
    bool AudioSource_GetLoop(int64_t entityID);
    void AudioSource_SetLoop(int64_t entityID, bool loop);
    void AudioSource_Play(int64_t entityID, int64_t audioTrackID);
    void AudioSource_Stop(int64_t entityID);

    // Sprite Renderer
    uint64_t SpriteRenderer_GetSprite(int64_t entityID);
    void SpriteRenderer_SetSprite(int64_t entityID, int64_t spriteID);

    // Animator
    void Animator_PlayAnimation(int64_t entityID, int64_t animationID);
    void Animator_Play(int64_t entityID);
    void Animator_Pause(int64_t entityID);
    void Animator_Stop(int64_t entityID);
    void Animator_Restart(int64_t entityID);

    // Camera
    int64_t Camera_GetMainEntityWithMainCamera();
    float Camera_GetWidth(int64_t entityID);
    void Camera_SetWidth(int64_t entityID, float width);
    float Camera_GetHeight(int64_t entityID);
    void Camera_SetHeight(int64_t entityID, float height);
    float Camera_GetNearClippingPlane(int64_t entityID);
    void Camera_SetNearClippingPlane(int64_t entityID, float distance);
    float Camera_GetFarClippingPlane(int64_t entityID);
    void Camera_SetFarClippingPlane(int64_t entityID, float distance);
    int Camera_GetResizingMode(int64_t entityID);
    void Camera_SetResizingMode(int64_t entityID, int mode);
    void Camera_WorldToScreenPoint(int64_t entityID, glm::vec2* worldPoint, glm::vec2* screenPoint);
    void Camera_ScreenToWorldPoint(int64_t entityID, glm::vec2* screenPoint, glm::vec2* worldPoint);

    // Physics
    float RigidBody_GetMass(int64_t entityID);
    void RigidBody_SetMass(int64_t entityID, float mass);
    RigidBodyTypes::RigidBodyType RigidBody_GetRigidBodyType(int64_t entityID);
    void RigidBody_SetRigidBodyType(int64_t entityID, RigidBodyTypes::RigidBodyType type);
    void BoxCollider_GetSize(int64_t entityID, glm::vec2* size);
    void BoxCollider_SetSize(int64_t entityID, glm::vec2* size);
}
