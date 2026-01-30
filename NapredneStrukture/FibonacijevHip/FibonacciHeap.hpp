#include <iostream>
#include <list>
#include <vector>
#define TYPE int
#define ull unsigned long long

#pragma once

struct FibNode
{    
    TYPE value;
    bool grieving = false;
    std::list<FibNode*> children;    
    FibNode* parent;
    FibNode(TYPE value);

    void insertChild(FibNode* newHeap);

    TYPE getMin();

    int getDegree();

};

struct FibHeap
{       
    private: 
    FibNode *min = nullptr;
    ull maxElementCount = 0;
    ull currElementCount = 0;

    void FibUp(std::vector<FibNode*> &arr, FibNode* heap);

    int maxBinomialTreeDeg();

    public:

    TYPE getMin();

    ull size();

    void insert(TYPE value);

    void extractMin();
    
    void decreaseKey(FibNode *key, TYPE value);
};