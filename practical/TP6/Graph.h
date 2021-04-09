/*
 * Graph.h
 */
#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <queue>
#include <list>
#include <limits>
#include <cmath>
#include "MutablePriorityQueue.h"


template <class T> class Edge;
template <class T> class Graph;
template <class T> class Vertex;

#define INF std::numeric_limits<double>::max()

/************************* Vertex  **************************/

template <class T>
class Vertex {
    T info;						// content of the vertex
    std::vector<Edge<T> > adj;		// outgoing edges

    size_t setIdx;

    double dist = 0;
    Vertex<T> *path = NULL;
    int queueIndex = 0; 		// required by MutablePriorityQueue

    bool visited = false;		// auxiliary field
    bool processing = false;	// auxiliary field

    void addEdge(Vertex<T> *dest, double w);

public:
    Vertex(T in);
    T getInfo() const;
    double getDist() const;
    Vertex *getPath() const;
    size_t getIdx() const;

    bool operator<(Vertex<T> & vertex) const; // // required by MutablePriorityQueue
    friend class Graph<T>;
    friend class MutablePriorityQueue<Vertex<T>>;
};


template <class T>
Vertex<T>::Vertex(T in): info(in) {}

/*
 * Auxiliary function to add an outgoing edge to a vertex (this),
 * with a given destination vertex (d) and edge weight (w).
 */
template <class T>
void Vertex<T>::addEdge(Vertex<T> *d, double w) {
    adj.push_back(Edge<T>(d, w));
}

template <class T>
bool Vertex<T>::operator<(Vertex<T> & vertex) const {
    return this->dist < vertex.dist;
}

template <class T>
T Vertex<T>::getInfo() const {
    return this->info;
}

template <class T>
double Vertex<T>::getDist() const {
    return this->dist;
}

template <class T>
Vertex<T> *Vertex<T>::getPath() const {
    return this->path;
}

/********************** Edge  ****************************/

template <class T>
class Edge {
    Vertex<T> * dest;      // destination vertex
    double weight;         // edge weight
public:
    Edge(Vertex<T> *d, double w);
    friend class Graph<T>;
    friend class Vertex<T>;
};

template <class T>
Edge<T>::Edge(Vertex<T> *d, double w): dest(d), weight(w) {}


/*************************** Graph  **************************/

template <class T>
class Graph {
    std::vector<Vertex<T> *> vertexSet;    // vertex set
    std::vector<Edge<T>> edgeSet;
    std::vector<std::vector<double>> floydMatrix;
    std::vector<std::vector<size_t>> floydNext;
public:
    Vertex<T> *findVertex(const T &in) const;
    bool addVertex(const T &in);
    bool addEdge(const T &sourc, const T &dest, double w);
    int getNumVertex() const;
    std::vector<Vertex<T> *> getVertexSet() const;

    // Fp06 - single source
    void unweightedShortestPath(const T &s);    //TODO...
    void dijkstraShortestPath(const T &s);      //TODO...
    void bellmanFordShortestPath(const T &s);   //TODO...
    std::vector<T> getPath(const T &origin, const T &dest) const;   //TODO...

    // Fp06 - all pairs
    void floydWarshallShortestPath();   //TODO...
    std::vector<T> getfloydWarshallPath(const T &origin, const T &dest) const;   //TODO...

};

template<class T>
size_t Vertex<T>::getIdx() const {
    return setIdx;
}

template <class T>
int Graph<T>::getNumVertex() const {
    return vertexSet.size();
}

template <class T>
std::vector<Vertex<T> *> Graph<T>::getVertexSet() const {
    return vertexSet;
}

/*
 * Auxiliary function to find a vertex with a given content.
 */
template <class T>
Vertex<T> * Graph<T>::findVertex(const T &in) const {
    for (auto v : vertexSet)
        if (v->info == in)
            return v;
    return NULL;
}

/*
 *  Adds a vertex with a given content or info (in) to a graph (this).
 *  Returns true if successful, and false if a vertex with that content already exists.
 */
template <class T>
bool Graph<T>::addVertex(const T &in) {
    if ( findVertex(in) != NULL)
        return false;
    Vertex<T>* v = new Vertex<T>(in);
    v->setIdx = vertexSet.size();
    vertexSet.push_back(v);
    return true;
}

/*
 * Adds an edge to a graph (this), given the contents of the source and
 * destination vertices and the edge weight (w).
 * Returns true if successful, and false if the source or destination vertex does not exist.
 */
template <class T>
bool Graph<T>::addEdge(const T &sourc, const T &dest, double w) {
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == NULL || v2 == NULL)
        return false;
    v1->addEdge(v2,w);
    edgeSet.template emplace_back(v2,w);
    return true;
}


/**************** Single Source Shortest Path algorithms ************/

