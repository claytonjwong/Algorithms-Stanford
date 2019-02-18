# Vertex Cover
https://en.wikipedia.org/wiki/Vertex_cover

## Contents
* [Lecture](#lecture)
* [Lecture Slides](#lecture-slides)
* [Solution](#solution)
* [Build Instructions](#build-instructions)
* [Dependencies](#dependencies)

## Lecture
[Video](https://www.coursera.org/lecture/algorithms-npcomplete/the-vertex-cover-problem-fxmkY)

## Lecture Slides
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course4/vertex_cover_k/documentation/cover_01.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course4/vertex_cover_k/documentation/cover_02.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course4/vertex_cover_k/documentation/cover_03.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course4/vertex_cover_k/documentation/cover_04.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course4/vertex_cover_k/documentation/cover_05.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course4/vertex_cover_k/documentation/cover_06.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course4/vertex_cover_k/documentation/cover_07.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course4/vertex_cover_k/documentation/cover_08.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course4/vertex_cover_k/documentation/cover_09.png)
---


## Solution
```cpp

    /**
     *
     * Modern C++ implementation of vertex cover K algorithm from the lecture
     *
     * (c) Copyright 2019 Clayton J. Wong ( http://www.claytonjwong.com )
     *
     **/
    
    
    #include "input.hpp"
    #include <iostream>
    #include <sstream>
    #include <unordered_set>
    #include <vector>
    #include <algorithm>
    
    
    using namespace std;
    using Vertex = long;
    using Cover = vector< Vertex >;
    struct Edge{ Vertex u{ 0 }, v{ 0 }; bool operator==( const Edge& rhs ) const { return u == rhs.u && v == rhs.v; } };
    struct Hash{ Vertex operator()( const Edge& e ) const { return ( 20001 * e.u ) + e.v; } };
    using Edges = unordered_set< Edge, Hash >;
    
    
    class Solution
    {
    public:
    
        using Answer = pair< Cover, bool >;
    
        Answer vertex_cover_k( Edges& E, size_t K )
        {
            return go( E, K );
        }
    
    private:
    
        Answer go( Edges& E, size_t K )
        {
            if( K == 0 || E.empty() )
                return { {}, E.empty() };
            auto edge{ E.begin() }; // arbitrarily choose the first edge in (E)dges
            auto u{ edge->u },
                 v{ edge->v };
            Edges Eu, Ev; // (E)dges with vertex u,v and corresponding incident edges removed
            copy_if( E.begin(), E.end(), inserter( Eu, Eu.end() ), [=]( auto& e ){ return u != e.u && u != e.v; });
            copy_if( E.begin(), E.end(), inserter( Ev, Ev.end() ), [=]( auto& e ){ return v != e.u && v != e.v; });
            auto Au = go( Eu, K-1 ), // (A)nswer with cover set of Eu: (E)dges with vertex u and u's incident edges removed
                 Av = go( Ev, K-1 ); // (A)nswer with cover set of Ev: (E)dges with vertex v and v's incident edges removed
            auto Su{ Au.first }, // cover (S)et for Eu
                 Sv{ Av.first }; // cover (S)et for Ev
            Su.push_back( u ),
            Sv.push_back( v );
            if( ! Au.second && ! Av.second )
                return{ {}, false };
            else
            if(( Au.second && Av.second && Su.size() <= Sv.size() ) || // if both valid, arbitrarily return Su ( unless size Su > Sv )
               ( Au.second && ! Av.second ))
                return{ Su, true };
            else
                return{ Sv, true };
        }
    
    }; // class Solution
    
    
    int main()
    {
        Solution solution;
        Edges E;
        istringstream stream{ Tree::Input };
        for( string line; getline( stream, line ); )
        {
            istringstream parser{ line };
            for( Vertex u{ 0 }, v{ 0 }; parser >> u >> v; E.insert({ u,v }) );
        }
        for( auto K{ 1 }; K < 10; ++K )
        {
            auto[ cover, ok ] = solution.vertex_cover_k( E, K );
            cout << "K{ " << K << " } cover ";
            if( ok )
                cout << "OK: ", copy( cover.begin(), cover.end(), ostream_iterator< Vertex >( cout, " " ) ), cout << endl;
            else
                cout << "NG!" << endl;
        }
    
    //    K{ 1 } cover NG!
    //    K{ 2 } cover NG!
    //    K{ 3 } cover OK: 3 2 5
    //    K{ 4 } cover OK: 3 2 5
    //    K{ 5 } cover OK: 3 2 5
    //    K{ 6 } cover OK: 3 2 5
    //    K{ 7 } cover OK: 3 2 5
    //    K{ 8 } cover OK: 3 2 5
    //    K{ 9 } cover OK: 3 2 5
    
        return 0;
    }

```

## Build Instructions
Use ```cmake``` to build this project:

```
    cmake --build cmake-build-debug --target vertex_cover_k -- -j 4
```

## Dependencies
* [cmake.org](https://cmake.org)
