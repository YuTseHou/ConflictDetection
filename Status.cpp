#include "Status.h"

Status::Status() {
	_ruleIndicator = -1;
	_ruleThreshold = -1;
	_actionValue = -1;
}

Status::Status(int ruleIndicator, int ruleThreshold, int actionValue) {
	_ruleIndicator = ruleIndicator;
	_ruleThreshold = ruleThreshold;
	_actionValue = actionValue;
}

Status::~Status() {
}

int Status::ruleIndicator() {
	return _ruleIndicator;
}

int Status::ruleThreshold() {
	return _ruleThreshold;
}

int Status::actionValue() {
	return _actionValue;
}

void Status::setRuleIndicator(int ruleIndicator) {
	_ruleIndicator = ruleIndicator;
}

void Status::setRuleThreshold(int ruleThreshold) {
	_ruleThreshold = ruleThreshold;
}

void Status::setActionValue(int actionValue) {
	_actionValue = actionValue;
}

void Status::clean() {
	_ruleIndicator = -1;
	_ruleThreshold = -1;
	_actionValue = -1;
}