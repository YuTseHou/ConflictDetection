#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <sqlite3.h>
#include <cmath>
#include "Rule.h"
#include "RuleDefine.h"

using namespace std;

typedef struct conflictNode* conflictPtr;
struct conflictNode {
	int conflictRuleID;
	int conflictType;
	conflictPtr conflictLink;
};

int conflict_detection(vector<Rule>, Rule, conflictPtr& , conflictPtr& );
int* rule_relation(Rule, Rule);
int contains(Status, int, Status, int);
int exclude(Status, int, Status, int);
vector<Rule> select_database();
int init(int& , int& , int& , vector<string>& , vector<Status>& , vector<int>& , vector<string>& , vector<Status>& , vector<Status>& , vector<string>& , vector<Status>& , int& , int& , int& );
int char2int(char*);
int insertNode(conflictPtr& , conflictPtr& , int, int);

int main() {
	vector<Rule> RDB = select_database();
	conflictPtr root = NULL;
	conflictPtr now = NULL;

	int ID;
	int user_ID;
	int user_Au;
	vector<string> trigger_ID;
	vector<Status> event;
	vector<int> priority;
	vector<string> envir_ID;
	vector<Status> pre_s;
	vector<Status> next_s;
	vector<string> actuator_ID;
	vector<Status> action;
	int ruleIndicator;
	int ruleThreshold;
	int actionValue;
	ID = 19;
	user_ID = -1;
	user_Au = -1;
	trigger_ID.push_back("dev_0004");
	priority.push_back(1);
	envir_ID.push_back("dev_0004");
	envir_ID.push_back("dev_0008");
	actuator_ID.push_back("dev_0008");
	ruleIndicator = 0;
	ruleThreshold = 80;
	actionValue = 1;
	Status status(ruleIndicator, ruleThreshold, actionValue);
	event.push_back(status);
	pre_s.push_back(status);
	next_s.push_back(status);
	pre_s.push_back(status);
	next_s.push_back(status);
	action.push_back(status);
	Rule ruleB(ID, user_ID, user_Au, trigger_ID, event, priority, envir_ID, pre_s, next_s, actuator_ID, action);

	if (conflict_detection(RDB, ruleB, root, now)) {
		now = root;
		while (now != NULL) {
			cout << "Conflict NO." << now->conflictType << ": Conflicted with rule#" << now->conflictRuleID << endl;
			now = now->conflictLink;
		}
	}
	
	return 0;
}

