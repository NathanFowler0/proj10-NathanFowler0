
#include "BST.h"
#include <string>
#include <fstream>
#include <iostream>
int main() {
    for (int i = 1; i <= 10; i++) {
        //I iterate over each file. the following 2 lines get the file name
        string number = ((i == 10) ? "" : "0") + to_string(i);
        string fileName = "/Users/nathanfowler/Desktop/computer_science/learning/learning_c++/projects/proj10-NathanFowler0/proj09randomints/randomInts" + (number)+".txt";

        ifstream fin(fileName);
        BST<long> bTree;

        istream_iterator<long> iter(fin);   //iterator to the first long value in the file stream
        istream_iterator<long> end;         //iterator to the end of the file stream

        unsigned duplicates = 0;

        while (iter != end) {   //loop to get the value and increment the iterator
            long val = *iter;
            iter++;

            //This try block is used to check for duplicate values in the ints file.
            //As the files contain completely random long values,
            //it is extremely unlikely that there will be any 2 collisions since
            //there are up to 2^64 different long values each with equal weight
            //I am still told to check for duplicates though, so I do.
            try {
                bTree.insert(val);
            }
            catch (Exception e) {
                duplicates++;
            }
        }
        cout << "file " << i << ":\n";
        cout << "height: " << bTree.getHeight() << endl;
        cout << "duplicates: " << duplicates << endl << endl;
    }
}