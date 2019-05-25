#pragma once

#include <minisat/core/Solver.h>

#include <vector>

using board = std::vector<std::vector<int>>;

enum Column {
	Colour = 0,
	Pet,
	Beverage,
	Cigarettes,
	Nationality
};

enum House {
	House1 = 0,
	House2,
	House3,
	House4,
	House5
};

enum Colour {
	White = 0,
	Red,
	Yellow,
	Blue,
	Green
};

enum Pet {
	Dog = 0,
	Bird,
	Cat,
	Horse,
	Fish
};

enum Beverage {
	Tea = 0,
	Coffee,
	Milk,
	Beer,
	Water
};

enum Cigarettes{
	PallMall = 0,
	Dunhill,
	BlueMaster,
	Blend,
	Princ
};

enum Nationality {
	Brit = 0,
	Swede,
	Dane,
	German,
	Norwegian
};

class Solver {
private:
    const bool m_write_dimacs = true;
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
// Riddle rules

	// - Englishman lives in a red house
	// void englishman_lives_in_red_house();
	// - Svede has a dog
	// - Danish drinks tea
	// - Green house is left of white house
	// - Green house’s inhabitant drinks coffee
	// - Pall Mall smoker has a bird
	// - Yellow house’s inhabitant smokes Dunhill
	// - Mid house inhabitant drinks milk
	// - Norwegian lives in the first house
    bool NorwegianLivesInTheFirstHouse();
	// - Blend smoker lives next to cat owner
	// - Horse owner lives next to Dunhill smoker
	// - Blue Master smoker drinks beer
	// - German smokes Prince
	// - Norwegian lives next to the blue house
	// - Blend smoker lives next to water drinker
	// ...
	
	// these may be generalized later
};
