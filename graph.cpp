#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

#include "graph.h"

using namespace std;

namespace out {
    void outputGraph(Graph &g) {
        for (auto i = 0; i < g.size(); i++) {
            for (auto j = 0; j < g.size(); j++) {
                cout << g[i][j] << ' ';
            }
            cout << '\n';
        }
        cout << '\n';
    }

    void outputDigraph(WeigDigraph &d) {
        for (auto &i: d)
            outputVector(i);
        cout << '\n';
    }
}

int rSliceSearch(vector<int> &v, int el, int start, int end) {
    for (auto i = end - 1; i >= start; i--)
        if (v[i] == el)
            return i;

    return -1;
}

bool isRoute(vector<int> &seq, Graph &g) {
    for (auto i = 1; i < seq.size(); i++)
        if (!g[(seq[i - 1]) - 1][(seq[i]) - 1])
            return false;

    return true;
}

bool isChain(vector<int> &seq, Graph &g) {
    if (!isRoute(seq, g))
        return false;

    vector<Edge> edges;
    edges.reserve(10);

    for (auto i = 1; i < seq.size(); i++) {
        Edge currentEdge = {seq[i - 1], seq[i]};
        if (seq[i - 1] < seq[i])
            swap(currentEdge.vertex1, currentEdge.vertex2);
        edges.push_back(currentEdge);
    }

    if (edges.size() == 0)
        return false;
    for (auto i = 0; i < edges.size() - 1; i++)
        for (auto j = i + 1; j < edges.size(); j++)
            if (edges[i].vertex1 == edges[j].vertex1 &&
                edges[i].vertex2 == edges[j].vertex2)
                return false;

    return true;
}

bool isSimpleChain(vector<int> &seq, Graph &g) {
    if (!isChain(seq, g))
        return false;

    for (auto i = 1; i < seq.size(); i++)
        if (i != rSliceSearch(seq, seq[i], i, seq.size()))
            return false;

    return true;
}

bool isCycle(vector<int> &seq, Graph &g) {
    if (!isChain(seq, g))
        return false;

    return seq[0] == seq[seq.size() - 1];
}

bool isSimpleCycle(vector<int> &seq, Graph &g) {
    return (isCycle(seq, g) && isSimpleChain(seq, g));
}

void printAnalysisSequence(vector<int> &sequence, Graph &g) {
    bool route = isRoute(sequence, g);
    cout << "This sequence is route - " << route << '\n';

    bool chain = isChain(sequence, g);
    cout << "This sequence is chain - " << chain << '\n';

    bool simpleChain = isSimpleChain(sequence, g);
    cout << "This sequence is simple chain - " << simpleChain << '\n';

    bool cycle = isCycle(sequence, g);
    cout << "This sequence is cycle - " << cycle << '\n';

    bool simpleCycle = isSimpleCycle(sequence, g);
    cout << "This sequence is simple cycle - " << simpleCycle << '\n';
}

void generateRoutes(Graph &g, vector<int> &route, int startVertex) {
    if (route.size() == route.capacity()) {
        out::outputVector(route);
        route.pop_back();
        return;
    }

    for (auto i = 0; i < g.size(); i++)
        if (g[startVertex][i]) {
            route.push_back(i + 1);
            generateRoutes(g, route, i);
        }

    route.pop_back();
}

void generateRoutes(Graph &g, vector<int> &route, int startVertex, const int finishVertex) {
    if (route.size() + 1 == route.capacity()) {
        auto rIter1 = route.rbegin();
        if (g[*rIter1 - 1][finishVertex - 1]) {
            route.push_back(finishVertex);
            out::outputVector(route);
            route.pop_back();
        }
        route.pop_back();
        return;
    }

    for (auto i = 0; i < g.size(); i++)
        if (g[startVertex][i]) {
            route.push_back(i + 1);
            generateRoutes(g, route, i, finishVertex);
        }

    route.pop_back();
}

void generateRoutes(Graph &g, vector<int> &route, int startVertex,
                    const int finishVertex, size_t &countRoutes) {
    if (route.size() + 1 == route.capacity()) {
        auto rIter1 = route.rbegin();
        if (g[*rIter1 - 1][finishVertex - 1]) {
            route.push_back(finishVertex);
            countRoutes++;
            route.pop_back();
        }
        route.pop_back();
        return;
    }

    for (auto i = 0; i < g.size(); i++)
        if (g[startVertex][i]) {
            route.push_back(i + 1);
            generateRoutes(g, route, i, finishVertex, countRoutes);
        }

    route.pop_back();
}

