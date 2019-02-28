# Kosaraju ( DFS + DFS - Iterative )
https://en.wikipedia.org/wiki/Kosaraju%27s_algorithm

## Contents
* [Lecture Slides](#lecture-slides)
* [Solution](#solution)
* [Build Instructions](#build-instructions)
* [Dependencies](#dependencies)

## Lecture Slides
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course2/kosaraju_itr/documentation/scc_01.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course2/kosaraju_itr/documentation/scc_02.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course2/kosaraju_itr/documentation/scc_03.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course2/kosaraju_itr/documentation/scc_04.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course2/kosaraju_itr/documentation/scc_05.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course2/kosaraju_itr/documentation/scc_06.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course2/kosaraju_itr/documentation/scc_07.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course2/kosaraju_itr/documentation/scc_08.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course2/kosaraju_itr/documentation/scc_09.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course2/kosaraju_itr/documentation/scc_10.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course2/kosaraju_itr/documentation/scc_11.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course2/kosaraju_itr/documentation/scc_12.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course2/kosaraju_itr/documentation/scc_13.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course2/kosaraju_itr/documentation/scc_14.png)
---

## Solution
```cpp

    /**
     *
     * Modern C++ implementation of Koraraju's algorithm to find the strongly connected components of a directed graph
     *
     * (c) Copyright 2019 Clayton J. Wong ( http://www.claytonjwong.com )
     *
     **/
    
    
    #include "input.hpp"
    #include <iostream>
    #include <unordered_map>
    #include <unordered_set>
    #include <set>
    #include <vector>
    #include <queue>
    #include <sstream>
    #include <fstream>
    
    
    //#define UNIT_TESTS 69 // comment this line to execute the large homework assignment instead of small unit tests
    
    
    using namespace std;
    
    
    class Solution
    {
    public:
    
        using Vertex = size_t;
        using AdjacencyList = unordered_set< Vertex >;
        using Graph = unordered_map< Vertex, AdjacencyList >;
        using Seen = unordered_set< Vertex >;
        using ConnectedComponents = vector< vector< Vertex > >;
        using OrderedList = deque< Vertex >;
        using Stack = vector< Vertex >;
    
        ConnectedComponents getSCC( Graph& G, ConnectedComponents CC={}, Stack stack={}, Seen seen={} )
        {
            auto L = topo_sort( reverse( G ) );
            for( auto cur: L )
            {
                if( seen.insert( cur ).second )
                    stack.push_back( cur );         // push unseen (cur)rent vertex onto the stack
                Stack path;
                while( ! stack.empty() )
                {
                    auto start{ stack.back() }; stack.pop_back(); path.push_back( start );
                    for( auto adj: G[ start ] )
                        if( seen.insert( adj ).second )
                            stack.push_back( adj ); // push unseen (adj)acent vertex onto the stack
                }
                if( ! path.empty() )
                    CC.emplace_back( path );
            }
            return CC;
        }
    
    private:
    
        Graph reverse( Graph& G )
        {
            Graph R;
            for( auto& pair: G )
            {
                auto u{ pair.first };
                for( auto v: G[ u ] )   // u -> v
                {
                    if( R.find( v ) == R.end() )
                        R[ v ] = {};
                    R[ v ].insert( u ); // v -> u
                }
            }
            return R;
        }
    
        OrderedList topo_sort( Graph&& G, Stack stack={}, Seen seen={} )
        {
            OrderedList L;
            for( auto& pair: G )
            {
                auto cur{ pair.first };
                if( seen.insert( cur ).second )
                    stack.push_back( cur );         // push unseen (cur)rent vertex onto the stack
                Stack path;
                while( ! stack.empty() )
                {
                    auto start{ stack.back() }; stack.pop_back(); path.push_back( start );
                    for( auto adj: G[ start ] )
                        if( seen.insert( adj ).second )
                            stack.push_back( adj ); // push unseen (adj)acent vertex onto the stack
                }
                for(; ! path.empty(); L.push_front( path.back() ), path.pop_back() );
            }
            return L;
        }
    
    };
    
    #ifdef UNIT_TESTS
    int main()
    {
        Solution s;
        Solution::Graph G;
        for( auto& test: { TEST_CASE_0, TEST_CASE_1, TEST_CASE_2, TEST_CASE_3, TEST_CASE_4, TEST_CASE_5, TEST_CASE_6, TEST_CASE_7 } )
        {
            G.clear();
            auto tail{ 0 }, head{ 0 };
            stringstream input{ test };
            for( string line; getline( input, line ); G[ tail ].insert( head ) )
            {
                stringstream parser{ line }; parser >> tail >> head;
                if( G.find( tail ) == G.end() )
                    G[ tail ] = {};
            }
            auto CC = s.getSCC( G );
            auto index{ 0 };
            for( auto& component: CC )
            {
                cout << index++ << ": ";
                for( auto& vertex: component )
                    cout << vertex << " ";
                cout << endl;
            }
            cout << endl;
        }
    
        return 0;
    }
    #else
    
    void print_answer( Solution::ConnectedComponents& CC, ostringstream stream=ostringstream() )
    {
        set< size_t, greater<int> > sizes;
        for( auto& C: CC )
            sizes.insert( C.size() );
        cout << "answer: ";
        auto N{ 5 };
        for( auto it{ sizes.begin() }; N--; ++it )
            cout << *it << ",";
        cout << endl;
    }
    
    int main()
    {
        Solution::Graph G;
        fstream stream{ "input.txt" }; // this file was too big to upload to github, so it is compressed as "input.txt.zip"
        for( string line; getline( stream, line ); )
        {
            stringstream parser{ line };
            auto tail{ 0 }, head{ 0 };
            parser >> tail >> head;
            if( G.find( tail ) == G.end() )
                G[ tail ] = {};
            G[ tail ].insert( head );
        }
        Solution s;
        auto CC = s.getSCC( G );
        print_answer( CC );
    
        // answer: 434821,968,459,313,211
    
        return 0;
    }
    #endif

```

## Build Instructions
Use ```cmake``` to build this project:

```
    cmake --build cmake-build-debug --target kosaraju_itr -- -j 4
```

## Dependencies
* [cmake.org](https://cmake.org)
