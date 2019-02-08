#include "input.hpp"
#include <iostream>
#include <sstream>
#include <vector>
#include <unordered_map>


using namespace std;


template< typename Type >
class Solution
{
public:

    using Cost = Type;
    using Vertex = size_t;
    using Graph = vector< Cost >;
    using Iter = typename vector< Cost >::iterator;
    using Memo = unordered_map< size_t, Cost >;

    Cost max_independent_set( Graph G )
    {
        return go( G, G.end() );
    }

private:

    Cost go( Graph& G, Iter end, Memo&& memo={} )
    {
        auto n = distance( G.begin(), end );
        auto memoIt = memo.find( n );
        if( memoIt != memo.end() )
        {
            auto cost{ memoIt->second };
            return cost;
        }
        if( n == 0 )
            return memo[ n ] = 0;
        auto Vn{ end-1 };
        if( n == 1 )
            return memo[ n ] = *Vn;
        auto S1 = memo[ n ] = go( G, Vn, move( memo ) ),
             S2 = memo[ n ] = go( G, Vn-1, move( memo ) ) + *Vn;
        if( S1 > S2 )
            return S1;
        return S2;
    }

};


int main()
{
    using Type = size_t;

    Solution< Type > s;
    Solution< Type >::Graph G;

    stringstream stream{ Lecture::Input };
    for( string line; getline( stream, line ); )
    {
        stringstream parser{ line };
        Solution< Type >::Cost cost{ 0 };
        parser >> cost;
        G.push_back( cost );
    }
    cout << "cost: " << s.max_independent_set( G ) << endl;

    return 0;
}