int getCountRoutes(Graph &g, vector<int> &route, int startVertex, int finishVertex) {
    size_t countRoutes = 0;
    generateRoutes(g, route, startVertex, finishVertex, countRoutes);

    return countRoutes;
}

auto getRouteCountMatrix(Graph &g, const int sizeRoute) {
    vector<vector<int>> routeCountMatrix;
    routeCountMatrix.resize(g.size());
    for (auto &i: routeCountMatrix)
        i.resize(g.size());

    for (auto i = 0; i < routeCountMatrix.size(); i++) {
        for (auto j = 0; j < routeCountMatrix.size(); j++) {
            vector<int> route;
            getVector(route, sizeRoute + 1, i + 1);

            routeCountMatrix[i][j] = getCountRoutes(g, route, i, j + 1);
        }
    }

    return routeCountMatrix;
}

static bool isFind = false;

void generateMaxSimpleChains(Graph &g, vector<int> &route, int startVertex) {
    if (isChain(route, g)) {
        //Max Simple Chain
        bool isMSC = true;
        for (auto col = 0; col < g.size(); col++)
            if (g[startVertex][col] && std::find(route.begin(),
                                                 route.end(), col + 1) == route.end()) {
                isMSC = false;
                break;
            }

        if (isMSC) {
            //out::outputVector(route);
            //route.pop_back();
            isFind = true;
            return;
        }
    }

    for (auto i = 0; i < g.size(); i++)
        if (g[startVertex][i] && std::find(route.begin(),
                                           route.end(), i + 1) == route.end()) {
            route.push_back(i + 1);
            generateMaxSimpleChains(g, route, i);
        }

    if (isFind || route.size() == 1)
        return;
    route.pop_back();
}

Graph getRandomGraph(int nVertexes, float nEdges, std::mt19937 &engine) {
    Graph g;
    resizeGraph(g, nVertexes);

    std::uniform_real_distribution<float> dist(0.0, 0.9999);

    int edges = floor(nEdges);
    for (auto i = 0; i < edges; i++) {
        auto randVal = floor(pow(g.size(), 2) * dist(engine));
        auto y = floor(randVal / nVertexes);
        auto x = randVal - y * nVertexes;

        if (!g[y][x] && y != x) {
            g[y][x] = true;
            g[x][y] = true;
        } else if (edges < nVertexes * nVertexes)
            edges++;
    }

    return g;
}


bool isHamiltone = false;

void checkHamiltoneCycle(Graph &g, vector<int> &route, int startNode, int size) {
    if (isSimpleCycle(route, g) && route.size() == size + 1 /*|| isHamiltone*/) {
        //out::outputVector(route);
        //route.pop_back();
        isHamiltone = true;
        return;
    }

    for (auto i = 0; i < g.size(); i++)
        if (g[startNode][i])
            if (route.size() == size || std::find(route.begin(),
                                                  route.end(), i + 1) == route.end()) {
                route.push_back(i + 1);
                checkHamiltoneCycle(g, route, i, size);
            }

    if (isHamiltone)
        return;

    route.pop_back();
}

vector<vector<int>> getConnectivityComponents(Graph &g) {
    vector<vector<int>> result;
    result.reserve(3);

    vector<int> vertexes(g.size());
    for (auto i = 1; i <= vertexes.size(); i++)
        vertexes[i - 1] = i;

    int startVertex = 1;
    while (startVertex <= g.size()) {
        if (std::count(vertexes.begin(), vertexes.end(), vertexes[startVertex - 1]) != 1) {
            startVertex++;
            continue;
        }

        vector<int> route;
        getVector(route, 5, startVertex);
        generateMaxSimpleChains(g, route, startVertex - 1);

        for (int i: route)
            vertexes[i - 1] = vertexes[startVertex - 1];
        result.push_back(route);
        startVertex++;
    }

    return result;
}

bool isEilerCycle(Graph &g) {
    vector<vector<int>> connect = getConnectivityComponents(g);

    //Only Component with Edges
    bool isOCE = false;
    for (auto &i: connect) {
        if (i.size() > 1 && !isOCE)
            isOCE = true;
        else if (isOCE)
            return false;
    }

    if (!isOCE)
        return false;

    for (auto i = 0; i < g.size(); i++) {
        if (std::count(g[i].begin(), g[i].end(), 1) % 2 != 0)
            return false;
    }

    return true;
}

void printResultInFile(const char *title, const int nAll,
                       const int nHamiltons, const int nEilers) {
    char filename[128];
    sprintf(filename, "./data/%s.csv", title);

    FILE *f = fopen(filename, "a");
    if (f == nullptr)
        exit(1);
    else
        fprintf(f, "%d; %d; %d\n", nEilers, nHamiltons, nAll);

    fclose(f);
}

