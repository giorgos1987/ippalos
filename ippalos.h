#include <conio.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>

// Global variables:

int day, hr;
FILE *fp;


// Class definitions:

class Station {

private:

	char name[21];
	int temp, hum, wind, sunl;
	int hasTemp, hasHum, hasWind, hasSunl;

public:

	Station(char *n, int t, int h, int w, int s);
	void genData();

};

class Measurement {

public:

	char name[21];
	int mday, mhr, temp, hum, wind, sunl;

	Measurement(char *str);
	Measurement(const Measurement &m);

};

class ListNode {

public:

	Measurement *data;
	ListNode *nextNode;

	ListNode(Measurement *m);
	ListNode(Measurement *m, ListNode *n);
	
};

class List {

private:

	ListNode *firstNode, *lastNode;
	int elements;

public:

	List();
	void insertAtBack(Measurement *m);
	Measurement removeFromFront();
	int isEmpty();
	int getElements();

};

class MainSystem {

public:

	void startMeasurements();
	void getMeanTempAndHum();
	void getExtrTemps();
	void getExtrSunl();
	void sortSunl();
	void bubbleSort(Measurement a[], int n);
	void heapSort (Measurement a[], int n);

};



