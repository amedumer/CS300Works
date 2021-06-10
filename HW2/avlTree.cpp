//
//  avlTree.cpp
//  cs300_hw2
//
//  Created by Ahmet Ömer Kayabaşı on 7.04.2021.
//

#include "avlTree.h"
#include <iostream>

using namespace std;

template <class Comparable>
AvlTree<Comparable>::AvlTree(){
    root = nullptr;
    //ITEM_NOT_FOUND = nullptr;
}

/**
        * Return the height of node t, or -1, if NULL.
*/
template <class Comparable>
int AvlTree<Comparable>::height( AvlNode<Comparable> *t )
const
{
       if (t == NULL)
          return -1;
   
     return t->height;
}

template <class Comparable>
void AvlTree<Comparable>::insert( const Comparable & x ){
    insert(x, root);
}

/**
        * Return maximum of lhs and rhs.
*/
template <class Comparable>
int AvlTree<Comparable>::max( int lhs, int rhs )
const
{
     if (lhs > rhs)
         return lhs;

     return rhs;
}

template <class Comparable>
void AvlTree<Comparable>::insert
                    ( const Comparable & x, AvlNode<Comparable> * & t ) const
{
     if ( t == NULL )
          t = new AvlNode<Comparable>( x, NULL, NULL );

     else if (t->element > x ) {
          // X should be inserted to the left tree!
          insert( x, t->left );
          
   // Check if the left tree is out of balance (left subtree grew in height!)
         if ( height( t->left ) - height( t->right ) == 2 ){
               if ( t->left->element > x)  // X was inserted to the left-left subtree!
                    rotateWithLeftChild( t );
               else {              // X was inserted to the left-right subtree!
                    doubleWithLeftChild( t );
               }
         }
      }
     else if( t->element < x )
     {    // Otherwise X is inserted to the right subtree
           insert( x, t->right );
         if ( height( t->right ) - height( t->left ) == 2 ){
      // height of the right subtree increased
                if ( t->right->element < x )
                   // X was inserted to right-right subtree
                      rotateWithRightChild( t );
                else{ // X was inserted to right-left subtree
                     doubleWithRightChild( t );
                }
         }
      }
      else
          ;  // Duplicate; do nothing
      
    // update the height the node
      t->height = max( height( t->left ), height( t->right ) ) + 1;
}

           
/**
  * Rotate binary tree node with left child.
  * For AVL trees, this is a single rotation for case 1.
  * Update heights, then set new root.
  */
 template <class Comparable>
 void AvlTree<Comparable>::rotateWithLeftChild(
             AvlNode<Comparable> * & k2 ) const
 {
        AvlNode<Comparable> *k1 = k2->left;
        k2->left = k1->right;
        k1->right = k2;
        k2->height = max( height( k2->left ), height( k2->right ) ) + 1;
        k1->height = max( height( k1->left ), k2->height ) + 1;
        k2 = k1;
 }

/**
 * Rotate binary tree node with right child.
 * For AVL trees, this is a single rotation for case 4.
 * Update heights, then set new root.
 */
template <class Comparable>
void AvlTree<Comparable>::rotateWithRightChild
            ( AvlNode<Comparable> * & k1 ) const
{
      AvlNode<Comparable> *k2 = k1->right;
      k1->right = k2->left;
      k2->left = k1;
      k1->height = max( height( k1->left ), height( k1->right ) ) + 1;
      k2->height = max( height( k2->right ), k1->height ) + 1;
      k1 = k2;
}

/**
  * Double rotate binary tree node: first left child.
  * with its right child; then node k3 with new left child.
  * For AVL trees, this is a double rotation for case 2.
  * Update heights, then set new root.
  */
 template <class Comparable>
 void AvlTree<Comparable>::doubleWithLeftChild
         ( AvlNode<Comparable> * & k3 ) const
 {
         rotateWithRightChild( k3->left );
         rotateWithLeftChild( k3 );
 }

