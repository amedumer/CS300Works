//
//  Stack.hpp
//  cs300_hw1
//
//  Created by Ahmet Ömer Kayabaşı on 11.03.2021.
//

#ifndef Stack_hpp
#define Stack_hpp

#include <stdio.h>
#include <iostream>

using namespace std;


extern int rowCount[20];
extern int colCount[20];
extern int diagCount[39];
extern int reverseDiagCount[39];
extern int SIZE;

template <class type>
struct StackNode
{
    type elem;
    StackNode *down, *up;
};

struct cell {
    int x_coordinate,y_coordinate;
    bool visited,has_pawn,has_knight;
    
    int directions[8] = {0};
    
    cell(int x,int y):x_coordinate(x),y_coordinate(y),visited(false),has_pawn(false),has_knight(false){
        
    }
    cell():x_coordinate(0),y_coordinate(0),visited(false),has_pawn(false){}
    
    void pawn_status(bool st){
        if (st) {
            
            if (!has_pawn) {
                rowCount[x_coordinate]++;
                colCount[y_coordinate]++;
                diagCount[x_coordinate + y_coordinate - 1]++;
                reverseDiagCount[ SIZE - x_coordinate + y_coordinate]++;
            }
            
            has_pawn = true;
        }
        else if (!st){
            
            if (has_pawn) {
                rowCount[x_coordinate]--;
                colCount[y_coordinate]--;
                diagCount[x_coordinate + y_coordinate - 1]--;
                reverseDiagCount[ SIZE - x_coordinate + y_coordinate]--;
            }
            
            has_pawn = false;
        }
    }
};

template <class type>
class Stack {
private:
    StackNode<type>* top;
    StackNode<type>* bottom;
    
public:
    int size;
    Stack(void);
    void push(type);
    void pop(type &);
    bool isEmpty(void);
    type& peek() const;
    void initReverse();
    
    
    type& operator[](int x){
        // in order to improve efficiency, Stack search starts either from top or bottom given index number.
        if (x > (size / 2)) {
            StackNode<type>* temp = top;
            
            for (int i = 0; i < size - x - 1; i++) {
                temp = temp->down;
            }
            return temp->elem;
        }
        else{
            StackNode<type>* temp = bottom;
            
            for (int i = 0; i < x; i++) {
                temp = temp->up;
            }
            return temp->elem;
        }
        
    }
    
};



#endif /* Stack_hpp */
