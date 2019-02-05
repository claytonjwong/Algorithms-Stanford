/*

Part 1:

In this programming problem and the next you'll code up the clustering algorithm from lecture
for computing a max-spacing kk-clustering.

This file describes a distance function (equivalently, a complete graph with edge costs). It has the following format:

[number_of_nodes]

[edge 1 node 1] [edge 1 node 2] [edge 1 cost]

[edge 2 node 1] [edge 2 node 2] [edge 2 cost]

...

There is one edge (i,j)(i,j) for each choice of 1 \leq i \lt j \leq n1≤i<j≤n, where nn is the number of nodes.

For example, the third line of the file is "1 3 5250", indicating that the distance between nodes 1 and 3
(equivalently, the cost of the edge (1,3)) is 5250. You can assume that distances are positive,
but you should NOT assume that they are distinct.

Your task in this problem is to run the clustering algorithm from lecture on this data set,
where the target number kk of clusters is set to 4. What is the maximum spacing of a 4-clustering?

ADVICE: If you're not getting the correct answer, try debugging your algorithm using some small test cases.
And then post them to the discussion forum!


Part 2:

*/

#include "input.hpp"
#include <iostream>
#include <sstream>
#include <fstream>
#include <unordered_set>
#include <unordered_map>
#include <map>
#include <set>
#include <vector>


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
    using EdgeCost = pair< Edge, Cost >;
    using Leader = unordered_map< Vertex, Vertex >;
    using Bucket = unordered_map< size_t, unordered_set< size_t > >;

    Cost maxSpacingKClusters( Graph& G, Edges& E, size_t K )
    {
        Cost cost{ 0 };
        auto N{ G.size() };
        Clusters clusters;
        for( auto& pair: G )
        {
            auto vertex{ pair.first };
            clusters.lead[ vertex ] = vertex;
        }
        auto Compare = []( const EdgeCost& lhs, const EdgeCost& rhs ){ return lhs.second < rhs.second; };
        multiset< EdgeCost, decltype( Compare )> edges{ E.begin(), E.end(), Compare };
        for( auto& edge: edges )
        {
            auto u{ edge.first.tail },
                 v{ edge.first.head };
            auto lu{ clusters.Find( u ) },
                 lv{ clusters.Find( v ) };
            if( lu == lv )
                continue;
            if( N <= K )
            {
                cost = edge.second;
                break;
            }
            clusters.Union( lu, lv ), --N; // decrement N for each union
        }
        return cost;
    }

    // TODO: write pseudo code for this first!!!
    size_t maxClusters( Bucket& bucket, size_t threshold ) // TODO: create a bucket of (ham)ming weights < threshold
    {
        auto N{ 0 };
        Clusters clusters;

        // TODO: find all same values and union together as initial 0 distance hamming weight disjoint sets --> initial ham0 set

        // TODO: for distance = 1 to threshold ( non-inclusive )

            // iter all bits of each num in the ham to find another num in the bucket which is not in the ham already ( or find lead to check if leads differ )
            // if off by 1-bit and not already part of the ham, include in next ham set

        // once next ham set is created (above for-loop), coalesce into the original ham set, keep repeating until threshold is met ( non-inclusive ) -- use hamCount < threshold?

        return N;
    }

private:

    struct Clusters
    {
        Leader lead;

        void Union( Vertex u, Vertex v )
        {
            auto lu{ Find( u ) },
                 lv{ Find( v ) };
            if( lu != lv )
                lead[ lu ] = lv; // arbitrary lead choice
        }

        Vertex Find( Vertex v ){ return( lead[ v ] == v )? v : lead[ v ] = Find( lead[ v ] ); }
    };

};


int main()
{
    //
    // part 1
    //
    using Type = int;

    auto K{ 4 };
    Solution< Type > s;
    Solution< Type >::Graph G;
    Solution< Type >::Edges E;
    istringstream stream{ Assignment1::Input };
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
    auto answer_part1 = s.maxSpacingKClusters( G, E, K );
    cout << "answer ( part 1 ): " << answer_part1 << endl << endl;

    //
    // part 2
    //
    auto hammingThreshold{ 3 }; // non-inclusive, find all K-clusters with hamming distance strictly LESS THAN this threshold
    Solution< Type >::Bucket bucket;
    string line;
    for( fstream stream{ "hamming.txt" }; getline( stream, line ); )
    {
        line.erase( remove( line.begin(), line.end(), ' ' ), line.end() );
        size_t num{ 0 };
        for( auto i{ 0 }; i < 24; ++i )
        {
            if( line[ i ] == '1' )
                num |= ( 1 << i );
        }
        if( bucket.find( num ) == bucket.end() )
            bucket[ num ] = {};
        bucket[ num ].insert( num );
    }
    auto answer_part2 = s.maxClusters( bucket, hammingThreshold );


    // answer ( part 1 ): 106

    return 0;
}
