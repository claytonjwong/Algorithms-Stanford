#include "input.hpp"
#include <iostream>
#include <vector>
#include <random>
#include <sstream>


using namespace std;


enum class PivotChoice{ Left, Median, Right, Random };


template< typename Type >
class Solution
{
public:

    using Collection = vector< Type >;
    using Iter = typename Collection::iterator;

    size_t quickSort( Collection& A, const PivotChoice pivotChoice = PivotChoice::Random  )
    {
        return go( A, A.begin(), A.end(), pivotChoice );
    }

private:

    size_t go( Collection& A, Iter L, Iter R, const PivotChoice PC ) // go() sorts from [ L : R ), that is, from L (inclusive) to R (non-inclusive)
    {
        if( L >= R ) return 0;
        choosePivot( L, R, PC );
        auto P = partition( A, L, R ); // (P)ivot
        return distance( L, R-1 ) + go( A, L, P, PC ) + go( A, P+1, R, PC );
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

    void choosePivot( Iter& L, Iter& R, const PivotChoice PC )
    {
        if( PC == PivotChoice::Left )
        {
            //
            // question #1: always use left-most [ L : R ) as pivot ( no-op: by default L is used as pivot )
            //
            iter_swap( L, L );
        }
        else if( PC == PivotChoice::Right )
        {
            //
            // question #2: always use right-most [ L : R ) as pivot ( note: this is R-1 since R is non-inclusive )
            //
            iter_swap( L, R-1 );
        }
        else if( PC == PivotChoice::Median )
        {
            //
            // question #3: use median from [ L : R ) as pivot ( note: the right-most value is at R-1 since R is non-inclusive )
            //
            auto M = L + ceil( distance( L, R ) / 2.0 ) - 1;                 // (M)iddle
            Collection C{ *L, *M, *( R-1 ) };                                  // Three pivot (C)andidates: (L)eft-most, (M)iddle, (R)ight-most element in [ L : R )
            sort( C.begin(), C.end() );                                      // median is the middle element C[ 1 ] for the sorted array C of size 3
            auto median = ( C[ 1 ] == *L )? L  : ( C[ 1 ] == *M )? M  : R-1; // find corresponding iterator
            iter_swap( L, median );                                          // use median as pivot
        }
        else if( PC == PivotChoice::Random )
        {
            //
            // extra credit: use random value from [ L : R ) for pivot
            //
            iter_swap( L, random( L, R ) );
        }
    }

    using RandomDevice = random_device;
    using Generator = mt19937;
    using Distribution = uniform_int_distribution< int >;

    Iter random( Iter L, Iter R, RandomDevice randomDevice=RandomDevice() )
    {
        Generator randomGenerator{ randomDevice() };
        int size = distance( L, R-1 ); // R is non-inclusive
        Distribution distribution{ 0, size };
        return L + distribution( randomGenerator );
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

    Solution< Type >::Collection Q1{ A };
    cout << "Question #1 ( Pivot is Left ):   " << s.quickSort( Q1, PivotChoice::Left ) << endl;
    assert( is_sorted( Q1.cbegin(), Q1.cend() ) );

    Solution< Type >::Collection Q2{ A };
    cout << "Question #2 ( Pivot is Right ):  " << s.quickSort( Q2, PivotChoice::Right ) << endl;
    assert( is_sorted( Q2.cbegin(), Q2.cend() ) );

    Solution< Type >::Collection Q3{ A };
    cout << "Question #3 ( Pivot is Median ): " << s.quickSort( Q3, PivotChoice::Median ) << endl;
    assert( is_sorted( Q3.cbegin(), Q3.cend() ) );

    Solution< Type >::Collection Q4{ A };
    cout << "Question #4 ( Pivot is Random ): " << s.quickSort( Q4, PivotChoice::Random ) << endl;
    assert( is_sorted( Q4.cbegin(), Q4.cend() ) );

//    copy( A.cbegin(), A.cend(), ostream_iterator< Type >( cout, " " ) );

//    Question #1 ( Pivot is Left ):   162085
//    Question #2 ( Pivot is Right ):  164123
//    Question #3 ( Pivot is Median ): 138382
//    Question #4 ( Pivot is Random ): 146451

    return 0;
}
