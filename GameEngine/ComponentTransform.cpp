#include "ComponentTransform.h"

ComponentTransform::ComponentTransform(GameObject* owner) : Component(ComponentType::TRANSFORM, owner)
{
	globalTransform.SetIdentity();
	localTransform.SetIdentity();

	position.Set(0.0f, 0.0f, 0.0f);
	rotation.Set(0.0f, 0.0f, 0.0f);
	scale.Set(0.0f, 0.0f, 0.0f);
}

ComponentTransform::~ComponentTransform()
{
}

void ComponentTransform::OnInspector()
{
	if (ImGui::CollapsingHeader("Local Transformation", ImGuiTreeNodeFlags_DefaultOpen))
	{
		ImGui::DragFloat3("Position", position.ptr(), 0.2f);
		ImGui::DragFloat3("Rotation", rotation.ptr(), 0.2f);
		ImGui::DragFloat3("Scale", scale.ptr(), 0.2f);
	}
}

float3 ComponentTransform::GetX()
{
	return globalTransform.RotatePart().Col(0).Normalized();
}

float3 ComponentTransform::GetY()
{
	return globalTransform.RotatePart().Col(1).Normalized();
}

float3 ComponentTransform::GetZ()
{
	return globalTransform.RotatePart().Col(2).Normalized();
}
