//
//  Stack.cpp
//  cs300_hw1
//
//  Created by Ahmet Ömer Kayabaşı on 11.03.2021.
//

#include "Stack.h"
#include <iostream>
using namespace std;

//************************************************
// Constructor to generate an empty stack.       *
//************************************************
template <class type>
Stack<type>::Stack()
{
    top = NULL;
    size = 0;
}


//************************************************
// Member function push pushes the argument onto *
// the stack.                                    *
//************************************************
template <class type>
void Stack<type>::push(type num)
{
    StackNode<type> *newNode;

    // Allocate a new node & store Num
    newNode = new StackNode<type>;
    newNode->elem = num;

    // If there are no nodes in the list
    // make newNode the first node
    if (isEmpty())
    {
        top = newNode;
        newNode->down = NULL;
    }
    else    // Otherwise, insert NewNode before top
    {
        newNode->down = top;
        top = newNode;
    }
    size++;
}

//****************************************************
// Member function pop pops the value at the top     *
// of the stack off, and copies it into the variable *
// passed as an argument.                            *
//****************************************************
template <class type>
void Stack<type>::pop(type &num)
{
    StackNode<type> *temp;

    if (isEmpty())
    {
        cout << "The stack is empty.\n";
    }
    else    // pop value off top of stack
    {
        num = top->elem;
        temp = top->down;
        delete top;
        top = temp;
    }
    size--;
}

//****************************************************
// Member funciton isEmpty returns true if the stack *
// is empty, or false otherwise.                     *
//****************************************************
template <class type>
bool Stack<type>::isEmpty(void)
{
    bool status;

    if (top == NULL)
        status = true;
    else
        status = false;

    return status;
}

template <class type>
void Stack<type>::initReverse(){
    
    StackNode<type>* head = top;
    
    while (head->down != NULL) {
        head->down->up = head;
        head = head->down;
    }
    bottom = head;
}


template <class type>
type& Stack<type>::peek() const{
    return top->elem;
}

