#pragma once

const short int add_edge = 1;
const short int remove_edge = 2;
const short int find_way = 3;



class Event
{
private:
	short int command;
public:
	bool is_empty;
	Event() { this->is_empty = true; }
	~Event() {};
	void setCommand(int cmd) {
		if ((cmd >= 0) && (cmd < 10)) {
			this->is_empty = false;
			this->command = cmd;
		}
	}
	short int getCommand() {
		return this->command;
	}

	void clear() {
		this->is_empty = true;
		this->command = -1;
	}
};
