#ifndef _BTREE
#define _BTREE

#include <string>
#include <vector>
using namespace std;

class item {
public:
    
    bool operator < (const item & rhs){
        return rhs.title > title;
    }
    bool operator > (const item & rhs){
        return rhs.title < title;
    }
    bool operator == (const item & rhs){
        return rhs.title == title; // && info == rhs.info;
    }
    
    friend ostream &operator<<( ostream &of, const item &i ) {
             of << i.title;
             return of;
          }
    
    item(string t,string i):title(t),info(i){};

    string title,info;
    
    
};

template <class type>
class bstree;

template <class type>
class tnode {
 public:
    type val;
   tnode *left;
   tnode *right;
    
    tnode(tnode * l,tnode * r, type v):left(l),right(r),val(v){};
    
    friend class bstree<type>;
};

template <class type>
class bstree {
 public:
   bstree();
    bstree(const bstree & tree){
        root = nullptr;
            vector<tnode<type> const* > remaining;
        
            tnode<type> const* cur = tree.root;
            while (cur) {
              insert(cur->val);
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
   ~bstree();

   bool search(type Value);
   void insert(type Value);
   void printInOrderIterative();
   void printInOrderRecursive();
    void remove(const type & x );
    type* searchItem(type elem);
    tnode<type> *root;
 private:
    tnode<type> * findMin( tnode<type> *t ) const;
    void rhelper( const type & x, tnode<type> * & t )const;
   void dhelper(tnode<type> * Tree);
   void phelper(tnode<type> * Tree);
   bool shelper(type Value, tnode<type> * Tree);
    type* shelpermodified(type & Value, tnode<type> * Tree);
   bool ihelper(type Value, tnode<type> * &Tree);

    
};
#endif
