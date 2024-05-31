#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <string>

using namespace std;

struct vertex {
    typedef pair<int, vertex*> ve;
    vector<ve> adj; //cost of edge, destination vertex
    string name;
    vertex(string s) : name(s) {}
};

class graph
{
public:
    typedef map<string, vertex*> vmap; // dict of string and vertex (name: vertex)
    vmap work;
    int** getmatrix();
    void connectAll(const string&);
    void addvertex(const string&);
    void addedge(const string& from, const string& to, const double& cost);
    void removeedge(const string&);
    void solve();
    void brute_force();
};