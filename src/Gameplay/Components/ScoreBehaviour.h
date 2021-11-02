#pragma once
#include "IComponent.h"
#include "Gameplay/Physics/TriggerVolume.h"
#include "Gameplay/Components/RenderComponent.h"
#include "Gameplay/Physics/TriggerVolume.h"

class ScoreBehaviour : public Gameplay::IComponent {

public:
	typedef std::shared_ptr<ScoreBehaviour> Sptr;
	ScoreBehaviour();
	virtual ~ScoreBehaviour();

	Gameplay::Material::Sptr        EnterMaterial;
	Gameplay::Material::Sptr        ExitMaterial;

	// Inherited from IComponent

	virtual void OnEnteredTrigger(const std::shared_ptr<Gameplay::Physics::TriggerVolume>& trigger) override;
	virtual void OnLeavingTrigger(const std::shared_ptr<Gameplay::Physics::TriggerVolume>& trigger) override;
	virtual void Awake() override;
	virtual void RenderImGui() override;
	virtual nlohmann::json ToJson() const override;
	static ScoreBehaviour::Sptr FromJson(const nlohmann::json& blob);
	MAKE_TYPENAME(ScoreBehaviour);

protected:

	RenderComponent::Sptr _renderer;
};