<h1 id="kosaraju_rec">Kosaraju ( DFS + DFS - Recursive )</h1>
<a href="https://en.wikipedia.org/wiki/Kosaraju%27s_algorithm">https://en.wikipedia.org/wiki/Kosaraju%27s_algorithm</a>
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
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course2/kosaraju_itr/documentation/scc_01.png" />
<hr/>
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course2/kosaraju_itr/documentation/scc_02.png" />
<hr/>
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course2/kosaraju_itr/documentation/scc_03.png" />
<hr/>
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course2/kosaraju_itr/documentation/scc_04.png" />
<hr/>
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course2/kosaraju_itr/documentation/scc_05.png" />
<hr/>
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course2/kosaraju_itr/documentation/scc_06.png" />
<hr/>
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course2/kosaraju_itr/documentation/scc_07.png" />
<hr/>
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course2/kosaraju_itr/documentation/scc_08.png" />
<hr/>
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course2/kosaraju_itr/documentation/scc_09.png" />
<hr/>
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course2/kosaraju_itr/documentation/scc_10.png" />
<hr/>
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course2/kosaraju_itr/documentation/scc_11.png" />
<hr/>
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course2/kosaraju_itr/documentation/scc_12.png" />
<hr/>
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course2/kosaraju_itr/documentation/scc_13.png" />
<hr/>
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course2/kosaraju_itr/documentation/scc_14.png" />
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
        using AdjacencyList = unordered_set< Vertex >;
        using Graph = unordered_map< Vertex, AdjacencyList >;
        using Seen = unordered_set< Vertex >;
        using ConnectedComponents = vector< vector< Vertex > >;
        using OrderedList = vector< Vertex >;
        using Queue = queue< Vertex >;
    
        ConnectedComponents getSCC( Graph& G, ConnectedComponents CC={}, Seen seen={} )
        {
            auto L = topo_sort( reverse( G ) );
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
    
        OrderedList topo_sort( Graph&& G, Seen seen={} )
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
    
    int main()
    {
        Solution s;
        Solution::Graph G;
        for( auto& test: { TEST_CASE_0, TEST_CASE_1, TEST_CASE_2, TEST_CASE_3, TEST_CASE_4, TEST_CASE_5, TEST_CASE_6, TEST_CASE_7 } )
        {
            G.clear();
            auto tail{ 0 }, head{ 0 };
            stringstream input{ test };
            for( string line; getline( input, line ); G[ tail ].insert( head ) )
            {
                stringstream parser{ line }; parser >> tail >> head;
                if( G.find( tail ) == G.end() )
                    G[ tail ] = {};
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

</pre>

<h2 id="build">Build Instructions</h2>
<p>Use <code>cmake</code> to build this project:</p>

<pre>
    cmake --build cmake-build-debug --target kosaraju_rec -- -j 4
</pre>

<h2 id="dependencies">Dependencies</h2>
<ul>
  <li>
    <a href="https://cmake.org/">cmake.org</a>
  </li>
</ul>

</body>
</html>