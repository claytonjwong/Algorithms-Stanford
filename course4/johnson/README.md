# Johnson
https://en.wikipedia.org/wiki/Johnson%27s_algorithm

## Contents
* [Lecture Slides](#lecture-slides)
* [Solution](#solution)
* [Build Instructions](#build-instructions)
* [Dependencies](#dependencies)

## Lecture Slides
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course4/johnson/documentation/john_01.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course4/johnson/documentation/john_02.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course4/johnson/documentation/john_03.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course4/johnson/documentation/john_04.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course4/johnson/documentation/john_05.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course4/johnson/documentation/john_06.png)
---


## Solution
```cpp

    /**
     *
     * Modern C++ implementation of Johnson's algorithm to find the all-pairs shortest paths in a graph
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
    #include <queue>
    
    
    using namespace std;
    using InputFiles = vector< string >;
    //
    // Lecture Test Input
    //
    const auto N{ 6 };
    const InputFiles inputFiles{ "lecture.txt" };
    //
    // Assignment Input
    //
    //const auto N{ 1000 };
    //const InputFiles inputFiles{ "g1.txt", "g2.txt", "g3.txt" };
    //
    // Optional Challenge Input
    //
    //const auto N{ 20000 };
    //const InputFiles inputFiles{ "large.txt" };
    using Integer = long long;
    using Vertex = Integer;
    using Cost = Integer;
    using VI = vector< Cost >;
    using VVI = vector< VI >;
    using VVVI = vector< VVI >;
    static const Cost INF = numeric_limits< Cost >::max();
    using AdjacencyList = unordered_set< Vertex >;
    using Graph = unordered_map< Vertex, AdjacencyList >;
    struct Edge{ Vertex u{ 0 }, v{ 0 }; bool operator==( const Edge& rhs ) const { return u == rhs.u && v == rhs.v; } };
    struct Hash{ Cost operator()( const Edge& e ) const { return ( N+1 ) * e.u + e.v; } };
    using Edges = unordered_map< Edge, Cost, Hash >;
    using Vertices = unordered_set< Vertex >;
    using VertexCost = pair< Vertex, Cost >;
    struct Compare{ bool operator()( const VertexCost& lhs, const VertexCost& rhs ) const { return lhs.second > rhs.second; } };
    using Queue = priority_queue< VertexCost, vector< VertexCost >, Compare >;
    
    
    Edges readInput( const string& input, Edges edges={}, Vertex u=0, Vertex v=0, Cost cost=0 )
    {
        fstream stream{ input };
        for( string line; getline( stream, line ); )
        {
            stringstream parser{ line };
            while( parser >> u >> v >> cost )
                edges[ {u,v} ] = cost;
        }
        return edges;
    }
    
    Graph generateGraph( const Vertices& V, const Edges& E, Graph G={} )
    {
        for( auto& vertex: V )
            G[ vertex ] = {};
        for( auto& pair: E )
        {
            auto edge{ pair.first };
            G[ edge.u ].insert( edge.v ); // u -> v
        }
        return G;
    }
    
    Graph reverse( Graph& G )
    {
        Graph R{ G }; // Reversed (G)raph: keep G's vertex keys ( pair.first ), but clear G's adjacency lists ( pair.second )
        for_each( R.begin(), R.end(), []( auto& pair ){ pair.second={}; });
        for( auto& pair: G )
        {
            auto u{ pair.first };
            for( auto v: G[ u ] )   // u -> v
                R[ v ].insert( u ); // v -> u
        }
        return R;
    }
    
    
    class BellmanFord
    {
    public:
    
        using Answer = pair< VI, bool >;
    
        static Answer getShortestPaths( Graph& G, Edges& E, Vertex start )
        {
            VI pre( N+1, INF ), cur( pre );
            pre[ start ] = 0;
            for( auto i{ 1 }; i <= N; ++i, swap( pre, cur ) )
                for( auto& pair: G )
                {
                    auto v{ pair.first };
                    cur[ v ] = pre[ v ]; // (pre)vious path or minimum (alt)erative path to v through w + cost of edge wv
                    for( auto w: G[ v ] ) // w -> v
                    {
                        Edge wv{ w,v };
                        Cost Cw = pre[ w ],
                             Cwv = E[ wv ],
                             alt = ( Cw < INF )? Cw + Cwv : INF;
                        if( cur[ v ] > alt )
                            cur[ v ] = alt;
                    }
                }
            auto hasCycle = BellmanFord::hasCycle( G, E, cur );
            return{ cur, hasCycle };
        }
    
    private:
    
        static bool hasCycle( Graph& G, Edges& E, VI& P )
        {
            for( auto& e: E )
            {
                auto edge{ e.first };
                auto u{ edge.u },
                     v{ edge.v };
                auto Pu = P[ u ],      // cost of (P)ath from s -> ... -> u
                     Pv = P[ v ],      // cost of (P)ath from s -> ... -> v
                     cost{ e.second }; // cost of u -> v
                if( Pu < INF && Pv > Pu + cost )
                    return true;
            }
            return false;
        }
    
    }; // class BellmanFord
    
    
    class Dijkstra
    {
    public:
    
        using MinCost = unordered_map< Vertex, Cost >;
    
        static MinCost getShortestPaths( Graph& G, Edges& E, Vertex start, Queue q={}, MinCost C={} )
        {
            for( auto& pair: G )
            {
                auto vertex{ pair.first };
                C[ vertex ] = INF;
            }
            C[ start ] = 0;
            for( q.push({ start, C[ start ] }); ! q.empty(); q.pop() )
            {
                auto u{ q.top().first };
                auto cost{ q.top().second };
                for( auto& v: G[ u ] )
                {
                    Edge uv{ u,v };
                    auto alt = ( cost < INF )? cost + E[ uv ] : INF;
                    if( C[ v ] > alt )
                        C[ v ] = alt,
                        q.push({ v, C[ v ] });
                }
            }
            return C;
        }
    
    };
    
    class Johnson
    {
    public:
    
        using Answer = pair< Cost, bool >;
    
        static Answer getShortestPaths( const string& input )
        {
            Vertices V;
            for( size_t vertex{ 1 }; vertex <= N; ++vertex )
                V.insert( vertex );
            auto E = readInput( input );
            auto G = generateGraph( V, E );
            //
            // form Gs by adding a new vertex 'source' and a new edge of cost 0
            // from 'source' to each vertex in G to determine if a cycle exists
            //
            Vertex source{ 0 };
            auto[ Gs, Es ] = Johnson::addSourceVertex( G, E, source );
            Gs = reverse( Gs ); // Gs was generated with outgoing adjacency lists, reverse Gs for incoming adjacency lists needed by Bellman-Ford
            auto[ P, hasCycle ] = BellmanFord::getShortestPaths( Gs, Es, source );
            if( hasCycle )
                return{ {}, true };
            //
            // re-weight edges using the (P)aths found from runnning Bellman-Ford
            // on the augmented graph Gs ( G with new vertex 'source' )
            //
            for( auto& pair: E )
            {
                auto edge{ pair.first };
                auto u{ edge.u },
                     v{ edge.v };
                auto Pu = P[ u ],
                     Pv = P[ v ];
                auto cost{ pair.second };
                E[{ u,v }] = ( cost < INF )? cost + Pu - Pv : 0;
            }
            //
            // run Dijkstra to find the minimum cost for each path from u -> ... -> v
            // convert the weight back to the original graph's edge weights
            // and track the minimum cost path to be returned
            //
            auto minCost{ INF };
            for( auto u: V )
            {
                auto C = Dijkstra::getShortestPaths( G, E, u );
                for( auto& pair: C )
                {
                    auto v{ pair.first };
                    auto cost{ pair.second };
                    auto Pu = P[ u ],
                         Pv = P[ v ];
                    cost = ( cost < INF )? cost - Pu + Pv : 0;
                    if( minCost > cost )
                        minCost = cost;
                }
            }
            return{ minCost, false };
        }
    
    private:
    
        static pair< Graph, Edges > addSourceVertex( Graph& G, Edges& E, Vertex s )
        {
            Graph Gs{ G };
            Edges Es{ E };
            Gs[ s ] = {};
            for( auto& pair: G )
            {
                auto v{ pair.first };
                Gs[ s ].insert( v ); // s -> v
                Es[ {s,v} ] = 0;     // s -> v has cost 0
            }
            return{ Gs, Es };
        }
    
    }; // class Johnson
    
    
    int main()
    {
        for( auto& inputFile: inputFiles )
        {
            auto answer = Johnson::getShortestPaths( inputFile );
            auto hasCycle{ answer.second };
            cout << inputFile << ": ";
            if( hasCycle )
                cout << "has a cycle" << endl;
            else
                cout << "has shortest path " << answer.first << endl;
        }
    
    //    lecture.txt: has shortest path -6
    
    //    g1.txt: has a cycle
    //    g2.txt: has a cycle
    //    g3.txt: has shortest path -19
    
    //    large.txt: has shortest path -6
    
        return 0;
    }

```

## Build Instructions
Use ```cmake``` to build this project:

```
    cmake --build cmake-build-debug --target johnson -- -j 4
```

## Dependencies
* [cmake.org](https://cmake.org)
