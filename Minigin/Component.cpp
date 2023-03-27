#include "Component.h"

Entity* Component::GetOwner() const
{
	return m_pOwner;
}

void Component::SetCanBeRemoved(bool value)
{
	m_CanBeRemoved = value;
}

bool Component::GetCanBeRemoved()
{
	return m_CanBeRemoved;
}

Component::~Component()
{
}
