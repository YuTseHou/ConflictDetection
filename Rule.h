#include <string>
#include <vector>

using namespace std;

class Rule {
public:
	Rule();
	Rule(int, int, int, vector<int>, vector<string>, vector<int>, vector<int>, vector<string>, vector<string>, vector<int>, vector<string>);
	~Rule();

	int ID();
	int user_ID();
	int user_Au();
	vector<string> trigger_ID();
	vector<string> event();
	vector<int> priority();
	vector<int> envir_ID();
	vector<string> pre_s();
	vector<string> next_s();
	vector<int> actuator_ID();
	vector<string> action();

	void putIntoDependenceRules(int);
	vector<int> DependenceRules();

private:
	int _ID;

	struct user {
		int _user_ID;
		int _user_Au;
	} U;

	struct trigger {
		vector<int> _trigger_ID;
		vector<string> _event;
		vector<int> _priority;
	} T;

	struct envir {
		vector<int> _envir_ID;
		vector<string> _pre_s;
		vector<string> _next_s;
	} E;

	struct actuator {
		vector<int> _actuator_ID;
		vector<string> _action;
	} A;

	vector<int> _DependenceRules;
};