#include<fstream>
#include<iostream>
#include<cstdlib>
#include<string>
#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include <bits/stdc++.h> 

using namespace std;

struct county {
	string name;
	float unemployed_2007;
	float unemployed_2015;
	int med_income;
};

struct state {
	string name;
	float unemployed_2007;
	float unemployed_2015;
	int med_income;
	struct county* counties;
	int num_county;
};

struct state* allocate_states(int num);
struct county* allocate_counties(int c_num);
void read_county_data(struct county* datas, int c_num, ifstream& inf);
void read_state_data(struct state* datas, int num, ifstream& inf);
void free_state_data(struct state* datas, int num);
void evol_un(struct state* datas, int num);
void med_house(struct state* datas, int num);
void h_house(struct state* datas, int num);
void h_2015(struct state* datas, int num);
void l_house(struct state* datas, int num);
void l_2015(struct state* datas, int num);
void cevol_un(struct county* datas, int num);
void cmed_house(struct county* datas, int num);
void ch_house(struct county* datas, int num);
void ch_2015(struct county* datas, int num);
void cl_house(struct county* datas, int num);
void cl_2015(struct county* datas, int num);