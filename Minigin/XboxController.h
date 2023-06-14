#ifndef XBOX_CONTROLLER_H
#define XBOX_CONTROLLER_H

#define WIN32_LEAN_AND_MEAN 
#include <windows.h>

#include <memory>
#include <glm/glm.hpp>

namespace BearBones
{
	class XboxController final
	{
	public:
		XboxController();
		XboxController(int controllerIndex);
		~XboxController();
		void Update();

		bool IsDownThisFrame(unsigned int button) const;
		bool IsUpThisFrame(unsigned int button) const;
		bool IsPressed(unsigned int button) const;
		float GetLeftTrigger() const;
		float GetRightTrigger() const;
		glm::vec2 GetLeftThumbStick() const;
		glm::vec2 GetRightThumbStick() const;

	private:
		class XboxControllerImpl;
		std::unique_ptr<XboxControllerImpl> pImpl;
	};
}
#endif //XBOX_CONTROLLER_H
