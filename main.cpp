#include <iostream>
#include <vector>
#include <set>
#include <bitset>

using namespace std;

const int SIZE = 8;

int Count(int num){
    return bitset<SIZE>(num).count();
}

bool canCombine(int num1, int num2){
    int diff = num1 ^ num2;
    return Count(diff) == 1;
}

int combine(int num1, int num2){
    int diff = num1 ^ num2;
    int mask = diff & ~(diff - 1);
    return num1 & ~mask;
}

vector<string>getDNF(set<int>&mint){
    vector<string>result;
    for(int m : mint){
        string term;
        bitset<SIZE>bits(m);
        for(int i = 0;i < SIZE;i++){
            if(bits[i] == 1){
                term += char('a' + i);
            }
            else{
                term += '-' + char('a' + i);
            }
        }
        result.push_back(term);
    }
    return result;
}

vector<string>mccluskey(set<int>&minterms){
    set<int>simple_terms;
    vector<set<int>>groups(SIZE + 1);
    for(int m : minterms){
        groups[Count(m)].insert(m);
    }
    for(int i = 0;i < groups.size() - 1;i++){
        for(int m1 : groups[i]){
            for(int m2 : groups[i + 1]){
                if(canCombine(m1, m2)){
                    int combined = combine(m1, m2);
                    simple_terms.insert(combined);
                }
            }
        }
    }
    for(const auto& a : groups){
        for(const auto& b : a){
            if(simple_terms.find(b) == simple_terms.end()){
                simple_terms.insert(b);
            }
        }
    }
    return getDNF(simple_terms);
}

int main(){
    set<int>numbers = {3, 7, 4, 10, 12, 2, 20, 17};
    vector<string>simple_terms = mccluskey(numbers);
    for(int i = 0;i < simple_terms.size();i++){
        cout << simple_terms[i];
        if(i + 1 != simple_terms.size()){
            cout << " | ";
        }
    }
    return 0;
}

