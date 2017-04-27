#include<iostream>
#include<algorithm>
#include<stdio.h>
#include<math.h>
#include<vector>
using namespace std;
int videos, endpoints, requests, caches, szOfCache;
int temp, dcl, nc, rv, re, rn;
vector<int>szOfVideos, dataCenterLatency;
vector< vector <pair<int, int> > >endps;
//vector< vector <pair<int, int> > >endpReqs;
vector< pair< int, pair< pair<int, int>, pair<int, int> > >  >reqs;
vector< vector <int> >g;
int freeSpace[1001], usedCaches;
bool used[10001][501];
main(){
freopen ("input.txt", "r", stdin);
freopen ("output.txt", "w", stdout);
    scanf ("%d%d%d%d%d", &videos, &endpoints, &requests, &caches, &szOfCache);

    endps.resize(endpoints + 10);
    //endpReqs.resize(endpoints + 10);
    g.resize(caches + 10);

    for (int i = 0; i < caches; i++)
        freeSpace[i] = szOfCache;

    for (int i = 0; i < videos; i++){
        for (int j = 0; j < caches; j++){
            used[i][j] = false;
        }
    }

    for (int i = 0; i < videos; i++){
        scanf ("%d", &temp);
        szOfVideos.push_back(temp);
    }
    for (int i = 0; i < endpoints; i++){
        scanf ("%d%d", &dcl, &nc);
        int c, l;
        for (int j = 0; j < nc; j++){
            scanf ("%d%d", &c, &l);
            endps[i].push_back(make_pair(l, c));
        }
    }
    for (int i = 0; i < requests; i++){
        scanf ("%d%d%d", &rv, &re, &rn);
        //endpReqs[re].push_back(make_pair(rn, rv));
        reqs.push_back({rn - szOfVideos[rv]*100, {{rn, szOfVideos[rv]},{rv, re}}});
    }


    /*
    for (int i = 0; i < videos; i++){
        if (szOfVideos[i] > szOfCache){

        }
    }
    */

    /*
    for (int i = 0; i < endpoints; i++){
        sort(endpReqs[i].begin(), endpReqs[i].end());
    }
    */

    sort(reqs.begin(), reqs.end());

    int prev = -1, cur, l = 0, r = 0;
    bool flag = false;
    for (int i = 0; i < reqs.size(); i++){
        cur = reqs[i].second.first.first;
        if (cur == prev && !flag){
            l = i - 1;
            flag = true;
        }
        else if (cur != prev && flag){
            r = i;
            flag = false;
            reverse(reqs.begin() + l, reqs.begin() + r);
        }
        prev = cur;
    }

    /*
    for (int i = 0; i < reqs.size(); i++)
        printf ("%d %d %d %d\n", reqs[i].first.first, reqs[i].first.second, reqs[i].second.first, reqs[i].second.second);
    */

    for (int i = 0; i < endpoints; i++){
        sort(endps[i].begin(), endps[i].end());
    }

    /*
    for (int i = 0; i < endpoints; i++){
        for (int j = 0; j < endps[i].size(); j++)
            printf ("%d %d, ", endps[i][j].first, endps[i][j].second);
            printf ("\n");
    }
    */

    bool flag1 = false;
    for (int i = reqs.size() - 1; i >= 0; i--){
        if (reqs[i].second.first.second <= szOfCache){
            int endPoint = reqs[i].second.second.second;
            flag1 = false;
            for (int j = 0; j < endps[endPoint].size(); j++){
                if (used[reqs[i].second.second.first][endps[endPoint][j].second]){
                    flag1 = true;
                    break;
                }
            }
            if (!flag1){
                for (int j = 0; j < endps[endPoint].size(); j++){
                    if (freeSpace[endps[endPoint][j].second] >= reqs[i].second.first.second){
                        freeSpace[endps[endPoint][j].second] -= reqs[i].second.first.second;
                        g[endps[endPoint][j].second].push_back(reqs[i].second.second.first);
                        used[reqs[i].second.second.first][endps[endPoint][j].second] = true;
                        break;
                    }
                }
            }
        }
    }

    usedCaches = 0;
    for (int i = 0; i < caches; i++){
        if (g[i].size() > 0)
            usedCaches++;
    }

    printf ("%d\n", usedCaches);
    for (int i = 0; i < usedCaches; i++){
        if (g[i].size() > 0)
            printf ("%d ", i);
        for (int j = 0; j < g[i].size(); j++)
            printf ("%d ", g[i][j]);
        printf ("\n");

    }
return 0;
}
