#include "solver.hpp"

#include <iostream>
#include <iomanip>

namespace {

const int rows = 5;
const int columns = 5;
const int values = 5;

Minisat::Var toVar(int row, int column, int value) {
    assert(row >= 0 && row < rows    && "Attempt to get var for nonexistant row");
    assert(column >= 0 && column < columns && "Attempt to get var for nonexistant column");
    assert(value >= 0 && value < values   && "Attempt to get var for nonexistant value");
    //return row * columns * values + column * values + value;
    return column * rows * values + row * values + value;
}

bool is_valid(board const& b) {
    if (b.size() != rows) {
        return false;
    }
    for (int row = 0; row < rows; ++row) {
        if (b[row].size() != columns) {
            return false;
        }
        for (int col = 0; col < columns; ++col) {
            auto value = b[row][col];
            if (value < 0 || value > 9) {
                return false;
            }
        }
    }
    return true;
}

void log_var(Minisat::Lit lit) {
    if (sign(lit)) {
        std::clog << '-';
    }
    std::clog << var(lit) + 1 << ' ';
}

void log_clause(Minisat::vec<Minisat::Lit> const& clause) {
    for (int i = 0; i < clause.size(); ++i) {
        log_var(clause[i]);
    }
    std::clog << "0\n";
}

void log_clause(Minisat::Lit lhs, Minisat::Lit rhs) {
    log_var(lhs); log_var(rhs);
    std::clog << "0\n";
}

std::string getString(int col, int val)
{
    if (col == Column::Colour)
    {
        switch (val-1) {
        case Colour::White:
            return std::string("white");
            break;
        case Colour::Red:
            return std::string("red");
            break;
        case Colour::Yellow:
            return std::string("yellow");
            break;
        case Colour::Blue:
            return std::string("blue");
            break;
        case Colour::Green:
            return std::string("green");
            break;
        }
    }
    if (col == Column::Colour)
    {
        switch (val-1) {
        case Colour::White:
            return std::string("white");
            break;
        case Colour::Red:
            return std::string("red");
            break;
        case Colour::Yellow:
            return std::string("yellow");
            break;
        case Colour::Blue:
            return std::string("blue");
            break;
        case Colour::Green:
            return std::string("green");
            break;
        }
    }
    if (col == Column::Colour)
    {
        switch (val-1) {
        case Colour::White:
            return std::string("white");
            break;
        case Colour::Red:
            return std::string("red");
            break;
        case Colour::Yellow:
            return std::string("yellow");
            break;
        case Colour::Blue:
            return std::string("blue");
            break;
        case Colour::Green:
            return std::string("green");
            break;
        }
    }
    if (col == Column::Colour)
    {
        switch (val-1) {
        case Colour::White:
            return std::string("white");
            break;
        case Colour::Red:
            return std::string("red");
            break;
        case Colour::Yellow:
            return std::string("yellow");
            break;
        case Colour::Blue:
            return std::string("blue");
            break;
        case Colour::Green:
            return std::string("green");
            break;
        }
    }
    else if (col == Column::Pet)
    {
        switch (val-1) {
        case Pet::Dog:
            return std::string("dog");
            break;
        case Pet::Bird:
            return std::string("bird");
            break;
        case Pet::Cat:
            return std::string("cat");
            break;
        case Pet::Horse:
            return std::string("horse");
            break;
        case Pet::Fish:
            return std::string("fish");
            break;
        }
    }
    else if (col == Column::Beverage)
    {
        switch (val-1) {
        case Beverage::Tea:
            return std::string("tea");
            break;
        case Beverage::Coffee:
            return std::string("coffee");
            break;
        case Beverage::Milk:
            return std::string("milk");
            break;
        case Beverage::Beer:
            return std::string("beer");
            break;
        case Beverage::Water:
            return std::string("water");
            break;
        }
    }
    else if (col == Column::Cigarettes)
    {
        switch (val-1) {
        case Cigarettes::PallMall:
            return std::string("pallmall");
            break;
        case Cigarettes::Dunhill:
            return std::string("dunhill");
            break;
        case Cigarettes::BlueMaster:
            return std::string("bluemaster");
            break;
        case Cigarettes::Blend:
            return std::string("blend");
            break;
        case Cigarettes::Princ:
            return std::string("princ");
            break;
        }
    }
    else if (col == Column::Nationality)
    {
        switch (val-1) {
        case Nationality::Brit:
            return std::string("brit");
            break;
        case Nationality::Swede:
            return std::string("swede");
            break;
        case Nationality::Dane:
            return std::string("dane");
            break;
        case Nationality::German:
            return std::string("german");
            break;
        case Nationality::Norwegian:
            return std::string("norwegian");
            break;
        }
    }
    else return std::string("problem");
}

} //end anonymous namespace

