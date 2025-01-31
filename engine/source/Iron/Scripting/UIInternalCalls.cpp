#include <mono/jit/jit.h>

#include "UIInternalCalls.h"
#include "InternalCallsCommon.h"
#include "../Core/Log.h"
#include "../Core/Application.h"
#include "../Scene/SceneHelper.h"
#include "../UI/UIElements/UIButton.h"
#include "../UI/UIElements/UIText.h"

void UIInternalCalls::RectTransformation_GetAnchorMin(EntityID entityID, glm::vec2* anchor)
{
    GET_COMPONENT_OR_RETURN(RectTransformation, )

    anchor->x = component.GetAnchorMin().x;
    anchor->y = component.GetAnchorMin().y;
}

void UIInternalCalls::RectTransformation_SetAnchorMin(EntityID entityID, glm::vec2* anchor)
{
    GET_COMPONENT_OR_RETURN(RectTransformation, )

    component.SetAnchorMin(*anchor);
}

void UIInternalCalls::RectTransformation_GetAnchorMax(EntityID entityID, glm::vec2* anchor)
{
    GET_COMPONENT_OR_RETURN(RectTransformation, )

    anchor->x = component.GetAnchorMax().x;
    anchor->y = component.GetAnchorMax().y;
}

void UIInternalCalls::RectTransformation_SetAnchorMax(EntityID entityID, glm::vec2* anchor)
{
    GET_COMPONENT_OR_RETURN(RectTransformation, )

    component.SetAnchorMax(*anchor);
}

void UIInternalCalls::RectTransformation_GetAnchoredPosition(EntityID entityID, glm::vec2* position)
{
    GET_COMPONENT_OR_RETURN(RectTransformation, )

    position->x = component.GetAnchoredPosition().x;
    position->y = component.GetAnchoredPosition().y;
}

void UIInternalCalls::RectTransformation_SetAnchoredPosition(EntityID entityID, glm::vec2* position)
{
    GET_COMPONENT_OR_RETURN(RectTransformation, )

    component.SetAnchoredPosition(*position);
}

void UIInternalCalls::RectTransformation_GetOffsetMin(EntityID entityID, glm::vec2* offset)
{
    GET_COMPONENT_OR_RETURN(RectTransformation, )

    offset->x = component.GetOffsetMin().x;
    offset->y = component.GetOffsetMin().y;
}

void UIInternalCalls::RectTransformation_SetOffsetMin(EntityID entityID, glm::vec2* offset)
{
    GET_COMPONENT_OR_RETURN(RectTransformation, )

    component.SetOffsetMin(*offset);
}

void UIInternalCalls::RectTransformation_GetOffsetMax(EntityID entityID, glm::vec2* offset)
{
    GET_COMPONENT_OR_RETURN(RectTransformation, )

    offset->x = component.GetOffsetMax().x;
    offset->y = component.GetOffsetMax().y;
}

void UIInternalCalls::RectTransformation_SetOffsetMax(EntityID entityID, glm::vec2* offset)
{
    GET_COMPONENT_OR_RETURN(RectTransformation, )

    component.SetOffsetMax(*offset);
}

void UIInternalCalls::RectTransformation_GetPivot(EntityID entityID, glm::vec2* pivot)
{
    GET_COMPONENT_OR_RETURN(RectTransformation, )

    pivot->x = component.GetPivot().x;
    pivot->y = component.GetPivot().y;
}

void UIInternalCalls::RectTransformation_SetPivot(EntityID entityID, glm::vec2* pivot)
{
    GET_COMPONENT_OR_RETURN(RectTransformation, )

    component.SetPivot(*pivot);
}

void UIInternalCalls::RectTransformation_GetSize(EntityID entityID, glm::vec2* size)
{
    GET_COMPONENT_OR_RETURN(RectTransformation, )

    size->x = component.GetSize().x;
    size->y = component.GetSize().y;
}

void UIInternalCalls::RectTransformation_SetSize(EntityID entityID, glm::vec2* size)
{
    GET_COMPONENT_OR_RETURN(RectTransformation, )

    component.SetSize(*size);
}

float UIInternalCalls::RectTransformation_GetSortingOrder(EntityID entityID)
{
    GET_COMPONENT_OR_RETURN(RectTransformation, 0.0f)

    return component.GetSortingOrder();
}

void UIInternalCalls::RectTransformation_SetSortingOrder(EntityID entityID, float sortingOrder)
{
    GET_COMPONENT_OR_RETURN(RectTransformation, )

    component.SetSortingOrder(sortingOrder);
}

glm::vec3 UIInternalCalls::RectTransformation_GetRotation(EntityID entityID)
{
    GET_COMPONENT_OR_RETURN(RectTransformation, glm::vec3(0.0f))

    return component.GetRotation();
}

void UIInternalCalls::RectTransformation_SetRotation(EntityID entityID, glm::vec3 rotation)
{
    GET_COMPONENT_OR_RETURN(RectTransformation, )

    component.SetRotation(rotation);
}

