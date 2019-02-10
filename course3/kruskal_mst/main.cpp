/*

In this programming problem you'll code up Kruskal's minimum spanning tree algorithm.

Download the text file below.

This file describes an undirected graph with integer edge costs. It has the format

[number_of_nodes] [number_of_edges]

[one_node_of_edge_1] [other_node_of_edge_1] [edge_1_cost]

[one_node_of_edge_2] [other_node_of_edge_2] [edge_2_cost]

...

For example, the third line of the file is "2 3 -8874",
indicating that there is an edge connecting vertex #2 and vertex #3 that has cost -8874.

You should NOT assume that edge costs are positive, nor should you assume that they are distinct.

Your task is to run Prim's minimum spanning tree algorithm on this graph. You should report the overall cost
of a minimum spanning tree --- an integer, which may or may not be negative --- in the box below.

IMPLEMENTATION NOTES: This graph is small enough that the straightforward O(mn) time implementation
of Prim's algorithm should work fine. OPTIONAL: For those of you seeking an additional challenge,
try implementing a heap-based version. The simpler approach, which should already give you a healthy speed-up,
is to maintain relevant edges in a heap (with keys = edge costs). The superior approach stores the unprocessed vertices
in the heap, as described in lecture. Note this requires a heap that supports deletions,
and you'll probably need to maintain some kind of mapping between vertices and their positions in the heap.

*/

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

    cout << "lecture answer: " << costMST( Lecture::Input ) << endl << endl
         << "assignment answer: " << costMST( Assignment::Input ) << endl << endl;

//    lecture answer: 7

//    assignment answer: -3612829

    return 0;
}
