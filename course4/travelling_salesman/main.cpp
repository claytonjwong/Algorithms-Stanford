/**
 *
 * Modern C++ implementation to find minimum path in a graph which traverses each vertex exactly once,
 * starting and finishing at a specific vertex
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


constexpr auto N{ 25 }; // assignment input contains 25 cities


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

    RealNum tour( CityList& C, Cost& D )
    {
        auto minCost{ INF };
        auto K = key( Set{ 1 }, 0 );
        Map A{{ K,0 }};
        for( auto m{ 2 }; m <= N; ++m ) // m = sub-problem size
        {
            auto S = Set( ( 1 << m ) - 1 ).to_string(); // all bits set till m
            do {
                auto bits = Set( S );
                for( auto j{ 1 }, k{ 1 }; j < N; ++j ) // for each j in S, j != 0
                {
                    if( ! bits[ j ] )
                        continue;
                    auto Sj = key( bits, j );
                    for( A[ Sj ] = INF, bits.reset( j ), k = 1; k < N; ++k ) // find min-k in S ( k != j): A[ S - {j}, k ] + cost of k,j
                    {
                        if( k == j )
                            continue;
                        auto Sk = key( bits, k );
                        auto it = A.find( Sk );
                        if( it != A.end() )
                        {
                            auto cost = ( it->second < INF )? it->second + D[ k ][ j ] : INF;
                            if( A[ Sj ] > cost )
                                A[ Sj ] = cost;
                        }
                    }
                }
            } while( next_permutation( S.begin(), S.end() ));
        }
        return minCost;
    }

private:

    using Key = size_t;
    using Map = unordered_map< Key, RealNum >;
    using Set = bitset< N >;

    Key key( Set& bits, int j ){ return ( bits.to_ulong() << N ) + j; }
    Key key( Set&& bits, int j ){ return ( bits.to_ulong() << N ) + j; }

}; // class Solution


int main()
{
    Solution solution;
    auto city = readInput( Assignment::Input );
    auto cost = getCosts( city );
    auto ans = solution.tour( city, cost );

    cout << "answer: " << ans << endl;

    return 0;
}
