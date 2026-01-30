#pragma once

#include <vector>

#define TYPE int

struct DisjointSet
{
    private:
    std::vector<int> parents;
    std::vector<int> degrees;
    int size = 0;

    public:

    DisjointSet();

    DisjointSet(int setCount);

    int pushSets(int setCount);

    int find(int element);

    void disjointUnion(int setA, int setB);

    void printSet();

};