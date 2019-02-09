/*

In this programming problem you'll code up the dynamic programming algorithm
for computing a maximum-weight independent set of a path graph.

Download the text file below.

This file describes the weights of the vertices in a path graph (with the weights listed in the order
in which vertices appear in the path). It has the following format:

[number_of_vertices]

[weight of first vertex]

[weight of second vertex]

...

For example, the third line of the file is "6395702,"
indicating that the weight of the second vertex of the graph is 6395702.

Your task in this problem is to run the dynamic programming algorithm (and the reconstruction procedure)
from lecture on this data set. The question is: of the vertices 1, 2, 3, 4, 17, 117, 517, and 997,
which ones belong to the maximum-weight independent set? (By "vertex 1" we mean the first vertex of the graph
--there is no vertex 0.) In the box below, enter a 8-bit string,
where the ith bit should be 1 if the ith of these 8 vertices is in the maximum-weight independent set,
and 0 otherwise. For example, if you think that the vertices 1, 4, 17, and 517 are in the maximum-weight independent set
and the other four vertices are not, then you should enter the string 10011010 in the box below.

*/


#include "input.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <map>
#include <numeric>


using namespace std;
using Type = size_t;
using Cost = Type;
using Vertex = Type;
using Graph = vector< Cost >; // Vertex id is implicitly the index of the (G)raph
using Iter = typename vector< Cost >::iterator;
using Memo = map< Vertex, Cost >;


Memo reconstruct( Graph& G, Memo& memo, Memo max={} )
{
    auto N{ G.size() };
    for( auto i{ long(N) }; i > 0; )
        if( memo[ i-1 ] == memo[ i ] )
            i -= 1;
        else
            max[ i ] = memo[ i ],
            i -= 2;
    return max;
}


namespace TopDown
{
    class Solution
    {
    public:

        Memo max_independent_set( Graph& G, Memo memo={} )
        {
            go( G, G.end(), memo );
            return memo;
        }

    private:
        
        Cost go( Graph& G, Iter end, Memo& memo )
        {
            auto n = distance( G.begin(), end );
            for( auto it{ memo.find(n) }; it != memo.end(); ) // if found, return memoized cost for Vn
            {
                auto cost{ it->second };
                return cost;
            }
            auto Vn = ( n == 0 )? end : end-1; // end is non-inclusive, when n > 0, Vn is the last element in the range [ G.begin() : end )
            if( n == 0 ) return memo[ n ] = 0;
            if( n == 1 ) return memo[ n ] = ( *Vn );
            auto S1 = go( G, Vn, memo ),
                 S2 = go( G, Vn-1, memo ) + ( *Vn );
            return memo[ n ] = ( S1 > S2 )? S1 : S2;
        }

    }; // class Solution

} // namespace TopDown


namespace BottomUp
{
    class Solution
    {
    public:

        Memo max_independent_set( Graph& G, Memo memo={} )
        {
            auto N{ G.size() };
            if( N == 0 )
                return {};
            auto Vn = G.begin();
            Graph dp( N + 1 );
            memo[ 0 ] = dp[ 0 ] = 0;
            memo[ 1 ] = dp[ 1 ] = ( *Vn++ );
            for( auto i{ 2 }; i <= N; ++i )
                memo[ i ] = dp[ i ] = max( dp[ i-1 ], dp[ i-2 ] + ( *Vn++ ) ); // note: *Vn is the same as G[ i-1 ] ( the i-th entry of G in terms of dp's (i)ndex )
            return memo;
        }

    }; // class Solution

} // namespace BottomUp


int main()
{
    //
    // Top Down
    //
    {
        TopDown::Solution solution;
        Graph G;
        istringstream stream{ Assignment::Input };
        for( string line; getline( stream, line ); )
        {
            istringstream parser{ line };
            Cost cost{ 0 };
            parser >> cost;
            G.push_back( cost );
        }
        auto memo = solution.max_independent_set( G );
        auto max = reconstruct( G, memo );
        cout << "TopDown answer:  ";
        for( auto vertex: { 1, 2, 3, 4, 17, 117, 517, 997 } )
            cout << ( max.find( vertex ) != max.end() );
        cout << endl << endl;
    }

    //
    // Bottom Up
    //
    {
        BottomUp::Solution solution;
        Graph G;
        istringstream stream{ Assignment::Input };
        for( string line; getline( stream, line ); )
        {
            istringstream parser{ line };
            Cost cost{ 0 };
            parser >> cost;
            G.push_back( cost );
        }
        auto memo = solution.max_independent_set( G );
        auto max = reconstruct( G, memo );
        cout << "BottomUp answer: ";
        for( auto vertex: { 1, 2, 3, 4, 17, 117, 517, 997 } )
            cout << ( max.find( vertex ) != max.end() );
        cout << endl << endl;
    }

//    TopDown answer:  10100110

//    BottomUp answer: 10100110

    return 0;
}
