/*

In this programming problem and the next you'll code up the knapsack algorithm from lecture.

Let's start with a warm-up. Download the text file below.

This file describes a knapsack instance, and it has the following format:

[knapsack_size][number_of_items]

[value_1] [weight_1]

[value_2] [weight_2]

...

For example, the third line of the file is "50074 659",
indicating that the second item has value 50074 and size 659, respectively.

You can assume that all numbers are positive. You should assume that item weights and the knapsack capacity are integers.

In the box below, type in the value of the optimal solution.

ADVICE: If you're not getting the correct answer, try debugging your algorithm using some small test cases.
And then post them to the discussion forum!

*/


#include "input.hpp"
#include <iostream>
#include <sstream>
#include <vector>
#include <unordered_map>


using namespace std;
using Type = int;
using Value = Type;
using Cost = Type;
using Item = pair< Value, Cost >;
using Items = vector< Item >;
using VT = vector< Type >;
using VVT = vector< VT >;


class Solution
{
public:

    Value maxSack( Items& sack, Cost W )
    {
        auto N = sack.size();
        VVT dp( N+1, VT( W+1, 0 ) );
        for( auto i{ 1 }; i <= N; ++i )
            for( auto x{ 1 }; x <= W; ++x )
            {
                auto Vi = sack[ i-1 ].first;
                auto Wi = sack[ i-1 ].second;
                if( x < Wi )
                    dp[ i ][ x ] = dp[ i-1 ][ x ];
                else
                    dp[ i ][ x ] = max( dp[ i-1 ][ x ], dp[ i-1 ][ x-Wi ] + Vi );
            }
        return dp[ N ][ W ];
    }
};


int main()
{
    Solution solution;
    Items sack;
    Cost capacity{ 0 }, cost{ 0 };
    Value value{ 0 };
    istringstream stream{ Assignment1::Input };
    for( string line; getline( stream, line ); )
    {
        istringstream parser{ line };
        if( capacity > 0 )
            parser >> value >> cost,
            sack.push_back({ value, cost });
        else
            parser >> capacity;
    }
    cout << "answer: " << solution.maxSack( sack, capacity ) << endl;

    // answer: 2493893

    return 0;
}
