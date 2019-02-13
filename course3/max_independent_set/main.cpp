/**
 *
 * Modern C++ implementation of maximum independent set algorithm
 *
 * (c) Copyright 2019 Clayton J. Wong ( http://www.claytonjwong.com )
 *
 **/


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


template< typename Solution >
string max_independent_set()
{
    Solution solution;
    Graph G;
    istringstream inStream{ Assignment::Input };
    for( string line; getline( inStream, line ); )
    {
        istringstream parser{ line };
        Cost cost{ 0 };
        parser >> cost;
        G.push_back( cost );
    }
    auto memo = solution.max_independent_set( G );
    auto max = reconstruct( G, memo );
    ostringstream outStream;
    for( auto vertex: { 1, 2, 3, 4, 17, 117, 517, 997 } )
        outStream << ( max.find( vertex ) != max.end() );
    return outStream.str();
}


int main()
{
    cout << "Top-Down answer: " << max_independent_set< TopDown::Solution >() << endl << endl
         << "Bottom-Up answer: " << max_independent_set< BottomUp::Solution >() << endl << endl;

//    Top-Down answer:  10100110

//    Bottom-Up answer: 10100110

    return 0;
}
