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

    Cost max_independent_set( Graph G )
    {
        if( G.empty() )
            return 0;
        else
        if( G.size() == 1 )
            return *G.begin();
        else
            return go( G, G.end() );
    }

private:

    Cost go( Graph& G, Iter end )
    {
        auto n = distance( G.begin(), end );
        if( n == 0 )
            return 0;
        auto Vn{ end-1 };
        if( n == 1 )
            return *Vn;
        auto S1 = go( G, Vn ),
             S2 = go( G, Vn-1 ) + *Vn;
        return max( S1, S2 );
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
    auto cost = s.max_independent_set( G );
    cout << cost << endl;

    return 0;
}
