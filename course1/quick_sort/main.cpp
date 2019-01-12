#include <iostream>
#include <vector>
#include <random>


using namespace std;


template< typename T >
class Solution
{
public:

    using Collection = vector< T >;
    using Iter = typename Collection::iterator;

    void quickSort( Collection& A )
    {
        go( A, A.begin(), A.end() );
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

private:

    using RandomDevice = random_device;
    using Generator = mt19937;
    using Distribution = uniform_int_distribution< int >;

    Iter random( Iter L, Iter R, RandomDevice randomDevice=RandomDevice() )
    {
        Generator randomGenerator{ randomDevice() };
        int size = static_cast< int >( distance( L, R ) );
        Distribution distribution{ 0, size - 1 }; // size - 1 since R is non-inclusive
        return L + distribution( randomGenerator );
    }

    void go( Collection& A, Iter L, Iter R ) // go() sorts from [ L : R ), that is, from L (inclusive) to R (non-inclusive)
    {
        if( L >= R ) return;
        iter_swap( L, random( L, R ) ); // move random threshold value for pivot to the beginning of [ L : R ) for partitioning
        auto pivot = partition( A, L, R );
        go( A, L, pivot );
        go( A, pivot + 1, R );
    }

};


int main()
{
    using Type = size_t;
    Solution< Type > s;
    Solution< Type >::Collection A{ 9,5,6,7,2,3,1,0,4,8 };
    s.quickSort( A );
    assert( is_sorted( A.cbegin(), A.cend() ) );
    copy( A.cbegin(), A.cend(), ostream_iterator< Type >( cout, " " ) );
    return 0;
}
