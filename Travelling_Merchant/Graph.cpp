#include "graph.h"
#include <iomanip>

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

void graph::initmatrix()
{
    cout <<  "adjacency matrix:" << endl;
    datamatrix.resize(work.size());
    for (int i = 0; i < work.size(); i++) {
        datamatrix[i].resize(work.size());
    }
    vmap::iterator it = work.begin();
    empty_space();
    cout << " | " << setw(5) << "'" + (*it).second->name + "'";
    for (int i = 0; i < work.size(); i++) {
        for (int j = 0; j < work.size(); j++) {
            datamatrix[i][j] = (*it).second->adj[j].first;
        }
        it++;
        if (it != work.cend()) cout << " | " << setw(5) << "'" + (*it).second->name + "'";
    }
    cout << endl; underscore(work.size()); cout << endl;
    it = work.begin();
    for (int i = 0; i < work.size(); i++) {
        cout << setw(5) << "'" + (*it).second->name + "' | ";
        it++;
        for (int j = 0; j < work.size()-1; j++) {
            cout << setw(5) << left << datamatrix[i][j] << " | ";
        }
        cout << setw(5) << left << datamatrix[i][work.size() - 1] << endl;
    }
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
        else {
            addedge(name, x.second->name, -1);
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


void graph::solve() {
    initmatrix();

}

void graph::underscore(int q)
{
    for (int i = 0; i < q; i++) {
        cout << "--------";
    }
    cout << "--";
}

void graph::empty_space() {
    int max = 0;
    for (auto const& it : work) {
        if (it.second->name.size() > max) max = it.second->name.size();
    }
    cout << setw(max+2) << " ";
}
