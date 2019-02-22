/**
 *
 * Modern C++ implementation of greedy heuristic nearest neighbor algorithm for the travelling salesman problem
 * to approximate a min tour in O(N^2) time
 *
 * Note: a tour is a path which traverses each vertex exactly once, starting and finishing at a specific vertex
 *
 * (c) Copyright 2019 Clayton J. Wong ( http://www.claytonjwong.com )
 *
 **/


#include "input.hpp"
#include <iostream>
#include <sstream>
#include <vector>
#include <iomanip>
#include <cmath>
#include <set>
#include <unordered_set>


//#define LECTURE_INPUT 69


#ifdef LECTURE_INPUT

    constexpr auto N{ 4 }; // lecture input contains 4 cities

#else

    constexpr auto N{ 33708 }; // assignment input contains 25 cities

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
using Pool = set< int >;
using Seen = unordered_set< int >;
using Tour = vector< int >;


CityList readInput( const string& input, CityList C={} )
{
    istringstream stream{ input };
    for( string line; getline( stream, line ); )
    {
        istringstream parser{ line };

#ifdef LECTURE_INPUT

        for( RealNum x{ 0 }, y{ 0 }; parser >> x >> y; C.push_back({ x,y }) );

#else

        auto id{ 0 };
        for( RealNum x{ 0 }, y{ 0 }; parser >> id >> x >> y; C.push_back({ x,y }) );

#endif
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

    RealNum minTour( Cost& D, Pool pool={}, RealNum minCost=0 )
    {
        auto cur{ 0 }; // 0-based index of (cur)rent city
        Seen seen{ cur };
        for( auto i{ cur }; i < N; pool.insert( i++ ) ); // include cur since distance() is invoked upon pool for (alt)ernative candidate indices
        for( auto next{ 0 }; seen.size() < pool.size(); swap( cur, next ) )
        {
            auto nextCost{ INF };
            for( auto it{ pool.begin() }; it != pool.end(); ++it )
            {
                if( seen.find( *it ) != seen.end() )
                    continue;
                auto alt = static_cast< int >( distance( pool.begin(), it ) ); // unseen (alt)ernative pool candidate index
                auto cost = D[ cur ][ alt ];
                if( nextCost > cost )
                    nextCost = cost,
                    next = alt;
            }
            minCost += nextCost;
            seen.insert( next );
        }
        return minCost + D[ cur ][ 0 ]; // return the first city to complete the tour
    }

}; // class Solution


int main()
{

#ifdef LECTURE_INPUT

    /**
     *
     * lecture input ( answer: 13 )
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
     **/

    Cost cost{
        { 0, 2, 1, 3 },
        { 2, 0, 4, 5 },
        { 1, 4, 0, 6 },
        { 3, 5, 6, 0 },
    };

#else

    //
    // assignment input
    //
    auto city = readInput( Assignment::Input );
    auto cost = getCosts( city );

#endif

    Solution solution;
    auto ans = solution.minTour( cost );

    cout << "answer: " << ans << endl;

    return 0;
}
