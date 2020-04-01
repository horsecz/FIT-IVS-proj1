//======== Copyright (c) 2017, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     White Box - Tests suite
//
// $NoKeywords: $ivs_project_1 $white_box_code.cpp
// $Author:     DOMINIK HORKY <xhorky32@stud.fit.vutbr.cz>
// $Date:       $2020-03-03
//============================================================================//
/**
 * @file white_box_tests.cpp
 * @author DOMINIK HORKY
 * 
 * @brief Implementace testu prace s maticemi.
 */

#include "gtest/gtest.h"
#include "white_box_code.h"

using namespace ::testing;

// trida pro testovani matic
class TestMatrix : public Test {
    protected:

        /*
         * Deklarace matic a dalsich promennych pouzivanych pozdeji v testech
         */

        Matrix matrix;
        Matrix matrix2;
        Matrix addition; // matice vysledku souctu matic
        Matrix multiplied; // matice vysledku nasobeni (matic)
        std::vector<double> result; // vysledky vypoctu rovnic

        /*
         *  Preddefinovane matice s hodnotami
         */

        std::vector<std::vector<double>> matrix_1_3x4 = {
                {1,  2,  -3, 0},
                {10, -2, 0,  4.219},
                {-1, 0,  1,  5},
        };

        std::vector<std::vector<double>> matrix_1_3x3 = {
                {1,  2,  -3},
                {10, -2, 0},
                {-1, 0,  1},
        };

        std::vector<std::vector<double>> matrix_2_3x3 = {
                {1,  0,  8},
                {0, 2, 5},
                {0, 4,  3},
        };

        std::vector<std::vector<double>> matrix_2_multiplied = {
                {1, -8, 9},
                {10, -4, 70},
                {-1, 4, -5},
        };

        std::vector<std::vector<double>> matrix_3_8x8 = {
                {1, 2, 3, 4, 5, 6, 7, 10},
                {9, 8, 7, 6, 5, 4, 3, 9},
                {2, 2, 2, 2, 2, 2, 2, 7},
                {9, 9, 8, 4, 1, 1, 2, 5},
                {8, 7, 2, 6, 1, 2, 1, 4},
                {8, 1, 2, 3, 48, 9, 2, 3},
                {9, 9, 9, 8, 1, 2, 3, 2},
                {8, 4, 2, 10, 15, 20, 9, 1},
        };

        std::vector<std::vector<double>> matrix_4_2x2 = {
                {1, 5},
                {9, 4},
        };

        /*
         * Singularni matice
         */

        std::vector<std::vector<double>> matrix_singular_1_3x3 = {
                {5, 3, 1},
                {1, 2, 4},
                {2, 4, 8},
        };

        std::vector<std::vector<double>> matrix_singular_2_3x3 = {
                {5, 3, 1},
                {1, 2, 4},
                {1, 2, 4},
        };

        std::vector<std::vector<double>> matrix_singular_3_3x3 = {
                {5, 3, 1},
                {1, 2, 4},
                {0, 0, 0},
        };

        /*
         *  Hodnoty vkladane do matic & pouzite k praci s nimi & testovani
         */

        std::vector<std::vector<double>> values_1 = {
                {1, 3, -1},
                {0},
                {1, 2, 3, 4},
        };

        std::vector<std::vector<double>> values_2 = {
                {0, 1, 2, 3, 4},
                {1, 2, 3, 4},
        };

        std::vector<std::vector<double>> values_3 = {
                {1, 2},
                {3, 4},
                {5, 6},
                {1, 2, 3},
        };

        std::vector<std::vector<double>> values_4 = {
                {1, 5},
                {8, 4},
        };

        std::vector<std::vector<double>> values_5 = {
                {1, 1, 1},
                {0, 5, 1},
                {0, 0, 1},
        };

        std::vector<std::vector<double>> values_6 = {
                {2,  4,  -6, 0},
                {20, -4, 0,  8.438},
                {-2, 0,  2,  10},
                {0, 0, 1, 10},
        };

        std::vector<std::vector<double>> values_7 = {
                {5, 4, 3},
                {0, 1},
                {1, 2, 5},
        };

        /*
         *  Hodnoty pravych stran lin. rovnic
         */

        // hodnoty pro singularni matice
        std::vector<double> vals_right_sing_2 = {1, 5, 5};
        std::vector<double> vals_right_sing_3 = {1, 5, 0};

