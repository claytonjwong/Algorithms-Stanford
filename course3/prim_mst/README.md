# Prim
https://en.wikipedia.org/wiki/Prim%27s_algorithm

## Contents
* [Lecture Slides](#lecture-slides)
* [Solution](#solution)
* [Build Instructions](#build-instructions)
* [Dependencies](#dependencies)

## Lecture Slides
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course3/prim_mst/documentation/prim_01.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course3/prim_mst/documentation/prim_02.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course3/prim_mst/documentation/prim_03.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course3/prim_mst/documentation/prim_04.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course3/prim_mst/documentation/prim_05.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course3/prim_mst/documentation/prim_06.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course3/prim_mst/documentation/prim_07.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course3/prim_mst/documentation/prim_08.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course3/prim_mst/documentation/prim_09.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course3/prim_mst/documentation/prim_10.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course3/prim_mst/documentation/prim_11.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course3/prim_mst/documentation/prim_12.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course3/prim_mst/documentation/prim_13.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course3/prim_mst/documentation/prim_14.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course3/prim_mst/documentation/prim_15.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course3/prim_mst/documentation/prim_16.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course3/prim_mst/documentation/prim_17.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course3/prim_mst/documentation/prim_18.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course3/prim_mst/documentation/prim_19.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course3/prim_mst/documentation/prim_20.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course3/prim_mst/documentation/prim_21.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course3/prim_mst/documentation/prim_22.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course3/prim_mst/documentation/prim_23.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course3/prim_mst/documentation/prim_24.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course3/prim_mst/documentation/prim_25.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course3/prim_mst/documentation/prim_26.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course3/prim_mst/documentation/prim_27.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course3/prim_mst/documentation/prim_28.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course3/prim_mst/documentation/prim_29.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course3/prim_mst/documentation/prim_30.png)
---

## Solution
```cpp

    /**
     *
     * Modern C++ implementation of Prim's minimum spanning tree algorithm
     *
     * (c) Copyright 2019 Clayton J. Wong ( http://www.claytonjwong.com )
     *
     **/
    
    
    #include "input.hpp"
    #include <iostream>
    #include <sstream>
    #include <unordered_set>
    #include <unordered_map>
    #include <map>
    #include <set>
    
    
    using namespace std;
    
    
    template< typename Type >
    class Solution
    {
    public:
    
        using Vertex = Type;
        using Cost = Type;
        struct Edge
        {
            Vertex tail{ 0 }, head{ 0 };
            bool operator==( const Edge& rhs ) const { return tail == rhs.tail && head == rhs.head; }
        };
        struct Hash{ size_t operator()( const Edge& e ) const { return e.tail << 16 + e.head; } };
        using Edges = unordered_map< Edge, Cost, Hash >;
        using AdjacencyList = unordered_set< Vertex >;
        using Graph = unordered_map< Vertex, AdjacencyList >;
        using Tree = unordered_set< Vertex >;
        using EdgeCost = pair< Edge, Cost >;
    
        Type costMST( Graph& G, Edges& E, Vertex start, Type cost=0 )
        {
            auto Compare = []( const EdgeCost& lhs, const EdgeCost& rhs ){ return lhs.second < rhs.second; };
            set< EdgeCost, decltype( Compare )> edges( {}, Compare );
            for( Tree tree{ start }; tree.size() < G.size(); edges.clear() )
            {
                for( auto vertex{ tree.begin() }; vertex != tree.end(); ++vertex ) for( auto& adj: G[ *vertex ] ) // each vertex (adj)acent to each tree vertex -- O( |V|^2 )
                {
                    auto edgeCost = E.find({ *vertex, adj });
                    if( edgeCost != E.end() && tree.find( adj ) == tree.end() ) // edge exists, and (adj)acent vertex is not part of the tree
                        edges.insert({ edgeCost->first, edgeCost->second });
                }
                auto min = edges.begin();
                auto minEdge = min->first;
                auto minCost = min->second;
                auto cur{ minEdge.tail }, // (cur)rrent tail vertex already included in the MST
                     adj{ minEdge.head }; // (adj)acent head vertex to be included in the MST
                tree.insert( adj );
                cost += minCost;
            }
            return cost;
        }
    
    };
    
    
    int main()
    {
        using Type = int;
        Solution< Type > s;
        for( auto& input: { Lecture::Input, Assignment::Input } ) // assume input graph is undirected and connected
        {
            Solution< Type >::Graph G;
            Solution< Type >::Edges E;
            istringstream stream{ input };
            for( string line; getline( stream, line ); )
            {
                stringstream parser{ line };
                Type u{ 0 }, v{ 0 }, cost{ 0 };
                parser >> u >> v >> cost;
                if( G.find( u ) == G.end() ) G[ u ] = {};
                if( G.find( v ) == G.end() ) G[ v ] = {};
                G[ u ].insert( v );
                G[ v ].insert( u );
                E.insert({ {u,v}, cost });
                E.insert({ {v,u}, cost });
            }
            auto start{ G.begin()->first }; // arbitrary start vertex is irrelevant
            auto answer = s.costMST( G, E, start );
            cout << "answer: " << answer << endl << endl;
        }
    
    //    answer: 7
    
    //    answer: -3612829
    
        return 0;
    }

```

## Build Instructions
Use ```cmake``` to build this project:

```
    cmake --build cmake-build-debug --target prim_mst -- -j 4
```

## Dependencies
* [cmake.org](https://cmake.org)
