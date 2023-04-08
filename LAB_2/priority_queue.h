#include <bits/stdc++.h>
using namespace std;

// using min heap //

template <typename h>
class Priority_Queue
{
    vector<h> array;

public:
    Priority_Queue()
    {
        ;
    }

    void reheap_up(vector<h> &a, int index)
    {
        int parent = (index - 1) / 2;
        while (index >= 0 and a[index] < a[parent])
        {
            swap(a[index], a[parent]);
            index = parent;
            parent = (index - 1) / 2;
        }
    }

    void reheap_down(vector<h> &a, int size, int current)
    {
        int smallest = current;
        int left = 2 * current + 1;
        int right = 2 * current + 2;

        if (left < size && a[left] < a[smallest])
        {
            smallest = left;
        }
        if (right < size && a[right] < a[smallest])
        {
            smallest = right;
        }
        if (smallest != current)
        {
            swap(a[current], a[smallest]);
            reheap_down(a, size, smallest);
        }
    }

    void push(h value)
    {
        array.push_back(value);
        int index_of_last_added_node = array.size() - 1;
        reheap_up(array, index_of_last_added_node);
    }

    void pop()
    {
        swap(array.front(), array.back());
        array.pop_back(); // decrement the array size ////
        reheap_down(array, array.size(), 0);
    }

    h top()
    {
        return array.front();
    }

    bool empty()
    {
        return array.empty();
    }
};
