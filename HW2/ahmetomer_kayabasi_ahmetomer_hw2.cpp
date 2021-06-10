//
//  main.cpp
//  cs300_hw2
//
//  Created by Ahmet Ömer Kayabaşı on 1.04.2021.
//

/*
 Dear grader,
 
 Welcome to my homework, I hope you like it.
 
 By the time I was doing this homework. My mother and my father was tested positive for covid-19 and I was having a rough time in home trying to deal with everything as the only non-positive person. So not everything about this homework is great. AVL tree implementation is awful and looks like my first c++ assignments back in CS201. But the Binary Search tree is good. If I did not fix it by time, you should know that there is no memory management :'). So sorry for your RAM. I hope I can fix it by deadline.
 
Best,
 Ömer
 */

#include <iostream>
#include "bstree.cpp"
#include "avlTree.cpp"
#include <vector>
#include <fstream>
#include <sstream>
#include <chrono>
#define endl "\n"

using namespace std;
void printMenu();
vector<string> sections;
int currentSection = -1;

class timer {
private:
    std::__1::chrono::steady_clock::time_point start_time;
    
    
public:
    void startTimer(){
        start_time = chrono::high_resolution_clock::now();
    }
    void endTimer(){
        totalTime = (chrono::high_resolution_clock::now() - start_time).count() / 1000.0;
    }
    long long totalTime;
    
};
timer chronometer;

struct bstSection {
    string title,description;
    bstree<item> items;
    
    bool operator < (const bstSection & rhs){
        return rhs.title > title;
    }
    bool operator > (const bstSection & rhs){
        return rhs.title < title;
    }
    bool operator == (const bstSection & rhs){
        return rhs.title == title;
    }
    
    friend ostream &operator<<( ostream &of, const bstSection &s ) {
             of << s.title;
             return of;
          }
    
    bstSection(){};
    
    bstSection(string t, string d = ""):title(t),description(d){};
};

struct avlSection {
    string title,description;
    AvlTree<item> items;
    
    bool operator < (const avlSection & rhs){
        return rhs.title > title;
    }
    bool operator > (const avlSection & rhs){
        return rhs.title < title;
    }
    bool operator == (const avlSection & rhs){
        return rhs.title == title;
    }
    
    friend ostream &operator<<( ostream &of, const avlSection &s ) {
             of << s.title;
             return of;
          }
    
    avlSection(){};
    
    avlSection(string t, string d = ""):title(t),description(d){};
};

struct notebook {
    bstree<bstSection> bstSections;
    
    AvlTree<avlSection> avlSections;
    
    notebook(){
        
    }
};

bool sectionFinder(const string & section){
    for (int i = 0 ; i < sections.size(); i++) {
        if (sections[i] == section) {
            currentSection = i;
            return true;
        }
    }
    return false;
}

void addSection(notebook & ntb){
    string title,desc;
    cout << "Enter a title for the section: ";
    cin >> title;
    
    if (sectionFinder(title)) {
        cout << "Section \"" << title << "\" already exists." << endl;
        return;
    }

    
    sections.push_back(title);
    
    
    chronometer.startTimer();
    ntb.bstSections.insert(bstSection(title));
    chronometer.endTimer();
    cout << "[BST] Elapsed time: "<< chronometer.totalTime << " μs" << endl;
    
    chronometer.startTimer();
    ntb.avlSections.insert(avlSection(title));
    chronometer.endTimer();
    cout << "[AVL] Elapsed time: "<< chronometer.totalTime << " μs" << endl;
    
    
}

void displayInfo(bstSection* bstSection, avlSection* avlSection){
    string title;
    
    cout << "Enter the title of the item: ";
    cin >> title;
    
    item temp(title,"");
    
    chronometer.startTimer();
    item* searchResult = avlSection->items.find(temp);
    chronometer.endTimer();
    cout << "[AVL] Elapsed time: "<< chronometer.totalTime << " μs" << endl;
    
    chronometer.startTimer();
    item* searchResultBST = bstSection->items.searchItem(temp);
    chronometer.endTimer();
    cout << "[BST] Elapsed time: "<< chronometer.totalTime << " μs" << endl;
    
    
    if (searchResult != nullptr) {
        cout << searchResult->info << endl;
    }
    else{
        cout << "Invalid title!" << endl;
    }
    
}

