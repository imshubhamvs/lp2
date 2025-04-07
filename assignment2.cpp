#include<iostream>
#include<unordered_map>
#include<list>
#include<set>
#include<vector>
using namespace std;
class Graph{
    unordered_map<string,list<pair<int,string>>> adj;
    unordered_map<string,int> straight_steps;
    int total_cities;
    public:
    Graph(int n)
    {
        total_cities=n;
    }
    void addEdge(string src,string dest, int dist)
    {
        adj[src].push_back(make_pair(dist,dest));
        adj[dest].push_back(make_pair(dist,src));
        cout<<"\nEdge added successfully";
    }
    int fun_g(string start,string end)
    {
        for(auto city:adj[start])
        {
            if(city.second==end)
            {
                return city.first;
            }
        }
        return 0;
    }
    int fun_h(string city)
    {
        return straight_steps[city];
    }
    void shortestPath(string src,string dest)
    {
        string s;
        int steps;
        cout<<"\nEnter straight steps from each city to "<<dest<<endl;
        for(int i=0;i<total_cities;i++)
        {
            cout<<"\nEnter src city:";
            cin>>s;
            cout<<"\nEnter steps to "<<dest<<" from "<<src;
            cin>>steps;
            straight_steps[s]=steps;
        }
        set<pair<int,string>> openList;//f(n),city

        openList.insert(make_pair(0,src));

        vector<string> closedList;

        unordered_map<string,bool> visited;
        unordered_map<string,string> parent; //to store (parent-city,city)
        unordered_map<string,int> min_dist;  //to store g(n) of each city from src
        while(1)
        {
            if(!closedList.empty()  && closedList.back()==dest)
            {
                break;
            }
            //get city with smallest f(n)
            auto topNode=*openList.begin();
            openList.erase(openList.begin());
            
            string top_city=topNode.second;
            //pop the closed list until parent of current city is retrived
            // while((!closedList.empty()) && (closedList.back()!=parent[top_city]))
            // {
            //     closedList.pop_back();
            // } 
            //push the current city into closed list
            closedList.push_back(top_city);
            //Check neighbours of current city to select next city
            for(auto neighbour:adj[top_city])
            {
                if(!visited[neighbour.second])
                {
                    //calculate g(n) using : distance from src to parent-city(top_city) + distance from top_city to curent city(neighbour.second)
                    int gn=min_dist[top_city] + fun_g(top_city,neighbour.second);
                    //calulate h(n)
                    int hn=fun_h(neighbour.second);
                    int fn=gn+hn;
                    //insert entry into open_list (f(n),city)
                    openList.insert(make_pair(fn,neighbour.second));
                    //store the minimum distance i.e g(n) from src city to currenet city(neighbour.second)
                    min_dist[neighbour.second]=gn;
                    //visit the city
                    if(neighbour.second!=dest)
                    {
                    visited[neighbour.second]=true;
                    }
                    //update the parent city
                    parent[neighbour.second]=top_city;

                }
            }

        }
        cout<<endl;
        for(auto city :closedList)
        {
            cout<<city<<"->";
        }
        cout<<endl;
        cout<<"\ncost : "<<min_dist[dest]<<endl;
    }
};
int main()
{
    int n;
    cout<<"Enter number of cities: ";
    cin>>n;
    Graph g(n);
    int choice=-1;
    string u,v;
    int wt;
    while(choice !=0 )
    {
        cout<<"\n0.exit\n1.Add Edge\n2.A* algorithm\nEnter choice: ";
        cin>>choice;
        if(choice==1)
        {
           cout<<"\nEnter src city: ";
           cin>>u;
           cout<<"\nEnter destination city: ";
           cin>>v;
           cout<<"Enter distance between "<<u<<" & "<<v;
           cin>>wt;
           g.addEdge(u,v,wt); 
        }
        else if(choice == 2)
        {
            cout<<"\nEnter source city: ";
            cin>>u;
            cout<<"\nEnter destination city: ";
            cin>>v;
            g.shortestPath(u,v);
        }
        else{
            cout<<"\nWrong choice!!! Please Enter valid choice"<<endl;
        }
    }
    return 0;
}

//1 A Z 75 1 A S 140 1 A T 118
//1 Z O 71
//1 T L 111
//1 L M 70
//1 M D 75
//1 D C 120
//1 O S 151
//1 S F 99 1 S RV 80
//1 C RV 146 1 C P 138
//1 P B 101 1 P RV 97
//1 F B 211
//1 B G 90 1 B U 85
//1 H U 98 1 H E 86 
//1 V I 92 1 V U 142
//1 N I 87

//1 A Z 75 1 A S 140 1 A T 118 1 Z O 71 1 T L 111 1 L M 70 1 M D 75 1 D C 120 1 O S 151 1 S F 99 1 S RV 80 1 P B 101 1 P RV 97 1 F B 211 1 B G 90 1 B U 85 1 H U 98 1 H E 86 1 V I 92 1 V U 142 1 N I 87

//A 366 B 0 C 160 D 242 E 161 F 178 G 77 H 151 I 226 L 244 M 241 N 234 O 380 P 98 RV 193 S 253 T 329 U 80 V 199 Z 374