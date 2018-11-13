// AvgDelays.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <random>
#include <math.h>
#include <cstring>
#include <string>
#include "time.h"

class c_delays
{
public:
	int index=0;
	int age=0;
	int year=0;
};

std::vector<c_delays> v_NoIntervention_delays;
std::vector<c_delays> v_DPP_RG_delays;
std::vector<c_delays> v_DPP_YMCA_delays;
std::vector<c_delays> v_DPP_HELPPD_delays;
std::vector<c_delays> v_PREMIER_delays;

void read_delay_files(int simulation_year)
{
	c_delays obj_delay;

	std::ifstream f_NoIntervention("C:/Users/snasrol/Google Drive/Research-Diabeties simulation/Code, Data, Results/Me/Results/3rd round/DelayData/NoIntervention_"+std::to_string(simulation_year)+"yr.txt");
	std::string line;
	while (std::getline(f_NoIntervention, line))
	{
		std::stringstream linestream(line);
		std::string		  index;
		int				  age;
		int				  year;

		std::getline(linestream, index, '\t');
		linestream >> age >> year;
		obj_delay.index = atoi(index.c_str());
		obj_delay.age = age;
		obj_delay.year = year;
		v_NoIntervention_delays.push_back(obj_delay);
	}
	f_NoIntervention.close();

	std::ifstream f_DPP_RG("C:/Users/snasrol/Google Drive/Research-Diabeties simulation/Code, Data, Results/Me/Results/3rd round/DelayData/DPP-RG-" + std::to_string(simulation_year) + "yr-55-65.txt");
	line="";
	while (std::getline(f_DPP_RG, line))
	{
		std::stringstream linestream(line);
		std::string		  index;
		int				  age;
		int				  year;

		std::getline(linestream, index, '\t');
		linestream >> age >> year;
		obj_delay.index = atoi(index.c_str());
		obj_delay.age = age;
		obj_delay.year = year;
		v_DPP_RG_delays.push_back(obj_delay);
	}
	f_DPP_RG.close();

	std::ifstream f_DPP_YMCA("C:/Users/snasrol/Google Drive/Research-Diabeties simulation/Code, Data, Results/Me/Results/3rd round/DelayData/DPP-YMCA_" + std::to_string(simulation_year) + "yr-55-65.txt");
	line = "";
	while (std::getline(f_DPP_YMCA, line))
	{
		std::stringstream linestream(line);
		std::string		  index;
		int				  age;
		int				  year;

		std::getline(linestream, index, '\t');
		linestream >> age >> year;
		obj_delay.index = atoi(index.c_str());
		obj_delay.age = age;
		obj_delay.year = year;
		v_DPP_YMCA_delays.push_back(obj_delay);
	}
	f_DPP_YMCA.close();

	std::ifstream f_DPP_HELPPD("C:/Users/snasrol/Google Drive/Research-Diabeties simulation/Code, Data, Results/Me/Results/3rd round/DelayData/DPP-HELP PD_" + std::to_string(simulation_year) + "yr-55-65.txt");
	line = "";
	while (std::getline(f_DPP_HELPPD, line))
	{
		std::stringstream linestream(line);
		std::string		  index;
		int				  age;
		int				  year;

		std::getline(linestream, index, '\t');
		linestream >> age >> year;
		obj_delay.index = atoi(index.c_str());
		obj_delay.age = age;
		obj_delay.year = year;
		v_DPP_HELPPD_delays.push_back(obj_delay);
	}
	f_DPP_HELPPD.close();

	/* std::ifstream f_PREMIER("C:/Users/snasrol/Google Drive/Research-Diabeties simulation/Code, Data, Results/Me/Results/10years/PREMIER_" + std::to_string(simulation_year) + "yr_delays.txt");
	line = "";
	while (std::getline(f_PREMIER, line))
	{
		std::stringstream linestream(line);
		std::string		  index;
		int				  age;
		int				  year;

		std::getline(linestream, index, '\t');
		linestream >> age >> year;
		obj_delay.index = atoi(index.c_str());
		obj_delay.age = age;
		obj_delay.year = year;
		v_PREMIER_delays.push_back(obj_delay);
	}
	f_PREMIER.close(); */
}

