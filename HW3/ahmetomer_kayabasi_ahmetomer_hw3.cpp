//
//  main.cpp
//  cs300_hw3
//
//  Created by Ahmet Ömer Kayabaşı on 26.04.2021.
//

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include "hash.h"

using namespace std;

double supportThreshhold = 0.25;
double confidenceThreshhold = 0.7;

vector<string> readFile(const string & fileName) {
    string line;
    fstream fStream;
    
    vector<string> lines;
    
    fStream.open(fileName.c_str());
    
    if (fStream.fail()) {
        cout << "File opening error!" << endl;
    }
    else{
        while (getline(fStream,line)) {
            lines.push_back(line);
        }
    }
    
    return lines;
}

bool alreadyCalculated(const vector<pair<vector<string>,double> > & results, const vector<string> showName){
    for (int i = 0; i < results.size(); i++) {
        if (showName.size() == 1) {
            if (results[i].first[0] == showName[0]) {
                return true;
            }
        }
        if (showName.size() == 2) {
            if (results[i].first[0] == showName[0] && results[i].first[1] == showName[1]) {
                return true;
            }
            if (results[i].first[0] == showName[1] && results[i].first[1] == showName[0]) {
                return true;
            }
        }
    }
    return false;
}


double calculateSupport(const vector<string> & lines, const vector<string> & shows){
    double matchCount = 0;
    bool exist = true;
    
    for (int i = 0 ; i < lines.size(); i++) {
        exist = true;
        
        for (int j = 0; j < shows.size(); j++) {
            if (lines[i].find(shows[j]) == string::npos) {
                exist = false;
                break;
            }
        }
        
        if (exist) {
            matchCount++;
        }
    }
    
    return matchCount / lines.size();
}
bool validPermutation(const pair<vector<string>,double > & lhs, const pair<vector<string>,double > & rhs){
    for (int i = 0; i < lhs.first.size(); i++) {
        for (int j = 0; j < rhs.first.size(); j++) {
            if (lhs.first[i] == rhs.first[j]) {
                return false;
            }
        }
    }
    return true;
}

vector<pair<vector<string>,double> >  supportCalculatorMain(const vector<string> & lines){
    
    vector<pair<vector<string>,double> > oneShowResults;
    auto lineCount = lines.size();
    double support;
    
    string show;
    
    for (int i = 0; i < lineCount; i++) {
        istringstream iss(lines[i]);
        
        while (iss >> show) {
            vector<string> showName;
            showName.push_back(show);
            
            if (!alreadyCalculated(oneShowResults, showName)) {
                
                support = calculateSupport(lines, showName);
                
                if (support >= supportThreshhold) {
                    oneShowResults.push_back(pair<vector<string>,double>(showName,support));
                }
                
            }
        }
    }
    auto oneShowResultSize = oneShowResults.size();
    
    for (int i = 0 ; i < oneShowResultSize; i++) {
        for (int j = i + 1 ; j < oneShowResultSize; j++) {
            vector<string> showName;
            
            showName.push_back(oneShowResults[i].first[0]);
            showName.push_back(oneShowResults[j].first[0]);
            
            if (!alreadyCalculated(oneShowResults, showName)) {
                
                
                support = calculateSupport(lines, showName);
                
                if (support >= supportThreshhold) {
                    
                    oneShowResults.push_back(pair<vector<string>,double>(showName,support));
                }
            }
        }
    }
    
    return oneShowResults;
}

int main() {
    string inpFileName;
    
    cout << "Please enter the transaction file name: ";
    cin >> inpFileName;
    
    cout << "Please enter support and confidence values between 0 and 1: ";
    cin >> supportThreshhold >> confidenceThreshhold;
    
    auto lineVector = readFile(inpFileName);
    auto showSupports = supportCalculatorMain(lineVector); 
    
    Hash lookupTable;
    
    for (int i = 0; i < showSupports.size(); i++) {
        lookupTable.insert(showSupports[i]);
    }
    
    vector<pair<vector<string>, double> > items;
    
    for (int i = 0; i < 13; i++) {
        auto temp = lookupTable.indexItems(i);
        for (int j = 0; j < temp.size(); j++) {
            items.push_back(temp[j]);
        }
    }
    int outputCount = 0;
    ofstream of;
    of.open("result.txt");
    
    for (int i = 0; i < items.size(); i++) {
        for (int j = 0 ; j < items.size(); j++) {
            
            if (validPermutation(items[i], items[j])) {
                
                auto srsVector = items[i].first;
                
                for (int k = 0; k < items[j].first.size(); k++) {
                    srsVector.push_back(items[j].first[k]);
                }
                
                auto allSupport = calculateSupport(lineVector, srsVector);
                auto lhsSupport = items[i].second;
                
                double confidence = allSupport / lhsSupport;
                
                if (confidence >= confidenceThreshhold) {
                    outputCount++;
                    for (int k = 0; k < items[i].first.size(); k++) {
                        if (k == items[i].first.size() - 1) {
                            of << items[i].first[k];
                        }
                        else{
                            of << items[i].first[k] << ",";
                        }
                    }
                    of << ";";
                    
                    for (int k = 0; k < items[j].first.size(); k++) {
                        if (k == items[j].first.size() - 1) {
                            of << items[j].first[k];
                        }
                        else{
                            of << items[j].first[k] << ",";
                        }
                    }
                    of << ";" <<  confidence << endl;
                }
            }
        }
    }
    cout << outputCount << " rules are written to results.txt" << endl;
    return 0;
}
