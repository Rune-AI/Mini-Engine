#include "TextComponent.h"
#include "EventManager.h"
#include "IObserver.h"


class HealthHUD : public TextComponent, public IObserver<int>
{
public:
	HealthHUD(Entity* entity, int health);

	void Update() override;
	void Render() const override;

	void OnNotify(int data) override;

	IObserver<int>* GetObserver() override
	{
		return this;
	}
};
