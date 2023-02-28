#include <iostream>
#include <vector>

using namespace std;

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

    for(int i = 0; i < num_problems; i++) {
        cin >> problem;

        // DO MAGIC!

    }

    return 0;

}