/**
 * Double rotate binary tree node: first right child.
 * with its left child; then node k1 with new right child.
 * For AVL trees, this is a double rotation for case 3.
 * Update heights, then set new root.
 */
template <class Comparable>
void AvlTree<Comparable>::doubleWithRightChild
        ( AvlNode<Comparable> * & k1 ) const
{
       rotateWithLeftChild( k1->right );
       rotateWithRightChild( k1 );
}


template <class type>
void AvlTree<type>::phelper(AvlNode<type>* node) {
    //TODO: Recursive implementation of inorder print
    if (node == NULL)
            return;
     
        /* first recur on left child */
        phelper(node->left);
     
        /* then print the data of node */
        cout << node->element << endl;
     
        /* now recur on right child */
        phelper(node->right);
}

template <class type>
void AvlTree<type>::printInOrderRecursive() {
    phelper(root);
}

template <class type>
type* AvlTree<type>::shelpermodified(type & val, AvlNode<type>* node) {
    if (node == nullptr)
        return nullptr;
    else if (node->element == val)
        return &node->element;
    else if (node->element > val)
        return (shelpermodified(val, node->left));
    else if (node->element < val)
        return (shelpermodified(val, node->right));
    else
        return nullptr;
}

template <class type>
type* AvlTree<type>::find(type val)  {
    return (shelpermodified(val, root));
}


template <class T>
void AvlTree<T>::remove(  AvlNode<T> * & head, const T & x ) {
            if(head==NULL) return;
            if(head->element > x){
                remove(head->left, x);
            }else if(head->element < x){
                remove(head->right, x);
            }else{
                AvlNode<T> * r = head->right;
                if(head->right==NULL){
                    AvlNode<T> * l = head->left;
                    delete(head);
                    head = l;
                }else if(head->left==NULL){
                    delete(head);
                    head = r;
                }else{
                    while(r->left!=NULL) r = r->left;
                    head->element = r->element;
                    remove(head->right, r->element);
                }
            }
            if(head==NULL) return;
            head->height = 1 + max(height(head->left), height(head->right));
            int bal = height(head->left) - height(head->right);
            if(bal>1){
                if(height(head->left) >= height(head->right)){
                    rotateWithLeftChild(head);
                    return ;
                }else{
                    rotateWithRightChild(head->left);
                    rotateWithLeftChild(head);
                    return ;
                }
            }else if(bal < -1){
                if(height(head->right) >= height(head->left)){
                    rotateWithRightChild(head);
                    return ;
                }else{
                    rotateWithLeftChild(head->right);
                    rotateWithRightChild(head);
                    return ;
                }
            }
            return;
        }


/*
 
 template <class T>
 void AvlTree<T>::remove(  AvlNode<T> * & head, const T & x ) {
             if(head==NULL) return;
             if(head->element > x){
                 remove(head->left, x);
             }else if(head->element < x){
                 remove(head->right, x);
             }else{
                 AvlNode<T> * r = head->right;
                 if(head->right==NULL){
                     AvlNode<T> * l = head->left;
                     delete(head);
                     head = l;
                 }else if(head->left==NULL){
                     delete(head);
                     head = r;
                 }else{
                     while(r->left!=NULL) r = r->left;
                     head->element = r->element;
                     remove(head->right, r->element);
                 }
             }
             if(head==NULL) return;
             head->height = 1 + max(height(head->left), height(head->right));
             int bal = height(head->left) - height(head->right);
             if(bal>1){
                 if(height(head->left) >= height(head->right)){
                     rotateWithRightChild(head);
                     return ;
                 }else{
                     rotateWithLeftChild(head->left);
                     rotateWithRightChild(head);
                     return ;
                 }
             }else if(bal < -1){
                 if(height(head->right) >= height(head->left)){
                     rotateWithLeftChild(head);
                     return ;
                 }else{
                     rotateWithRightChild(head->right);
                     rotateWithLeftChild(head);
                     return ;
                 }
             }
             return;
         }

 */
