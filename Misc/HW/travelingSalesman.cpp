#include <cstdio>
#include <iostream>
#include <utility>
#include <vector>
#include <fstream>
#include <string>
#include <assert.h>
#include <cmath>
#include <limits>

using std::string;
using std::pair;
using std::vector;

#define SIZEOFINT (sizeof(unsigned int) * 8)

typedef pair<float, float> Coord;

static float distance(const Coord& lhs, const Coord& rhs)
{
    float xdiff = lhs.first - rhs.first;
    float ydiff = lhs.second - rhs.second;
    return (std::sqrt((xdiff * xdiff) + (ydiff * ydiff)));
}

//////////////////////////////////////////////////////////////////////////////////
//      Subset class - all cities are represented by a bit in subset
//////////////////////////////////////////////////////////////////////////////////

class Subset {
  public:
    Subset() : repr_(0) {}
    Subset(unsigned int r) : repr_(r) {}
    Subset(const Subset& rhs) : repr_(rhs.repr_) {}
    ~Subset() {}

    void add(unsigned int position);            //add indicated bit position
    void remove(unsigned int position);         //remove indicated bit position
    bool contains(unsigned int position) const; //query function
    void reset() {repr_=0;}                     //reset

    unsigned int repr() const {return repr_;}   //what is the representation
    unsigned int size() const;                  //how many cities in this subset
  private:
    unsigned int repr_;
};

void Subset::remove(unsigned int position)
{
    assert(position < SIZEOFINT);
    unsigned int reset = ~(1 << position);
    repr_ &= reset;
}

void Subset::add(unsigned int position)
{
    assert(position < SIZEOFINT);
    unsigned int set = (1 << position);
    repr_ |= set;
}

bool Subset::contains(unsigned int position) const
{
    assert(position < SIZEOFINT);
    unsigned int set = (1 << position);
    return (repr_ & set) ;
}

unsigned int Subset::size() const
{
    unsigned int marker = 1;
    unsigned int count=0;
    for (unsigned int cnt=0; cnt < SIZEOFINT; cnt++) {
        if (marker & repr_) {
            count++;
        }
        marker = marker << 1;
    }
    return count;
}

static void getSubsets(vector<Subset>& subsets, unsigned int m, unsigned int cities)
{
    for (unsigned int i = 0; i < (1<<cities) ; i++) {
        Subset s(i);
        if (s.contains(0) && s.size() == m) {
            subsets.push_back(s);
        }
    }
}

//////////////////////////////////////////////////////////////////////////////////
//                  Class for the Traveling Salesman Problem
//////////////////////////////////////////////////////////////////////////////////

class TSPProblem {
  public:
    TSPProblem() : cities_(), cache_(0), rows_(0), cols_(0) {}
    ~TSPProblem() {freeTSPCache_();}

    void readCities(const char* file);  //read cities from file
    float solveTSP();                   //solve the TSP problem
  private:
    void allocateTSPCache_();           //allocate dyn prog cache
    void freeTSPCache_();               //deallocate cache

    vector<Coord> cities_;
    float **cache_;
    unsigned int rows_;
    unsigned int cols_;
};

void TSPProblem::readCities(const char* file)
{
    std::ifstream input(file);
    unsigned int numCities;
    input >> numCities;
    for (unsigned int i=0; i<numCities; i++) {
        float x, y;
        input >> x >> y;
        cities_.push_back(std::make_pair(x, y));
    }
}

void TSPProblem::allocateTSPCache_()
{
    assert(cities_.size() < SIZEOFINT);
    rows_ = 1 << cities_.size();
    cols_ = cities_.size();

    cache_ = new float*[rows_];
    for (unsigned int i=0; i<rows_; i++) {
        cache_[i] = new float[cols_];
    }

    for (unsigned int i=0; i<rows_; i++) {
        for (unsigned int j=0; j<cols_; j++) {
            cache_[i][j] = 0;
        }
    }
}

void TSPProblem::freeTSPCache_()
{
    for (unsigned int i=0; i<rows_; i++) {
        delete [] cache_[i];
    }

    delete [] cache_;
}

float TSPProblem::solveTSP()
{
    allocateTSPCache_();

    //base cases
    {
        for (unsigned int i=0; i<rows_; i++) {
            cache_[i][0] = std::numeric_limits<float>::max();
        }
        Subset s; s.add(0);
        cache_[s.repr()][0] = 0; // from node to itself using exactly itself
    }

    //meat of the algorithm
    for (unsigned int m=2; m <= cities_.size(); m++) {      //subset size (including 0)
        vector<Subset> subsets;
        getSubsets(subsets, m, cities_.size());

        for (const Subset& s : subsets) {

            for (unsigned int j=1; j<cities_.size(); j++) { //omit start node 0
                if (!(s.contains(j))) {                     // omit stuff not in subset
                    continue;
                }

                Subset sprime(s);
                sprime.remove(j);

                float minval = std::numeric_limits<float>::max();
                for (unsigned int k=0; k<cities_.size(); k++) {
                    if (!(s.contains(k)) || k == j) {
                        continue;
                    }
                    float localCost = cache_[sprime.repr()][k] + distance(cities_[k], cities_[j]);
                    if (localCost < minval) {
                        minval = localCost;
                    }
                }
                cache_[s.repr()][j] = minval;
            }
        }
    }

    //finally find minimum of all paths computed so far
    float minval = std::numeric_limits<float>::max();
    {
        Subset s;
        for (unsigned int i=0; i<cities_.size() ; i++) {
            s.add(i);
        }
        for (unsigned int j=1; j < cities_.size(); j++) {
            float localCost = cache_[s.repr()][j] + distance(cities_[j], cities_[0]);
            if (localCost < minval) {
                minval = localCost;
            }
        }
    }

    return minval;
}

//////////////////////////////////////////////////////////////////////////////////

int main(int argc, char* argv[])
{
    if (argc <= 1) {
        std::cout << "Usage: ./travelingSalesman ipfile" << std::endl;
        exit(1);
    }

    TSPProblem tsp;
    tsp.readCities(argv[1]);

    float ans = tsp.solveTSP();

    std::cout << "Answer = " << ans << std::endl;
}


