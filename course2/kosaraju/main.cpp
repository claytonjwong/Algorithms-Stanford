#include "input.hpp"
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <vector>
#include <queue>
#include <sstream>


using namespace std;


class Solution
{
public:

    using Vertex = unsigned int;
    using AdjacencyList = vector< Vertex >;
    using Graph = unordered_map< Vertex, AdjacencyList >;
    using Seen = unordered_set< Vertex >;
    using ConnectedComponents = vector< vector< Vertex > >;
    using OrderedList = vector< Vertex >;
    using Queue = queue< Vertex >;

    ConnectedComponents getSCC( Graph& G, ConnectedComponents CC={}, Seen seen={} )
    {
        auto R = reverse( G );           // (R)eversed (G)raph
        auto L = topo_sort( R );
        for( auto cur: L )               // L is the reverse topological order of R
            if( seen.insert( cur ).second )
                CC.push_back( {} ),
                dfs( CC, R, cur, seen ); // coalesce (cur)rent vertex into a new (C)onnected (C)omponent
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
                R[ adj ].push_back( cur );
        }
        return R;
    }

    OrderedList topo_sort( Graph& G, Seen visiting={}, Seen visited={} )
    {
        OrderedList L;

        // TODO: write working TopoSort implementation on directed cyclic graphs,
        //       5 should be the first in the reverse ordered list, because its a "sink"
/*

            1 ----> 2 ----> 3
              <---- | <----
                    |
                    V
                    5

*/
        // TODO: check pseudocode for TopoSort ( pg 50 ) and Kosaraju ( pg 62 ) and re-write code verbatim?

        // TODO: if above doesn't work, maybe look for functional implementations to see why test case #5 isn't topologically sorted as expected

        return L;
    }

};

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

    for( auto& test: { TEST_CASE_4 } ) //TEST_CASE_1, TEST_CASE_2, TEST_CASE_3, TEST_CASE_4, TEST_CASE_5
    {
        G.clear();
        auto u{ 0 }, v{ 0 };
        stringstream input{ test };
        for( string line; getline( input, line ); G[ u ].push_back( v ) )
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
