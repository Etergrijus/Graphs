#include <iostream>
#include <vector>
#include <ctime>
#include <random>
#include <cstring>
#include <set>

#include "graph.h"

using namespace std;
/*
void task4(Graph &g1, Graph &g2) {
    int sizeRoute, startNode;
    cout << "\nInput the size of route and the starting node\n";
    cin >> sizeRoute;
    cin >> startNode;

    vector<int> route;
    getVector(route, sizeRoute + 1, startNode);

    int graphNumber;
    cout << "Enter number of the graph you want to work with (1 or 2)\n";
    cin >> graphNumber;
    if (graphNumber == 1)
        generateRoutes(g1, route, startNode - 1);
    else
        generateRoutes(g2, route, startNode - 1);
}

void task5(Graph &g1, Graph &g2) {
    int sizeRoute, startNode, finishNode;
    cout << "\nInput the size of route, the starting node and the ending node\n";
    cin >> sizeRoute;
    cin >> startNode;
    cin >> finishNode;

    vector<int> route;
    getVector(route, sizeRoute + 1, startNode);

    int graphNumber;
    cout << "Enter number of the graph you want to work with (1 or 2)\n";
    cin >> graphNumber;
    if (graphNumber == 1)
        generateRoutes(g1, route, startNode - 1, finishNode);
    else
        generateRoutes(g2, route, startNode - 1, finishNode);
}

void task6(Graph &g1, Graph &g2) {
    int sizeRoute;
    cout << "\nInput the size of route\n";
    cin >> sizeRoute;

    int graphNumber;
    cout << "Enter number of the graph you want to work with (1 or 2)\n";
    cin >> graphNumber;

    vector<vector<int>> result;
    if (graphNumber == 1)
        result = getRouteCountMatrix(g1, sizeRoute);
    else
        result = getRouteCountMatrix(g2, sizeRoute);

    for (auto i = 0; i < result.size(); i++) {
        for (auto j = 0; j < result.size(); j++) {
            cout << result[i][j] << ' ';
        }
        cout << '\n';
    }
    cout << '\n';
}

void task7(Graph &g1, Graph &g2) {
    int startNode;
    cout << "\nInput the starting node\n";
    cin >> startNode;

    int graphNumber;
    cout << "Enter number of the graph you want to work with (1 or 2)\n";
    cin >> graphNumber;

    vector<int> route;
    if (graphNumber == 1) {
        getVector(route, g1.size(), startNode);
        generateMaxSimpleChains(g1, route, startNode - 1);
    }
    else {
        getVector(route, g2.size(), startNode);
        generateMaxSimpleChains(g2, route, startNode - 1);
    }
}*/

//Lab 4.1
/*int main() {
    Graph g1;
    string filename1 = "graph1.txt";
    readGraph(g1, filename1);

    Graph g2;
    string filename2 = "graph2.txt";
    readGraph(g2, filename2);

    //outputGraph(g1);
    //outputGraph(g2);


    const vector<vector<int>> sequences{
            {3, 5, 6, 7, 1, 2},
            {3, 6, 7, 1, 2, 6, 5},
            {4, 3, 6, 5, 4},
            {5, 5, 7, 6, 3, 5},
            {5, 3, 6, 7, 1, 6, 5}
    };

    int nSequences = 0;
    for (auto i: sequences) {
        cout << "sequence " << ++nSequences << ":\n";
        for (auto nGraphs = 0; nGraphs < 2; nGraphs++)
            if (nGraphs == 0) {
                cout << "Analysis in graph 1:\n";
                printAnalysisSequence(i, g1);
            } else {
                cout << "Analysis in graph 2:\n";
                printAnalysisSequence(i, g2);
            }
        cout << '\n';
    }

    //task4(g1, g2);
    //task5(g1, g2);
    //task6(g1, g2);
    //task7(g1, g2);

    return 0;
}*/

//Lab 4.2
/*int main() {
#define TEN_SECONDS_TIME 10

    static int nAllGraphs;
    static int nHamiltons;
    static int nEilers;

    std::mt19937 engine;
    engine.seed(time(nullptr));

    int nVertexes;
    cin >> nVertexes;
    float nEdges = nVertexes;

    clock_t startTime = clock();
    clock_t endTime = clock();

    int nGrowings = 0;
    while ((endTime - startTime) / CLOCKS_PER_SEC <= TEN_SECONDS_TIME) {
        Graph g = getRandomGraph(nVertexes, nEdges, engine);
        nAllGraphs++;
        //out::outputGraph(g);

        nGrowings++;
        vector<int> route;
        getVector(route, g.size(), 1);

        isHamiltone = false;
        checkGamiltoneCycle(g, route, 0, g.size());

        if (isHamiltone)
            nHamiltons++;
        if (isEilerCycle(g))
            nEilers++;

        nEdges += 0.0015;

        endTime = clock();

        if (nGrowings == 666) {
            char title[10] = "size - ";
            char intToStr[10] = "";
            sprintf(intToStr, "%d", nVertexes);
            strcat(title, intToStr);
            printResultInFile(title, nAllGraphs, nHamiltons, nEilers);

            nGrowings = 0;
        }
    }

    cout << nAllGraphs << ' ' << nHamiltons << ' ' << nEilers;
}*/

int getCountEdges(Graph &g) {
    int result = 0;
    int startPos = 1;
    for (auto i = 0; i < g.size(); i++) {
        for (auto j = startPos; j < g.size(); j++)
            if (g[i][j])
                result++;
        startPos++;
    }

    return result;
}

void putInBouq(set<int> &s, vector<vector<int>> &bouq,
               const int value, const int bouqNumber) {
    int val = *s.find(value);
    bouq[bouqNumber].push_back(val);
    s.erase(value);
}

//Lab 4.3
//As I walk
//With a spirit
//Into the binding forest
//In fog and darkness
//I walk
//I disappear
//Into the mighty forest
int main() {
    Graph g;
    string filename = "graph2.txt";
    readGraph(g, filename);

    out::outputGraph(g);
    cout << "------\n";

    int nVertexes = g.size();
    Graph coverForest;
    resizeGraph(coverForest, g.size());
    kruskallAlg(nVertexes, g, coverForest);

    out::outputGraph(coverForest);

    cout << "------\n";

/*    auto n = getConnectivityComponents(g);
    cout << n.size();*/

    vector<vector<int>> storage;
    storage.reserve(10);

    getAllSpanningTrees(nVertexes, nVertexes - 1, g, storage);

    for (auto &i: storage)
        out::outputVector(i);
}