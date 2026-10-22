/* Name: Montasir Mahir and Weijia Li
 * Course: CS106B
 * Section: Thu 7:30 pm
 * Description: This file finds brackets in a string and checks
 * whether they are matched correctly.
 */
#include <iostream>    // for cout, endl
#include <string>      // for string class
#include "recursion.h"
#include "SimpleTest.h"

using namespace std;

/*
 * This function returns only the bracket characters from str.
 * It checks the first character, then recursively processes the rest.
 */
string operatorsFrom(string str) {
    if (str.empty()) {
        return "";
    }

    string rest = operatorsFrom(str.substr(1));
    char first = str[0];

    if (first == '{' || first == '[' || first == '(' ||
        first == '}' || first == ']' || first == ')') {
        return first + rest;
    }
    return rest;
}

/*
 * This function checks whether all brackets in ops are matched
 * It removes a matching pair and recursively checks the remaining
 * brackets. It returns false if no matching pair can be found
 */
bool operatorsAreMatched(string ops) {
    if (ops.empty()) {
        return true;
    }

    Vector<string> brackets = {"[]", "{}", "()"};

    for (string pair : brackets) {
        int b = stringIndexOf(ops, pair);
        if (b > -1) {
            ops.erase(b, 2);  // Remove this exact opening/closing pair
            return operatorsAreMatched(ops);
        }
    }

    return false;
}

/*
 * The isBalanced function assumes correct implementation of
 * the above two functions operatorsFrom and operatorsMatch.
 * It uses operatorsFrom to extract the operator characters
 * from the input string and then confirms that those
 * operators are balanced by using operatorsMatch.
 * You should not modify the provided code in the isBalanced
 * function.  If the previous two functions have been implemented
 * correctly, the provided isBalanced will correctly report whether
 * the input string has balanced bracketing operators.
 */
bool isBalanced(string str) {
    string ops = operatorsFrom(str);
    return operatorsAreMatched(ops);
}


/* * * * * * Test Cases * * * * * */

PROVIDED_TEST("operatorsFrom on simple example") {
    EXPECT_EQUAL(operatorsFrom("vec[3]"), "[]");
}

PROVIDED_TEST("operatorsAreMatched on simple example") {
    EXPECT(operatorsAreMatched("{}"));
}

PROVIDED_TEST("isBalanced on example from writeup") {
    string example ="int main() { int x = 2 * (vec[2] + 3); x = (1 + random()); }";
    EXPECT(isBalanced(example));
}

PROVIDED_TEST("isBalanced on non-balanced examples from writeup") {
    EXPECT(!isBalanced("( ( [ a ] )"));
    EXPECT(!isBalanced("3 ) ("));
    EXPECT(!isBalanced("{ ( x } y )"));
}

STUDENT_TEST("operatorsFrom extracts brackets from random text") {
    EXPECT_EQUAL(
        operatorsFrom("zebra (42) wandered past [seven sleepy robots] near {the old clock}!"),
        "()[]{}"
        );
}

STUDENT_TEST("operatorsFrom keeps brackets in order") {
    EXPECT_EQUAL(
        operatorsFrom("alpha {beta [gamma (delta) epsilon] zeta} and then [42 more words]"),
        "{[()]}[]"
        );
}

STUDENT_TEST("operatorsFrom ignores other punctuation") {
    EXPECT_EQUAL(
        operatorsFrom("R7 (clouds) drifted {above [old, blue] towers}, while foxes (sleep) nearby."),
        "(){[]}()"
        );
}

STUDENT_TEST("operatorsAreMatched handles nested mixed brackets") {
    EXPECT(operatorsAreMatched("[(){}]"));
}

STUDENT_TEST("operatorsAreMatched handles adjacent pairs") {
    EXPECT(operatorsAreMatched("()[]{}"));
}

STUDENT_TEST("operatorsAreMatched rejects mismatched nesting") {
    EXPECT(!operatorsAreMatched("([)]"));
    EXPECT(!operatorsAreMatched("{[(])}"));
}

STUDENT_TEST("operatorsAreMatched handles empty and unpaired brackets") {
    EXPECT(operatorsAreMatched(""));
    EXPECT(!operatorsAreMatched("["));
    EXPECT(!operatorsAreMatched("())"));
}