#include <iostream>

struct MaxHeap
{
    int *values;
    int heapSize = 4;
    int lasti = 0;

    MaxHeap(){
        values = new int[heapSize];
    }
    
};

bool heapFull(MaxHeap* heap)
{
    if(heap->lasti + 1 == heap->heapSize) return true;
    return false;
}

void expandHeap(MaxHeap* heap)
{
    heap->heapSize *= 2;

    int *newVals = new int[heap->heapSize];
    for(int i = 0; i < heap->lasti; i++)
    {
        newVals[i] = heap->values[i];
    }

    delete heap->values;
    heap->values = newVals;
}


void heapifyUp(MaxHeap *heap, int i)
{
    if(i == 0) return;
    if(heap->values[i / 2] > heap->values[i]) return;
    
    int tmp = heap->values[i];
    heap->values[i] = heap->values[i / 2];
    heap->values[i / 2] = tmp;

    heapifyUp(heap, i / 2);

}


void addElement(MaxHeap *heap, int element)
{
    if(heapFull(heap))
    {
        expandHeap(heap);
    }

    heap->values[heap->lasti] = element;

    heapifyUp(heap, heap->lasti);

    heap->lasti++;
}

int peakTop(MaxHeap* heap)
{
    return heap->values[0];
}

void heapifyDown(MaxHeap* heap, int i)
{
    if(2 * i < heap->lasti)
    {
        int max = heap->values[i], maxi = i;
        maxi = max > heap->values[2 * i] ? maxi : 2 * i; 
        max = max > heap->values[2 * i ] ? max : heap->values[2 * i];

        if(2 * i + 1 < heap->lasti)
        {
            maxi = max > heap->values[2 * i + 1] ? maxi : 2 * i + 1; 
            max = max > heap->values[2 * i + 1] ? max : heap->values[2 * i + 1];
        }

        if(maxi == i) return;
        
        heap->values[maxi] = heap->values[i];
        heap->values[i] = max;

        heapifyDown(heap, maxi);
    }
    
}

void popTop(MaxHeap* heap)
{
    if(heap->lasti == 0) return;
    int max = heap->values[0];

    heap->values[0] = heap->values[heap->lasti - 1];
    heap->lasti--;
    heapifyDown(heap, 0);

}

void printHeap(MaxHeap* heap)
{
    for(int i = 0; i < heap->lasti; i++)
    {
        std::cout << heap->values[i] << " ";
    }
}

int main()
{
    int n; std::cin >> n;

    MaxHeap *heap = new MaxHeap();

    for(int i = 0; i < n; i++)
    {
        int k; std::cin >> k;
        addElement(heap, k);
    }

    popTop(heap);
    popTop(heap);
    popTop(heap);

    printHeap(heap);

    return 0;
}