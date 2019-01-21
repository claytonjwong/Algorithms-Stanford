#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <queue>


using namespace std;


class Solution
{
public:

    using Vertex = unsigned char;
    using AdjacencyList = vector< Vertex >;
    using Graph = unordered_map< Vertex, AdjacencyList >;
    using Seen = unordered_set< Vertex >;
    using Queue = queue< Vertex >;

    Seen bfs( Graph& G, Vertex start='s' )
    {
        Queue q{{ start }}; Seen seen{ start };
        while( ! q.empty() )
        {
            auto cur{ q.front() }; q.pop();     // (cur)rent front of the (q)ueue
            for( auto adj: G[ cur ] )           // (adj)acent neighbor vertices of the (G)raph's (cur)rent vertex
                if( seen.insert( adj ).second ) // if this is the first time the (adj)acent neighbor vertex has been seen
                    q.push( adj );              // push (adj)acent neighbor vertex onto (q)ueue for future processing
        }
        return seen;
    }
    
};

int main()
{
    //
    // Figure 8.5 from page 26 of Algorithms Illuminated: Part 2
    //
    Solution::Graph G = {

        { 's', { 'a', 'b' } },

        { 'a', { 's', 'c' } },

        { 'b', { 's', 'c' } },

        { 'c', { 'a', 'b', 'd', 'e' } },

        { 'd', { 'b', 'c', 'e' } },

        { 'e', { 'c', 'd', } }

    };
    Solution s;
    auto result = s.bfs( G );

    return 0;
}