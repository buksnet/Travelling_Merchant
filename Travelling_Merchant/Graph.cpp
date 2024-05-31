#include "graph.h"

void graph::addvertex(const string& name)
{
    vmap::iterator itr = work.find(name);
    if (itr == work.end())
    {
        vertex* v;
        v = new vertex(name);
        work[name] = v;
        return;
    }
    cout << "\nVertex already exists!";

}

void graph::addedge(const string& from, const string& to, const double& cost)
{
    vertex* f = (work.find(from)->second);
    vertex* t = (work.find(to)->second);
    pair<int, vertex*> edge = make_pair(cost, t);
    f->adj.push_back(edge);
}

void graph::connectAll(const string & name) {
    for (auto const& x : work) {
        if (name != x.first) {
            int cost;
            cout << "Input " << name << " -> " << x.first << " cost: " << endl;
            cin >> cost;
            addedge(name, x.second->name, cost);
            addedge(x.second->name, name, cost);
        }
    }
}


void graph::removeedge(const string& name) {
    for (auto it = work.cbegin(); it != work.cend();) {
        if (it->second->name == name) {
            work.erase(it++);
        }
        else {
            ++it;
        }
    }
}

int** graph::getmatrix() {
    int** matrix = new int* [work.size()];
    return matrix;
}

void graph::solve() {

}
void graph::brute_force() {}
