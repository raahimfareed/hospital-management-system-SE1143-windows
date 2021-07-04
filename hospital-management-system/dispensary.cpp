#include <string>
#include <map>
#include <vector>

#include "Dispensary.hpp"
#include "Budget.hpp"
#include "Functions.hpp"
#include "Utils.hpp"
#include "Menu.hpp"
#include "User.hpp"

Dispensary::Dispensary()
: mBudget(15.00)
{}

Dispensary::Dispensary(Budget budget)
: mBudget(budget)
{}

void Dispensary::setBudget(double budget)
{
	mBudget = budget;
}

Budget Dispensary::getBudget() const
{
	return mBudget;
}

Budget& Dispensary::rGetBudget()
{
	return mBudget;
}

std::map<std::string, int>& Dispensary::rGetDrugs()
{
	return mDrugs;
}

bool Dispensary::drugExists(std::string drugName)
{
	if (mDrugs.count(drugName) > 0)
	{
		return true;
	}

	return false;
}

void Dispensary::addDrug(const std::unique_ptr<User>& loggedInUser, MenuLevel& menuLevel, std::vector<std::string>& breadcrumbs)
{
	std::string uInput;
    menu(loggedInUser, menuLevel, breadcrumbs);
    input(uInput);

    if (toupper(uInput[0]) == 'B') return;

    switch (toupper(uInput[0]))
    {
    case '1':
        if (mBudget - 312.55 < 0)
        {
            printf("Not enough funds to add Panadol\n%f extra funds needed to add x200 Tabs of Panadol\n", -(mBudget - 312.55));
            menuLevel = MenuLevel::Dispensary;
            breadcrumbs.pop_back();
            haltProgram();
            return;
        }
        if (drugExists("panadol"))
        {
            rGetDrugs()["panadol"] += 200;
        }
        else
        {
            rGetDrugs()["panadol"] = 200;
        }
        
        mBudget -= 312.55;
        printf("x200 Tabs of Panadol added into dispensary\n");
        break;
    case '2':
        if (mBudget - 371.13 < 0)
        {
            printf("Not enough funds to add Duphalac\n%f extra funds needed to add x1 Bottle of Duphalac\n", -(mBudget - 371.13));
            menuLevel = MenuLevel::Dispensary;
            breadcrumbs.pop_back();
            haltProgram();
            return;
        }
        if (drugExists("duphalac"))
        {
            rGetDrugs()["duphalac"] += 1;
        }
        else
        {
            rGetDrugs()["dduphalac"] = 1;
        }
        
        mBudget -= 371.13;
        printf("x1 bottle of Duphalac added into dispensary\n");
        break;
    case '3':
        if (mBudget - 15.00 < 0)
        {
            printf("Not enough funds to add Brufen\n%f extra funds needed to add x10 Tabs of Brufen\n", -(mBudget - 15.00));
            menuLevel = MenuLevel::Dispensary;
            breadcrumbs.pop_back();
            haltProgram();
            return;
        }
        if (drugExists("brufen"))
        {
            rGetDrugs()["brufen"] += 10;
        }
        else
        {
            rGetDrugs()["brufen"] = 10;
        }

        mBudget -= 15.00;
        printf("x10 Tabs of brufen added into dispensary\n");
        break;
    case '4':
        if (mBudget - 155.00 < 0)
        {
            printf("Not enough funds to add Hand Sanitizer\n%f extra funds needed to add x1 Bottle of Hand Sanitizer\n", -(mBudget - 155.00));
            menuLevel = MenuLevel::Dispensary;
            breadcrumbs.pop_back();
            haltProgram();
            return;
        }
        if (drugExists("hand-sanitizer"))
        {
            rGetDrugs()["hand-sanitizer"] += 1;
        }
        else
        {
            rGetDrugs()["hand-sanitizer"] = 1;
        }

        mBudget -= 155.00;
        printf("x1 Bottle of Hand Sanitizer added into dispensary\n");
        break;
    case '5':
        if (mBudget - 180.00 < 0)
        {
            printf("Not enough funds to add Insulin\n%f extra funds needed to add x1 Syringe of Insulin\n", -(mBudget - 180.00));
            menuLevel = MenuLevel::Dispensary;
            breadcrumbs.pop_back();
            haltProgram();
            return;
        }
        if (drugExists("insulin"))
        {
            rGetDrugs()["insulin"] += 1;
        }
        else
        {
            rGetDrugs()["insulin"] = 1;
        }

        mBudget -= 180.00;
        printf("x1 Syringe of Insulin added into dispensary\n");
        break;
    case '6':
        if (mBudget - 3000.00 < 0)
        {
            printf("Not enough funds to add First Aid Kit\n%f extra funds needed to add x1 Kit of First Aid\n", -(mBudget - 3000.00));
            menuLevel = MenuLevel::Dispensary;
            breadcrumbs.pop_back();
            haltProgram();
            return;
        }
        if (drugExists("first-aid"))
        {
            rGetDrugs()["first-aid"] += 1;
        }
        else
        {
            rGetDrugs()["first-aid"] = 1;
        }

        mBudget -= 3000.00;
        printf("x1 Kit of First Aid added into dispensary\n");
        break;
    case '7':
        if (mBudget - 300.00 < 0)
        {
            printf("Not enough funds to add Durex\n%f extra funds needed to add x3 Durex\n", -(mBudget - 300.00));
            menuLevel = MenuLevel::Dispensary;
            breadcrumbs.pop_back();
            haltProgram();
            return;
        }
        if (drugExists("condoms"))
        {
            rGetDrugs()["condoms"] += 3;
        }
        else
        {
            rGetDrugs()["condoms"] = 3;
        }

        mBudget -= 300.00;
        printf("x3 Durex added into dispensary\n");
        break;
    case '8':
        if (mBudget - 650.00 < 0)
        {
            printf("Not enough funds to add Multilife\n%f extra funds needed to add x30 Tabs of Multilife\n", -(mBudget - 650.00));
            menuLevel = MenuLevel::Dispensary;
            breadcrumbs.pop_back();
            haltProgram();
            return;
        }
        if (drugExists("multilife"))
        {
            rGetDrugs()["multilife"] += 30;
        }
        else
        {
            rGetDrugs()["multilife"] = 30;
        }

        mBudget -= 650.00;
        printf("x30 Tabs of Multilife added into dispensary\n");
        break;
    case '9':
        if (mBudget - 440.00 < 0)
        {
            printf("Not enough funds to add Nexum\n%f extra funds needed to add x40 Tabs of Nexum\n", -(mBudget - 440.00));
            menuLevel = MenuLevel::Dispensary;
            breadcrumbs.pop_back();
            haltProgram();
            return;
        }
        if (drugExists("nexum"))
        {
            rGetDrugs()["nexum"] += 40;
        }
        else
        {
            rGetDrugs()["nexum"] = 40;
        }

        mBudget -= 440.00;
        printf("x40 Tabs of Nexum added into dispensary\n");
        break;
    case 'B':
        menuLevel = MenuLevel::Root;
        breadcrumbs.pop_back();
        return;
    }

    menuLevel = MenuLevel::Dispensary;
    breadcrumbs.pop_back();
    haltProgram();
}

void Dispensary::showAllDrugs() const
{
    system(CLEAR);
    bool noDrugs = true;
    for (auto const& pair : mDrugs) {
        noDrugs = false;
        printf("%s: %d\n", pair.first.c_str(), pair.second);
    }

    if (noDrugs)
    {
        printf("No Drugs Available\n");
    }
    haltProgram();
}
