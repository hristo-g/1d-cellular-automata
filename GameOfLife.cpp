#include "GameOfLife.h"

#define DEFAULT_GRID_SIZE 40

/*
GameOfLife::GameOfLife() : m_Grid(Grid(DEFAULT_GRID_SIZE)), m_Rule(1) {}
GameOfLife::GameOfLife(int rule) : m_Grid(Grid(DEFAULT_GRID_SIZE)), m_Rule(rule) {}
GameOfLife::GameOfLife(Grid g) : m_Grid(g), m_Rule(1) {}
GameOfLife::GameOfLife(Grid g, int rule) : m_Grid(g), m_Rule(rule) {}
*/

template <class T>
std::ostream& operator<<(std::ostream& out, std::vector<T> v) {
    out << "(";

    for (typename std::vector<T>::const_iterator p = v.begin(); p != v.end(); ++p) {
        out << " [" << *p << "]";
    }

    out << " )";
    return out;
}


GameOfLife::GameOfLife(Grid g, unsigned int rule, std::ostream& out) : m_Grid(g),
                                                                       m_Rule(rule), 
                                                                       m_RuleMap(CreateRuleMap(rule, g.dimension())),
                                                                       m_Out(out)
                                                                       { InitMessage(); }

std::map<std::vector<bool>, bool> CreateRuleMap(const unsigned int rule, const unsigned short int dimension) {
    std::map<std::vector<bool>, bool> rule_map;
    const short int num_states = 2;
    const short int nsize = 3;

    std::cout << "Dimension: " << dimension << std::endl;
    unsigned int num_configurations = pow(num_states, pow(nsize, dimension));
    std::cout << "Number of configurations: " << num_configurations << std::endl;

    std::vector<bool> binarized_rule = Binarize(rule, num_configurations, true);
    std::cout << binarized_rule << std::endl;

    for (unsigned int i = 0; i < num_configurations; i++) {
        rule_map[Binarize(i, nsize, false)] = binarized_rule[i];

        std::cout << Binarize(i, nsize, false) << " -> " << binarized_rule[i] << std::endl;
    }

    return rule_map;
}

std::vector<bool> Binarize(unsigned int configuration, bool reverse) {
    std::vector<bool> binary_representation;

    while (configuration > 0) {
        if (reverse) {
            binary_representation.push_back(configuration % 2);
        }
        else {
            binary_representation.insert(binary_representation.begin(), configuration % 2);
        }
        configuration /= 2;
    }

    return binary_representation;
}

std::vector<bool> Binarize(unsigned int configuration, unsigned short int num_bits, bool reverse) {
    std::vector<bool> binary_representation(Binarize(configuration, reverse));
    unsigned int current_bits = binary_representation.size();

    while (-current_bits + num_bits--) { 
        if (reverse) {
            binary_representation.push_back(false);
        }          
        else {
            binary_representation.insert(binary_representation.begin(), false);
        }
    }

    return binary_representation;
}

void GameOfLife::InitMessage() {
    m_Out << "GameOfLife created: rule " << m_Rule
          << ", grid dimension: " << m_Grid.dimension()
          << ", grid size: " << &m_Grid << std::endl;
}

void GameOfLife::Draw() { m_Grid.Draw(m_Out); }
void GameOfLife::Update() { m_Grid.Update(m_RuleMap); }

void GameOfLife::Iterate(long int iterations) {
    while (iterations--) {
        Draw();
        usleep(250000);
        Update();
    }
}

void GameOfLife::TurnCellsOn(std::vector<unsigned int> cells) { m_Grid.TurnCellsOn(cells); }
