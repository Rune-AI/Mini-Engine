#include "Component.h"
#include "Subject.h"

class HealthComponent : public Component, public Subject<int>
{
public:
	HealthComponent(Entity* entity);
	~HealthComponent();
	void Update() override;
	void Render() const override;

	void SetHealth(int health);
	int GetHealth() const;
	void TakeDamage(int damage);

private:
	int m_Health{ 3 };
};