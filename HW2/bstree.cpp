#include "bstree.h"
#include <iostream>
//#include "DynStack.h"

using namespace std;

template <class type>
bstree<type>::bstree() {
	root = nullptr;
}

template <class type>
void bstree<type>::
dhelper(tnode<type>* node) {
	if (node != nullptr) {
		dhelper(node->left);
		dhelper(node->right);
		delete node;
	}
    
}

template <class type>
       void bstree<type>::remove
                                    ( const type & x )
       {
              rhelper( x, root );
       }


template <class type>
tnode<type> * bstree<type>::findMin( tnode<type> *t ) const
        {
            if( t == NULL )
                return NULL;
            if( t->left == NULL )
                return t;
            return findMin( t->left );
        }

template <class type>
void bstree<type>::rhelper( const type & x, tnode<type> * & t )
                                    const
        {
            if( t == NULL )
                return;   // Item not found; do nothing
            if( t->val > x )
                rhelper( x, t->left );
            else if( t->val < x )
                rhelper( x, t->right );
            
            else if( t->left != NULL && t->right != NULL ) // Two children
           {
               t->val = findMin( t->right )->val;
               rhelper( t->val, t->right );
           }
           else // one or no children
           {
               tnode<type> *oldNode = t;
               t = ( t->left != NULL ) ? t->left : t->right;
               delete oldNode;
           }
       }


template <class type>
bstree<type>::~bstree() {
	//dhelper(root);
}

template <class type>
bool bstree<type>::shelper(type val, tnode<type>* node) {
	if (node == nullptr)
		return false;
	else if (node->val == val)
		return true;
	else if (node->val > val)
		return (shelper(val, node->left));
	else if (node->val < val)
		return (shelper(val, node->right));
	else
		return false;
}

template <class type>
type* bstree<type>::shelpermodified(type & val, tnode<type>* node) {
    if (node == nullptr)
        return nullptr;
    else if (node->val == val)
        return &node->val;
    else if (node->val > val)
        return (shelpermodified(val, node->left));
    else if (node->val < val)
        return (shelpermodified(val, node->right));
    else
        return nullptr;
}

template <class type>
bool bstree<type>::search(type val) {
	return (shelper(val, root));
}

template <class type>
type* bstree<type>::searchItem(type elem){
    return (shelpermodified(elem, root));
}

//note the use of reference variable - in the lecture we used pointerd
template <class type>
bool bstree<type>::ihelper(type val, tnode<type> * &node) {
	if (node == nullptr) {
        node = new tnode<type>(nullptr,nullptr,val);
	  return true;
	} else if (node->val > val) {
		return (ihelper(val, node->left));
	} else  if (node->val < val) {
		return (ihelper(val, node->right));
	} else  if (node->val == val) {
		return false;
	}
    return false;
}

template <class type>
void bstree<type>::insert(type val) {
	if( (ihelper(val, root))) {
		//cout << 1 << " is inserted." << endl;
	} else {
		//cout << val.title << " already exists." << endl;
	}
}

template <class type>
void bstree<type>::phelper(tnode<type>* node) {
	//TODO: Recursive implementation of inorder print
    if (node == NULL)
            return;
     
        /* first recur on left child */
        phelper(node->left);
     
        /* then print the data of node */
        cout << node->val << endl;
     
        /* now recur on right child */
        phelper(node->right);
}

template <class type>
void bstree<type>::printInOrderRecursive() {
	phelper(root);
	
}
/*
void bstree::printInOrderIterative() {
	DynStack stack;
	tnode* node = root;
	while (!stack.isEmpty() || node) {
		if (node) {
			stack.push(node);
			node = node->left;
		} else {
			stack.pop(node);
			cout << node->val << " ";
			node = node->right;
		}
	}
	cout << endl;
}

*/
