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


using namespace std;
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
using VI = vector< Cost >;
using VVI = vector< VI >;
using VVVI = vector< VVI >;
static const Cost INF = numeric_limits< Cost >::max();
using AdjacencyList = unordered_set< Vertex >;
using Graph = unordered_map< Vertex, AdjacencyList >;
struct Edge
{
    Vertex u{ 0 }, v{ 0 };
    bool operator==( const Edge& rhs ) const { return u == rhs.u && v == rhs.v; }
};
struct Hash{ Cost operator()( const Edge& e ) const { return ( N+1 ) * e.u + e.v; } };
using Edges = unordered_map< Edge, Cost, Hash >;
using Vertices = unordered_set< Vertex >;


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

    using Answer = pair< VVI, bool >;

    static Answer getShortestPaths( Graph& G, Edges& E, Vertex start )
    {
        VVI dp( N+1, VI( N+1, INF )); // 1-based indexing
        dp[ 0 ][ start ] = 0;
        for( auto i{ 1 }; i <= N; ++i )
            for( auto& pair: G )
            {
                auto v{ pair.first };
                dp[ i ][ v ] = dp[ i-1 ][ v ]; // (pre)vious path or minimum (alt)erative path to v through w + cost of edge wv
                for( auto w: G[ v ] ) // w -> v
                {
                    Edge wv{ w,v };
                    Cost Cw = dp[ i-1 ][ w ],
                         Cwv = E[ wv ],
                         alt = ( Cw < INF )? Cw + Cwv : INF;
                    if( dp[ i ][ v ] > alt )
                        dp[ i ][ v ] = alt;
                }
            }
        auto hasCycle = BellmanFord::hasCycle( G, E, dp );
        return{ dp, hasCycle };
    }

private:

    static bool hasCycle( Graph& G, Edges& E, VVI& dp )
    {
        for( auto& e: E )
        {
            auto edge{ e.first };
            auto Cuv = e.second,
                 Cu = dp[ N ][ edge.u ],
                 Cv = dp[ N ][ edge.v ];
            if( Cu < INF && Cv > Cu + Cuv )
                return true;
        }
        return false;
    }

}; // class BellmanFord


class Johnson
{
public:

    using Answer = pair< VVVI, bool >;

    static Answer getShortestPaths( const string& input )
    {
        Vertices V;
        for( size_t vertex{ 1 }; vertex <= N; ++vertex )
            V.insert( vertex );
        auto E = readInput( input );
        auto G = generateGraph( V, E );
        Vertex source{ 0 };
        auto[ Gs, Es ] = Johnson::addSourceVertex( G, E, source );
        Gs = reverse( Gs ); // Gs was generated with outgoing adjacency lists, reverse Gs for incoming adjacency lists needed by Bellman-Ford
        auto[ P, hasCycle ] = BellmanFord::getShortestPaths( Gs, Es, source );
        if( hasCycle )
            return{ {}, true };
        return{ {}, false };
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
        cout << inputFile << " contains cycle? " << answer.second << endl;
    }

    return 0;
}
