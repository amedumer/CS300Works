#include "hash.h"
#include <string>
#include <vector>

using namespace std;

int LinkedList::createLinkedList(pair<vector<string>,double> name) {
	if (!pHead) {
		pHead = new Node(name, NULL);
		if (!pHead) {
			return -1;
		}
		size = 1;
		return 0;
	}
	else {
		return -1;
	}
}

int LinkedList::addHead(pair<vector<string>,double> name)
{
	if (!pHead) {
		return -1;
	}
	else {
		Node* pNode = new Node(name, pHead);
		pHead = pNode;
		++size;
		return 1;
	}
}

int LinkedList::deleteHead() {
	if (!pHead) {
		return -1;
	}
	else {
		Node* pDel = pHead;
		pHead = pHead->pNext;
		pDel->pNext = NULL;
		delete pDel;
		pDel = NULL;
		--size;
		return 1;
	}
}

int LinkedList::deleteTail()
{
	Node * pTemp = pHead;
	while (pTemp->pNext->pNext != NULL) {
		pTemp = pTemp->pNext;
	}
	Node * pDel = pTemp->pNext;
	delete pDel;
	pDel = NULL;
	pTemp->pNext = NULL;
	--size;
	return 1;
}
/*
void LinkedList::printHeadNode() {
	pHead->printInfo();
}
*/

Node* LinkedList::seekHeadNode() {
	return pHead;
}

Node* LinkedList::seekNode(int index) {
	if (index >= size) {
		return NULL;
	}
	else if (index == 0) {
		return pHead;
	}
	else {
		Node *pTemp{ pHead };
		for (int i{ 0 }; i < index; i++) {
			pTemp = pTemp->pNext;
		}
		return pTemp;
	}

}

Node* LinkedList::operator[](int index) {
	if (index >= size) {
		return NULL;
	}
	Node* pTemp = this->pHead;
	for (int i{ 0 }; i < index; i++) {
		pTemp = pTemp->pNext;
	}
	return pTemp;
}

int LinkedList::addTail(pair<vector<string>,double> name) {
	Node * pTemp = pHead;
	while (pTemp->pNext != NULL) {
		pTemp = pTemp->pNext;
	}
	pTemp->pNext = new Node(name);
	++size;
	return 1;
}

Node * LinkedList::getHeadPointer()
{
	return this->pHead;
}

int LinkedList::getSize()
{
	return this->size;
}

void LinkedList::setSize(int value)
{
	this->size = this->size + value;
}

LinkedList::LinkedList() {
	pHead = NULL;
	size = 0;
}


int Hash::hashFunction(vector<string> key)
{
    int sum = 0;
    
    for (int i = 0; i < key.size(); i++) {
        for (int j = 0; j < key[i].length(); j++) {
            sum += key[i][j];
        }
    }
    
	return sum % 13;
}

Hash::Hash()
{

}

int Hash::insert(pair<vector<string>,double> name)
{
	int hash{ hashFunction(name.first) };
    
	if (this->hashTable[hash].getHeadPointer() == NULL) {
		hashTable[hash].createLinkedList(name);
		return 1;
	}
	hashTable[hash].addTail(name);
	return 1;
}

bool Hash::findKey(pair<vector<string>,double> name)
{
	int hash{ hashFunction(name.first) };

	if (hashTable[hash].getSize() == 0) {
		return false;
	}

	Node* pTemp = hashTable[hash].getHeadPointer();
	while (pTemp != NULL) {
		if (pTemp->item.first == name.first) {
			return true;
		}
		pTemp = pTemp->pNext;
	}
	return false;
}

Node * Hash::findDeleteKey(pair<vector<string>,double> name)
{
	int hash{ hashFunction(name.first) };

	if (hashTable[hash].getSize() == 0) {
		return NULL;
	}

	Node* pTemp = hashTable[hash].getHeadPointer();
	while (pTemp != NULL) {
		if (pTemp->item.first == name.first) {
			return pTemp;
		}
		pTemp = pTemp->pNext;
	}
	return NULL;
}

int Hash::deleteKey(pair<vector<string>,double> name)
{
	if (!findKey(name)) {
		return -1;
	}
	int hash{ hashFunction(name.first) };

	Node* pTemp{ hashTable[hash].getHeadPointer() };
	if (pTemp->item.first == name.first) {
		hashTable[hash].deleteHead();
		return 1;
	}

	if (pTemp->pNext->pNext == NULL && pTemp->pNext->item.first == name.first ) {
		hashTable[hash].deleteTail();
		return 1;
	}

	while (pTemp->pNext != NULL) {
		if (pTemp->pNext->item.first == name.first) {
			Node* pDel = pTemp->pNext;
			pTemp->pNext = pTemp->pNext->pNext;
			delete pDel;
			pDel = NULL;
			hashTable[hash].setSize(-1);
			return 1;
		}
		pTemp = pTemp->pNext;
	}
    
    return 0;
}

vector<pair<vector<string>, double >> Hash::indexItems(int i)  {
    vector<pair<vector<string>, double > > tbr;
    
    for (int j = 0; j < hashTable[i].getSize(); j++) {
        tbr.push_back(hashTable[i].seekNode(j)->item);
    }
    
    return tbr;
}
