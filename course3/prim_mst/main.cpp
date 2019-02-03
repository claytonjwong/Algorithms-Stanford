/*

In this programming problem you'll code up Prim's minimum spanning tree algorithm.

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
 is to maintain relevant edges in a heap (with keys = edge costs). The superior approach stores
 the unprocessed vertices in the heap, as described in lecture. Note this requires a heap that supports deletions,
 and you'll probably need to maintain some kind of mapping between vertices and their positions in the heap.

*/

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
