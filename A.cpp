#include<bits/stdc++.h>
using namespace std;
const int INF = 1e9 + 7, MAXN = 1e4, MAXF = 1e3;
int R, C, F, N, B, T;
int curRideInd = 0;
vector<int>freeCars;
vector<int>assignments[MAXF];
struct Ride{
    int a;
    int b;
    int x;
    int y;
    int s;
    int f;
    int id;
    bool taken;
}rides[MAXN];
struct Vehicle{
    int x;
    int y;
    int timeFree;
}vehicles[MAXF];
bool rideCompare(Ride A, Ride B){
    int lengthA = abs(A.a - A.x) + abs(A.b - A.y);
    int lengthB = abs(B.a - B.x) + abs(B.b - B.y);
    int fromOriginA = abs(A.a) + abs(A.b);
    int fromOriginB = abs(B.a) + abs(B.b);
    return (A.s < B.s || A.s == B.s && A.f < B.f || A.s == B.s && A.s == B.s && (fromOriginA < fromOriginB || fromOriginA == fromOriginB && lengthA < lengthB));
    //return (lengthA < lengthB || lengthA == lengthB && fromOriginA < fromOriginB);
}
bool sortFreeCars(int a, int b){
    int curRide = rides[curRideInd].id;
    int distA = abs(vehicles[a].x - rides[curRide].a) + abs(vehicles[a].y - rides[curRide].b);
    int distB = abs(vehicles[b].x - rides[curRide].a) + abs(vehicles[b].y - rides[curRide].b);
    return (distA < distB);
}
int main(){
    freopen ("e_high_bonus.in", "r", stdin);
    freopen ("output_e_high_bonus.txt", "w", stdout);
    scanf ("%d%d%d%d%d%d", &R, &C, &F, &N, &B, &T);
    int a, b, x, y, s, f;
    for (int i = 0; i < N; i++){
        scanf ("%d%d%d%d%d%d", &a, &b, &x, &y, &s, &f);
        rides[i].a = a;
        rides[i].b = b;
        rides[i].x = x;
        rides[i].y = y;
        rides[i].s = s;
        rides[i].f = f;
        rides[i].id = i;
        rides[i].taken = false;
    }
    for (int i = 0; i < F; i++){
        vehicles[i].x = 0;
        vehicles[i].y = 0;
        vehicles[i].timeFree = 0;
    }

    sort(rides, rides + N, rideCompare);
    /*
    for (int i = 0; i < N; i++){
        printf ("%d %d %d %d %d %d\n", rides[i].a, rides[i].b, rides[i].x,
                                       rides[i].y, rides[i].s, rides[i].f);
    }
    */
    set< pair<int, int> >freeVehicles;
    for (int i = 0; i < F; i++)
        freeVehicles.insert({0, i});
    int t = 0;
    int ridesLeft = N;
    while (t <= T && ridesLeft > 0){
        if (freeVehicles.empty()){
            t++;
            continue;
        }
        else{
            freeCars.clear();
            while (!freeVehicles.empty() && freeVehicles.begin()->first >= t){
                int to = freeVehicles.begin()->second;
                freeVehicles.erase(freeVehicles.begin());
                freeCars.push_back(to);
            }
            int cnt = 0;
            int temp = curRideInd;
            while (cnt + 1 < freeCars.size()){
                if (curRideInd < N)
                    sort(freeCars.begin() + cnt, freeCars.end(), sortFreeCars);
                curRideInd++;
                cnt++;
            }
            /*for (int i = 0; i < freeCars.size(); i++)
                printf ("%d ", freeCars[i]);
            printf ("\n");*/
            curRideInd = temp;
            cnt = 0;
            while (ridesLeft > 0 && cnt < freeCars.size()){
                int to = freeCars[cnt];
                int curRide = rides[curRideInd].id;
                //freeVehicles.erase(freeVehicles.begin());

                int reachTime = abs(vehicles[to].x - rides[curRideInd].a) + abs(vehicles[to].y - rides[curRideInd].b);
                int waitTime = max(rides[curRideInd].s - (t + reachTime), 0);
                int delta = abs(rides[curRideInd].a - rides[curRideInd].x) + abs(rides[curRideInd].b - rides[curRideInd].y);
                int totalTime = t + reachTime + waitTime + delta;

                if (totalTime >= rides[curRideInd].f){
                    curRideInd++;
                    ridesLeft--;
                    continue;
                }

                assignments[to].push_back(curRide);
                vehicles[to].x = rides[curRideInd].x;
                vehicles[to].y = rides[curRideInd].y;
                vehicles[to].timeFree = totalTime;
                freeVehicles.insert({totalTime, to});
                curRideInd++;
                ridesLeft--;
                cnt++;
            }
            /*while (ridesLeft > 0 && !freeVehicles.empty() && freeVehicles.begin()->first >= t){
                int to = freeVehicles.begin()->second;
                int curRide = rides[curRideInd].id;
                freeVehicles.erase(freeVehicles.begin());
                assignments[to].push_back(curRide);

                int reachTime = abs(vehicles[to].x - rides[curRide].a) + abs(vehicles[to].y - rides[curRide].b);
                int waitTime = max(rides[curRide].s - (t + reachTime), 0);
                int delta = abs(rides[curRide].a - rides[curRide].x) + abs(rides[curRide].b - rides[curRide].y);
                int totalTime = reachTime + waitTime + delta;
                vehicles[to].x = rides[curRide].x;
                vehicles[to].y = rides[curRide].y;
                vehicles[to].timeFree = totalTime;
                freeVehicles.insert({totalTime, to});
                curRideInd++;
                ridesLeft--;
            }*/
            t++;
        }
    }

    for (int i = 0; i < F; i++){
        printf ("%d ", assignments[i].size());
        for (int j = 0; j < assignments[i].size(); j++)
            printf ("%d ", assignments[i][j]);
        printf ("\n");
    }


    return 0;
}
