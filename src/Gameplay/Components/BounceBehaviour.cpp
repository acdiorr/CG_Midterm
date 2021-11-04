#include "Gameplay/Components/BounceBehaviour.h"
#include "Gameplay/Components/ComponentManager.h"
#include "Gameplay/GameObject.h"

BounceBehaviour::BounceBehaviour() :
	IComponent(),
	_renderer(nullptr),
	EnterMaterial(nullptr),
	ExitMaterial(nullptr)
{ }
BounceBehaviour::~BounceBehaviour() = default;

// Grabbing specific names of triggers to activate them (Putting them together does not work, have to invoke individually)
void BounceBehaviour::OnEnteredTrigger(const Gameplay::Physics::TriggerVolume::Sptr & trigger) {
	if (trigger->GetGameObject()->Name == "topB") {
		_body->ApplyImpulse(10.0f * (glm::normalize(-1.0f * (_body->GetVelocity()))));
	}
	if (trigger->GetGameObject()->Name == "bottomB") {
		_body->ApplyImpulse(10.0f * (glm::normalize(-1.0f * (_body->GetVelocity()))));
	}
	if (trigger->GetGameObject()->Name == "leftTB") {
		_body->ApplyImpulse(10.0f * (glm::normalize(-1.0f * (_body->GetVelocity()))));
	}
	if (trigger->GetGameObject()->Name == "leftBB") {
		_body->ApplyImpulse(10.0f * (glm::normalize(-1.0f * (_body->GetVelocity()))));
	}
	if (trigger->GetGameObject()->Name == "rightTB") {
		_body->ApplyImpulse(10.0f * (glm::normalize(-1.0f * (_body->GetVelocity()))));
	}
	if (trigger->GetGameObject()->Name == "rightBB") {
		_body->ApplyImpulse(10.0f * (glm::normalize(-1.0f * (_body->GetVelocity()))));
	}
	/* Doesn't work correctly (Launching off the paddle almost unpredictable)
	if (trigger->GetGameObject()->Name == "Paddle1") {
		_body->ApplyImpulse(5.0f * (glm::normalize(glm::vec3(-1.0f, -1.0f, 0.0f) * (_body->GetVelocity()))));
	}
	if (trigger->GetGameObject()->Name == "Paddle2") {
		_body->ApplyImpulse(5.0f * (glm::normalize(glm::vec3(-1.0f, -1.0f, 0.0f) * (_body->GetVelocity()))));
	}
	*/
}

void BounceBehaviour::OnLeavingTrigger(const Gameplay::Physics::TriggerVolume::Sptr & trigger) {
	if (_renderer && ExitMaterial) {
		_renderer->SetMaterial(ExitMaterial);
	}
	LOG_INFO("Exitting Trigger {}", trigger->GetGameObject()->Name);
}

void BounceBehaviour::Awake() {
	_renderer = GetComponent<RenderComponent>();
	_body = GetComponent<Gameplay::Physics::RigidBody>();
	if (_body == nullptr) {
		IsEnabled = false;
	}
}

void BounceBehaviour::RenderImGui() { }

nlohmann::json BounceBehaviour::ToJson() const {
	return {
		{ "enter_material", EnterMaterial != nullptr ? EnterMaterial->GetGUID().str() : "null" },
		{ "exit_material", ExitMaterial != nullptr ? ExitMaterial->GetGUID().str() : "null" }
	};
}

BounceBehaviour::Sptr BounceBehaviour::FromJson(const nlohmann::json & blob) {
	BounceBehaviour::Sptr result = std::make_shared<BounceBehaviour>();
	result->EnterMaterial = ResourceManager::Get<Gameplay::Material>(Guid(blob["enter_material"]));
	result->ExitMaterial = ResourceManager::Get<Gameplay::Material>(Guid(blob["exit_material"]));
	return result;
}
