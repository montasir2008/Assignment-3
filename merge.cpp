/* Name: Montasir Mahir and Weijia Li
 * Course: CS106B
 * Section: Thu 7:30 pm
 * Description: This file merges sorted queues. It includes functions
 * for merging two queues and for merging many queues recursively.
 */
#include <iostream>    // for cout, endl
#include "queue.h"
#include "SimpleTest.h"
using namespace std;

/*
 * This function checks whether the values in q are sorted.
 * It calls error if it finds a value smaller than the one before it.
 */
void checkSorted(Queue<int> q) {
    if (q.isEmpty()) {
        return;
    }

    int previous = q.dequeue();
    while (!q.isEmpty()) {
        int current = q.dequeue();
        if (current < previous) {
            error("binaryMerge: input queue is not sorted.");
        }
        previous = current;
    }
}


/*
 * This function combines two sorted queues into one sorted queue.
 * It checks that both queues are sorted, then repeatedly adds the
 * smaller front value to the result.
 */
Queue<int> binaryMerge(Queue<int> a, Queue<int> b) {
    Queue<int> result;
    checkSorted(a);
    checkSorted(b);

    while (a.size() != 0 || b.size() != 0) {
        if (!b.size()) {
            result.enqueue(a.dequeue());
        }
        else if (!a.size()) {
            result.enqueue(b.dequeue());
        }
        else if (a.peek() <= b.peek()) {
            result.enqueue(a.dequeue());
        }
        else if (b.peek() <= a.peek()) {
            result.enqueue(b.dequeue());
        }

    }

    return result;
}

/*
 * The function naiveMultiMerge assumes you have a correctly working
 * binaryMerge function, which this function calls to iteratively
 * merge a collection of sequences, starting off with an empty sequence
 * and repeatedly merging in an additional sequence until all are merged.
 * The code below is provided to you is implemented correctly and you
 * should not need to modify it.
 */
Queue<int> naiveMultiMerge(Vector<Queue<int>>& all) {
    Queue<int> result;

    for (Queue<int>& q : all) {
        result = binaryMerge(q, result);
    }
    return result;
}

/*
 * This function combines all the queues in all into one sorted queue.
 * It splits the queues into two groups, recursively merges each group,
 * and then combines the two results.
 */
Queue<int> recMultiMerge(Vector<Queue<int>>& all) {
    if (all.isEmpty()) {
        return {};
    }
    if (all.size() == 1) {
        return all[0];
    }

    int mid = all.size() / 2;
    Vector<Queue<int>> left = all.subList(0, mid);
    Vector<Queue<int>> right = all.subList(mid);

    Queue<int> leftResult = recMultiMerge(left);
    Queue<int> rightResult = recMultiMerge(right);

    return binaryMerge(leftResult, rightResult);
}


/* * * * * * Test Cases * * * * * */

Queue<int> createSequence(int size);
void distribute(Queue<int> input, Vector<Queue<int>>& all);

PROVIDED_TEST("binaryMerge, two short sequences") {
    Queue<int> a = {2, 4, 5};
    Queue<int> b = {1, 3, 3};
    Queue<int> expected = {1, 2, 3, 3, 4, 5};
    EXPECT_EQUAL(binaryMerge(a, b), expected);
    EXPECT_EQUAL(binaryMerge(b, a), expected);
}

PROVIDED_TEST("naiveMultiMerge, small collection of short sequences") {
    Vector<Queue<int>> all = {{3, 6, 9, 9, 100},
                             {1, 5, 9, 9, 12},
                             {5},
                             {},
                             {-5, -5},
                             {3402}
                            };
    Queue<int> expected = {-5, -5, 1, 3, 5, 5, 6, 9, 9, 9, 9, 12, 100, 3402};
    EXPECT_EQUAL(naiveMultiMerge(all), expected);
}

PROVIDED_TEST("recMultiMerge, compare to naiveMultiMerge") {
    int n = 20;
    Queue<int> input = createSequence(n);
    Vector<Queue<int>> all(n);
    distribute(input, all);
    EXPECT_EQUAL(recMultiMerge(all), naiveMultiMerge(all));
}

PROVIDED_TEST("Time binaryMerge operation") {
    int n = 1000000;
    Queue<int> a = createSequence(n);
    Queue<int> b = createSequence(n);
    TIME_OPERATION(a.size() + b.size(), binaryMerge(a, b));
}

PROVIDED_TEST("Time naiveMultiMerge operation") {
    int n = 11000;
    int k = n/10;
    Queue<int> input = createSequence(n);
    Vector<Queue<int>> all(k);
    distribute(input, all);
    TIME_OPERATION(input.size(), naiveMultiMerge(all));
}
PROVIDED_TEST("Time recMultiMerge operation") {
    int n = 90000;
    int k = n/10;
    Queue<int> input = createSequence(n);
    Vector<Queue<int>> all(k);
    distribute(input, all);
    TIME_OPERATION(input.size(), recMultiMerge(all));
}


/* Test helper to fill queue with sorted sequence */
Queue<int> createSequence(int size) {
    Queue<int> q;
    for (int i = 0; i < size; i++) {
        q.enqueue(i);
    }
    return q;
}