void Solver::init_variables() {
    if (m_write_dimacs) {
        std::clog << "c (row, column, value) = variable\n";
    }
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < columns; ++c) {
            for (int v = 0; v < values; ++v) {
                auto var = solver.newVar();
                if (m_write_dimacs) {
                    std::clog << "c (" << r << ", " << c << ", " << v + 1 << ") = " << var + 1 << '\n';
                }
            }
        }
    }
    std::clog << std::flush;
}


void Solver::exactly_one_true(Minisat::vec<Minisat::Lit> const& literals) {
    if (m_write_dimacs) {
        log_clause(literals);
    }
    solver.addClause(literals);
    for (size_t i = 0; i < literals.size(); ++i) {
        for (size_t j = i + 1; j < literals.size(); ++j) {
            if (m_write_dimacs) {
                log_clause(~literals[i], ~literals[j]);
            }
            solver.addClause(~literals[i], ~literals[j]);
        }
    }
}

void Solver::one_square_one_value() {
    for (int row = 0; row < rows; ++row) {
        for (int column = 0; column < columns; ++column) {
            Minisat::vec<Minisat::Lit> literals;
            for (int value = 0; value < values; ++value) {
                literals.push(Minisat::mkLit(toVar(row, column, value)));
            }
            exactly_one_true(literals);
        }
    }
}

void Solver::non_duplicated_values() {
    // In each column, for each value, forbid two rows sharing that value
    for (int column = 0; column < columns; ++column) {
        for (int value = 0; value < values; ++value) {
            Minisat::vec<Minisat::Lit> literals;
            for (int row = 0; row < rows; ++row) {
                literals.push(Minisat::mkLit(toVar(row, column, value)));
            }
            exactly_one_true(literals);
        }
    }
}

// Transforms (x_1 && y_2) || (x_2 && y_1) || (x_2 && y_3) ... into (z_1 || z_2 || ... z_n) && (z_1 || x_1) && (z_1 || y_1) ... (z_n || y_n)
bool Solver::transform_to_cnf(Minisat::vec<Minisat::Lit> const& lit_vec1, Minisat::vec<Minisat::Lit> const& lit_vec2) {
	bool ret = true;

    Minisat::vec<Minisat::Lit> litZ;

	// TODO not sure if I should be coming up with
	// variables, or recycle some pool for the Zn vars
    for (size_t i=0; i<lit_vec1.size(); i++) {
        auto var = solver.newVar();
        litZ.push(Minisat::mkLit(var));
    }

    solver.addClause(litZ);
		if (m_write_dimacs) {
			log_clause(litZ);
		}

    for (size_t i = 0; i < lit_vec1.size(); ++i) {
        ret &= solver.addClause(~litZ[i], lit_vec1[i]);
        ret &= solver.addClause(~litZ[i], lit_vec2[i]);
		
		if (m_write_dimacs) {
			log_clause(~litZ[i], lit_vec1[i]);
			log_clause(~litZ[i], lit_vec2[i]);
		}
    }
	
	return ret;
}

bool Solver::nextTo(int col1, int val1, int col2, int val2)
{
    bool ret = true;

    Minisat::vec<Minisat::Lit> lit1, lit2;
	
    for ( int row = House::House1; row <= House::House4; row++ )
    {
        lit1.push(Minisat::mkLit(toVar(row  , col1, val1)));
        lit2.push(Minisat::mkLit(toVar(row+1, col2, val2)));
        lit1.push(Minisat::mkLit(toVar(row+1, col1, val1)));
        lit2.push(Minisat::mkLit(toVar(row  , col2, val2)));
    }

    transform_to_cnf(lit1, lit2);

    return ret;	
}

bool Solver::setColValToColVal(int col1, int val1, int col2, int val2) {
    bool ret = true;
	
    for ( int row = House::House1; row <= House::House5; row++ )
    {
        ret &= solver.addClause(~Minisat::mkLit(toVar(row, col1, val1)), Minisat::mkLit(toVar(row, col2, val2)));
    }
	
	return ret;
}

Solver::Solver(bool write_dimacs):
    m_write_dimacs(write_dimacs) {
    // Initialize the board
    init_variables();
    one_square_one_value();
    non_duplicated_values();

    // Riddle rules application
    NorwegianLivesInTheFirstHouse();
    SwedeHasADog();
    BritLivesInARedGHouse();
    DaneDrinksTea();
    GreenLeftOfWhite();
    GreenDrinksCoffee();
    PallMallHasBird();
    YellowSmokesDunhill();
    MidHouseDrinksMilk();
    BlendSmokerNextToCatOwner();
    HorseOwnerNextToDunhillSmoker();
    BlueMasterSmokerDrinksBeer();
    GermanSmokesPrince();
    NorwegianNextToBlue();
    BlendSmokerNextToWaterDrinker();
}

bool Solver::solve() {
    return solver.solve();
}