int conflict_detection(vector<Rule> RDB, Rule ruleB, conflictPtr &root, conflictPtr &now) {
	queue<Rule> ruleQueue;
	vector<int*> rel(RDB.size()+1);

	for (vector<Rule>::iterator rule=RDB.begin(); rule!=RDB.end(); rule++) {
		Rule ruleA = *rule;
		rel[ruleA.ID()] = rule_relation(ruleA, ruleB);
		if (rel[ruleA.ID()]_SimlTr == 1) {
			/**Environmental Mutual Conflict*/
			if ((rel[ruleA.ID()]_SimlTr == 1) && (rel[ruleA.ID()]_ContPs == 1)) {
				insertNode(root, now, ruleA.ID(), Environment_Mutual_Conflict);
				continue;
				//return Environment_Mutual_Conflict;
			}
			/**Shadow Conflict*/
			if ((rel[ruleA.ID()]_SimlAc == 1) && (rel[ruleA.ID()]_PeerAuth == 1)) {
				insertNode(root, now, ruleA.ID(), Shadow_Conflict);
				continue;
				//return Shadow_Conflict;
			}
		}

		/**Execution Conflict*/
		if ((rel[ruleA.ID()]_TrigEve == 1) || (rel[ruleA.ID()]_SimlTr == 1))
			if ((rel[ruleA.ID()]_NegiAc == 1) && (rel[ruleA.ID()]_PeerAuth == 1)) {
				insertNode(root, now, ruleA.ID(), Execution_Conflict);
				continue;
				//return Execution_Conflict;
			}

		if ((rel[ruleA.ID()]_ExplDepe == 1) || (rel[ruleA.ID()]_ImplDepe == 1)) {
			/**Direct Dependence Conflict*/
			if ((rel[ruleA.ID()]_contrary_ExplDepe == 1) || (rel[ruleA.ID()]_contrary_ImplDepe == 1)) {
				insertNode(root, now, ruleA.ID(), Direct_Dependence_Conflict);
				continue;
				//return Direct_Dependence_Conflict;
			}
			else {
				ruleQueue.push(ruleA);
				ruleB.putIntoDependenceRules(ruleA.ID());
			}
		}
	}

	while (!ruleQueue.empty()) {
		Rule ruleC = ruleQueue.front();
		ruleQueue.pop();
		/**Indirect Dependence Conflict*/
		if ((rel[ruleC.ID()]_contrary_ExplDepe == 1) || (rel[ruleC.ID()]_contrary_ImplDepe == 1)) {
			insertNode(root, now, ruleC.ID(), Indirect_Dependence_Conflict);
			break;
			//return Indirect_Dependence_Conflict;
		}
		else {
			for (int i=0; i<ruleC.dependenceRules().size(); i++) {
				int tmp = ruleC.dependenceRules()[i];
				for (vector<Rule>::iterator rule=RDB.begin(); rule!=RDB.end(); rule++) {
					Rule ruleTmp = *rule;
					if (ruleTmp.ID() == tmp) {
						ruleQueue.push(ruleTmp);
						break;
					}
				}
			}
		}
	}

	for (int j=1; j<RDB.size()+1; j++) {
		if ((rel[j]_contrary_ExplDepe == 1) || (rel[j]_contrary_ImplDepe == 1)) {
			for (vector<Rule>::iterator rule=RDB.begin(); rule!=RDB.end(); rule++) {
				Rule ruleJ = *rule;
				if (ruleJ.ID() == j) {
						ruleJ.putIntoDependenceRules(ruleB.ID());
						break;
				}
			}
		}
	}

/*******TO DO stored RULEb in DB*/
	if (root == NULL)
		return NO_Conflict;
	return Conflict;
}

