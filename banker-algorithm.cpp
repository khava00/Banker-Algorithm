#include<bits/stdc++.h>
using namespace std;
void Banker();
void init();
int Allocation[10][10], Need[10][10], Max[10][10], Available[1][10], Safety[10];
int p, current[10], m, d = 0;
bool executed[10], come;
void res_request(int A[10][10], int N[10][10], int AV[1][10], int pr, int m);
bool check(int index, int N[10][10], int curr[10]);
int main (){
	int keepon = 1, pr;
	char tmp;
	cout << "Enter total no. of processes: ";
	cin >> p;
	cout << "\nEnter total no. of resources: ";
	cin >> m;
	cout << "\nAvailable resources: ";
	for(int i = 0; i < m; ++i) {
		cin >> current[i];
	}
	for (int i = 0; i < p; ++i)
	{
		cout << "\n\nProcess P" << i + 1 << "\n";
		int tmp = 0;
		cout << "Enter Allocation: ";
		while (tmp < m) {
			cin >> Allocation[i][tmp++];
		}
		tmp = 0;
		cout << "\nEnter Max: ";
		while (tmp < m) {
			cin >> Max[i][tmp];
			Need[i][tmp] = Max[i][tmp] - Allocation[i][tmp];
			tmp++;
		}
	}
	cout << "\n\nAvailable: ";
	for(int i = 0; i < m; ++i){
		Available[0][i] = current[i];
		cout << current[i] << " ";
	}
	cout<<"\n\nProcess    \tMax    \tAllocation    \tNeed\n";
	for (int i = 0; i < p; ++i)
	{
		cout << "  P" << i + 1 << "    ";
		for(int j = 0; j < m; ++j)
			cout << "  " << Max[i][j] << "  ";
		for(int j = 0; j < m; ++j)	
			cout << "  " << Allocation[i][j] << "  ";
		for(int j = 0; j < m; ++j)
			cout << "  " << Need[i][j] << "  ";
		cout << "\n";
	}
	cout<<"\n\n";
	Banker();
	while(keepon){
		cout << "\nDo you want to add request? (Y = Yes | N = No)" << endl;
		cin >> tmp;
		if (tmp == 'Y' || tmp == 'y') {
			cout << "Enter process No: ";
			cin >> pr;
			res_request(Allocation, Need, Available, pr - 1, m);
			for(int i = 0; i < m; ++i){
				current[i] = Available[0][i];
			}
			cout<<"\n\nProcess    \tMax    \tAllocation    \tNeed\n";
			for (int i = 0; i < p; ++i)
			{
				cout<< "  P" << i + 1 << "    ";
				for(int j = 0; j < m; ++j)
					cout << "  " << Max[i][j] << "  ";
				for(int j = 0; j < m; ++j)	
					cout << "  " << Allocation[i][j] << "  ";
				for(int j = 0; j < m; ++j)
					cout << "  " << Need[i][j] << "  ";
				cout << "\n";			
			}
			cout << "\n\n";
	
			Banker();
		} else {
			break;
		}
	
	}
	return 0;
}

void Banker(){
	init();
	int i,j;
	for (i = 0; i < p; ++i)
	{	
		for (j = 0; j < p; ++j)
		{
			while(executed[j] && j < p - 1){
				j++;
			}
			
			if (check(j, Need, current))
			{
				if (!executed[j])
				{
					executed[j] = true;
					Safety[d] = j;
					d++; 
					for(int k = 0; k < m; k++)
						current[k] += Allocation[j][k];
					cout << "\nProcess P" << j + 1;
					cout << "\nCurrent: ";
					for(int k = 0; k < m; k++)
						cout << current[k] << " ";
					cout << "\nProcess executed without deadlock";
					come = true;
					break;
				}
			}
		}
		if (!come) {	
			cout << "\n\t\t\tDead lock\n\n";
			d = 0;
			break;
		} else {
			come = false;
		}
	}
	if (d != 0){
		cout << "\nA safety sequence has been detected: ";
		for(int i = 0; i < d; ++i){
			if (i < d - 1)
				cout << "P" << Safety[i] + 1 << " -> ";
			else
				cout << "P" << Safety[i] + 1;
		}
		
	}
}
bool check(int index, int N[10][10], int curr[10]){
	for(int i = 0; i < m; ++i){
		if (Need[index][i] > curr[i])
			return false;
	}
	return true;
}
void res_request(int A[10][10], int N[10][10], int AV[1][10], int pr, int m){
		int req[1][10];
		int i;
		cout << "Enter request: ";
		for(int i = 0; i < m; ++i)
			cin >> req[0][i];		
		for(i = 0; i < m; i++)
			if(req[0][i] > N[pr][i]){
				cout << "\nError encountered.\n";
				exit(0);
		}
	
		for(i = 0; i < m; i++)
			if(req[0][i] > AV[0][i]){
				cout << "\nResources unavailable.\n";
				exit(0);
			}
		
		for(i = 0; i < m; i++){
			AV[0][i] -= req[0][i];
			A[pr][i] += req[0][i];
			N[pr][i] -= req[0][i];
		}
	}
void init(){
	come = false;
	d = 0;
	for (int i = 0; i < 10; ++i)
	{
		executed[i] = false;
	}
}