        // hodnoty pro 'spravne' matice
        std::vector<double> vals_right_1xN = {8};
        std::vector<double> vals_right_1xN_zeroed = {0};
        std::vector<double> vals_right_2xN = {1, 2};
        std::vector<double> vals_right_2xN_zeroed = {0, 0};
        std::vector<double> vals_right_3xN = {1, 5, 10};
        std::vector<double> vals_right_3xN_zeroed = {0, 0, 0};
        std::vector<double> vals_right_4xN = {1, 2, 3, 4};
        std::vector<double> vals_right_4xN_zeroed = {0, 0, 0, 0};
        std::vector<double> vals_right_8xN = {100, 13, 15, 98, 19, 20, 8, 1};
        std::vector<double> vals_right_8xN_zeroed = {0, 0, 0, 0, 0, 0, 0, 0};

        /*
         *  Vysledky vypoctu lin. rovnic z matic
         */

        std::vector<double> equation_values_5_result = {-8, -1, 10};
        std::vector<double> equation_8xN_result = {-314.35836693548387092, 364.64616935483870975, -21.258568548387096854, -9.246471774193548377, 34.910282258064516124, 92.809979838709677395, -131.69052419354838707, -2.375};
        std::vector<double> equation_matrix_4_result = {0.14634146341463414635, 0.17073170731707317073};

        /*
         *  Funkce pouzivane pri testech
         */

        // vytvori matici o velikosti rows a cols
        Matrix newMatrix(size_t rows, size_t cols) {
            return Matrix(rows, cols);
        }

        // overi funkci get - ziskavani hodnot v rozsahu matice (+ dodatecna kontrola zda ty hodnoty jsou ziskane/nastavene spravne)
        void checkValues(size_t rows, size_t cols, std::vector<std::vector<double>> expected_values) {
            for (int x = 0; x < rows; x++) {
                for (int y = 0; y < cols; y++) {
                    ASSERT_DOUBLE_EQ(matrix.get(x, y), expected_values[x][y]);
                }
            }
        }

        // overi funkci scitani matic
        void additionCheck(size_t rows, size_t cols, std::vector<std::vector<double>> vector1, std::vector<std::vector<double>> vector2) {
            for (int x = 0; x < rows; x++) {
                for (int y = 0; y < cols; y++) {
                    EXPECT_DOUBLE_EQ(addition.get(x, y), (vector1[x][y] + vector2[x][y]));
                }
            }
        }

        // overi funkci nasobeni matic
        void multiplyCheck(size_t rows, size_t cols, std::vector<std::vector<double>> vector, double multiplyNumber) {
            for (int x = 0; x < rows; x++) {
                for (int y = 0; y < cols; y++) {
                    ASSERT_DOUBLE_EQ(multiplied.get(x, y), vector[x][y] * multiplyNumber);
                }
            }
        }