/**
* RuleA -- in database
* RuleB -- added rule
*/
int* rule_relation(Rule ruleA, Rule ruleB) {
	int *relation = new int[rel_length];

	for (int i=0; i<rel_length; i++)
		relation[i] = 0;

	/**Relation of Simlar Trigger*/
	for (int i = 0; i < ruleB.trigger_ID().size(); i++)
		for (int j = 0; j <ruleA.trigger_ID().size(); j++)
			if ((ruleA.trigger_ID()[j] == ruleB.trigger_ID()[i]) && contains(ruleA.event()[j], StatusEvent, ruleB.event()[i], StatusEvent))
				relation_SimlTr = 1;

	/**Relation of Contrary Implicitly Dependence*/
	for (int i = 0; i < ruleB.envir_ID().size(); i++)
		for (int j = 0; j <ruleA.trigger_ID().size(); j++)
			if ((ruleA.trigger_ID()[j] == ruleB.envir_ID()[i]) && contains(ruleB.next_s()[i], StatusNext_s, ruleA.event()[j], StatusEvent))
				relation_contrary_ImplDepe = 1;

	/**Relation of Contrary Explicitly Dependence*/
	for (int i = 0; i < ruleB.actuator_ID().size(); i++)
		for (int j = 0; j <ruleA.trigger_ID().size(); j++)
			if ((ruleA.trigger_ID()[j] == ruleB.actuator_ID()[i]) && contains(ruleB.action()[i], StatusAction, ruleA.event()[j], StatusEvent))
				relation_contrary_ExplDepe = 1;

	/**Relation of Explicitly Dependence*/
	for (int i = 0; i < ruleB.trigger_ID().size(); i++)
		for (int j = 0; j <ruleA.actuator_ID().size(); j++)
			if ((ruleA.actuator_ID()[j] == ruleB.trigger_ID()[i]) && contains(ruleA.action()[j], StatusAction, ruleB.event()[i], StatusEvent))
				relation_ExplDepe = 1;

	/**Relation of Simlar Action and Relation of Negative Action */
	for (int i = 0; i < ruleB.actuator_ID().size(); i++)
		for (int j = 0; j <ruleA.actuator_ID().size(); j++)
			if (ruleA.actuator_ID()[j] == ruleB.actuator_ID()[i]) {
				if (contains(ruleA.action()[j], StatusAction, ruleB.action()[i], StatusAction))
					relation_SimlAc = 1;
				if (exclude(ruleA.action()[j], StatusAction, ruleB.action()[i], StatusAction))
					relation_NegiAc = 1;
			}

	/**Relation of Simlar Prestate and Relation of Contrary Poststate and Relation of Trigger Event*/
	for (int i = 0; i < ruleB.envir_ID().size(); i++)
		for (int j = 0; j <ruleA.envir_ID().size(); j++)
			if (ruleA.envir_ID()[j] == ruleB.envir_ID()[i]) {
				if (contains(ruleA.pre_s()[j], StatusPre_s, ruleB.pre_s()[i], StatusPre_s))
					relation_SimlPr = 1;
				if (exclude(ruleA.next_s()[j], StatusNext_s, ruleB.next_s()[i], StatusNext_s))
					relation_ContPs = 1;
				if (contains(ruleA.pre_s()[j], StatusPre_s, ruleB.next_s()[i], StatusNext_s))
					relation_TrigEve = 1;
			}

	/**Relation of Implicitly Dependence*/
	for (int i = 0; i < ruleB.trigger_ID().size(); i++)
		for (int j = 0; j <ruleA.envir_ID().size(); j++)
			if ((ruleA.envir_ID()[j] == ruleB.trigger_ID()[i]) && (contains(ruleA.next_s()[j], StatusNext_s, ruleB.event()[i], StatusEvent)))
				relation_ImplDepe = 1;

	/**Relation of Peer Authority and Relation of Leapforg Authority and Relation of Conpatible Authority*/
	if (ruleA.user_Au() < ruleB.user_Au())
		relation_LeapAuth = 1;
	else if (ruleA.user_Au() == ruleB.user_Au())
		relation_PeerAuth = 1;
	else
		relation_CompAuth = 1;
#if 0
	for (int i = 0; i < rel_length; i++)
		cout << *(relation+i) << ", ";
	cout << endl;
#endif

	return relation;
}

