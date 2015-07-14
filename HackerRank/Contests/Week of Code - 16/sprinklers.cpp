// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <limits>

using std::vector;

typedef unsigned long long Cost;

class Sprinklers {
public:
    Sprinklers();
    void solveProblem();
private:
    void readInput();
    void determineQMinMax();
    void printSolution();
    bool done(const vector<bool>& sat);
    vector<bool> placeRoses(int qrange);
    void rollbackLeftIfNeeded(int qrange, int& rightpointer);
    void rollbackRightIfNeeded(int qrange, int& rightpointer);
    Cost computeCost(int numSpr, int qup);

    int numRoses; //the number of roses in the garden
    Cost qcost;            //the cost to increase range by unit amount
    Cost scost;            //the cost for each sprinkler
    int numAvail; //the number of positions available
    vector<bool> ms;       //the actual positions that are available

    int qmin, qmax;       //these are the minimum and maximum times I should increase the range
    int qst, qend;
    vector<bool> finalSPos;//the places where sprinklers should be placed
    int finalq;           //the final amount by which range must be increased
};

Sprinklers::Sprinklers() 
: numRoses(0), qcost(0), scost(0), numAvail(0), ms(), 
  qmin(0), qmax(0), qst(0), qend(0),
  finalSPos(), finalq(0) {
      readInput();
}

void Sprinklers::readInput() {
    std::cin >> numRoses >> numAvail;
    std::cin >> scost >> qcost;

    ms = finalSPos = vector<bool>(numRoses, false);

    for (int i=0; i<numAvail; i++) {
        int pos; std::cin >> pos;
        pos -= 1; //make 0-indexed
        ms[pos] = true;
    }
}

void Sprinklers::determineQMinMax() {
    //determining the minimum value of q upgrades needed
    int lenseq = 0;
    for (int i=0; i<ms.size(); i++) {
        if (ms[i] == false) lenseq++; else break;
    }
    qst = lenseq;
    lenseq = 0;
    for (int i=ms.size()-1; i>=0; i--) {
        if (ms[i] == false) lenseq++; else break;
    }
    qend = lenseq;
    lenseq = 0;
    int qcand=0; 
    for (int i=0; i<ms.size(); i++) {
        if (ms[i] == false) {
            lenseq++;
        } else {
            qcand = (lenseq > qcand) ? lenseq : qcand;
            lenseq = 0;
        }
    }
    qcand = (lenseq > qcand) ? lenseq : qcand;
    qcand = qcand/2 + qcand%2; //ceiling value

    qmin = std::max(qcand, std::max(qst, qend));

    qmax = ms.size()-1;
    return;
}

bool Sprinklers::done(const vector<bool>& sat) {
    for (int i=0; i<sat.size(); i++) {
        if (sat[i] == false) return false;
    }
    return true;
}

void Sprinklers::rollbackLeftIfNeeded(int qrange, int& leftpointer) {
    int ctr = qrange;
    while (ctr && leftpointer > 0 && (ms[leftpointer] == false)) { //this was watered, or I cant place here, rollback
        leftpointer--;
    }
}

void Sprinklers::rollbackRightIfNeeded(int qrange, int& rightpointer) {
    int ctr = qrange;
    while (ctr && rightpointer < numRoses-1 && (ms[rightpointer] == false)) { //this was watered, or I cant place here, rollback
        rightpointer++;
    }
}

// will service greedily from L, R, L, R extreme intervals
vector<bool> Sprinklers::placeRoses(int qrange) {
    vector<bool> sat(numRoses, false); //initial all unsatisfied
    vector<bool> sprinklerPlacements(numRoses, false);
    int leftover = numRoses;

    int leftpointer = qrange, rightpointer = ms.size()-1-qrange;
    rollbackLeftIfNeeded(qrange, leftpointer);
    rollbackRightIfNeeded(qrange, rightpointer);

    while (leftover) {

        //place sprinkler on left
        sprinklerPlacements[leftpointer] = true;
        for (int i=std::max(0, leftpointer-qrange); i<=std::min(leftpointer+qrange, numRoses-1); i++) {
            if (sat[i] == false) {
                leftover--;
                sat[i] = true; //watered these roses
            }
        }
        int ctr=0;
        while ((ctr < 2 * qrange + 1) && leftpointer < numRoses-1) { //get next position
            leftpointer++; ctr++;
        }
        rollbackLeftIfNeeded(qrange, leftpointer);
        if (leftover == 0) {
            return sprinklerPlacements;
        }

        //place sprinkler on right
        sprinklerPlacements[rightpointer] = true;
        for (int i=std::min(numRoses-1, rightpointer+qrange); i>= std::max(0, rightpointer - qrange); i--) {
            if (sat[i] == false) {
                leftover--;
                sat[i] = true; //watered these roses
            }
        }
        ctr=0;
        while ((ctr < 2 * qrange + 1) && rightpointer > 0) { //get next position
            rightpointer--; ctr++;
        }
        rollbackRightIfNeeded(qrange, rightpointer);
        if (leftover == 0) {
            return sprinklerPlacements;
        }
    }

    return sprinklerPlacements;
}

Cost Sprinklers::computeCost(int numSpr, int qup) {
    Cost sprinklerCost = numSpr * scost;
    Cost rangeCost     = qup * qcost;
    return (sprinklerCost + rangeCost);
}

void Sprinklers::printSolution() {
    int finalscnt = 0;
    for (int i=0; i<finalSPos.size(); i++) {
        if (finalSPos[i]) finalscnt++;
    }
    std::cout << finalscnt << " " <<  finalq << std::endl;
    for (int i=0; i<numRoses; i++) {
        if (finalSPos[i]) std::cout << (i+1) << " ";
    }
    std::cout << std::endl;
}

void Sprinklers::solveProblem() {
    determineQMinMax();
    Cost finalCost = std::numeric_limits<Cost>::max();

    for (int qup = qmin; qup <= qmax; qup++) { //maybe binary search later?
        vector<bool> places = placeRoses(qup);

        int numSpr = 0;
        for (int i=0; i<places.size(); i++) {
            if (places[i]) numSpr++;
        }

        Cost cand = computeCost(numSpr, qup);
        if (cand < finalCost) {
            finalCost = cand;
            finalSPos = places;
            finalq = qup;
        }

        if (numSpr == 1) {
            break; //any further increases in q value just increases cost
        }
    }

    printSolution();
}


int main() {
    unsigned int tc; std::cin >> tc;
    for (unsigned int i=0; i<tc; i++) {
        Sprinklers sprinklers; 
        sprinklers.solveProblem();
    }
}


