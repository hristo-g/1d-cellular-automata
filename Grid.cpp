#include "Grid.h"

template <class T>
std::ostream& operator<<(std::ostream& out, std::vector<T> v) {
    out << "(";

    for (typename std::vector<T>::const_iterator p = v.begin(); p != v.end(); ++p) {
        out << " [" << *p << "]";
    }

    out << " )";
    return out;
}


Grid::Grid(const unsigned int xsize) : m_Dimension(1),
                              m_Size(1, xsize),
                              m_Cells(xsize, false)
                              { std::cout << "Grid created! (" << m_Dimension << ")" << std::endl; }

Grid::Grid(const unsigned int xsize, const unsigned int ysize) : m_Dimension(2),
       										   m_Size(CreateVector(xsize, ysize)),
       										   m_Cells(std::vector<bool>(xsize * ysize, false))
       										   {}

Grid::Grid(const std::vector<unsigned int> sizevec) : m_Dimension(sizevec.size()),
 								             m_Size(sizevec),
 								             m_Cells(InitGrid(sizevec))
 								             {}

std::vector<unsigned int> Grid::CreateVector(const unsigned int xsize, const unsigned int ysize) const {
    unsigned int arr[] = { xsize, ysize };
    const std::vector<unsigned int> s(arr, arr + sizeof(arr) / sizeof(arr[0]));
    return s;
}

/*
std::vector<bool> Grid::InitGrid(const unsigned int xsize, const unsigned int ysize) {
	std::vector<bool>(xsize * ysize, false)
	return ;
}
*/

std::vector<bool> Grid::InitGrid(const std::vector<unsigned int> s) {
    long unsigned int total_dim = 1;

    for (std::vector<unsigned int>::const_iterator p = s.begin(); p != s.end(); ++p)	{
		total_dim *= (*p);
    }

    return std::vector<bool>(total_dim, false);
}

void Grid::Draw(std::ostream& out) {
	// TODO: this only works properly for the 1D case.

	for (std::vector<bool>::const_iterator p = m_Cells.begin(); p != m_Cells.end(); ++p) {
		out << (*p ? 'o' : '.');
	}

	out << std::endl;
}

/*
void Grid::Update(std::map<std::vector<bool>, bool> rule_map) {
	std::vector<bool> updated_cells;

    //updated_cells.push_back(false);

	for (std::vector<bool>::iterator p = m_Cells.begin(); p != m_Cells.end(); ++p) {
		//std::cout << GetNeighborhood(p) << " -> " << rule_map[GetNeighborhood(p)] << std::endl;
		updated_cells.push_back(rule_map[GetNeighborhood(p)]);
	}

	//updated_cells.push_back(false);

	m_Cells = updated_cells;
}

std::vector<bool> Grid::GetNeighborhood(std::vector<bool>::iterator p) {
	// Assume dimensionality of 1.
	std::vector<bool> neighborhood;
	unsigned int nsize = pow(3, m_Dimension);
	unsigned int loop_start = 0;

	if (p == m_Cells.begin()) {
		neighborhood.push_back(*(m_Cells.end() - 1));
		std::cout << "Rightmost cell: " << *(m_Cells.end() - 1) << std::endl;
		loop_start = nsize / 2;
	}
	else if (p == m_Cells.end() - 1) {
		neighborhood.push_back(*(m_Cells.begin()));
		std::cout << "Leftmost cell: " << *(m_Cells.begin()) << std::endl;
		loop_start = nsize / 2;
	}

	for (unsigned int i = loop_start; i < nsize; i++) {
		neighborhood.push_back(*(p + i - nsize / 2));
	}

	return neighborhood;
}
*/

void Grid::Update(std::map<std::vector<bool>, bool> rule_map) {
	std::vector<bool> updated_cells;

    //updated_cells.push_back(false);

	for (unsigned int i = 0; i < m_Cells.size(); i++) {
		//std::cout << GetNeighborhood(i) << " -> " << rule_map[GetNeighborhood(i)] << std::endl;
		updated_cells.push_back(rule_map[GetNeighborhood(i)]);
	}

	//updated_cells.push_back(false);

	m_Cells = updated_cells;
}

std::vector<bool> Grid::GetNeighborhood(unsigned int pos) {
	// Assume dimensionality of 1.
	std::vector<bool> neighborhood;
	unsigned int nsize = pow(3, m_Dimension);
	unsigned int loop_start = 0;
	unsigned int last_pos = m_Cells.size() - 1;
	unsigned int step = static_cast<unsigned int> (nsize / 2);

	//std::cout << "Neighborhood:";

	if (pos == 0) {
		loop_start = step;

		while (loop_start--) {
			//std::cout << " * " << last_pos - loop_start;
			neighborhood.push_back(m_Cells[last_pos - loop_start]);
		}

		loop_start = step;

		for (unsigned int i = loop_start; i < nsize; i++) {
			//std::cout << " " << pos + i - step;
			neighborhood.push_back(m_Cells[pos + i - step]);
		}
	}
	else if (pos == last_pos) {
		for (unsigned int i = loop_start; i < nsize - 1; i++) {
			//std::cout << " " << pos + i - step;
			neighborhood.push_back(m_Cells[pos + i - step]);
		}

		loop_start = step;

		while (loop_start--) {
			//std::cout << " * " << loop_start;
			neighborhood.push_back(m_Cells[loop_start]);
		}
	}
	else {
		for (unsigned int i = loop_start; i < nsize; i++) {
			//std::cout << " " << pos + i - step;
			neighborhood.push_back(m_Cells[pos + i - step]);
		}
	}

	//std::cout << std::endl;

	return neighborhood;
}

void Grid::TurnCellsOn(std::vector<unsigned int> cells) {
	for (std::vector<unsigned int>::iterator p = cells.begin(); p != cells.end(); ++p) {
        m_Cells[*p] = true;
    }
}

std::ostream& operator<<(std::ostream& out, Grid* g) {
    return out << g->size();
}