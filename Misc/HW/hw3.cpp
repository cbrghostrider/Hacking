#include <iostream>
#include <cstdio>
#include <vector>

struct Item {
  unsigned long long value;
  unsigned long long weight;
  Item (unsigned long long v, unsigned long long w) : value(v), weight(w) {}
};

void readProblem (std::vector<Item>& items, unsigned long long& wt) 
{
    unsigned int number;
    std::cin >> wt >> number;
    for (unsigned int i=0;i<number; i++) {
        unsigned long long value=0, weight=0;
        std::cin >> value >> weight;
        items.push_back(Item(value, weight));
    }
}

unsigned long long solveProblem (const std::vector<Item>& items, unsigned long long weight)
{
    unsigned long long ** arr = new unsigned long long*[2];
    arr[0] = new unsigned long long[weight];
    arr[1] = new unsigned long long[weight];

    for (unsigned int w=0; w<weight+1; w++) {
        arr[0][w] = 0;
    }

    unsigned int last_iter = 0;
    unsigned int this_iter = 1;

    for (unsigned int i=1; i<items.size()+1; i++) {
        for (unsigned int w=0; w<weight+1; w++) {
            unsigned int ci = i-1;
            unsigned long long opt1 = arr[last_iter][w];
            unsigned long long opt2 = (w < items[ci].weight ) ? 0 : arr[last_iter][w-items[ci].weight] + items[ci].value;
            arr[this_iter][w] = opt1 > opt2 ? opt1 : opt2;
        }
        last_iter = 1 - last_iter;
        this_iter = 1 - this_iter;
    }
    unsigned long long ret = arr[last_iter][weight];
    delete [] arr[1];
    delete [] arr[0];
    delete [] arr;

    return ret;
}

int main() 
{
    std::vector<Item> items;
    unsigned long long weight=0;

    readProblem(items, weight);
    unsigned long long answer = solveProblem(items, weight);

    std::cout << "Answer = " << answer << std::endl;

}

