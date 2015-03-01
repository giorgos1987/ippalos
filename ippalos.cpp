#include "ippalos.h"

Station::Station(char *n, int t, int h, int w, int s) {

	strcpy(name, n);
	hasTemp = t;
	hasHum = h;
	hasWind = w;
	hasSunl = s;

}

void Station::genData() {

	printf("Day %d\n", day);
	printf("%2d:00\n", hr);
	printf("%s\n", name);

	if(hasTemp) {
		
		temp = (rand() % 51) - 10;
		printf("T = %d deg C\n", temp);

	}

	else temp = 255;

	if(hasHum) {
		
		hum = rand() % 101;
		printf("H = %d %%\n", hum);

	}

	else hum = 255;
				
	if(hasWind) {
		
		wind = rand() % 11;
		printf("W = %d Bf\n", wind);

	}

	else wind = 255;
		
	if(hasSunl) {

		if(hr < 7 || hr > 19) sunl = -1;
		else sunl = rand() % 11;

		printf("S = %d\n", sunl);
		
	}
	
	else sunl = 255;

	printf("\n");
	fprintf(fp, "%-20s %1d %2d %3d %3d %3d %3d\n", name, day, hr, temp, hum, wind, sunl);

}

Measurement::Measurement(char *str) {

	char md[2], mh[3], t[4], h[4], w[4], s[4];
	strncpy(name, str, 20);
	name[20] = '\0';
	strncpy(md, str + 21, 1);
	md[1] = '\0';
	strncpy(mh, str + 23, 2);
	mh[2] = '\0';
	strncpy(t, str + 26, 3);
	t[3] = '\0';
	strncpy(h, str + 30, 3);
	h[3] = '\0';
	strncpy(w, str + 34, 3);
	w[3] = '\0';
	strncpy(s, str + 38, 3);
	s[3] = '\0';

	mday = atoi(md);
	mhr = atoi(mh);
	temp = atoi(t);
	hum = atoi(h);
	wind = atoi(w);
	sunl = atoi(s);

}

Measurement::Measurement(const Measurement &m) {

	strcpy(name, m.name);
	mday = m.mday;
	mhr = m.mhr;
	temp = m.temp;
	hum = m.hum;
	wind = m.wind;
	sunl = m.sunl;

}

ListNode::ListNode(Measurement *m) {

	data = m;
	nextNode = 0;

}

ListNode::ListNode(Measurement *m, ListNode *n) {

	data = m;
	nextNode = n;

}

List::List() {

	firstNode = lastNode = 0;
	elements = 0;

}

void List::insertAtBack(Measurement *m) {

	if(isEmpty()) firstNode = lastNode = new ListNode(m);
	else lastNode = lastNode->nextNode = new ListNode(m);

	elements++;

}

Measurement List::removeFromFront() {

	Measurement *removedItem = firstNode->data;

	if(firstNode == lastNode) firstNode = lastNode = 0;
	else firstNode = firstNode->nextNode;
	elements--;

	return *removedItem;

}

int List::isEmpty() {

	if(firstNode == 0) return 1;
	else return 0;

}

int List::getElements() {

	return elements;

}

void MainSystem::startMeasurements() {

	Station s1("RHODES", 1, 1, 1, 1);
	Station s2("IOANNINA", 1, 0, 0, 1);
	Station s3("ALEXANDROUPOLI", 1, 1, 0, 1);
	Station s4("CHANIA", 1, 1, 1, 1);
	Station s5("KITHIRA", 1, 1, 1, 1);

	fp = fopen("measurements.dat", "w");

	for(day = 1; day < 6; day++) {

		for(hr = 0; hr < 24; hr++) {

			s1.genData();
			s2.genData();
			s3.genData();
			s4.genData();
			s5.genData();

			Sleep(1000);

		}

	}

	fclose(fp);

}

