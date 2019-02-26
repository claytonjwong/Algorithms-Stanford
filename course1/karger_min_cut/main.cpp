/**
 *
 * Modern C++ implementation of Karger's algorithm to find the minimum cut in a graph
 *
 * (c) Copyright 2019 Clayton J. Wong ( http://www.claytonjwong.com )
 *
 **/


#include "input.hpp"
#include <iostream>
#include <sstream>
#include <vector>
#include <set>
#include <unordered_map>
#include <random>


using namespace std;


class Solution
{
public:

    using Vertex = size_t;
    using AdjacencyList = multiset< Vertex >;
    using Graph = unordered_map< Vertex, AdjacencyList >;
    struct Edge{ Vertex u{ 0 }, v{ 0 }; };

    int getMinCut( Graph G ) // assume (G)raph is connected undirected with at least one edge and two vertices
    {
        for( Edge edge; G.size() > 2; contractEdge( G, edge ) )
            edge = randomEdge( G );
        return G.cbegin()->second.size();
    }

private:

    using RandomDevice = random_device;
    using Generator = mt19937;
    using Distribution = uniform_int_distribution< Vertex >;

    int randomVertex( Vertex begin, Vertex end, RandomDevice randomDevice=RandomDevice() )
    {
        Generator generator{ randomDevice() };
        Distribution distribution{ begin, end-1 }; // end-1, since end is non-inclusive
        return distribution( generator );
    }

    Edge randomEdge( Graph& G )
    {
        auto N{ G.size() }, u{ next( G.cbegin(), randomVertex( 0, N ))->first };     // random u from |V| ( the set of all vertices )
        auto M{ G[ u ].size() }, v{ *next( G[ u ].cbegin(), randomVertex( 0, M )) }; // random v from the set of vertices adjacent to u
        return { u,v };
    }

    void contractEdge( Graph& G, const Edge& edge ) // coalesce u into v, then delete u
    {
        auto v{ edge.v }, u{ edge.u };
        for( auto& adj: G[ u ] )  // contract edge{ u -> v }: create edges from v based on u's (adj)acent vertices  and erase each vertex (adj)acent to u
        {
            if( adj == v )
                continue;         // avoid adding self-loop when coalescing u's adj(acent) vertices into v
            G[ v ].insert( adj ); // edge{ v -> adj }: each (adj)acent vertex of u is contracted as an (adj)acent vertex to v
            G[ adj ].insert( v ); // edge{ adj -> v }: since the graph is undirected, also add an (adj)acency in the opposite direction
            G[ adj ].erase( u );  // since the graph is undirected, erase u from each of u's (adj)acent vertices
        }
        G.erase( u ); // erase all edges{ u -> adj } and edge{ u -> v }: performed all-at-once VS piecemeal removal of edge{ adj -> u } above
        G[ v ].erase( u ); // since the graph is undirected, also remove v -> u
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
    for( auto N{ 100 }; N--; minCut = min( minCut, s.getMinCut( G ) ) ); // run min cut algo an arbitrary amount of times
    cout << "minCut: " << minCut << endl;

    // minCut: 17

    return 0;
}