template<class T>
void Graph<T>::unweightedShortestPath(const T &orig) {
    for (auto & v : vertexSet) {
        v->dist = MAXFLOAT;
        v->visited = false;
        v->path = nullptr;
    }
    Vertex<T> *v = findVertex(orig);
    if (v == NULL) return;
    v->dist = 0;

    std::queue<Vertex<T> *> vertices;
    vertices.push(v);

    while (!vertices.empty()) {
        v = vertices.front(); vertices.pop();
        for (Edge<T> & edge: v->adj) {
            Vertex<T> *dest = edge.dest;
            if (!dest->visited) {
                vertices.push(dest);
                dest->visited = true;
            }
            if (dest->dist > v->dist + 1) {
                dest->path = v;
                dest->dist = v->dist + 1;
            }
        }
    }
    
}


template<class T>
void Graph<T>::dijkstraShortestPath(const T &origin) {
    for (auto & v : vertexSet) {
        v->dist = MAXFLOAT;
        v->visited = false;
        v->path = nullptr;
    }
    Vertex<T> *v = findVertex(origin); if (v == NULL) return;
    v->dist = 0;

    MutablePriorityQueue<Vertex<T>> vertices;
    vertices.insert(v);
    while (!vertices.empty()) {
        v = vertices.extractMin();
        for (Edge<T> e: v->adj) {
            Vertex<T> *curr = e.dest;
            if (curr->dist > v->dist + e.weight) {
                curr->dist = v->dist + e.weight;
                curr->path = v;
                if (curr->visited) vertices.decreaseKey(curr);
                else {
                    curr->visited = true;
                    vertices.insert(curr);
                }
            }
        }
    }
}


template<class T>
void Graph<T>::bellmanFordShortestPath(const T &orig) {
    for (auto & v : vertexSet) {
        v->dist = MAXFLOAT;
        v->path = nullptr;
    }

    Vertex<T>* org = findVertex(orig);
    if (org == nullptr) return;
    org->dist = 0;

    for (int i = 0; i < vertexSet.size() - 1; ++i) {
        bool changed = false;
        for (Vertex<T> * v : vertexSet) {
            for (Edge<T> & e: v->adj) {
                Vertex<T>* dest = e.dest;
                if (dest->dist > v->dist + e.weight) {
                    dest->dist = v->dist + e.weight;
                    dest->path = v;
                    changed = true;
                }
            }
        }
        if (!changed)
            break;
    }

    for (Vertex<T> * v : vertexSet) {
        for (Edge<T> & e: v->adj) {
            Vertex<T>* dest = e.dest;
            if (dest->dist > v->dist + e.weight)
                dest->dist = -MAXFLOAT;
        }
    }

}


template<class T>
std::vector<T> Graph<T>::getPath(const T &origin, const T &dest) const{
    std::vector<T> res;
    Vertex<T>* org = findVertex(origin); if (org == nullptr) return res;
    Vertex<T>* dst = findVertex(dest); if (dst == nullptr) return res;

    while (dst != org && dst->path != nullptr) {
        res.insert(res.begin(), dst->info);
        dst = dst->path;
    }

    res.insert(res.begin(), dst->info);

    return res;
}



/**************** All Pairs Shortest Path  ***************/

template<class T>
void Graph<T>::floydWarshallShortestPath() {
    floydMatrix = std::vector<std::vector<double>>(vertexSet.size(), std::vector<double>(vertexSet.size(), MAXFLOAT));
    floydNext = std::vector<std::vector<size_t>>(vertexSet.size(), std::vector<size_t>(vertexSet.size(), -1));
    for (int i = 0; i < vertexSet.size(); ++i) {
        for (Edge<T> &e: vertexSet[i]->adj) {
            floydMatrix[i][e.dest->setIdx] = e.weight;
            floydNext[i][e.dest->setIdx] = e.dest->setIdx;
        }
        floydMatrix[i][i] = 0;
    }

    for (int k = 0; k < vertexSet.size(); ++k) {
        for (int i = 0; i < vertexSet.size(); ++i) {
            for (int j = 0; j < vertexSet.size(); ++j) {
                if (floydMatrix[i][k] + floydMatrix[k][j] < floydMatrix[i][j]) {
                    floydMatrix[i][j] = floydMatrix[i][k] + floydMatrix[k][j];
                    floydNext[i][j] = floydNext[i][k];
                }
            }
        }
    }
}

template<class T>
std::vector<T> Graph<T>::getfloydWarshallPath(const T &orig, const T &dest) const {
    std::vector<T> res;

    auto v1 = findVertex(orig);
    auto v2 = findVertex(dest);
    if (v1 == NULL || v2 == NULL)
        return res;

    while (v1 != v2) {
        res.push_back(v1->info);
        v1 = vertexSet[floydNext[v1->setIdx][v2->setIdx]];
    }

    res.push_back(v1->info);

    return res;
}


#endif /* GRAPH_H_ */
