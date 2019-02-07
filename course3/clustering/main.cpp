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

In this question your task is again to run the clustering algorithm from lecture,
but on a MUCH bigger graph. So big, in fact, that the distances (i.e., edge costs) are only defined implicitly,
rather than being provided as an explicit list.

The format is:

[# of nodes] [# of bits for each node's label]

[first bit of node 1] ... [last bit of node 1]

[first bit of node 2] ... [last bit of node 2]

...

For example, the third line of the file "0 1 1 0 0 1 1 0 0 1 0 1 1 1 1 1 1 0 1 0 1 1 0 1"
denotes the 24 bits associated with node #2.

The distance between two nodes uu and vv in this problem is defined as
the Hamming distance--- the number of differing bits --- between the two nodes' labels.
For example, the Hamming distance between the 24-bit label of node #2 above
and the label "0 1 0 0 0 1 0 0 0 1 0 1 1 1 1 1 1 0 1 0 0 1 0 1" is 3 (since they differ in the 3rd, 7th, and 21st bits).

The question is: what is the largest value of k such that there is a k-clustering with spacing at least 3?
That is, how many clusters are needed to ensure that no pair of nodes with all but 2 bits
 in common get split into different clusters?

NOTE: The graph implicitly defined by the data file is so big that you probably can't write it out explicitly,
let alone sort the edges by cost. So you will have to be a little creative to complete this part of the question.
For example, is there some way you can identify the smallest distances without explicitly looking at every pair of nodes?

*/

#include "input.hpp"
#include <iostream>
#include <iomanip>
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
    using Buckets = unordered_map< size_t, size_t >;
    using Leads = unordered_set< Type >;
    using Hammed = bitset< 24 >;

    Cost maxSpacingKClusters( const string& input, size_t K )
    {
        Graph G;
        Edges E;
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
        auto Compare = []( const EdgeCost& lhs, const EdgeCost& rhs ){ return lhs.second < rhs.second; };
        multiset< EdgeCost, decltype( Compare )> edges{ E.begin(), E.end(), Compare };
        Leads leads;
        transform( G.begin(), G.end(), inserter( leads, leads.end() ), []( auto& pair )
        {
            auto vertex{ pair.first };
            return vertex;
        });
        Clusters clusters{ leads };
        Cost cost{ 0 };
        for( auto& edge: edges )
        {
            auto u{ edge.first.tail },
                 v{ edge.first.head };
            auto lu{ clusters.Find( u ) },
                 lv{ clusters.Find( v ) };
            if( lu == lv )
                continue;
            if( clusters.size() <= K )
            {
                cost = edge.second;
                break;
            }
            clusters.Union( lu, lv );
        }
        return cost;
    }

    size_t maxClusters( size_t threshold )
    {
        Buckets buckets;
        Leads leads;
        string line;
        for( fstream stream{ "hamming.txt" }; getline( stream, line ); )
        {
            line.erase( remove( line.begin(), line.end(), ' ' ), line.end() );
            Hammed hammed{ line };
            auto num{ hammed.to_ulong() };
            ++buckets[ num ];
            leads.insert( num );
        }
        Clusters clusters{ leads };
        for( auto& pair: buckets )
        {
            auto num{ pair.first };
            for( auto i{ 0 }; i < 24; ++i )
            {
                Hammed alt{ num }; // (alt)ernative number to be manipulated as "hamming distance" away from (num)ber
                alt.flip( i );
                auto match = alt.to_ulong();
                if( buckets.find( match ) != buckets.end() )
                    clusters.Union( num, match );
                for( auto j{ i+1 }; j < 24; ++j )
                {
                    alt.flip( j );
                    match = alt.to_ulong();
                    if( buckets.find( match ) != buckets.end() )
                        clusters.Union( num, match );
                    alt.flip( j );
                }
            }
        }
        return clusters.size();
    }

private:

    class Clusters
    {
    public:

        Clusters( Leads& leads ) : N_{ leads.size() }
        {
            for( auto x: leads )
                lead_[ x ] = x;
        }

        void Union( Type u, Type v )
        {
            auto lu{ Find( u ) },
                 lv{ Find( v ) };
            if( lu == lv )
                return;
            lead_[ lu ] = lv, --N_; // arbitrary lead choice and decrement N
        }

        Type Find( Type x )
        {
            if( lead_[ x ] == x )
                return x;
            else
                return lead_[ x ] = Find( lead_[ x ] );
        }

        size_t size()
        {
            return N_;
        }

    private:

        size_t N_;
        using Leader = unordered_map< Type, Type >;
        Leader lead_;

    };

};


int main()
{
    //
    // part 1
    //
    using Type = size_t;

    auto K{ 4 };
    Solution< Type > s;
    auto answer_part1 = s.maxSpacingKClusters( Assignment1::Input, K );
    cout << "answer ( part 1 ): " << answer_part1 << endl << endl;

    //
    // part 2
    //
    auto hammingThreshold{ 3 }; // non-inclusive, find all K-clusters with hamming distance strictly LESS THAN this threshold
    auto answer_part2 = s.maxClusters( hammingThreshold );
    cout << "answer ( part 2 ): " << answer_part2 << endl << endl;

//    answer ( part 1 ): 106

//    answer ( part 2 ): 6118

    return 0;
}
