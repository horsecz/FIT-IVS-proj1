//======== Copyright (c) 2017, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     Red-Black Tree - public interface tests
//
// $NoKeywords: $ivs_project_1 $black_box_tests.cpp
// $Author:     DOMINIK HORKY <xhorky32@stud.fit.vutbr.cz>
// $Date:       $2020-03-03
//============================================================================//
/**
 * @file black_box_tests.cpp
 * @author DOMINIK HORKY
 * 
 * @brief Implementace testu binarniho stromu.
 */

#include <vector>

#include <cstdlib>

#include "gtest/gtest.h"

#include "red_black_tree.h"

using namespace ::testing;

class TestingClass : public Test {
protected:

    /*
     *  Deklarace promennych pouzivanych pozdeji v testech
     */

    BinaryTree tree;

    bool insert_data_a;

    Node_t* node;
    Node_t *insert_data_b;
    Node_t* root;

    std::pair<bool, Node_t *> insert_data;

    std::vector<std::pair<bool, Node_t *>> insert_data_list;

    std::vector<int> insert_data_list_keys;
    std::vector<Node_t *> leaf_nodes;
    std::vector<Node_t *> non_leaf_nodes;
    std::vector<Node_t *> all_nodes;

    /*
     *  Funkce pouzivane pozdeji v testech
     */

    // funkce na "update" promennych
    void UpdateInsertData(std::pair<bool, Node_t*> pair) {
        insert_data = pair;
        insert_data_a = insert_data.first;
        insert_data_b = insert_data.second;
    }

    // vlozi novy uzel s hodnotou key a "aktualizuje" promenne, aby se dali pouzivat v testech
    void InsertNewNode(int key) {
        UpdateInsertData(tree.InsertNode(key));
    }

    // vlozi nove uzly do stromu z 'insert_data_list_keys' a dvojce vlozi do 'insert_data_list'
    void InsertNewNodes() {
        tree.InsertNodes(insert_data_list_keys, insert_data_list);
    }

    // naplni strom (pro tridu NonEmptyTree)
    void FillTree() {
        insert_data_list_keys = {2, 1, 5, 4};
        InsertNewNodes();
    }

    // 'aktualizuje promenne' - data/pole listu, nelistu a vsech uzlu stromu vc. rootu
    void FillStats() {
        tree.GetLeafNodes(leaf_nodes);
        tree.GetNonLeafNodes(non_leaf_nodes);
        tree.GetAllNodes(all_nodes);
        root = tree.GetRoot();
    }

    // funkce testu axiomu 1
    void Axiom1_test() {
        for (Node_t *temp : leaf_nodes) {
            // je bez potomku ?
            ASSERT_TRUE(temp->pLeft == NULL);
            ASSERT_TRUE(temp->pRight == NULL);
            // je cerny ?
            ASSERT_TRUE(temp->color == BinaryTree::BLACK);
        }
    }

    // funkce testu axiomu 2
    void Axiom2_test() {
        for (Node_t *temp : all_nodes) {
            if (temp->color == BinaryTree::RED) { // najdu cerveny uzel => zkontroluju zda potomci jsou cerne
                ASSERT_TRUE(temp->pRight->color == BinaryTree::BLACK);
                ASSERT_TRUE(temp->pLeft->color == BinaryTree::BLACK);
            }
        }
    }

    // funkce testu axiomu 3
    void Axiom3_test() {
        int counter_first = -1;
        int counter = 0;
        Node_t* temp;

        // pole vsech listu ziskane z funkce GetLeafNodes() projdu cele (=> projdu vsechny listy) az do konce
        for (std::vector<Node_t *>::size_type i = 0; i != leaf_nodes.size(); i++) {
            temp = leaf_nodes[i];
            counter = 0;

            // cestuji az ke korenu a zapocitam cerne uzly
            while (temp->pParent != NULL) {
                if (temp->color == BinaryTree::BLACK)
                    counter++;
                temp = temp->pParent;
            }

            // porovnam soucasnou hodnotu s prvni hodnotou - kazdy list ma stejny pocet cernych uzlu jako prvni => vsechny maji stejny pocet cernych uzlu
            if (counter_first != -1)
                ASSERT_EQ(counter_first, counter);
            else
                counter_first = counter;
        }
    }

};

