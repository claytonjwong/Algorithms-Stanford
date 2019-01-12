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
        auto threshold = A.begin(), less = next( threshold );
        for( auto more{ less }; more != R; ++more )
            if( *more < *threshold )
                iter_swap( less++, more );
        auto pivot = prev( less );
        auto index = distance( A.begin(), pivot );
        iter_swap( A.begin(), pivot );
        return A.begin() + index;
    }

private:

    using RandomDevice = random_device;
    using Generator = mt19937;

    Iter random( Iter L, Iter R, RandomDevice randomDevice=RandomDevice() )
    {
        Generator randomGenerator{ randomDevice() };
        int size = static_cast< int >( distance( L, R ) );
        uniform_int_distribution< int > distribute{ 0, size - 1 }; // size - 1 since R is non-inclusive
        return L + distribute( randomGenerator );
    }

    void go( Collection& A, Iter L, Iter R ) // go() sorts from [ L : R ), that is, from L (inclusive) to R (non-inclusive)
    {
        if( L >= R ) return;
        auto threshold = random( L, R );
        iter_swap( A.begin(), threshold );
        auto pivot = partition( A, L, R );
        go( A, L, pivot );
        go( A, next( pivot ), R );
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