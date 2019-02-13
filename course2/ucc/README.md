# Undirected Connected Components ( BFS )
https://en.wikipedia.org/wiki/Connected_component_(graph_theory)

## Contents
* [Lecture Slides](#lecture-slides)
* [Solution](#solution)
* [Build Instructions](#build-instructions)
* [Dependencies](#dependencies)

## Lecture Slides
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course2/bfs/documentation/bfs_01.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course2/bfs/documentation/bfs_02.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course2/bfs/documentation/bfs_03.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course2/bfs/documentation/bfs_04.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course2/bfs/documentation/bfs_05.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course2/bfs/documentation/bfs_06.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course2/bfs/documentation/bfs_07.png)
---

## Solution
```cpp

    /**
     *
     * Modern C++ implementation of UCC algorithm to find the connected components in an undirected graph
     *
     * (c) Copyright 2019 Clayton J. Wong ( http://www.claytonjwong.com )
     *
     **/
    
    
    #include <iostream>
    #include <unordered_map>
    #include <unordered_set>
    #include <set>
    #include <vector>
    #include <queue>
    
    
    using namespace std;
    
    
    class Solution
    {
    public:
    
        using Vertex = unsigned int;
        using AdjacencyList = vector< Vertex >;
        using Graph = unordered_map< Vertex, AdjacencyList >;
        using Seen = unordered_set< Vertex >;
        using ConnectedComponents = vector< vector< Vertex > >;
        using Queue = queue< Vertex >;
    
        ConnectedComponents getUCC( Graph& G, ConnectedComponents CC={}, Seen seen={} )
        {
            for( auto& pair: G )
            {
                auto vertex{ pair.first };
                if( seen.insert( vertex ).second )
                {
                    CC.push_back( {} );             // make space for a new group of (C)onnected (C)omponents
                    for( Queue q{{ vertex }}; ! q.empty(); q.pop() )
                    {
                        auto cur{ q.front() };
                        CC.back().push_back( cur ); // (cur)rent vertex to be included as part of the last (C)onnected (C)omponent
                        for( auto adj: G[ cur ] )   // (adj)acent neighbor vertices of the (G)raph's (cur)rent vertex
                            if( seen.insert( adj ).second )
                                q.push( adj );
                    }
                }
            }
            return CC;
        }
    
    };
    
    int main()
    {
        //
        // graph from figure 8.8, page 35 of Algorithms Illuminated: Part 2
        //
        Solution::Graph G{
            { 1, { 3, 5 } },
            { 2, { 4 } },
            { 3, { 1, 5 } },
            { 4, { 2 } },
            { 5, { 1, 3, 7, 9 } },
            { 6, { 8, 10 } },
            { 7, { 5 } },
            { 8, { 6 } },
            { 9, { 5 } },
            { 10, { 6 } },
        };
        Solution s;
        auto ucc = s.getUCC( G );
    
        return 0;
    }

```

## Build Instructions
Use ```cmake``` to build this project:

```
    cmake --build cmake-build-debug --target ucc -- -j 4
```

## Dependencies
* [cmake.org](https://cmake.org)
