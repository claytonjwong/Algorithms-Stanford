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
    using Queue = queue< Vertex >;

    Seen bfs( const Graph& G, Vertex start=0 )
    {
        Queue q{{ start }}; Seen seen{ start };
        while( ! q.empty() )
        {
            auto cur{ q.front() }; q.pop(); // (cur)rent front of the queue
            for( const auto adj: G[ cur ] ) // (adj)acent neighbor vertices
                if( seen.insert( adj ).second )
                    q.push( adj );
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
    auto result = s.bfs( G );

    return 0;
}