void kruskallAlg(const int nVertexes, const Graph &g,
                 Graph &coverForest) {
    int vertexes[nVertexes];
    for (auto i = 1; i <= nVertexes; i++)
        vertexes[i - 1] = i;

    int startPos = 1;
    for (auto i = 0; i < g.size(); i++) {
        for (auto j = startPos; j < g.size(); j++)
            if (g[i][j])
                if (vertexes[i] != vertexes[j]) {
                    vertexes[j] = vertexes[i];
                    coverForest[i][j] = true;
                    coverForest[j][i] = true;

                }
        startPos++;
    }
}

void convertAdjacencyToEdgesMatrix(Graph &g, vector<vector<int>> &edgesMatrix) {
    int countEdges = 0;
    int startPos = 1;

    for (auto i = 0; i < g.size(); i++) {
        for (auto j = startPos; j < g.size(); j++)
            if (g[i][j]) {
                edgesMatrix[i][j] = ++countEdges;
                edgesMatrix[j][i] = countEdges;
            }
        startPos++;
    }
}

Graph getDeletingEdges(const Graph &g1, const Graph &g2) {
    Graph result = g1;

    int startPos = 1;
    for (int i = 0; i < g1.size(); i++) {
        for (int j = startPos; j < g1.size(); j++)
            if (g1[i][j] && g2[i][j]) {
                result[i][j] = false;
                result[j][i] = false;
            }
        startPos++;
    }

    return result;
}

bool isNoIsolatedVertexes(const vector<vector<int>> &comps) {
    for (auto &i: comps)
        if (i.size() == 1)
            return false;

    return true;
}

void removeVertex(int *vertexes, vector<vector<int>> &edgesMatrix, vector<int> &tree,
                  Graph &forest) {
    for (auto &i: edgesMatrix) {
        auto posCol = std::find(i.begin(), i.end(), *tree.rbegin());
        if (posCol != i.end()) {
            int numberCol = std::distance(i.begin(), posCol);
            vertexes[numberCol] = numberCol + 1;

            auto posRow = std::find(edgesMatrix.begin(), edgesMatrix.end(), i);
            int numberRow = std::distance(edgesMatrix.begin(), posRow);
            forest[numberRow][numberCol] = false;
            forest[numberCol][numberRow] = false;

            break;
        }
    }

    tree.pop_back();
}

void checkSolvingTask(const Graph &g, Graph &forest, vector<int> &tree,
                      vector<vector<int>> &storage) {
    Graph applicant = getDeletingEdges(g, forest);
    auto comps = getConnectivityComponents(applicant);
    if (comps.size() == 2 && isNoIsolatedVertexes(comps)) {
        sort(tree.begin(), tree.end());
        if (std::find(storage.begin(), storage.end(), tree) == storage.end())
            storage.push_back(tree);
    }
}

vector<vector<int>> _getAllSpanningTrees(int *vertexes, const int nEdges, const Graph &g, Graph &forest,
                                         vector<vector<int>> &edgesMatrix, vector<int> &tree,
                                         vector<vector<int>> &storage) {
    if (tree.size() == nEdges) {
        checkSolvingTask(g, forest, tree, storage);
        removeVertex(vertexes, edgesMatrix, tree, forest);
        return storage;
    }

    int startPos = 1;
    for (auto i = 0; i < edgesMatrix.size(); i++) {
        for (auto j = startPos; j < edgesMatrix.size(); j++) {
            auto value = edgesMatrix[i][j];
            if (value && (tree.empty() || std::find(tree.begin(), tree.end(), value) ==
                                          tree.end())) {
                tree.push_back(value);
                vertexes[j] = vertexes[i];

                forest[i][j] = true;
                forest[j][i] = true;

                checkSolvingTask(g, forest, tree, storage);

                if (tree.size() != 1 && *tree.rbegin() < *(tree.rbegin() + 1) && vertexes[i] == vertexes[j]) {
                    removeVertex(vertexes, edgesMatrix, tree, forest);
                    continue;
                }

                _getAllSpanningTrees(vertexes, nEdges, g, forest, edgesMatrix, tree, storage);
            }
        }
        startPos++;
    }

    removeVertex(vertexes, edgesMatrix, tree, forest);

    return storage;
}

