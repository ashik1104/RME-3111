// STACK USING LINKED LIST //

#include <bits/stdc++.h>
using namespace std;

template <typename N>
class node
{
public:
    N value;
    node *next;
    node *prev;

    node(N val)
    {
        this->value = val;
        this->next = NULL;
        this->prev = NULL;
    }
};

template <typename S>
class Stack
{
public:
    node<S> *head;
    node<S> *top;
    int count = 0;

    Stack()
    {
        head = NULL;
        top = NULL;
    }

    // PUSH OPERATION
    // time complexity = O(n)
    void push(S val)
    {
        node<S> *newnode = new node<S>(val);
        if (head == NULL)
        {
            head = top = newnode;
            count++;
            return;
        }

        top->next = newnode;
        newnode->prev = top;
        top = newnode;
        count++;
    }

    // POP OPERATION
    S pop()
    {
        node<S> *delnode;
        delnode = top;
        S pop_return;

        if(head == NULL) // stack is empty
        {
            cout << "Stack underflow" << endl;
            return pop_return;
        }
        else if (top == head) // There is only 1 element
        {
            top = head = NULL;
        }
        else // there is more than 1 element
        {

            top = delnode->prev;
            top->next = NULL;
        }
        pop_return = delnode->value;
        delete delnode;
        count--;
        return pop_return;
    }

    // EMPTY CHECK
    bool empty()
    {
        if(head == NULL)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    // TOP
    S Top()
    {
        S top_val;
        if(top == NULL)
        {
            cout << "stack underflow | there is no elment in the top" << endl;
            return top_val;
        }
        else
        {
            top_val = top->value;
            return top_val;
        }
    }

    // SIZE
    int size()
    {
        return count;
    }
};