int contains(Status statusA, int first, Status statusB, int second) {
	int pre_sA[2] = {-1, -1};
	int pre_sB[2] = {-1, -1};
	int next_sA[2] = {-1, -1};
	int next_sB[2] = {-1, -1};

	if ((first == StatusEvent) && (second == StatusEvent)) {
		if (statusA.ruleIndicator() == statusB.ruleIndicator()) {
			if ((statusA.ruleIndicator() == 0) && (statusA.ruleThreshold() > statusB.ruleThreshold()))
				return 1;
			if ((statusA.ruleIndicator() == 2) && (statusA.ruleThreshold() < statusB.ruleThreshold()))
				return 1;
		}
	}

	else if ((first == StatusAction) && (second == StatusEvent)) {
		return 1;
	}

	else if ((first == StatusAction) && (second == StatusAction)) {
		if (statusA.actionValue() == statusB.actionValue())
			return 1;
	}

	else if ((first == StatusNext_s) && (second == StatusEvent)) {
		if (statusA.ruleIndicator() != -1) {
			if (statusA.ruleIndicator() == 0)
				next_sA[0] = 2;
			else if (statusA.ruleIndicator() == 2)
				next_sA[0] = 0;
			next_sA[1] = statusA.ruleThreshold();
			if (next_sA[0] == statusB.ruleIndicator()) {
				if ((next_sA[0] == 0) && (next_sA[1] > statusB.ruleThreshold()))
					return 1;
				if ((next_sA[0] == 2) && (next_sA[1] < statusB.ruleThreshold()))
					return 1;
			}
		}
		else if (statusA.ruleIndicator() == -1) {
			next_sA[0] = statusA.actionValue();
			if (next_sA[0] == statusB.actionValue())
				return 1;
		}
	}

	else if ((first == StatusPre_s) && (second == StatusPre_s)) {
		if ((statusA.ruleIndicator() != -1) && (statusB.ruleIndicator() != -1)) {
			pre_sA[0] = statusA.ruleIndicator();
			pre_sA[1] = statusA.ruleThreshold();
			pre_sB[0] = statusB.ruleIndicator();
			pre_sB[1] = statusB.ruleThreshold();
			if (pre_sA[0] == pre_sB[0]) {
				if ((pre_sA[0] == 0) && (pre_sA[1] > pre_sB[1]))
					return 1;
				if ((pre_sA[0] == 2) && (pre_sA[1] < pre_sB[1]))
					return 1;
			}
		}
		else if ((statusA.ruleIndicator() == -1) && (statusB.ruleIndicator() == -1)) {
			if (statusA.actionValue() > 0)
				pre_sA[0] = 0;
			else
				pre_sA[0] = 1;
			if (statusB.actionValue() > 0)
				pre_sB[0] = 0;
			else
				pre_sB[0] = 1;
			if (pre_sA[0] == pre_sB[0])
				return 1;
		}
	}

	else if ((first == StatusPre_s) && (second == StatusNext_s)) {
		if ((statusA.ruleIndicator() != -1) && (statusB.ruleIndicator() != -1)) {
			pre_sA[0] = statusA.ruleIndicator();
			pre_sA[1] = statusA.ruleThreshold();
			if (statusB.ruleIndicator() == 0)
				next_sB[0] = 2;
			else if (statusB.ruleIndicator() == 2)
				next_sB[0] = 0;
			next_sB[1] = statusB.ruleThreshold();
			if (pre_sA[0] == next_sB[0]) {
				if ((pre_sA[0] == 0) && (pre_sA[1] > next_sB[1]))
					return 1;
				if ((pre_sA[0] == 2) && (pre_sA[1] < next_sB[1]))
					return 1;
			}
		}
		else if ((statusA.ruleIndicator() == -1) && (statusB.ruleIndicator() == -1)) {
			if (statusA.actionValue() > 0)
				pre_sA[0] = 0;
			else
				pre_sA[0] = 1;
			next_sB[0] = statusB.actionValue();
			if (pre_sA[0] == next_sB[0])
				return 1;
		}
	}
	return 0;
}

int exclude(Status statusA, int first, Status statusB, int second) {
	int next_sA[2] = {-1, -1};
	int next_sB[2] = {-1, -1};

	if ((first == StatusAction) && (second == StatusAction)) {
		if (statusA.actionValue() != statusB.actionValue())
				return 1;
	}

	else if ((first == StatusNext_s) && (second == StatusNext_s)) {
		if ((statusA.ruleIndicator() != -1) && (statusB.ruleIndicator() != -1)) {
			if (statusA.ruleIndicator() == 0)
				next_sA[0] = 2;
			else if (statusA.ruleIndicator() == 2)
				next_sA[0] = 0;
			next_sA[1] = statusA.ruleThreshold();

			if (statusB.ruleIndicator() == 0)
				next_sB[0] = 2;
			else if (statusB.ruleIndicator() == 2)
				next_sB[0] = 0;
			next_sB[1] = statusB.ruleThreshold();

			if (next_sA[0] != next_sB[0])
				return 1;
			else if ((next_sA[0] == next_sB[0]) && (next_sA[1] != next_sB[1]))
				return 1;
		}
		else if ((statusA.ruleIndicator() == -1) && (statusB.ruleIndicator() == -1)) {
			next_sA[0] = statusA.actionValue();
			next_sB[0] = statusA.actionValue();
			if (next_sA[0] != next_sB[0])
				return 1;
		}
	}
	return 0;
}