void getAllSpanningTrees(int nVertexes, Graph &g, vector<vector<int>> &storage) {
    int vertexes[nVertexes];
    for (auto i = 1; i <= nVertexes; i++)
        vertexes[i - 1] = i;

    vector<vector<int>> edgesMatrix;
    edgesMatrix.resize(g.size());
    for (auto &i: edgesMatrix)
        i.resize(g.size());
    convertAdjacencyToEdgesMatrix(g, edgesMatrix);

    vector<int> tree;
    tree.reserve(nVertexes - 1);

    Graph forest;
    resizeGraph(forest, g.size());

    _getAllSpanningTrees(vertexes, nVertexes - 1, g, forest, edgesMatrix, tree, storage);
}

int getMinOfUnseen(const vector<bool> &v, vector<int> &deltas) {
    int localMin = INT16_MAX;
    int pos = -1;
    for (int i = 0; i < v.size(); i++)
        if (!v[i] && deltas[i] < localMin) {
            localMin = deltas[i];
            pos = i;
        }

    return pos;
}

bool dijkstraAlg(WeigDigraph &d, const int startVertex, const int finishVertex) {
    int nVertexes = d.size();
    vector<bool> vertexes(nVertexes);
    vertexes[startVertex - 1] = true;

    vector<int> deltas(nVertexes);
    deltas[startVertex - 1] = 0;
    for (int i = 1; i <= deltas.size(); i++)
        if (i != startVertex)
            deltas[i - 1] = INT16_MAX;

    vector<int> tree(nVertexes);
    tree[startVertex - 1] = 0;
    for (int i = 1; i <= tree.size(); i++)
        if (i != startVertex)
            tree[i - 1] = -1;

    int newVertex = startVertex - 1;
    while (std::find(vertexes.begin(), vertexes.end(), false) != vertexes.end()) {
        for (int i = 0; i < nVertexes; i++) {
            int weight = d[newVertex][i];
            if (weight) {
                auto savedValue = deltas[i];
                deltas[i] = min(deltas[i], deltas[newVertex] + weight);

                if (savedValue != deltas[i])
                    tree[i] = newVertex + 1;
            }
        }

        newVertex = getMinOfUnseen(vertexes, deltas);
        if (newVertex == -1)
            return false;
        else
            vertexes[newVertex] = true;
    }

/*    out::outputVector(vertexes);
    out::outputVector(deltas);
    out::outputVector(tree);*/

    cout << deltas[finishVertex - 1];

    return true;
}

int dijkstraAlg_(WeigDigraph &d, const int startVertex, const int finishVertex) {
    int nVertexes = d.size();
    vector<bool> vertexes(nVertexes);
    vertexes[startVertex - 1] = true;

    vector<int> deltas(nVertexes);
    deltas[startVertex - 1] = 0;
    for (int i = 1; i <= deltas.size(); i++)
        if (i != startVertex)
            deltas[i - 1] = INT16_MAX;

    vector<int> tree(nVertexes);
    tree[startVertex - 1] = 0;
    for (int i = 1; i <= tree.size(); i++)
        if (i != startVertex)
            tree[i - 1] = -1;

    vector<int> route;
    getVector(route, 4, startVertex);

    int newVertex = startVertex - 1;
    int oldVertex = newVertex;
    while (std::find(vertexes.begin(), vertexes.end(), false) != vertexes.end()) {
        for (int i = 0; i < nVertexes; i++) {
            int weight = d[newVertex][i];
            if (weight) {
                auto savedValue = deltas[i];

                if (i == startVertex - 1 && deltas[i] == 0)
                    deltas[i] = deltas[newVertex] + weight;
                else
                    deltas[i] = min(deltas[i], deltas[newVertex] + weight);

                if (savedValue != deltas[i]) {
                    tree[i] = newVertex + 1;

                    if (i == finishVertex - 1) {
                        route.push_back(i + 1);
                        if (*route.begin() == *route.rbegin()) {
                            for (int j = 1; j < route.size(); j++)
                                if (j != rSliceSearch(route, route[j], j, route.size()))
                                    return INT16_MAX;
                        } else
                            return INT16_MAX;
                        return deltas[finishVertex - 1];
                    }
                }
            }
        }

        newVertex = getMinOfUnseen(vertexes, deltas);

        if (newVertex == -1)
            return INT16_MAX;
        else
            vertexes[newVertex] = true;

        if (!d[oldVertex][newVertex])
            route.pop_back();
        route.push_back(newVertex + 1);
        oldVertex = newVertex;
    }
}

int getMinSimpleCycle(WeigDigraph &d) {
    int result = INT16_MAX;
    int startVertex = 1;
    while (startVertex <= d.size()) {
        int localMin = dijkstraAlg_(d, startVertex, startVertex);
        if (localMin < result)
            result = localMin;
        startVertex++;
    }

    return result;
}