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
    
        Seen dfs( Graph& G, Vertex start='s' )
        {
            Seen seen{ start };
            go( G, start, seen );
            return seen;
        }
    
        void go( Graph& G, Vertex cur, Seen& seen ) // (cur)rent vertex at the top of the callstack
        {
            for( auto adj: G[ cur ] )               // (adj)acent neighbor vertices of the (G)raph's (cur)rent vertex
                if( seen.insert( adj ).second )     // if this is the first time the (adj)acent neighbor vertex has been seen
                    go( G, adj, seen );             // go further process (adj)acent neighbor vertex
        }
    
    };
    
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
        Solution s;
        auto result = s.dfs( G );
    
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