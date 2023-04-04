#include <iostream>
using namespace std;


int remainingBurstColumn = 2;
int burstTimeColumn = 1;
int processIDColumn = 0;
int arrColumn = 3;

int Quantum = 2;

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
			processList[i] = new int[4];
		
		for(int i = 0; i < processCount; i++) {
			for(int j = 0; j < 4; j++) {
				processList[i][j] = 0;
			   
            }
		   
         }
		
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

	cout << "Enter the Total Number of Process: ";
	int numberProcess;
  	cin >> numberProcess;
  	
	process p(numberProcess);
	
	userPrompt(p);
	waitTime(p);
	turnTime(p);
	print(p); 
	avgWaitAndTurnTime(p); 
   
   }

void userPrompt(process p) {
	int burstTime;
	int arrTime;
	int processID;
	for(int i = 0; i < p.numberProcess; ++i) {
		processID = i + 1;
		cout << "Enter Burst Time for Process " << processID << ":  "; 
		cin >> burstTime;
		cout << "Enter Arrival Time of Process " << processID << ": ";
		cin >> arrTime;
		p.processList[i][processIDColumn] = processID;
		p.processList[i][burstTimeColumn] = burstTime;
		p.processList[i][remainingBurstColumn]= burstTime; 
		p.processList[i][arrColumn] = arrTime;
	
   }  

}

void print(process p) {
      for (int i = 0; i < p.numberProcess; ++i) {
        cout << "\nProcess ID: " << p.processList[i][0]
          << " | Burst Time: " << p.processList[i][burstTimeColumn]
          << " | Waiting Time: " << p.waitTime[i]
          << " | Turnaround Time: "<< p.turnTime[i]
          << " | Completion Time: "<< p.compTime[i];
      
        }
      
      }

void waitTime(process p) {
	int currentTime = 0;
	int arrTime = 0;
	while(true){
		bool done = true;
		for(int i = 0; i<p.numberProcess; i++) {
			if(p.processList[i][2] > 0) {
 
                done = false; 
                if(p.processList[i][2] > Quantum && p.processList[i][3] <= arrTime) { 
                    currentTime += Quantum; 
                    p.processList[i][2] -= Quantum; 
                    arrTime++; 
                
                } 
                
                else { 
                
                    if(p.processList[i][3]<=arrTime) { 
                        arrTime++; 
                        currentTime += p.processList[i][2]; 
                        p.processList[i][2] = currentTime - p.processList[i][1]; 
                        p.processList[i][2] = 0; 
                        p.compTime[i] = currentTime; 
					      
                    } 
               
               } 				
			
          }
		
      }
		
      if (done == true) {
			break;
		
         }
	
      }

   }
	
void turnTime(process p) { 
    for(int i = 0; i < p.numberProcess; i++) { 
        p.turnTime[i]= p.compTime[i] - p.processList[i][3]; 
        p.waitTime[i] = p.turnTime[i] - p.processList[i][1];       
    
    }

}

void avgWaitAndTurnTime(process p) {
	int totalWaitTime = 0;
	int totalTurnTime = 0;
	
	for(int i = 0; i < p.numberProcess; i++) {
		totalWaitTime += p.waitTime[i];
		totalTurnTime += p.turnTime[i];
	
      }
	
	int avgWait = (float)totalWaitTime / (float)p.numberProcess; 
	int avgTurn = (float)totalTurnTime / (float)p.numberProcess; 
	cout << "\n\nAverage Waiting Time = " << avgWait << endl;
	cout << "Average Turnaround Time =  " << avgTurn << endl;

   }