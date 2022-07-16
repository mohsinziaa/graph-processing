/*

NAME:						REG NO:

Muhammad Abdullah			2020256
Mohsin Zia					2020244
Irtaza Haider				2020474
Zartaj Asim					2020526

*/

#include "SDL.h"
#undef main

#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

struct adjListNode {
	double weight;
	int data;

	float pos_x, pos_y;

	adjListNode* next;
};

struct adjList {
	adjListNode* head;
};

struct graph {
	int vertices;
	adjList* array;
};

// total rows added from file
const int totalRows = 500;

adjListNode* newAdjListNode(int data, double weight) {

	adjListNode* newNode = new adjListNode;
	newNode->data = data;
	newNode->weight = weight;
	newNode->next = NULL;

	return newNode;
}

graph* createGraph(int v) {

	graph* newGraph = new graph;
	newGraph->vertices = v;
	newGraph->array = new adjList[v];

	for (int i = 0; i < v; i++) {
		newGraph->array[i].head = NULL;
	}

	return newGraph;
}

void addEdge(graph* grp, int source, int destination, double weight, int vertArr[][totalRows]) {

	vertArr[source][destination] = 1;

	adjListNode* newNode = newAdjListNode(destination, weight);

	newNode->next = grp->array[source].head;
	grp->array[source].head = newNode;
}

void displayAdjMatrix(int vertices, int vertArr[][totalRows]) {

	for (int i = 0; i < vertices; i++) {

		cout << "			";

		for (int j = 0; j < vertices; j++) {
			cout << vertArr[i][j] << "  ";
		}

		cout << endl;
	}

}

void printGraph(graph* grp, string wordsArray[], double weightArr[], int wordsInArray) {

	for (int i = 0; i < wordsInArray - 1; i++) {

		adjListNode* start = grp->array[i].head;

		cout << endl << wordsArray[i] << " : ";

		while (start != NULL) {	
			cout << wordsArray[start->data];
			start = start->next;
			cout << " -> ";
			if (start == NULL) {
				cout << "NULL";
			}
		}
		cout << endl;
	}
}

void findDegree(graph* grp, string wordsArray[], int vertices) {

	int choice;
	cout << "Select a node of which you want to find degree : " << endl;
	for (int i = 0; i < vertices-1; i++) {
		cout << i + 1 << ". " << wordsArray[i] << endl;
	}

	cout << "\nSelect a node: ";
	cin >> choice;

	adjListNode* start = grp->array[choice - 1].head;
	int count = 0;

	while (start != NULL) {
		count++;
		start = start->next;
	}
	cout << endl << "Degree of " << wordsArray[choice - 1] << " is : " << count << endl;
}

void findMaxDegree(graph* grp, string wordsArray[], int vertices, int vertArray[][totalRows]) {

	int* count = new int[vertices];

	for (int i = 0; i < vertices; i++)
	{
		count[i] = 0;
	}

	for (int i = 0; i < vertices; i++) {
		for (int j = 0; j < vertices; j++) {
			if (vertArray[i][j] == 1) {
				count[i]++;
			}
		}
	}

	int maxNode = 0;

	for (int i = 0; i < vertices; i++) {
		if (maxNode < count[i]) {
			maxNode = count[i];
		}
	}

	for (int i = 0; i < vertices; i++) {
		if (count[i] == maxNode) {
			cout << endl << "Node with maximum degree is : " << wordsArray[i] << " with degree " << maxNode << endl;
		}
	}

}

void findMinDegree(graph* grp, string wordsArray[], int vertices, int vertArray[][totalRows]) {

	int* count = new int[vertices];

	for (int i = 0; i < vertices; i++)
	{
		count[i] = 0;
	}

	for (int i = 0; i < vertices; i++) {
		for (int j = 0; j < vertices; j++) {
			if (vertArray[i][j] == 1) {
				count[i]++;
			}
		}
	}

	int minNode = 100;

	for (int i = 0; i < vertices; i++) {
		if (minNode > count[i]) {
			minNode = count[i];
		}
	}

	cout << endl << "Node with minimum degree is : " << endl;
	for (int i = 0; i < vertices; i++) {
		if (count[i] == minNode) {
			cout << wordsArray[i] << " with degree " << minNode << endl;
		}
	}

}

