# Karger Minimum Cut ( Randomized Edge Contractions )
https://en.wikipedia.org/wiki/Karger%27s_algorithm

## Contents
* [Lecture](#lecture)
* [Lecture Slides](#lecture-slides)
* [Solution](#solution)
* [Build Instructions](#build-instructions)
* [Dependencies](#dependencies)

# Lecture
* [Video](https://www.coursera.org/lecture/algorithms-divide-conquer/random-contraction-algorithm-FKAnq)

## Lecture Slides
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course1/karger_min_cut/documentation/karger_01.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course1/karger_min_cut/documentation/karger_02.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course1/karger_min_cut/documentation/karger_03.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course1/karger_min_cut/documentation/karger_04.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course1/karger_min_cut/documentation/karger_05.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course1/karger_min_cut/documentation/karger_06.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course1/karger_min_cut/documentation/karger_07.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course1/karger_min_cut/documentation/karger_08.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course1/karger_min_cut/documentation/karger_09.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course1/karger_min_cut/documentation/karger_10.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course1/karger_min_cut/documentation/karger_11.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course1/karger_min_cut/documentation/karger_12.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course1/karger_min_cut/documentation/karger_13.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course1/karger_min_cut/documentation/karger_14.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course1/karger_min_cut/documentation/karger_15.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course1/karger_min_cut/documentation/karger_16.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course1/karger_min_cut/documentation/karger_17.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course1/karger_min_cut/documentation/karger_18.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course1/karger_min_cut/documentation/karger_19.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course1/karger_min_cut/documentation/karger_20.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course1/karger_min_cut/documentation/karger_21.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course1/karger_min_cut/documentation/karger_22.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course1/karger_min_cut/documentation/karger_23.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course1/karger_min_cut/documentation/karger_24.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course1/karger_min_cut/documentation/karger_25.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course1/karger_min_cut/documentation/karger_26.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course1/karger_min_cut/documentation/karger_27.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course1/karger_min_cut/documentation/karger_28.png)
---

## Solution
```cpp

    /**
     *
     * Modern C++ implementation of Karger's algorithm to find the minimum cut in a graph
     *
     * (c) Copyright 2019 Clayton J. Wong ( http://www.claytonjwong.com )
     *
     **/
    
    
    #include "input.hpp"
    #include <iostream>
    #include <vector>
    #include <set>
    #include <map>
    #include <unordered_map>
    #include <random>
    #include <sstream>
    
    
    using namespace std;
    
    
    class Solution
    {
    public:
    
        using Vertex = int;
        using AdjacencyList = multiset< Vertex >;
        using Graph = unordered_map< Vertex, AdjacencyList >;
        struct Edge{ Vertex tail{ 0 }, head{ 0 }; };
    
        int getMinCut( Graph G ) // assume (G)raph is connected undirected with at least one edge and two vertices
        {
            for( Edge edge; G.size() > 2; contractEdge( G, edge ) )
                edge = randomEdge( G );
            return G.cbegin()->second.size();
        }
    
    private:
    
        using RandomDevice = random_device;
        using Generator = mt19937;
        using Distribution = uniform_int_distribution< int >;
    
        int randomVertex( Vertex begin, Vertex end, RandomDevice randomDevice=RandomDevice() )
        {
            Generator generator{ randomDevice() };
            Distribution distribution{ begin, end-1 }; // end-1, since end is non-inclusive
            return distribution( generator );
        }
    
        Edge randomEdge( Graph& G )
        {
            auto N = static_cast< Vertex >( G.size() ),
                 tail = next( G.cbegin(), randomVertex( 0, N ) )->first;
            auto M = static_cast< Vertex >( G[ tail ].size() ),
                 head = *next( G[ tail ].cbegin(), randomVertex( 0, M ) );
            return { tail, head };
        }
    
        void contractEdge( Graph& G, const Edge& edge )
        {
            auto head{ edge.head }, tail{ edge.tail };
            for( auto& adj: G[ tail ] )
            {
                if( adj == head )
                    continue; // avoid adding self-loop when coalescing tail's adj(acent) vertices into head
                G[ head ].insert( adj );
                G[ adj ].insert( head );
                G[ adj ].erase( tail );
            }
            G[ head ].erase( tail );
            G.erase( tail );
        }
    
    };
    
    
    int main()
    {
        Solution s;
        Solution::Graph G;
        stringstream stream{ Assignment::Input };
        for( string line; getline( stream, line ); )
        {
            stringstream parser{ line };
            auto vertex{ 0 };
            parser >> vertex;
            if( G.find( vertex ) == G.end() )
                G[ vertex ] = {};
            for( auto adj{ 0 }; parser >> adj; )
            {
                if( G.find( adj ) == G.end() )
                    G[ adj ] = {};
                if( G[ adj ].find( vertex ) == G[ adj ].end() ) // only insert each unique vertex once
                    G[ adj ].insert( vertex );
                if( G[ vertex ].find( adj ) == G[ vertex ].end() ) // only insert each unique (adj)acent vertex once
                    G[ vertex ].insert( adj );
            }
        }
    
        auto minCut = numeric_limits< int >::max();
        for( auto N{ 100 }; N--; minCut = min( minCut, s.getMinCut( G ) ) );
        cout << "minCut: " << minCut << endl;
    
        return 0;
    }

```

## Build Instructions
Use ```cmake``` to build this project:

```
    cmake --build cmake-build-debug --target karger_min_cut -- -j 4
```

## Dependencies
* [cmake.org](https://cmake.org)
