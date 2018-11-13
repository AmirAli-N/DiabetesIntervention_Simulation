// DPP(YMCA).cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
// DPP(YMCA).cpp : Defines the entry point for the console application.
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

class individual
{//defining a class for each individual to have index, age, gender, initial bmi value and status, initial diabetes value and status, death probability and updating
 //function for bmi value and diabetes status
public:
	int person_ind = 0;
	int person_age = 0;
	float bmi_value;
	double m_death_factor[8] = { -2.75, -2.85, -3, -3, -3, -2.5, -2, 0 }; //male death factor for age groupes <30, 30-40, 40-50, 50-60, 60-70, 70-80, 80-90, >90
	double f_death_factor[8] = { -2.45, -2.45, -2.45, -2.45, -2.7, -2.3, -2.3, 0 }; //female death factor for age groupes <30, 30-40, 40-50, 50-60, 60-70, 70-80, 80-90, >90
	bool alive = 1;
	std::string bmi_status;
	std::string diabetes_status;
	std::string person_gender;

	void getindex()
	{
		//index of the person under simulation
		person_ind = person_ind + 1;
	}
	void getage(int start_age, int end_age)
	{
		//create a random age based on start age and end age of the group
		double rnd = rand();
		std::mt19937 mt(rnd);
		std::uniform_real_distribution<double> dist(0, 1);
		double initial_prob = 0;
		initial_prob = dist(mt);
		int age_interval;
		age_interval = end_age - start_age;
		person_age = initial_prob*age_interval + start_age;
	}
	void getgender(double p_male) /*generating random gender for age group a_b*/
	{
		//create a random age based on the probability of being male in the age group
		double rnd = rand();
		std::mt19937 mt(rnd);
		std::uniform_real_distribution<double> dist(0, 1);
		double gender_prob;
		gender_prob = dist(mt);
		if (gender_prob<p_male)
		{
			person_gender = "Male";
		}
		else if (gender_prob>p_male & gender_prob<1)
		{
			person_gender = "Female";
		}
	}
	void initial_bmi(double p_bmi_normal, double p_bmi_overweight) /*assign random status of weight to individuals*/
	{
		//create a random initial bmi based on the probability of having normal and overweight bmi
		double rnd = rand();
		std::mt19937 mt(rnd);
		std::uniform_real_distribution<double> dist(0, 1);
		double init_bmi_prob = 0.0;
		init_bmi_prob = dist(mt);
		if (init_bmi_prob<p_bmi_normal)
		{
			bmi_status = "Normal";
			std::uniform_real_distribution<double> dist(0, 1);
			bmi_value = (dist(mt) * 5) + 20;
		}
		else if (init_bmi_prob>p_bmi_normal & init_bmi_prob<p_bmi_overweight)
		{
			bmi_status = "Overweight";
			std::uniform_real_distribution<double> dist(0, 1);
			bmi_value = (dist(mt) * 5) + 25;
		}
		else if (init_bmi_prob>p_bmi_overweight & init_bmi_prob<1)
		{
			bmi_status = "Obese";
			std::uniform_real_distribution<double> dist(0, 1);
			bmi_value = (dist(mt) * 15) + 30;
		}
	}
	void initial_diabetes(double p_get_pre_dia, double p_diabetes)
	{
		//create a random status of diabetes based on the probability of having normal, prediabetes or diabetes status 
		double rnd = rand();
		std::mt19937 mt(rnd);
		std::uniform_real_distribution<double> dist(0, 1);
		double init_diabetes_prob = 0;
		init_diabetes_prob = dist(mt);
		double p_pre_dia = 0;
		p_pre_dia = p_get_pre_dia + p_diabetes;
		if (init_diabetes_prob<p_diabetes)
		{
			diabetes_status = "Diabetes";
		}
		else if (init_diabetes_prob>p_diabetes & init_diabetes_prob<p_pre_dia)
		{
			diabetes_status = "Predia";
		}
		else if (init_diabetes_prob>p_pre_dia & init_diabetes_prob<1)
		{
			diabetes_status = "Normal";
		}
	}
	void update_diabetes(individual person) /*update diabeties status*/
	{
		double p_normal = 0;
		double p_pre_dia = 0;
		double p_diabetes = 0;
		if (person.diabetes_status == "Normal")
		{//if the person is Normal
			if (person.bmi_status == "Normal")
			{//if the person has Normal BMI
				p_normal = 0.98;
				p_pre_dia = 1;
				p_diabetes = 1;
			}
			else if (person.bmi_status == "Overweight")
			{//Overweight
				p_normal = 0.96;
				p_pre_dia = 1;
				p_diabetes = 1;
			}
			else
			{//Obese
				p_normal = 0.94;
				p_pre_dia = 1;
				p_diabetes = 1;
			}
		}
		else if (person.diabetes_status == "Predia")
		{//if the person has Prediabetes
			if (person.bmi_status == "Normal")
			{//if the person has Normal BMI
				p_normal = 0.05;
				p_pre_dia = 1;
				p_diabetes = 1;
			}
			else if (person.bmi_status == "Overweight")
			{//Overweight
				p_normal = 0.01;
				p_pre_dia = 0.982;
				p_diabetes = 1;
			}
			else
			{//Obese
				p_normal = 0.0;
				p_pre_dia = 0.96;
				p_diabetes = 1;
			}
		}
		else
		{//if the person has Diabetes
			if (person.bmi_status == "Normal")
			{//if the person has Normal BMI
				p_normal = 0.0;
				p_pre_dia = 0.015;
				p_diabetes = 1;
			}
			else if (person.bmi_status == "Overweight")
			{//Overweight
				p_normal = 0.0;
				p_pre_dia = 0.005;
				p_diabetes = 1;
			}
			else
			{//Obese
				p_normal = 0.0;
				p_pre_dia = 0.0025;
				p_diabetes = 1;
			}
		}


		double rnd = rand();
		std::mt19937 mt(rnd);
		std::uniform_real_distribution<double> dist(0, 1);
		double initial_p_diabetes;
		initial_p_diabetes = dist(mt);
		if (initial_p_diabetes<p_normal)
		{
			diabetes_status = "Normal";
		}
		else if (initial_p_diabetes>p_normal & initial_p_diabetes<p_pre_dia)
		{
			diabetes_status = "Predia";
		}
		else if (initial_p_diabetes>p_pre_dia & initial_p_diabetes<p_diabetes)
		{
			diabetes_status = "Diabetes";
		}
	}
	void death_probability(individual person, int year, std::vector<std::vector<double>> v_m_death_rate, std::vector<std::vector<double>> v_f_death_rate)
	{
		double rnd = rand();
		std::mt19937 mt(rnd);
		std::uniform_real_distribution<double> dist(0, 1);
		double initial_p_death = 0;
		initial_p_death = dist(mt);
		double p_death = 0;
		if (person.diabetes_status == "Diabetes")
		{
			if (person.person_gender == "Male")
			{
				double death_factor = 0;
				if (person.person_age > 90)
				{
					death_factor = 0;
				}
				else
				{
					death_factor = m_death_factor[(person.person_age / 10) - 2];
				}
				double risk_score = (0.0586*person.person_age + 0.1078*abs(person.bmi_value - 26) + death_factor);
				p_death = ((1 - (pow(0.9567, exp(0.9768*(risk_score + 0.0415))))) / 5);
			}
			else
			{
				double death_factor = 0;
				if (person.person_age > 90)
				{
					death_factor = 0;
				}
				else
				{
					death_factor = m_death_factor[(person.person_age / 10) - 2];
				}
				double risk_score = (0.0586*person.person_age - 0.7049 + 0.1078*abs(person.bmi_value - 26) + death_factor);
				p_death = ((1 - (pow(0.9567, exp(0.9768*(risk_score + 0.0415))))) / 5);
			}
		}
		else
		{
			if (person.person_gender == "Male")
			{
				if (person.person_age > 100)
				{
					p_death = 1;
				}
				else
				{
					p_death = v_m_death_rate[year][person.person_age - 20];
				}
			}
			else
			{
				if (person.person_age > 100)
				{
					p_death = 1;
				}
				else
				{
					p_death = v_f_death_rate[year][person.person_age - 20];
				}
			}
		}

		if (initial_p_death<p_death)
		{
			alive = 0;
		}
		else
		{
			alive = 1;
		}
	}
	void update_bmi(individual person)
	{
		double rnd = rand();
		std::mt19937 mt(rnd);
		std::uniform_real_distribution<double> dist(0, 1);
		double p_update_bmi = 0.0;
		p_update_bmi = dist(mt);
		if (p_update_bmi > 0.5)
		{
			if (person.person_gender == "Male")
			{
				bmi_value += 0.2;
			}
			else
			{
				bmi_value += 0.15;
			}
		}
		if (person.bmi_value <= 25)
		{
			bmi_status = "Normal";
		}
		else if (person.bmi_value>25 && person.bmi_value<30)
		{
			bmi_status = "Overweight";
		}
		else
		{
			bmi_status = "Obese";
		}
	}
};

