#include "input.hpp"
#include <iostream>
#include <sstream>
#include <vector>



using namespace std;


template< typename Type >
class Solution
{
public:

    static constexpr size_t N{ 1000 };
    using Cost = Type;
    using Vertex = size_t;
    using Graph = vector< Cost >;
    using Iter = typename vector< Cost >::iterator;

    Graph max_indep_set( Graph G )
    {
        if( G.size() < 2 )
            return G;
        Graph maxIS;
        go( G, G.end(), maxIS );
        return maxIS;
    }

private:

    Cost go( Cost& C, Iter it )
    {
        auto n = distance( C.begin(), it );
        auto Vn{ it - 1 };
        if( n == 1 )
            return *Vn;
        if( n == 2 )
            return max( *Vn, *( Vn-1 ) );
        auto S1 = go( C, Vn ),
             S2 = go( C, Vn-1 ) + *Vn;
        return max( S1, S2 );
    }
};

int main()
{
    using Type = size_t;

    Solution< Type >::Graph G;

    stringstream stream{ Assignment3::Input };
    for( string line; getline( stream, line ); )
    {
        stringstream parser{ line };
        Solution< Type >::Cost cost{ 0 };
        parser >> cost;
        G.push_back( cost );
    }


    return 0;
}
