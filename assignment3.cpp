#include<iostream>
#include <vector>
#include <queue>
#include <list>
#include<stack>
#include<set>
#include<thread>
#include<algorithm>
#include <unordered_map>
using namespace std;
struct edge{
    int u,v,wt;
};
bool compare(edge u,edge v)
{
    return u.wt < v.wt;
}
class Graph
{
    unordered_map<int, list<pair<int,int>>> adj;

public:
    Graph() {}
    int getNumOfNode()
    {
        return adj.size();
    }
    void addEdge(int u, int v,int wt)
    {
        adj[u].push_back(make_pair(v,wt));
        adj[v].push_back(make_pair(u,wt));
        cout << "Edge added successfully" << endl;
    }
    void Dijkstra(int src,int target)
    {
        set<pair<int,int>> st ;//distance,node
        unordered_map<int,int> distance,parent;
        for(auto i:adj)
        {
            distance[i.first]=INT8_MAX;
            parent[i.first]=-1;
        }
        distance[src]=0;
        
        st.insert(make_pair(0,src));
        while(!st.empty())
        {
            auto topNode = *(st.begin());
            st.erase(topNode);
            int node=topNode.second;
            int dist = topNode.first;
            for(auto neighbour:adj[node])
            {
                if(neighbour.second+dist < distance[neighbour.first])
                {
                    auto record = st.find(make_pair(distance[neighbour.first],neighbour.first));
                    
                    if(record!=st.end())
                    {
                        st.erase(record);
                    }
                    
                    distance[neighbour.first]= neighbour.second+dist;
                    parent[neighbour.first] = node;
                    
                    st.insert(make_pair(distance[neighbour.first],neighbour.first));
                    
                }
            }

        }
        string path="";
        cout<<endl;
        for(auto i=target;i!=-1;i=parent[i])
        {
            path= to_string(i)+"-"+path;
        }
        cout<<path<<endl;
        cout<<"Cost: "<<distance[target];
    }
    void prims(int src)
    {
        unordered_map<int,int> key,parent;
        unordered_map<int,bool> mst;
        for(auto i:adj)
        {
            key[i.first]=INT8_MAX;
            parent[i.first]=-1;
            mst[i.first]=false;
        }
        key[src]=0;
        for(auto i:adj)
        {
            int mini=INT8_MAX;
            int u;
            for(auto j:adj)
            {
                if(mst[j.first] == false && mini > key[j.first])
                {
                    mini=key[j.first];
                    u=j.first;
                }
            }

            mst[u]=true;
            for(auto neighbour:adj[u])
            {
                if(key[neighbour.first] > neighbour.second)
                {
                    key[neighbour.first]=neighbour.second;
                    parent[neighbour.first]=u;
                }
            }
        }
        int cost=0;
        for(auto i:parent)
        {
            cout<<i.second<<"->"<<i.first;
            cout<<" weight="<<key[i.first]<<endl;
            cost+=key[i.first];
        }
        cout<<"Cost: "<<cost<<endl;
    }
    void scheduleJob(vector<pair<int,int>> &jobList)
    {
        int completedJobs=0;
        int shortest=INT8_MAX;
        int mintime=0;
        int currTime=0;
        vector<int> completeTime(jobList.size(),0);
        while(completedJobs!=jobList.size())
        {
            
            for(int i=0;i<jobList.size();i++)
            {
                if(currTime <= jobList[i].first && mintime > jobList[i].second && completeTime[i]==0)
                {
                    mintime = jobList[i].second;
                    shortest=i;
                }
            }
            if(jobList[shortest].second>0)
            {
                jobList[shortest].second--;
                this_thread::sleep_for(chrono::milliseconds(1500));
                
            }
            else if(jobList[shortest].second==0)
            {
                completeTime[shortest]=currTime;
                completedJobs++;
            }
            currTime++;
        }
    }

