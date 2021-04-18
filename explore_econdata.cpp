/*********************************************************************
** Program Filename: assignment 1 stgate ecnomic data cpp_print file
** Author: jaegeun oh
** Date: 1/16/2019
** Description: Bring the data file from the outside and sorting them into the struct
** Input: test_data.txt
** Output: state or county's economic datafile
*********************************************************************/

#include "econdata.hpp"

using namespace std;


/*********************************************************************
** Function: main 
** Description: main system 
** Parameters: 
** Pre-Conditions: user_input
** Post-Conditions: output from the function
*********************************************************************/ 

int main() {
	struct state *ptr_state;
	int num, again = 0, again2 = 0;
	string d_input, user_input, user_input2;
	
	ifstream inf("test_data.txt");
	inf >> d_input;
	num = atoi(d_input.c_str());

	ptr_state = allocate_states(num);
	read_state_data(ptr_state,num,inf);

	cout << "The data currently have " << num << " states." << endl;
	for(int i = 0; i < num; i++) {
		cout << i+1 << ". " << ptr_state[i].name << endl;
	}
	cout << "\nOverall information------" << endl;
	cout << "1. The highest median household income" << endl;
	cout << "2. The lowest median household ioncome" << endl;
	cout << "3. The highest unemployment in 2015" << endl;
	cout << "4. The lowest unemployment in 2015" << endl;
	cout << "5. Change unemployment from 2007 to 2015" << endl;
	cout << "6. The states in order based on median household income" << endl;
	
	while(again == 0) {
		cout <<"\nEnter the state you want to see the economic data or number (q = quite): ";
		getline(cin, user_input);
	
		if(user_input == "q" || user_input == "Q") {
		again = 1;
		}
		else if(user_input == "1") {h_house(ptr_state, num);}
		else if(user_input == "2") {l_house(ptr_state, num);}
		else if(user_input == "3") {h_2015(ptr_state, num);}
		else if(user_input == "4") {l_2015(ptr_state, num);}
		else if(user_input == "5") {evol_un(ptr_state, num);}
		else if(user_input == "6") {med_house(ptr_state, num);}

		for(int i = 0; i < num; i++) {
		if(user_input == ptr_state[i].name) {
			cout << "\nOverall information------" << endl;
			cout << "1. The highest median household income" << endl;
			cout << "2. The lowest median household ioncome" << endl;
			cout << "3. The highest unemployment in 2015" << endl;
			cout << "4. The lowest unemployment in 2015" << endl;
			cout << "5. Change unemployment from 2007 to 2015" << endl;
			cout << "6. The states in order based on median household income" << endl;
			while(again2 == 0){
			cout <<"\nEnter the number to see the county economic data (q = quite): ";
			getline(cin, user_input2);
			if(user_input2 == "1") {ch_house(ptr_state[i].counties, ptr_state[i].num_county);}
			else if(user_input2 == "2") {cl_house(ptr_state[i].counties, ptr_state[i].num_county);}
			else if(user_input2 == "3") {ch_2015(ptr_state[i].counties, ptr_state[i].num_county);}
			else if(user_input2 == "4") {cl_2015(ptr_state[i].counties, ptr_state[i].num_county);}
			else if(user_input2 == "5") {cevol_un(ptr_state[i].counties, ptr_state[i].num_county);}
			else if(user_input2 == "6") {cmed_house(ptr_state[i].counties, ptr_state[i].num_county);}
			else if(user_input2 == "q" || user_input2 == "Q") {again2 = 1;}
			}
		}
	}

	}
	free_state_data(ptr_state,num);
	return 0;
}