# Breadth First Search
https://en.wikipedia.org/wiki/Breadth-first_search

## Contents
* [Lecture Slides](#lecture-slides)
* [Solution](#solution)
* [Build Instructions](#build-instructions)
* [Dependencies](#dependencies)

##Lecture Slides
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
     * Modern C++ implementation of Breadth First Search algorithm on a graph
     *
     * (c) Copyright 2019 Clayton J. Wong ( http://www.claytonjwong.com )
     *
     **/
    
    
    #include <iostream>
    #include <vector>
    #include <unordered_set>
    #include <unordered_map>
    #include <queue>
    
    
    using namespace std;
    
    
    class Solution
    {
    public:
    
        using Vertex = unsigned char;
        using AdjacencyList = vector< Vertex >;
        using Graph = unordered_map< Vertex, AdjacencyList >;
        using Seen = unordered_set< Vertex >;
        using Queue = queue< Vertex >;
    
        Seen bfs( Graph& G, Vertex start='s' )
        {
            Queue q{{ start }};
            Seen seen{ start };
            while( ! q.empty() )
            {
                auto cur{ q.front() }; q.pop();     // (cur)rent front of the (q)ueue
                for( auto adj: G[ cur ] )           // (adj)acent neighbor vertices of the (G)raph's (cur)rent vertex
                    if( seen.insert( adj ).second ) // if this is the first time the (adj)acent neighbor vertex has been seen
                        q.push( adj );              // push (adj)acent neighbor vertex onto (q)ueue for future processing
            }
            return seen;
        }
        
    };
    
    int main()
    {
        //
        // Figure 8.5 from page 26 of Algorithms Illuminated: Part 2
        //
        Solution::Graph G = {
    
            { 's', { 'a', 'b' } },
    
            { 'a', { 's', 'c' } },
    
            { 'b', { 's', 'c' } },
    
            { 'c', { 'a', 'b', 'd', 'e' } },
    
            { 'd', { 'b', 'c', 'e' } },
    
            { 'e', { 'c', 'd', } }
    
        };
        Solution s;
        auto result = s.bfs( G );
    
        return 0;
    }

```

## Build Instructions
Use ```cmake``` to build this project:

```
    cmake --build cmake-build-debug --target bfs -- -j 4
```

## Dependencies
* [cmake.org](https://cmake.org)