void findNeighbours(graph* grp, string wordsArray[], int vertices) {

	int choice;
	cout << "Select a node of which you want to find neighbours : " << endl;
	for (int i = 0; i < vertices-1 ; i++) {
		cout << i + 1 << ". " << wordsArray[i] << endl;
	}

	cout << "\nSelect a node: ";
	cin >> choice;

	cout << endl << endl << "Neighbours of " << wordsArray[choice - 1] << " : ";

	adjListNode* start = grp->array[choice - 1].head;

	while (true) {
		cout << wordsArray[start->data];
		start = start->next;
		if (start == NULL) {
			return;
		}
		cout << " -> ";
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

	return 0;
}

void drawGraph(graph* grp, string wordsArray[], int wordsInArray)
{
	wordsInArray--;

	// give values to x and y of nodes
	float theta = 0;			// theta is in radians
	float radius = 80;
	float pi = 3.14159;

	float increaseTheta = 0.0174533 * 6;	
	
	for (int i = 0; i < wordsInArray; i++)
	{
		adjListNode* start = grp->array[i].head;
		
		start->pos_x = radius * cos(theta);
		start->pos_y = radius * sin(theta);

		theta = theta + increaseTheta;	// increase in radian

		if (theta + 0.0174533 >= 2 * pi)
		{
			theta = 0;
			radius = radius + 20;
		}

	}

	// window datatype
	SDL_Window* window;
	// renderer datatype
	SDL_Renderer* renderer;

	// initilialize SDL2

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		cout << "Window could not be initialized. Error Code: " << SDL_GetError();
	}
	else
	{
		cout << "Displaying Graph on seperate window:";
		cout << "\nClose the graph window to continue\n";
	}

	//create window
	window = SDL_CreateWindow("Graph", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 800, 0);
	//create renderer
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	// loop for displaying graph infinitely until window closed
	bool displayingGraph = true;

	while (displayingGraph)
	{
		// creating event for handling 'quiting' 
		SDL_Event event;

		// (1). Handle Input

		// event loop
		while (SDL_PollEvent(&event))
		{
			// to handle specific 'QUIT' event
			if (event.type == SDL_QUIT)
			{
				displayingGraph = false;
			}
		}

		// (2). Handle Updates

		// (3). Clear and draw the screen

		// SDL_RenderClear(renderer) gives an empty canvas
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);  // set canvas color
		SDL_RenderClear(renderer);

		// drawing
		SDL_SetRenderDrawColor(renderer, 78, 204, 207, SDL_ALPHA_OPAQUE);  // set line color

		float x_correction = 400, y_correction = 400;

		for (int i = 0; i < wordsInArray; i++)
		{
			adjListNode* start = grp->array[i].head;

			SDL_RenderDrawPointF(renderer, start->pos_x + x_correction, start->pos_y + y_correction);
			
			float x1, y1;

			adjListNode* temp = start;
			
			//start = start->next;

			
			while (start->next != NULL)
			{
				SDL_RenderDrawLineF(renderer, temp->pos_x + x_correction, temp->pos_y + x_correction, grp->array[start->next->data].head->pos_x + x_correction, grp->array[start->next->data].head->pos_y + x_correction);

				start = start->next;
			}
			
		}

		// shows what we have drawn on canvas
		SDL_RenderPresent(renderer);

	}


	// close and destroy window
	SDL_DestroyWindow(window);

	// clean up
	SDL_Quit();

}

int main() {


	// adding data from file
	ifstream dataFile("PPI-I.txt");

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

	// 50 - 1 = 49
	int totalVertices = totalRows - 1;
	graph* crtGraph = new graph;
	crtGraph = createGraph(totalVertices);

	int vertArr[totalRows][totalRows];

	int srcIndex, destIndex;

	for (int i = 0; i < totalRows; i++) {
		for (int j = 0; j < totalRows; j++) {
			vertArr[i][j] = 0;
		}
	}

	for (int i = 0; i < totalRows - 1; i++)
	{

		srcIndex = getIndex(wordsArray, columnOne[i], WordsInArray);
		destIndex = getIndex(wordsArray, columnTwo[i], WordsInArray);

		addEdge(crtGraph, srcIndex, destIndex, weightArray[i], vertArr);

		addEdge(crtGraph, destIndex, srcIndex, weightArray[i], vertArr);

	}

	adjListNode* start = crtGraph->array[WordsInArray - 2].head;
	start->next = NULL;

	int choice;
	int tempWord;
	while (1) {
		cout << "\n\nSelect from the following : " << endl << endl
			<< "(1). Print the graph." << endl
			<< "(2). Find neighbours of desired node." << endl
			<< "(3). Find degree of desired node." << endl
			<< "(4). Find node/nodes with maximum degree." << endl
			<< "(5). Find node/nodes with minimum degree." << endl
			<< "(6). Display adjacency matrix." << endl
			<< "(7). Display Graph" << endl
			<< "(8). Exit." << endl
			<< "\n  ";

			cout << "\nSelect (1-8) : ";
			cin >> choice;

			cout << endl << endl;

		switch (choice) {

		case 1:
			printGraph(crtGraph, wordsArray, weightArray, WordsInArray);
			break;

		case 2:
			findNeighbours(crtGraph, wordsArray, WordsInArray);
			break;

		case 3:
			findDegree(crtGraph, wordsArray, WordsInArray);
			break;

		case 4:
			findMaxDegree(crtGraph, wordsArray, totalRows, vertArr);
			break;

		case 5:

			tempWord = WordsInArray;
			if (WordsInArray >= totalRows) {
				tempWord = totalRows;
			}

			findMinDegree(crtGraph, wordsArray, tempWord-1, vertArr);
			break;

		case 6:
			displayAdjMatrix(totalRows - 1, vertArr);
			break;

		case 7:

			drawGraph(crtGraph, wordsArray, WordsInArray);
			break;

		case 8:

			exit(0);
			break;

		default:
			break;
		}
		cout << "\n\n\n\n";
	}


	return 0;
}
