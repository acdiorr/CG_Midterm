#pragma once
#include "IComponent.h"
#include "Gameplay/Physics/TriggerVolume.h"
#include "Gameplay/Components/RenderComponent.h"
#include "Gameplay/Physics/TriggerVolume.h"

class BounceBehaviour : public Gameplay::IComponent {

public:
	typedef std::shared_ptr<BounceBehaviour> Sptr;
	BounceBehaviour();
	virtual ~BounceBehaviour();

	Gameplay::Material::Sptr        EnterMaterial;
	Gameplay::Material::Sptr        ExitMaterial;
	// Inherited from IComponent

	virtual void OnEnteredTrigger(const std::shared_ptr<Gameplay::Physics::TriggerVolume>& trigger) override;
	virtual void OnLeavingTrigger(const std::shared_ptr<Gameplay::Physics::TriggerVolume>& trigger) override;
	virtual void Awake() override;
	virtual void RenderImGui() override;
	virtual nlohmann::json ToJson() const override;
	static BounceBehaviour::Sptr FromJson(const nlohmann::json& blob);
	MAKE_TYPENAME(BounceBehaviour);

protected:
	RenderComponent::Sptr _renderer;
	Gameplay::Physics::RigidBody::Sptr _body;
};