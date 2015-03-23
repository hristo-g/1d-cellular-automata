#ifndef GAMEOFLIFE_H
#define GAMEOFLIFE_H

#include <string>

#include "Grid.h"

class GameOfLife {
public:
    void Update();
    void Draw();

    void InitMessage();

    void TurnCellsOn(std::vector<unsigned int>);
    //void TurnCellsOn(std::vector<vector<long int> >);

    void Iterate(long int);

    /*
    GameOfLife();
    GameOfLife(int);
    GameOfLife(Grid);
    GameOfLife(Grid, int);
    */

    GameOfLife(Grid, unsigned int, std::ostream&);

    //inline void SetOutput(std::ostream& out) { m_Out = out; }

private:
    unsigned int m_Rule;
    std::map<std::vector<bool>, bool> m_RuleMap;
    Grid m_Grid;
    std::ostream& m_Out;
};

std::map<std::vector<bool>, bool> CreateRuleMap(const unsigned int, const unsigned short int);
std::vector<bool> Binarize(unsigned int, bool);
std::vector<bool> Binarize(unsigned int, unsigned short int, bool);

#endif // GAMEOFLIFE_H