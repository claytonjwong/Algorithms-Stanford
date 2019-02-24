/**
 *
 * Modern C++ implementation of 2-satisfiability constraint satisfaction problem solved in polynomial asymptotic runtime
 * via randomized Papadimitriou local search algorithm
 *
 * (c) Copyright 2019 Clayton J. Wong ( http://www.claytonjwong.com )
 *
 **/


#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <random>


using namespace std;
using Type = int;
struct Literal
{
    Type value{ 0 };
    bool assignment{ true }, constraint{ true };
};
struct Clause
{
    Literal first, second;
    bool isSatisfied(){ return( first.assignment == first.constraint ) || ( second.assignment == second.constraint ); }
};
using ClauseList = vector< Clause >;


class Solution
{
public:

    bool isSatisfiable( ClauseList& clauseList )
    {
        return true;
    }

};


using RandomDevice = random_device;
using Generator = mt19937;
using Distribution = uniform_int_distribution< bool >;
bool randomAssignment( RandomDevice randomDevice=RandomDevice() )
{
    Generator randomGenerator{ randomDevice() };
    Distribution distribution{ true, false };
    return distribution( randomGenerator );
}


ClauseList readInput( const string& filename, ClauseList clauseList={} )
{
    fstream stream{ filename };
    auto N{ 0 };
    for( string line; getline( stream, line ); )
    {
        istringstream parser{ line };
        if( N > 0 )
        {
            Clause clause{ {0,true},{0,true} };
            parser >> clause.first.value >> clause.second.value;
            if( clause.first.value < 0 )
                clause.first.value *= -1,
                clause.first.constraint = false;
            if( clause.second.value < 0 )
                clause.second.value *= -1,
                clause.second.constraint = false;
            clause.first.assignment = randomAssignment();
            clause.second.assignment = randomAssignment();
            continue;
        }
        parser >> N;
    }
    return clauseList;
}


int main()
{
    Solution solution;
    string ans;
    for( auto& filename: { "lecture.txt" } )
    {
        auto clauseList = readInput( filename );
        auto ok = solution.isSatisfiable( clauseList );
        ans.push_back( ok? '1': '0' );
        
    }

    cout << "answer: " << ans << endl;

    return 0;
}
