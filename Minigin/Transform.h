#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <glm/glm.hpp>

namespace BearBones
{
	class Transform final
	{
	public:
		const glm::vec3& GetPosition() const { return m_position; }
		void SetPosition(float x, float y, float z);
	private:
		glm::vec3 m_position;
	};
}

#endif //TRANSFORM_H