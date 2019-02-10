<h1 id="job_scheduler">Job Scheduling</h1>
<a href="https://en.wikipedia.org/wiki/Scheduling_(computing)">https://en.wikipedia.org/wiki/Scheduling_(computing)</a>
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
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course3/schedule_jobs/documentation/job_00.png" />
<hr/>
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course3/schedule_jobs/documentation/job_01.png" />
<hr/>
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course3/schedule_jobs/documentation/job_02.png" />
<hr/>
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course3/schedule_jobs/documentation/job_03.png" />
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course3/schedule_jobs/documentation/job_04.png" />
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course3/schedule_jobs/documentation/job_05.png" />
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course3/schedule_jobs/documentation/job_06.png" />
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course3/schedule_jobs/documentation/job_07.png" />
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course3/schedule_jobs/documentation/job_08.png" />
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course3/schedule_jobs/documentation/job_09.png" />
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course3/schedule_jobs/documentation/job_10.png" />
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course3/schedule_jobs/documentation/job_11.png" />
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course3/schedule_jobs/documentation/job_12.png" />
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course3/schedule_jobs/documentation/job_13.png" />
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course3/schedule_jobs/documentation/job_14.png" />
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course3/schedule_jobs/documentation/job_15.png" />
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course3/schedule_jobs/documentation/job_16.png" />
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course3/schedule_jobs/documentation/job_17.png" />
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course3/schedule_jobs/documentation/job_18.png" />
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course3/schedule_jobs/documentation/job_19.png" />

<h2 id="solution">Solution</h2>
<pre>

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
    
        Type schedule() const
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
    
    
    template< typename Job >
    Type schedule( const string& input )
    {
        Solution< Job > jobs;
        istringstream stream{ input };
        for( string line; getline( stream, line ); )
        {
            stringstream parser{ line };
            Type cost{ 0 }, time{ 0 };
            parser >> cost >> time;
            jobs.insert({ cost, time });
        }
        return jobs.schedule();
    }
    
    
    int main()
    {
        cout << "lecture answer 1: "    << schedule< D_Job >( Lecture::Input )    << " ( sub-optimal )" << endl
             << "lecture answer 2: "    << schedule< R_Job >( Lecture::Input )    << " ( optimal )" << endl << endl
             << "assignment answer 1: " << schedule< D_Job >( Assignment::Input ) << " ( sub-optimal )" << endl
             << "assignment answer 2: " << schedule< R_Job >( Assignment::Input ) << " ( optimal )" << endl;
    
    //    lecture answer 1: 23 ( sub-optimal )
    //    lecture answer 2: 22 ( optimal )
    
    //    assignment answer 1: 69119377652 ( sub-optimal )
    //    assignment answer 2: 67311454237 ( optimal )
    
        return 0;
    }

</pre>

<h2 id="build">Build Instructions</h2>
<p>Use <code>cmake</code> to build this project:</p>

<pre>
    cmake --build cmake-build-debug --target schedule_jobs -- -j 4
</pre>

<h2 id="dependencies">Dependencies</h2>
<ul>
  <li>
    <a href="https://cmake.org/">cmake.org</a>
  </li>
</ul>

</body>
</html>