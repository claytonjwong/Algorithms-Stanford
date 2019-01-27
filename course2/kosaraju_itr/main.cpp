#include "input.hpp"
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <vector>
#include <sstream>
#include <fstream>


//#define UNIT_TESTS 69 // comment this line to execute the large homework assignment instead of small unit tests


using namespace std;


class Solution
{
public:

    using Vertex = unsigned int;
    using AdjacencyList = unordered_set< Vertex >;
    using Graph = unordered_map< Vertex, AdjacencyList >;
    using Seen = unordered_set< Vertex >;
    using ConnectedComponents = vector< vector< Vertex > >;
    using OrderedList = vector< Vertex >;
    using Stack = vector< Vertex >;

    ConnectedComponents getSCC( Graph& G, ConnectedComponents CC={}, Stack stack={}, Seen seen={} )
    {
        auto L = topo_sort( reverse( G ) );
        for( auto cur: L )
        {
            if( seen.insert( cur ).second )
                stack.push_back( cur );
            Stack path;
            while( ! stack.empty() )
            {
                auto start{ stack.back() }; stack.pop_back(); path.push_back( start );
                for( auto adj: G[ start ] )
                    if( seen.insert( adj ).second )
                        stack.push_back( adj );
            }
            if( ! path.empty() )
                CC.emplace_back( path );
        }
        return CC;
    }

private:

    Graph reverse( Graph& G )
    {
        Graph R( G ); // (R)eversed (G)raph: keep G's vertex keys ( pair.first ), but clear G's adjacency lists ( pair.second )
        for_each( R.begin(), R.end(), []( auto& pair ){ pair.second={}; });
        for( auto& pair: G )
        {
            auto cur{ pair.first };
            for( auto adj: G[ cur ] )
                R[ adj ].insert( cur );
        }
        return R;
    }

    OrderedList topo_sort( Graph&& G, Stack stack={}, Seen seen={} )
    {
        auto N{ G.size() };
        OrderedList L( N + 1 );
        for( auto& pair: G )
        {
            auto cur{ pair.first };
            if( seen.insert( cur ).second )
                stack.push_back( cur );
            Stack path;
            while( ! stack.empty() )
            {
                auto start{ stack.back() }; stack.pop_back(); path.push_back( start );
                for( auto adj: G[ start ] )
                    if( seen.insert( adj ).second )
                        stack.push_back( adj );
            }
            for(; ! path.empty(); L[ N-- ] = path.back(), path.pop_back() );
        }
        return { L.cbegin() + 1, L.cend() }; // return buckets as 0-based index of [ 1 : N+1 )
    }

};

#ifdef UNIT_TESTS
int main()
{
    Solution s;
    Solution::Graph G;
    for( auto& test: { TEST_CASE_0, TEST_CASE_1, TEST_CASE_2, TEST_CASE_3, TEST_CASE_4, TEST_CASE_5, TEST_CASE_6, TEST_CASE_7 } )
    {
        G.clear();
        auto u{ 0 }, v{ 0 };
        stringstream input{ test };
        for( string line; getline( input, line ); G[ u ].insert( v ) )
        {
            stringstream parser{ line }; parser >> u >> v;
            if( G.find( u ) == G.end() )
                G[ u ] = {};
        }
        auto result = s.getSCC( G );
        auto index{ 0 };
        for( auto& component: result )
        {
            cout << index++ << ": ";
            for( auto& vertex: component )
                cout << vertex << " ";
            cout << endl;
        }
        cout << endl;
    }

    return 0;
}
#else

void print_answer( const Solution::ConnectedComponents& CC )
{
    set< size_t, greater<int> > sizes;
    for( auto& C: CC )
        sizes.insert( C.size() );
    auto N{ 5 };
    for( auto it{ sizes.begin() }; N--; ++it )
        cout << *it << ",";
}

int main()
{
    Solution::Graph G;
    fstream stream{ "input.txt" };
    string line;
    while( getline( stream, line ) )
    {
        stringstream parser{ line };
        auto tail{ 0 }, head{ 0 };
        parser >> tail >> head;
        if( G.find( tail ) == G.end() )
            G[ tail ] = {};
        G[ tail ].insert( head );
    }
    Solution s;
    auto CC = s.getSCC( G );
    print_answer( CC );

    // answer: 434821,968,459,313,211

    return 0;
}
#endif
