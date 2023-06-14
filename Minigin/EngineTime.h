#ifndef TIME_H
#define TIME_H
#include "Singleton.h"

namespace BearBones
{
#define TIME Time::GetInstance()


	class Time final : public Singleton<Time>
	{
	public:
		void Update(float deltaTime);

		float GetDeltaTime() const;
		double GetElapsedTime() const;

	private:
		float m_DeltaTime{};
		double m_ElapsedTime{};
	};
}
#endif //TIME_H