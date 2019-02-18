/*
    In this assignment you will implement one or more algorithms for the traveling salesman problem,
    such as the dynamic programming algorithm covered in the video lectures.
    Here is a data file describing a TSP instance.

    The first line indicates the number of cities. Each city is a point in the plane,
    and each subsequent line indicates the x- and y-coordinates of a single city.

    The distance between two cities is defined as the Euclidean distance ---
    that is, two cities at locations (x,y)(x,y) and (z,w)(z,w) have distance \sqrt{(x-z)^2 + (y-w)^2} between them.

    In the box below, type in the minimum cost of a traveling salesman tour for this instance,
    rounded down to the nearest integer.

    OPTIONAL: If you want bigger data sets to play with, check out the TSP instances
    from around the world here: http://www.math.uwaterloo.ca/tsp/world/countries.html.
    The smallest data set (Western Sahara) has 29 cities, and most of the data sets are much bigger than that.
    What's the largest of these data sets that you're able to solve
    using dynamic programming or, if you like, a completely different method?

    HINT: You might experiment with ways to reduce the data set size. For example, trying plotting the points.
    Can you infer any structure of the optimal solution? Can you use that structure to speed up your algorithm?
 */

#pragma once


#include <string>


namespace Assignment
{
    const std::string Input
    {
R"(
20833.3333 17100.0000
20900.0000 17066.6667
21300.0000 13016.6667
21600.0000 14150.0000
21600.0000 14966.6667
21600.0000 16500.0000
22183.3333 13133.3333
22583.3333 14300.0000
22683.3333 12716.6667
23616.6667 15866.6667
23700.0000 15933.3333
23883.3333 14533.3333
24166.6667 13250.0000
25149.1667 12365.8333
26133.3333 14500.0000
26150.0000 10550.0000
26283.3333 12766.6667
26433.3333 13433.3333
26550.0000 13850.0000
26733.3333 11683.3333
27026.1111 13051.9444
27096.1111 13415.8333
27153.6111 13203.3333
27166.6667 9833.3333
27233.3333 10450.0000
)"
    }; // const std::string Input

} // namespace Assignment
