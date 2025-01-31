#pragma once

#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

#include "../EntityComponentSystem/Component.h"
#include "../EntityComponentSystem/EntitiesRegistry.h"
#include "HierarchyNode.h"

class Transformation : public Component
{
public:
    explicit Transformation(EntityID ownerEntityID);

    virtual glm::vec3 GetPosition();
    virtual void SetPosition(const glm::vec3& position);
    glm::vec3 GetRotation();
    void SetRotation(const glm::vec3& rotation);
    glm::vec3 GetScale();
    void SetScale(const glm::vec3& scale);

    virtual glm::vec3 GetLocalPosition() const;
    virtual void SetLocalPosition(const glm::vec3& position);
    glm::vec3 GetLocalRotation() const;
    void SetLocalRotation(const glm::vec3& rotation);
    glm::vec3 GetLocalScale() const;
    void SetLocalScale(const glm::vec3& scale);

    virtual const glm::mat4& GetTransformationMatrixCached();
    virtual void UpdateTransformation(ComponentAccessor<Transformation>& transformationsAccessor, HierarchyNode& hierarchyNode);
    virtual const glm::mat4& GetTransformationMatrix();
    virtual const glm::mat4& GetInverseTransformationMatrix();
    float GetGlobalSortingOrderCached() const;

    // Did anything in transformation change in this frame
    bool DidTransformationChange() const;
    void SetTransformationChanged(bool changed);

private:
    glm::mat4 _transformationMatrix = glm::mat4(1.0f);
    glm::mat4 _inverseTransformationMatrix = glm::mat4(1.0f);

    glm::vec3 _position = { 0.0f, 0.0f, 0.0f };
    glm::vec3 _rotation = { 0.0f, 0.0f, 0.0f };
    glm::vec3 _scale = { 1.0f, 1.0f, 1.0f };
    glm::vec3 _localPosition = { 0.0f, 0.0f, 0.0f };
    glm::vec3 _localRotation = { 0.0f, 0.0f, 0.0f };
    glm::vec3 _localScale = { 1.0f, 1.0f, 1.0f };

    bool transformationChanged = true;
};
