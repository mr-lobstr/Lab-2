#include <iostream>
#include "data_struct/hash_set.h"
using namespace std;
using namespace data_struct;

namespace data_struct
{
    template <>
    struct Hasher<string> {
        size_t operator() (string const& str) {
            size_t res = 597065720022;

            for (char c : str) {
                res += c;
            }

            return res;
        }
    };
}

int main()
{
    HashSet<string> set;

    while (true) {
        string command;
        cin >> command;

        if (command == "exit")
            break;
        
        if (command == "add") {
            string value;  
            cin >> value;         
            set.add (value);
            continue;
        }

        if (command == "del") {
            string value;  
            cin >> value;

            try {
                set.erase (value);
            } catch (runtime_error& e) {
                cout << e.what();
            }
            continue;
        }

        if (command == "print") {
            for (auto& el : set) {
                cout << el << " ";
            }
            cout << endl;
        }

        if (command == "at") {
            string value;  
            cin >> value;

            auto it = set.find(value);

            if (it == set.end()) {
                cout << value << " отсутствует" << endl;
            } else {
                cout << value << " есть" << endl;
            }

            continue;
        }
    }
}