        // overi funkci vypoctu linearnich rovnic
        void checkEquation(size_t rows, std::vector<double> expected_vales) {
            for (int i = 0; i < rows; i++) {
                EXPECT_FLOAT_EQ(result[i], expected_vales[i]);
            }
        }
    };

    // test vytvoreni/konstrukce matice
    TEST_F(TestMatrix, Construction) {
        // spravne hodnoty ((rows > 1 && cols > 1) || nic) => zadna chyba
        EXPECT_NO_THROW(Matrix matrix_1x1_empty);
        EXPECT_NO_THROW(Matrix());
        EXPECT_NO_THROW(Matrix(1, 1));
        EXPECT_NO_THROW(Matrix(100, 500));
        EXPECT_NO_THROW(Matrix(500, 100));
        EXPECT_NO_THROW(Matrix(100, 100));

        // chybne hodnoty (rows < 1 || cols < 1) nebo jine blaboly => chyba
        EXPECT_ANY_THROW(Matrix(0, 0));
        EXPECT_ANY_THROW(Matrix(0, 10));
        EXPECT_ANY_THROW(Matrix(3, 0));
    }

    // test nastavovani jednotlivych hodnot do matice
    TEST_F(TestMatrix, SetSingleValues) {
        matrix = newMatrix(5, 8);

        // spravne hodnoty, tzn. (row & col hodnoty nezaporne) && (row & col hodnoty v rozsahu velikosti matice)
        ASSERT_TRUE(matrix.set(1, 1, 1));
        ASSERT_TRUE(matrix.set(4, 7, 189.219));
        ASSERT_TRUE(matrix.set(1, 7, -500));
        ASSERT_TRUE(matrix.set(4, 1, 0));

        // spatne hodnoty - preteceni unsigned <=> nastavovani hodnot mimo rozsah
        ASSERT_FALSE(matrix.set(-1, 1, 10));
        ASSERT_FALSE(matrix.set(1, -1, -5));
        ASSERT_FALSE(matrix.set(-1, -1, 15));
        ASSERT_FALSE(matrix.set(5, 8, -1));
        ASSERT_FALSE(matrix.set(5, 7, 3));
        ASSERT_FALSE(matrix.set(4, 8, 1));
        ASSERT_FALSE(matrix.set(std::vector<std::vector<double>> {0, {0, 0}}));
    }

    // kontrola spravnosti funkce set (jednotlive hodnoty)
    TEST_F(TestMatrix, SetSingleValues_correctCheck) {
        matrix = newMatrix(3, 3);
        matrix.set(0, 0, 5);
        matrix.set(2, 2, -6);
        matrix.set(1, 0, 4.321);
        matrix.set(2, 1, -0.2);

        // pokud jsou hodnoty v matici nastaveny spravne, pak se soucet bude rovnat
        ASSERT_TRUE((matrix.get(0, 0) + matrix.get(2, 2) + matrix.get(1, 0) + matrix.get(2, 1)) == (5 + (-6) + 4.321 + (-0.2)));
    }

    // test nastavovani hodnot z pole
    TEST_F(TestMatrix, SetArrayValues) {
        matrix = newMatrix(3, 4);
        matrix2 = newMatrix(3, 3);

        // spravne hodnoty - v rozsahu matice
        ASSERT_TRUE(matrix.set(matrix_1_3x4));
        ASSERT_TRUE(matrix2.set(matrix_1_3x3));
        ASSERT_TRUE(matrix2.set(values_7));

        // spatne hodnoty - pole mensi nez matice, pole vetsi nez matice
        ASSERT_FALSE(matrix.set(values_1));
        ASSERT_FALSE(matrix.set(values_2));
        ASSERT_FALSE(matrix.set(values_3));
        ASSERT_FALSE(matrix2.set(values_2));
        ASSERT_FALSE(matrix2.set(values_3));
        ASSERT_FALSE(matrix2.set(std::vector<std::vector<double>> {{1, 2, 3, 4, 5, 6, 7, 8, 9}}));
    }

    // test spravnosti set (hodnoty z pole)
    TEST_F(TestMatrix, SetArrayValues_correctCheck) {
        // vytvorim matici, nastavim hodnoty, zkontroluji
        matrix = newMatrix(3, 3);
        matrix.set(matrix_1_3x3);
        checkValues(3, 3, matrix_1_3x3);

        matrix = newMatrix(2, 2);
        matrix.set(matrix_4_2x2);
        checkValues(2, 2, matrix_4_2x2);

        matrix = newMatrix(8, 8);
        matrix.set(matrix_3_8x8);
        checkValues(8, 8, matrix_3_8x8);

        // funguje to i na nectvercove matice ?
        matrix = newMatrix(3, 4);
        matrix.set(matrix_1_3x4);
        checkValues(3, 4, matrix_1_3x4);
    }

    // test ziskavani hodnot z matic
    TEST_F(TestMatrix, GetMatrixValue) {
        // 3x4 matice
        matrix = newMatrix(3, 4);
        matrix.set(matrix_1_3x4);
        EXPECT_NO_THROW(matrix.get(0, 0));
        EXPECT_NO_THROW(matrix.get(2, 3));
        EXPECT_NO_THROW(matrix2.get(0, 0));

        // ziskavani hodnot mimo matici
        EXPECT_ANY_THROW(matrix.get(3, 4));
        EXPECT_ANY_THROW(matrix.get(3, 0));
        EXPECT_ANY_THROW(matrix.get(0, 4));

        // co 2x2 ?
        matrix = newMatrix(2, 2);
        matrix.set(matrix_4_2x2);
        EXPECT_NO_THROW(matrix.get(0, 0));
        EXPECT_NO_THROW(matrix.get(1, 0));

        EXPECT_ANY_THROW(matrix.get(1, 2));
        EXPECT_ANY_THROW(matrix.get(2, 1));

    }

    // kontrola spravnosti vystupu funkce get
    TEST_F(TestMatrix, GetMatrixValue_correctCheck) {
        // 3x4 matice
        matrix = newMatrix(3, 4);
        matrix.set(matrix_1_3x4);
        checkValues(3, 4, matrix_1_3x4);

        // 8x8 matice
        matrix = newMatrix(8, 8);
        matrix.set(matrix_3_8x8);
        checkValues(8, 8, matrix_3_8x8);

        // 2x2 matice
        matrix = newMatrix(2, 2);
        matrix.set(matrix_4_2x2);
        checkValues(2, 2, matrix_4_2x2);

        // 1x1 matice
        matrix = newMatrix(1, 1);
        matrix.set(0, 0, 10);
        checkValues(1, 1, std::vector<std::vector<double>> { { 10 } });
    }

    // porovnavani (rovnost) dvou matic
    TEST_F(TestMatrix, MatrixCompare) {
        // stejne matice
        matrix = newMatrix(3, 4);
        matrix2 = newMatrix(3, 4);
        matrix.set(matrix_1_3x4);
        matrix2.set(matrix_1_3x4);
        EXPECT_TRUE(matrix == matrix2);

        // dve 1x1 prazdne
        Matrix small1;
        Matrix small2;
        EXPECT_TRUE(small1 == small2);

        // ruzne hodnoty matic
        for (int x = 0; x < 3; x++) {
            for (int y = 0; y < 4; y++) {
                matrix.set(x, y, matrix.get(x, y) + 1);
                EXPECT_FALSE(matrix == matrix2);
                matrix.set(x, y, matrix.get(x, y) - 1);
            }
        }

        // ruzna velikost matic
        matrix = newMatrix(3, 4);
        matrix2 = newMatrix(2, 4);
        EXPECT_ANY_THROW(matrix == matrix2);
    }

    // scitani matic
    TEST_F(TestMatrix, MatrixAddition) {
        // 1x1 prazdne
        EXPECT_NO_THROW(matrix+matrix2);

        // stejne velke => spravne
        matrix = newMatrix(3, 4);
        matrix2 = newMatrix(3, 4);
        matrix.set(matrix_1_3x4);
        matrix2.set(matrix_1_3x4);
        EXPECT_NO_THROW(matrix+matrix2);
        Matrix addition = matrix+matrix2;

        // ruzne velikosti matic
        matrix2 = newMatrix(2, 4);
        EXPECT_ANY_THROW(matrix+matrix2);
        matrix2 = newMatrix(3, 5);
        EXPECT_ANY_THROW(matrix+matrix2);
        matrix = newMatrix(3, 6);
        EXPECT_ANY_THROW(matrix+matrix2);
        matrix = newMatrix(2, 5);
        EXPECT_ANY_THROW(matrix+matrix2);

        // sama se sebou => stejne velke
        EXPECT_NO_THROW(matrix+matrix);
    }

    // test spravnosti scitani matic
    TEST_F(TestMatrix, MatrixAddition_correctCheck) {
        // 3x4 matice
        matrix = newMatrix(3, 4);
        matrix2 = newMatrix(3, 4);
        matrix.set(matrix_1_3x4);
        matrix2.set(matrix_1_3x4);
        addition = matrix+matrix2;
        additionCheck(3, 4, matrix_1_3x4, matrix_1_3x4);

        // 2x2 matice
        matrix = newMatrix(2, 2);
        matrix2 = newMatrix(2, 2);
        matrix.set(std::vector<std::vector<double>> { {10, 8}, {1, 7} });
        matrix2.set(std::vector<std::vector<double>> { {0, 98}, {-50, -4} });
        addition = matrix+matrix2;
        additionCheck(2, 2, std::vector<std::vector<double>> { {10, 8}, {1, 7} }, std::vector<std::vector<double>> { {0, 98}, {-50, -4} });

        // 8x8 matice
        matrix = newMatrix(8, 8);
        matrix2 = newMatrix(8, 8);
        matrix.set(matrix_3_8x8);
        matrix2.set(matrix_3_8x8);
        addition = matrix+matrix2;
        additionCheck(8, 8, matrix_3_8x8, matrix_3_8x8);
    }

    // nasobeni matice skalarem
    TEST_F(TestMatrix, MatrixMultiplyByNumber) {
        // nulova 1x1 matice
        EXPECT_NO_THROW(matrix*10);

        // 3x3 matice
        matrix = newMatrix(3, 3);
        matrix.set(matrix_1_3x3);
        EXPECT_NO_THROW(matrix*6);

        // 3x4 matice
        matrix = newMatrix(3, 4);
        matrix.set(matrix_1_3x4);
        EXPECT_NO_THROW(matrix*10);

        // 2x2 matice
        matrix = newMatrix(2, 2);
        matrix.set(matrix_4_2x2);
        EXPECT_NO_THROW(matrix*9.81);
    }

    // kontrola nasobeni matic skalarem
    TEST_F(TestMatrix, MatrixMultiplyByNumber_correctCheck) {
        // 8x8 matice
        matrix = newMatrix(8, 8);
        matrix.set(matrix_3_8x8);
        multiplied = matrix*(-1.9823);
        multiplyCheck(8, 8, matrix_3_8x8, -1.9823);

        // 3x3 matice
        matrix = newMatrix(3, 3);
        matrix.set(matrix_1_3x3);
        multiplied = matrix*6;
        multiplyCheck(3, 3, matrix_1_3x3, 6);

        // 2x2 matice
        matrix = newMatrix(2, 2);
        matrix.set(matrix_4_2x2);
        multiplied = matrix*6901;
        multiplyCheck(2, 2, matrix_4_2x2, 6901);
    }

    // kontrola nasobeni matice matici
    TEST_F(TestMatrix, MatrixMultiply) {
        // 1x1 prazdna matice
        EXPECT_NO_THROW(matrix*matrix2);

        // 3x3 ctvercova matice
        matrix = newMatrix(3, 3);
        matrix2 = newMatrix(3, 3);
        matrix.set(matrix_1_3x3);
        matrix2.set(matrix_2_3x3);
        EXPECT_NO_THROW(matrix*matrix2);
        EXPECT_NO_THROW(matrix2*matrix);
        EXPECT_NO_THROW(matrix*matrix);

        // nectvercova matice - sloupce matice1 == radky matice2
        matrix = newMatrix(3, 4);
        matrix2 = newMatrix(4, 3);
        EXPECT_NO_THROW(matrix2*matrix);

        // sloupce != radky -> tyto vynasobit nejdou (ani sama se sebou, pokud neni ctvercova)
        matrix2 = newMatrix(3, 4);
        matrix.set(matrix_1_3x4);
        matrix2.set(matrix_1_3x4);
        EXPECT_ANY_THROW(matrix2*matrix);
        EXPECT_ANY_THROW(matrix2*matrix2);
    }

    // kontrola funkce (spravnosti) nasobeni matice matici
    TEST_F(TestMatrix, MatrixMultiply_correctCheck) {
        matrix = newMatrix(3, 3);
        matrix2 = newMatrix(3, 3);
        matrix.set(matrix_1_3x3);
        matrix2.set(matrix_2_3x3);

        // komutativita (u matic a,b plati a*b != b*a <=> a != b) => nasobeni neni komutativni, asociativita
        EXPECT_FALSE((matrix2*matrix) == (matrix*matrix2));
        EXPECT_TRUE((matrix*(matrix2*matrix)) == ((matrix*matrix2)*matrix));

        // umi to nasobit? (a ja?)
        Matrix multiplied = matrix*matrix2;
        for (int x = 0; x < 3; x++) {
            for (int y = 0; y < 3; y++) {
                EXPECT_DOUBLE_EQ(multiplied.get(x, y), matrix_2_multiplied[x][y]);
            }
        }

    }

    // kontrola reseni linearnich rovnic v "beznych" pripadech
    TEST_F(TestMatrix, MatrixEquation_standard) {
        // reseni n x n matice, počet řádků == počet prvků pole b (pravých stran rovnic); hodnoty == 0 a hodnoty != 0
        matrix = newMatrix(3, 3);
        matrix.set(matrix_1_3x3);
        EXPECT_NO_THROW(matrix.solveEquation(vals_right_3xN));
        EXPECT_NO_THROW(matrix.solveEquation(vals_right_3xN_zeroed));

        matrix = newMatrix(4, 4);
        matrix.set(values_6);
        EXPECT_NO_THROW(matrix.solveEquation(vals_right_4xN));
        EXPECT_NO_THROW(matrix.solveEquation(vals_right_4xN_zeroed));

        // nesouhlas počtu řádků a počtu prvků pole b
        EXPECT_ANY_THROW(matrix2.solveEquation(vals_right_3xN));
    }

    // kontrola reseni linearnich rovnic - test singularnich matic
    TEST_F(TestMatrix, MatrixEquation_singular) {
        // matice neni ctvercova
        matrix2 = newMatrix(3, 4);
        matrix2.set(matrix_1_3x4);
        EXPECT_ANY_THROW(matrix2.solveEquation(std::vector<double>{1, 2, 3, 4}));

        // singularni matice => det. A = 0
        // dva linearne zavisle radky (řádek a je n-násobek řádku b)
        matrix = newMatrix(3, 3);
        matrix.set(matrix_singular_1_3x3);
        EXPECT_ANY_THROW(matrix.solveEquation(vals_right_3xN));
        EXPECT_ANY_THROW(matrix.solveEquation(vals_right_sing_2));

        // dva stejne radky
        matrix.set(matrix_singular_2_3x3);
        EXPECT_ANY_THROW(matrix.solveEquation(vals_right_sing_2));
        EXPECT_ANY_THROW(matrix.solveEquation(vals_right_3xN));

        // jeden nulovy radek
        matrix.set(matrix_singular_3_3x3);
        EXPECT_ANY_THROW(matrix.solveEquation(vals_right_sing_3));
        EXPECT_ANY_THROW(matrix.solveEquation(vals_right_3xN));

        // nulova matice
        EXPECT_ANY_THROW(matrix.solveEquation(vals_right_3xN)); // 0x + 0y + 0z = k; k != 0
        EXPECT_ANY_THROW(matrix.solveEquation(vals_right_3xN_zeroed)); // k = 0
    }

    // kontrola reseni linearnich rovnic - test ruznych velikosti
     TEST_F(TestMatrix, MatrixEquation_sizes) {
        // 1x1 matice
        matrix = newMatrix(1, 1);
        EXPECT_ANY_THROW(matrix.solveEquation(vals_right_1xN_zeroed));
        EXPECT_ANY_THROW(matrix.solveEquation(vals_right_1xN));
        matrix.set(0, 0, 10);
        EXPECT_NO_THROW(matrix.solveEquation(vals_right_1xN_zeroed));
        EXPECT_NO_THROW(matrix.solveEquation(vals_right_1xN));

        // 2x2 matice
        matrix = newMatrix(2, 2);
        EXPECT_ANY_THROW(matrix.solveEquation(vals_right_2xN_zeroed));
        EXPECT_ANY_THROW(matrix.solveEquation(vals_right_2xN));
        matrix.set(values_4);
        EXPECT_NO_THROW(matrix.solveEquation(vals_right_2xN_zeroed));
        EXPECT_NO_THROW(matrix.solveEquation(vals_right_2xN));

        // 4x4 matice (a vetsi)
        matrix = newMatrix(4, 4);
        EXPECT_ANY_THROW(matrix.solveEquation(vals_right_4xN_zeroed));
        EXPECT_ANY_THROW(matrix.solveEquation(vals_right_4xN));
        matrix.set(values_6);
        EXPECT_NO_THROW(matrix.solveEquation(vals_right_4xN_zeroed));
        EXPECT_NO_THROW(matrix.solveEquation(vals_right_4xN));
    }

    // test spravneho vypoctu soustav linearnich rovnic
    TEST_F(TestMatrix, MatrixEquation_correctCheck) {
        // 2x2 matice
        matrix = newMatrix(2, 2);
        matrix.set(matrix_4_2x2);
        result = matrix.solveEquation(vals_right_2xN);
        checkEquation(3, equation_matrix_4_result);

        // vyresi to spravne homogenni soustavu?
        ASSERT_TRUE((matrix.solveEquation(vals_right_2xN_zeroed)) == (std::vector<double> {0, 0}));

        // 3x3 matice
        matrix = newMatrix(3, 3);
        matrix.set(values_5);
        ASSERT_TRUE((matrix.solveEquation(vals_right_3xN)) == equation_values_5_result);

        // vyresi to spravne homogenni soustavu?
        ASSERT_TRUE((matrix.solveEquation(vals_right_3xN_zeroed)) == (std::vector<double> {0, 0, 0}));

        // 8x8 matice
        matrix = newMatrix(8, 8);
        matrix.set(matrix_3_8x8);
        result = matrix.solveEquation(vals_right_8xN);
        checkEquation(8, equation_8xN_result);

        // vyresi to spravne homogenni soustavu?
        ASSERT_TRUE((matrix.solveEquation(vals_right_8xN_zeroed)) == (std::vector<double>{0, 0, 0, 0, 0, 0, 0, 0}));
    }

/*** Konec souboru white_box_tests.cpp ***/