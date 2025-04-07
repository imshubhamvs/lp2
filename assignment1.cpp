#include <iostream>
#include <vector>
#include <queue>
#include <list>
#include <unordered_map>
using namespace std;
class Graph
{
    unordered_map<int, list<int>> adj;

public:
    Graph() {}
    int getNumOfNode()
    {
        return adj.size();
    }
    void addEdge(int u, int v)
    {
        adj[u].push_back(v);
        adj[v].push_back(u);
        cout << "Edge added successfully" << endl;
    }
    void BFS(queue<int> &q, vector<bool> &visited)
    {
        int node = q.front();
        q.pop();
        if (!visited[node])
        {
            cout << node << " ";
            visited[node] = true;
        }
        for (auto i : adj[node])
        {
            if (!visited[i])
            {
                q.push(i);
            }
        }
        if (!q.empty())
        {
            BFS(q, visited);
        }
        return;
    }
    void DFS(int node, vector<bool> &visited)
    {
        visited[node] = true;
        cout << node << " ";
        for (auto i : adj[node])
        {
            if (!visited[i])
            {
                DFS(i, visited);
            }
        }
    }
    bool DLS(int height, int limit, int node,int target, vector<bool> &visited )
    {
        visited[node] = true;
        if(height>limit)
        {
            return false;
        }
        if(node == target)
        {
            return true;
        }
        bool ans=false;
        for (auto i : adj[node])
        {
            if (!visited[i])
            {
                ans = DLS(height+1,limit,i,target, visited);
                if(ans)
                {
                    return true;
                }
            }
        }
        return false;
    }
};
int main()
{
    Graph g;
    int n, u, v, choice;
    while (1)
    {
        cout << "\nEnter \n1.Add Edge \n2.BFS\n3.DFS \n4.DLS:";
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
            g.addEdge(u, v);
        }
        else if (choice == 2)
        {
            cout << "Enter starting node: ";
            cin >> u;
            n = g.getNumOfNode();
            vector<bool> visited(n, false);
            queue<int> q;
            q.push(u);
            g.BFS(q, visited);
        }
        else if (choice == 3)
        {
            cout << "Enter statring node: ";
            cin >> u;
            n = g.getNumOfNode();
            vector<bool> visited(n, false);
            g.DFS(u, visited);
        }
        else if(choice == 4)
        {
            cout << "Enter node to be DLSed: ";
            cin>>u;
            cout<<"Enter maximum level allowed: ";
            cin>>v;
            n = g.getNumOfNode();
            vector<bool> visited(n, false);
            bool ans = g.DLS(0,v,0,u,visited);
            if(ans)
            {
                cout<<"\nfound"<<endl;
            }
            else{
                cout<<"\nnot found";
            }
        }
    }
    return 0;
}
// 1 1 2 1 1 3 1 2 5 1 2 4 1 3 7 1 3 6
// 1 0 1 1 0 2 1 1 4 1 1 3 1 2 6 1 2 5
// 1 0 1 1 0 2 1 2 4 1 4 3 1 1 3 1 3 5 1 4 6 1 5 6
// 1 0 1 1 0 2 1 1 4 1 1 3 1 2 6 1 2 5