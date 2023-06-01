#include<iostream>
#include<map>
#include<vector>
#include<queue>
#include<list>
#include<string>

using namespace std;

class Metro_st{
public:
    string name;

    Metro_st(string name){
    this->name= name;
    }
};

typedef Metro_st* Pmetro;
typedef pair<int, Pmetro> myPair;
int flag = 0;
int bo = 0;

map<Pmetro, int> dist;
map<Pmetro, Pmetro> parent;

class Graph
{
    map<Pmetro, vector<pair<Pmetro, int>>> adj;
    void printAllUtils(Pmetro src, Pmetro dest, map<Pmetro, bool> &visit, vector<string> &path, int &);

public:
    vector<Pmetro> listOfMetroStation;

    void addRoute(Pmetro u, Pmetro v, int w, bool bidirected);
    void shortestRoute(Pmetro s, Pmetro d);
    void addMetro_st(Pmetro a);
    void printRoutes(Pmetro a, Pmetro b);
    void viewMap();
    void PrintAllRoutes(Pmetro src, Pmetro dest);
    void minFare(Pmetro src, Pmetro dest);
    Pmetro SearchMetroStation(string abc);

};

bool doesRouteExist(Pmetro dest){

    //cout<<dist[dest]<<"\n";
    return dist[dest] != INT_MAX;
}

void Graph::minFare(Pmetro src, Pmetro dest)
{

   //Shortest_distance_between2*fareperkm

for (auto v : listOfMetroStation) {
        dist[v] = INT_MAX;
    }


    priority_queue<myPair, vector<myPair>, greater<myPair>> pq;

    pq.push(make_pair(0, src));
    dist[src] = 0;
    parent[src] = nullptr;

    while (!pq.empty())
    {
        Pmetro u = pq.top().second;
        pq.pop();

        for (pair<Pmetro, int> i : adj[u]) {


            Pmetro v = i.first;
            int weight = i.second;

            if (dist[v] > dist[u] + weight) {
                dist[v] = dist[u] + weight;
                pq.push(make_pair(dist[v], v));
                parent[v] = u;
            }
        }
    }

    if(doesRouteExist(dest)){
        cout << endl << "Shortest Metro Distance between " << src->name << " and " << dest->name << " is " << dist[dest] << endl << endl;

    }else{
        cout << "No Path Exist between " << src->name << " and " << dest->name << endl << endl;
    }

 cout<<endl<<"Total Metro Fare: Rs "<<dist[dest]*5;
}


void Graph::PrintAllRoutes(Pmetro src, Pmetro dest)
{
    map<Pmetro, bool>visit;
    vector<string>path(100);
    int path_index = 0;

    for (auto itr : listOfMetroStation)
    {
        visit[itr] = false;
    }
    printAllUtils(src, dest, visit, path, path_index);
}


void Graph::printAllUtils(Pmetro src, Pmetro dest, map<Pmetro, bool> &visit, vector<string> &path, int &path_index)
{
    visit[src] = true;
    path[path_index] = src->name;
    path_index++;


    if (src->name.compare(dest->name) == 0)
    {
        //flag++;
        for (int i = 0; i < path_index; i++)
            cout << "->"<< path[i] ;
        cout << endl;
    }
   else
    {
        for (pair<Pmetro, int> i : adj[src])
        {
            if (visit[i.first] == false)
            {
                printAllUtils(i.first, dest, visit, path, path_index);
            }
        }

    }
    path_index--;
    visit[src] = false;

}

Pmetro Graph::SearchMetroStation(string abc)
{
    int flag = 0;
    for (auto itr : listOfMetroStation)
    {

        if (itr->name.compare(abc) == 0)
        {
            flag = 1;
            return itr;
        }
    }
    if (flag == 0)
    {
        return NULL;
    }
    return NULL;
}

void Graph::addRoute(Pmetro u, Pmetro v, int w, bool bidirected = true)
{
    if (bidirected) {
        adj[u].push_back(make_pair(v, w));
        adj[v].push_back(make_pair(u, w));
    } else {
        adj[u].push_back(make_pair(v, w));
    }

}
void Graph::addMetro_st(Pmetro a) {
    listOfMetroStation.push_back(a);
}

void printRoute(Pmetro p) {
    if (parent[p] == nullptr) {
        return;
    }

    printRoute(parent[p]);

    cout << p->name << "->";
}

/*bool doesRouteExist(Pmetro dest){

    //cout<<dist[dest]<<"\n";
    return dist[dest] != INT_MAX;
}*/

void Graph::shortestRoute(Pmetro src, Pmetro dest)
{
    for (auto v : listOfMetroStation) {
        dist[v] = INT_MAX;
    }


    priority_queue<myPair, vector<myPair>, greater<myPair>> pq;

    pq.push(make_pair(0, src));
    dist[src] = 0;
    parent[src] = nullptr;

    while (!pq.empty())
    {
        Pmetro u = pq.top().second;
        pq.pop();

        for (pair<Pmetro, int> i : adj[u]) {


            Pmetro v = i.first;
            int weight = i.second;

            if (dist[v] > dist[u] + weight) {
                dist[v] = dist[u] + weight;
                pq.push(make_pair(dist[v], v));
                parent[v] = u;
            }
        }
    }

    if(doesRouteExist(dest)){
        cout << endl << "Shortest Metro Distance between " << src->name << " and " << dest->name << " is " << dist[dest] << endl << endl;

        cout << "Shortest Route is: " << src->name << "->";
        printRoute(dest);
        cout << endl;
    }else{
        cout << "No Path Exist between " << src->name << " and " << dest->name << endl << endl;
    }

}

