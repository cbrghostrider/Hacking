// O(n^3 log n) naive implementation of papadimitrious' algorithm
// need to make improvements
#include <cstdio>
#include <iostream>
#include <fstream>
#include <utility>
#include <vector>
#include <algorithm>
#include <functional>
#include <random>
#include <cmath>

#define ITERS(n) (2*n*n)

/////////////////////////////////////////////////////////////
//                Random number generator
/////////////////////////////////////////////////////////////

class RandomGen {
  public:
    //range [low, high], both inclusive
    RandomGen(unsigned int low, unsigned int high); 
    ~RandomGen() {}
    RandomGen(const RandomGen& rhs) = delete;
    RandomGen& operator=(const RandomGen& rhs) = delete;

    unsigned int getRand() {return distr_(eng_);}
  private:
    std::random_device rd_;
    std::mt19937 eng_;
    std::uniform_int_distribution<> distr_;
};

RandomGen::RandomGen(unsigned int low, unsigned int high)
: rd_(), eng_(rd_()), distr_(low, high)
{
}

/////////////////////////////////////////////////////////////
//            Boolean Satisfiability Solver
/////////////////////////////////////////////////////////////

class TwoSatProblem {
  public:
    TwoSatProblem(const char* file);
    ~TwoSatProblem();
    TwoSatProblem(const TwoSatProblem& rhs) = delete;
    TwoSatProblem& operator=(const TwoSatProblem& rhs) = delete;

    bool isSolvable();

  private:
    typedef int Var;
    typedef std::pair<Var, Var> Clause;

    const bool boolOr_[2][2] = {{false, true}, {true, true}};
    bool EvalClause_(const Var& lhs, const Var& rhs);
    void Init_(const char* file);
    void InitAssn_();               //initialize the initial random assignment of vars
    bool CheckSatisfiability_() const;
    unsigned int PickUnsatClause_() const;

    std::vector<Clause> clauses_;   //the clauses in the problem e.g. (x15 v x783)
    std::vector<bool>   assns_;     //the values currently assigned to the variables
    std::vector<bool>   evals_;     //for the assns above, what are the values of the clauses
};


TwoSatProblem::TwoSatProblem(const char* file)
: clauses_(), assns_(), evals_()
{
    Init_(file);
}

TwoSatProblem::~TwoSatProblem()
{
}

void TwoSatProblem::Init_(const char* file)
{
    std::ifstream fin(file);
    unsigned int variables=0, clauses=0;
    fin >> variables;
    clauses = variables;

    assns_.reserve(variables + 1); //0th index unused for variables
    assns_ = std::vector<bool>(variables + 1, false);

    evals_.reserve(clauses);
    evals_ = std::vector<bool>(clauses, false);

    clauses_.reserve(clauses);
    for (unsigned int c=0; c < clauses; c++) {
        Var v1=0, v2=0;
        fin >> v1 >> v2;
        clauses_.push_back(std::make_pair(v1, v2));
    }
}

bool TwoSatProblem::EvalClause_(const Var& lhs, const Var& rhs)
{
    unsigned int ulhs = (lhs < 0 ? (-1 * lhs) : lhs);
    unsigned int urhs = (rhs < 0 ? (-1 * rhs) : rhs);
    unsigned int ilhs = (lhs < 0 ? (assns_[ulhs] ? 0 : 1) : (assns_[ulhs] ? 1 : 0));
    unsigned int irhs = (rhs < 0 ? (assns_[urhs] ? 0 : 1) : (assns_[urhs] ? 1 : 0));
    return (boolOr_ [ilhs][irhs]);
}

//initial assignment: each of the variable values chosen uniformly at random (T/F)
void TwoSatProblem::InitAssn_()
{
    RandomGen rg(0, 1);
    for (unsigned int i=0; i<assns_.size(); i++) {
        assns_[i] = rg.getRand(); 
    }
}

bool TwoSatProblem::CheckSatisfiability_() const
{
    for (auto it = evals_.begin(); it != evals_.end(); it++) {
        if (!(*it)) {
            return false;
        }
    }
    return true;
}

unsigned int TwoSatProblem::PickUnsatClause_() const
{
    std::vector<unsigned int> unsat;
    unsat.reserve(evals_.size());

    for (unsigned int i=0; i<evals_.size(); i++) {
        if (evals_[i] == false) {
            unsat.push_back(i);
        }
    }

    RandomGen rg(0, unsat.size()-1);
    return unsat[rg.getRand()];
}

bool TwoSatProblem::isSolvable() 
{
    const int n = assns_.size();
    const int c = clauses_.size();
    RandomGen rtwo (0, 1);
    for (unsigned int iter = 0; iter < log2(n); iter++) {
        InitAssn_();

        for (unsigned int i=0; i<ITERS(n); i++) {
            std::transform(clauses_.begin(), clauses_.end(), evals_.begin(), [this] (const Clause& c) -> bool {
                return (EvalClause_(c.first, c.second));
            });

            if (CheckSatisfiability_()) {
                return true;
            }

            Clause clause = clauses_[PickUnsatClause_()];
            Var var = rtwo.getRand() == 0 ? clause.first : clause.second;
            Var uvar = var < 0 ? (-1 * var) : var;
            assns_[uvar] = !assns_[uvar];
        }
    }
    return false;
}

////////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[])
{
    if (argc < 2) {
        std::cout << "Usage: ./2-sat ipfile" << std::endl;
    }

    TwoSatProblem tsat(argv[1]);
    bool answer = tsat.isSolvable();

    std::cout << "Solvable = " << (answer ? "Yes" : "No" ) << std::endl;
}