void deleteItem(bstSection * bstSection,avlSection* avlSection){
    string itemTitle;
    
    cout << "Enter the title of the item: ";
    cin >> itemTitle;
    
    if (bstSection->items.search(item(itemTitle,""))) {
        //well done
        chronometer.startTimer();
        bstSection->items.remove(item(itemTitle,""));
        chronometer.endTimer();
        cout << "[BST] Elapsed time: "<< chronometer.totalTime << " μs" << endl;
        
        
        chronometer.startTimer();
        avlSection->items.remove( avlSection->items.root,item(itemTitle,""));
        chronometer.endTimer();
        cout << "[AVL] Elapsed time: "<< chronometer.totalTime << " μs" << endl;
        
        
    }
    else {
        cout << "Item \""<< itemTitle << "\" does not exists in the \""<< bstSection->title <<"\"." <<endl;
    }
}

void addItem(bstSection* & bstSection,avlSection* & avlSection){
    string itemName,itemDesc;
    
    cout << "Enter a title for the item: ";
    cin >> itemName;
    
    if (!bstSection->items.search(item(itemName,""))) {
        cout << "Enter a description for the item: ";
        cin >> itemDesc;
        
        const item temp(itemName,itemDesc);
        
        chronometer.startTimer();
        avlSection->items.insert(temp);
        chronometer.endTimer();
        cout << "[AVL] Elapsed time: "<< chronometer.totalTime << " μs" << endl;
        
        
        chronometer.startTimer();
        bstSection->items.insert(temp);
        chronometer.endTimer();
        cout << "[BST] Elapsed time: "<< chronometer.totalTime << " μs" << endl;
        
        cout << "The new item \""<< itemName << "\" has been inserted." << endl;
    }
    else{
        cout << "Item \""<< itemName << "\" already exists in the \""<< bstSection->title <<"\"." <<endl;
    }
}

void updateItem( bstSection* & bstSelected, avlSection* & avlSelected){
    string itemTitle,itemDesc;
    
    cout << "Enter the title of the item: ";
    cin >> itemTitle;
    
    chronometer.startTimer();
    item* searchItem = avlSelected->items.find(item(itemTitle,""));
    chronometer.endTimer();
    cout << "[AVL] Elapsed time: "<< chronometer.totalTime << " μs" << endl;
    
    chronometer.startTimer();
    item* searchItemBST = bstSelected->items.searchItem(item(itemTitle,""));
    chronometer.endTimer();
    cout << "[BST] Elapsed time: "<< chronometer.totalTime << " μs" << endl;
    
    if (searchItem != nullptr) {
        cout << "Enter the new information: ";
        cin >> itemDesc;
        
        searchItem->info = itemDesc;
        searchItemBST->info = itemDesc;
        cout << "The content "<< itemTitle << " has updated." << endl;
        //well done
    }
    else {
        cout << "Item \""<< itemTitle << "\" does not exists in the \""<< bstSelected->title <<"\"." <<endl;
    }
}

void sectionSelection(notebook & ntb){
    string sectionName;
    bstSection* bstSelected,temp;
    avlSection* avlSelected,tempAVL;
    int inp;
    cout << "Enter the title of the section: ";
    cin >> sectionName;
    
    if (sectionFinder(sectionName)) {
        temp.title = sectionName;
        tempAVL.title = sectionName;
        bstSelected = ntb.bstSections.searchItem(temp);
        avlSelected = ntb.avlSections.find(tempAVL);
        
        cout << endl <<"Selected section -> "<< sectionName;
        
        cout << endl
        <<"Please enter an input between [1 - 7]:" << endl
        << "1- Display the items [AVL]" << endl
        << "2- Display the items [BST]" << endl
        << "3- Display the information of a item" << endl
        << "4- Add new item" << endl
        << "5- Update the information of a item" << endl
        << "6- Delete an item" << endl
        << "7- Return to main menu";
        
        bool cont = true;
        while (cont) {
            
            cout << endl << "Input: ";
            
            cin >> inp;
            
            
            switch (inp) {
                case 1:
                    cout << endl << "*****" << endl;
                    avlSelected->items.printInOrderRecursive();
                    cout << "*****" << endl;
                    break;
                    break;
                case 2:
                    cout << endl << "*****" << endl;
                    bstSelected->items.printInOrderRecursive();
                    cout << "*****" << endl;
                    break;
                case 3:
                    displayInfo(bstSelected,avlSelected);
                    break;
                case 4:
                    addItem(bstSelected,avlSelected);
                    break;
                case 5:
                    updateItem(bstSelected,avlSelected);
                    break;
                case 6:
                    deleteItem(bstSelected,avlSelected);
                    break;
                case 7:
                    cout << endl;
                    printMenu();
                    cont = false;
                    break;
                default:
                    continue;
            }
        }
    }
    
    else {
        cout << "Invalid title!" << endl;
    }
    
    
}

