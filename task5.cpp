#include <iostream>
#include <string>
#include "data_struct/binary_tree.h"
using namespace std;
using namespace data_struct;

void add_and_print_depth (BinTree<int>& tree, int value) {
auto it = tree.root();
    int depth = 1;

    while (not it.is_end()) {
        if (value >= *it) {
            it.to_right();
        } else {
            it.to_left();
        }
        ++depth;
    }

    tree.insert (Tilt::to_left, it, value);
    cout << depth << " ";
}

int main()
{
    BinTree<int> tree;
    int n;
    cin >> n;

    while (n != 0) {
        add_and_print_depth (tree, n);
        cin >> n;
    }
}

    // if (tree.empty()) {
    //     tree.push_root (Tilt::to_left, value);
    //     cout << 1 << " ";
    //     return;
    // }

    