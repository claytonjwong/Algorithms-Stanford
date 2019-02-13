/**
 *
 * Modern C++ implementation of Array Inversions algorithm to count the amount of inversions in an array
 *
 * (c) Copyright 2019 Clayton J. Wong ( http://www.claytonjwong.com )
 *
 **/


#include "input.hpp"
#include <iostream>
#include <vector>
#include <sstream>


using namespace std;


template< typename Type >
class Solution
{
public:

    using Collection = vector< Type >;

    size_t inversions( const Collection& A )
    {
        return go({ A.begin(), A.end() }).count;
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
        auto pivot = A.begin() + A.size() / 2;
        return merge( go({ A.begin(), pivot }), go({ pivot, A.end() }) );
    }

    Result merge( Result&& lhs, Result&& rhs )
    {
        Result res{ {}, lhs.count + rhs.count }; // left + right inversions
        auto L = lhs.A.begin(), R = rhs.A.begin();
        while( L != lhs.A.end() && R != rhs.A.end() )
            if( *L < *R )
                res.A.push_back( *L++ );
            else
                res.A.push_back( *R++ ),
                res.count += distance( L, lhs.A.end() ); // split inversions
        res.A.insert( res.A.end(), L, lhs.A.end() ), res.A.insert( res.A.end(), R, rhs.A.end() ); // append leftovers ( if applicable )
        return res;
    }

};


int main()
{
    string line;
    stringstream stream{ Assignment::Input };
    Solution< size_t >::Collection A;
    for( size_t num{ 0 }; getline( stream, line ); A.push_back( num ) )
    {
        stringstream parser{ line };
        parser >> num;
    }
    Solution< size_t > s;
    cout << "answer: " << s.inversions( A ) << endl;

    // answer: 2407905288

    return 0;
}