void MainSystem::getMeanTempAndHum() {

	fp=fopen("measurements.dat", "r");
	char instr[80];
	
	List l1;
	List l2;
	List l3;
	List l4;
	List l5;
	
	while(!feof(fp)){
		
		fgets(instr,80,fp);
		if(strstr(instr,"RHODES")) l1.insertAtBack(new Measurement(instr));
		if(strstr(instr,"IOANNINA")) l2.insertAtBack(new Measurement(instr));
		if(strstr(instr,"ALEXANDROUPOLI")) l3.insertAtBack(new Measurement(instr));
		if(strstr(instr,"CHANIA")) l4.insertAtBack(new Measurement(instr));
		if(strstr(instr,"KITHIRA")) l5.insertAtBack(new Measurement(instr));
	
	}
	
	fclose(fp);

	int n1=l1.getElements();
	int n2=l2.getElements();
	int n3=l3.getElements();
	int n4=l4.getElements();
	int n5=l5.getElements();

	Measurement *a1, *a2, *a3, *a4, *a5;

	a1 = (Measurement *) malloc(sizeof(Measurement) * n1);
	a2 = (Measurement *) malloc(sizeof(Measurement) * n2);
	a3 = (Measurement *) malloc(sizeof(Measurement) * n3);
	a4 = (Measurement *) malloc(sizeof(Measurement) * n4);
	a5 = (Measurement *) malloc(sizeof(Measurement) * n5);

	
	for(int i = 0; i < n1; i++) {
		
		a1[i] = l1.removeFromFront();

	}

	for(i = 0; i < n2; i++) {
		
		a2[i] = l2.removeFromFront();

	}
	
	for(i = 0; i < n3; i++) {
		
		a3[i] = l3.removeFromFront();

	}

	for(i = 0; i < n4; i++) {
		
		a4[i] = l4.removeFromFront();

	}

	for(i = 0; i < n5; i++) {
		
		a5[i] = l5.removeFromFront();

	}

	int sum1 = 0, sum2 = 0;

	printf("\n%20s\t", a1[0].name);
	
	for(i = 0; i < n1; i++) {

		if(a1[0].temp != 255) sum1 = sum1 + a1[i].temp;
		if(a1[0].hum != 255) sum2 = sum2 + a1[i].hum;

	}

	if(a1[0].temp != 255) printf("Tm = %.2f deg C\t", ((float) sum1) / ((float) n1));
	if(a1[0].hum != 255) printf("Hm = %.2f %%", ((float) sum2 / (float) n1));
	printf("\n");

	sum1 = sum2 = 0;

	printf("\n%20s\t", a2[0].name);
	
	for(i = 0; i < n2; i++) {

		if(a2[0].temp != 255) sum1 = sum1 + a2[i].temp;
		if(a2[0].hum != 255) sum2 = sum2 + a2[i].hum;

	}

	if(a2[0].temp != 255) printf("Tm = %.2f deg C\t", ((float) sum1 / (float) n2));
	if(a2[0].hum != 255) printf("Hm = %.2f %%", ((float) sum2 / (float) n2));
	printf("\n");

	sum1 = sum2 = 0;

	printf("\n%20s\t", a3[0].name);
	
	for(i = 0; i < n3; i++) {

		if(a3[0].temp != 255) sum1 = sum1 + a3[i].temp;
		if(a3[0].hum != 255) sum2 = sum2 + a3[i].hum;

	}

	if(a3[0].temp != 255) printf("Tm = %.2f deg C\t", ((float) sum1 / (float) n3));
	if(a3[0].hum != 255) printf("Hm = %.2f %%", ((float) sum2 / (float) n3));
	printf("\n");

	sum1 = sum2 = 0;

	printf("\n%20s\t", a4[0].name);
	
	for(i = 0; i < n4; i++) {

		if(a4[0].temp != 255) sum1 = sum1 + a4[i].temp;
		if(a4[0].hum != 255) sum2 = sum2 + a4[i].hum;

	}

	if(a4[0].temp != 255) printf("Tm = %.2f deg C\t", ((float) sum1 / (float) n4));
	if(a4[0].hum != 255) printf("Hm = %.2f %%", ((float) sum2 / (float) n4));
	printf("\n");

	sum1 = sum2 = 0;

	printf("\n%20s\t", a5[0].name);
	
	for(i = 0; i < n5; i++) {

		if(a5[0].temp != 255) sum1 = sum1 + a5[i].temp;
		if(a5[0].hum != 255) sum2 = sum2 + a5[i].hum;

	}

	if(a5[0].temp != 255) printf("Tm = %.2f deg C\t", ((float) sum1 / (float) n5));
	if(a5[0].hum != 255) printf("Hm = %.2f %%", ((float) sum2 / (float) n5));
	printf("\n");

	free(a1);
	free(a2);
	free(a3);
	free(a4);
	free(a5);

	printf("\nPress any key to continue. . .");

	while(!_kbhit());

}