std::vector<int>	v_st_age;
std::vector<int>	v_end_age;
std::vector<int>	v_age_pop;
std::vector<double>	v_p_male;
std::vector<double>	v_p_get_prediabetes;
std::vector<double>	v_p_diabetes;
std::vector<double>	v_p_bmi_u;
std::vector<double>	v_p_bmi_n;
std::vector<double>	v_p_bmi_o;

std::vector<double> v_birth_rate;
std::vector<std::vector<double>> v_m_death_rate;
std::vector<std::vector<double>> v_f_death_rate;

std::vector<double>	v_y_p_male;
std::vector<double>	v_y_p_get_prediabetes;
std::vector<double>	v_y_p_diabetes;
std::vector<double>	v_y_p_bmi_u;
std::vector<double>	v_y_p_bmi_n;
std::vector<double>	v_y_p_bmi_o;

void read_age_group()
{
	//reading Age_group_data.txt file consisting of starting age, end age, population of age group, probability of being male in an age group, probabiliy of having
	//having pre_diabetes, probability of having diabetesm, probability being underweight, normal, and overweight
	std::ifstream file("C:/Users/snasrol/Google Drive/Research-Diabeties simulation/Code, Data, Results/Me/Data/Age_groups_data.txt");
	std::string   line;
	while (std::getline(file, line))
	{
		std::stringstream	linestream(line);
		std::string         st_age;				//starting age of age group
		int					end_age;			//ending age of age group
		int					age_pop;			//age group population
		double				p_male;				//proability of being male in an age group
		double				p_get_prediabetes;  //probability of "getting" pre_diabetes
		double				p_diabetes;			//probability of having diabetes
		double				p_bmi_u;			//probability of being underweight
		double				p_bmi_n;			//probability of having normal weight
		double				p_bmi_o;			//probability of being overewight
												//read the first element of the line separated by a TAB
		std::getline(linestream, st_age, '\t');
		//reading the rest of data separated by a TAB into variables
		linestream >> end_age >> age_pop >> p_male >> p_get_prediabetes >> p_diabetes >> p_bmi_u >> p_bmi_n >> p_bmi_o;
		//converts st_age from string to integer and push it into the vector
		v_st_age.push_back(atoi(st_age.c_str()));
		//pushing the data into vectors
		v_end_age.push_back(end_age);
		v_age_pop.push_back(age_pop);
		v_p_male.push_back(p_male);
		v_p_get_prediabetes.push_back(p_get_prediabetes);
		v_p_diabetes.push_back(p_diabetes);
		v_p_bmi_u.push_back(p_bmi_u);
		v_p_bmi_n.push_back(p_bmi_n);
		v_p_bmi_o.push_back(p_bmi_o);
	}
}
void read_birth_death_rate()
{
	//reading Birth_rate_data.txt file
	std::ifstream file_birth("C:/Users/snasrol/Google Drive/Research-Diabeties simulation/Code, Data, Results/Me/Data/Birth_rate_data.txt");
	std::string   line;
	while (std::getline(file_birth, line))
	{
		std::stringstream	linestream(line);
		std::string         birth_rate;
		std::getline(linestream, birth_rate);
		v_birth_rate.push_back(atof(birth_rate.c_str()));
	}
	file_birth.close();
	//reading m_death_rate_data.txt file
	std::ifstream file_m_death("C:/Users/snasrol/Google Drive/Research-Diabeties simulation/Code, Data, Results/Me/Data/m_death_rate_data.txt");
	while (std::getline(file_m_death, line))
	{
		v_m_death_rate.push_back(std::vector<double>());
		std::stringstream	linestream(line);
		std::string         death_rate;
		while (std::getline(linestream, death_rate, ','))
		{
			v_m_death_rate.back().push_back(atof(death_rate.c_str()));
		}
	}
	file_m_death.close();
	//reading f_death_rate_data.txt file
	std::ifstream file_f_death("C:/Users/snasrol/Google Drive/Research-Diabeties simulation/Code, Data, Results/Me/Data/f_death_rate_data.txt");
	while (std::getline(file_f_death, line))
	{
		v_f_death_rate.push_back(std::vector<double>());
		std::stringstream	linestream(line);
		std::string         death_rate;
		while (std::getline(linestream, death_rate, ','))
		{
			v_f_death_rate.back().push_back(atof(death_rate.c_str()));
		}
	}
	file_f_death.close();
}
void read_year_group_data()
{
	//read Year_20_25_group_data.txt file
	std::ifstream file("C:/Users/snasrol/Google Drive/Research-Diabeties simulation/Code, Data, Results/Me/Data/Year_20_25_group_data.txt");
	std::string   line;
	while (std::getline(file, line))
	{
		std::stringstream	linestream(line);
		std::string         year;
		double				p_male;				//proability of being male in an age group
		double				p_get_prediabetes;  //probability of "getting" pre_diabetes
		double				p_diabetes;			//probability of having diabetes
		double				p_bmi_u;			//probability of being underweight
		double				p_bmi_n;			//probability of having normal weight
		double				p_bmi_o;			//probability of being overewight 
												//read the first element of the line separated by a TAB
		std::getline(linestream, year, '\t');
		//reading the rest of data separated by a TAB into variables
		linestream >> p_male >> p_diabetes >> p_get_prediabetes >> p_bmi_u >> p_bmi_n >> p_bmi_o;
		v_y_p_male.push_back(p_male);
		v_y_p_get_prediabetes.push_back(p_get_prediabetes);
		v_y_p_diabetes.push_back(p_diabetes);
		v_y_p_bmi_u.push_back(p_bmi_u);
		v_y_p_bmi_n.push_back(p_bmi_n);
		v_y_p_bmi_o.push_back(p_bmi_o);
	}
}

