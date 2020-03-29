#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>

class Proposal
{
private:
	std::string name;
	float price;
	int requirements_num;
	std::vector<std::string> requirements;
	float compliance;
public:
	Proposal(int number_of_requirements)
	{
		getline(std::cin, name);
		get_price_and_requirements();
		std::string current_requirement;
		for (int i = 0; i < requirements_num; ++i)
		{
			getline(std::cin, current_requirement);
			requirements.push_back(current_requirement);
		}
		compliance = (float)requirements_num / (float)number_of_requirements;
	}
	void get_price_and_requirements()
	{
		std::string data;
		getline(std::cin, data);
		sscanf(data.c_str(), "%f %d", &price, &requirements_num);
	}
	float get_compliance()
	{
		return compliance;
	}
	float get_price()
	{
		return price;
	}
	std::string get_name()
	{
		return name;
	}
};

class RFP
{
private:
	int requirements_num;
	int proposals_num;
	std::vector<std::string> requirements;
	std::vector<Proposal> proposals;
public:
	RFP(int i, int j) : requirements_num{i}, proposals_num{j} {}
	void read_requirements()
	{
		std::string current_requirement;
		for (int i = 0; i < requirements_num; ++i)
		{
			getline(std::cin, current_requirement); 
			requirements.push_back(current_requirement);
		}
	}
	void read_proposals()
	{
		for (int i = 0; i < proposals_num; ++i)
			proposals.push_back(Proposal(requirements_num));
	}
	std::string get_result()
	{
		float max_compliance = proposals[0].get_compliance();
		std::vector<Proposal*> max_c_proposals;

		for(std::vector<Proposal>::iterator it = proposals.begin(); it != proposals.end(); ++it)
		{

			if (it->get_compliance() < max_compliance)
			{
				continue;
			}
			else if (it->get_compliance() == max_compliance)
			{
				max_c_proposals.push_back(&(*it));
			}
			else
			{
				max_c_proposals.clear();
				max_c_proposals.push_back(&(*it));
				max_compliance = it->get_compliance();
			}
		}
		float min_price = max_c_proposals[0]->get_price();
		Proposal * min_price_proposal = max_c_proposals[0];

		for (auto i : max_c_proposals)
		{
			if (i->get_price() > min_price)
				continue;
			else if (i->get_price() < min_price)
			{
				min_price = i->get_price();
				min_price_proposal = i;

			}
		}
		return min_price_proposal->get_name();
	}
};


void get_numbers(int *i, int *j)
{
	std::string data;
	getline(std::cin, data);
	sscanf(data.c_str(), "%d %d", i, j);
}

bool get_RFP(std::vector<std::string> *result)
{
	int i=0, j=0;
	get_numbers(&i, &j);
	if (i==0 && j==0)
		return false;

	RFP rfp(i, j);
	rfp.read_requirements();
	rfp.read_proposals();
	result->push_back(rfp.get_result());
	return true;
}

void print_results(std::vector<std::string> &results)
{
	int i = 1;
	for (auto r : results)
	{
		if (i!=1)
			std::cout << std::endl;
		std::cout << "RFP #" << i << std::endl;
		std::cout << r << std::endl;
		i++;
	}
}

int main()
{
	std::vector<std::string> results;
	while(get_RFP(&results));
	#ifdef _DEBUG_
	get_RFP(&results);
	get_RFP(&results);
	get_RFP(&results);
	#endif
	print_results(results);
	return 0;
}