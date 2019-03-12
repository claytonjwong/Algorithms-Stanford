# Bellman Ford ( memory optimized + cycle detection )
https://en.wikipedia.org/wiki/Bellman–Ford_algorithm

## Contents
* [Lecture](#lecture)
* [Lecture Slides](#lecture-slides)
* [Solution](#solution)

# Lecture
* [Video](https://www.coursera.org/lecture/algorithms-npcomplete/single-source-shortest-paths-revisted-x0YZd)

## Lecture Slides
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course4/bellman_ford/documentation/bell_01.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course4/bellman_ford/documentation/bell_02.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course4/bellman_ford/documentation/bell_03.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course4/bellman_ford/documentation/bell_04.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course4/bellman_ford/documentation/bell_05.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course4/bellman_ford/documentation/bell_06.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course4/bellman_ford/documentation/bell_07.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course4/bellman_ford/documentation/bell_08.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course4/bellman_ford/documentation/bell_09.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course4/bellman_ford/documentation/bell_10.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course4/bellman_ford/documentation/bell_11.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course4/bellman_ford/documentation/bell_12.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course4/bellman_ford/documentation/bell_13.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course4/bellman_ford/documentation/bell_14.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course4/bellman_ford/documentation/bell_15.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course4/bellman_ford/documentation/bell_16.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course4/bellman_ford/documentation/bell_17.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course4/bellman_ford/documentation/bell_18.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course4/bellman_ford/documentation/bell_19.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course4/bellman_ford/documentation/bell_20.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course4/bellman_ford/documentation/bell_21.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course4/bellman_ford/documentation/bell_22.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course4/bellman_ford/documentation/bell_23.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course4/bellman_ford/documentation/bell_24.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course4/bellman_ford/documentation/bell_25.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course4/bellman_ford/documentation/bell_26.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course4/bellman_ford/documentation/bell_27.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course4/bellman_ford/documentation/bell_28.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course4/bellman_ford/documentation/bell_29.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course4/bellman_ford/documentation/bell_30.png)
---

## Solution
**Note:** the memory optimization and cycle detection functionality are included in the implementation
of [Johnson's algorithm]( https://github.com/claytonjwong/Algorithms-Stanford/tree/master/course4/johnson ).
Refer to [Johnson's algorithm]( https://github.com/claytonjwong/Algorithms-Stanford/tree/master/course4/johnson )
for the complete solution.
```cpp

    class BellmanFord
    {
    public:
    
        using Answer = pair< VI, bool >;
    
        static Answer getShortestPaths( Graph& G, Edges& E, Vertex start )
        {
            VI pre( N+1, INF ), cur( pre );
            pre[ start ] = 0;
            for( auto i{ 1 }; i <= N; ++i, swap( pre, cur ) )
                for( auto& pair: G )
                {
                    auto v{ pair.first };
                    cur[ v ] = pre[ v ]; // (pre)vious path or minimum (alt)erative path to v through w + cost of edge wv
                    for( auto w: G[ v ] ) // w -> v
                    {
                        Edge wv{ w,v };
                        Cost Cw = pre[ w ],
                             Cwv = E[ wv ],
                             alt = ( Cw < INF )? Cw + Cwv : INF;
                        if( cur[ v ] > alt )
                            cur[ v ] = alt;
                    }
                }
            auto hasCycle = BellmanFord::hasCycle( G, E, cur );
            return{ cur, hasCycle };
        }
    
    private:
    
        static bool hasCycle( Graph& G, Edges& E, VI& P )
        {
            for( auto& e: E )
            {
                auto edge{ e.first };
                auto u{ edge.u },
                     v{ edge.v };
                auto Pu = P[ u ],      // cost of (P)ath from s -> ... -> u
                     Pv = P[ v ],      // cost of (P)ath from s -> ... -> v
                     cost{ e.second }; // cost of u -> v
                if( Pu < INF && Pv > Pu + cost )
                    return true;
            }
            return false;
        }
    
    }; // class BellmanFord
    
```