void Graph::viewMap()
{
    for (auto itr : listOfMetroStation)
    {
        cout << "\n\n" << itr->name << "\n" << endl;
    }
}

vector<Pmetro> * getSourceAndDestinationMetro_St(Graph &g) {
    auto len = g.listOfMetroStation.size();
    bool validInput = false;
    int src = -1, dest = -1;

    while (!validInput) {
        cout << "List of Source Metro Station" << endl;

        for (int i = 0; i < g.listOfMetroStation.size(); i++) {
            cout << i + 1 << " " << g.listOfMetroStation[i]->name << endl;
        }
        cout << "Select Source Metro Station(1-" << len << ") : " << endl;
        cin >> src;

        cout << "List of Destination Metro Station" << endl;
        for (int i = 0; i < g.listOfMetroStation.size(); i++) {
            cout << i + 1 << " " << g.listOfMetroStation[i]->name << endl;
        }
        cout << "Select Destination Metro Station(1-" << len << ") : " << endl;
        cin >> dest;

        if (src == dest) {
            cout << "Source and Destination cannot be same" << endl;
            validInput = false;
            continue;
        }

        if (src >= 1 && src <= len && dest >= 1 && dest <= len) {
            validInput = true;
        }
    }

    Pmetro srcmetro, destmetro;
    srcmetro = g.listOfMetroStation[src - 1];
    destmetro = g.listOfMetroStation[dest - 1];

    vector<Pmetro> *srcAndDest = new vector<Pmetro>;
    srcAndDest->push_back(srcmetro);
    srcAndDest->push_back(destmetro);

    return srcAndDest;
}

int main()
{
    Graph g;

    Pmetro a1 = new Metro_st("Kashmere Gate");
    Pmetro a2 = new Metro_st("Rajiv Chawk");
    Pmetro a3 = new Metro_st("NSP");
    Pmetro a4 = new Metro_st("Botanical Garden");
    g.addMetro_st(a1);
    g.addMetro_st(a2);
    g.addMetro_st(a3);
    g.addMetro_st(a4);

    g.addRoute(a1, a2, 15);
    g.addRoute(a2, a3, 30);
    g.addRoute(a1, a3, 200);
    g.addRoute(a1, a4, 30);

    char choice = 'y';
    do
    {
        int ch;
        cout << "\t\t\t WELCOME TO THE DELHI METRO MAP " << endl;
        cout << "\t 1. To View the metro station list" << endl;
        cout << "\t 2. To Add a new Metro Station" << endl;
        cout << "\t 3. To Add a new Route" << endl;
        cout << "\t 4  To View all Routes" << endl;
        cout << "\t 5. To Get shortest Distance to your destination" << endl;
        cout << "\t 6. To View Fare Charges" << endl;
        cout << "\t 7. To Exit\n" << endl;
        cin >> ch;
        if (ch == 7)
        {
            exit(0);
        }
        else
        {
            switch (ch)
            {
                case 1:
                {
                    system("cls");
                    g.viewMap();
                    break;
                }
                case 2:
                {
                    system("cls");
                    cout << "\n\n Enter Name of the New Metro Station\n" << endl;
                    string st;
                    cin >> st;
                    Pmetro a5 = new Metro_st(st);
                    g.addMetro_st(a5);
                   dist[a5] = INT_MAX;
                    break;
                }
                case 3:
                {
                    vector<Pmetro> *srcAndDest = getSourceAndDestinationMetro_St(g);
                    Pmetro srcmetro = (*srcAndDest)[0];
                    Pmetro destmetro = (*srcAndDest)[1];

                    int weight;
                    cout << "\n\nEnter Distance \n" << endl;
                    cin >> weight;

                    g.addRoute(srcmetro, destmetro, weight);
                    cout << "\n\nMetro Station added successfully\n\n" << endl;
                    break;
                }
                case 4:
                {

                    vector<Pmetro> *srcAndDest = getSourceAndDestinationMetro_St(g);
                    Pmetro srcmetro = (*srcAndDest)[0];
                    Pmetro destmetro = (*srcAndDest)[1];

                    if(doesRouteExist(destmetro)){
                            //cout<<doesPathExist(destAirport)<<"\n";
                        g.PrintAllRoutes(srcmetro, destmetro);
                    }
                    else{
                        cout << "No Path Exist between " << srcmetro->name << " and " << destmetro->name << endl;
                    }

                    break;
                }
                case 5:
                {
                    system("cls");
                    vector<Pmetro> *srcAndDest = getSourceAndDestinationMetro_St(g);
                    Pmetro srcmetro = (*srcAndDest)[0];
                    Pmetro destmetro = (*srcAndDest)[1];
                    g.shortestRoute(srcmetro, destmetro);
                    break;

                }
                case 6:
                {
                    vector<Pmetro> *srcAndDest = getSourceAndDestinationMetro_St(g);
                    Pmetro srcmetro = (*srcAndDest)[0];
                    Pmetro destmetro = (*srcAndDest)[1];
                    cout << "\n\nFare is 5 rupee per kilometer \n" << endl;
                    g.minFare(srcmetro,destmetro);



                    break;

                }
            }
        }
        cout << "\n\n\nDo you want to go to the main page or not?(Y/N)\n";
        cin >> choice;
        system("cls");

    } while (choice == 'y' || choice == 'Y');

    for (auto &v : g.listOfMetroStation) {
        delete v;
    }

    return 0;
}
