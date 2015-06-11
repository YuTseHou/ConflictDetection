#include <string>
#include <vector>
#include "Status.h"

using namespace std;

class Rule {
public:
	Rule();
	Rule(int, int, int, vector<string>, vector<Status>, vector<int>, vector<string>, vector<Status>, vector<Status>, vector<string>, vector<Status>);
	~Rule();

	int ID();
	int user_ID();
	int user_Au();
	vector<string> trigger_ID();
	vector<Status> event();
	vector<int> priority();
	vector<string> envir_ID();
	vector<Status> pre_s();
	vector<Status> next_s();
	vector<string> actuator_ID();
	vector<Status> action();

	void putIntoDependenceRules(int);
	vector<int> dependenceRules();

private:
	int _ID;

	struct user {
		int _user_ID;
		int _user_Au;
	} U;

	struct trigger {
		vector<string> _trigger_ID;
		vector<Status> _event;
		vector<int> _priority;
	} T;

	struct envir {
		vector<string> _envir_ID;
		vector<Status> _pre_s;
		vector<Status> _next_s;
	} E;

	struct actuator {
		vector<string> _actuator_ID;
		vector<Status> _action;
	} A;

	vector<int> _dependenceRules;
};