/* Name: Montasir Mahir and Weijia Li
 * Course: CS106B
 * Section: Thu 7:30 pm
 * Description: This file counts ways to arrange A's and B's.
 * It also counts arrangements where A's stay in the lead.
 */
#include "recursion.h"
#include "SimpleTest.h"
using namespace std;

/*
 * This function counts the ways to arrange a A's and b B's.
 * It recursively counts the arrangements that start with A and B.
 */
int countAllOrderings(int a, int b) {
    if (a == 0 || b == 0) {
        return 1;
    }
    return countAllOrderings(a - 1, b) + countAllOrderings(a , b - 1);
}

/*
 * This function counts good arrangements using the current lead.
 * It returns 0 if A is no longer in the lead. Otherwise, it
 * recursively counts the arrangements after choosing an A or B.
 */
int goodOrderingsHelper(int a, int b, int lead) {
    if (lead <= 0) {
        return 0;
    }
    if (a == 0 || b == 0) {
        return 1;
    }
    return goodOrderingsHelper(a - 1, b, lead + 1) + goodOrderingsHelper(a , b - 1, lead - 1);
}

/*
 * This function starts counting good arrangements by placing the
 * first A, then calls the helper with the updated counts and lead.
 */
int countGoodOrderings(int a, int b) {
    int lead = 1;
    return goodOrderingsHelper(a - 1, b, lead);
}

/* * * * * * Test Cases * * * * * */

PROVIDED_TEST("countAllOrderings, two A one B") {
   EXPECT_EQUAL(countAllOrderings(2, 1), 3);
}

PROVIDED_TEST("countGoodOrderings, two A one B") {
   EXPECT_EQUAL(countGoodOrderings(2, 1), 1);
}

STUDENT_TEST("countAllOrderings, 4 A and 1 B") {
    EXPECT_EQUAL(countAllOrderings(4, 1), 5);
}

STUDENT_TEST("countAllOrderings, 10 A and 3 B") {
    EXPECT_EQUAL(countAllOrderings(10, 3), 286);
}

STUDENT_TEST("countAllOrderings, 3 A and 1 B") {
    EXPECT_EQUAL(countAllOrderings(3, 1), 4);
}

STUDENT_TEST("countGoodOrderings, 4 A and 1 B") {
    EXPECT_EQUAL(countGoodOrderings(4, 1), 3);
}

STUDENT_TEST("countGoodOrderings, 10 A and 3 B") {
    EXPECT_EQUAL(countGoodOrderings(10, 3), 154);
}

STUDENT_TEST("countGoodOrderings, 3 A and 1 B") {
    EXPECT_EQUAL(countGoodOrderings(3, 1), 2);
}

STUDENT_TEST("Bertrand's Theorem Test on functions") {
    for (int a = 1 ; a <= 15 ; a++) {
        for (int b = 1 ; b < a ; b++) {
            double test = double(countGoodOrderings(a,b)) / countAllOrderings(a,b);
            EXPECT_EQUAL(test, double((a-b))/(a+b));
        }
    }
}