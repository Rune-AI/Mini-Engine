#if _DEBUG
#if __has_include(<vld.h>)
//#include <vld.h>
#endif
#endif

#include "Minigin.h"

constexpr auto windowWidth = 640;
constexpr auto windowHeight = 480;

using namespace BearBones;


void load()
{

}


int main(int, char* [])
{
	Minigin engine("./Data/", windowWidth, windowHeight);
	engine.Run(load);

	return 0;
}