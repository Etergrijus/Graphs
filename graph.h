#ifndef DM41_GRAPH_H
#define DM41_GRAPH_H

#include <algorithm>
#include <fstream>

typedef std::vector<std::vector<bool>> Graph;

typedef std::vector<std::vector<int>> WeigDigraph;

typedef struct Edge {
    int vertex1;
    int vertex2;
} Edge;

namespace out {
    template<typename Type>
    void outputVector(std::vector<Type> &v) {
        for (auto i: v)
            std::cout << i << ' ';
        std::cout << '\n';
    }

    void outputGraph(Graph &g);

    void outputDigraph(WeigDigraph &d);
}

extern bool isHamiltone;

template<typename Type>
void getVector(std::vector<Type> &v, const int size, const int firstValue) {
    v.reserve(size);
    v.push_back(firstValue);
}

template<typename Type>
void resizeGraph(std::vector<std::vector<Type>>&g, const int size) {
    g.resize(size);
    for (auto &i: g)
        i.resize(size);
}

template<typename Type>
void readGraph(std::vector<std::vector<Type>>&g, std::string &filename) {
    std::ifstream f(filename);
    f.open(filename, std::ios::in);
    f.clear();

    size_t size1 = std::count(std::istreambuf_iterator<char>(f),
                              std::istreambuf_iterator<char>(), '\n') + 1;
    resizeGraph(g, size1);

    f.seekg(0, std::ios::beg);

    if (f)
        for (auto i = 0; i < g.size(); i++)
            for (auto j = 0; j < g.size(); j++) {
                Type buf;
                f >> buf;
                g[i][j] = buf;
            }
    else {
        std::cout << "Epic fail";
        return;
    }

    f.close();
}

int rSliceSearch(std::vector<int> &v, int el, int start, int end);

bool isRoute(std::vector<int> &seq, Graph &g);

bool isChain(std::vector<int> &seq, Graph &g);

bool isSimpleChain(std::vector<int> &seq, Graph &g);

bool isCycle(std::vector<int> &seq, Graph &g);

bool isSimpleCycle(std::vector<int> &seq, Graph &g);

void printAnalysisSequence(std::vector<int> &sequence, Graph &g);

void generateRoutes(Graph &g, std::vector<int> &route, int startVertex);

void generateRoutes(Graph &g, std::vector<int> &route,
                    int startVertex, int finishVertex);

void generateRoutes(Graph &g, std::vector<int> &route, int startVertex,
                    int finishVertex, size_t &countRoutes);

int getCountRoutes(Graph &g, std::vector<int> &route, int startVertex, int finishVertex);

auto getRouteCountMatrix(Graph &g, int sizeRoute);

void generateMaxSimpleChains(Graph &g, std::vector<int> &route, int startVertex);

Graph getRandomGraph(int nVertexes, float nEdges, std::mt19937 &engine);

void checkHamiltoneCycle(Graph &g, std::vector<int> &route, int startNode, int size);

std::vector<std::vector<int>> getConnectivityComponents(Graph &g);

bool isEilerCycle(Graph &g);

void printResultInFile(const char *title, const int nAll,
                       const int nHamiltons, const int nEilers);

void kruskallAlg(const int nVertexes, const Graph &g,
                 Graph &coverForest);

void convertAdjacencyToEdgesMatrix(Graph &g, std::vector<std::vector<int>> &edgesMatrix);

void getAllSpanningTrees(int nVertexes, Graph &g, std::vector<std::vector<int>> &storage);

bool dijkstraAlg(WeigDigraph &d, const int startVertex, const int finishVertex);

int getMinSimpleCycle(WeigDigraph &d);

#endif //DM41_GRAPH_H
