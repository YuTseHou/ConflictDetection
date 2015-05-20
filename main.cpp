#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include "Rule.h"
#include "RelationDefine.h"

using namespace std;

int conflict_detection(Rule, Rule);
int* rule_relation(Rule, Rule);
int contains(string, string);
int exclude(string, string);

int main() {
	int ID = 1;
	int user_ID = 1;
	int user_Au = 0;
	vector<int> trigger_ID;
	vector<string> event;
	vector<int> priority;
	vector<int> envir_ID;
	vector<string> pre_s;
	vector<string> next_s;
	vector<int> actuator_ID;
	vector<string> action;

	trigger_ID.push_back(1);
	event.push_back(">30");
	priority.push_back(0);
	envir_ID.push_back(2);
	pre_s.push_back("0");
	next_s.push_back("1");
	envir_ID.push_back(1);
	pre_s.push_back(">30");
	next_s.push_back("<30");
	actuator_ID.push_back(2);
	action.push_back("on");

	Rule ruleA;
	Rule ruleB(ID, user_ID, user_Au, trigger_ID, event, priority, envir_ID, pre_s, next_s, actuator_ID, action);
	
	
	conflict_detection(ruleA, ruleB);
	
	return 0;
}

int conflict_detection(Rule ruleA, Rule ruleB) {
	queue<Rule> ruleQueue;

/*******How much rules in DB*/
	vector<int*> rel(10);
	rel[ruleA.ID()] = rule_relation(ruleA, ruleB);

/*******for each ruleA in database*/
	if (rel[ruleA.ID()]_SimlTr == 1) {
		/**Environmental Mutual Conflict*/
		if ((rel[ruleA.ID()]_SimlTr == 1) && (rel[ruleA.ID()]_ContPs == 1))
			return Environment_Mutual_Conflict;
		/**Shadow Conflict*/
		if ((rel[ruleA.ID()]_SimlAc == 1) && (rel[ruleA.ID()]_PeerAuth == 1))
			return Shadow_Conflict;
	}

	/**Execution Conflict*/
	if ((rel[ruleA.ID()]_TrigEve == 1) || (rel[ruleA.ID()]_SimlTr == 1))
		if ((rel[ruleA.ID()]_NegiAc == 1) && (rel[ruleA.ID()]_PeerAuth == 1))
			return Execution_Conflict;

	if ((rel[ruleA.ID()]_ExplDepe == 1) || (rel[ruleA.ID()]_ImplDepe == 1)) {
		/**Direct Dependence Conflict*/
		if ((rel[ruleA.ID()]_contrary_ExplDepe == 1) || (rel[ruleA.ID()]_contrary_ImplDepe == 1))
			return Direct_Dependence_Conflict;
		else {
			ruleQueue.push(ruleA);
			ruleB.putIntoDependenceRules(ruleA.ID());
		}
	}

	while (!ruleQueue.empty()) {
		Rule ruleC = ruleQueue.front();
		ruleQueue.pop();

		if ((rel[ruleC.ID()]_contrary_ExplDepe == 1) || (rel[ruleC.ID()]_contrary_ImplDepe == 1))
			return Indirect_Dependence_Conflict;
		else {
			for (int i=0; i<ruleC.DependenceRules().size(); i++) {
				int tmp = ruleC.DependenceRules()[i];
/*******put RULEtmp in Queue*/
			}
		}
	}
/*******How much rules in DB*/
	for (int j=0; j<10; j++) {
		if ((rel[j]_contrary_ExplDepe == 1) || (rel[j]_contrary_ImplDepe == 1)) {
/*******add RULEb.ID to RULEj DependenceRules*/
		}
	}

/*******stored RULEb in DB*/

	return NO_Conflict;
}

/**
* RuleA -- in database
* RuleB -- added rule
*/
int* rule_relation(Rule ruleA, Rule ruleB) {
	int *relation = new int[rel_length];

	/**Relation of Simlar Trigger*/
	for (int i = 0; i < ruleB.trigger_ID().size(); i++)
		for (int j = 0; j <ruleA.trigger_ID().size(); j++)
			if ((ruleA.trigger_ID()[j] == ruleB.trigger_ID()[i]) && contains(ruleA.event()[j], ruleB.event()[i]))
				relation_SimlTr = 1;

	/**Relation of Contrary Implicitly Dependence*/
	for (int i = 0; i < ruleB.envir_ID().size(); i++)
		for (int j = 0; j <ruleA.trigger_ID().size(); j++)
			if ((ruleA.trigger_ID()[j] == ruleB.envir_ID()[i]) && contains(ruleB.next_s()[i], ruleA.event()[j]))
				relation_contrary_ImplDepe = 1;

	/**Relation of Contrary Explicitly Dependence*/
	for (int i = 0; i < ruleB.actuator_ID().size(); i++)
		for (int j = 0; j <ruleA.trigger_ID().size(); j++)
			if ((ruleA.trigger_ID()[j] == ruleB.actuator_ID()[i]) && contains(ruleB.action()[i], ruleA.event()[j]))
				relation_contrary_ExplDepe = 1;

	/**Relation of Explicitly Dependence*/
	for (int i = 0; i < ruleB.trigger_ID().size(); i++)
		for (int j = 0; j <ruleA.actuator_ID().size(); j++)
			if ((ruleA.actuator_ID()[j] == ruleB.trigger_ID()[i]) && contains(ruleA.action()[j], ruleB.event()[i]))
				relation_ExplDepe = 1;

	/**Relation of Simlar Action and Relation of Negative Action */
	for (int i = 0; i < ruleB.actuator_ID().size(); i++)
		for (int j = 0; j <ruleA.actuator_ID().size(); j++)
			if (ruleA.actuator_ID()[j] == ruleB.actuator_ID()[i]) {
				if (contains(ruleA.action()[j], ruleB.action()[i]))
					relation_SimlAc = 1;
				if (exclude(ruleA.action()[j], ruleB.action()[i]))
					relation_NegiAc = 1;
			}

	/**Relation of Simlar Prestate and Relation of Contrary Poststate and Relation of Trigger Event*/
	for (int i = 0; i < ruleB.envir_ID().size(); i++)
		for (int j = 0; j <ruleA.envir_ID().size(); j++)
			if (ruleA.envir_ID()[j] == ruleB.envir_ID()[i]) {
				if (contains(ruleA.pre_s()[j], ruleB.pre_s()[i]))
					relation_SimlPr = 1;
				if (exclude(ruleA.next_s()[j], ruleB.next_s()[i]))
					relation_ContPs = 1;
				if (contains(ruleA.pre_s()[j], ruleB.next_s()[i]))
					relation_TrigEve = 1;
			}

	/**Relation of Implicitly Dependence*/
	for (int i = 0; i < ruleB.trigger_ID().size(); i++)
		for (int j = 0; j <ruleA.envir_ID().size(); j++)
			if ((ruleA.envir_ID()[j] == ruleB.trigger_ID()[i]) && (contains(ruleA.next_s()[j], ruleB.event()[i])))
				relation_ImplDepe = 1;

	/**Relation of Peer Authority and Relation of Leapforg Authority and Relation of Conpatible Authority*/
	if (ruleA.user_Au() < ruleB.user_Au())
		relation_LeapAuth = 1;
	else if (ruleA.user_Au() == ruleB.user_Au())
		relation_PeerAuth = 1;
	else
		relation_CompAuth = 1;

	for (int i = 0; i < rel_length; i++)
		cout << *(relation+i) << ", ";
	cout << endl;

	return relation;
}

int contains(string A, string B) {

	return 1;
}

int exclude(string A, string B) {

	return 1;
}