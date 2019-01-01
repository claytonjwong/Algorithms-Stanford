#include <iostream>
#include <vector>
#include <algorithm>


using namespace std;


template< typename T >
class Solution
{
    using Vector = vector< T >;
    using Iter = typename Vector::iterator;

    Vector go( Vector&& A )
    {
        auto N{ A.size() };
        if( N < 2 ) return A;
        auto pivot{ A.cbegin() + N / 2 };
        return merge( go({ A.cbegin(), pivot }), go({ pivot, A.cend() }) );
    }

    Vector merge( const Vector& lhs, const Vector& rhs, Vector res={} )
    {
        auto i{ lhs.cbegin() }, j{ rhs.cbegin() };
        while( i < lhs.cend() && j < rhs.cend() ) res.push_back( ( *i < *j )? *i++ : *j++ );
        if( i != lhs.cend() ) res.insert( res.end(), i, lhs.cend() );
        if( j != rhs.cend() ) res.insert( res.end(), j, rhs.cend() );
        return res;
    }

public:

    Vector mergeSort( const Vector& A )
    {
        return go({ A.cbegin(), A.cend() });
    }

};


int main()
{
    vector< int > A{ 9,5,6,3,2,8,0,4,1,7 };
    vector< int > B{ 3,9,7,1,2,8,6,5,0,4 };
    vector< int > C{ 3,2,9,7,1,3,7,2,8,1,6,5,0,8,0,4 };

    Solution< int > s;
    auto
        resultA{ s.mergeSort( A ) },
        resultB{ s.mergeSort( B ) },
        resultC{ s.mergeSort( C ) };

    cout << "is_sorted()? " << is_sorted( resultA.cbegin(), resultA.cend() ) << endl;
    cout << "is_sorted()? " << is_sorted( resultB.cbegin(), resultB.cend() ) << endl;
    cout << "is_sorted()? " << is_sorted( resultC.cbegin(), resultC.cend() ) << endl;

    return 0;
}