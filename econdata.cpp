/*********************************************************************
** Program Filename: assignment 1 stgate ecnomic data
** Author: jaegeun oh
** Date: 1/16/2019
** Description: Bring the data file from the outside and sorting them into the struct
** Input: test_data.txt
** Output: state or county's economic datafile
*********************************************************************/

#include "econdata.hpp"


using namespace std;

struct state* allocate_states(int num) {
	struct state *ptr_state = new state[num];
return ptr_state;
}

struct county* allocate_counties(int c_num) {
	struct county *ptr_county = new county[c_num];
return ptr_county;
}

/*********************************************************************
** Function: read_county_data
** Description: sorting the data into the county strcut file
** Parameters: struct, int, inf(reading file)
** Pre-Conditions: county struct, number of county, reading file
** Post-Conditions: nothing
*********************************************************************/ 

void read_county_data(struct county* datas, int c_num, ifstream& inf) {
	struct county *ptr_county;
	ptr_county = datas;
	string d_input;

	for(int i = 0; i < c_num; i++) {
		inf >> d_input;
		ptr_county[i].name = d_input;
		inf >> d_input;
		ptr_county[i].unemployed_2007 = atof(d_input.c_str());
		inf >> d_input;
		ptr_county[i].unemployed_2015 = atof(d_input.c_str());
		inf >> d_input;
		ptr_county[i].med_income = atoi(d_input.c_str());
	}

}

/*********************************************************************
** Function: read_state_data
** Description: sorting the data into the state struct file and county at the same time
** Parameters: struct, int, inf(reading file)
** Pre-Conditions: state struct, number of state, reading file
** Post-Conditions: nothing
*********************************************************************/ 

void read_state_data(struct state* datas, int num, ifstream& inf){
	struct state *ptr_state;
	ptr_state = datas;
	string d_input;
	for(int i = 0; i < num; i++) {
		inf >> d_input;	
		ptr_state[i].name = d_input;
		inf >> d_input;
		ptr_state[i].unemployed_2007 = atof(d_input.c_str());
		inf >> d_input;
		ptr_state[i].unemployed_2015 = atof(d_input.c_str());
		inf >> d_input;
		ptr_state[i].med_income = atoi(d_input.c_str());
		inf >> d_input;
		ptr_state[i].num_county = atoi(d_input.c_str());
		ptr_state[i].counties = allocate_counties(ptr_state[i].num_county);
		read_county_data(ptr_state[i].counties, ptr_state[i].num_county, inf);
	}
	
}

/*********************************************************************
** Function: free_state_data
** Description: deleting data to prevent leaking data
** Parameters: struct, int
** Pre-Conditions: state struct, number of state, reading file
** Post-Conditions: nothing
*********************************************************************/ 

void free_state_data(struct state* datas, int num) {
	struct state *ptr_state;
	ptr_state = datas;
	for(int i = 0; i < num; i++) {
		delete[] ptr_state[i].counties;
	}
	delete[] ptr_state;
}

/*********************************************************************
** Function: evol_un
** Description: showing how economic data change from 2015 to 2007
** Parameters: struct, int
** Pre-Conditions: state struct, number of state
** Post-Conditions: lowest change to highest change
*********************************************************************/ 

void evol_un(struct state* datas, int num) {
	string name[num];
	float rate[num];
	struct state *ptr_state;
	ptr_state = datas;

	cout << "\nChange unemployment from 2007 to 2015--------" << endl;
	for(int i = 0; i < num; i++) {
		rate[i] = ptr_state[i].unemployed_2015 - ptr_state[i].unemployed_2007;
	}
	sort(rate, rate+num, greater<float>());

	for(int i = 0; i < num; i++) {
		for(int j = 0; j < num; j++) {
		if((ptr_state[j].unemployed_2015 - ptr_state[j].unemployed_2007) == rate[i]) {
			name[i] = ptr_state[j].name;
		}
		}
	}
	for(int i = 0; i < num; i++) {
		cout << name[i] << "'s unemployment change from 2007 to 2015 is " << rate[i] << "%" << endl;
	}
}

/*********************************************************************
** Function: med_house
** Description: sorting showing the median house income 
** Parameters: struct, int
** Pre-Conditions: state struct, number of state
** Post-Conditions: shows highest house income to the lowest house income
*********************************************************************/ 