// trida pro testy prazdneho stromu
class EmptyTree : public TestingClass {
protected:

};

// trida pro testy neprazdneho stromu
class NonEmptyTree : public TestingClass {
protected:

};

// trida pro testy axiomu
class TreeAxioms : public TestingClass {
protected:

};

/*
 * TESTY OPERACI NAD PRAZDNYM STROMEM
 * TRIDA:   EmptyTree
 *
 */

// test vkladani jednotlivych uzlu
TEST_F(EmptyTree, InsertNode) {
    Node_t* old_pointer;

    // test vlozeni noveho uzlu
    InsertNewNode(0);
    ASSERT_TRUE(insert_data_a);
    ASSERT_TRUE(insert_data_b == tree.FindNode(0));
    ASSERT_TRUE(tree.GetRoot() == tree.FindNode(0));
    old_pointer = insert_data_b;

    // vlozim novy uzel se stejnou hodnotou
    InsertNewNode(0);
    ASSERT_FALSE(insert_data_a);
    EXPECT_TRUE(insert_data_b == old_pointer);

    // vlozim dalsi uzly
    InsertNewNode(1);
    ASSERT_TRUE(insert_data_a);
    ASSERT_TRUE(insert_data_b == tree.FindNode(1));
    InsertNewNode(5);
    ASSERT_TRUE(insert_data_a);
    ASSERT_TRUE(insert_data_b == tree.FindNode(5));
    old_pointer = insert_data_b;

    // vraci spravny ukazatel ?
    InsertNewNode(3);
    ASSERT_TRUE(insert_data_a);
    ASSERT_TRUE(insert_data_b == tree.FindNode(3));
    InsertNewNode(5);
    ASSERT_FALSE(insert_data_a);
    EXPECT_TRUE(insert_data_b == old_pointer);
}

// test vkladani vice prvku
TEST_F(EmptyTree, InsertNode_list_good) {
    insert_data_list_keys = {1, 2, 5, 3, 7, 4, 9, 6, 8};
    InsertNewNodes();

    ASSERT_FALSE(tree.GetRoot() == NULL);

    // jsou tam vsechny prvky ?
    for (int i = 1; i < 10; i++) {
        ASSERT_TRUE(tree.FindNode(i) != NULL);
    }

    // test vystupniho pole
    UpdateInsertData(insert_data_list[0]);
    EXPECT_TRUE(insert_data_a);
    EXPECT_TRUE(tree.FindNode(1) == insert_data_b);
    UpdateInsertData(insert_data_list[1]);
    EXPECT_TRUE(insert_data_a);
    EXPECT_TRUE(tree.FindNode(2) == insert_data_b);
    UpdateInsertData(insert_data_list[2]);
    EXPECT_TRUE(insert_data_a);
    EXPECT_TRUE(tree.FindNode(5) == insert_data_b);
    UpdateInsertData(insert_data_list[3]);
    EXPECT_TRUE(insert_data_a);
    EXPECT_TRUE(tree.FindNode(3) == insert_data_b);
    UpdateInsertData(insert_data_list[4]);
    EXPECT_TRUE(insert_data_a);
    EXPECT_TRUE(tree.FindNode(7) == insert_data_b);
    UpdateInsertData(insert_data_list[5]);
    EXPECT_TRUE(insert_data_a);
    EXPECT_TRUE(tree.FindNode(4) == insert_data_b);
    UpdateInsertData(insert_data_list[6]);
    EXPECT_TRUE(insert_data_a);
    EXPECT_TRUE(tree.FindNode(9) == insert_data_b);
    UpdateInsertData(insert_data_list[7]);
    EXPECT_TRUE(insert_data_a);
    EXPECT_TRUE(tree.FindNode(6) == insert_data_b);
    UpdateInsertData(insert_data_list[8]);
    EXPECT_TRUE(insert_data_a);
    EXPECT_TRUE(tree.FindNode(8) == insert_data_b);
}

