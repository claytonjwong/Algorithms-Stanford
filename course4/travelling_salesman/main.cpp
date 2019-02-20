/**
 *
 * Modern C++ implementation of the Held-Karp travelling salesman algorithm to find minimum tour in a graph
 *
 * Note: a tour is a path which traverses each vertex exactly once, starting and finishing at a specific vertex
 *
 * (c) Copyright 2019 Clayton J. Wong ( http://www.claytonjwong.com )
 *
 **/

#include "input.hpp"
#include <iostream>
#include <sstream>
#include <bitset>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <cmath>
#include <unordered_map>


constexpr auto N{ 4 }; // assignment input contains 25 cities


using namespace std;
using RealNum = double;
constexpr auto INF = numeric_limits< RealNum >::max();
using VR = vector< RealNum >;
using VVR = vector< VR >;
using Cost = VVR;
struct City{ RealNum x{ 0 }, y{ 0 }; };
ostream& operator<<( ostream& os, const City& c )
{
    os << fixed << setprecision( 4 ) << "{" << c.x << "," << c.y << "}";
    return os;
}
using CityList = vector< City >;


CityList readInput( const string& input, CityList C={} )
{
    istringstream stream{ input };
    for( string line; getline( stream, line ); )
    {
        istringstream parser{ line };
        for( RealNum x{ 0 }, y{ 0 }; parser >> x >> y; C.push_back({ x,y }) );
    }
    assert( N == C.size() );
    return C;
}


Cost getCosts( CityList& C )
{
    Cost cost = VVR( N, VR( N, 0 ) );
    for( auto i{ 0 }; i < N; ++i ) for( auto j{ 0 }; j < N; ++j ) // euclidean distance for each i,j pair of (C)ities
    {
        auto x = ( C[ i ].x - C[ j ].x ),
             y = ( C[ i ].y - C[ j ].y );
        cost[ i ][ j ] = sqrt(( x * x ) + ( y * y ));
    }
    return cost;
}


class Solution
{
public:

    RealNum tour( Cost& D )
    {
        // TODO: reconsider overall strategy bottom-up, make things easier on myself by using a 2-D vector instead of map
        // for the first implementation, since that *should* be less error prone, as it is a more simple approach
        VVR dp(( 1 << N ), VR( N, INF ));
        dp[ 1 ][ 0 ] = 0; // base case: bit at position 0 is set ( 1 ): S = {0}
//            A[ key( 1, k ) ] = D[ 0 ][ k ]; //            so S + {k} = {0} + {k} = cost of 0,k
        auto minCost{ INF };
        for( auto m{ 2 }; m <= N; ++m ) // m = sub-problem size ( cardinality of S )
        {
            auto S = Set( ( 1 << m ) - 1 ).to_string(); // all bits set till m
            do {
                auto bits{ Set{ S } };
                auto S_with_j{ bits.to_ulong() };
                for( auto j{ 1 }, k{ 0 }; j < N; ++j ) // for each bit-j in S, j != 0
                {
                    if( ! bits[ j ] )
                        continue;
                    bits.reset( j ); // S - {j} ( forward tracking )
                    auto S_without_j = bits.to_ulong();
                    {
                        for( dp[ S_with_j ][ j ] = INF, k = 0; k < N; ++k ) // find min-k in S ( k != j ): A[ S - {j}, k ] + cost of k,j
                        {
                            if( k == j )
                                continue;
                            auto Ck = dp[ S_without_j ][ k ], // A[ S - {j}, k ] == (C)ost of path 1 -> ... -> k ( without j )
                                 Ckj = D[ k ][ j ],           // (C)ost of k,j
                                 cost = ( Ck < INF )? Ck + Ckj : INF;
                                if( dp[ S_with_j ][ j ] > cost )
                                    dp[ S_with_j ][ j ] = cost;
                        }
                    }
                    bits.set( j ); // S + {j} ( back tracking )
                }
            } while( next_permutation( S.begin(), S.end() - 1 )); // Note: end - 1 to NOT permute upon the last bit, source vertex {0} is always included in S
        }
        auto P{ dp.back() }; // use (P)aths of {S} from 1 -> ... -> k to calculate the min full tour by connecting k with source vertex {0}
        for( auto k{ 1 }; k < N; ++k )
        {
            auto alt = P[ k ] + D[ k ][ 0 ]; // consider each (alt)ernative cost based on each penultimate vertex choice k
            if( minCost > alt )
                minCost = alt;
        }
        return minCost;
    }

private:

    using Key = unsigned long;
    using Set = bitset< N >;

    Key key(Set &bits ){ return bits.to_ulong(); }
    Key key(Set &&bits ){ return bits.to_ulong(); }

}; // class Solution


int main()
{
    Solution solution;
//    auto city = readInput( Assignment::Input );
//    auto cost = getCosts( city );
//    auto ans = solution.tour( city, cost );

    // lecture input ( 13 )
    Cost cost{
        { 0, 2, 1, 3 },
        { 2, 0, 4, 5 },
        { 1, 4, 0, 6 },
        { 3, 5, 6, 0 },
    };
    auto ans = solution.tour( cost );

    cout << "answer: " << ans << endl;

    return 0;
}