void med_house(struct state* datas, int num) {
	struct state *ptr_state;
	ptr_state = datas;
	float rate[num];
	string name[num];

	cout << "\nMedian house hold income order-----" << endl;
	for(int i = 0; i < num; i++) {
		rate[i] = ptr_state[i].med_income;
	}
	sort(rate, rate+num, greater<float>());
	for(int i = 0; i < num; i++) {
		for(int j = 0; j < num; j++) {
		if(ptr_state[j].med_income == rate[i]) {
			name[i] = ptr_state[j].name;
			}
		}
	}
	for(int i = 0; i < num; i++) {
		cout << name[i] << "'s median house hold income " << "$" << rate[i] << endl;
	}
}

/*********************************************************************
** Function: h_house
** Description: show the highest median house income
** Parameters: struct, int
** Pre-Conditions: state struct, number of state
** Post-Conditions: the highest median house income
*********************************************************************/ 

void h_house(struct state* datas, int num) {
	int s_num;
	int max = 0;
	struct state *ptr_state;
	ptr_state = datas;

	for(int i = 0; i < num; i++) {
		if(ptr_state[i].med_income > max) {
			max = ptr_state[i].med_income;
			s_num = i;
		}
	}
	cout << ptr_state[s_num].name << " has the highest median household incom: $" << max << endl;
}

/*********************************************************************
** Function: h_2015
** Description: shows the highest 2015 income
** Parameters: struct, int
** Pre-Conditions: state struct, number of state
** Post-Conditions: the highest 2015 state income
*********************************************************************/ 

void h_2015(struct state* datas, int num) {
	int s_num;
	float max = 0;
	struct state *ptr_state;
	ptr_state = datas;

	for(int i = 0; i < num; i++) {
		if(ptr_state[i].unemployed_2015 > max) {
			max = ptr_state[i].unemployed_2015;
			s_num = i;
		}
	}
	cout << ptr_state[s_num].name << " has the highest 2015 unemployed rate: " << max << "%" << endl;;
}

/*********************************************************************
** Function: l_house
** Description: show the lowest house income
** Parameters: struct, int
** Pre-Conditions: state struct, number of state
** Post-Conditions: shows the lowest house income
*********************************************************************/ 

void l_house(struct state* datas, int num) {
	string name;
	int min = 0;
	struct state *ptr_state;
	ptr_state = datas;

	for(int i = 0; i < num; i++) {
		if(ptr_state[i].med_income > min) {
			min = ptr_state[i].med_income;
		}	
	}
	for(int i = 0; i < num; i++) {
		if(ptr_state[i].med_income < min) {
			min = ptr_state[i].med_income;
			name = ptr_state[i].name;
		}
	}
	cout << name << " has the lowest median household incom: $" << min << endl;
}

/*********************************************************************
** Function: l_2015
** Description: shows the 2015 lowest unemployment state
** Parameters: struct, int
** Pre-Conditions: sate struct, number of state
** Post-Conditions: shows the 2015 lowest unemployment
*********************************************************************/ 

void l_2015(struct state* datas, int num) {
	string name;
	float min = 0;

	struct state *ptr_state;
	ptr_state = datas;

	for(int i = 0; i < num; i++) {
		if(ptr_state[i].unemployed_2015 > min) {
			min = ptr_state[i].unemployed_2015;
		}
	}
	for(int i = 0; i < num; i++) {
		if(ptr_state[i].unemployed_2015 < min) {
			min = ptr_state[i].unemployed_2015;
			name = ptr_state[i].name;
		}
	}
	cout << name << " has the lowest 2015 unemployed rate: " << min << "%" << endl;
}

/*********************************************************************
** Function: cevol_un
** Description: showing county economic data from
** Parameters: struct int
** Pre-Conditions: county strucy, number of county
** Post-Conditions: change unemployment from 2007 to 2015
*********************************************************************/ 

void cevol_un(struct county* datas, int num) {
	string name[num], s_time;
	float rate[num], temp;
	struct county *ptr_state;
	ptr_state = datas;

	cout << "\nChange unemployment from 2007 to 2015--------" << endl;
	for(int i = 0; i < num; i++) {
		rate[i] = ptr_state[i].unemployed_2015 - ptr_state[i].unemployed_2007;
		name[i] = ptr_state[i].name;
	}

	for(int i=0; i< num; i++) {
        for(int j=i+1; j< num; j++) {
            if(rate[i]>rate[j]) {
                temp = rate[i];
                rate[i] = rate[j];
                rate[j] = temp;

                s_time = name[i];
                name[i] = name[j];
                name[j] = s_time;
			}
		}
	}

	for(int i = 0; i < num; i++) {
		cout << name[i] << "'s unemployment change from 2007 to 2015 is " << rate[i] << "%" << endl;
	}
}

