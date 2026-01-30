#include <iostream>
#include <list>
#include <vector>
#include "FibonacciHeap.hpp"
#define TYPE int
#define ull unsigned long long

FibNode::FibNode(TYPE value)
{
    this->parent = nullptr;
    this->value = value;
}

void FibNode::insertChild(FibNode* newHeap)
{
    children.push_back(newHeap);
    newHeap->parent = this;
}

TYPE FibNode::getMin()
{
    return value;
}

int FibNode::getDegree()
{
    return children.size();
}

void FibHeap::FibUp(std::vector<FibNode*> &arr, FibNode* heap)
{
    int n = heap->children.size();
    if(arr[n] != nullptr)
    {
        FibNode* comboHeap = arr[n];
        arr[n] = nullptr;

        if(heap->value < comboHeap->value)
        {
            heap->insertChild(comboHeap);
            FibUp(arr, heap);
        }
        else
        {
            comboHeap->insertChild(heap);
            FibUp(arr, comboHeap);
        }
    }
    else arr[n] = heap;
}

int FibHeap::maxBinomialTreeDeg()
{
    int k = 0; int t = maxElementCount;
    while(t)
    {
        t >>= 1;
        k++;
    }
    return k + 1;
}

TYPE FibHeap::getMin()
{
    return min->value;
}

ull FibHeap::size()
{
    return currElementCount;
}

void FibHeap::insert(TYPE value)
{
    FibNode* newChild = new FibNode(value);

    currElementCount++;
    maxElementCount = std::max(currElementCount, maxElementCount);
    //nothing to compare
    if(min == nullptr)
    {
        min = newChild;
        return;
    }
    //we have a new minimum?
    else if(value < min->value)
    {
        newChild->value = min->value;
        min->value = value;
    }
    min->insertChild(newChild);
}

void FibHeap::extractMin()
{
    //0 elements in heap?
    if(min == nullptr) return;
    //maintaining correct size
    currElementCount--;

    //only 1 element in heap
    if(min->getDegree() == 0)
    {
        delete min;
        min = nullptr;
        return;
    }

    //finding the new minimum
    FibNode* minHeap = *(min->children.begin());
    for(std::list<FibNode*>::iterator it = min->children.begin(); it != min->children.end(); it++)
    {
        if((*it)->value < minHeap->getMin())
        {    
            minHeap = *it;
        }
    }
    //extracting the children from the new minimum
    for(std::list<FibNode*>::iterator it = minHeap->children.begin(); it != minHeap->children.end(); it++)
    {
        min->children.push_back(*it);
    }
    minHeap->children.clear();

    //merging nodes with same degrees
    std::vector<FibNode*> a(maxBinomialTreeDeg(), nullptr);
    for(std::list<FibNode*>::iterator it = min->children.begin(); it != min->children.end(); it++)
    {
        if(*it != minHeap)
            FibUp(a, *it);
    }

    //switching the official minimum
    delete min;
    min = minHeap;

    //putting the fixed children back in the minimum
    for(int i = 0; i < a.size(); i++)
    {
        if(a[i] != nullptr)
            min->insertChild(a[i]);
    }
}

void FibHeap::decreaseKey(FibNode *key, TYPE value)
{
    FibNode* parent = key->parent;
    if(parent == nullptr)
    {
        key->value = value;
    }
    else
    {
        parent->children.remove(key);
        min->insertChild(key);
        if(parent->grieving)
        {
            decreaseKey(parent, parent->value);
            parent->grieving = false;
        }
        else
        {
            parent->grieving = true;
        }
    }
}