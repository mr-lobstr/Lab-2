#include <iostream>
#include <string>
#include "data_struct/hash_table.h"
using namespace std;
using namespace data_struct;

namespace data_struct
{
    template <>
    struct Hasher<char> {
        size_t operator() (char c) const {
            return c;
        }
    };
}


string max_sub_string (string const& str)  {
    HashTable<char, int> table;
    string maxSub = "";
    size_t begInd = 0, len = 0;
    size_t maxLen = 0;

    for (size_t i = 0; i < str.size(); ++i) {
        if (table.find(str[i]) == table.end()) {
            table.add (str[i], i);
            ++len;
            continue;
        }

        if (len > maxLen) {
            maxSub = str.substr (begInd, len);
            maxLen = len;
        }

        auto prevInd = table[str[i]];

        if (prevInd >= begInd) {
            begInd = prevInd + 1;
            table[str[i]] = i;
            len = i - begInd + 1;
        }
    }

    if (len > maxLen) {
        maxSub = str.substr (begInd, len);
    }

    return maxSub;
}

int main()
{
    string s;
    cin >> s;
    cout << max_sub_string (s);
}