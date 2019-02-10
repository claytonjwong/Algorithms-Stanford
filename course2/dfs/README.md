<h1 id="dfs">Depth First Search ( DFS - Iterative )</h1>
<a href="https://en.wikipedia.org/wiki/Depth-first_search">https://en.wikipedia.org/wiki/Depth-first_search</a>
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
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course2/dfs/documentation/dfs_01.png" />
<hr/>
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course2/dfs/documentation/dfs_02.png" />
<hr/>
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course2/dfs/documentation/dfs_03.png" />
<hr/>
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course2/dfs/documentation/dfs_04.png" />
<hr/>
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course2/dfs/documentation/dfs_05.png" />
<hr/>
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course2/dfs/documentation/dfs_06.png" />
<hr/>
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course2/dfs/documentation/dfs_07.png" />
<hr/>
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course2/dfs/documentation/dfs_08.png" />
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
        using Stack = vector< Vertex >;
    
        Seen dfs( Graph& G, Vertex start='s' )
        {
            Stack stack{ start }; Seen seen{ start };
            while( ! stack.empty() )
            {
                auto cur{ stack.back() }; stack.pop_back(); // (cur)rent vertex at the top of the stack
                for( auto adj: G[ cur ] )                   // (adj)acent neighbor vertices of the (G)raph's (cur)rent vertex
                    if( seen.insert( adj ).second )         // if this is the first time the (adj)acent neighbor vertex has been seen
                        stack.push_back( adj );             // push (adj)acent neighbor vertex onto stack for future processing
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
    cmake --build cmake-build-debug --target dfs -- -j 4
</pre>

<h2 id="dependencies">Dependencies</h2>
<ul>
  <li>
    <a href="https://cmake.org/">cmake.org</a>
  </li>
</ul>

</body>
</html>