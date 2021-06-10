//
//  main.cpp
//  cs300hw4
//
//  Created by Ahmet Ömer Kayabaşı on 11.05.2021.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <iomanip>

#define endl "\n"
using namespace std;


bool fullSearchQuery;

class timer {
private:
    std::__1::chrono::steady_clock::time_point start_time;
    
    
public:
    void startTimer(){
        start_time = chrono::high_resolution_clock::now();
    }
    void endTimer(){
        totalTime = std::chrono::duration_cast<std::chrono::nanoseconds>(chrono::high_resolution_clock::now()-start_time).count();
    }
    long long totalTime;
    //std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start).count()
};

timer chronometer;
bool sMatch = false;
bool bMatch = false;


struct Person {
    string name,city,number;
    
    Person(){
        name = city = number = "";
    };
    
    void personInfo() const {
        cout << name << " " << number << " " << city << endl;
    }
    
    Person(string n, string c, string num):name(n),city(c),number(num){};
};

vector<Person> results;
void swap_heap(vector<Person> &list, unsigned int i, unsigned int j);
void downHeap(vector<Person> &list, int i, int size);
void heapify(vector<Person> &list);


void ToUpper(string & s)
// postcondition: s all lower case
{
    int len = s.length();
    for(int k=0; k < len; k++)
    {
        s[k] = toupper(s[k]);
    }
}

vector<Person> readFile(ifstream & fileStream){
    
    vector<Person> db;
    string line,name,surname,number,city;
    
    while (getline(fileStream,line)) {
        istringstream iss(line);
        
        
        iss >> name >> surname >> number >> city;
        
        ToUpper(name);
        ToUpper(surname);
        
        db.push_back(Person(name + " " + surname, number,city));
    }
    
    return db;
}

void printVector(const vector<Person> & db){
    cout << "VECTOR INFO" << endl << "------------------------------------------------------" << endl;
    for (int i = 0; i < db.size(); i++) {
        cout << left <<setw(20) << db[i].name << left << setw(12) << db[i].number << left <<setw(15) << db[i].city << endl;
    }
    cout << endl;
}


//INSERTION SORT
void insertionSort( vector<Person> & list) {
    int i, j;
    Person temp("","","");
    
    for (i = 1; i < list.size(); i++) {
        j = i;
        while (j > 0 && list[j - 1].name > list[j].name) {
            temp = list[j];
            list[j] = list[j - 1];
            list[j - 1] = temp;
            j--;
        }
    }
    
}

// HEAP SORT
void heapSort( vector<Person> & list)
{
    // Build a max heap
    heapify(list);

    for (int i = (int) list.size() - 1; i >= 0; i--) {
        swap_heap(list, 0, i);
        downHeap(list, 0, i);
    }
    
    
}


void heapify(vector<Person> &list)
{
    int size = list.size();
    for (int i = size / 2; i >= 0 ; i--) {
        downHeap(list, i, size);
    }
}

void downHeap(vector<Person> &list, int i, int size)
{
    int left    = 2 * i + 1; // Index of left child
    int right   = 2 * i + 2; // Index of right child
    int largest = i;


    if (left < size and list[left].name > list[largest].name) {
        largest = left;
    }
    if (right < size and list[right].name > list[largest].name) {
        largest = right;
    }
    // Swap parent with the larger of its children if necessary
    if (largest != i) {
        swap_heap(list, i, largest);
        // Down heap from its larger children
        downHeap(list, largest, size);
    }
}

void swap_heap(vector<Person> &list, unsigned int i, unsigned int j)
{
    auto temp = list[i];
    list[i]  = list[j];
    list[j]  = temp;
}


//QUICK SORT
void quickSort(vector<Person> & arr, int left, int right) {
    int i = left, j = right;
    Person tmp("","","");
    string pivot = arr[(left + right) / 2].name;

    
    while (i <= j) {
        while (arr[i].name < pivot)
            i++;
        while (arr[j].name > pivot)
            j--;
        if (i <= j) {
            tmp = arr[i];
            arr[i] = arr[j];
            arr[j] = tmp;
            i++;
            j--;
        }
    };

    if (left < j)
        quickSort(arr, left, j);
    if (i < right)
        quickSort(arr, i, right);
}

// MERGE SORT
void merge(vector <Person> &v, int start, int mid, int end)
{
    vector <Person> aux(v.size());
    int i = start;    // begin of the first part
    int j = mid + 1; // begin of the second part
    int k = start;  // start of the aux vector


    // Elements in both parts
    while (i <= mid && j <= end) {
        if (v[i].name < v[j].name)
            aux[k] = v[i++];
        else
            aux[k] = v[j++];

        k++;
    }

    // Left part has elements
    while (i <= mid) {
        aux[k] = v[i++];
        k++;
    }

    // Right part has elements
    while (j <= end) {
        aux[k] = v[j++];
        k++;
    }

    // Copy the vector
    for (int i = start; i <= end; i++) {
        v[i] = aux[i];
    }

}

// Merge sort
void mergeSort(vector <Person> &v, int start, int end) {

    if (start < end) {
        int m = (start + end) / 2;
        mergeSort(v, start, m);
        mergeSort(v, m + 1, end);
        merge(v, start, m, end);
    }
}

