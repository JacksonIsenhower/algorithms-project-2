#include <iostream>
#include <vector>
#include <string>

using namespace std;

// CoinPurse class
class coinPurse {
    public:
        vector<int> based;
        vector<int> coins_bases;
        int total_coins = 0;

        void fillPurse(vector<int> bases, vector<int> coins, int total = 0) {
            this->based = bases;
            this->coins_bases = coins;
            this->total_coins = total;
        }
};

// Set new purse
coinPurse newPurse(vector<int> bases) {
    coinPurse purse;
    purse.based.resize(bases.size());
    for (int i = 0; i < purse.based.size(); i++) {
        purse.based.at(i) = bases.at(i);
        purse.coins_bases.push_back(0);
    }

    return purse;
}


// The actual recursion magic is here
coinPurse solveProblem(int problem, coinPurse &bestPurse, coinPurse currPurse) {
    // create murse with currPurse's values (want values, not pointer) -- gotta represent men's fashion too :)
    coinPurse murse;
    murse.fillPurse(currPurse.based, currPurse.coins_bases, currPurse.total_coins);

    // Base case
    if (problem == 0) {
        return murse;
    }
    // Recursive case
    else {
        coinPurse res;
        for (int i = 0; i < murse.based.size(); i++) {
            if ((problem - murse.based.at(i)) >= 0) {
                // temp for passing in to recursion without ruining murse for the loop.
                coinPurse wallet;
                wallet.fillPurse(murse.based, murse.coins_bases, murse.total_coins);
                wallet.coins_bases.at(i)++;
                wallet.total_coins++;

                // Set sub-problem and recurse into it
                int sub_problem = problem - wallet.based.at(i);
                res = solveProblem(sub_problem, bestPurse, wallet);

                // Set best purse as we go along (not necessarily the prettiest purse though...)
                if (res.total_coins < bestPurse.total_coins) {
                    bestPurse.coins_bases = res.coins_bases;
                    bestPurse.total_coins = res.total_coins;
                }
            }
        }
        return res;
    }
}

int main(int argc, char** argv) {

    // Number of bases
    int num_bases;
    cin >> num_bases;

    // Set bases array
    vector<int> bases;
    bases.resize(num_bases);
    for (int i = 0; i < num_bases; i++) {
        cin >> bases.at(i);
    }

    // Set 2d table for storage
    vector<vector<int>> dynamic_storage(1, vector<int>(num_bases));

    // Set problems to loop through
    int num_problems;
    cin >> num_problems;
    int problem;

    // Store results
    vector<string> results(num_problems);

    for(int i = 0; i < num_problems; i++) {
        cin >> problem;

        // Prep work
        coinPurse currPurse = newPurse(bases);
        coinPurse bestPurse = currPurse;
        bestPurse.total_coins = 1000000000; // set to rediculously large value
        results[i] = to_string(problem) + " cents = ";  // prep output
        
        // DO MAGIC!
        solveProblem(problem, bestPurse, currPurse);

        // add to output based on results
        for (int j = bestPurse.based.size() - 1; j > -1; j--) {
            if (bestPurse.coins_bases.at(j) != 0) {
                results[i] += to_string(bestPurse.based.at(j)) + ":" + to_string(bestPurse.coins_bases.at(j));
                if (j != 0) results[i] += " ";
            }
        }
    }

    // Print results
    for (int i = 0; i < num_problems; i++) {
        cout << results[i] << endl;
    }

    return 0;

    // 1) Recursion (Jacob) and Bottom-Up (Jackson)
    // 2) Memoization and Timing
    // 3) Report
}
