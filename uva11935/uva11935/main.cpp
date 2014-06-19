//
//  main.cpp
//  uva11935 Though the Desert
//
//  Created by SUN Ka Meng Isaac on 20/6/14.
//  Copyright (c) 2014 SUN, Ka Meng Isaac. All rights reserved.
//

#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <deque>
#include <bitset>
#include <algorithm>
#include <set>
#include <list>

using namespace std;

typedef long long       ll;
typedef pair<int, int>  ii;
typedef vector<ii>      vii;
typedef vector<int>     vi;
#define INF             1000000000
#define EPS             1e-9

char event[55];     // event type
int val[55];        // consumption of fuel
int km[55];         // run km per litre fuel
int n;              // number of Events

bool can(double fuel) {
    double init = fuel;
    int cons = 0, ckm = 0, leak = 0, i;
    
    for (i = 0; i < n; ++i)
    {
        fuel = fuel - leak*(km[i] - ckm) - cons*(km[i] - ckm)/100.0;
        if ( fuel < 0 )
            return false;
        
        if ( event[i] == 'F' )
            cons = val[i];
        else if ( event[i] == 'L' )
            leak++;
        else if ( event[i] == 'M' )
            leak = 0;
        else if ( event[i] == 'G' && fuel >= 0 )
            fuel = init;
        
        ckm = km[i];
    }
    
    return true;
}

int main(int argc, char const *argv[])
{
    char input[100], str1[100], str2[100];
    int number, ret, a;
    n = 0;
    
    while ( fgets(input, sizeof(input), stdin) )
    {
        ret = sscanf(input, "%d %s %s %d", &a, str1, str2, &number);
        if ( ret == 4 && a == 0 && number == 0 )    // EOF
            break;
        if ( ret == 2 && str1[0] == 'G' )       // Goal
        {
            km[n] = a;
            event[n] = 'g';
            n++;
            
            double lo = 0.0, mid = 0.0, hi = 10000.0, answer = 0.0;
            
            for (int i = 0; i < 64; ++i)
            {
                mid = ( lo + hi ) / 2.0;
                if (can(mid)) { answer = mid; hi = mid; }
                else            lo = mid;
            }
            printf("%.3lf\n", answer);
            n = 0;
        }
        else
        {
            if ( ret <= 3 )     // record event name by char[0], happens at a km, no. of evt++
            {
                km[n] = a;
                event[n] = str1[0];
                n++;
            }
            if ( ret == 4 )     // %d Fuel consumption %d
            {
                km[n] = a;
                event[n] = str1[0];
                val[n] = number;
                n++;
            }
        }
        
    }
    
    return 0;
}


