<h1 id="bfs">Minimum Path Distances ( BFS )</h1>
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
    #include <vector>
    #include <unordered_map>
    #include <unordered_set>
    #include <map>
    #include <queue>
    #include <limits>
    
    
    using namespace std;
    
    
    class Solution
    {
    public:
    
        using Vertex = unsigned char;
        using AdjacencyList = vector< Vertex >;
        using Graph = unordered_map< Vertex, AdjacencyList >;
        using Seen = unordered_set< Vertex >;
        using Queue = queue< Vertex >;
        using Distance = map< Vertex, size_t >;
    
        Distance bfs( Graph& G, Vertex start='s' )
        {
            Distance D{{ start, 0 }};               // augmented-BFS
            Queue q{{ start }};
            Seen seen{ start };
            while( ! q.empty() )
            {
                auto cur{ q.front() }; q.pop();
                for( auto adj: G[ cur ] )
                    if( seen.insert( adj ).second )
                        D[ adj ] = D[ cur ] + 1,    // augmented-BFS
                        q.push( adj );
            }
            return D;
        }
    
    };
    
    ostream& operator<<( ostream& stream, const Solution::Distance& distance )
    {
        for( auto pair: distance )
        {
            stream << "distance to " << pair.first << " = " << pair.second << endl;
        }
        return stream;
    }
    
    int main()
    {
        //
        // Figure 8.5 from page 26 of Algorithms Illuminated ( Part 2 )
        //
        Solution::Graph G = {
    
            { 's', { 'a', 'b' } },
    
            { 'a', { 's', 'c' } },
    
            { 'b', { 's', 'c' } },
    
            { 'c', { 'a', 'b', 'd', 'e' } },
    
            { 'd', { 'b', 'c', 'e' } },
    
            { 'e', { 'c', 'd', } }
    
        };
        Solution solution;
        auto s = solution.bfs( G, 's' );
        auto a = solution.bfs( G, 'a' );
        auto b = solution.bfs( G, 'b' );
        auto c = solution.bfs( G, 'c' );
        auto d = solution.bfs( G, 'd' );
        auto e = solution.bfs( G, 'e' );
        cout << "starting from 's': " << endl << s << endl << endl;
        cout << "starting from 'a': " << endl << a << endl << endl;
        cout << "starting from 'b': " << endl << b << endl << endl;
        cout << "starting from 'c': " << endl << c << endl << endl;
        cout << "starting from 'd': " << endl << d << endl << endl;
        cout << "starting from 'e': " << endl << e << endl << endl;
    
        return 0;
    }

</pre>

<h2 id="build">Build Instructions</h2>
<p>Use <code>cmake</code> to build this project:</p>

<pre>
    cmake --build cmake-build-debug --target bfs_min_path_dist -- -j 4
</pre>

<h2 id="dependencies">Dependencies</h2>
<ul>
  <li>
    <a href="https://cmake.org/">cmake.org</a>
  </li>
</ul>

</body>
</html>