// test vkladani vice prvku - spatne hodnoty
TEST_F(EmptyTree, InsertNode_list_bad) {
    insert_data_list_keys = {1, 2, 5, 2, 1, 3};
    InsertNewNodes();

    ASSERT_FALSE(tree.GetRoot() == NULL);

    // jsou tam vsechny prvky co tam maji byt ?
    for (int i = 1; i < 5; i++) {
        if (i != 4)
            ASSERT_TRUE(tree.FindNode(i) != NULL);
    }

    // test vystupniho pole
    UpdateInsertData(insert_data_list[0]);
    EXPECT_TRUE(insert_data_a);
    EXPECT_TRUE(tree.FindNode(1) == insert_data_b);
    UpdateInsertData(insert_data_list[1]);
    EXPECT_TRUE(insert_data_a);
    EXPECT_TRUE(tree.FindNode(2) == insert_data_b);
    UpdateInsertData(insert_data_list[2]);
    EXPECT_TRUE(insert_data_a);
    EXPECT_TRUE(tree.FindNode(5) == insert_data_b);
    UpdateInsertData(insert_data_list[3]);
    EXPECT_FALSE(insert_data_a);
    EXPECT_TRUE(tree.FindNode(2) == insert_data_b);
    UpdateInsertData(insert_data_list[4]);
    EXPECT_FALSE(insert_data_a);
    EXPECT_TRUE(tree.FindNode(1) == insert_data_b);
    UpdateInsertData(insert_data_list[5]);
    EXPECT_TRUE(insert_data_a);
    EXPECT_TRUE(tree.FindNode(3) == insert_data_b);
}

// test vkladani vice prvku - jeden prvek
TEST_F(EmptyTree, InsertNode_list_empty) {
    insert_data_list_keys = { 0 };
    InsertNewNodes();

    ASSERT_FALSE(tree.GetRoot() == NULL);

    ASSERT_TRUE(tree.FindNode(0) != NULL);
    UpdateInsertData(insert_data_list[0]);
    EXPECT_TRUE(insert_data_a);
    EXPECT_TRUE(tree.FindNode(0) == insert_data_b);
}

// test smazani prvku prazdneho stromu
TEST_F(EmptyTree, DeleteNode) {
    ASSERT_FALSE(tree.DeleteNode(0));
    ASSERT_FALSE(tree.DeleteNode(120));
    ASSERT_FALSE(tree.DeleteNode(-1));
    ASSERT_FALSE(tree.DeleteNode(-89));
    ASSERT_FALSE(tree.DeleteNode(42));
}

TEST_F(EmptyTree, FindNode) {
    ASSERT_TRUE(tree.FindNode(0) == NULL);
    ASSERT_TRUE(tree.FindNode(1) == NULL);
    ASSERT_TRUE(tree.FindNode(-5) == NULL);
    ASSERT_TRUE(tree.FindNode(-89) == NULL);
    ASSERT_TRUE(tree.FindNode(9) == NULL);
}

// (dodatecny) test vytvoreni prazdneho stromu
TEST_F(EmptyTree, Construct) {
    EXPECT_NO_THROW(BinaryTree());
    ASSERT_TRUE(tree.GetRoot() == NULL);
}

/*
 * TESTY OPERACI NAD NEPRAZDNYM STROMEM
 * TRIDA:   NonEmptyTree
 *
 * Funkce FillTree() naplni strom uzly:  2, 1, 5, 4
 */

// test vkladani prvku do neprazdneho stromu
TEST_F(NonEmptyTree, InsertNode) {
    FillTree();
    Node_t* old_pointer;

    ASSERT_FALSE(tree.GetRoot() == NULL);

    // vlozeni prvku co tam nejsou
    InsertNewNode(3);
    ASSERT_TRUE(insert_data_a);
    ASSERT_TRUE(insert_data_b == tree.FindNode(3));
    InsertNewNode(6);
    ASSERT_TRUE(insert_data_a);
    ASSERT_TRUE(insert_data_b == tree.FindNode(6));
    InsertNewNode(8);
    ASSERT_TRUE(insert_data_a);
    ASSERT_TRUE(insert_data_b == tree.FindNode(8));
    InsertNewNode(7);
    ASSERT_TRUE(insert_data_a);
    ASSERT_TRUE(insert_data_b == tree.FindNode(7));
    InsertNewNode(0);
    ASSERT_TRUE(insert_data_a);
    ASSERT_TRUE(insert_data_b == tree.FindNode(0));
    old_pointer = insert_data_b;

    // vlozeni prvku co tam je
    InsertNewNode(5);
    ASSERT_FALSE(insert_data_a);
    ASSERT_TRUE(insert_data_b == tree.FindNode(5));
    ASSERT_TRUE(insert_data_b != old_pointer);
    old_pointer = insert_data_b;

    // vlozeni dalsiho prvku & test spravnosti ukazatele (musi ukazovat na stejne misto!)
    InsertNewNode(10);
    ASSERT_TRUE(insert_data_a);
    ASSERT_TRUE(insert_data_b == tree.FindNode(10));
    InsertNewNode(5);
    ASSERT_FALSE(insert_data_a);
    ASSERT_TRUE(insert_data_b == tree.FindNode(5));
    ASSERT_TRUE(insert_data_b == old_pointer);
}

