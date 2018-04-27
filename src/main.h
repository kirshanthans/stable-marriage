#ifndef MAIN_H_
#define MAIN_H_
#include <cstdlib>
#include <iostream>

#define SIZE 3

using namespace std;

typedef struct person{
	int id;
	//id of a person
	int pid;
	//id of the potential partner
	bool engaged;
	//engaged with potential partner or not
	int rank[SIZE];
	//i:id rank[i]:rank 
	int proposed[SIZE];
	//i:id proposed[i]:proposed or not
}Person;

int getRank(Person a, Person b);
int getCurrentPartnerRank(Person x);
int getIDPotential(Person x);
bool terminate(Person* A);
void stable_match(Person* Man, Person* Woman);
void print_match(Person* Man);
#endif
