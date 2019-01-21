#include <iostream>
#include <vector>
#include <unordered_set>
#include <queue>


using namespace std;


class Solution
{
public:

    using Vertex = size_t;
    using Graph = vector< vector< Vertex > >;
    using Seen = unordered_set< Vertex >;

    Seen dfs( const Graph& G, Vertex start=0 )
    {
        Seen seen{ start };
        go( G, start, seen );
        return seen;
    }

    void go( const Graph& G, Vertex cur, Seen& seen )
    {
        for( const auto adj: G[ cur ] )
            if( seen.insert( adj ).second )
                go( G, adj, seen );
    }

};

int main()
{
    //
    // Figure 8.5 from page 26 of Algorithms Illuminated ( Part 2 )
    //
    Solution::Graph G = {
        { 1, 2 },           // 0
        { 0, 3 },           // 1
        { 0, 3 },           // 2
        { 1, 2, 4, 5 },     // 3
        { 3 },              // 4
        { 3, 4 }            // 5
    };
    Solution s;
    auto result = s.dfs( G );

    return 0;
}