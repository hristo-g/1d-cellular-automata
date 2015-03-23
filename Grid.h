#ifndef GRID_H
#define GRID_H

#include <cmath>
#include <iostream>
#include <map>
#include <vector>

class Grid {
public:
    Grid(const unsigned int);
    Grid(const unsigned int, const unsigned int);
    Grid(const std::vector<unsigned int>);

    void Draw(std::ostream&);
    void Update(std::map<std::vector<bool>, bool>);

    void TurnCellsOn(std::vector<unsigned int>);

    inline std::vector<unsigned int> size() const { return m_Size; }
    inline unsigned short int dimension() const { return m_Dimension; }

private:
    std::vector<unsigned int> CreateVector(const unsigned int, const unsigned int) const;
    const unsigned short int m_Dimension;
    const std::vector<unsigned int> m_Size;
    std::vector<bool> m_Cells;

    //std::vector<bool> InitGrid(const int, const int);
    std::vector<bool> InitGrid(const std::vector<unsigned int>);

    //std::vector<bool> GetNeighborhood(std::vector<bool>::iterator);
    std::vector<bool> GetNeighborhood(unsigned int pos);
};

template <class T>
std::ostream& operator<<(std::ostream&, std::vector<T>);
std::ostream& operator<<(std::ostream&, Grid*);

#endif // GRID_H