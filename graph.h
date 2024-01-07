#ifndef DM41_GRAPH_H
#define DM41_GRAPH_H

typedef std::vector<std::vector<bool>> Graph;

typedef struct Edge {
    int vertex1;
    int vertex2;
} Edge;

namespace out {
    void outputVector(std::vector<int> &v);

    void outputGraph(Graph &g);
}

extern bool isHamiltone;

template<typename Type>
void getVector(std::vector<Type> &v, const int size, const int firstValue) {
    v.reserve(size);
    v.push_back(firstValue);
}

void resizeGraph(Graph &g, const int size);

void readGraph(Graph &g, std::string &filename);

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

void checkGamiltoneCycle(Graph &g, std::vector<int> &route, int startNode, int size);

std::vector<std::vector<int>> getConnectivityComponents(Graph &g);

bool isEilerCycle(Graph &g);

void printResultInFile(const char *title, const int nAll,
                       const int nHamiltons, const int nEilers);

void kruskallAlg(const int nVertexes, const Graph &g,
                 Graph &coverForest);

void convertAdjacencyToEdgesMatrix(Graph &g, std::vector<std::vector<int>> &edgesMatrix);

void getAllSpanningTrees(int nVertexes, int nEdges, Graph &g, std::vector<std::vector<int>> &storage);

#endif //DM41_GRAPH_H
