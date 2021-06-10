//
//  avlTree.h
//  cs300_hw2
//
//  Created by Ahmet Ömer Kayabaşı on 7.04.2021.
//

#ifndef avlTree_h
#define avlTree_h
#include <vector>

template <class Comparable>
       class AvlTree;

       template <class Comparable>
       class AvlNode
       {
              Comparable     element;
              AvlNode           *left;
              AvlNode           *right;
           int                height;

              AvlNode( const Comparable & theElement,
                         AvlNode *lt, AvlNode *rt, int h = 0 )
                   : element( theElement ), left( lt ), right( rt ), height( h ) { }

             friend class AvlTree<Comparable>;
       };

template <class Comparable>
        class AvlTree
        {
             public:
            
            
            
            
                AvlTree();
                 explicit AvlTree( const Comparable & notFound );
            
            AvlTree( const AvlTree & rhs ){
                root = nullptr;
                    std::vector<AvlNode<Comparable> const*> remaining;
                    AvlNode<Comparable> const* cur = rhs.root;
                    while (cur) {
                      insert(cur->element);
                      if (cur->right) {
                        remaining.push_back(cur->right);
                      }
                      if (cur->left) {
                        cur = cur->left;
                      }
                      else if (remaining.empty()) {
                        break;
                      }
                      else {
                        cur = remaining.back();
                        remaining.pop_back();
                      }
                    }
            }
               //~AvlTree( );

                const Comparable & findMin( ) const;
                const Comparable & findMax( ) const;
                Comparable* find(  Comparable  x );
                bool isEmpty( ) const;
                void printTree( ) const;
            void printInOrderRecursive();
                void makeEmpty( );
                void insert( const Comparable & x );
                
            void remove(  AvlNode<Comparable> * & t,const Comparable & x ) ;

            const AvlTree & operator=( const AvlTree & rhs ){
                static const AvlTree<Comparable> newTree(rhs);
                
                return newTree;
            };
            AvlNode<Comparable> *root;
        private:
            
                //const Comparable ITEM_NOT_FOUND;
            Comparable * shelpermodified(Comparable & val, AvlNode<Comparable>* node);
                const Comparable & elementAt( AvlNode<Comparable> *t ) const;
            void phelper(AvlNode<Comparable>* node);
                void insert( const Comparable & x, AvlNode<Comparable> * & t ) const;
                

                AvlNode<Comparable> * findMin( AvlNode<Comparable> *t ) const;
                AvlNode<Comparable> * findMax( AvlNode<Comparable> *t ) const;
                AvlNode<Comparable> * find( const Comparable & x, AvlNode<Comparable> *t )const;
                void makeEmpty( AvlNode<Comparable> * & t ) const;
                void printTree( AvlNode<Comparable> *t ) const;
                AvlNode<Comparable> * clone( AvlNode<Comparable> *t ) const;
                         // Avl manipulations
                int height( AvlNode<Comparable> *t ) const;
                int max( int lhs, int rhs ) const;
                void rotateWithLeftChild( AvlNode<Comparable> * & k2 ) const;
                void rotateWithRightChild( AvlNode<Comparable> * & k1 ) const;
                void doubleWithLeftChild( AvlNode<Comparable> * & k3 ) const;
                void doubleWithRightChild( AvlNode<Comparable> * & k1 ) const;
                    };




#endif /* avlTree_h */
