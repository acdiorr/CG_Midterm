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
	if (trigger->GetGameObject()->Name == "P1Trigger") {

		GetGameObject()->SetPostion(glm::vec3(0.0f, 0.0f, 2.0f));
		score2++; //Player 2 Scored
		LOG_INFO("+1 for Player 2", trigger->GetGameObject()->Name);
		std::cout << "Score: " << score1 << " : " << score2 << "\n";
		if (score2 == 3)
		{
			std::cout << "Game Over! Player 2 Wins!";
			exit(0);
		}
	}
	if (trigger->GetGameObject()->Name == "P2Trigger") {

		GetGameObject()->SetPostion(glm::vec3(0.0f, 0.0f, 2.0f));
		score1++; //Player 1 Scored
		LOG_INFO("+1 for Player 1", trigger->GetGameObject()->Name);
		std::cout << "Score: " << score1 << " : " << score2 << "\n";
		if (score1 == 3)
		{
			std::cout << "Game Over! Player 1 Wins!";
			exit(0);
		}
	}
}

void ScoreBehaviour::OnLeavingTrigger(const Gameplay::Physics::TriggerVolume::Sptr& trigger) {
	/*
	if (_renderer && ExitMaterial) {
		_renderer->SetMaterial(ExitMaterial);
	}
	LOG_INFO("Exitting Trigger {}", trigger->GetGameObject()->Name);
	*/
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
