<h1 id="topo_sort_bfs">Topological Sort ( BFS - Iterative Pruning )</h1>
<a href="https://en.wikipedia.org/wiki/Breadth-first_search">https://en.wikipedia.org/wiki/Breadth-first_search</a>
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
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course2/bfs/documentation/bfs_01.png" />
<hr/>
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course2/bfs/documentation/bfs_02.png" />
<hr/>
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course2/bfs/documentation/bfs_03.png" />
<hr/>
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course2/bfs/documentation/bfs_04.png" />
<hr/>
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course2/bfs/documentation/bfs_05.png" />
<hr/>
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course2/bfs/documentation/bfs_06.png" />
<hr/>
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course2/bfs/documentation/bfs_07.png" />
<hr/>


<h2 id="solution">Solution</h2>
<pre>

    #include <iostream>
    #include <unordered_map>
    #include <unordered_set>
    #include <set>
    #include <vector>
    #include <queue>
    
    
    using namespace std;
    
    
    class Solution
    {
    public:
    
        using Vertex = unsigned char;
        using AdjacencyList = unordered_set< Vertex >;
        struct AdjacentRelations{ AdjacencyList parent, children; };
        using Graph = unordered_map< Vertex, AdjacentRelations >;
        using Seen = unordered_set< Vertex >;
        using OrderedList = vector< Vertex >;
        using Queue = queue< Vertex >;
    
        OrderedList topo_sort( Graph G, OrderedList L={}, Queue q={}, Seen seen={} )
        {
            for( auto& pair: G ) // initialize (q)ueue to contains all vertices without parents
            {
                auto vertex{ pair.first };
                auto parent{ pair.second.parent };
                if( parent.empty() && seen.insert( vertex ).second )
                    q.push( vertex );
            }
            for( Vertex cur; ! q.empty(); q.pop() ) // pruning (q)ueue contains seen vertices without parents
            {
                cur = q.front(), L.push_back( cur );
                for( auto child: G[ cur ].children )
                {
                    G[ child ].parent.erase( cur );
                    if( G[ child ].parent.empty() && seen.insert( child ).second )
                        q.push( child );
                }
            }
            for( auto& pair: G ) // append remaining vertices onto the end of the list in arbitrary order since these vertices form a cycle
            {
                auto vertex{ pair.first };
                if( seen.insert( vertex ).second )
                    L.push_back( vertex );
            }
            return L;
        }
    
    };
    
    int main()
    {
        //
        // graph from Quiz 8.3 on page 45 of Algorithms Illuminated: Part 2
        //
        Solution::Graph G{
            { '1', { { '3' }, { '2' } } },
            { '2', { { '1' }, { '3' } } },
            { '3', { { '2', '4' }, { '4' } } },
            { '4', { { '3' }, { '3', '5', '6' } } },
            { '5', { {     }, { '4' } } },
            { '6', { { '4', '8' }, { '4', '7' } } },
            { '7', { { '6' }, { '8' } } },
            { '8', { { '7' }, { '6' } } },
        };
        Solution s;
        auto list = s.topo_sort( G );
        copy( list.cbegin(), list.cend(), ostream_iterator< Solution::Vertex >( cout, " " ) );
    
        return 0;
    }

</pre>

<h2 id="build">Build Instructions</h2>
<p>Use <code>cmake</code> to build this project:</p>

<pre>
    cmake --build cmake-build-debug --target topo_sort_prune_bfs -- -j 4
</pre>

<h2 id="dependencies">Dependencies</h2>
<ul>
  <li>
    <a href="https://cmake.org/">cmake.org</a>
  </li>
</ul>

</body>
</html>