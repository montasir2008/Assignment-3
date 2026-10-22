/* Name: Montasir Mahir and Weijia Li
 * Course: CS106B
 * Section: Thu 7:30 pm
 * Description: This file draws Sierpinski triangles using recursion.
 * It draws smaller black triangles and returns how many were drawn. Very nice simulation.
 */
#include <iostream>    // for cout, endl
#include "recursion.h"
#include "SimpleTest.h"
using namespace std;

/*
 * This function draws a filled, black triangle on the provided GWindow
 * that is defined by the corner GPoints one, two, and three. This
 * function has been provided for you and does not need to be modified.
 */
void fillBlackTriangle(GWindow& window, GPoint one, GPoint two, GPoint three) {
    window.setColor("black");
    window.fillPolygon( {one, two, three} );
}

/* This function draws a Sierpinski triangle at the given order.
 * At order 0, it draws one black triangle and returns 1.
 * For higher orders, it finds the side midpoints and draws the
 * three smaller corner triangles. It returns their total count.
 */
int drawSierpinskiTriangle(GWindow& window, GPoint one, GPoint two, GPoint three, int order) {
    if (order == 0) {
        fillBlackTriangle(window, one, two, three);
        return 1;
    }

    GPoint midpoint1((one.x + two.x)/2, (one.y + two.y)/2);
    GPoint midpoint2((two.x + three.x)/2, (two.y + three.y)/2);
    GPoint midpoint3((one.x + three.x)/2, (one.y + three.y)/2);

    return drawSierpinskiTriangle(window, one, midpoint1, midpoint3, order - 1) + drawSierpinskiTriangle(window, two, midpoint1, midpoint2, order - 1) + drawSierpinskiTriangle(window, three, midpoint3, midpoint2, order - 1);
}


/* * * * * * Test Cases * * * * * */

/*
 * Do not modify the code beyond this line! There are no
 * unit tests for this problem. You should do all your testing
 * via the interactive demo.
 */

PROVIDED_TEST("Test fractal drawing interactively using graphical demo") {
    runInteractiveDemo();
}

