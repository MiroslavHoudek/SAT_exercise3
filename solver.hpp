#pragma once

#include <minisat/core/Solver.h>

#include <vector>

using board = std::vector<std::vector<int>>;

class Solver {
private:
    const bool m_write_dimacs = false;
    Minisat::Solver solver;

public:
    Solver(bool write_dimacs = false);

    bool solve();

    board get_solution() const;

private:
    void one_square_one_value();
    void non_duplicated_values();
    void exactly_one_true(Minisat::vec<Minisat::Lit> const& literals);
    void init_variables();
};