ResourceID UIInternalCalls::UIImage_GetSprite(EntityID entityID)
{
    GET_COMPONENT_OR_RETURN(UIImage, 0)
    auto image = component.GetImage();

    return image == nullptr ? 0 : image->ID;
}

void UIInternalCalls::UIImage_SetSprite(EntityID entityID, ResourceID spriteID)
{
    GET_COMPONENT_OR_RETURN(UIImage, )

    component.SetImage(Application::Instance->GetResourcesManager()->GetImage(spriteID));
}

ResourceID UIInternalCalls::UIButton_GetSprite(EntityID entityID)
{
    GET_COMPONENT_OR_RETURN(UIButton, 0)
    auto image = component.GetImage();

    return image == nullptr ? 0 : image->ID;
}

void UIInternalCalls::UIButton_SetSprite(EntityID entityID, ResourceID spriteID)
{
    GET_COMPONENT_OR_RETURN(UIButton, )

    component.SetImage(Application::Instance->GetResourcesManager()->GetImage(spriteID));
}

bool UIInternalCalls::UIButton_GetInteractable(EntityID entityID)
{
    GET_COMPONENT_OR_RETURN(UIButton, false)

    return component.GetInteractable();
}

void UIInternalCalls::UIButton_SetInteractable(EntityID entityID, bool interactable)
{
    GET_COMPONENT_OR_RETURN(UIButton, )

    component.SetInteractable(interactable);
}

ButtonTransitionsInfo UIInternalCalls::UIButton_GetTransition(EntityID entityID)
{
    GET_COMPONENT_OR_RETURN(UIButton, ButtonTransitionsInfo())

    return component.GetTransitionsInfo();
}

void UIInternalCalls::UIButton_SetTransition(EntityID entityID, ButtonTransitionsInfo info)
{
    GET_COMPONENT_OR_RETURN(UIButton, )

    component.SetTransitionsInfo(info);
}

MonoString* UIInternalCalls::UIText_GetText(EntityID entityID)
{
    GET_COMPONENT_OR_RETURN(UIText, nullptr)

    return mono_string_new_utf16(mono_domain_get(), component.GetText().c_str(), component.GetText().size());
}

void UIInternalCalls::UIText_SetText(EntityID entityID, MonoString* text)
{
    GET_COMPONENT_OR_RETURN(UIText, )

    component.SetText(mono_string_to_utf16(text));
}

int UIInternalCalls::UIText_GetTextSize(EntityID entityID)
{
    GET_COMPONENT_OR_RETURN(UIText, 0)

    return component.GetTextSize();
}

void UIInternalCalls::UIText_SetTextSize(EntityID entityID, int textSize)
{
    GET_COMPONENT_OR_RETURN(UIText, )

    component.SetTextSize(textSize);
}

glm::vec4 UIInternalCalls::UIText_GetColor(EntityID entityID)
{
    GET_COMPONENT_OR_RETURN(UIText, glm::vec4(0.0f))

    return component.GetColor();
}

void UIInternalCalls::UIText_SetColor(EntityID entityID, glm::vec4 color)
{
    GET_COMPONENT_OR_RETURN(UIText, )

    component.SetColor(color);
}

bool UIInternalCalls::UIButton_GetIsTextAutoSize(EntityID entityID)
{
    GET_COMPONENT_OR_RETURN(UIText, 0)

    return component.GetIsTextAutoSize();
}

void UIInternalCalls::UIButton_SetIsTextAutoSize(EntityID entityID, bool isAutoSize)
{
    GET_COMPONENT_OR_RETURN(UIText, )

    component.SetIsTextAutoSize(isAutoSize);
}

bool UIInternalCalls::UIButton_GetTextAlignment(EntityID entityID)
{
    GET_COMPONENT_OR_RETURN(UIText, 0)

    return component.GetTextAlignment();
}

void UIInternalCalls::UIButton_SetTextAlignment(EntityID entityID, AlignmentTypes::AlignmentType alignmentType)
{
    GET_COMPONENT_OR_RETURN(UIText, )

    component.SetTextAlignment(alignmentType);
}

EntityID UIInternalCalls::UI_CreateUIElement()
{
    return Application::Instance->GetCurrentScene()->GetUILayer()->CreateUIElement();
}

EntityID UIInternalCalls::UI_CreateUIElement2(MonoString* name)
{
    return Application::Instance->GetCurrentScene()->GetUILayer()->CreateUIElement(mono_string_to_utf8(name), NULL_ENTITY);
}

EntityID UIInternalCalls::UI_CreateUIElement3(MonoString* name, EntityID parentEntityID)
{
    return Application::Instance->GetCurrentScene()->GetUILayer()->CreateUIElement(mono_string_to_utf8(name), parentEntityID);
}

bool UIInternalCalls::UI_IsPointerOverUI()
{
    return Application::Instance->GetCurrentScene()->GetUILayer()->IsPointerOverUI();
}
