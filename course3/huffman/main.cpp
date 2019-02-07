/*

In this programming problem and the next you'll code up the greedy algorithm from the lectures on Huffman coding.

This file describes an instance of the problem. It has the following format:

[number_of_symbols]

[weight of symbol #1]

[weight of symbol #2]

...

For example, the third line of the file is "6852892," indicating that the weight of the second symbol
of the alphabet is 6852892. (We're using weights instead of frequencies, like in the "A More Complex Example" video.)

Your task in this problem is to run the Huffman coding algorithm from lecture on this data set.
What is the maximum length of a codeword in the resulting Huffman code?

ADVICE: If you're not getting the correct answer, try debugging your algorithm using some small test cases.
And then post them to the discussion forum!

*/


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
        while( costs.size() > 1 )
        {
            auto first{ costs.top() }; costs.pop();
            auto second{ costs.top() }; costs.pop();
            auto next = make_shared< Node >( first->cost + second->cost, first, second );
            costs.push( next );
        }
        if( costs.empty() )
            return{ 0,0 };
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
    struct Cmp{ bool operator()( HNode& lhs, HNode& rhs ){ return lhs->cost > rhs->cost; } };
    using Costs = priority_queue< HNode, vector< HNode >, Cmp >;

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
