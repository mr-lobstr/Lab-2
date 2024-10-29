#include <iostream>
#include <string>
#include "data_struct/hash_set.h"
using namespace std;
using namespace data_struct;

namespace data_struct
{
    template <>
    struct Hasher<int> {
        size_t operator() (int i) const {
            return i;
        }
    };
}

int main()
{
    int turtlesCnt;
    cin >> turtlesCnt;

    HashSet<int> turtles;

    for (int i = 0; i < turtlesCnt; ++i) {
        int before, after;
        cin >> before >> after;

        if (before + after + 1 == turtlesCnt) {
            turtles.add (after + 1);
        }
    }

    cout << turtles.size() << endl;
}