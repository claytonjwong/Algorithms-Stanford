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
        return go({ A.cbegin(), A.cend() });
    }

private:

    Collection go( Collection&& A )
    {
        if( A.size() < 2 ) // base case
            return A;

        auto pivot = A.cbegin() + A.size() / 2;
        return merge( go({ A.cbegin(), pivot }), go({ pivot, A.cend() }) );
    }

    Collection merge( Collection&& lhs, Collection&& rhs, Collection res={} ) // merge (res)ult
    {
        auto L = lhs.cbegin(), R = rhs.cbegin();
        while( L != lhs.cend() && R != rhs.cend() )
            res.push_back( ( *L < *R )? *L++ : *R++ );
        res.insert( res.end(), L, lhs.cend() ), res.insert( res.end(), R, rhs.cend() ); // append left-overs ( if applicable )
        return res;
    }

};


int main()
{
    const Solution< int >::Collection
        A{ 9,5,6,3,2,8,0,4,1,7 },
        B{ 3,9,7,1,2,8,6,5,0,4 },
        C{ 3,2,9,7,1,3,7,2,8,1,6,5,0,8,0,4 };

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