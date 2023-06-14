#include "Component.h"

BearBones::Entity* BearBones::Component::GetOwner() const
{
	return m_pOwner;
}

void BearBones::Component::SetCanBeRemoved(bool value)
{
	m_CanBeRemoved = value;
}

bool BearBones::Component::GetCanBeRemoved()
{
	return m_CanBeRemoved;
}

BearBones::Component::~Component()
{
}
