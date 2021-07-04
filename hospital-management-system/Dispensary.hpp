#pragma once
#include <string>
#include <map>
#include <vector>

#include "Budget.hpp"
#include "User.hpp"


class Dispensary
{
public:
	Dispensary();
	Dispensary(Budget budget);
	void setBudget(double budget);
	Budget getBudget() const;
	Budget& rGetBudget();
	std::map<std::string, int>& rGetDrugs();
	bool drugExists(std::string drugName);
	void addDrug(const std::unique_ptr<User>& loggedInUser, MenuLevel& menuLevel, std::vector<std::string>& breadcrumbs);
	void showAllDrugs() const;

private:
	Budget mBudget;
	std::map<std::string, int> mDrugs;
};