/* Test helper to distribute elements of sorted sequence across k sequences,
   k is size of Vector */
void distribute(Queue<int> input, Vector<Queue<int>>& all) {
    while (!input.isEmpty()) {
        all[randomInteger(0, all.size()-1)].enqueue(input.dequeue());
    }
}

STUDENT_TEST("binaryMerge handles two empty queues") {
    Queue<int> empty;
    EXPECT_EQUAL(binaryMerge(empty, empty), empty);
}

STUDENT_TEST("binaryMerge handles one empty queue") {
    Queue<int> empty;
    Queue<int> values = {-4, 0, 8};

    EXPECT_EQUAL(binaryMerge(empty, values), values);
    EXPECT_EQUAL(binaryMerge(values, empty), values);
}

STUDENT_TEST("binaryMerge handles very uneven queue sizes") {
    Queue<int> longQueue = createSequence(1000);  // 0 through 999
    Queue<int> shortQueue = {1000, 1000};

    Queue<int> expected = createSequence(1000);
    expected.enqueue(1000);
    expected.enqueue(1000);

    EXPECT_EQUAL(binaryMerge(longQueue, shortQueue), expected);
}

STUDENT_TEST("binaryMerge accepts sorted queues") {
    Queue<int> a = {1, 4, 7};
    Queue<int> b = {2, 3, 8};
    Queue<int> expected = {1, 2, 3, 4, 7, 8};

    EXPECT_EQUAL(binaryMerge(a, b), expected);
}

STUDENT_TEST("binaryMerge errors when the first queue is unsorted") {
    Queue<int> a = {1, 5, 3};
    Queue<int> b = {2, 4, 6};

    EXPECT_ERROR(binaryMerge(a, b));
}

STUDENT_TEST("binaryMerge errors when the second queue is unsorted") {
    Queue<int> a = {1, 2, 5};
    Queue<int> b = {0, 4, 3};

    EXPECT_ERROR(binaryMerge(a, b));
}

STUDENT_TEST("Time binaryMerge at doubling sizes") {
    for (int n = 12500000; n <= 100000000; n *= 2) {
        Queue<int> a = createSequence(n);
        Queue<int> b = createSequence(n);

        TIME_OPERATION(a.size() + b.size(), binaryMerge(a, b));
    }
}

STUDENT_TEST("naiveMultiMerge handles no queues") {
    Vector<Queue<int>> all;
    Queue<int> expected;

    EXPECT_EQUAL(naiveMultiMerge(all), expected);
}

STUDENT_TEST("naiveMultiMerge handles only empty queues") {
    Vector<Queue<int>> all = {{}, {}, {}, {}};
    Queue<int> expected;

    EXPECT_EQUAL(naiveMultiMerge(all), expected);
}

STUDENT_TEST("naiveMultiMerge handles empty queues mixed with values") {
    Vector<Queue<int>> all = {{}, {1, 4}, {}, {2, 3}};
    Queue<int> expected = {1, 2, 3, 4};

    EXPECT_EQUAL(naiveMultiMerge(all), expected);
}

STUDENT_TEST("Time naiveMultiMerge as n grows") {
    int k = 10;
    for (int n = 100000; n <= 1600000; n *= 2) {
        Queue<int> input = createSequence(n);
        Vector<Queue<int>> all(k);
        distribute(input, all);

        TIME_OPERATION(n, naiveMultiMerge(all));
    }
}

STUDENT_TEST("Time naiveMultiMerge as k grows") {
    int n = 100000;
    for (int k = 10; k <= 160; k *= 2) {
        Queue<int> input = createSequence(n);
        Vector<Queue<int>> all(k);
        distribute(input, all);

        TIME_OPERATION(k, naiveMultiMerge(all));
    }
}

STUDENT_TEST("recMultiMerge handles no queues") {
    Vector<Queue<int>> all;
    EXPECT_EQUAL(recMultiMerge(all), naiveMultiMerge(all));
}

STUDENT_TEST("recMultiMerge handles one queue") {
    Vector<Queue<int>> all = {{1, 3, 5, 7}};
    EXPECT_EQUAL(recMultiMerge(all), naiveMultiMerge(all));
}

STUDENT_TEST("recMultiMerge handles odd numbers of queues, empties, and duplicates") {
    Vector<Queue<int>> all = {{}, {1, 3}, {2, 2}, {}, {0, 5}};
    EXPECT_EQUAL(recMultiMerge(all), naiveMultiMerge(all));
}

STUDENT_TEST("Time recMultiMerge as n grows") {
    int k = 10;
    for (int n = 100000; n <= 1600000; n *= 2) {
        Queue<int> input = createSequence(n);
        Vector<Queue<int>> all(k);
        distribute(input, all);

        TIME_OPERATION(n, recMultiMerge(all));
    }
}

STUDENT_TEST("Time recMultiMerge as k grows") {
    int n = 100000;
    for (int k = 1; k <= 256; k *= 4) {
        Queue<int> input = createSequence(n);
        Vector<Queue<int>> all(k);
        distribute(input, all);

        TIME_OPERATION(k, recMultiMerge(all));
    }
}