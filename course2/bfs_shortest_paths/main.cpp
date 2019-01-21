#include <iostream>
#include <vector>
#include <unordered_set>
#include <queue>
#include <limits>


using namespace std;


class Solution
{
public:

    using Vertex = size_t;
    using Graph = vector< vector< Vertex > >;
    using Seen = unordered_set< Vertex >;
    using Queue = queue< Vertex >;
    using MinPathSize = vector< Vertex >;
    const Vertex maximum = numeric_limits< int >::max();

    MinPathSize bfs( const Graph& G, Vertex start=0 )
    {
        auto N{ G.size() }; MinPathSize P( N, maximum ); P[ start ] = 0;   // augmented-bfs
        Queue q{{ start }}; Seen seen{ start };
        while( ! q.empty() )
        {
            auto cur{ q.front() }; q.pop(); // (cur)rent front of the queue
            for( const auto adj: G[ cur ] ) // (adj)acent neighbor vertices
                if( seen.insert( adj ).second )
                    P[ adj ] = P[ cur ] + 1,                               // augmented-bfs
                    q.push( adj );
        }
        return P;
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
    cout << "shortest path size from start ( 0 ) to each vertex 0,1,2,3,4,5..." << endl;
    copy( result.cbegin(), result.cend(), ostream_iterator< Solution::Vertex >( cout, ",") );

    return 0;
}