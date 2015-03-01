#include "ippalos.cpp"

void main() {

	char keyin;
	long t;
	MainSystem ms;

	t = time(0);
	srand((unsigned int) t);

	printf("***** IPPALOS METEOROLOGICAL SYSTEM *****\n\n\n1. Start measurements\n2. Exit\n\n");

	while(keyin != '1' && keyin != '2') {

		keyin = (char) getchar();

	}

	if(keyin == '1') {

		printf("\n\nGathering data. Please wait. . .\n");
		ms.startMeasurements();
		printf("\n\nData acquisition completed.\n\nPress any key to continue. . .");

		while(!_kbhit());

		while(keyin != '5') {

			keyin = '\0';
			printf("\n\n\n1. Calculate temperature & humidity avg.\n2. Calculate extreme temperatures\n3. Calculate extreme sunlight\n4. Sort by sunlight\n5. Exit\n\n");

			while(keyin != '1' && keyin != '2' && keyin != '3' && keyin != '4' && keyin != '5') {

				keyin = (char) getchar();

			}	

			if(keyin == '1') ms.getMeanTempAndHum();
			if(keyin == '2') ms.getExtrTemps();
			if(keyin == '3') ms.getExtrSunl();
			if(keyin == '4') ms.sortSunl();

		}

	}
	
}