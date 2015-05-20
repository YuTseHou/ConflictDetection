#include <string>
#include <vector>
#include "Rule.h"

using namespace std;

Rule::Rule() {
	_ID = 0;
	U._user_ID = -1;
	U._user_Au = -1;
	T._trigger_ID.push_back(1);
	T._event.push_back("");
	T._priority.push_back(-1);
	E._envir_ID.push_back(-1);
	E._pre_s.push_back("");
	E._next_s.push_back("");
	A._actuator_ID.push_back(-1);
	A._action.push_back("");
}

Rule::Rule(int ID, int user_ID, int  user_Au, vector<int> trigger_ID, vector<string> event, vector<int> priority, vector<int> envir_ID, vector<string> pre_s, vector<string> next_s, vector<int> actuator_ID, vector<string> action) {
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

vector<int> Rule::trigger_ID() {
	return T._trigger_ID;
}

vector<string> Rule::event() {
	return T._event;
}

vector<int> Rule::priority() {
	return T._priority;
}

vector<int> Rule::envir_ID() {
	return E._envir_ID;
}

vector<string> Rule::pre_s() {
	return E._pre_s;
}

vector<string> Rule::next_s() {
	return E._next_s;
}

vector<int> Rule::actuator_ID() {
	return A._actuator_ID;
}

vector<string> Rule::action() {
	return A._action;
}

void Rule::putIntoDependenceRules(int ID) {
	_DependenceRules.push_back(ID);
}
vector<int> Rule::DependenceRules() {
	return _DependenceRules;
}