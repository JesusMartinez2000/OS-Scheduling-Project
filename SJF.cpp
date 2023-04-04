#include <iostream>
using namespace std;


int burstTimeColumn = 1;
int pIDColumn = 0;
int arrTimeColumn = 2;

int timeSlice = 2;

struct process {
	int numberProcess; 
	int** processList;
	int* waitTime;
	int* compTime; 
	int* turnTime; 
	
	process(int processCount) { 
   
		numberProcess = processCount;
       
    	processList = new int* [processCount];
		for (int i = 0; i < processCount; i++)
			processList[i] = new int[3];
		
		for(int i = 0; i < processCount; i++){
			for(int j = 0; j < 3; j++){
				processList[i][j] = 0;
			
         }
		
      }
		
    	waitTime = new int [processCount];
    	turnTime = new int [processCount];
    	compTime = new int [processCount];
	
   }

};

void sortingProcesses(process p);
void userPrompt(process p); 
void print(process p);
void waitTime(process p);
void compTime(process p);
void turnTime(process p);
void avgWaitAndTurnTime(process p); 

int main() {

	cout << "Enter the total number of processes: ";
	int numberProcess;
  	cin >> numberProcess;
  	
	process p(numberProcess);
	
	userPrompt(p); 
	sortingProcesses(p);
	compTime(p); 
	turnTime(p);
	waitTime(p); 
	print(p); 
	avgWaitAndTurnTime(p); 
		
   return 0;

   }
   
void userPrompt(process p) {
	int burstTime;
	int arrTime;
	int pID;
	for(int i = 0; i < p.numberProcess; ++i) {
		pID = i + 1;
		cout << "Enter Burst time for Process" << pID << " :"; 
		cin >> burstTime;
		cout << "Enter Arrival Time of Process" << pID << " :";
		cin >> arrTime;
		p.processList[i][pIDColumn] = pID;
		p.processList[i][burstTimeColumn] = burstTime; 
		p.processList[i][arrTimeColumn] = arrTime;
	
   }  

}

void sortingProcesses(process p) {
	int temp = 0, burst = 0, arr = 0;
	for(int i = 0;i < p.numberProcess; i++) {
		for(int j = i + 1; j < p.numberProcess; j++) {
			if(p.processList[j][2] < p.processList[i][2]) {
				arr=p.processList[i][2];
				p.processList[i][2] = p.processList[j][2];
				p.processList[j][2] = arr;
				temp = p.processList[i][0];
				p.processList[i][0] = p.processList[j][0];
				p.processList[j][0] = temp;

				burst = p.processList[i][1];
				p.processList[i][1] = p.processList[j][1];
				p.processList[j][1] = burst;
			
         }
		
      }
	
   }
   
	for(int i = 1; i < p.numberProcess-1; i++) {
		if(p.processList[i][1] > p.processList[i+1][1]) {
			arr = p.processList[i][2];
			p.processList[i][2] = p.processList[i+1][2];
			p.processList[i+1][2] = arr;
				temp = p.processList[i][0];
				p.processList[i][0] = p.processList[i+1][0];
				p.processList[i+1][0] = temp;
				burst = p.processList[i][1];
				p.processList[i][1] = p.processList[i+1][1];
				p.processList[i+1][1] = burst;
		
      }
	
   }

}

void waitTime(process p) {
	for(int i = 0;i < p.numberProcess; i++) {
		int time = p.turnTime[i] - p.processList[i][1];
		if(time >= 0) {
			p.waitTime[i] = time;
		
      }
		
      else
			p.waitTime[i]=0;
	
         }
   }

void turnTime(process p) {
	for(int i = 0; i < p.numberProcess; i++) {
		p.turnTime[i] = p.compTime[i] - p.processList[i][2];
	
      }

   }

void compTime(process p) {
	p.compTime[0] = p.processList[0][1];
	for(int i = 1; i < p.numberProcess; i++) {
		p.compTime[i] = p.processList[i][1] + p.compTime[i-1];
	
      }

   }

void avgWaitAndTurnTime(process p) {
	int totalWaitTime = 0;
	int totalTurnTime = 0;
	
	for(int i = 0; i<p.numberProcess; i++) {
		totalWaitTime += p.waitTime[i];
		totalTurnTime += p.turnTime[i];
	   
      }
	
	int avgWait = (float)totalWaitTime / (float)p.numberProcess; 
	int avgTurn = (float)totalTurnTime / (float)p.numberProcess; 
	cout << "\n\nAverage Waiting Time = " << avgWait <<endl;
	cout << "Average Turnaround Time =  " << avgTurn <<endl;

   }
   
void print(process p) {
   for (int i = 0; i < p.numberProcess; ++i) {
        cout << "\nProcess: " << p.processList[i][0]
          << " | Burst Time: " << p.processList[i][burstTimeColumn]
          << " | Waiting Time: " << p.waitTime[i]
          << " | Turnaround Time: "<< p.turnTime[i]
          << " | Completion Time: "<< p.compTime[i];
     
         }
         
   }