vector<Rule> select_database() {
	sqlite3 *db;
	char *errMsg = NULL;
	char **result;
	int rows, cols;
	vector<Rule> RDB;	//Rule Database
	int ID;
	int user_ID;
	int user_Au;
	vector<string> trigger_ID;
	vector<Status> event;
	vector<int> priority;
	vector<string> envir_ID;
	vector<Status> pre_s;
	vector<Status> next_s;
	vector<string> actuator_ID;
	vector<Status> action;
	int ruleIndicator;
	int ruleThreshold;
	int actionValue;
	Status status;

	/**Open Database*/
	if (sqlite3_open("AMASctrl.db", &db) == SQLITE_OK) {
		cout << "Open Database" << endl;
	}

	/**Get Table*/
	const char* sql = "SELECT * from RuleEventTrigger";
	sqlite3_get_table(db , sql, &result , &rows, &cols, &errMsg);

	for (int i=1; i<=rows; i++) {
		init(ID, user_ID, user_Au, trigger_ID, event, priority, envir_ID, pre_s, next_s, actuator_ID, action, ruleIndicator, ruleThreshold, actionValue);
		status.clean();
		for (int j=0; j<cols; j++) {
			if (j == RuleID)
				ID = char2int(result[i*cols+j]);
			if (j == EventDeviceID) {
				trigger_ID.push_back(result[i*cols+j]);
				envir_ID.push_back(result[i*cols+j]);
			}
			if (j == RuleIndicator)
				ruleIndicator = (int)*result[i*cols+j] - 48;
			if (j == RuleThreshold) {
				ruleThreshold = (int)*result[i*cols+j] - 48;
				status.setRuleIndicator(ruleIndicator);
				status.setRuleThreshold(ruleThreshold);
				event.push_back(status);
				pre_s.push_back(status);
				next_s.push_back(status);
				status.clean();
			}
			if (j == ActionDeviceID) {
				actuator_ID.push_back(result[i*cols+j]);
				envir_ID.push_back(result[i*cols+j]);
			}
			if (j == ActionValue) {
				actionValue = (int)*result[i*cols+j] - 48;
				status.setActionValue(actionValue);
				action.push_back(status);
				pre_s.push_back(status);
				next_s.push_back(status);
				status.clean();
			}
			if (j == Priority)
				priority.push_back((int)*result[i*cols+j] - 48);
		}

		Rule rule(ID, user_ID, user_Au, trigger_ID, event, priority, envir_ID, pre_s, next_s, actuator_ID, action);
		RDB.push_back(rule);
	}

	sqlite3_free_table(result);
	sqlite3_close(db);
	cout << "Close Database" << endl;
	return RDB;
}

int init(int &ID, int &user_ID, int &user_Au, vector<string> &trigger_ID, vector<Status> &event, vector<int> &priority, vector<string> &envir_ID, vector<Status> &pre_s, vector<Status> &next_s, vector<string> &actuator_ID, vector<Status> &action, int &ruleIndicator, int &ruleThreshold, int &actionValue) {
	ID = -1;
	user_ID = -1;
	user_Au = -1;
	trigger_ID.clear();
	event.clear();
	priority.clear();
	envir_ID.clear();
	pre_s.clear();
	next_s.clear();
	actuator_ID.clear();
	action.clear();
	ruleIndicator = -1;
	ruleThreshold = -1;
	actionValue = -1;
}

int char2int(char* ch) {
	string str(ch);
	int value = 0;
	int len = str.size();
	int tmp = 0;

	for (int i=0; i<len; i++) {
		tmp = (int)str[i] - 48;
		value = value + tmp * (int)pow(10, (double)(len-1-i));
	}
	return value;
}

int insertNode(conflictPtr &root, conflictPtr &now, int ID, int Type) {
	conflictNode *tmp = new conflictNode;
	tmp->conflictRuleID = ID;
	tmp->conflictType = Type;
	tmp->conflictLink = NULL;
	if (root == NULL)
		root = tmp;
	else
		now->conflictLink = tmp;
	now = tmp;

	return 1;
}