    int find(int u, vector<int> &parent)
    {
        if(u!=parent[u])
        {
            return find(parent[u],parent);
        }
        return parent[u];
    }
    void unionRank(int u,int v, vector<int> &parent, vector<int> &rank)
    {
        int rootU=find(u,parent);
        int rootV=find(v,parent);
        if(rank[rootU] > rank[rootV])
        {
            parent[rootV]=rootU;
        }
        else if(rank[rootU] < rank[rootV])
        {
            parent[rootU]=rootV;
        }
        else{
            parent[rootV]=rootU;
            rank[rootU]++;
        }
    }
    void Kruskal()
    {
 
        int m,n;
        cout<<"\nEnter number of Nodes: ";
        cin>>n;
        cout<<"\nEnter number of edges: ";
        cin>>m;

        vector<edge> Edges(m);
        int src,dest,wt;
        vector<int> parent(n);
        vector<int> rank(m,0);  
        for(int i=0;i<m;i++)
        {
            
            cout<<"\nEnter src node: ";
            cin>>src;
            cout<<"\nEnter dest node: ";
            cin>>dest;
            cout<<"\nEnter weight: ";
            cin>>wt;
            Edges[i].u=src;
            Edges[i].v=dest;
            Edges[i].wt=wt;
        }
        for(int i=0;i<n;i++)
        {
            parent[i]=i;
        }
        sort(Edges.begin(),Edges.end(),compare);
        int cost=0;
        for(auto i:Edges)
        {
            int pu=find(i.u,parent);
            int pv=find(i.v,parent);
            if(pu!=pv)
            {
                cout<<i.u<<" - "<<i.v<<endl;
                cost += i.wt;
                unionRank(i.u,i.v,parent,rank);
            }
        }
        cout<<"\nTotal cost: "<<cost<<endl;
           
    }
};
void selection_sort(int arr[],int size)
{
    int idx;
    int element;
    for(int i=0;i<size;i++)
    {
        idx=i;
        for(int j=i;j<size;j++)
        {
            if(arr[j]<arr[idx])
            {
                idx=j;
            }
        }
        element = arr[i];
        arr[i]=arr[idx];
        arr[idx]=element;
    }
    for(int i=0;i<size;i++)
    {
        cout<<arr[i]<<' ';
    }
}
int main()
{
    // int n;
    // cout<<"Enter number of elements: ";
    // cin>>n;
    // int arr[n];
    // for(int i=0;i<n;i++)
    // {
    //     cout<<"\nEnter "<<i+1<<" element: ";
    //     cin>>arr[i];
    // }
    // cout<<endl;
    // selection_sort(arr,n);
    Graph g;
    int n, u, v,wt, choice;
    while (1)
    {
        cout << "\n1.Add Edge \n2.Dijsktra\n3.Prims\n4.Kruskal\n5.Job Scheduling\nEnter :";
        cin >> choice;
        if (choice == -1)
        {
            break;
        }
        else if (choice == 1)
        {
            cout << "Enter source Edge: ";
            cin >> u;
            cout << "Enter destination edge: ";
            cin >> v;
            cout<<"Enter distance: ";
            cin>>wt;
            g.addEdge(u, v,wt);
        }
        else if(choice==2)
        {
            cout<<"Enter source :";
            cin>>u;
            cout<<"Enter destination: ";
            cin>> v;
            g.Dijkstra(u,v);
        }
        else if(choice==3)
        {
            cout<<"\nEnter source: ";
            cin>>u;
            g.prims(u);
        }
        else if(choice == 4)
        {
            g.Kruskal();
        }
        else if(choice == 5)
        {
            vector<pair<int,int> > jobs;
            int at,bt;
            int n;
            cout<<"\nEnter number of jobs: ";
            cin>>n;
            for(int i=0;i<n;i++)
            {
                cout<<"Enter arrival time: ";
                cin>>at;
                cout<<"\nEnter burst time: ";
                cin>>bt;
                jobs.push_back(make_pair(at,bt));
                g.scheduleJob(jobs);
            }
        }
        else{
            cout<<"\nEnter valid choice!!!";
        }
    }
    return 0;
}
//6 1 5 4 3 2 6
// 1 0 1 1 1 0 3 2 1 1 2 4 1 1 4 5 1 2 5 9 1 4 5 8 1 3 4 2

//kruskal : 0 1 2 0 2 4 1 2 1 1 3 7 2 4 3 3 4 2 3 5 1 4 5 5
