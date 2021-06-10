#include <string>
#include <vector>
#include <iostream>
#pragma once

using namespace std;

struct Node {
    pair<vector<string>,double> item;
	Node* pNext;

	Node() {
		pNext = NULL;
	}

	Node(pair<vector<string>,double> i):item(i),pNext(NULL) {}

	Node(pair<vector<string>,double> i, Node* pNext):item(i),pNext(pNext) {}

};


class LinkedList {
private:
	Node * pHead;
	int size;
public:
	int createLinkedList(pair<vector<string>,double>);
	int addHead(pair<vector<string>,double>);
	int addTail(pair<vector<string>,double>);
	int deleteHead();
	int deleteTail();
	//void printHeadNode();
	Node* seekHeadNode();
	Node* seekNode(int);
	Node* operator[](int);
	Node* getHeadPointer();
	int getSize();
	void setSize(int value);
	LinkedList();
};

class Hash {
private:
	LinkedList hashTable[13];
	
public:
    // BUNU IMPLEMENT EDIYORSUN
    vector<pair<vector<string>, double >> indexItems(int i) ;
	int insert(pair<vector<string>,double>);
	bool findKey(pair<vector<string>,double>);
	Node* findDeleteKey(pair<vector<string>,double>);
	int deleteKey(pair<vector<string>,double>);
	int hashFunction(vector<string>);
	Hash();
};
