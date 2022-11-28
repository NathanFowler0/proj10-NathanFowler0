#define CATCH_CONFIG_MAIN
#include "BST.h"
#include "catch.hpp"


//these are my tests for project 10

TEST_CASE("getHeight") {
    SECTION("empty") {
        BST<unsigned> bst;
        REQUIRE(bst.getHeight() == 0);
    }

    SECTION("balanced") {
        BST<unsigned> bst;
        bst.insert(5);      //      5
        REQUIRE(bst.getHeight() == 1);
        bst.insert(3);      //      5
        bst.insert(7);      //  3       7
        REQUIRE(bst.getHeight() == 2);
        bst.insert(2);  //        5
        bst.insert(4);  //    3       7
        bst.insert(6);  //  2   4   6   8
        bst.insert(8);
        REQUIRE(bst.getHeight() == 3);
    }

    SECTION("unbalanced") {
        BST<unsigned> unbalancedRight;
        for (int i = 1; i <= 10; i++) {
            unbalancedRight.insert(i);
            REQUIRE(unbalancedRight.getHeight() == i);
        }

        BST<unsigned> unbalancedLeft;
        for (int i = 10; i >= 1; i--) {
            unbalancedLeft.insert(i);
            REQUIRE(unbalancedLeft.getHeight() == (11 - i));
        }

        //unbalanced left and right
        BST<unsigned> unbalanced;
        for (int i = 11; i <= 20; i++) {
            unbalanced.insert(i);
        }
        for (int i = 10; i >= 1; i--) {
            unbalanced.insert(i);
        }
        REQUIRE(unbalanced.getHeight() == 11);

        //I could add more tests, but given the fact 
        //that each Node is identical in it's getHeight() method,
        //this shuld be sufficient
    }
}



//the following tests are copied from the lab.
//I keep this uncommented by I have not edited them

TEST_CASE("constructors") {
    SECTION("default") {
        // valid parameter
        BST<unsigned> bst;
        REQUIRE(bst.isEmpty());
        REQUIRE(bst.getNumItems() == 0);
        REQUIRE(bst.myRoot == nullptr);
        REQUIRE(bst.myNumItems == 0);
    }
}

TEST_CASE("insert()") {
    BST<unsigned> bst;
    REQUIRE(bst.isEmpty());

    bst.insert(55);
    REQUIRE(!bst.isEmpty());
    REQUIRE(bst.myRoot != nullptr);
    REQUIRE(bst.myRoot->myItem == 55);
    REQUIRE(bst.myRoot->myLeft == nullptr);
    REQUIRE(bst.myRoot->myRight == nullptr);
    REQUIRE(bst.getNumItems() == 1);

    bst.insert(33);
    REQUIRE(bst.getNumItems() == 2);
    REQUIRE(bst.myRoot->myRight == nullptr);
    REQUIRE(bst.myRoot->myLeft != nullptr);
    REQUIRE(bst.myRoot->myRight == nullptr);
    REQUIRE(bst.myRoot->myLeft->myItem == 33);

    bst.insert(44);
    REQUIRE(bst.getNumItems() == 3);
    REQUIRE(bst.myRoot->myRight == nullptr);
    REQUIRE(bst.myRoot->myLeft->myRight != nullptr);
    REQUIRE(bst.myRoot->myLeft->myRight->myItem == 44);

    bst.insert(11);
    REQUIRE(bst.getNumItems() == 4);
    REQUIRE(bst.myRoot->myRight == nullptr);
    REQUIRE(bst.myRoot->myLeft->myLeft != nullptr);
    REQUIRE(bst.myRoot->myLeft->myLeft->myItem == 11);

    bst.insert(22);
    REQUIRE(bst.getNumItems() == 5);
    REQUIRE(bst.myRoot->myRight == nullptr);
    REQUIRE(bst.myRoot->myLeft->myLeft->myRight != nullptr);
    REQUIRE(bst.myRoot->myLeft->myLeft->myRight->myItem == 22);

    bst.insert(77);
    REQUIRE(bst.getNumItems() == 6);
    REQUIRE(bst.myRoot->myRight != nullptr);
    REQUIRE(bst.myRoot->myRight->myItem == 77);

    bst.insert(66);
    REQUIRE(bst.getNumItems() == 7);
    REQUIRE(bst.myRoot->myRight->myLeft->myItem == 66);

    bst.insert(99);
    REQUIRE(bst.getNumItems() == 8);
    REQUIRE(bst.myRoot->myRight->myRight->myItem == 99);

    bst.insert(88);
    REQUIRE(bst.getNumItems() == 9);
    REQUIRE(bst.myRoot->myRight->myRight->myLeft->myItem == 88);

    REQUIRE_THROWS_AS(bst.insert(55), Exception);
    REQUIRE_THROWS_AS(bst.insert(11), Exception);
    REQUIRE_THROWS_AS(bst.insert(88), Exception);

    bst.insert(111);
    REQUIRE(bst.getNumItems() == 10);
    REQUIRE(bst.myRoot->myRight->myRight->myRight->myItem == 111);
}

TEST_CASE("contains()") {
    BST<unsigned> bst;
    SECTION("empty bst") {
        REQUIRE(!bst.contains(55));
    }
    SECTION("non-empty bst") {
        bst.insert(55);
        REQUIRE(bst.contains(55));

        bst.insert(33);
        bst.insert(77);
        REQUIRE(bst.contains(55));
        REQUIRE(bst.contains(33));
        REQUIRE(bst.contains(77));
        REQUIRE(!bst.contains(11));
        REQUIRE(!bst.contains(111));

        bst.insert(11);
        bst.insert(22);
        bst.insert(44);
        bst.insert(66);
        bst.insert(88);
        bst.insert(99);
        for (int i = 1; i <= 100; ++i) {
            if (i % 11) {
                REQUIRE(!bst.contains(i));
            }
            else {
                REQUIRE(bst.contains(i));
            }
        }
    }
}

TEST_CASE("traversals") {
    BST<double> bst;
    bst.insert(55);
    bst.insert(33);
    bst.insert(11);
    bst.insert(22);
    bst.insert(44);
    bst.insert(77);
    bst.insert(99);
    bst.insert(88);
    bst.insert(66);
    cout << "- Preorder: expecting: 55 33 11 22 44 77 66 99 88" << endl;
    cout << "- Got                :" << flush;
    bst.traversePreorder();
    cout << endl;
    cout << "\n- Postorder: expecting: 22 11 44 33 66 88 99 77 55" << endl;
    cout << "- Got                 :" << flush;
    bst.traversePostorder();
    cout << endl;
    cout << "\n- Inorder: expecting: 11 22 33 44 55 66 77 88 99" << endl;
    cout << "- Got               :" << flush;
    bst.traverseInorder();
    cout << endl;
}