board Solver::get_solution() const {
    board b(rows, std::vector<int>(columns));
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < columns; ++col) {
            int found = 0;
            for (int val = 0; val < values; ++val) {
                if (solver.modelValue(toVar(row, col, val)).isTrue()) {
                    ++found;
                    b[row][col] = val + 1;
                }
            }
            assert(found == 1 && "The SAT solver assigned one position more than one value");
            (void)found;
        }
    }
    return b;
}

void Solver::printPretty()
{
    auto solution = get_solution();
    for (auto const& row : solution) {
        int n = 0;
        for (auto const& col : row) {
            std::cout << std::setw(12) << getString(n, col) << ' ';
            // TODO fixme
            n++;
        }
        std::cout << '\n';
    }
}

bool Solver::BritLivesInARedGHouse()
{
    bool ret = true;

	ret &= setColValToColVal(Column::Nationality, Nationality::Brit, Column::Colour, Colour::Red);

    return ret;
}


bool Solver::SwedeHasADog()
{
    bool ret = true;

	ret &= setColValToColVal( Column::Nationality, Nationality::Swede, Column::Pet, Pet::Dog);

    return ret;
}

bool Solver::NorwegianLivesInTheFirstHouse()
{
	bool ret = true;

    ret &= solver.addClause( Minisat::mkLit(toVar(House::House1, Column::Nationality, Nationality::Norwegian)));

	return ret;
}

bool Solver::DaneDrinksTea()
{
    bool ret = true;

	ret &= setColValToColVal( Column::Nationality, Nationality::Dane, Column::Beverage, Beverage::Tea);

    return ret;
}

// - Green house is left of white house
bool Solver::GreenLeftOfWhite() {
    bool ret = true;

    Minisat::vec<Minisat::Lit> lit1, lit2;

    for ( int row = House::House1; row <= House::House4; row++ )
    {
        for (int row_in = row+1; row_in <= House::House5; row_in++) {
            lit1.push(Minisat::mkLit(toVar(row   , Column::Colour, Colour::Green)));
            lit2.push(Minisat::mkLit(toVar(row_in, Column::Colour, Colour::White)));
        }
    }

    ret &= transform_to_cnf(lit1, lit2);

    return ret;
}

// - Green house’s inhabitant drinks coffee
bool Solver::GreenDrinksCoffee() {
	bool ret = true;
	
	ret &= setColValToColVal( Column::Colour, Colour::Green, Column::Beverage, Beverage::Coffee);

    return ret;
}

// - Pall Mall smoker has a bird
bool Solver::PallMallHasBird() {
    bool ret = true;

	ret &= setColValToColVal(  Column::Cigarettes, Cigarettes::PallMall, Column::Pet, Pet::Bird);

    return ret;
}

// - Yellow house’s inhabitant smokes Dunhill
bool Solver::YellowSmokesDunhill() {
    bool ret = true;

	ret &= setColValToColVal( Column::Colour, Colour::Yellow, Column::Cigarettes, Cigarettes::Dunhill);

    return ret;
}

// - Mid house inhabitant drinks milk
bool Solver::MidHouseDrinksMilk() {
    bool ret = true;

    ret &= solver.addClause( Minisat::mkLit(toVar(House::House3, Column::Beverage, Beverage::Milk)));

    return ret;
}

// - Blend smoker lives next to cat owner
bool Solver::BlendSmokerNextToCatOwner() {
    bool ret = true;

	ret &= nextTo(Column::Pet, Pet::Cat, Column::Cigarettes, Cigarettes::Blend);

    return ret;
}

// - Horse owner lives next to Dunhill smoker
bool Solver::HorseOwnerNextToDunhillSmoker() {
    bool ret = true;

	ret &= nextTo(Column::Pet, Pet::Horse, Column::Cigarettes, Cigarettes::Dunhill);

    return ret;
}

// - Blue Master smoker drinks beer
bool Solver::BlueMasterSmokerDrinksBeer() {
    bool ret = true;

	ret &= setColValToColVal( Column::Cigarettes, Cigarettes::BlueMaster, Column::Beverage, Beverage::Beer);

    return ret;
}

// - German smokes Prince
bool Solver::GermanSmokesPrince() {
    bool ret = true;

 	ret &= setColValToColVal( Column::Nationality,  Nationality::German, Column::Cigarettes, Cigarettes::Princ);

    return ret;
}

// - Norwegian lives next to the blue house
bool Solver::NorwegianNextToBlue() {
    bool ret = true;

	ret &= nextTo(Column::Nationality,  Nationality::Norwegian, Column::Colour, Colour::Blue);

    return ret;
}

// - Blend smoker lives next to water drinker
bool Solver::BlendSmokerNextToWaterDrinker() {
    bool ret = true;

	ret &= nextTo(Column::Cigarettes,  Cigarettes::Blend, Column::Beverage, Beverage::Water);

    return ret;
}
