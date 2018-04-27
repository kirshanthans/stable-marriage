#include "main.h"

int getRank(Person a, Person b)
{
	//find the rank of b in view of a
	return a.rank[b.id];
}

int getCurrentPartnerRank(Person x)
{
	return x.rank[x.pid];
}

int getIDPotential(Person x)
{
	//find the highest ranked person of who x hasn't proposed yet
	int r = SIZE;
	int pid = 0;
	for(int i = 0; i < SIZE; ++i){
		if(!x.proposed[i]){
			if(x.rank[i] < r){
				r = x.rank[i];
				pid = i;
			}	
		}
	}

	return pid;
}

bool terminate(Person* A)
{
	//if all are engaged terminate the matching
	for(int i = 0; i < SIZE; ++i){
		if(!A[i].engaged) return false;
	}
	return true;
}

void stable_match(Person* Man, Person* Woman)
{
	int count = 0;
	while(!terminate(Man)){
		//proposing phase: Man decides 
		for(int i = 0; i < SIZE; ++i){
			if(!Man[i].engaged){	
				int pid = getIDPotential(Man[i]);
				Man[i].pid = pid; 
				Man[i].proposed[pid] = true;
			}
		}
		//engaging phase: Woman decides
		for(int i = 0; i < SIZE; ++i){
			int proposedWomanID = Man[i].pid;
			int proposedManRank = getRank(Woman[proposedWomanID], Man[i]);
			if(Woman[proposedWomanID].engaged){
				int currentManRank  = getCurrentPartnerRank(Woman[proposedWomanID]);
				if (proposedManRank < currentManRank){
					//break the engagement
					Man[Woman[proposedWomanID].pid].engaged = false;
					//re-engage
					Woman[proposedWomanID].pid = Man[i].id;
					Woman[proposedWomanID].engaged = true;
					Man[i].pid = proposedWomanID;
					Man[i].engaged = true;

				}
			}
			else {
				//engage for the first time
				Woman[proposedWomanID].pid = Man[i].id;
				Woman[proposedWomanID].engaged = true;
				Man[i].pid = proposedWomanID;
				Man[i].engaged = true;
			}


		}
		count++;
		cout << "Iteration " << count << "----------------------------------------"<< endl;
		print_match(Man);

	}
}

void print_match(Person* Man)
{
	for(int i = 0; i < SIZE; ++i)
		if(Man[i].engaged) cout << "Man : " << Man[i].id << ", Woman : " << Man[i].pid << endl;
}

int main(int argc, char** argv){

	Person Man[SIZE] = 
		{
		{0,-1,false,{0, 1, 2},{false, false, false}}, 
		{1,-1,false,{0, 1, 2},{false, false, false}}, 
		{2,-1,false,{0, 1, 2},{false, false, false}}
		};

	Person Woman[SIZE] = 
		{
		{0,-1,false,{2, 1, 0},{false, false, false}}, 
		{1,-1,false,{2, 1, 0},{false, false, false}}, 
		{2,-1,false,{2, 1, 0},{false, false, false}}
		};

	stable_match(Man, Woman);
	//print_match(Man);

	return 0;
}
