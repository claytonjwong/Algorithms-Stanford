<h1 id="knapsack">Knapsack</h1>
<a href="https://en.wikipedia.org/wiki/Huffman_coding">https://en.wikipedia.org/wiki/Huffman_coding</a>
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
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course3/huffman/documentation/huffman_01.png" />
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course3/huffman/documentation/huffman_02.png" />
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course3/huffman/documentation/huffman_03.png" />
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course3/huffman/documentation/huffman_04.png" />
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course3/huffman/documentation/huffman_05.png" />
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course3/huffman/documentation/huffman_06.png" />
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course3/huffman/documentation/huffman_07.png" />
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course3/huffman/documentation/huffman_08.png" />
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course3/huffman/documentation/huffman_09.png" />
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course3/huffman/documentation/huffman_10.png" />
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course3/huffman/documentation/huffman_11.png" />
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course3/huffman/documentation/huffman_12.png" />
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course3/huffman/documentation/huffman_13.png" />
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course3/huffman/documentation/huffman_14.png" />
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course3/huffman/documentation/huffman_15.png" />
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course3/huffman/documentation/huffman_16.png" />
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course3/huffman/documentation/huffman_17.png" />
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course3/huffman/documentation/huffman_18.png" />
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course3/huffman/documentation/huffman_19.png" />
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course3/huffman/documentation/huffman_20.png" />
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course3/huffman/documentation/huffman_21.png" />
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course3/huffman/documentation/huffman_22.png" />
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course3/huffman/documentation/huffman_23.png" />
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course3/huffman/documentation/huffman_24.png" />
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course3/huffman/documentation/huffman_25.png" />
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course3/huffman/documentation/huffman_26.png" />

<h2 id="solution">Solution</h2>
<pre>

    #include "input.hpp"
    #include <iostream>
    #include <sstream>
    #include <vector>
    #include <queue>
    
    
    using namespace std;
    
    
    template< typename Type >
    class Solution
    {
    public:
    
        using Cost = Type;
        using MinMax = pair< Cost, Cost >;
        using Depths = vector< size_t >;
    
        MinMax minMaxCodeSize( const string& input, MinMax minMax={0,0} )
        {
            Costs costs;
            istringstream stream{ input };
            for( string line; getline( stream, line ); )
            {
                Cost cost; istringstream parser{ line }; parser >> cost;
                costs.push( make_shared< Node >( cost ) );
            }
            if( costs.empty() )
                return{ 0,0 };
            while( costs.size() > 1 )
            {
                auto first{ costs.top() }; costs.pop();
                auto second{ costs.top() }; costs.pop();
                auto next = make_shared< Node >( first->cost + second->cost, first, second );
                costs.push( next );
            }
            auto root{ costs.top() };
            Depths D;
            go( root, D );
            auto[ min, max ] = minmax_element( D.begin(), D.end() );
            return{ *min, *max };
        }
    
    private:
    
        struct Node;
        using HNode = shared_ptr< Node >;
        struct Node
        {
            Cost cost; HNode left, right;
            Node( Cost cost, HNode left={}, HNode right={} ) : cost{ cost }, left{ left }, right{ right } {}
        };
        struct Compare{ bool operator()( HNode& lhs, HNode& rhs ){ return lhs->cost > rhs->cost; } };
        using Costs = priority_queue< HNode, vector< HNode >, Compare >;
    
        void go( HNode root, Depths& D, int depth=0 )
        {
            if( ! root->left && ! root->right )
                D.push_back( depth );
            if( root->left )
                go( root->left, D, depth + 1 );
            if( root->right )
                go( root->right, D, depth + 1 );
        }
    
    };
    
    
    int main()
    {
        using Type = int;
    
        Solution< Type > s;
        auto[ min, max ] = s.minMaxCodeSize( Assignment1::Input );
        cout << "answer 1: " << max << endl << endl
             << "answer 2: " << min << endl << endl;
    
    //    answer 1: 19
    
    //    answer 2: 9
    
        return 0;
    }

</pre>

<h2 id="build">Build Instructions</h2>
<p>Use <code>cmake</code> to build this project:</p>

<pre>
    cmake --build cmake-build-debug --target huffman -- -j 4
</pre>

<h2 id="dependencies">Dependencies</h2>
<ul>
  <li>
    <a href="https://cmake.org/">cmake.org</a>
  </li>
</ul>

</body>
</html>