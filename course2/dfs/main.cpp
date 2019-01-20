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
    using Stack = vector< Vertex >;

    Seen dfs( const Graph& G, Vertex start=0 )
    {
        Stack stack{ start }; Seen seen{ start };
        while( ! stack.empty() )
        {
            auto cur{ stack.back() }; stack.pop_back(); // (cur)rent top of the stack
            for( const auto adj: G[ cur ] )             // (adj)acent neighbor vertices
                if( seen.insert( adj ).second )
                    stack.push_back( adj );
        }
        return seen;
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