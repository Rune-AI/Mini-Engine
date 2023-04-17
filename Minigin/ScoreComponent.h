#include "Component.h"
#include "Subject.h"
class ScoreComponent : public Component, public Subject<int>
{
public:
	ScoreComponent(Entity* entity);
	~ScoreComponent();
	void Update() override;
	void Render() const override;

	void SetScore(int score);
	int GetScore() const;
	void AddScore(int score);

private:
	int m_Score{ 0 };
};