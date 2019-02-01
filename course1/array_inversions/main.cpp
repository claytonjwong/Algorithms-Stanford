/*

This file contains all of the 100,000 integers between 1 and 100,000 (inclusive)
in some order, with no integer repeated.  Your task is to compute the number of inversions
in the file given, where the i-th row of the file indicates the i-th entry of an array.
Because of the large size of this array, you should implement the fast divide-and-conquer algorithm
covered in the video lectures.

*/

#include "input.hpp"
#include <iostream>
#include <vector>
#include <sstream>


using namespace std;


template< typename T >
class Solution
{
public:

    using Collection = vector< T >;

    size_t inversions( const Collection& A )
    {
        return go({ A.cbegin(), A.cend() }).count;
    }

private:

    struct Result
    {
        Collection A;
        size_t count{ 0 };
    };

    Result go( Collection&& A )
    {
        if( A.size() < 2 )
            return { A, 0 };
        auto pivot = A.cbegin() + A.size() / 2;
        return merge( go({ A.cbegin(), pivot }), go({ pivot, A.cend() }) );
    }

    Result merge( Result&& lhs, Result&& rhs )
    {
        Result res{ {}, lhs.count + rhs.count }; // left + right inversions
        auto L = lhs.A.cbegin(), R = rhs.A.cbegin();
        while( L != lhs.A.cend() && R != rhs.A.cend() )
            if( *L < *R )
                res.A.push_back( *L++ );
            else
                res.A.push_back( *R++ ),
                res.count += distance( L, lhs.A.cend() ); // split inversions
        res.A.insert( res.A.end(), L, lhs.A.cend() ), res.A.insert( res.A.end(), R, rhs.A.cend() ); // append leftovers ( if applicable )
        return res;
    }

};


int main()
{
    string line;
    stringstream stream{ INPUT };
    Solution< size_t >::Collection A;
    for( size_t num{ 0 }; getline( stream, line ); A.push_back( num ) )
    {
        stringstream parser{ line };
        parser >> num;
    }
    Solution< size_t > s;
    cout << s.inversions( A ) << endl; // 2407905288
    return 0;
}