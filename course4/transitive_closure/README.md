# Floyd Warshall ( Transitive Closure )
https://en.wikipedia.org/wiki/Floyd%E2%80%93Warshall_algorithm

## Contents
* [Lecture](#lecture)
* [Lecture Slides](#lecture-slides)
* [Solution](#solution)
* [Build Instructions](#build-instructions)
* [Dependencies](#dependencies)

# Lecture
* [Video](https://www.coursera.org/lecture/algorithms-npcomplete/the-floyd-warshall-algorithm-WKb60)

## Lecture Slides
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course4/floyd_warshall/documentation/floyd_01.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course4/floyd_warshall/documentation/floyd_02.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course4/floyd_warshall/documentation/floyd_03.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course4/floyd_warshall/documentation/floyd_04.png)
---

## Solution
```cpp

    /**
     *
     * Modern C++ implementation of Floyd Warshall's algorithm to find the transitive closures in a graph
     *
     * (c) Copyright 2019 Clayton J. Wong ( http://www.claytonjwong.com )
     *
     **/
    
    
    #include <iostream>
    #include <fstream>
    #include <sstream>
    #include <vector>
    #include <string>
    #include <unordered_map>
    #include <unordered_set>
    #include <bitset>
    
    
    using namespace std;
    using namespace std::chrono;
    using InputFiles = vector< string >;
    //
    // Assignment Input
    //
    const auto N{ 1000 };
    const InputFiles inputFiles{ "g1.txt", "g2.txt", "g3.txt" };
    //
    // Optional Challenge Input
    //
    //const auto N{ 20000 };
    //const InputFiles inputFiles{ "large.txt" };
    using Integer = long long;
    using Vertex = Integer;
    using Cost = Integer;
    using VI = bitset< N >;
    using VVI = vector< VI >;
    struct Edge
    {
        Vertex u{ 0 }, v{ 0 };
        bool operator==( const Edge& rhs ) const { return u == rhs.u && v == rhs.v; }
    };
    struct Hash{ Cost operator()( const Edge& e ) const { return ( N+1 ) * e.u + e.v; } };
    using Edges = unordered_map< Edge, Cost, Hash >;
    using Answer = pair< VVI, bool >;
    
    
    Edges readInput( const string& filename, Edges edges={} )
    {
        fstream stream{ filename };
        for( string line; getline( stream, line ); )
        {
            stringstream parser{ line };
            Vertex i,j; Cost cost;
            parser >> i >> j >> cost;
            Edge edge{ i,j };
            edges.insert({ edge, cost }); // i -> j
        }
        return edges;
    }
    
    
    class Solution
    {
    public:
    
        VVI getPaths( Edges& E )
        {
            VVI cur( N+1, false ), next( cur );
            for( auto i{ 1 }; i <= N; ++i ) for( auto j{ 1 }; j <= N; ++j ) // for each i,j: base cases for k == 1 ( k is non-inclusive, so Vertex 1 is NOT considered here )
                {
                    Edge edge{ i,j };
                    auto it = E.find( edge );
                    auto hasEdge = ( it != E.end() );
                    cur[ i ][ j ] = ( i == j )? true : hasEdge;
                }
            for( auto k{ 2 }; k <= N; ++k, swap( cur, next ) ) for( auto i{ 2 }; i <= N; ++i ) for( auto j{ 2 }; j <= N; ++j ) // for each i,j,k
            {
                // Note: let (1...k-1) denote a path which is only comprised of candidate vertices [1:k-1], that is 1 inclusive to k-1 inclusive
                //       this does NOT mean that all of these candidate vertices are included in this path, but these vertices are the only candidates
                //       which may potentially be included in the path ( this is a fundamental concept of this algorithm to create overlapping subproblems! )
                bool pre = cur[ i ][ j ], // (pre)vious existence of path i -> (1...k-1) -> j  ( without k )
                      ik = cur[ i ][ k ], // existence of path i -> (1...k-1) -> k
                      kj = cur[ k ][ j ], // existence of path k -> (1...k-1) -> j
                     alt = ( ik & kj );    // (alt)ernative existence of path i -> (1...k-1) -> k -> (1...k-1) -> j
                next[ i ][ j ] = ( pre | alt );
            }
            return next;
        }
    
    }; // class Solution
    
    
    void test( const string& inputFile, ostringstream outStream=ostringstream{} )
    {
        Solution solution;
        auto E = readInput( inputFile );
        auto A = solution.getPaths( E );
        size_t count{ 0 };
        for( auto i{ 1 }; i <= N; ++i )
            for( auto j{ 1 }; j <= N; ++j )
                if( A[ i ][ j ] )
                    ++count;
        cout << inputFile << " contains " << count << " transitive closures" << endl;
    }
    
    
    int main()
    {
        for( auto& inputFile: inputFiles )
            test( inputFile );
    
    //    g1.txt contains 998090 transitive closures
    //    g2.txt contains 998108 transitive closures
    //    g3.txt contains 998114 transitive closures
    
        return 0;
    }

```

## Build Instructions
Use ```cmake``` to build this project:

```
    cmake --build cmake-build-debug --target transitive_closure -- -j 4
```

## Dependencies
* [cmake.org](https://cmake.org)
