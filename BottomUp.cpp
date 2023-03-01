#include <iostream>
#include <vector>
#include <string>
#include <limits.h>
//#include "p2.cpp"

using namespace std;

class BottomUp {
    private:
        vector<int> bases;
        vector<vector<int>> solutionVector;
        int totalCoins(vector<int> coinVectors) {
            int returnCoins = 0;
            if (coinVectors.at(0) != INT_MAX) {
                for (int i = 0; i < coinVectors.size(); i++) {
                    returnCoins = returnCoins + coinVectors.at(i);
                }
                return returnCoins;
            }
            return INT_MAX;
        }
    
    public:
        BottomUp(vector<int> bases) {
            this->bases = bases;
            solutionVector.push_back(vector<int>(bases.size(), 0));
        }
        // Returns the minimum amount of coins while also modifying an existing 
        //  vector that is solved bottom-up to cache results
        vector<int> minCoins(int problem) {
            vector<int> result;
            if (problem + 1 > solutionVector.size()) {
                solutionVector.resize(problem + 1, vector<int>(bases.size(), INT_MAX));
                int currentCoinCount;
                for (int i = 1; i < solutionVector.size(); i++) {
                    if (solutionVector.at(i).at(0) == INT_MAX) {
                        for (int j = 0; j < bases.size(); j++) {
                            if (bases.at(j) <= i) {
                                currentCoinCount = totalCoins(solutionVector.at(i - bases.at(j)));
                                //cout << currentCoinCount << " ";
                                if (currentCoinCount + 1 < totalCoins(solutionVector.at(i)) && currentCoinCount != INT_MAX) {
                                    solutionVector.at(i) = solutionVector.at(i - bases.at(j));
                                    solutionVector.at(i).at(j)++;
                                }
                            }
                        }
                    }
                }
            }
            result = solutionVector.at(problem);
            return result;
        }
        vector<vector<int>> getSolutionVector() {
            return solutionVector;
        }
};

int main(int argc, char** argv) {
    // Number of bases
    int numBases;
    cin >> numBases;
    
    // Bases vector
    vector<int> bases;
    bases.resize(numBases);
    for (int i = 0; i < numBases; i++) {
        cin >> bases.at(i);
    }

    BottomUp bottomUpSolver(bases);

    // Set problems to loop through
    int numProblems;
    cin >> numProblems;

    int problems[numProblems];
    for (int i = 0; i < numProblems; i++) {
        cin >> problems[i];
        bottomUpSolver.minCoins(problems[i]);
    }
    vector<vector<int>> results = bottomUpSolver.getSolutionVector();
    for (int i = 0; i < numProblems; i++) {
        cout << problems[i] << " cents ="; 
        for (int j = numBases - 1; j >= 0; j--) {
            if (results.at(problems[i]).at(j) != 0) {

                cout << " " << bases.at(j) << ":" << results.at(problems[i]).at(j);
            }
        }
        cout << endl;
    }
}