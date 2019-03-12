/**
 *
 * Modern C++ implementation of Kruskal's minimum spanning tree algorithm
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
#include <vector>


using namespace std;
using Type = int;


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
    using EdgeCost = pair< Edge, Cost >;
    using Leader = unordered_map< Vertex, Vertex >;


    Type costMST( Graph& G, Edges& E )
    {
        Tree tree;
        for( auto& pair: G )
        {
            auto vertex{ pair.first };
            tree.lead[ vertex ] = vertex;
        }
        auto Compare = []( const EdgeCost& lhs, const EdgeCost& rhs ){ return lhs.second < rhs.second; };
        multiset< EdgeCost, decltype( Compare )> edges{ E.begin(), E.end(), Compare };
        for( auto& edge: edges )
        {
            auto u{ edge.first.tail },
                 v{ edge.first.head };
            auto lu{ tree.Find( u ) },
                 lv{ tree.Find( v ) };
            if( lu == lv )
                continue; // skip past edges where both vertices are already part of the tree, since this would form a cycle
            tree.Union( lu, lv );
            auto cost{ edge.second };
            tree.cost += cost;
        }
        return tree.cost;
    }

private:

    struct Tree
    {
        Cost cost{ 0 };
        Leader lead;

        void Union( Vertex u, Vertex v )
        {
            auto lu{ Find( u ) },
                 lv{ Find( v ) };
            if( lu != lv )
                lead[ lu ] = lv; // arbitrary lead choice
        }

        Vertex Find( Vertex v )
        {
            if( v == lead[ v ] )
                return v;
            else
                return lead[ v ] = Find( lead[ v ] );
        }
    };

};


Type costMST( const string& input )
{
    Solution< Type > s;
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
    return s.costMST( G, E );
}


int main()
{

    cout << "lecture answer: "    << costMST( Lecture::Input )    << endl << endl
         << "assignment answer: " << costMST( Assignment::Input ) << endl << endl;

    return 0;
}