int get_bmi_ind(std::string bmi_status)
{
	if (bmi_status == "Normal")
	{
		return 0;
	}
	else if (bmi_status == "Overweight")
	{
		return 1;
	}
	else
	{//bmi_status==Obese
		return 2;
	}
}
int get_diabetes_ind(std::string diabetes_status)
{
	if (diabetes_status == "Normal")
	{
		return 0;
	}
	else if (diabetes_status == "Predia")
	{
		return 1;
	}
	else
	{//diabetes_status==Diabetes
		return 2;
	}
}
int get_age_ind(int age)
{
	if (age >= 105)
	{
		return 16; //the last index of in age groups is 16
	}
	else
	{
		return ((age / 5) - 4); //the least age is 20 which translates into index 0
	}
}
int get_gender_ind(std::string gender)
{
	if (gender == "Male")
	{
		return 0;
	}
	else
	{//gender==Female
		return 1;
	}
}

int main()
{
	std::ofstream results;
	int tot_pop = 272357; //272357 is the total population after simulating from 1997-2010
	int intervention_year = 14;
	std::vector<individual> v_people;
	std::vector<individual> v_people_alive;
	std::vector<individual> v_people_dead;
	//create a reference for class individual
	individual person;
	//call function read_age_group to read Age_groups_data.txt file
	read_age_group();
	int no_age_groups;
	no_age_groups = v_st_age.size();
	//call function read_birth_rate to read birth_rate_data.txt file
	read_birth_death_rate();
	int no_sim_years;
	no_sim_years = 29;
	//call function read_year_group_data to read Year_20_25_group_data.txt file
	read_year_group_data();
	//in intervention simulation only the data of the last year is used
	int last_year_birth_death = v_birth_rate.size(); //used as index for updating death probabilities
	int last_year_grop_data = v_y_p_male.size(); //used as index for updating new born populations data
	int initial_pop = 0;
	for (int reps = 1; reps < 2; reps++)
	{//for reps=3 replications
	 //generate a seed for each replication
		srand(reps);
		double rnd = rand();
		std::mt19937 mt(rnd);
		std::cout << "creating age groups population..." << std::endl;
		for (int age_gr_ind = 0; age_gr_ind < no_age_groups; age_gr_ind++)
		{//for each age group in Age_groups_data.txt file
			for (int pop_ind = 0; pop_ind < v_age_pop.at(age_gr_ind); pop_ind++)
			{//for each person create index of the person under simulation
			 //this module creates each person in the people's vector
				person.getindex();
				//create a random age for the person in age group(age_gr_ind)
				person.getage(v_st_age.at(age_gr_ind), v_end_age.at(age_gr_ind));
				//create a random gender for the person in age group(.)
				person.getgender(v_p_male.at(age_gr_ind));
				//create a random initial bmi for the person in age group(.)
				person.initial_bmi(v_p_bmi_n.at(age_gr_ind), v_p_bmi_o.at(age_gr_ind));
				//create a random status for diabetes of the person in age group(.)
				person.initial_diabetes(v_p_get_prediabetes.at(age_gr_ind), v_p_diabetes.at(age_gr_ind));
				//push the person information: index, age, gender, bmi, diabetes status into the vector of people
				v_people.push_back(person);
			}
		}
		//right now, the population of each age group is created and assigned values of index, age, gender, bmi, diabetes status
		for (int year = 0; year < no_sim_years; year++)
		{//simulating years
		 //for each year the birth rate is calculated for new people who are added to the age-group 20-25.
			int no_diabetes_new_pop = 0;
			int no_new_updated_diabetes = 0;
			int new_pop = 0;
			initial_pop = v_people.size();
			if (year <= 13)
			{
				new_pop = tot_pop*v_birth_rate.at(year);
			}
			else
			{
				new_pop = tot_pop*v_birth_rate.at(last_year_birth_death - 1);
			}
			std::cout << "creating new population for 20-25 age group..." << std::endl;
			if (year < 13)
			{
				for (int new_pop_ind = 0; new_pop_ind < new_pop; new_pop_ind++)
				{//for each person in the new population
				 //this module creates a new person in people's vector
					person.getindex();
					person.getage(20, 25); //recall that the new population is only added to age group 20-25
										   //v_y_p_male is the 'v'ector of 'p_male' for each 'y'ear
					person.getgender(v_y_p_male.at(year));
					person.initial_bmi(v_y_p_bmi_n.at(year), v_y_p_bmi_o.at(year));
					person.initial_diabetes(v_y_p_get_prediabetes.at(year), v_y_p_diabetes.at(year));
					if (person.diabetes_status == "Diabetes")
					{
						no_diabetes_new_pop++;
					}
					v_people.push_back(person);
				}
			}
			else
			{
				for (int new_pop_ind = 0; new_pop_ind < new_pop; new_pop_ind++)
				{//for each person in the new population
				 //this module creates a new person in people's vector
					person.getindex();
					person.getage(20, 25); //recall that the new population is only added to age group 20-25
										   //v_y_p_male is the 'v'ector of 'p_male' for each 'y'ear
					person.getgender(v_y_p_male.at(last_year_grop_data - 1));
					person.initial_bmi(v_y_p_bmi_n.at(last_year_grop_data - 1), v_y_p_bmi_o.at(last_year_grop_data - 1));
					person.initial_diabetes(v_y_p_get_prediabetes.at(last_year_grop_data - 1), v_y_p_diabetes.at(last_year_grop_data - 1));
					if (person.diabetes_status == "Diabetes")
					{
						no_diabetes_new_pop++;
					}
					v_people.push_back(person);
				}
			}
			std::cout << "updating diabetes status & alive/dead status..." << std::endl;
			//clean the people's vector to separate alive people and push them back in
			std::ofstream delay_results;
			delay_results.open("C:/Users/snasrol/Google Drive/Research-Diabeties simulation/Code, Data, Results/Me/Results/15years-inclusion/DPP(YMCA)-delays.txt", std::ofstream::out | std::ofstream::app);
			for (int np_op_ind = 0; np_op_ind < v_people.size(); np_op_ind++)
			{//for each person in new and old population
			 //updating diabetes status wrt previous diabetes status and current bmi status
				bool previous_diabetes_state = 0;
				if (v_people.at(np_op_ind).diabetes_status == "Diabetes")
				{//if a person already has diabetes or not
					previous_diabetes_state = 1;
				}
				//update people's diabetes status
				v_people.at(np_op_ind).update_diabetes(v_people.at(np_op_ind));

				if (v_people.at(np_op_ind).diabetes_status == "Diabetes" && previous_diabetes_state == 0)
				{//if a person has diabetes and didn't have it before
					delay_results << v_people.at(np_op_ind).person_ind << '\t' << v_people.at(np_op_ind).person_age <<'\t' << year << std::endl;
					no_new_updated_diabetes++;
				}
				//assigning death probabilities people
				v_people.at(np_op_ind).death_probability(v_people.at(np_op_ind), last_year_birth_death-1, v_m_death_rate, v_f_death_rate);
				if (v_people.at(np_op_ind).alive == 1)
				{//separating alive and dead people
					v_people_alive.push_back(v_people.at(np_op_ind));
				}
				else
				{
					v_people_dead.push_back(v_people.at(np_op_ind));
				}
			}
			v_people.clear();
			long no_intervention = 0;
			long no_intervention_by_age[4]={0};
			std::cout << "updating bmi values..." << std::endl;
			for (int ap_ind = 0; ap_ind < v_people_alive.size(); ap_ind++)
			{//for each person alive
			 //updates the bmi value
				v_people_alive.at(ap_ind).update_bmi(v_people_alive.at(ap_ind));
				if (year == intervention_year)
				{//the year that intervention happens in
					if (v_people_alive.at(ap_ind).person_age >= 20 && v_people_alive.at(ap_ind).bmi_value >= 24 && v_people_alive.at(ap_ind).diabetes_status == "Predia")
					{//inclusion criteria for people who go under intervention
						no_intervention++;
						if (v_people_alive.at(ap_ind).person_age<=65 && v_people_alive.at(ap_ind).person_age>=55)
						{
							no_intervention_by_age[0]++;
						}
						if (v_people_alive.at(ap_ind).person_age<=65 && v_people_alive.at(ap_ind).person_age>=45)
						{
							no_intervention_by_age[1]++;
						}
						if (v_people_alive.at(ap_ind).person_age<=65 && v_people_alive.at(ap_ind).person_age>=35)
						{
							no_intervention_by_age[2]++;
						}
						if (v_people_alive.at(ap_ind).person_age<=65 && v_people_alive.at(ap_ind).person_age>=25)
						{
							no_intervention_by_age[3]++;
						}
						//DPP-YMCA intervention causes the bmi value to drop 7% 
						v_people_alive.at(ap_ind).bmi_value -= 0.053*v_people_alive.at(ap_ind).bmi_value;
					}
				}
				//each alive person gets older
				v_people_alive.at(ap_ind).person_age++;
				//pushing the new person with new bmi and new age in the people's vector
				v_people.push_back(v_people_alive.at(ap_ind));
			}
			std::cout << "gathering simulation results..." << std::endl;
			//after the above for, v_people = v_alive_people
			//declare a 4d vector for alive people after intervention based on age_group. gender, bmi_status and diabetes_status
			std::vector<std::vector<std::vector<std::vector<int>>>> count_alive_results;
			for (int age_ind = 0; age_ind < no_age_groups; age_ind++)
			{//initializing the 4d vector
				count_alive_results.push_back(std::vector<std::vector<std::vector<int>>>());
				for (int gender_ind = 0; gender_ind < 2; gender_ind++)
				{
					count_alive_results[age_ind].push_back(std::vector<std::vector<int>>());
					for (int bmi_ind = 0; bmi_ind < 3; bmi_ind++)
					{
						count_alive_results[age_ind][gender_ind].push_back(std::vector<int>());
						for (int diabetes_ind = 0; diabetes_ind < 3; diabetes_ind++)
						{
							count_alive_results[age_ind][gender_ind][bmi_ind].push_back(0);
						}
					}
				}
			}
			//declate an ofstream for aversion and delay results
			for (int alive_ind = 0; alive_ind < v_people.size(); alive_ind++)
			{//for each person alive 
				count_alive_results[get_age_ind(v_people.at(alive_ind).person_age)][get_gender_ind(v_people.at(alive_ind).person_gender)][get_bmi_ind(v_people.at(alive_ind).bmi_status)][get_diabetes_ind(v_people.at(alive_ind).diabetes_status)]++;
			}
			std::vector<std::vector<std::vector<std::vector<int>>>> count_dead_results;
			for (int age_ind = 0; age_ind < no_age_groups; age_ind++)
			{//initializing the 4d vector
				count_dead_results.push_back(std::vector<std::vector<std::vector<int>>>());
				for (int gender_ind = 0; gender_ind < 2; gender_ind++)
				{
					count_dead_results[age_ind].push_back(std::vector<std::vector<int>>());
					for (int bmi_ind = 0; bmi_ind < 3; bmi_ind++)
					{
						count_dead_results[age_ind][gender_ind].push_back(std::vector<int>());
						for (int diabetes_ind = 0; diabetes_ind < 3; diabetes_ind++)
						{
							count_dead_results[age_ind][gender_ind][bmi_ind].push_back(0);
						}
					}
				}
			}
			for (int dead_ind = 0; dead_ind < v_people_dead.size(); dead_ind++)
			{//for each person dead
				count_dead_results[get_age_ind(v_people_dead.at(dead_ind).person_age)][get_gender_ind(v_people_dead.at(dead_ind).person_gender)][get_bmi_ind(v_people_dead.at(dead_ind).bmi_status)][get_diabetes_ind(v_people_dead.at(dead_ind).diabetes_status)]++;
			}
			int diabetes_state = 0; //shows if the person has diabetes =1 or not=0
			long no_diabetes = 0;		//'n'umber 'o'f alive people with diabetes
			long no_diabetes_dead = 0;	//'n'umber 'o'f dead people with diabetes
			long no_pre_dia = 0;		//'n'umber 'o'f alive people with 'pre'diabetes
			long no_pre_dia_dead = 0;	//'n'umber 'o'f dead people with 'pre'diabetes
			long no_diabetes_death_by_age[4] = { 0 };
			long no_diabetes_by_age[4] = { 0 };
			for (int age_ind = 0; age_ind < no_age_groups; age_ind++)
			{//for all age_groups
				for (int gender_ind = 0; gender_ind < 2; gender_ind++)
				{//for all genders
					for (int bmi_ind = 0; bmi_ind < 3; bmi_ind++)
					{//for all bmi statuses
					 //the last index is the diabetes status where 2 indicates diabetes, and 1 indicates pre-diabetes
						
						// differentiating the no diabetes death and diabetes by age group 0:55-65, 1:45-65, 2:35-65, 3:25-65
						if (age_ind >= 7 && age_ind <= 8)
						{
							no_diabetes_by_age[0] += count_alive_results[age_ind][gender_ind][bmi_ind][2];
							no_diabetes_death_by_age[0] += count_dead_results[age_ind][gender_ind][bmi_ind][2];
						}
						if (age_ind >= 5 && age_ind <= 8)
						{
							no_diabetes_by_age[1] += count_alive_results[age_ind][gender_ind][bmi_ind][2];
							no_diabetes_death_by_age[1] += count_dead_results[age_ind][gender_ind][bmi_ind][2];
						}
						if (age_ind >= 3 && age_ind <= 8)
						{
							no_diabetes_by_age[2] += count_alive_results[age_ind][gender_ind][bmi_ind][2];
							no_diabetes_death_by_age[2] += count_dead_results[age_ind][gender_ind][bmi_ind][2];
						}
						if (age_ind >= 1 && age_ind <= 8)
						{
							no_diabetes_by_age[3] += count_alive_results[age_ind][gender_ind][bmi_ind][2];
							no_diabetes_death_by_age[3] += count_dead_results[age_ind][gender_ind][bmi_ind][2];
						}
						no_diabetes += count_alive_results[age_ind][gender_ind][bmi_ind][2];
						no_diabetes_dead += count_dead_results[age_ind][gender_ind][bmi_ind][2];
						no_pre_dia += count_alive_results[age_ind][gender_ind][bmi_ind][1];
						no_pre_dia_dead += count_dead_results[age_ind][gender_ind][bmi_ind][1];
					}
				}
			}
			//printing the year, initial total population, new born population, final population after death and intervention, number of death, number of diabetes incidence among alive
			//people, number of diabetes incidence among dead people, number of pre-diabetes among alive people, number of pre-diabetes among dead poeple, number of interventions
			std::ofstream results;
			results.open("C:/Users/snasrol/Google Drive/Research-Diabeties simulation/Code, Data, Results/Me/Results/15years-inclusion/DPP(YMCA)-statistics.txt", std::ofstream::out | std::ofstream::app);
			results << year << '\t' << tot_pop << '\t' << new_pop << '\t' << v_people.size() << '\t' << v_people_dead.size() << '\t' << no_diabetes_new_pop << '\t' << no_new_updated_diabetes << '\t' << no_diabetes << '\t' << no_diabetes_dead << '\t' << no_pre_dia << '\t' << no_pre_dia_dead << '\t' << no_intervention << std::endl;
			results.close();
			//results by age group
			std::ofstream results0;
			results0.open("C:/Users/snasrol/Google Drive/Research-Diabeties simulation/Code, Data, Results/Me/Results/15years-inclusion/DPP(YMCA)-statistics0.txt", std::ofstream::out | std::ofstream::app);
			results0 << year << '\t' << no_diabetes_by_age[0] << '\t' << no_diabetes_death_by_age[0] << '\t' << no_intervention_by_age[0] << std::endl;
			results0.close();
			std::ofstream results1;
			results1.open("C:/Users/snasrol/Google Drive/Research-Diabeties simulation/Code, Data, Results/Me/Results/15years-inclusion/DPP(YMCA)-statistics1.txt", std::ofstream::out | std::ofstream::app);
			results1 << year << '\t' << no_diabetes_by_age[1] << '\t' << no_diabetes_death_by_age[1] << '\t' << no_intervention_by_age[1] << std::endl;
			results1.close();
			std::ofstream results2;
			results2.open("C:/Users/snasrol/Google Drive/Research-Diabeties simulation/Code, Data, Results/Me/Results/15years-inclusion/DPP(YMCA)-statistics2.txt", std::ofstream::out | std::ofstream::app);
			results2 << year << '\t' << no_diabetes_by_age[2] << '\t' << no_diabetes_death_by_age[2] << '\t' << no_intervention_by_age[2] << std::endl;
			results2.close();
			std::ofstream results3;
			results3.open("C:/Users/snasrol/Google Drive/Research-Diabeties simulation/Code, Data, Results/Me/Results/15years-inclusion/DPP(YMCA)-statistics3.txt", std::ofstream::out | std::ofstream::app);
			results3 << year << '\t' << no_diabetes_by_age[3] << '\t' << no_diabetes_death_by_age[3] << '\t' << no_intervention_by_age[3] << std::endl;
			results3.close();
			//new total population is the population alive and saved in v_people vector
			tot_pop = v_people.size();
			v_people_dead.clear();
			v_people_alive.clear();
			std::ofstream detail_results[17]; //17=no_age_groups
			for (int age_ind = 0; age_ind < no_age_groups; age_ind++)
			{
				detail_results[age_ind].open("C:/Users/snasrol/Google Drive/Research-Diabeties simulation/Code, Data, Results/Me/Results/15years-inclusion/DPP(YMCA)-details" + std::to_string(age_ind) + ".txt", std::ofstream::out | std::ofstream::app);
				detail_results[age_ind] << year << '\t';
				for (int gender_ind = 0; gender_ind < 2; gender_ind++)
				{
					for (int bmi_ind = 0; bmi_ind < 3; bmi_ind++)
					{
						for (int diabetes_ind = 0; diabetes_ind < 3; diabetes_ind++)
						{
							detail_results[age_ind] << count_alive_results[age_ind][gender_ind][bmi_ind][diabetes_ind] << '\t' << count_dead_results[age_ind][gender_ind][bmi_ind][diabetes_ind] << '\t';
						}
					}
				}
				detail_results[age_ind] << std::endl;
			}
			std::cout << "End of year " << year << std::endl;
		}
		v_people.clear();
		std::cout << "End of replication " << reps << std::endl;
	}
	std::cin.ignore(10000, '\n');
	return 0;
}