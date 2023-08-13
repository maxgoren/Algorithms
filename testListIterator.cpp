#include <iostream>
#include "List.hpp"
using std::cout;
using std::endl;
using std::string;

int main() {
    string sed = "aiteratorexample";
    List<char> list;
    for (char c : sed) {
        list.pushBack(c);
    }
    auto it = list.getIterator();
    for (it->first(); it->done() == false; it->next()) {
        cout<<it->value()<<" ";
    }
    cout<<endl;
}