void deleteSection(notebook & ntb){
    string itemName;
    
    
    cout << "Enter the title of the item: ";
    cin >> itemName;
    
    if (sectionFinder(itemName)) {
        ntb.bstSections.remove(bstSection(itemName, ""));
        ntb.avlSections.remove(ntb.avlSections.root, avlSection(itemName,""));
        //avlSection->items.remove( avlSection->items.root,item(itemTitle,""));
        cout << "The section has been deleted." << endl;
        
        sections.erase(sections.begin() + currentSection);

    }
    else{
        cout << "Section \"" << itemName << "\" does not exist." << endl;
    }
}

void printMenu(){
    cout <<"MENU" << endl
    << "Please enter an input between [1 - 6]: "<< endl
    << "1- Display the sections [AVL]" << endl
    << "2- Display the sections [BST]" << endl
    << "3- Select a section" << endl
    << "4- Add new section" << endl
    << "5- Delete a section" << endl
    << "6- Exit";
    
}

bool menu(notebook & ntb){
    int inp;
    
    cout << endl <<"Input: ";
    cin >> inp;
    
    
    switch (inp) {
            
        case 1:
            
            cout << endl << "*****" << endl;
            ntb.avlSections.printInOrderRecursive();
            cout << "*****" << endl;
            break;
        case 2:
            cout << endl << "*****" << endl;
            ntb.bstSections.printInOrderRecursive();
            cout << "*****" << endl;
            break;
        case 3:
            sectionSelection(ntb);
            break;
        case 4:
            addSection(ntb);
            break;
        case 5:
            deleteSection(ntb);
            break;
        case 6:
            cout << endl << "Terminating..." << endl;
            return false;
            
        default:
            cout << "Invalid Option for Main Menu" << endl;
            break;
    }
    //cout << "*****" << endl << endl;
    return true;
}

void processInput(notebook & ntb){
    vector<long long> bstTimes,avlTimes;
    
    const string fName = "data.txt";
    string line,token,title,info;
    istringstream iss;
    
    
    fstream fileStream;
    fileStream.open(fName);
    
    chronometer.startTimer();
    avlSection* newSection = nullptr;
    
    while (getline(fileStream,line)) {
        if (line.at(0) != '-') {
            
            chronometer.startTimer();
            
            if (newSection != nullptr) {
                const avlSection sectionToAddAVL = *newSection;
                ntb.avlSections.insert(sectionToAddAVL);
                chronometer.endTimer();
                
                avlTimes.push_back(chronometer.totalTime);
                
            }
            
            
            // This is a new section.
            newSection = new avlSection;
            
            newSection->title = line;
            sections.push_back(newSection->title);
            
        }
        
        else {
            // this is an information line
            istringstream iss(line);
            
            getline(iss, token, '-');
            getline(iss, token, '-');
            title = token;
            getline(iss, token, '-');
            info = token;
            
            newSection->items.insert(item(title,info));
        }
    }
    const avlSection sectionToAddAVL = *newSection;
    ntb.avlSections.insert(sectionToAddAVL);
    
    chronometer.endTimer();
    avlTimes.push_back(chronometer.totalTime);
    
    
    fileStream.ignore();
    fileStream.clear();
    
    fileStream.seekg(0);
    
    bstSection* newSectionBst = nullptr;
    while (getline(fileStream,line)) {
        chronometer.startTimer();
        if (line.at(0) != '-') {
            
            if (newSectionBst != nullptr) {
                const bstSection sectionToAddBST = *newSectionBst;
                ntb.bstSections.insert(sectionToAddBST);
                
                chronometer.endTimer();
                
                bstTimes.push_back(chronometer.totalTime);
            }
            // This is a new section.
            newSectionBst = new bstSection;
            
            newSectionBst->title = line;
            
        }
        
        else {
            // this is an information line
            istringstream iss(line);
            
            getline(iss, token, '-');
            getline(iss, token, '-');
            title = token;
            getline(iss, token, '-');
            info = token;
            
            newSectionBst->items.insert(item(title,info));
        }
    }
    const bstSection sectionToAddBST = *newSectionBst;
    ntb.bstSections.insert(sectionToAddBST);
    
    chronometer.endTimer();
    bstTimes.push_back(chronometer.totalTime);
    

    
    for (int i = 0; i < sections.size(); i++) {
        cout << "Section \"" << sections[i] << "\" has been inserted into the AVL notebook." << endl;
        cout << "[AVL] Elapsed time: " << avlTimes[i] << " microseconds" << endl;
        
        cout << "Section \"" << sections[i] << "\" has been inserted into the BST notebook." << endl;
        cout << "[BST] Elapsed time: " << bstTimes[i] << " microseconds" << endl << endl;
        
    }
}

int main(){
    cout <<  "Welcome to the Notes" << endl << endl;
    notebook ntb;
    processInput(ntb);
    
    printMenu();
    while (menu(ntb)) {
        continue;
    }

    return 0;
    
    
}
