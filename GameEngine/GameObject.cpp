#include "GameObject.h"

GameObject::GameObject()
{
	mParent = nullptr;
	transform = (ComponentTransform*)NewComponent(ComponentType::TRANSFORM);
	NewComponent(ComponentType::MESH);

}

GameObject::GameObject(std::string name) : _name(name)
{
}

GameObject::~GameObject()
{
}

void GameObject::NewChild(GameObject* go)
{
	go->SetParent(this);
	mChildren.push_back(go);
}

Component* GameObject::NewComponent(ComponentType type)
{
	Component* component = nullptr;

	switch (type)
	{
	case ComponentType::UNKNOWN:
		break;
	case ComponentType::TRANSFORM:
		component = new ComponentTransform(this);
		break;
	case ComponentType::MESH:
		component = new ComponentMesh(this);
		break;
	case ComponentType::MATERIAL:
		break;
	case ComponentType::LIGHT:
		break;
	case ComponentType::CAMERA:
		component = new ComponentCamera(this);
	default:
		break;
	}

	if (!CheckComponent(type))
		mComponents.push_back(component);
	else
		LOG("Can't create duplicate Component");

	return component; 
}

void GameObject::SetParent(GameObject* parent)
{
	this->mParent = parent; 
}

void GameObject::Reparent(GameObject* newParent) {
	if (newParent != nullptr) {
		mParent->RemoveChild(this);
		mParent = newParent; 
		newParent->NewChild(this);
	}
}

void GameObject::RemoveChild(GameObject* child)
{
	for (uint i = 0; i < mChildren.size(); i++) {
		if (mChildren[i] == child) {
			mChildren.erase(mChildren.begin() + i);
		}
	}
}

void GameObject::ChangeName(std::string name)
{
	_name = name;
}

void GameObject::PrintInspector()
{
	char newName[255]; 
	//Change name, available for all objects, including scene
	strcpy(newName, _name.c_str());
	ImGui::BulletText("Name: ");
	ImGui::SameLine();
	ImGui::InputText("##Name", newName, 255, ImGuiInputTextFlags_EnterReturnsTrue);

	if (ImGui::IsKeyDown(ImGuiKey_Enter))
		_name = newName;

	if (mParent != nullptr) {
		//Components on inspector
		for (uint i = 0; i < mComponents.size(); i++) {
			ImGui::Separator();
			mComponents[i]->OnInspector();
		}
		ImGui::Separator();
	}
}

bool GameObject::CheckComponent(ComponentType type)
{
	bool ret = false;

	for (int i = 0; i < mComponents.size(); i++) {

		if (mComponents.at(i)->_type == type) ret = true;
	}

	return ret;
}

void GameObject::Inspector()
{
	for (int i = 0; i < mComponents.size(); i++) {

		mComponents.at(i)->OnInspector();
	}
}

void GameObject::RemoveComponent(Component* component) {
	mComponents.erase(std::find(mComponents.begin(), mComponents.end(), component));
}
