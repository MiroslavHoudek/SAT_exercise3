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
	// This is going to be adapted from the Sudoku example.
	// Where Sudoku is 9 * 9 with 9 possible values, this riddle
	// is 5 * 5 with 5 possible values
    void init_variables();

	// The functions bellow may remain the same ...
    void one_square_one_value();
	// ... except this one could be simplified because a row may
	// actually may contain identical values ...
    void non_duplicated_values();
    void exactly_one_true(Minisat::vec<Minisat::Lit> const& literals);
	
	// ... but I may need another one which ensures that values for each
	// quality are going to be constrained to their respective columns. In
	// some way it may be unnecessary, because if we conceptually assign  
	// numerical values 1-5 to five options for each column, it may not matter
	// what they represent, as long as they obey the constraints.
    // void house_colours_in_house_column();
	// void pets_in_pet_column();
	// void nationality_in_nationality_column();
	// void cigarettes_in_cigarettes_column();
	// void beverages_in_beverage_column();
	
	// In addition we need to develop all statements about the arrangement:
	//
	// void englishman_lives_in_red_house();
	// ...
	
	// these may be generalized later
};
