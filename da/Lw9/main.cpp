#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

const long long int INF = LLONG_MAX;

struct TGraph{
    std::vector<std::vector< std::pair<int,int> > > vertices;
    int nOfVertices;
    int nOfEdge;
};

void CreateGraph(TGraph &graph, int &start, int &finish);
void PrintGraph(TGraph &graph, int start, int finish);
long long int Dijkstra(TGraph &graph, int start, int finish);

int main() {
    int start;
    int finish;
    long long int res;
    TGraph graph;
    CreateGraph(graph, start, finish);
    res = graph.nOfVertices > 0 ? Dijkstra(graph, start - 1, finish - 1) : -1;
    if(res < 0) {
        std::cout << "No solution" << std::endl;
    } else {
        std::cout << res << std::endl;
    }
    return 0;
}

long long int Dijkstra(TGraph &graph, int start, int finish) {
    std::vector<long long int> dist(graph.nOfVertices);

    typedef std::pair<long long int, int> distAndIndex;
    std::priority_queue<distAndIndex, std::vector<distAndIndex>, std::greater<distAndIndex> > prQueue; 

    for(int i = 0; i < graph.nOfVertices; ++i) {
        dist[i] = INF;
    }
    dist[start] = 0;
    prQueue.push(std::make_pair(0, start));

    while(!prQueue.empty()) {
        int active = prQueue.top().second;
        prQueue.pop();
        std::vector<std::pair<int, int> >::iterator i;
        for (i = graph.vertices[active].begin(); i != graph.vertices[active].end(); ++i) {
            int tmp = (*i).first;
            int weight = (*i).second;

            if (dist[tmp] > dist[active] + weight) {
                dist[tmp] = dist[active] + weight;
                prQueue.push(std::make_pair(dist[tmp], tmp));
            }
        }
    }
    if(dist[finish] == INF) {
        return -1;
    }
    return dist[finish];
}

void CreateGraph(TGraph &graph, int &start, int &finish) {
    int vertex1;
    int vertex2;
    int weight;
    std::cin >> graph.nOfVertices 
             >> graph.nOfEdge
             >> start
             >> finish;
    graph.vertices.resize(graph.nOfVertices);
    while(std::cin >> vertex1
                   >> vertex2
                   >> weight) {
        graph.vertices[vertex1 - 1].push_back(std::make_pair(vertex2 - 1, weight));
        graph.vertices[vertex2 - 1].push_back(std::make_pair(vertex1 - 1, weight));
    }
}

void PrintGraph(TGraph &graph, int start, int finish) {
    for(int i = 0; i < graph.nOfVertices; ++i) {
        std::cout << ">  Vertex " << i + 1 << std::endl; 
        for(int j = 0; j < graph.vertices[i].size(); ++j) {
            std::cout << j + 1 << ") Vertex    " << graph.vertices[i][j].first + 1 << std::endl;
            std::cout << j + 1 << ") Weight    " << graph.vertices[i][j].second << std::endl;
            std::cout << "===========" << std::endl;
        }
    }
}