#include "input.hpp"
#include <iostream>
#include <vector>
#include <random>
#include <sstream>


using namespace std;


template< typename T >
class Solution
{
public:

    using Collection = vector< T >;
    using Iter = typename Collection::iterator;

    void quickSort( Collection& A )
    {
        auto count = go( A, A.begin(), A.end() );
        cout << "Comparision count: " << count << endl;
    }

private:

    using RandomDevice = random_device;
    using Generator = mt19937;
    using Distribution = uniform_int_distribution< int >;

    size_t go( Collection& A, Iter L, Iter R ) // go() sorts from [ L : R ), that is, from L (inclusive) to R (non-inclusive)
    {
        if( L >= R ) return 0;

        //
        // move random threshold value for pivot to the beginning of [ L : R ) for partitioning
        //
//        iter_swap( L, random( L, R ) );

        //
        // question #1: always use left-most [ L : R ) as pivot
        //
//        iter_swap( L, L );

        //
        // question #2: always use right-most [ L : R ) as pivot ( note: this is R-1 since R is non-inclusive )
        //
//        iter_swap( L, R-1 );

        //
        // question #3: use median from [ L : R ) as pivot ( note: the right-most value is at R-1 since R is non-inclusive )
        //
        auto M = L + ceil( distance( L, R ) / 2.0 ) - 1;                 // (M)iddle
        Collection C{ *L, *M, *(R-1) };                                  // Three pivot (C)andidates: (L)eft-most, (M)iddle, (R)ight-most element in [ L : R )
        sort( C.begin(), C.end() );                                      // median is the middle element C[ 1 ] for the sorted array C of size 3
        auto median = ( C[ 1 ] == *L )? L  : ( C[ 1 ] == *M )? M  : R-1; // find corresponding iterator
        iter_swap( L, median );                                          // use median as pivot

        auto P = partition( A, L, R ); // (P)ivot
        return distance( L, R-1 ) + go( A, L, P ) + go( A, P+1, R );
    }

    Iter random( Iter L, Iter R, RandomDevice randomDevice=RandomDevice() )
    {
        Generator randomGenerator{ randomDevice() };
        int size = static_cast< int >( distance( L, R ) );
        Distribution distribution{ 0, size - 1 }; // size - 1 since R is non-inclusive
        return L + distribution( randomGenerator );
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

};


int main()
{
    using Type = size_t;
    Solution< Type > s;
    Solution< Type >::Collection A;
    stringstream stream{ INPUT };
    for( string line; getline( stream, line ); )
    {
        stringstream parser{ line };
        Type number{ 0 };
        parser >> number;
        A.push_back( number );
    }
    s.quickSort( A );
    assert( is_sorted( A.cbegin(), A.cend() ) );
    copy( A.cbegin(), A.cend(), ostream_iterator< Type >( cout, " " ) );

    // 1: 162085 - OK
    // 2: 164123 - OK
    // 3: 138382 - OK

    return 0;
}
