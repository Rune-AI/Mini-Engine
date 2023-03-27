#pragma once
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
	virtual void RenderImGui() = 0;

	bool GetCanBeRemoved();

	friend class Entity;
	
protected:
	explicit Component(Entity* pOwner) : m_pOwner{ pOwner } {}
	Entity* GetOwner() const;
	void SetCanBeRemoved(bool value);
	
	Entity* m_pOwner{};
	bool m_MarkedForDeletion{};
	bool m_CanBeRemoved{};
};
