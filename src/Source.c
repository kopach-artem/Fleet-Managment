#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h> //To use malloc
#include <string.h> //To use strcpy()

typedef struct c //This structure for cars from our cars.txt
{
	int id;
	char plate[7];
	char make[20]; 
	char model[20];
}Car;

typedef struct d //This structure for date information from our fueling.txt
{
	int year;
	int month;
	int day;
}Date;

typedef struct f //This structure for fueling infromation from our fueling.txt
{
	int id;
	Date date; //In this case, we use including structure by Date struct 
	int liters;
	unsigned int mileage;
}Fuel;

typedef struct fn //Structure for node of fueling file
{
	Fuel fuel;
	struct fn* next;
} FuelNode;

typedef struct nc //Structure for node of cars file
{
	Car car;
	struct nc* next;
	struct fn* fuels;
}CarNode;


void PrintFuelByCar(int id)
{
	printf("Now this function in process of coding, sorry!\n");

	// In this function we should realise double linked lists 


	/*FILE* fp;
	Fuel zapravka;
	fp = fopen("C:\\Users\\akopa\\OneDrive\\Рабочий стол\\My education BME\\HW Prog\\refueling.txt", "r");

	while (fscanf(fp, "%d %d.%d.%d %d %d", &zapravka.id, &zapravka.date.year, &zapravka.date.month, &zapravka.date.day, &zapravka.liters, &zapravka.mileage) == 6)
	{
		if (zapravka.id == id)
			printf("%d %d.%d.%d %d %d\n", zapravka.id, zapravka.date.year, zapravka.date.month, zapravka.date.day, zapravka.liters, zapravka.mileage);
	}
	fclose(fp);*/
}


CarNode* AddNodeToCarList(CarNode* hp, Car* newCar)
{
	if (hp == NULL) //Add the first node
	{
		hp = (CarNode*)malloc(sizeof(CarNode));
		if (hp)
		{
			hp->car.id = newCar->id;
			strcpy(hp->car.make, newCar->make);
			strcpy(hp->car.model, newCar->model);
			strcpy(hp->car.plate, newCar->plate);
			hp->next = NULL;
			return hp;
		}
		else
		{
			// Write here something
		}
	}

	CarNode* temp = hp;

	while (temp->next)
	{
		temp = temp->next;
	}
	// Now temp is the last npde

		
	CarNode* newCarNode;
	newCarNode = (CarNode*)malloc(sizeof(CarNode));

	if (newCarNode)
	{
	newCarNode->car.id = newCar->id;
	strcpy(newCarNode->car.make, newCar->make);
	strcpy(newCarNode->car.model, newCar->model);
	strcpy(newCarNode->car.plate, newCar->plate);
	newCarNode->next = NULL;
	temp->next = newCarNode;
	return hp;
	free(newCarNode);
	}
}


void PrintCars(CarNode* head) //Function to pint our nodes
{
	if (!head)
		printf("Car list is empty!");
	else
	{
		while (head)
		{
			printf("%d %s %s %s \n", head->car.id, head->car.plate, head->car.make, head->car.model);
			head = head->next;
		}
	}
}

void PrintFuel(FILE *fp)
{
	Fuel zapravka;
	while (fscanf(fp, "%d %d.%d.%d %d %d", &zapravka.id, &zapravka.date.year, &zapravka.date.month, &zapravka.date.day, &zapravka.liters, &zapravka.mileage) == 6)
	{
		// In this function later we will use function to get double linked list
		printf("%d %d.%d.%d %d %d\n", zapravka.id, zapravka.date.year, zapravka.date.month, zapravka.date.day, zapravka.liters, zapravka.mileage);
	}
	fclose(fp);
}


int userInput()
{
	int choice;

	printf("===========================\n");
	printf("(1). View all cars\n");
	printf("(2). View all details about fueling\n");
	printf("(3). Add new car\n");
	printf("(4). Add new fueling\n");
	printf("(5). Print fuel by car\n");
	printf("(6). Calculate the average on 100 km\n");
	printf("(0). Exit\n");
	printf("===========================\n\n");

	printf("Enter your choice Please\n");
	scanf("%d", &choice);

	return choice;
}



int main()
{
	CarNode* CarsHead = NULL; //Must put our pointer of head to NULL

	FILE* fp; //Pointer of file 

	int carID = 0;

	fp = fopen("C:\\Users\\akopa\\OneDrive\\Рабочий стол\\My education BME\\HW Prog\\cars.txt", "r"); //Please, right new dway to file after saving ZIP!

	//We must open the file of cars to get this to list
	
	if (fp == NULL) // Check do we have file or no?
	{
		printf("No File");
		return 1;
	}

	Car mashina;

	while (fscanf(fp, "%d %s %s %s", &mashina.id, mashina.plate, mashina.make, mashina.model) == 4) 
	{
		CarsHead = AddNodeToCarList(CarsHead, &mashina);
	}

	fp = fopen("C:\\Users\\akopa\\OneDrive\\Рабочий стол\\My education BME\\HW Prog\\refueling.txt", "r"); //Please, right new dway to file after saving ZIP!

	//We must open the file of cars to get this to list

	if (fp == NULL) // Check do we have file or no?
	{
		printf("No File ");
		return 1;
	}
	

	int sel = 1; //select number for menu


	while (sel != 0)
	{
		sel = userInput();

		switch (sel)
		{
		case 1:
			PrintCars(CarsHead);
			break;

		case 2:
			PrintFuel(fp);
			break;

		case 3:
			printf("Now this function in process of coding, sorry!\n");
			break;

		case 4:
			printf("Now this function in process of coding, sorry!\n");
			break;

		case 5:
			PrintFuelByCar(carID);
			break;

		case 6:
			printf("Now this function in process of coding, sorry!\n");
			break;
		}
		if (sel == 0)
			break;
	}


	fclose(fp); //Don't forget to close the file after reading 


	return 0;
}