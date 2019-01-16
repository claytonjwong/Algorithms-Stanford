#include "input.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
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
        if( distance( L, R ) == 1 ) return *L; // base case: sub-array size 1
        iter_swap( L, random( L, R ) );        // random (P)ivot
        auto P = partition( A, L, R );
        auto j = distance( L, P ) + 1;         // +1 for 1-based indexing
        if( i == j )
            return *P;                         // lucky guess
        else if( i < j )
            return go( A, L, P, i );           // first half
        else
            return go( A, P + 1, R, i - j );   // second half
    }

    Iter partition( Collection& A, Iter L, Iter R )
    {
        auto threshold{ L }, less{ L + 1 };
        for( auto more{ less }; more != R; ++more )
            if( *more < *threshold )
                iter_swap( less++, more );
        auto pivot{ less - 1 };
        iter_swap( L, pivot );
        return pivot;
    }

    using RandomDevice = random_device;
    using Generator = mt19937;
    using Distribution = uniform_int_distribution< int >;

    Iter random( Iter L, Iter R, RandomDevice randomDevice=RandomDevice() )
    {
        Generator randomGenerator{ randomDevice() };
        int size = distance( L, R-1 );        // R-1 since R is non-inclusive
        Distribution distribution{ 0, size }; // size of size+1 for distribution from [ 0 : size ], that is 0 ( inclusive ) to size ( inclusive )
        return L + distribution( randomGenerator );
    }
};


int main()
{
    using Type = size_t;
    Solution< Type > solution;
    Solution< Type >::Collection A{
        2148, 9058, 7742, 3153, 6324, 609, 7628, 5469, 7017, 504 };
    assert( solution.r_select( A, 5 ) == 5469 );

    Solution< Type >::Collection B;
    stringstream stream{ INPUT };
    for( string line; getline( stream, line ); )
    {
        stringstream parser{ line };
        Type num{ 0 };
        parser >> num;
        B.emplace_back( num );
    }
    assert( solution.r_select( B, 50 ) == 4715 );

    return 0;
}