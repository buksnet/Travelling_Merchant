#pragma once
#include "Event.h"
#include "Graph.h"
#include "UI.h"

// abstract class representing base App object
class App  
{
protected:
	bool isRunning;
	UI gui;
public:
	App() {}
	~App() {}
	virtual void run() = 0;
	virtual void getEvent(Event&) = 0;
	virtual void response(Event&) = 0;
};

// class representing Travelling Seller App
class TSApp : public App {
public:
	graph ts;
	TSApp();
	TSApp(bool faster);
	~TSApp();
	void run() override;
	void getEvent(Event&) override;
	void response(Event&) override;
};
