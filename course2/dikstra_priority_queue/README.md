<h1 id="dikstra">Dikstra ( priority queue )</h1>
<a href="https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm">https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm</a>
<h2>Contents</h2>
<ul>
  <li>
      <a href="#slides">Lecture Slides</a>
  </li>
  <li>
    <a href="#solution">Solution</a>
  </li>
  <li>
    <a href="#build">Build Instructions</a>
  </li>
  <li>
    <a href="#dependencies">Dependencies</a>
  </li>
</ul>

<h2 id="slides">Lecture Slides</h2>
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course2/dikstra_priority_queue/documentation/dikstra_01.png" />
<hr/>
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course2/dikstra_priority_queue/documentation/dikstra_02.png" />
<hr/>
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course2/dikstra_priority_queue/documentation/dikstra_03.png" />
<hr/>
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course2/dikstra_priority_queue/documentation/dikstra_04.png" />
<hr/>
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course2/dikstra_priority_queue/documentation/dikstra_05.png" />
<hr/>
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course2/dikstra_priority_queue/documentation/dikstra_06.png" />
<hr/>
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course2/dikstra_priority_queue/documentation/dikstra_07.png" />
<hr/>
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course2/dikstra_priority_queue/documentation/dikstra_08.png" />
<hr/>
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course2/dikstra_priority_queue/documentation/dikstra_09.png" />
<hr/>
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course2/dikstra_priority_queue/documentation/dikstra_10.png" />
<hr/>
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course2/dikstra_priority_queue/documentation/dikstra_11.png" />
<hr/>
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course2/dikstra_priority_queue/documentation/dikstra_12.png" />
<hr/>
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course2/dikstra_priority_queue/documentation/dikstra_13.png" />
<hr/>
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course2/dikstra_priority_queue/documentation/dikstra_14.png" />
<hr/>
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course2/dikstra_priority_queue/documentation/dikstra_15.png" />
<hr/>
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course2/dikstra_priority_queue/documentation/dikstra_16.png" />
<hr/>
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course2/dikstra_priority_queue/documentation/dikstra_17.png" />
<hr/>
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course2/dikstra_priority_queue/documentation/dikstra_18.png" />
<hr/>
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course2/dikstra_priority_queue/documentation/dikstra_19.png" />
<hr/>
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course2/dikstra_priority_queue/documentation/dikstra_20.png" />
<hr/>
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course2/dikstra_priority_queue/documentation/dikstra_21.png" />
<hr/>

<h2 id="solution">Solution</h2>
<pre>

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
        using Cost = size_t;
        static const size_t N{ 200 };
        static const size_t Infinity = numeric_limits< Cost >::max();
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
        struct Compare{ bool operator()( const VertexCost& lhs, const VertexCost& rhs ) const { return lhs.second > rhs.second; } };
        using Queue = priority_queue< VertexCost, vector< VertexCost >, Compare >;
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
    
        pair< MinCost, Parent > getShortestPaths( Graph& G, Edges& E, Vertex start, Queue q={}, MinCost C={}, Parent P={} )
        {
            for( auto& pair: G )
            {
                auto vertex{ pair.first };
                C[ vertex ] = Infinity;
            }
            C[ start ] = 0;
            for( q.push({ start, C[ start ] }); ! q.empty(); q.pop() )
            {
                auto tail{ q.top().first };
                auto cost{ q.top().second };
                for( auto& head: G[ tail ] )
                {
                    Edge edge{ tail, head };
                    auto candidate = cost + E[ edge ];
                    if( C[ head ] > candidate )
                        C[ head ] = candidate,
                        P[ head ] = tail,
                        q.push({ head, C[ head ] });
                }
            }
            return { C, P };
        }
    
        Edges readInput( const string& input, Edges edges={}, Vertex tail=0, Vertex head=0, char comma=',', Cost cost=0 )
        {
            istringstream stream{ input };
            for( string line; getline( stream, line ); )
            {
                stringstream parser{ line };
                parser >> tail;
                while( parser >> head >> comma >> cost )
                    edges.insert({ { tail, head }, cost });
            }
            return edges;
        }
    
    };
    
    
    int main()
    {
        Solution s;
        Solution::Vertices V;
        for( size_t vertex{ 1 }; vertex <= 200; ++vertex )
            V.insert( vertex );
        auto E = s.readInput( INPUT );
        auto G = s.generateGraph( V, E );
        auto[ C, P ] = s.getShortestPaths( G, E, 1 );
        for( auto vertex: { 7,37,59,82,99,115,133,165,188,197 } ) // 2599,2610,2947,2052,2367,2399,2029,2442,2505,3068
            cout << C[ vertex ] << ",";
        cout << endl;
    
        return 0;
    }

</pre>

<h2 id="build">Build Instructions</h2>
<p>Use <code>cmake</code> to build this project:</p>

<pre>
    cmake --build cmake-build-debug --target dikstra_priority_queue -- -j 4
</pre>

<h2 id="dependencies">Dependencies</h2>
<ul>
  <li>
    <a href="https://cmake.org/">cmake.org</a>
  </li>
</ul>

</body>
</html>