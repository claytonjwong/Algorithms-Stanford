#include "input.hpp"
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <vector>
#include <queue>
#include <sstream>
#include <fstream>


#define UNIT_TESTS 69 // comment this line to execute the large homework assignment instead of small unit tests


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
    using Queue = queue< Vertex >;

    ConnectedComponents getSCC( Graph& G, ConnectedComponents CC={}, Seen seen={} )
    {
        auto R = reverse( G );           // (R)eversed (G)raph
        auto L = topo_sort( R );
        for( auto cur: L )               // L is the topological order of (R)eversed (G)raph
            if( seen.insert( cur ).second )
                CC.push_back( {} ),
                dfs( CC, G, cur, seen ); // coalesce (cur)rent vertex as new (C)onnected (C)omponent of original (G)raph
        return CC;
    }

private:

    void dfs( ConnectedComponents& CC, Graph& G, Vertex cur, Seen& seen )
    {
        CC.back().push_back( cur );
        for( auto adj: G[ cur ] )
            if( seen.insert( adj ).second )
                dfs( CC, G, adj, seen );
    }

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

    OrderedList topo_sort( Graph& G, Seen seen={} )
    {
        auto N{ G.size() };
        OrderedList L( N + 1 );
        for( auto& pair: G )
        {
            auto cur{ pair.first };
            if( seen.insert( cur ).second )
                go( L, G, cur, N, seen );
        }
        return { L.cbegin() + 1, L.cend() }; // return buckets as 0-based index of [ 1 : N+1 )
    }

    void go( OrderedList& L, Graph& G, Vertex cur, // (cur)rent vertex at the top of the callstack
             size_t& N, Seen& seen )
    {
        for( auto adj: G[ cur ] )              // (adj)acent neighbor vertices of the (G)raph's (cur)rent vertex
            if( seen.insert( adj ).second )    // if this is the first time the (adj)acent neighbor vertex has been seen
                go( L, G, adj, N, seen );      // go further process (adj)acent neighbor vertex
        L[ N-- ] = cur;                        // update ordered-(L)ist entries in reverse order as the callstack returns from [ N : 1 ]
    }

};

#ifdef UNIT_TESTS
int main()
{
    //
    // graph from figure 8.8, page 35 of Algorithms Illuminated: Part 2
    //
    Solution::Graph G{
        { 1, { 3 } },
        { 2, { 4, 10 } },
        { 3, { 5, 11 } },
        { 4, { 7 } },
        { 5, { 1, 7, 9 } },
        { 6, { 10 } },
        { 7, { 9 } },
        { 8, { 6 } },
        { 9, { 2, 4, 8 } },
        { 10, { 8 } },
        { 11, { 6, 8 } },
    };
    Solution s;
    auto scc = s.getSCC( G );
    for( auto& test: { TEST_CASE_1, TEST_CASE_2, TEST_CASE_3, TEST_CASE_4, TEST_CASE_5, TEST_CASE_6, TEST_CASE_7 } )
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
    cout << "G.size() == " << G.size() << endl;
    auto CC = s.getSCC( G );
    cout << "CC.size() == " << CC.size() << endl;
    for( auto& component: CC )
        cout << "component.size() == " << component.size() << endl;

    return 0;
}
#endif
