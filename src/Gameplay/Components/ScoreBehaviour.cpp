#include "Gameplay/Components/ScoreBehaviour.h"
#include "Gameplay/Components/ComponentManager.h"
#include "Gameplay/GameObject.h"

ScoreBehaviour::ScoreBehaviour() : 
	IComponent(),
	_renderer(nullptr),
	EnterMaterial(nullptr),
	ExitMaterial(nullptr)
{ }
ScoreBehaviour::~ScoreBehaviour() = default;

void ScoreBehaviour::OnEnteredTrigger(const Gameplay::Physics::TriggerVolume::Sptr& trigger) {
	if (_renderer && EnterMaterial) {
		_renderer->SetMaterial(EnterMaterial);
		std::cout << "Score +1";
	}
	LOG_INFO("Entered trigger: {}", trigger->GetGameObject()->Name);
}

void ScoreBehaviour::OnLeavingTrigger(const Gameplay::Physics::TriggerVolume::Sptr& trigger) {
	if (_renderer && ExitMaterial) {
		_renderer->SetMaterial(ExitMaterial);
	}
	LOG_INFO("Left trigger: {}", trigger->GetGameObject()->Name);
}

void ScoreBehaviour::Awake() {
	_renderer = GetComponent<RenderComponent>();
}

void ScoreBehaviour::RenderImGui() { }

nlohmann::json ScoreBehaviour::ToJson() const {
	return {
		{ "enter_material", EnterMaterial != nullptr ? EnterMaterial->GetGUID().str() : "null" },
		{ "exit_material", ExitMaterial != nullptr ? ExitMaterial->GetGUID().str() : "null" }
	};
}

ScoreBehaviour::Sptr ScoreBehaviour::FromJson(const nlohmann::json& blob) {
	ScoreBehaviour::Sptr result = std::make_shared<ScoreBehaviour>();
	result->EnterMaterial = ResourceManager::Get<Gameplay::Material>(Guid(blob["enter_material"]));
	result->ExitMaterial = ResourceManager::Get<Gameplay::Material>(Guid(blob["exit_material"]));
	return result;
}
