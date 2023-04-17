#include "TextComponent.h"
#include "EventManager.h"
#include "IObserver.h"

class ScoreHUD final :public TextComponent, public IObserver<int>
{
public:
	ScoreHUD(Entity* entity, int score);

	void Update() override;
	void Render() const override;

	void OnNotify(int data) override;

	IObserver<int>* GetObserver() override
	{
		return this;
	}
};