/**
 *
 * Modern C++ implementation of Randomized Linear Selection algorithm to find the i-th order statistic in linear time
 *
 * (c) Copyright 2019 Clayton J. Wong ( http://www.claytonjwong.com )
 *
 **/


#include "input.hpp"
#include "pi.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <random>


using namespace std;


template< typename Type >
class Solution
{
public:

    using Collection = vector< Type >;
    using Iter = typename Collection::iterator;

    Type r_select( const Collection& A, size_t i )
    {
        auto C{ A }; // make a (C)opy of A to find the i-th smallest element.  this copy is made because r-select
                     // requires sorting via partitioning, so the collection is modified during the search

        return go( C, C.begin(), C.end(), i );
    }

private:

    Type go( Collection& A, Iter L, Iter R, size_t i )
    {
        if( distance( L, R ) == 1 )            // base case: sub-array size 1
            return *L;

        iter_swap( L, random( L, R ) );        // random (P)ivot
        auto P = partition( A, L, R );
        auto j = distance( L, P ) + 1;         // +1 for 1-based indexing
        if( i == j )
            return *P;                         // lucky guess
        else if( i < j )
            return go( A, L, P, i );           // first half
        else
            return go( A, P+1, R, i-j );       // second half
    }

    Iter partition( Collection& A, Iter L, Iter R )
    {
        auto threshold{ L }, less{ L+1 };
        for( auto more{ less }; more != R; ++more )
            if( *more < *threshold )
                iter_swap( less++, more );
        auto pivot{ less-1 };
        iter_swap( L, pivot );
        return pivot;
    }

    using RandomDevice = random_device;
    using Generator = mt19937;
    using Distribution = uniform_int_distribution< int >;

    Iter random( Iter L, Iter R, RandomDevice randomDevice=RandomDevice() )
    {
        Generator randomGenerator{ randomDevice() };
        int size = distance( L, R-1 );              // R-1 since R is non-inclusive
        Distribution distribution{ 0, size };       // distribution span [ 0 : size ], that is 0 ( inclusive ) to size ( inclusive )
        return L + distribution( randomGenerator ); // [ L : R-1 ], that is from L ( inclusive ) to R-1 ( inclusive )
    }
};


int main()
{
    using Type = size_t;
    Solution< Type > solution;

    //
    // test case #1: http://www.algorithmsilluminated.org/datasets/problem6.5test1.txt
    //
    Solution< Type >::Collection A{ 2148, 9058, 7742, 3153, 6324, 609, 7628, 5469, 7017, 504 };
    assert( solution.r_select( A, 5 ) == 5469 ); // 5-th order statistic

    //
    // test case #2: http://www.algorithmsilluminated.org/datasets/problem6.5test2.txt
    //
    Solution< Type >::Collection B;
    stringstream stream{ INPUT };
    for( string line; getline( stream, line ); )
    {
        stringstream parser{ line };
        Type num{ 0 };
        parser >> num;
        B.emplace_back( num );
    }
    assert( solution.r_select( B, 50 ) == 4715 ); // 50-th order statistic

    //
    // challenge data set: form an array in which the first element is the first 10 digits of pi,
    // the second element is the next 10 digits of pi, and so on.  Make the array as big as you can
    // (perhaps 100,000 elements or 1 million elements, or ...).  What is the median of the array?
    //
    int chunkSize{ 10 };
    Solution< Type >::Collection C;
    stringstream pi_10{ PI_10 };
    for( string digits; pi_10 >> setw( chunkSize ) >> digits; )
    {
        stringstream parser{ digits };
        Type num{ 0 };
        parser >> num;
        C.emplace_back( num );
    }
    cout << "Median for first 10 digits of PI:      " << solution.r_select( C, ceil( C.size() / 2.0 ) )
         << endl,
    C.clear();

    stringstream pi_100{ PI_100 };
    for( string digits; pi_100 >> setw( chunkSize ) >> digits; )
    {
        stringstream parser{ digits };
        Type num{ 0 };
        parser >> num;
        C.emplace_back( num );
    }
    cout << "Median for first 100 digits of PI:     " << solution.r_select( C, C.size() / 2 )
         << endl,
    C.clear();

    stringstream pi_1000{ PI_1000 };
    for( string digits; pi_1000 >> setw( chunkSize ) >> digits; )
    {
        stringstream parser{ digits };
        Type num{ 0 };
        parser >> num;
        C.emplace_back( num );
    }
    cout << "Median for first 1000 digits of PI:    " << solution.r_select( C, C.size() / 2 )
         << endl,
    C.clear();

    stringstream pi_10000{ PI_10000 };
    for( string digits; pi_10000 >> setw( chunkSize ) >> digits; )
    {
        stringstream parser{ digits };
        Type num{ 0 };
        parser >> num;
        C.emplace_back( num );
    }
    cout << "Median for first 10000 digits of PI:   " << solution.r_select( C, C.size() / 2 )
         << endl,
    C.clear();

    stringstream pi_100000{ PI_100000 };
    for( string digits; pi_100000 >> setw( chunkSize ) >> digits; )
    {
        stringstream parser{ digits };
        Type num{ 0 };
        parser >> num;
        C.emplace_back( num );
    }
    cout << "Median for first 100000 digits of PI:  " << solution.r_select( C, C.size() / 2 )
         << endl,
    C.clear();

    stringstream pi_1000000{ PI_1000000 };
    for( string digits; pi_1000000 >> setw( chunkSize ) >> digits; )
    {
        stringstream parser{ digits };
        Type num{ 0 };
        parser >> num;
        C.emplace_back( num );
    }
    cout << "Median for first 1000000 digits of PI: " << solution.r_select( C, C.size() / 2 )
         << endl,
    C.clear();

//    Median for first 10 digits of PI:      3141592653
//    Median for first 100 digits of PI:     4592307816
//    Median for first 1000 digits of PI:    4330572703
//    Median for first 10000 digits of PI:   5157098583
//    Median for first 100000 digits of PI:  4933967376
//    Median for first 1000000 digits of PI: 5013895529

    return 0;
}