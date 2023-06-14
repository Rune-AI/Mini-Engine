#ifndef KEYBOARD_H
#define KEYBOARD_H
#include <memory>

namespace BearBones
{
	class Keyboard final
	{
	public:
		Keyboard();
		~Keyboard();

		void Update();
		bool IsPressedThisFrame(unsigned int key) const;
		bool IsReleasedThisFrame(unsigned int key) const;
		bool IsPressed(unsigned int key) const;
	private:
		class KeyboardImpl;
		std::unique_ptr<KeyboardImpl> m_KeyboardImpl;
	};
}
#endif