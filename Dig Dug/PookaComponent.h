#ifndef POOKA_COMPONENT_H
#define POOKA_COMPONENT_H

#include <Component.h>

#include <memory>
#include <Texture2D.h>
#include <IObserver.h>

namespace DigDug
{
	class PookaComponent : public BearBones::Component, public BearBones::IObserver<BearBones::Entity*>
	{
	public:
		PookaComponent(BearBones::Entity* object);
		virtual ~PookaComponent() = default;

		PookaComponent(const PookaComponent& other) = delete;
		PookaComponent(PookaComponent&& other) = delete;
		PookaComponent& operator=(const PookaComponent& other) = delete;
		PookaComponent& operator=(PookaComponent&& other) = delete;

		virtual void Update() override;
		virtual void Render() const override;

		void OnNotify(BearBones::Entity*) override;

		IObserver<BearBones::Entity*>* GetObserver() override
		{
			return this;
		}

	private:
		std::shared_ptr<BearBones::Texture2D> m_idleTexture{};


		float m_deflateTimer{};
		float m_deflateInterval{1.f};
		int m_inflateIndex{};

	};
}

#endif