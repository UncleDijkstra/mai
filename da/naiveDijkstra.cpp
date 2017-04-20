#include <iostream>
#include <vector>
// #include <queue>
#include <algorithm>
#include <ctime>

const long long int INF = LLONG_MAX;

struct Graph{
    std::vector<std::vector< std::pair<int,int> > > vertices;
    std::vector<bool> visited;
    int nOfVertices;
    int nOfEdge;
};

void CreateGraph(Graph &graph, int &start, int &finish);
void PrintGraph(Graph &graph, int start, int finish);
long long int Dijkstra(Graph &graph, int start, int finish);

int main() {
    double start_time = clock();
    int start;
    int finish;
    long long int res;
    Graph graph;
    CreateGraph(graph, start, finish);
    // PrintGraph(graph, start, finish);
    res = graph.nOfVertices > 0 ? Dijkstra(graph, start - 1, finish - 1) : -1;
    if(res < 0) {
        std::cout << "No solution" << std::endl;
    } else {
        std::cout << res << std::endl;
    }
    double end_time = clock();
    double search_time = end_time - start_time;
    printf("Dynamic time: %f sec\n", (double)search_time/CLOCKS_PER_SEC);
    return 0;
}

long long int Dijkstra(Graph &graph, int start, int finish) {
    int countOfVisited = graph.nOfVertices - 1;
    int active = start;
    std::vector<long long int> dist(graph.nOfVertices);
    for(int i = 0; i < graph.nOfVertices; ++i) {
        dist[i] = INF;
        graph.visited[i] = false;
    }
    dist[start] = 0;
    while(countOfVisited--) {
        graph.visited[active] = true;
        for(int i = 0; i < graph.vertices[active].size(); ++i) {
            if(!graph.visited[graph.vertices[active][i].first] &&
                dist[graph.vertices[active][i].first] > 
                graph.vertices[active][i].second + dist[active]) {
                dist[graph.vertices[active][i].first] = 
                    graph.vertices[active][i].second + dist[active];
            }
        }
        int v = -1;
        for(int i = 0; i < graph.nOfVertices; ++i) {
            if(!graph.visited[i] && (v == -1 || dist[i] < dist[v])) {
                v = i;
            }
        }
        if (dist[v] == INF) {
            break;
        }
        active = v;
    }
    if(dist[finish] == INF) {
        return -1;
    }
    return dist[finish];
}

void CreateGraph(Graph &graph, int &start, int &finish) {
    int vertex1;
    int vertex2;
    int weight;
    std::cin >> graph.nOfVertices 
             >> graph.nOfEdge
             >> start
             >> finish;
    graph.vertices.resize(graph.nOfVertices);
    graph.visited.resize(graph.nOfVertices);
    while(std::cin >> vertex1
                   >> vertex2
                   >> weight) {
        graph.vertices[vertex1 - 1].push_back(std::pair<int, int>(vertex2 - 1, weight));
        graph.vertices[vertex2 - 1].push_back(std::pair<int, int>(vertex1 - 1, weight));
    }
}

void PrintGraph(Graph &graph, int start, int finish) {
    for(int i = 0; i < graph.nOfVertices; ++i) {
        std::cout << ">  Vertex " << i + 1 << std::endl; 
        for(int j = 0; j < graph.vertices[i].size(); ++j) {
            std::cout << j + 1 << ") Vertex    " << graph.vertices[i][j].first + 1 << std::endl;
            std::cout << j + 1 << ") Weight    " << graph.vertices[i][j].second << std::endl;
            std::cout << "===========" << std::endl;
        }
    }
}