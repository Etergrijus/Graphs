#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <random>

#include "graph.h"

using namespace std;

namespace out {
    void outputVector(vector<int> &v) {
        for (auto i: v)
            cout << i << ' ';
        cout << '\n';
    }

    void outputGraph(Graph &g) {
        for (auto i = 0; i < g.size(); i++) {
            for (auto j = 0; j < g.size(); j++) {
                cout << g[i][j] << ' ';
            }
            cout << '\n';
        }
        cout << '\n';
    }
}

void resizeGraph(Graph &g, const int size) {
    g.resize(size);
    for (auto &i: g)
        i.resize(size);
}

void readGraph(Graph &g, string &filename) {
    ifstream f(filename);
    f.open(filename, ios::in);
    f.clear();

    size_t size1 = std::count(istreambuf_iterator<char>(f),
                              istreambuf_iterator<char>(), '\n') + 1;
    resizeGraph(g, size1);

    f.seekg(0, ios::beg);

    if (f)
        for (auto i = 0; i < g.size(); i++)
            for (auto j = 0; j < g.size(); j++) {
                bool buf;
                f >> buf;
                g[i][j] = buf;
            }
    else {
        cout << "Epic fail";
        return;
    }

    f.close();
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

void checkGamiltoneCycle(Graph &g, vector<int> &route, int startNode, int size) {
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
                checkGamiltoneCycle(g, route, i, size);
            }

    if (isHamiltone)
        return;

    route.pop_back();
}

vector<vector<int>> getConnectivityComponents(Graph &g) {
    vector<vector<int>> result;
    result.reserve(3);

/*    int vertexes[g.size()];
    for (auto i = 1; i <= g.size(); i++)
        vertexes[i - 1] = i;*/
    vector<int> vertexes (g.size());
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
    /*Graph result;
    resizeGraph(result, g1.size());*/
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

void getAllSpanningTrees(int *vertexes, const int nEdges, const Graph &g, Graph &forest,
                         vector<vector<int>> &edgesMatrix, vector<int> &tree) {
    if (tree.size() == nEdges) {
        Graph applicant = getDeletingEdges(g, forest);
        auto comps = getConnectivityComponents(applicant);
        if (comps.size() == 2 && isNoIsolatedVertexes(comps))
            out::outputVector(tree);

        //out::outputVector(tree);
        removeVertex(vertexes, edgesMatrix, tree, forest);
        return;
    }

    int startPos = 1;
    for (auto i = 0; i < edgesMatrix.size(); i++) {
        for (auto j = startPos; j < edgesMatrix.size(); j++)
            if (edgesMatrix[i][j])
                if (tree.empty() || edgesMatrix[i][j] > *tree.rbegin() && vertexes[i] != vertexes[j]) {
                    tree.push_back(edgesMatrix[i][j]);
                    vertexes[j] = vertexes[i];

                    forest[i][j] = true;
                    forest[j][i] = true;

                    getAllSpanningTrees(vertexes, nEdges, g, forest, edgesMatrix, tree);
                }
        startPos++;
    }

    removeVertex(vertexes, edgesMatrix, tree, forest);
}