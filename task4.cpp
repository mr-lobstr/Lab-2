#include <iostream>
#include <string>
#include "data_struct/dynamic_array.h"
using namespace std;
using namespace data_struct;

size_t bin_search (DynamicArray<char> const& arr, char letter) {
    size_t left = 0;
    size_t right = arr.size();

    while (left < right) {
        auto middle = (right + left) / 2;

        if (letter > arr[middle]) {
            left = middle + 1;
        } else {
            right = middle;
        }
    }

    return left;
}

void print_histogram (DynamicArray<char> const& letters, DynamicArray<int> const& counts) {
    int maxHeight = 0;
    for (int i : counts) {
        maxHeight = max (i, maxHeight);
    }

    for (size_t i = maxHeight; i > 0; --i) {
        for (int count : counts) {
            cout << (i <= count ? "#" : " ");
        }
        cout << endl;
    }

    for (char l : letters) {
        cout << l;
    }
    cout << endl;
}

int main()
{
    string s;
    getline (cin, s);

    DynamicArray<char> letters;
    DynamicArray<int> counts;

    for (char letter : s) {
        if (isspace (letter))
            continue;

        if (letters.empty()) {
            letters.push_back (letter);
            counts.push_back (1);
            continue;
        }

        auto ind = bin_search (letters, letter);

        if (letters[ind] == letter) {
            ++counts[ind];
        } else {
            letters.insert (letters.begin() + ind, letter);
            counts.insert (counts.begin() + ind, 1);
        }
    }

    print_histogram (letters, counts);
}