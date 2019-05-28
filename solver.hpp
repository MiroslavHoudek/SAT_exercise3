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

    bool transform_to_cnf(Minisat::vec<Minisat::Lit> const& lit_vec1, Minisat::vec<Minisat::Lit> const& lit_vec2);
	bool nextTo(int col1, int val1, int col2, int val2);
	bool setColValToColVal(int col1, int val1, int col2, int val2);
public:
    Solver(bool write_dimacs = false);

    bool solve();

    board get_solution() const;

    void printPretty();

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
	

	// Riddle rules
    // - Brit lives in a red house
    bool BritLivesInARedGHouse();
    // - Swede has a dog
    bool SwedeHasADog();
    // - Dane drinks tea
    bool DaneDrinksTea();
	// - Green house is left of white house
    bool GreenLeftOfWhite();
	// - Green house’s inhabitant drinks coffee
    bool GreenDrinksCoffee();
	// - Pall Mall smoker has a bird
    bool PallMallHasBird();
	// - Yellow house’s inhabitant smokes Dunhill
    bool YellowSmokesDunhill();
	// - Mid house inhabitant drinks milk
    bool MidHouseDrinksMilk();
	// - Norwegian lives in the first house
    bool NorwegianLivesInTheFirstHouse();
	// - Blend smoker lives next to cat owner
    bool BlendSmokerNextToCatOwner();
	// - Horse owner lives next to Dunhill smoker
    bool HorseOwnerNextToDunhillSmoker();
	// - Blue Master smoker drinks beer
    bool BlueMasterSmokerDrinksBeer();
	// - German smokes Prince
    bool GermanSmokesPrince();
	// - Norwegian lives next to the blue house
    bool NorwegianNextToBlue();
	// - Blend smoker lives next to water drinker
    bool BlendSmokerNextToWaterDrinker();

};