// test vkladani spravnycho hodnost do neprazdneho stromu
TEST_F(NonEmptyTree, InsertNode_list_good) {
    FillTree();
    insert_data_list_keys = {3, 6, 9, 7};
    InsertNewNodes();

    ASSERT_FALSE(tree.GetRoot() == NULL);

    // nenahradilo to nejaky prvek? jsou tam vsechny co maji byt ?
    for (int i = 1; i < 10; i++) {
        if (i != 8)
            EXPECT_TRUE(tree.FindNode(i) != NULL);
    }

    // test vystupniho pole
    UpdateInsertData(insert_data_list[0]);
    EXPECT_TRUE(insert_data_a);
    EXPECT_TRUE(tree.FindNode(3) == insert_data_b);
    UpdateInsertData(insert_data_list[1]);
    EXPECT_TRUE(insert_data_a);
    EXPECT_TRUE(tree.FindNode(6) == insert_data_b);
    UpdateInsertData(insert_data_list[2]);
    EXPECT_TRUE(insert_data_a);
    EXPECT_TRUE(tree.FindNode(9) == insert_data_b);
    UpdateInsertData(insert_data_list[3]);
    EXPECT_TRUE(insert_data_a);
    EXPECT_TRUE(tree.FindNode(7) == insert_data_b);

}

// test vkladani 'spatnych' hodnot do neprazdneho stromu
TEST_F(NonEmptyTree, InsertNode_list_bad) {
    FillTree();
    insert_data_list_keys = {3, 6, 9, 2, 5, 11};
    InsertNewNodes();

    ASSERT_FALSE(tree.GetRoot() == NULL);

    // nenahradilo to nejaky prvek? jsou tam vsechny co maji byt ?
    for (int i = 1; i < 10; i++) {
        if (i != 8 && i != 7)
            EXPECT_TRUE(tree.FindNode(i) != NULL);
    }

    // test vystupniho pole
    UpdateInsertData(insert_data_list[0]);
    EXPECT_TRUE(insert_data_a);
    EXPECT_TRUE(tree.FindNode(3) == insert_data_b);
    UpdateInsertData(insert_data_list[1]);
    EXPECT_TRUE(insert_data_a);
    EXPECT_TRUE(tree.FindNode(6) == insert_data_b);
    UpdateInsertData(insert_data_list[2]);
    EXPECT_TRUE(insert_data_a);
    EXPECT_TRUE(tree.FindNode(9) == insert_data_b);
    UpdateInsertData(insert_data_list[3]);
    EXPECT_FALSE(insert_data_a);
    EXPECT_TRUE(tree.FindNode(2) == insert_data_b);
    UpdateInsertData(insert_data_list[4]);
    EXPECT_FALSE(insert_data_a);
    EXPECT_TRUE(tree.FindNode(5) == insert_data_b);
    UpdateInsertData(insert_data_list[5]);
    EXPECT_TRUE(insert_data_a);
    EXPECT_TRUE(tree.FindNode(11) == insert_data_b);

}

// test vkladani vice prvku do neprazdneho stromu - jeden prvek
TEST_F(NonEmptyTree, InsertNode_list_empty) {
    FillTree();
    insert_data_list_keys = { 0 };
    InsertNewNodes();

    ASSERT_FALSE(tree.GetRoot() == NULL);

    ASSERT_TRUE(tree.FindNode(0) != NULL);
    UpdateInsertData(insert_data_list[0]);
    EXPECT_TRUE(insert_data_a);
    EXPECT_TRUE(tree.FindNode(0) == insert_data_b);

    for (int i = 0; i < 6; i++) {
        if (i != 3)
            EXPECT_TRUE(tree.FindNode(i) != NULL);
    }
}