int main()
{
	int simulation_years = 10;
	read_delay_files(simulation_years);
	int end_year = 0;
	if (simulation_years == 10)
	{
		end_year = 23;
	}
	else
	{
		end_year = 43;
	}
	/* int DPPRG_difference[4] = { 0 }; //index 0..3 are used for age groups 55-65, 45-65, 35-65, 25-65
	int no_DPPRG_matches[4] = { 0 }; //index 0..3 are used for age groups 55-65, 45-65, 35-65, 25-65
	int DPPYMCA_difference[4] = { 0 };
	int no_DPPYMCA_matches[4] = { 0 };
	int DPPHELPPD_difference[4] = { 0 };
	int no_DPPHELPPD_matches[4] = { 0 }; */

	int DPP_difference=0;
	int no_Delay_matches=0;
	std::vector<c_delays> v_copy1_NoIntervention(v_NoIntervention_delays);
	std::vector<c_delays> v_copy2_NoIntervention(v_NoIntervention_delays);

	std::cout << "finding avg delays in DPP-RG and NoIntervention when a person developes diabetes in both..." << std::endl;
	for (int i = 0; i < v_DPP_RG_delays.size(); i++)
	{// for people who develop diabetes in both the intervention and the control group
		// std::distance returns the distance between to iterators on a vector
		// std::find_if returns the index of an element who matches the if condition in the vector, if not found retruns the last element
			//[&] passess all local variables into the if condition function
			//(c_delays & obj_delay) declares the class and the objects needed in the if condition function
		int match_ind = std::distance(v_NoIntervention_delays.begin(), std::find_if(v_NoIntervention_delays.begin(), v_NoIntervention_delays.end(), [&](c_delays & obj_delay) {return obj_delay.index == v_DPP_RG_delays.at(i).index; }));
		if (match_ind < v_NoIntervention_delays.size())
		{
			/* int min_age = fmin(v_NoIntervention_delays.at(match_ind).age, v_DPP_RG_delays.at(i).age);
			if (min_age <= 65 && min_age > 55)
			{
				DPPRG_difference[0] += v_DPP_RG_delays.at(i).year - v_NoIntervention_delays.at(match_ind).year;
				no_DPPRG_matches[0]++;
			}
			if (min_age <= 65 && min_age > 45)
			{
				DPPRG_difference[1] += v_DPP_RG_delays.at(i).year - v_NoIntervention_delays.at(match_ind).year;
				no_DPPRG_matches[1]++;
			}
			if (min_age <= 65 && min_age > 35)
			{
				DPPRG_difference[2] += v_DPP_RG_delays.at(i).year - v_NoIntervention_delays.at(match_ind).year;
				no_DPPRG_matches[2]++;
			}
			if (min_age <= 65 && min_age > 25)
			{
				DPPRG_difference[3] += v_DPP_RG_delays.at(i).year - v_NoIntervention_delays.at(match_ind).year;
				no_DPPRG_matches[3]++;
			} */
			
			DPP_difference+=v_DPP_RG_delays.at(i).year - v_NoIntervention_delays.at(match_ind).year;
			no_Delay_matches++;
			
			v_DPP_RG_delays.erase(v_DPP_RG_delays.begin() + i);
			v_NoIntervention_delays.erase(v_NoIntervention_delays.begin() + match_ind);
		}
	}
	//std::cout << "avg mathced Delay in DPP-RG for age group 55-65: " << (double)DPP_difference / (double)no_Delay_matches << std::endl;
	
	/* std::cout << "avg mathced Delay in DPP-RG for age group 45-65: " << (double)DPPRG_difference[1] / (double)no_DPPRG_matches[1] << std::endl;
	std::cout << "avg mathced Delay in DPP-RG for age group 35-65: " << (double)DPPRG_difference[2] / (double)no_DPPRG_matches[2] << std::endl;
	std::cout << "avg mathced Delay in DPP-RG for age group 25-65: " << (double)DPPRG_difference[3] / (double)no_DPPRG_matches[3] << std::endl; */
	
	std::cout << "finding avg delays in DPP-RG when a person developes diabetes in the intervention group only..." << std::endl;
	for (int i = 0; i < v_DPP_RG_delays.size(); i++)
	{// for people who develop diabetes in the intervention group only
		/* int min_age = v_DPP_RG_delays.at(i).age;
		if (min_age <= 65 && min_age > 55)
		{
			DPPRG_difference[0] += v_DPP_RG_delays.at(i).year - end_year;
			no_DPPRG_matches[0]++;
		}
		if (min_age <= 65 && min_age > 45)
		{
			DPPRG_difference[1] += v_DPP_RG_delays.at(i).year - end_year;
			no_DPPRG_matches[1]++;
		}
		if (min_age <= 65 && min_age > 35)
		{
			DPPRG_difference[2] += v_DPP_RG_delays.at(i).year - end_year;
			no_DPPRG_matches[2]++;
		}
		if (min_age <= 65 && min_age > 25)
		{
			DPPRG_difference[3] += v_DPP_RG_delays.at(i).year - end_year;
			no_DPPRG_matches[3]++;
		} */
		DPP_difference+=v_DPP_RG_delays.at(i).year - end_year;
		no_Delay_matches++;
	}
	/* std::cout << "avg mathced Delay in DPP-RG for age group 55-65: " << (double)DPPRG_difference[0] / (double)no_DPPRG_matches[0] << std::endl;
	std::cout << "avg mathced Delay in DPP-RG for age group 45-65: " << (double)DPPRG_difference[1] / (double)no_DPPRG_matches[1] << std::endl;
	std::cout << "avg mathced Delay in DPP-RG for age group 35-65: " << (double)DPPRG_difference[2] / (double)no_DPPRG_matches[2] << std::endl;
	std::cout << "avg mathced Delay in DPP-RG for age group 25-65: " << (double)DPPRG_difference[3] / (double)no_DPPRG_matches[3] << std::endl; */
	std::cout << "finding avg delays in DPP-RG when a person developes diabetes in the control group only..." << std::endl;
	for (int i = 0; i < v_NoIntervention_delays.size(); i++)
	{// for people who develop diabetes in control group only
		/* int min_age = v_NoIntervention_delays.at(i).age;
		if (min_age <= 65 && min_age > 55)
		{
			DPPRG_difference[0] += end_year - v_NoIntervention_delays.at(i).year;
			no_DPPRG_matches[0]++;
		}
		if (min_age <= 65 && min_age > 45)
		{
			DPPRG_difference[1] += end_year - v_NoIntervention_delays.at(i).year;
			no_DPPRG_matches[1]++;
		}
		if (min_age <= 65 && min_age > 35)
		{
			DPPRG_difference[2] += end_year - v_NoIntervention_delays.at(i).year;
			no_DPPRG_matches[2]++;
		}
		if (min_age <= 65 && min_age > 25)
		{
			DPPRG_difference[3] += end_year - v_NoIntervention_delays.at(i).year;
			no_DPPRG_matches[3]++;
		} */
		DPP_difference+=end_year - v_NoIntervention_delays.at(i).year;
		no_Delay_matches++;
	}
	std::cout << "avg mathced Delay in DPP-RG for age group 55-65: " << (double)DPP_difference / (double)no_Delay_matches << std::endl;
	/* std::cout << "avg mathced Delay in DPP-RG for age group 45-65: " << (double)DPPRG_difference[1] / (double)no_DPPRG_matches[1] << std::endl;
	std::cout << "avg mathced Delay in DPP-RG for age group 35-65: " << (double)DPPRG_difference[2] / (double)no_DPPRG_matches[2] << std::endl;
	std::cout << "avg mathced Delay in DPP-RG for age group 25-65: " << (double)DPPRG_difference[3] / (double)no_DPPRG_matches[3] << std::endl; */
	
	DPP_difference=0;
	no_Delay_matches=0;
	
	std::cout << "finding avg delays in DPP-YMCA and NoIntervention when a person developes diabetes in both..." << std::endl;
	for (int i = 0; i < v_DPP_YMCA_delays.size(); i++)
	{
		// std::distance returns the distance between to iterators on a vector
		// std::find_if returns the index of an element who matches the if condition in the vector, if not found retruns the last element
		//[&] passess all local variables into the if condition function
		//(c_delays & obj_delay) declares the class and the objects needed in the if condition function
		int match_ind = std::distance(v_copy1_NoIntervention.begin(), std::find_if(v_copy1_NoIntervention.begin(), v_copy1_NoIntervention.end(), [&](c_delays & obj_delay) {return obj_delay.index == v_DPP_YMCA_delays.at(i).index; }));
		if (match_ind < v_copy1_NoIntervention.size())
		{
			/* int min_age = fmin(v_copy1_NoIntervention.at(match_ind).age, v_DPP_YMCA_delays.at(i).age);
			if (min_age <= 65 && min_age > 55)
			{
				DPPYMCA_difference[0] += v_DPP_YMCA_delays.at(i).year - v_copy1_NoIntervention.at(match_ind).year;
				no_DPPYMCA_matches[0]++;
			}
			if (min_age <= 65 && min_age > 45)
			{
				DPPYMCA_difference[1] += v_DPP_YMCA_delays.at(i).year - v_copy1_NoIntervention.at(match_ind).year;
				no_DPPYMCA_matches[1]++;
			}
			if (min_age <= 65 && min_age > 35)
			{
				DPPYMCA_difference[2] += v_DPP_YMCA_delays.at(i).year - v_copy1_NoIntervention.at(match_ind).year;
				no_DPPYMCA_matches[2]++;
			}
			if (min_age <= 65 && min_age > 25)
			{
				DPPYMCA_difference[3] += v_DPP_YMCA_delays.at(i).year - v_copy1_NoIntervention.at(match_ind).year;
				no_DPPYMCA_matches[3]++;
			} */
			DPP_difference+=v_DPP_YMCA_delays.at(i).year - v_copy1_NoIntervention.at(match_ind).year;
			no_Delay_matches++;
			
			v_DPP_YMCA_delays.erase(v_DPP_YMCA_delays.begin() + i);
			v_copy1_NoIntervention.erase(v_copy1_NoIntervention.begin() + match_ind);
		}
	}
	/* std::cout << "avg mathced Delay in DPP-YMCA for age group 55-65: " << (double)DPPYMCA_difference[0] / (double)no_DPPYMCA_matches[0] << std::endl;
	std::cout << "avg mathced Delay in DPP-YMCA for age group 45-65: " << (double)DPPYMCA_difference[1] / (double)no_DPPYMCA_matches[1] << std::endl;
	std::cout << "avg mathced Delay in DPP-YMCA for age group 35-65: " << (double)DPPYMCA_difference[2] / (double)no_DPPYMCA_matches[2] << std::endl;
	std::cout << "avg mathced Delay in DPP-YMCA for age group 25-65: " << (double)DPPYMCA_difference[3] / (double)no_DPPYMCA_matches[3] << std::endl; */
	std::cout << "finding avg delays in DPP-YMCA when a person developes diabetes in the intervention group only..." << std::endl;
	for (int i = 0; i < v_DPP_YMCA_delays.size(); i++)
	{
		/* int min_age = v_DPP_YMCA_delays.at(i).age;
		if (min_age <= 65 && min_age > 55)
		{
			DPPYMCA_difference[0] += v_DPP_YMCA_delays.at(i).year - end_year;
			no_DPPYMCA_matches[0]++;
		}
		if (min_age <= 65 && min_age > 45)
		{
			DPPYMCA_difference[1] += v_DPP_YMCA_delays.at(i).year - end_year;
			no_DPPYMCA_matches[1]++;
		}
		if (min_age <= 65 && min_age > 35)
		{
			DPPYMCA_difference[2] += v_DPP_YMCA_delays.at(i).year - end_year;
			no_DPPYMCA_matches[2]++;
		}
		if (min_age <= 65 && min_age > 25)
		{
			DPPYMCA_difference[3] += v_DPP_YMCA_delays.at(i).year - end_year;
			no_DPPYMCA_matches[3]++;
		} */
		DPP_difference+=v_DPP_YMCA_delays.at(i).year - end_year;
		no_Delay_matches++;
	}
	/* std::cout << "avg mathced Delay in DPP-YMCA for age group 55-65: " << (double)DPPYMCA_difference[0] / (double)no_DPPYMCA_matches[0] << std::endl;
	std::cout << "avg mathced Delay in DPP-YMCA for age group 45-65: " << (double)DPPYMCA_difference[1] / (double)no_DPPYMCA_matches[1] << std::endl;
	std::cout << "avg mathced Delay in DPP-YMCA for age group 35-65: " << (double)DPPYMCA_difference[2] / (double)no_DPPYMCA_matches[2] << std::endl;
	std::cout << "avg mathced Delay in DPP-YMCA for age group 25-65: " << (double)DPPYMCA_difference[3] / (double)no_DPPYMCA_matches[3] << std::endl; */
	std::cout << "finding avg delays in DPP-YMCA when a person developes diabetes in the control group only..." << std::endl;
	for (int i = 0; i < v_copy1_NoIntervention.size(); i++)
	{
		/* int min_age = v_copy1_NoIntervention.at(i).age;
		if (min_age <= 65 && min_age > 55)
		{
			DPPYMCA_difference[0] += end_year - v_copy1_NoIntervention.at(i).year;
			no_DPPYMCA_matches[0]++;
		}
		if (min_age <= 65 && min_age > 45)
		{
			DPPYMCA_difference[1] += end_year - v_copy1_NoIntervention.at(i).year;
			no_DPPYMCA_matches[1]++;
		}
		if (min_age <= 65 && min_age > 35)
		{
			DPPYMCA_difference[2] += end_year - v_copy1_NoIntervention.at(i).year;
			no_DPPYMCA_matches[2]++;
		}
		if (min_age <= 65 && min_age > 25)
		{
			DPPYMCA_difference[3] += end_year - v_copy1_NoIntervention.at(i).year;
			no_DPPYMCA_matches[3]++;
		} */
		DPP_difference+=end_year - v_copy1_NoIntervention.at(i).year;
		no_Delay_matches++;
	}
	std::cout << "avg mathced Delay in DPP-YMCA for age group 55-65: " << (double)DPP_difference / (double)no_Delay_matches << std::endl;
	/* std::cout << "avg mathced Delay in DPP-YMCA for age group 45-65: " << (double)DPPYMCA_difference[1] / (double)no_DPPYMCA_matches[1] << std::endl;
	std::cout << "avg mathced Delay in DPP-YMCA for age group 35-65: " << (double)DPPYMCA_difference[2] / (double)no_DPPYMCA_matches[2] << std::endl;
	std::cout << "avg mathced Delay in DPP-YMCA for age group 25-65: " << (double)DPPYMCA_difference[3] / (double)no_DPPYMCA_matches[3] << std::endl; */
	DPP_difference=0;
	no_Delay_matches=0;
	
	std::cout << "finding avg delays in DPP-HELPPD and NoIntervention when a person developes diabetes in both..." << std::endl;
	for (int i = 0; i < v_DPP_HELPPD_delays.size(); i++)
	{
		// std::distance returns the distance between to iterators on a vector
		// std::find_if returns the index of an element who matches the if condition in the vector, if not found retruns the last element
		//[&] passess all local variables into the if condition function
		//(c_delays & obj_delay) declares the class and the objects needed in the if condition function
		int match_ind = std::distance(v_copy2_NoIntervention.begin(), std::find_if(v_copy2_NoIntervention.begin(), v_copy2_NoIntervention.end(), [&](c_delays & obj_delay) {return obj_delay.index == v_DPP_HELPPD_delays.at(i).index; }));
		if (match_ind < v_copy2_NoIntervention.size())
		{
			/* int min_age = fmin(v_copy2_NoIntervention.at(match_ind).age, v_DPP_HELPPD_delays.at(i).age);
			if (min_age <= 65 && min_age > 55)
			{
				DPPHELPPD_difference[0] += v_DPP_HELPPD_delays.at(i).year - v_copy2_NoIntervention.at(match_ind).year;
				no_DPPHELPPD_matches[0]++;
			}
			if (min_age <= 65 && min_age > 45)
			{
				DPPHELPPD_difference[1] += v_DPP_HELPPD_delays.at(i).year - v_copy2_NoIntervention.at(match_ind).year;
				no_DPPHELPPD_matches[1]++;
			}
			if (min_age <= 65 && min_age > 35)
			{
				DPPHELPPD_difference[2] += v_DPP_HELPPD_delays.at(i).year - v_copy2_NoIntervention.at(match_ind).year;
				no_DPPHELPPD_matches[2]++;
			}
			if (min_age <= 65 && min_age > 25)
			{
				DPPHELPPD_difference[3] += v_DPP_HELPPD_delays.at(i).year - v_copy2_NoIntervention.at(match_ind).year;
				no_DPPHELPPD_matches[3]++;
			}  */
			DPP_difference+=v_DPP_HELPPD_delays.at(i).year - v_copy2_NoIntervention.at(match_ind).year;
			no_Delay_matches++;
			
			v_DPP_HELPPD_delays.erase(v_DPP_HELPPD_delays.begin() + i);
			v_copy2_NoIntervention.erase(v_copy2_NoIntervention.begin() + match_ind);
		}
	}
	/* std::cout << "avg mathced Delay in DPP-HELPPD for age group 55-65: " << (double)DPPHELPPD_difference[0] / (double)no_DPPHELPPD_matches[0] << std::endl;
	std::cout << "avg mathced Delay in DPP-HELPPD for age group 45-65: " << (double)DPPHELPPD_difference[1] / (double)no_DPPHELPPD_matches[1] << std::endl;
	std::cout << "avg mathced Delay in DPP-HELPPD for age group 35-65: " << (double)DPPHELPPD_difference[2] / (double)no_DPPHELPPD_matches[2] << std::endl;
	std::cout << "avg mathced Delay in DPP-HELPPD for age group 25-65: " << (double)DPPHELPPD_difference[3] / (double)no_DPPHELPPD_matches[3] << std::endl; */
	std::cout << "finding avg delays in DPP-HELPPD when a person developes diabetes in the intervention group only..." << std::endl;
	for (int i = 0; i < v_DPP_HELPPD_delays.size(); i++)
	{
		/* int min_age = v_DPP_HELPPD_delays.at(i).age;
		if (min_age <= 65 && min_age > 55)
		{
			DPPHELPPD_difference[0] += v_DPP_HELPPD_delays.at(i).year - end_year;
			no_DPPHELPPD_matches[0]++;
		}
		if (min_age <= 65 && min_age > 45)
		{
			DPPHELPPD_difference[1] += v_DPP_HELPPD_delays.at(i).year - end_year;
			no_DPPHELPPD_matches[1]++;
		}
		if (min_age <= 65 && min_age > 35)
		{
			DPPHELPPD_difference[2] += v_DPP_HELPPD_delays.at(i).year - end_year;
			no_DPPHELPPD_matches[2]++;
		}
		if (min_age <= 65 && min_age > 25)
		{
			DPPHELPPD_difference[3] += v_DPP_HELPPD_delays.at(i).year - end_year;
			no_DPPHELPPD_matches[3]++;
		} */
		DPP_difference+=v_DPP_HELPPD_delays.at(i).year - end_year;
		no_Delay_matches++;
	}
	/* std::cout << "avg mathced Delay in DPP-HELPPD for age group 55-65: " << (double)DPPHELPPD_difference[0] / (double)no_DPPHELPPD_matches[0] << std::endl;
	std::cout << "avg mathced Delay in DPP-HELPPD for age group 45-65: " << (double)DPPHELPPD_difference[1] / (double)no_DPPHELPPD_matches[1] << std::endl;
	std::cout << "avg mathced Delay in DPP-HELPPD for age group 35-65: " << (double)DPPHELPPD_difference[2] / (double)no_DPPHELPPD_matches[2] << std::endl;
	std::cout << "avg mathced Delay in DPP-HELPPD for age group 25-65: " << (double)DPPHELPPD_difference[3] / (double)no_DPPHELPPD_matches[3] << std::endl; */
	std::cout << "finding avg delays in DPP-HELPPD when a person developes diabetes in the control group only..." << std::endl;
	for (int i = 0; i < v_copy2_NoIntervention.size(); i++)
	{
		/* int min_age = v_copy2_NoIntervention.at(i).age;
		if (min_age <= 65 && min_age > 55)
		{
			DPPHELPPD_difference[0] += end_year - v_copy2_NoIntervention.at(i).year;
			no_DPPHELPPD_matches[0]++;
		}
		if (min_age <= 65 && min_age > 45)
		{
			DPPHELPPD_difference[1] += end_year - v_copy2_NoIntervention.at(i).year;
			no_DPPHELPPD_matches[1]++;
		}
		if (min_age <= 65 && min_age > 35)
		{
			DPPHELPPD_difference[2] += end_year - v_copy2_NoIntervention.at(i).year;
			no_DPPHELPPD_matches[2]++;
		}
		if (min_age <= 65 && min_age > 25)
		{
			DPPHELPPD_difference[3] += end_year - v_copy2_NoIntervention.at(i).year;
			no_DPPHELPPD_matches[3]++;
		} */
		DPP_difference+=end_year - v_copy2_NoIntervention.at(i).year;
		no_Delay_matches++;
	}
	std::cout << "avg mathced Delay in DPP-HELPPD for age group 55-65: " << (double)DPP_difference / (double)no_Delay_matches << std::endl;
	/* std::cout << "avg mathced Delay in DPP-HELPPD for age group 45-65: " << (double)DPPHELPPD_difference[1] / (double)no_DPPHELPPD_matches[1] << std::endl;
	std::cout << "avg mathced Delay in DPP-HELPPD for age group 35-65: " << (double)DPPHELPPD_difference[2] / (double)no_DPPHELPPD_matches[2] << std::endl;
	std::cout << "avg mathced Delay in DPP-HELPPD for age group 25-65: " << (double)DPPHELPPD_difference[3] / (double)no_DPPHELPPD_matches[3] << std::endl; */
	std::cin.ignore(10000, '\n');
	return 0;
}

