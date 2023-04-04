#include <iostream>
using namespace std;

struct process {
	int numberProcess;
	int* processList;
	int* burstTime;
	int* arrTime;
	int* waitTime;
	int* compTime;
	int* turnTime;
	
	process(int processCount) {
		numberProcess = processCount;
    	processList = new int [processCount];
    	burstTime = new int [processCount];
    	arrTime = new int [processCount];
    	waitTime = new int [processCount];
    	turnTime = new int [processCount];
    	compTime = new int [processCount];
	   
      }
   };

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
	compTime(p);
	turnTime(p);
	waitTime(p);
	print(p);
	avgWaitAndTurnTime(p);

   }

void userPrompt(process p) {
	
	for(int i = 0; i < p.numberProcess; ++i) {
		p.processList[i] = i + 1;
		cout << "Enter Burst Time for Process " << i + 1 << " :";
		int burstTime;
		cin >> burstTime;
		p.burstTime[i] = burstTime;
		cout << "Enter Arrival Time for Process " << i + 1 << "	:";
		int arrTime;
      cin >> arrTime;
		p.arrTime[i] = arrTime;
	
   } 

}

void print(process p) {
      for (int i = 0; i < p.numberProcess; ++i) {
        cout << "\nProcess: " << p.processList[i]
          << " | Burst Time: " << p.burstTime[i]
          << " | Waiting Time: " << p.waitTime[i]
          << " | Turnaround Time: " << p.turnTime[i]
          << " | Completion Time: " << p.compTime[i];
      
      }

}

void waitTime(process p) {
	p.waitTime[0] = 0; 
	for (int i = 1; i < p.numberProcess; i++ ) {
		p.waitTime[i] = p.turnTime[i] - p.burstTime[i];
	
   }

}

void compTime(process p) {
    p.compTime[0] = p.burstTime[0];
    for(int i = 1; i < p.numberProcess; i++) {
         p.compTime[i] = p.compTime[i - 1] + p.burstTime[i];
    
         }
   }
	
void turnTime(struct process p) { 
	for (int i = 0; i < p.numberProcess; i++) {
		p.turnTime[i] = p.compTime[i]-p.arrTime[i];}
      
      }

void avgWaitAndTurnTime(process p) {
	int totalWaitTime = 0;
	int totalTurnTime=0;
	
	for(int i = 0; i<p.numberProcess; i++) {
		totalWaitTime += p.waitTime[i];
		totalTurnTime += p.turnTime[i];
	
      }
	
	int avgWait = (float)totalWaitTime / (float)p.numberProcess; 
	int avgTurn = (float)totalTurnTime / (float)p.numberProcess; 
	cout << "\n\nAverage Waiting time = " << avgWait << endl;
	cout << "Average Turnaround time =  " << avgTurn << endl;

   }