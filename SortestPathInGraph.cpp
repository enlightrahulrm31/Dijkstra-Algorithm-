// Shortest path from source node to every other node in a connected graph
#include<bits/stdc++.h>
using namespace std;
const int N = 1e5+5;
class Dijikstra{
public:
    multiset<pair<int,int>>grp[N];
    // grp[p].pb({q,w}) means node p is directly connected to node q with weight w  
    int nodes;
    int mnReach[N];
    int mx = 1e9;
    Dijikstra(multiset<pair<int,int>>g[],int n){ // constructor 
        for(int i=1;i<=n;i++){ // creating graph from given graph 
            if(g[i].size()>0){
                int p = i;
                for(auto &x:g[i]){
                    int q = x.first;
                    int w = x.second;
                    grp[p].insert({q,w});
                }
            }
        }
        nodes = n;
        for(int i=1;i<=nodes;i++){
            mnReach[i] = mx;
        }
    }
    vector<pair<int,int>> Find_Sortest_Path(int src_node){
        set<pair<int, int>> q;
        // The first element of pair is the distance 
        // The second element of pair is node 
        q.insert({0,src_node}); // inserting source node with initial distance as zero
        mnReach[src_node] = 0;
        while (!q.empty()) {
            int v = q.begin()->second;
            q.erase(q.begin());
            for (auto edge : grp[v]) {
                int u = edge.first;
                int w = edge.second;
                if (mnReach[v] + w < mnReach[u]) {
                    q.erase({mnReach[u], u});
                    mnReach[u] = mnReach[v] + w;
                    q.insert({mnReach[u], u});
                }
            }
        }
        vector<pair<int,int>>ans;
        for(int i=1;i<=nodes;i++){
            ans.push_back({i,mnReach[i]});
        }
        return ans;
    }

};
int main(){
    int n,m; // n number of nodes  m number of edges 
    cin>>n>>m;
    multiset<pair<int,int>>grp[n+1];
    while(m--){
        int p,q,w;
        cin>>p>>q>>w;
        grp[p].insert({q,w});
    }
    Dijikstra dj = Dijikstra(grp,n);
    vector<pair<int,int>>ans;
    ans = dj.Find_Sortest_Path(1);
    for(int i=0;i<ans.size();i++){
        int node = ans[i].first;
        int dis = ans[i].second;
        cout<<node<<"=>"<<dis<<"\n";
    }
    return 0;

}
