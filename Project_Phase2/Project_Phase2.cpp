#include <iostream>
#include <iomanip>
#include <fstream>
#include <conio.h>
#include <cfloat>

using namespace std;

#define INF 99999

const int totalRows = 12;
const int V=totalRows;

// A function to print the solution matrix
void printSolution(double dist[][V]);

void floydWarshall(double graph[][V],int choice)
{
	double dist[V][V];
	int i, j, k;

	for (i = 0; i < V; i++)
		for (j = 0; j < V; j++)
			dist[i][j] = graph[i][j];

	for (k = 0; k < V; k++) {

 		for (i = 0; i < V; i++) {

			for (j = 0; j < V; j++) {
				if (dist[i][j] > (dist[i][k] + dist[k][j])&& (dist[k][j] != INF && dist[i][k] != INF))
					dist[i][j] = dist[i][k] + dist[k][j];
			}
		}
	}
	
	int sourceNode;
	
	if(choice == 1){

		cout<<"Enter a source node for shortest path (1 - "<<totalRows-1<<") : ";
		cin>>sourceNode;
	
		for (int i = sourceNode; i < sourceNode+1 ; i++) {
			cout<<"\nShortest distances : \n\n";
			for (int j = 0; j < V; j++){
				if(i==j){
					continue;
				}	
				cout<<"	To node "<<sourceNode<<" from node "<<j<<" : ";
				if (dist[i][j] == INF){
					cout << "No path exists"<<"  ";
					cout<<endl;
					continue;
				}
				cout<<dist[i][j]<<"  ";
				cout<<endl;
			}
		}		
		cout<<"\n\n";						
	}	
	
	if(choice == 2){	
		printSolution(dist);
	}
}

void printSolution(double dist[][V])
{
	cout << "						MST Graph Matrix \n\n\n\n";
	for (int i = 0; i < V; i++) {
		cout<<"		";
		for (int j = 0; j < V; j++) {
			if (dist[i][j] == INF)
				cout << "INF"
					<< "	 ";
			else
				cout << dist[i][j] << "	 ";
		}
		cout << endl;
	}
}

int getIndex(string wordsArray[], string word, int size)
{
	for (int i = 0; i < size; i++)
	{
		if (word == wordsArray[i])
		{
			return i;
		}
	}
}


int main(){

	double weightMatrix[totalRows][totalRows];
	// adding data from file
	ifstream dataFile("Project_PPI.txt");

	string protienOne, protienTwo;
	double weight;

	int WordsInArray = 0;
	string* wordsArray = new string[WordsInArray];
	string* tempWordsArray = new string[WordsInArray];

	double* weightArray = new double[totalRows];

	bool skipWord = false;

	// stores source
	string* columnOne = new string[totalRows];
	// stores destinations
	string* columnTwo = new string[totalRows];

	for (int i = 0; i < totalRows; i++)
	{
		dataFile >> protienOne >> protienTwo >> weight;

		// storing sources and destinations in columns
		columnOne[i] = protienOne;
		columnTwo[i] = protienTwo;

		// check if proteinOne is repeated
		for (int j = 0; j < WordsInArray; j++)
		{
			if (protienOne == wordsArray[j])
			{
				skipWord = true;
				break;
			}
		}

		if (skipWord == false)
		{
			// temp array
			tempWordsArray = new string[++WordsInArray];

			// transfer original to temp
			for (int j = 0; j < (WordsInArray - 1); j++)
			{
				tempWordsArray[j] = wordsArray[j];
			}
			tempWordsArray[WordsInArray - 1] = protienOne;

			// re create oigina/
			wordsArray = new string[WordsInArray];

			// transfer temp to original
			for (int j = 0; j < WordsInArray; j++)
			{
				wordsArray[j] = tempWordsArray[j];
			}
		}

		skipWord = false;
		// check if proteinTwo is repeated
		for (int j = 0; j < WordsInArray; j++)
		{
			if (protienTwo == wordsArray[j])
			{
				skipWord = true;
				break;
			}
		}

		if (skipWord == false)
		{
			// temp array
			tempWordsArray = new string[++WordsInArray];

			// transfer original to temp
			for (int j = 0; j < (WordsInArray - 1); j++)
			{
				tempWordsArray[j] = wordsArray[j];
			}
			tempWordsArray[WordsInArray - 1] = protienTwo;

			// re create oigina/
			wordsArray = new string[WordsInArray];

			// transfer temp to original
			for (int j = 0; j < WordsInArray; j++)
			{
				wordsArray[j] = tempWordsArray[j];
			}
		}

		skipWord = false;
		// transfer weights to array
		weightArray[i] = weight;

	}
	int srcIndex, destIndex;

	for(int i=0; i < totalRows; i++){
		for(int j=0; j < totalRows; j++){
			weightMatrix[i][j]=INF;
			if(i==j){
			weightMatrix[i][j]=0;				
			}
		}
	}
			
	for (int i = 0; i < totalRows-1; i++)
	{
		srcIndex = getIndex(wordsArray, columnOne[i], WordsInArray);
		destIndex = getIndex(wordsArray, columnTwo[i], WordsInArray);
		weightMatrix[srcIndex][destIndex]=weightArray[i];
		weightMatrix[destIndex][srcIndex]=weightArray[i];
	}
	
	int choice;
	while(1){
		cout<<"Select from the following : "<<endl
			<<"1.Show shortest path of all nodes from desired source node."<<endl
			<<"2.Print MST graph matrix."<<endl
			<<"3.Exit."<<endl
			<<"Your choice : ";
		cin>>choice;
		cout<<endl<<endl;
		
		switch(choice){
			
			case 1:
				floydWarshall(weightMatrix,1);								
				break;

			case 2:
				floydWarshall(weightMatrix,2);								
				break;
						
			case 3:
				exit(0);
				break;

			default:
				break;
		}
		cout<<"\n\n\n\n";			
}

	return 0;
}
