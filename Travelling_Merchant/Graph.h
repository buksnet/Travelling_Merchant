#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <list>
#include <fstream>
using namespace std;

struct vertex {
    typedef pair<int, vertex*> ve;
    vector<ve> adj; //cost of edge, destination vertex
    string name;
    vertex(string s) : name(s) {}
};

class graph
{
    list<string> result;
public:
    vector<vector<int>> datamatrix;
    typedef map<string, vertex*> vmap; // dict of string and vertex (name: vertex)
    list<string> vertexes;
    vmap work;
    void initmatrix();
    void connectAll(const string&);
    void addvertex(const string&);
    void addedge(const string& from, const string& to, const double& cost);
    void removeedge(const string&);
    void empty_space();
    static void underscore(int q);
    static int min(vector<int> pile);
    
};

class LittleAlgorithm {
public:
    vector<vector<int>> data;
    vector<pair<int, int>> result;
    vector<pair<int, int>> export_result;
    LittleAlgorithm();
    LittleAlgorithm(vector<vector<int>>);
    LittleAlgorithm(char*);
    virtual vector<pair<int, int>> run();
    int getResultSum(); // Считывание суммы всех выбранных дуг
private:
    virtual bool validateData();
    bool block = false;
    enum check { Row, Col };
    bool LoadData(char*);
    bool LoadData(vector<vector<int>>);
    void matrixProcedure(vector<vector<int>>); // Метод в котором идет поиск цикла
    void showMatrix(vector<vector<int>>); // Вывод матрицы
    int getMin(vector<vector<int>>, int, check); // Поиск минимального элемента столбца/строки
    int GetStrCount(ifstream&);
    int GetColCount(ifstream&);
};
