<h1 id="min_cut">Karger Minimum Cut ( Randomized Edge Contractions )</h1>
<a href="https://en.wikipedia.org/wiki/Karger%27s_algorithm">https://en.wikipedia.org/wiki/Karger%27s_algorithm</a>
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
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course1/karger_min_cut/documentation/karger_01.png" />
<hr/>
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course1/karger_min_cut/documentation/karger_02.png" />
<hr/>
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course1/karger_min_cut/documentation/karger_03.png" />
<hr/>
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course1/karger_min_cut/documentation/karger_04.png" />
<hr/>
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course1/karger_min_cut/documentation/karger_05.png" />
<hr/>
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course1/karger_min_cut/documentation/karger_06.png" />
<hr/>
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course1/karger_min_cut/documentation/karger_07.png" />
<hr/>
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course1/karger_min_cut/documentation/karger_08.png" />
<hr/>
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course1/karger_min_cut/documentation/karger_09.png" />
<hr/>
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course1/karger_min_cut/documentation/karger_10.png" />
<hr/>
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course1/karger_min_cut/documentation/karger_11.png" />
<hr/>
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course1/karger_min_cut/documentation/karger_12.png" />
<hr/>
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course1/karger_min_cut/documentation/karger_13.png" />
<hr/>
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course1/karger_min_cut/documentation/karger_14.png" />
<hr/>
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course1/karger_min_cut/documentation/karger_15.png" />
<hr/>
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course1/karger_min_cut/documentation/karger_16.png" />
<hr/>
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course1/karger_min_cut/documentation/karger_17.png" />
<hr/>
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course1/karger_min_cut/documentation/karger_18.png" />
<hr/>
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course1/karger_min_cut/documentation/karger_19.png" />
<hr/>
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course1/karger_min_cut/documentation/karger_20.png" />
<hr/>
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course1/karger_min_cut/documentation/karger_21.png" />
<hr/>
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course1/karger_min_cut/documentation/karger_22.png" />
<hr/>
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course1/karger_min_cut/documentation/karger_23.png" />
<hr/>
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course1/karger_min_cut/documentation/karger_24.png" />
<hr/>
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course1/karger_min_cut/documentation/karger_25.png" />
<hr/>
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course1/karger_min_cut/documentation/karger_26.png" />
<hr/>
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course1/karger_min_cut/documentation/karger_27.png" />
<hr/>
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course1/karger_min_cut/documentation/karger_28.png" />
<hr/>

<h2 id="solution">Solution</h2>
<pre>

    /*
    
    Download the text file here (http://bit.ly/1CRWhtL)
    The file contains the adjacency list representation of a
    simple undirected graph. There are 200 vertices labeled 1 to 200.
    
    The first column in the file represents the vertex label,
    and the particular row (other entries except the first column)
    tells all the vertices that the vertex is adjacent to.
    
    So for example, the 6th row looks like : "6	155	56	52	120	...".
    This just means that the vertex with label 6 is adjacent to
    (i.e., shares an edge with) the vertices with labels
    155,56,52,120,......,etc
    
    Your task is to code up and run the randomized contraction algorithm
    for the min cut problem and use it on the above graph to compute the
    min cut (i.e., the minimum-possible number of crossing edges).
    
    (HINT: Note that you'll have to figure out an implementation of
    edge contractions. Initially, you might want to do this naively,
    creating a new graph from the old every time there's an edge contraction.
    But you should also think about more efficient implementations.)
    
    (WARNING: As per the video lectures, please make sure to run the
    algorithm many times with different random seeds, and remember the
    smallest cut that you ever find.)
    
    */
    
    
    #include "input.hpp"
    #include <iostream>
    #include <vector>
    #include <set>
    #include <map>
    #include <unordered_map>
    #include <random>
    #include <sstream>
    
    
    using namespace std;
    
    
    class Solution
    {
    public:
    
        using Vertex = int;
        using AdjacencyList = multiset< Vertex >;
        using Graph = unordered_map< Vertex, AdjacencyList >;
        struct Edge{ Vertex tail{ 0 }, head{ 0 }; };
    
        int getMinCut( Graph G ) // assume (G)raph is connected undirected with at least one edge and two vertices
        {
            for( Edge edge; G.size() > 2; contractEdge( G, edge ) )
                edge = randomEdge( G );
            return G.cbegin()->second.size();
        }
    
    private:
    
        using RandomDevice = random_device;
        using Generator = mt19937;
        using Distribution = uniform_int_distribution< int >;
    
        int randomVertex( Vertex begin, Vertex end, RandomDevice randomDevice=RandomDevice() )
        {
            Generator generator{ randomDevice() };
            Distribution distribution{ begin, end-1 }; // end-1, since end is non-inclusive
            return distribution( generator );
        }
    
        Edge randomEdge( Graph& G )
        {
            auto N = static_cast< Vertex >( G.size() ),
                 tail = next( G.cbegin(), randomVertex( 0, N ) )->first;
            auto M = static_cast< Vertex >( G[ tail ].size() ),
                 head = *next( G[ tail ].cbegin(), randomVertex( 0, M ) );
            return { tail, head };
        }
    
        void contractEdge( Graph& G, const Edge& edge )
        {
            auto head{ edge.head }, tail{ edge.tail };
            for( auto& adj: G[ tail ] )
            {
                if( adj == head )
                    continue; // avoid adding self-loop when coalescing tail's adj(acent) vertices into head
                G[ head ].insert( adj );
                G[ adj ].insert( head );
                G[ adj ].erase( tail );
            }
            G[ head ].erase( tail );
            G.erase( tail );
        }
    
    };
    
    
    int main()
    {
        Solution s;
        Solution::Graph G;
        stringstream stream{ Assignment::Input };
        for( string line; getline( stream, line ); )
        {
            stringstream parser{ line };
            auto vertex{ 0 };
            parser >> vertex;
            if( G.find( vertex ) == G.end() )
                G[ vertex ] = {};
            for( auto adj{ 0 }; parser >> adj; )
            {
                if( G.find( adj ) == G.end() )
                    G[ adj ] = {};
                if( G[ adj ].find( vertex ) == G[ adj ].end() ) // only insert each unique vertex once
                    G[ adj ].insert( vertex );
                if( G[ vertex ].find( adj ) == G[ vertex ].end() ) // only insert each unique (adj)acent vertex once
                    G[ vertex ].insert( adj );
            }
        }
    
        auto minCut = numeric_limits< int >::max();
        for( auto N{ 100 }; N--; minCut = min( minCut, s.getMinCut( G ) ) );
        cout << "minCut: " << minCut << endl;
    
        // minCut: 17
    
        return 0;
    }

</pre>

<h2 id="build">Build Instructions</h2>
<p>Use <code>cmake</code> to build this project:</p>

<pre>
    cmake --build cmake-build-debug --target karger_min_cut -- -j 4
</pre>

<h2 id="dependencies">Dependencies</h2>
<ul>
  <li>
    <a href="https://cmake.org/">cmake.org</a>
  </li>
</ul>

</body>
</html>