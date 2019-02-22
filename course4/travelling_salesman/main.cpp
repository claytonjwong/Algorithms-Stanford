/**
 *
 * Modern C++ implementation of the Held-Karp travelling salesman algorithm to find min tour in O(N^2 * 2^N) time
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


#define LECTURE_INPUT 69


#ifdef LECTURE_INPUT

    constexpr auto N{ 4 }; // lecture input contains 25 cities ( optimal solution: 13 )

#else

    constexpr auto N{ 25 }; // assignment input contains 25 cities ( optimal solution: 26442 )

#endif


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

    RealNum minTour( Cost& D, RealNum minCost=INF )
    {
        VVR dp(( 1 << N ), VR( N, INF ));
        dp[ 1 ][ 0 ] = 0; // base case: set bit at position 0 ( S = {0} ): A[ S, 0 ] = 0
        for( auto m{ 2 }; m <= N; ++m ) // m = sub-problem size ( cardinality of S )
        {
            auto S = Set( ( 1 << m ) - 1 ).to_string(); // set right-most m-bits
            do {
                auto bits = Set{ S };
                auto Sj = bits.to_ulong();
                for( auto j{ 1 }, k{ 0 }; j < N; ++j ) // for each bit-j in S, j != 0, source vertex 0 is always included in S
                {
                    if( ! bits[ j ] )
                        continue;
                    bits.reset( j ); // S - {j}
                    auto alt = bits.to_ulong(); // (alt)ernative path ending at j, comprised of vertices S - {j}
                    for( dp[ Sj ][ j ] = INF, k = 0; k < N; ++k ) // for each penultimate vertex k, find min-k in S: A[ S - {j}, k ] + cost of k,j
                    {
                        if( k == j )
                            continue;
                        auto Ck = dp[ alt ][ k ], // A[ S - {j}, k ] == (C)ost of (alt)ernative path 1 -> ... -> k ( without j )
                            Ckj = D[ k ][ j ],   // (C)ost of k,j
                            cost = ( Ck < INF )? Ck + Ckj : INF; // (alt)ernative path 1 -> ... -> k ( without j ) + cost of k,j
                        if( dp[ Sj ][ j ] > cost )
                            dp[ Sj ][ j ] = cost; // min cost of each (alt)ernative path with penultimate vertex k ending at vertex j
                    }
                    bits.set( j ); // S + {j}
                }
            } while( next_permutation( S.begin(), S.end() - 1 )); // Note: end - 1 to NOT permute upon the right-most bit, source vertex 0 is always included in S
        }
        auto P{ dp.back() }; // use (P)aths of {S} from 0 -> ... -> k to calculate the min tour by connecting k with source vertex 0
        for( auto k{ 1 }; k < N; ++k )
        {
            auto alt = P[ k ] + D[ k ][ 0 ]; // consider each (alt)ernative cost based on each penultimate vertex choice k
            if( minCost > alt )
                minCost = alt;
        }
        return minCost;
    }

private:

    using Set = bitset< N >;

}; // class Solution


int main()
{

#ifdef LECTURE_INPUT

    /*
     *   lecture input ( answer: 13 )
     *
     *             2
     *     (0)-----------(1)
     *      |\           /|
     *      | \         / |
     *      |  \ 3     /  |
     *      |   \     /   |
     *      |    \   /    |
     *      |     \ /     |
     *    1 |      \      | 5
     *      |     / \     |
     *      |    /   \    |
     *      |   /     \   |
     *      |  / 4     \  |
     *      | /         \ |
     *      |/           \|
     *     (2)-----------(3)
     *             6
     *
     */
    Cost cost{
        { 0, 2, 1, 3 },
        { 2, 0, 4, 5 },
        { 1, 4, 0, 6 },
        { 3, 5, 6, 0 },
    };

#else

    auto city = readInput( Assignment::Input );
    auto cost = getCosts( city );

#endif

    Solution solution;
    auto ans = solution.minTour( cost );

    cout << "answer: " << static_cast< int >( ans ) << endl; // answer: 26442

    return 0;
}
