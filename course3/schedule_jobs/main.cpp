/*

In this programming problem and the next you'll code up the greedy algorithms
from lecture for minimizing the weighted sum of completion times

This file describes a set of jobs with positive and integral weights and lengths. It has the format

[number_of_jobs]

[job_1_weight] [job_1_length]

[job_2_weight] [job_2_length]

...

For example, the third line of the file is "74 59", indicating that the second job has weight 74 and length 59.

You should NOT assume that edge weights or lengths are distinct.

Your task in this problem is to run the greedy algorithm that schedules jobs
 in decreasing order of the difference (weight - length). Recall from lecture that this algorithm
 is not always optimal. IMPORTANT: if two jobs have equal difference (weight - length),
 you should schedule the job with higher weight first. Beware: if you break ties in a different way,
 you are likely to get the wrong answer. You should report the sum of weighted completion times
 of the resulting schedule --- a positive integer --- in the box below.

ADVICE: If you get the wrong answer, try out some small test cases to debug your algorithm
(and post your test cases to the discussion forum).

*/

#include "input.hpp"
#include <iostream>
#include <sstream>
#include <set>


using namespace std;
using Type = long long;

//
// NOTICE: this solution uses 'cost' in place of 'weight' and 'time' in place of 'length' since I subjectively feel
// that 'weight' and 'length' are somewhat synonymous which can cause ambiguous confusion.  So I chose 'cost' and 'time'
// to clearly represent how much a job costs and how much time it takes to perform that job.
//
template< typename Job >
class Solution
{
public:

    void print(){ copy( jobs.begin(), jobs.end(), ostream_iterator< Job >( cout, "\n" ) ); }

    void insert( Job&& job ){ jobs.insert( job ); }

    Type minCostTime() const
    {
        Type cost{ 0 }, time{ 0 };
        for( auto& job: jobs )
            time += job.time,
            cost += job.cost * time;
        return cost;
    }

private:

    using Jobs = multiset< Job >;

    Jobs jobs;

};


struct Job
{
    const Type cost{ 0 }, time{ 0 };
    Job( Type cost, Type time ) : cost{ cost }, time{ time } {}
    virtual bool operator<( const Job& ) const = 0;
};
ostream& operator<<( ostream& os, const Job& j ){ os << "{" << j.cost << "," << j.time << "}"; return os; }

struct D_Job : public Job // a D_Job is sub-optimal greedily scheduled via the (D)ifference ( cost - time )
{
    D_Job( Type cost, Type time ) : Job{ cost, time } {}
    bool operator<( const Job& rhs ) const
    {
        return ( cost - time ) > ( rhs.cost - rhs.time )
               || (( cost - time ) == ( rhs.cost - rhs.time ) && cost > rhs.cost );
    }
};

struct R_Job : public Job // a R_Job is optimal greedily scheduled via the (R)atio ( cost / time ) ( i.e. cost divided by time )
{
    R_Job( Type cost, Type time ) : Job{ cost, time } {}
    bool operator<( const Job& rhs ) const
    {
        return ( cost / double( time )) > ( rhs.cost / double( rhs.time ));
    }
};

int main()
{
    for( auto& input: { Lecture::Input, Assignment::Input } )
    {
        Solution< D_Job > d_jobs;
        istringstream d_stream{ input };
        for( string line; getline( d_stream, line ); )
        {
            stringstream parser{ line };
            Type cost{ 0 }, time{ 0 };
            parser >> cost >> time;
            d_jobs.insert({ cost, time });
        }
        cout << "answer 1: " << d_jobs.minCostTime() << " ( sub-optimal ) " << endl;

        Solution< R_Job > r_jobs;
        istringstream r_stream{ input };
        for( string line; getline( r_stream, line ); )
        {
            stringstream parser{ line };
            Type cost{ 0 }, time{ 0 };
            parser >> cost >> time;
            r_jobs.insert({ cost, time });
        }
        cout << "answer 2: " << r_jobs.minCostTime() << " ( optimal ) " << endl << endl;
    }

//    answer 1: 23 ( sub-optimal )
//    answer 2: 22 ( optimal )
//
//    answer 1: 69119377652 ( sub-optimal )
//    answer 2: 67311454237 ( optimal )

    return 0;
}

