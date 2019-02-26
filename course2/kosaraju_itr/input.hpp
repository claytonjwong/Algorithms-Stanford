/*

    input.txt

    The file contains the edges of a directed graph. Vertices are labeled as
    positive integers from 1 to 875714. Every row indicates an edge, the vertex
    label in first column is the tail and the vertex label in second column is
    the head (recall the graph is directed, and the edges are directed from the
    first column vertex to the second column vertex).

    So for example, the 11th row looks like: "2 47646". This just means that
    the vertex with label 2 has an outgoing edge to the vertex with label 47646.

    Your task is to code up the algorithm from the video lectures for computing
    strongly connected components (SCCs), and to run this algorithm on the given graph.

    Output Format: You should output the sizes of the 5 largest SCCs in the given graph,
    in decreasing order of sizes, separated by commas (avoid any spaces).
    So if your algorithm computes the sizes of the five largest SCCs to be
    500, 400, 300, 200 and 100, then your answer should be "500,400,300,200,100".
    If your algorithm finds less than 5 SCCs, then write 0 for the remaining terms.
    Thus, if your algorithm computes only 3 SCCs whose sizes are 400, 300, and 100,
    then your answer should be "400,300,100,0,0".

 */


#pragma once


#include <string>


//
// graph from figure 8.16, page 55 of Algorithms Illuminated: Part 2
//
const std::string TEST_CASE_0 =
R"(1 3
2 4
2 10
3 5
3 11
4 7
5 1
5 7
5 9
6 10
7 9
8 6
9 2
9 4
9 8
10 8
11 6
11 8
)";

//
// http://www.algorithmsilluminated.org/datasets/problem8.10test1.txt
//
const std::string TEST_CASE_1 =
R"(1 4
2 8
3 6
4 7
5 2
6 9
7 1
8 5
8 6
9 7
9 3
)";

//
// http://www.algorithmsilluminated.org/datasets/problem8.10test2.txt
//
const std::string TEST_CASE_2 =
R"(1 2
2 6
2 3
2 4
3 1
3 4
4 5
5 4
6 5
6 7
7 6
7 8
8 5
8 7
)";

//
// http://www.algorithmsilluminated.org/datasets/problem8.10test3.txt
//
const std::string TEST_CASE_3 =
R"(1 2
2 3
3 1
3 4
5 4
6 4
8 6
6 7
7 8
)";

//
// http://www.algorithmsilluminated.org/datasets/problem8.10test4.txt
//
const std::string TEST_CASE_4 =
R"(1 2
2 3
3 1
3 4
5 4
6 4
8 6
6 7
7 8
4 3
4 6
)";

//
// http://www.algorithmsilluminated.org/datasets/problem8.10test5.txt
//
const std::string TEST_CASE_5 =
R"(1 2
2 3
2 4
2 5
3 6
4 5
4 7
5 2
5 6
5 7
6 3
6 8
7 8
7 10
8 7
9 7
10 9
10 11
11 12
12 10
)";

const std::string TEST_CASE_6 =
R"(1 2
2 1
2 3
)";

const std::string TEST_CASE_7 =
R"(1 2
2 1
3 2
)";