void binary_search(const vector<Person> & a, string key,const bool & print) {
    int l = 0;
    int r = a.size();

    if (fullSearchQuery) {
        while (l <= r) {
            int m = l + (r - l) / 2;
            if (key == a[m].name){
                if (!bMatch) {
                    a[m].personInfo();
                    bMatch = true;
                }
                break;
            }
            else if (key < a[m].name)
                r = m - 1;
            else
                l = m + 1;
        }
    }
    else{
        while (l <= r) {
            int m = l + (r - l) / 2;
            if (string::npos != a[m].name.find(key)){
                bMatch = true;
                if (print) {
                    a[m].personInfo();
                    
                    int lowerbound = m - 1;
                    while (lowerbound >= 0 && string::npos != a[lowerbound].name.find(key)) {
                        lowerbound--;
                    }
                    
                    int upperbound = m + 1;
                    while (upperbound < a.size() && string::npos != a[upperbound].name.find(key)) {
                        upperbound++;
                    }
                    
                    for (int i = lowerbound + 1; i < upperbound; i++) {
                        a[i].personInfo();
                    }
                    break;
                }
                
                
            }
            if (key < a[m].name)
                r = m - 1;
            else
                l = m + 1;
        }
    }

}

void sequentialSearch(const vector<Person> & db, string key, const bool & print){
    if (fullSearchQuery) {
        for (int i = 0;  i < db.size(); i++) {
            if (db[i].name == key) {
                if (!sMatch) {
                    db[i].personInfo();
                    sMatch = true;
                }
            }
        }
    }
    else{
        for (int i = 0;  i < db.size(); i++) {
            if (db[i].name.find(key) != string::npos) {
                sMatch = true;
                if (print) {
                    db[i].personInfo();
                }
            }
        }
    }

}


void speedUps(const long long & insertion, const long long & merge, const long long & quick, const long long & heap){
    double iFinal,mFinal,hFinal;
    
    if (insertion > quick) {
        iFinal = insertion / (quick * 1.0);
    }
    else{
        iFinal =  quick / (insertion * 1.0);
    }
    
    if (merge > quick) {
        mFinal = merge / (quick * 1.0);
    }
    else{
         mFinal =  quick / (merge * 1.0);
    }
    
    if (heap > quick) {
        hFinal = heap / (quick * 1.0);
    }
    else{
        hFinal =  quick / (heap * 1.0);
    }
    
    cout <<  endl <<"SpeedUps between Sorting Algorithms" << endl <<"======================================" << endl;
    cout << "(Insertion Sort/ Quick Sort) SpeedUp = " << iFinal << endl;
    cout << "(Merge Sort / Quick Sort) SpeedUp = " << mFinal << endl;
    cout << "(Heap Sort / Quick Sort) SpeedUp = " << hFinal << endl;
}


int main(int argc, const char * argv[]) {
    string fileName,searchQuery;
    cout << "Please enter the contact file name:" << endl;
    cin >> fileName;
    cout << "Please enter the word to be queried :" << endl;
    cin.ignore();
    getline(cin,searchQuery);
    
    fullSearchQuery = searchQuery.find(' ') != string::npos ? true : false;
    
    ToUpper(searchQuery);
    
    ifstream fileStream;
    fileStream.open(fileName.c_str());
    
    if (fileStream.fail()) {
        cout << "File could not be opened properly!" << endl;
    }
    else{
        
        auto db = readFile(fileStream);
        
        vector<Person> insertion = db ,heap = db ,quick = db ,merge = db;
        
        cout << endl << "Sorting the vector copies" << endl << "======================================" << endl;
        
        chronometer.startTimer();
        quickSort(quick, 0, quick.size() -1 );
        chronometer.endTimer();
        auto quickTime = chronometer.totalTime;
        
        cout << "Quick Sort Time: " << quickTime << " Nanoseconds" << endl;
        
        chronometer.startTimer();
        insertionSort(insertion);
        chronometer.endTimer();
        auto insertionTime = chronometer.totalTime;
        
        cout << "Insertion Sort Time: " << insertionTime << " Nanoseconds" << endl;
        
        chronometer.startTimer();
        mergeSort(merge, 0, merge.size()-1);
        chronometer.endTimer();
        auto mergeTime = chronometer.totalTime;
        
        cout << "Merge Sort Time: " << mergeTime << " Nanoseconds" << endl;
        
        chronometer.startTimer();
        heapSort(heap);
        chronometer.endTimer();
        auto heapTime = chronometer.totalTime;
        
        cout << "Heap Sort Time: " << heapTime << " Nanoseconds" << endl;

        
        
        cout << endl <<"Searching for "<< searchQuery << endl << "======================================" << endl << "Search results for Binary Search:" << endl;
        
        
        const int N = 1000;
        chronometer.startTimer();
        for (int i = 0 ; i < N; i++) {
            binary_search(quick,searchQuery,false);
        }
        binary_search(quick,searchQuery,true);
        chronometer.endTimer();
        
        if (!bMatch) {
            cout << searchQuery << " does NOT exist in the dataset"<< endl ;
        }
        
        auto binarySearchTime = chronometer.totalTime / (N * 1.0);
        cout << "Binary Search Time: " << binarySearchTime << " Nanoseconds" << endl << endl;
        
        
        cout << "Search results for Sequential Search:" << endl;
        chronometer.startTimer();
        for (int i = 0 ; i < N - 1; i++) {
            sequentialSearch(quick, searchQuery,false);
        }
        sequentialSearch(quick, searchQuery,true);
        chronometer.endTimer();
        
        
        
        if (!sMatch) {
            cout << searchQuery << " does NOT exist in the dataset"<< endl;
        }
        
        auto sequentialSearchTime = chronometer.totalTime / (N * 1.0);
        cout << "Sequential Search Time: " << sequentialSearchTime << " Nanoseconds" << endl;
        
        cout << endl <<"SpeedUp between Search Algorithms" << endl "======================================" << endl << "(Sequential Search/ Binary Search) SpeedUp = " << sequentialSearchTime / (binarySearchTime * 1.0) << endl;
        
        
        
        speedUps(insertionTime, mergeTime, quickTime, heapTime);
        
        //printVector(db);
    }
    
    
    return 0;
}