/*********************************************************************
** Function: cmed_house
** Description: county median house hold income order
** Parameters: struct, int
** Pre-Conditions: county struct, number of county
** Post-Conditions: median house hold income order
*********************************************************************/ 

void cmed_house(struct county* datas, int num) {
	struct county *ptr_state;
	ptr_state = datas;
	float rate[num];
	string name[num];

	cout << "\nMedian house hold income order-----" << endl;
	for(int i = 0; i < num; i++) {
		rate[i] = ptr_state[i].med_income;
	}
	sort(rate, rate+num, greater<float>());
	for(int i = 0; i < num; i++) {
		for(int j = 0; j < num; j++) {
		if(ptr_state[j].med_income == rate[i]) {
			name[i] = ptr_state[j].name;
			}
		}
	}
	for(int i = 0; i < num; i++) {
		cout << name[i] << "'s median house hold income " << "$" << rate[i] << endl;
	}
}

/*********************************************************************
** Function: ch_house
** Description: show highest to lowest median house hold
** Parameters: struct, int
** Pre-Conditions: county struct, number of county
** Post-Conditions: show median house hold in order
*********************************************************************/ 

void ch_house(struct county* datas, int num) {
	int s_num;
	int max = 0;
	struct county *ptr_state;
	ptr_state = datas;

	for(int i = 0; i < num; i++) {
		if(ptr_state[i].med_income > max) {
			max = ptr_state[i].med_income;
			s_num = i;
		}
	}
	cout << ptr_state[s_num].name << " has the highest median household incom: $" << max << endl;
}

/*********************************************************************
** Function: ch_2015
** Description: show 2015 unemplyd rate
** Parameters:struct, int
** Pre-Conditions: county struct, number of county 
** Post-Conditions: shows the highest 2015 unemployed rate
*********************************************************************/ 

void ch_2015(struct county* datas, int num) {
	int s_num;
	float max = 0;
	struct county *ptr_state;
	ptr_state = datas;

	for(int i = 0; i < num; i++) {
		if(ptr_state[i].unemployed_2015 > max) {
			max = ptr_state[i].unemployed_2015;
			s_num = i;
		}
	}
	cout << ptr_state[s_num].name << " has the highest 2015 unemployed rate: " << max << "%" << endl;;
}

/*********************************************************************
** Function: cl_house
** Description: shows the lowest county house rate
** Parameters: struct, int
** Pre-Conditions: county struct, number of county 
** Post-Conditions: show the low county house rate
*********************************************************************/ 

void cl_house(struct county* datas, int num) {
	string name;
	int min = 0;
	struct county *ptr_state;
	ptr_state = datas;

	for(int i = 0; i < num; i++) {
		if(ptr_state[i].med_income > min) {
			min = ptr_state[i].med_income;
		}	
	}
	for(int i = 0; i < num; i++) {
		if(ptr_state[i].med_income < min) {
			min = ptr_state[i].med_income;
			name = ptr_state[i].name;
		}
	}
	cout << name << " has the lowest median household incom: $" << min << endl;
}

/*********************************************************************
** Function: cl_2015
** Description: show lowest 2015 house income
** Parameters: struct, int
** Pre-Conditions: county struct, number of county
** Post-Conditions: show lowest 2015 house income
*********************************************************************/ 

void cl_2015(struct county* datas, int num) {
	string name;
	float min = 0;

	struct county *ptr_state;
	ptr_state = datas;

	for(int i = 0; i < num; i++) {
		if(ptr_state[i].unemployed_2015 > min) {
			min = ptr_state[i].unemployed_2015;
		}
	}
	for(int i = 0; i < num; i++) {
		if(ptr_state[i].unemployed_2015 < min) {
			min = ptr_state[i].unemployed_2015;
			name = ptr_state[i].name;
		}
	}
	cout << name << " has the lowest 2015 unemployed rate: " << min << "%" << endl;
}
