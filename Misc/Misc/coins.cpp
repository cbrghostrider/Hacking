#include <algorithm>
#include <tuple>
#include <functional>
#include <ostream>
#include <iostream>
#include <numeric>

using std::cout;
using std::endl;
using std::tuple;
using std::vector;
using std::get;
using std::make_tuple;
using std::transform;
using std::function;
using std::bind;
using std::accumulate;
using namespace std::placeholders;

typedef unsigned int UInt;
typedef UInt Amt;
typedef vector<tuple<Amt, UInt> > Ways;
typedef tuple<Amt, Amt, Ways> UseRemWays;  //tuple of (amount used, amount remaining, (num, deno) list of coins used)

vector<UseRemWays> applyAmt(const Amt deno, UseRemWays urw)
{
    //we are going to try these number of coins of denomination deno
    vector<UInt> numCoins;
    for (UInt i=0; i<=(get<1>(urw))/deno; i++) {numCoins.emplace_back(i);}

    vector<UseRemWays> retVal(numCoins.size());
    transform(numCoins.begin(), numCoins.end(), retVal.begin(), [deno, urw] (UInt nc) -> UseRemWays {
        auto partWay = get<2>(urw);
        partWay.emplace_back(make_tuple(deno, nc));
        return make_tuple(get<0>(urw) + nc*deno, get<1>(urw) - nc*deno, partWay);
    });

    return retVal;
}

//list monad bind (>>=) function
// (>>=) ::m a -> (a -> m b) -> m b
template <typename T1, typename T2>
vector<T2> listMonadBindFunc(vector<T1> lhs, function<vector<T2> (T1)> rhsFunc)
{
    vector<vector<T2> >  result(lhs.size());
    transform(lhs.begin(), lhs.end(), result.begin(), rhsFunc);

    vector<T2> retVal;
    for_each (result.begin(), result.end(), [&retVal] (vector<T1>& vec) -> void {retVal.insert(retVal.end(), vec.begin(), vec.end());});

    return retVal;
}

UInt numCombos(Amt amount)
{
    //all the coin denominations we have
    vector<Amt> amts = {200, 100, 50, 20, 10, 5, 2, 1};

    //make a vector of curried functions that apply a specific denomination
    vector<function<vector<UseRemWays> (UseRemWays)> > amtFuncs(amts.size());
    transform(amts.begin(), amts.end(), amtFuncs.begin(), 
    [] (Amt amt) -> function<vector<UseRemWays> (UseRemWays)> {return bind(applyAmt, amt, _1);} );

    //fold the vector of curried functions, using listMonadBindFunc
    vector <UseRemWays> initAccum; initAccum.push_back(make_tuple(0, amount, Ways()));
    vector <UseRemWays> ans = accumulate(amtFuncs.begin(), amtFuncs.end(), initAccum, listMonadBindFunc<UseRemWays, UseRemWays>);

    //not all combos used the entire amount, so filter out those that didn't consume amount
    vector<UseRemWays> retVal;
    for_each (ans.begin(), ans.end(), [&retVal] (UseRemWays urw) -> void {if (get<1>(urw) == 0) retVal.emplace_back(urw);} );

    return retVal.size();

}

int main()
{
    cout << "Num of ways to make 200 pence is " << numCombos (200) << std::endl;
}

