#include "App.h"
#include <iostream>

using namespace std;

TSApp::TSApp(){
	gui.link_graph(&this->ts);
	this->isRunning = false;
}

TSApp::TSApp(bool faster) {
	gui.link_graph(&ts);
	this->isRunning = faster;
}

TSApp::~TSApp() {
	this->isRunning = false;
}

void TSApp::run(){
	Event ev;
	this->isRunning = true;
	while (this->isRunning == true) {
		cout << endl << "Travelling salesman problem solver. Pick an action:" << endl <<
			"'1' - Add edge to graph and visualise it;" << endl <<
			"'2' - Remove edge from graph and visualization;" << endl <<
			"'3' - Find an optimal way to visit all verticles." << endl <<
			"'9' - Render the graph" << endl << 
			"'0' - Exit program" << endl << endl << ">>>";
		this->getEvent(ev);
		this->response(ev);
	}
}

void TSApp::getEvent(Event& ev) {
	int cmd;
	cin >> cmd;
	cout << endl;
	ev.setCommand(cmd);
}

void TSApp::response(Event& ev) {
	if (!ev.is_empty) {
		switch (ev.getCommand()) {
		case add_edge: {
			string name;
			cout << "Input edge name: ";
			cin >> name;
			this->ts.addvertex(name);
			this->ts.connectAll(name);
			break;
		}
		case remove_edge: {
			string name;
			cout << "Input edge name: ";
			cin >> name;
			this->ts.removeedge(name);
			break;
		}
		case find_way:
		{	
			ts.initmatrix();
			LittleAlgorithm alg(ts.datamatrix);
			vector<pair<int, int>> data = alg.run();
			cout << ts.datamatrix[data[0].first-1][data[0].second-1];
			int sum = ts.datamatrix[data[0].first - 1][data[0].second - 1];
			for (int i = 1; i < data.size(); i++) {
				sum += ts.datamatrix[data[i].first - 1][data[i].second - 1];
				cout << " + " << ts.datamatrix[data[i].first - 1][data[i].second - 1];
			}
			cout << " = " << sum << endl;
			gui.solve_init(data);
			break;
		}
		case 9:
			gui.draw();
			break;
		case 0:
			this->isRunning = false;
			break;
		}
	}
	ev.clear();
}