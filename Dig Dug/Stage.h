#ifndef STAGE_STRUCTS_H
#define STAGE_STRUCTS_H
#include <string>
#include <vector>

namespace DigDug
{
    struct Position
    {
		int row{ 0 };
		int col{ 0 };
	};

    struct Stage
    {
        std::string name {};
        int rows{ 13 };
        int cols{ 12 };
        std::vector<Position> rocks{};
        std::vector<Position> pookas{};
        std::vector<Position> fygars{};
        std::vector<int> groundStates{};
    };
}

#endif