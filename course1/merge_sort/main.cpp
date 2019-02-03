#include <iostream>
#include <vector>
#include <algorithm>


using namespace std;


template< typename T >
class Solution
{
public:

    using Collection = vector< T >;

    Collection mergeSort( const Collection& A )
    {
        return go({ A.begin(), A.end() });
    }

private:

    Collection go( Collection&& A )
    {
        if( A.size() < 2 )
            return A;
        auto pivot = A.begin() + A.size() / 2;
        return merge( go({ A.begin(), pivot }), go({ pivot, A.end() }) );
    }

    Collection merge( Collection&& lhs, Collection&& rhs, Collection res={} ) // merge (res)ult
    {
        auto L = lhs.begin(), R = rhs.begin();
        while( L != lhs.end() && R != rhs.end() )
            res.push_back( ( *L < *R )? *L++ : *R++ );
        res.insert( res.end(), L, lhs.end() ), res.insert( res.end(), R, rhs.end() ); // append left-overs ( if applicable )
        return res;
    }

};


int main()
{
    using Type = int;

    const Solution< Type >::Collection
        A_unsorted{ 9,5,6,3,2,8,0,4,1,7 },
        B_unsorted{ 3,9,7,1,2,8,6,5,0,4 },
        C_unsorted{ 3,2,9,7,1,3,7,2,8,1,6,5,0,8,0,4 };

    Solution< Type > s;
    auto
        A{ s.mergeSort( A_unsorted ) },
        B{ s.mergeSort( B_unsorted ) },
        C{ s.mergeSort( C_unsorted ) };

    assert( is_sorted( A.begin(), A.end() ) );
    assert( is_sorted( B.begin(), B.end() ) );
    assert( is_sorted( C.begin(), C.end() ) );

    cout << "A: "; copy( A.begin(), A.end(), ostream_iterator< Type >( cout, " " ) ); cout << endl;
    cout << "B: "; copy( B.begin(), B.end(), ostream_iterator< Type >( cout, " " ) ); cout << endl;
    cout << "C: "; copy( C.begin(), C.end(), ostream_iterator< Type >( cout, " " ) ); cout << endl;

//    A: 0 1 2 3 4 5 6 7 8 9
//    B: 0 1 2 3 4 5 6 7 8 9
//    C: 0 0 1 1 2 2 3 3 4 5 6 7 7 8 8 9

    return 0;
}