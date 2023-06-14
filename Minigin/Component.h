#ifndef COMPONENT_H
#define COMPONENT_H

namespace BearBones
{
	class Entity;
	class Component
	{
	public:
		virtual ~Component();

		Component(const Component& other) = delete;
		Component(Component&& other) = delete;
		Component& operator=(const Component& other) = delete;
		Component& operator=(Component&& other) = delete;

		virtual void Update() = 0;
		virtual void Render() const = 0;
		virtual void RenderImGui() {};

		bool GetCanBeRemoved();
		Entity* GetOwner() const;

		friend class Entity;

	protected:
		explicit Component(Entity* pOwner) : m_pOwner{ pOwner } {}
		void SetCanBeRemoved(bool value);

		Entity* m_pOwner{};
		bool m_MarkedForDeletion{};
		bool m_CanBeRemoved{};
	};
}
#endif //COMPONENT_H