// test mazani prvku z neprazdneho stromu
TEST_F(NonEmptyTree, DeleteNode) {
    FillTree();

    // mazani prvku ze seznamu
    ASSERT_TRUE(tree.DeleteNode(1));
    ASSERT_FALSE(tree.DeleteNode(1)); // uz byl smazan
    ASSERT_TRUE(tree.DeleteNode(2));
    ASSERT_FALSE(tree.DeleteNode(3)); // tento tam neni
    ASSERT_TRUE(tree.DeleteNode(4));
    ASSERT_TRUE(tree.DeleteNode(5));
    ASSERT_TRUE(tree.GetRoot() == NULL); // cely seznam byl smazany => root == NULL
}

// test hledani prvku v neprazdnem stromu
TEST_F(NonEmptyTree, FindNode) {
    FillTree();

    // hledani prvku v seznamu
    ASSERT_TRUE(tree.FindNode(1) != NULL);
    ASSERT_TRUE(tree.FindNode(2) != NULL);
    ASSERT_FALSE(tree.FindNode(3) != NULL); // tento prvek tam neni!
    ASSERT_TRUE(tree.FindNode(4) != NULL);
    ASSERT_TRUE(tree.FindNode(5) != NULL);
    ASSERT_TRUE(tree.FindNode(-1) == NULL); // neexistuje
    ASSERT_TRUE(tree.FindNode(10) == NULL); // neexistuje
}

/*
 * TESTY 3 ZAKLADNICH AXIOMU RED-BLACK TREE
 * TRIDA:   ThreeAxioms
 *
 */

// test zda vsechny listove uzly (ty bez potomku) jsou cerne - nezavisle na datech ve stromu
TEST_F(TreeAxioms, Axiom1) {
    Axiom1_test();
}

// (dodatecny) test na ruznych variantach stromu (1 prvek, vice prvku) - prazdny se otestuje vyse
TEST_F(TreeAxioms, Axiom1_nonEmpty) {
    // test stromu s 1 prvkem
    tree.InsertNode(0);
    FillStats();
    Axiom1_test();

    // test stromu s vice prvky
    FillTree();
    FillStats();
    Axiom1_test();

    // a neprosto to jenom nahodou ?
    tree.InsertNode(-5);
    tree.InsertNode(-2);
    tree.InsertNode(69);
    FillTree(); // "vlozi" se stejne hodnoty ! => nevlozi se do stromu vlastne nic
    FillStats();
    Axiom1_test();
}

// test potomku - pokud je uzel cerveny => oba potomci jsou cerne -> prazdny strom - nezavisle na datech ve stromu
TEST_F(TreeAxioms, Axiom2) {
    Axiom2_test();
}

// (dodatecny) test 2. axiomu na neprazdnem stromu
TEST_F(TreeAxioms, Axiom2_nonEmpty) {
    // pouze koren
    tree.InsertNode(1);
    FillStats();
    Axiom2_test();

    // vice prvku
    FillTree();
    FillStats();
    Axiom2_test();

    // nevyslo to jen nahodou ? pridam dalsi nahodne uzly
    tree.InsertNode(91);
    tree.InsertNode(-10);
    tree.InsertNode(-69);
    FillTree(); // "vlozi" se stejne hodnoty => neprida se nic
    FillStats();
    Axiom2_test();
}

// test zda kazda cesta od kazdeho listoveho uzlu (bez potomku) ke koreni obsahuje stejny pocet cernych uzlu - prazdny strom
TEST_F(TreeAxioms, Axiom3) {
    Axiom3_test();
}

// (dodatecny) test 3. axiomu na neprazdnem stromu
TEST_F(TreeAxioms, Axiom3_nonEmpty) {
    // jen koren
    tree.InsertNode(1);
    FillStats();
    Axiom3_test();

    // vice prvku
    FillTree();
    FillStats();
    Axiom3_test();

    // nebyla to jen nahoda ze to vyslo ? (nebyla!)
    tree.InsertNode(15);
    tree.InsertNode(-19);
    tree.InsertNode(-300);
    tree.InsertNode(98);
    tree.InsertNode(420);
    FillTree(); // "vlozi" se stejen hodnoty => nic se neprida
    FillStats();
    Axiom3_test();
}

/*** Konec souboru black_box_tests.cpp ***/
