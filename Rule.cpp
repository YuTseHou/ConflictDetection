#include <string>
#include <vector>
#include "Rule.h"

using namespace std;

Rule::Rule() {
	_ID = -1;
}

Rule::Rule(int ID, int user_ID, int  user_Au, vector<string> trigger_ID, vector<Status> event, vector<int> priority, vector<string> envir_ID, vector<Status> pre_s, vector<Status> next_s, vector<string> actuator_ID, vector<Status> action) {
	_ID = ID;
	U._user_ID = user_ID;
	U._user_Au = user_Au;
	T._trigger_ID = trigger_ID;
	T._event = event;
	T._priority = priority;
	E._envir_ID = envir_ID;
	E._pre_s = pre_s;
	E._next_s = next_s;
	A._actuator_ID = actuator_ID;
	A._action = action;
}

Rule::~Rule() {
}

int Rule::ID() {
	return _ID;
}

int Rule::user_ID() {
	return U._user_ID;
}

int Rule::user_Au() {
	return U._user_Au;
}

vector<string> Rule::trigger_ID() {
	return T._trigger_ID;
}

vector<Status> Rule::event() {
	return T._event;
}

vector<int> Rule::priority() {
	return T._priority;
}

vector<string> Rule::envir_ID() {
	return E._envir_ID;
}

vector<Status> Rule::pre_s() {
	return E._pre_s;
}

vector<Status> Rule::next_s() {
	return E._next_s;
}

vector<string> Rule::actuator_ID() {
	return A._actuator_ID;
}

vector<Status> Rule::action() {
	return A._action;
}

void Rule::putIntoDependenceRules(int ID) {
	_dependenceRules.push_back(ID);
}
vector<int> Rule::dependenceRules() {
	return _dependenceRules;
}