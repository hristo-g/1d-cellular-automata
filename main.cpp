#include "GameOfLife.h"
#include "Grid.h"

int main() {
	std::vector<unsigned int> rules;
	rules.push_back(110);
	rules.push_back(150);
	rules.push_back(90);
	rules.push_back(106);
	rules.push_back(142);
	rules.push_back(41);
	rules.push_back(184);

	std::vector<unsigned int> pattern;
	pattern.push_back(0);
	pattern.push_back(1);
	pattern.push_back(49);
	pattern.push_back(5);
	pattern.push_back(6);
	pattern.push_back(75);
	pattern.push_back(88);
	pattern.push_back(87);
	pattern.push_back(90);
	pattern.push_back(59);

    for (std::vector<unsigned int>::const_iterator p = rules.begin(); p != rules.end(); ++p) {
		GameOfLife gol = GameOfLife(Grid(100), *p, std::cout);

		gol.TurnCellsOn(pattern);
		gol.Iterate(50);
	}

	return 0;
}