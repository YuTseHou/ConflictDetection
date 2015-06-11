class Status {
public:
	Status();
	Status(int, int, int);
	~Status();

	int ruleIndicator();
	int ruleThreshold();
	int actionValue();
	void setRuleIndicator(int);
	void setRuleThreshold(int);
	void setActionValue(int);
	void clean();

private:
	int _ruleIndicator;
	int _ruleThreshold;
	int _actionValue;
};