/**
 *
 * Modern C++ implementation of Bellman-Ford algorithm to find the single-source shortest paths in a graph
 *
 * (c) Copyright 2019 Clayton J. Wong ( http://www.claytonjwong.com )
 *
 **/


#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>


using namespace std;
using Integer = long long;
using VI = vector< Integer >;
using VVI = vector< VI >;
using Vertex = Integer;
using Cost = Integer;
static const Integer N{ 200 };
static const Cost Infinity = numeric_limits< Cost >::max();
using VertexCost = pair< Vertex, Cost >;
struct Edge
{
    Vertex tail{ 0 }, head{ 0 };
    bool operator==( const Edge& rhs ) const { return tail == rhs.tail && head == rhs.head; }
};
struct Hash{ Cost operator()( const Edge& e ) const { return ( N+1 ) * e.tail + e.head; } };
using Edges = unordered_map< Edge, Cost, Hash >;
using Vertices = unordered_set< Vertex >;
using MinCost = unordered_map< Vertex, Cost >;
using AdjacencyList = unordered_set< Vertex >;
using Graph = unordered_map< Vertex, AdjacencyList >;


namespace TopDown
{
    class Solution
    {
    public:

        VVI getShortestPaths( )
        {
            VVI memo;
            go();
            return memo;
        }

    private:

        void go()
        {

        }

    }; // class Solution

} // namespace TopDown


namespace BottomUp
{
    class Solution
    {
    public:

        VVI getShortestPaths( )
        {
            VVI dp;
            return dp;
        }

    }; // class Solution

} // namespace BottomUp


int main()
{


    return 0;
}