void MainSystem::getExtrTemps() {

	fp=fopen("measurements.dat", "r");
	char instr[80];

	List l;
	Measurement *m;

	while(!feof(fp)) {
	
	fgets(instr, 80, fp);

	m = new Measurement(instr);

	if(m->temp != 255) l.insertAtBack(m);
	
	}

	fclose(fp);

	int n = l.getElements();

	Measurement *a = (Measurement *) malloc(sizeof(Measurement) * n);

	for(int i = 0; i < n; i++) a[i]=l.removeFromFront();

	int max = 0, min = 0;

	for(i = 1; i < n; i++){

		if(a[i].temp > a[max].temp) max=i;
		if(a[i].temp < a[min].temp) min=i;
	
	}

	printf("\nTmin = %3d deg C\t(%20s - Day %1d, %2d:00)\n", a[min].temp, a[min].name, a[min].mday, a[min].mhr);
	printf("\nTmax = %3d deg C\t(%20s - Day %1d, %2d:00)\n\n", a[max].temp, a[max].name, a[max].mday, a[max].mhr);

	free(a);

	printf("Press any key to continue. . .");
		
	while(!_kbhit());

}

void MainSystem::getExtrSunl() {
	
	fp=fopen("measurements.dat", "r");
	char instr[80];

	List l;
	Measurement *m;

	while(!feof(fp)) {
	
	fgets(instr, 80, fp);

	m = new Measurement(instr);

	if(m->sunl != 255 && m->sunl != -1) l.insertAtBack(m);
	
	}

	fclose(fp);

	int n = l.getElements();

	Measurement *a = (Measurement *) malloc(sizeof(Measurement) * n);

	for(int i = 0; i < n; i++) a[i] = l.removeFromFront();

	int max = 0, min = 0;

	for(i = 1; i < n; i++){

		if(a[i].sunl > a[max].sunl) max=i;
		if(a[i].sunl < a[min].sunl) min=i;
	
	}

	printf("\nMinimum sunlight = %2d\t(%20s - Day %1d, %2d:00)\n", a[min].sunl, a[min].name, a[min].mday, a[min].mhr);
	printf("\nMaximum sunlight = %2d\t(%20s - Day %1d, %2d:00)\n\n", a[max].sunl, a[max].name, a[max].mday, a[max].mhr);

	free(a);

	printf("Press any key to continue. . .");
	
	while(!_kbhit());

}

void MainSystem::sortSunl() {

	char keyin;

	printf("\n\nChoose sorting method:\n\n1. Bubble sort\n2. Heap sort\n\n");

	while(keyin != '1' && keyin != '2') {

		keyin = (char) getchar();

	}

	fp = fopen("measurements.dat", "r");
	char instr[80];

	List l;
	Measurement *m;

	while(!feof(fp)) {

		fgets(instr, 80, fp);
		m = new Measurement(instr);

		if(m->sunl != 255 && m->sunl != -1) l.insertAtBack(m);

	}

	fclose(fp);

	int n = l.getElements();

	Measurement *a = (Measurement *) malloc(sizeof(Measurement) * n);

	for(int i = 0; i < n; i++) {

		a[i] = l.removeFromFront();

	}

	if(keyin == '1') bubbleSort(a, n);
	else heapSort(a, n);

	printf("\nResults of sorting by sunlight in descending order:\n\n");

	for(i = 0; i < n; i++) {

		printf("Sunlight = %2d\t(%20s - Day %1d, %2d:00)\n", a[i].sunl, a[i].name, a[i].mday, a[i].mhr);

	}

	free(a);

	printf("\nPress any key to continue. . .");

	while(!_kbhit());
	
}

void MainSystem::bubbleSort(Measurement a[], int n) {
		
	int i, j;
	Measurement *tmp;

	for (i = 0; i < n - 1; i++) {

		for(j = n - 1; j > i; j--) {

			if(a[j].sunl > a[j - 1].sunl) {

				tmp = new Measurement(a[j]);
				a[j] = a[j - 1];
				a[j - 1] = *tmp;

			}

		}
	
	}

}

void MainSystem::heapSort(Measurement a[], int n) {
	
	int j, k;
	Measurement *tmp;

	int l = (int) n / 2;
	int r = n - 1;

	while(r > 0) {
		
		if(l > 0) {
			
			l--;
			j = l;
		
		}
		
		else {
			
			tmp = new Measurement(a[0]);
			a[0] = a[r];
			a[r] = *tmp;
			
			r--;
			j = 0;

		}

		int s = a[j].sunl;
		
		while((k = 2 * j) <= r) {
			
			if(k < r && a[k].sunl > a[k + 1].sunl) k++;
			
			if(s > a[k].sunl) {

				tmp = new Measurement(a[j]);
				a[j] = a[k];
				a[k] = *tmp;

				j = k;

			}

			else break;

		}
	
	}

}






	



