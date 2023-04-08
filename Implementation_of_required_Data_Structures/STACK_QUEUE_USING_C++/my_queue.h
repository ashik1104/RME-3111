// QUEUE IMPLEMENTATION USING LINKED LIST //

#include <bits/stdc++.h>
using namespace std;

template <typename n>
class queue_node
{
public:
    n value;
    queue_node *next;

    queue_node(n val)
    {
        this->value = val;
        this->next = NULL;
    }
};

template <typename Q>
class Queue
{
public:
    queue_node<Q> *front;
    queue_node<Q> *rear;

    Queue()
    {
        front = NULL;
        rear = NULL;
    }

    // enqueue --> push
    void push(Q val)
    {
        queue_node<Q> *newnode = new queue_node<Q>(val);

        if (front == NULL)
        {
            front = newnode;
            rear = newnode;
            return;
        }

        rear->next = newnode;
        rear = rear->next;
    }

    // dequeue --> pop
    Q pop()
    {
        Q return_value;
        if (rear == NULL)
        {
            cout << "Queue underflow | there is no element in the queue" << endl;
            return return_value;
        }
        queue_node<Q> *delnode;
        delnode = front;
        front = front->next;
        if (front == NULL)
        {
            rear = NULL;
        }
        return_value = delnode->value;
        delete delnode;
        return return_value;
    }

    // peak --> Front(), Back()
    Q Front()
    {
        Q f_val;
        f_val = front->value;
        return f_val;
    }

    Q Back()
    {
        Q r_val;
        r_val = rear->value;
        return r_val;
    }

    // empty()
    bool empty()
    {
        if (front == NULL && rear == NULL)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
};