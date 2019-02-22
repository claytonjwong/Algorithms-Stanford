# Travelling Salesman ( nearest neighbor )
* [Wikipedia.org: Travelling Salesman Problem](https://en.wikipedia.org/wiki/Travelling_salesman_problem)
* [Wikipedia.org: Nearest neighbor algorithm](https://en.wikipedia.org/wiki/Nearest_neighbour_algorithm)

## Contents
* [Lecture](#lecture)
* [Lecture Slides](#lecture-slides)
* [Solution](#solution)
* [Build Instructions](#build-instructions)
* [Dependencies](#dependencies)

## Lecture
[Video](https://www.coursera.org/lecture/algorithms-npcomplete/the-traveling-salesman-problem-49MkW)

## Lecture Slides
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course4/travelling_salesman/documentation/tsp_01.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course4/travelling_salesman/documentation/tsp_02.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course4/travelling_salesman/documentation/tsp_03.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course4/travelling_salesman/documentation/tsp_04.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course4/travelling_salesman/documentation/tsp_05.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course4/travelling_salesman/documentation/tsp_06.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course4/travelling_salesman/documentation/tsp_07.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course4/travelling_salesman/documentation/tsp_08.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course4/travelling_salesman/documentation/tsp_09.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course4/travelling_salesman/documentation/tsp_10.png)
---


## Solution
```cpp

    /**
     *
     * Modern C++ implementation of greedy heuristic nearest neighbor algorithm for the travelling salesman problem
     * to approximate a min tour in O(N^2) time
     *
     * Note: a tour is a path which traverses each vertex exactly once, starting and finishing at a specific vertex
     *
     * (c) Copyright 2019 Clayton J. Wong ( http://www.claytonjwong.com )
     *
     **/
    
    
    #include "input.hpp"
    #include <iostream>
    #include <sstream>
    #include <vector>
    #include <iomanip>
    #include <cmath>
    #include <unordered_set>
    
    
    #define SMALL_INPUT 69
    
    
    #ifdef SMALL_INPUT
    
        //
        // previous TSP assignment input contains 25 cities
        //
        // optimal solution:      26442
        // sub-optimal solution:  32981
        //
        constexpr auto N{ 25 };
    
    #else
    
        constexpr auto N{ 33708 }; // assignment input contains 33708 cities
    
    #endif
    
    
    using namespace std;
    using RealNum = double;
    constexpr auto INF = numeric_limits< RealNum >::max();
    using VR = vector< RealNum >;
    using VVR = vector< VR >;
    using Cost = VVR;
    struct City{ RealNum x{ 0 }, y{ 0 }; };
    ostream& operator<<( ostream& os, const City& c )
    {
        os << fixed << setprecision( 4 ) << "{" << c.x << "," << c.y << "}";
        return os;
    }
    using CityList = vector< City >;
    using Pool = vector< int >;
    using Seen = unordered_set< int >;
    using Tour = vector< int >;
    
    
    CityList readInput( const string& input, CityList C={} )
    {
        istringstream stream{ input };
        for( string line; getline( stream, line ); )
        {
            istringstream parser{ line };
    
    #ifdef SMALL_INPUT
    
            for( RealNum x{ 0 }, y{ 0 }; parser >> x >> y; C.push_back({ x,y }) );
    
    #else
    
            auto id{ 0 };
            for( RealNum x{ 0 }, y{ 0 }; parser >> id >> x >> y; C.push_back({ x,y }) );
    
    #endif
    
        }
        assert( N == C.size() );
        return C;
    }
    
    Cost getCosts( CityList& C )
    {
        Cost cost = VVR( N, VR( N, 0 ) );
        for( auto i{ 0 }; i < N; ++i ) for( auto j{ 0 }; j < N; ++j ) // euclidean distance for each i,j pair of (C)ities
        {
            auto x = ( C[ i ].x - C[ j ].x ),
                 y = ( C[ i ].y - C[ j ].y );
            cost[ i ][ j ] = ( x * x ) + ( y * y );
        }
        return cost;
    }
    
    
    class Solution
    {
    public:
    
        RealNum minTour( Cost& D, Pool pool={}, RealNum minCost=0 )
        {
            auto cur{ 0 }; // 0-based index of (cur)rent city
            Seen seen{ cur };
            for( auto i{ cur }; i < N; pool.push_back( i++ ) ); // include cur since (alt)ernative candidate indices are offset from cur
            for( auto next{ 0 }; seen.size() < pool.size(); swap( cur, next ) )
            {
                auto nextCost{ INF };
                for( auto alt{ 1 }; alt < N; ++alt )
                {
                    if( seen.find( alt ) != seen.end() )
                        continue;
                    auto cost = D[ cur ][ alt ]; // find min cost of unseen (alt)ernative next candidate index
                    if( nextCost > cost )
                        nextCost = cost,
                        next = alt;
                }
                minCost += sqrt( nextCost );
                seen.insert( next );
            }
            return minCost + sqrt( D[ cur ][ 0 ] ); // complete tour by returning to the first city
        }
    
    }; // class Solution
    
    
    int main()
    {
    
    #ifdef SMALL_INPUT
    
        auto city = readInput( Small::Input );
    
    #else
    
        auto city = readInput( Assignment::Input );
    
    #endif
    
        Solution solution;
        auto cost = getCosts( city );
        auto ans = solution.minTour( cost );
    
        cout << "answer: " << static_cast< int >( ans ) << endl;
    
        // answer: 1203406
    
        return 0;
    }

```

## Build Instructions
Use ```cmake``` to build this project:

```
    cmake --build cmake-build-debug --target travelling_salesman_nn -- -j 4
```

## Dependencies
* [cmake.org](https://cmake.org)
