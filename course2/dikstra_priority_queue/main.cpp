#include "input.hpp"
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <vector>
#include <queue>
#include <sstream>
#include <fstream>


using namespace std;


class Solution
{
public:

    using Vertex = unsigned int;
    using Weight = size_t;
    static const size_t N{ 200 };
    static const size_t Infinity = numeric_limits< Weight >::max();
    using VertexWeight = pair< Vertex, Weight >;
    struct Edge
    {
        Vertex tail{ 0 }, head{ 0 };
        bool operator==( const Edge& rhs ) const { return tail == rhs.tail && head == rhs.head; }
    };
    struct Hash{ Weight operator()( const Edge& e ) const { return ( N+1 ) * e.tail + e.head; } };
    using Edges = unordered_map< Edge, Weight, Hash >;
    using Vertices = unordered_set< Vertex >;
    using MinWeight = unordered_map< Vertex, Weight >;
    using AdjacencyList = unordered_set< Vertex >;
    using Graph = unordered_map< Vertex, AdjacencyList >;
    struct Compare{ bool operator()( const VertexWeight& lhs, const VertexWeight& rhs ) const { return lhs.second > rhs.second; } };
    using Queue = priority_queue< VertexWeight, vector< VertexWeight >, Compare >;
    using Parent = unordered_map< Vertex, Vertex >;

    Graph generateGraph( const Vertices& V, const Edges& E, Graph G={} )
    {
        for( auto& vertex: V )
            G[ vertex ] = {};
        for( auto& pair: E )
        {
            auto edge{ pair.first };
            G[ edge.tail ].insert( edge.head );
        }
        return G;
    }

    pair< MinWeight, Parent > getShortestPaths( Graph& G, Edges& E, Vertex start, Queue q={}, MinWeight W={}, Parent P={} )
    {
        for( auto& pair: G )
        {
            auto vertex{ pair.first };
            W[ vertex ] = Infinity;
        }
        W[ start ] = 0;
        for( q.push({ start, W[ start ] }); ! q.empty(); q.pop() )
        {
            auto tail{ q.top().first };
            auto weight{ q.top().second };
            for( auto& head: G[ tail ] )
            {
                Edge edge{ tail, head };
                auto candidate = weight + E[ edge ];
                if( W[ head ] > candidate )
                    W[ head ] = candidate,
                    P[ head ] = tail,
                    q.push({ head, W[ head ] });
            }
        }
        return { W, P };
    }

    Edges readInput( const string& input, Edges edges={}, Vertex tail=0, Vertex head=0, char comma=',', Weight weight=0 )
    {
        istringstream stream{ input };
        for( string line; getline( stream, line ); )
        {
            stringstream parser{ line };
            parser >> tail;
            while( parser >> head >> comma >> weight )
                edges.insert({ { tail, head }, weight });
        }
        return edges;
    }

};



int main()
{
    Solution s;
    Solution::Vertices V{ 1,2,3,4 };
    Solution::Edges E{
        { {1,2}, 1 },
        { {1,3}, 4 },
        { {2,3}, 2 },
        { {2,4}, 6 },
        { {3,4}, 3 },
    };
    auto G = s.generateGraph( V, E );
    auto[ W, P ] = s.getShortestPaths( G, E, 1 );

    V.clear();
    for( size_t vertex{ 1 }; vertex <= 200; ++vertex )
        V.insert( vertex );
    E.clear();
    E = s.readInput( INPUT );
    G.clear();
    G = s.generateGraph( V, E );
    auto[ W2, P2 ] = s.getShortestPaths( G, E, 1 );

    for( auto vertex: { 7,37,59,82,99,115,133,165,188,197 } ) // 2599,2610,2947,2052,2367,2399,2029,2442,2505,3068
        cout << W2[ vertex ] << ",";
    cout << endl;

    return 0;
}
