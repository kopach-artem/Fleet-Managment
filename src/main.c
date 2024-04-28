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

typedef struct nf //Structure for node of cars file
{
	Car car;
	struct nc* next;
}CarNodeF;




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
			hp->fuels = NULL;
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
		strcpy(newCarNode->car.model, newCar->model);   //Copy with right "sequnces"
		strcpy(newCarNode->car.plate, newCar->plate);
		newCarNode->next = NULL;
		newCarNode->fuels = NULL;
		temp->next = newCarNode;
		return hp;
		free(newCarNode);
	}
}


void AddNewCarFromUserInput(CarNode* head)
{
	CarNode* newcar = (CarNode*)malloc(sizeof(CarNode));
	char buf[32];
	printf("Provide data for a new car: \n");
	printf(" - Licence plate: ");
	scanf("%s", buf);
 	for (int i = 0; i < 6; i++)
		newcar->car.plate[i] = buf[i];
	newcar->car.plate[6] = '\0';

	printf(" - Make: ");
	scanf("%s", buf);
	for (int i = 0; i < 6; i++)
		newcar->car.make[i] = buf[i];
	newcar->car.make[19] = '\0';

	printf(" - Model: ");
	scanf("%s", buf);
	for (int i = 0; i < 6; i++)
		newcar->car.model[i] = buf[i];
	newcar->car.model[19] = '\0';
	
	while (head->next)
		head = head->next;
	newcar->car.id = head->car.id + 1;
	head->next = newcar;
	newcar->next = NULL;
	newcar->fuels = NULL;
}

void PrintCar(CarNode* car)
{
	printf("%d %s %s %s \n", car->car.id, car->car.plate, car->car.make, car->car.model);

}


void PrintFuel(Fuel* fuel)
{
	printf(" - %d.%d.%d\t%d liters\t%d km\n", fuel->date.year, fuel->date.month, fuel->date.day, fuel->liters, fuel->mileage);
}

void PrintCars(CarNode* head) //Function to print our nodes
{
	if (!head)
		printf("Car list is empty!");
	else
	{
		while (head)
		{
			PrintCar(head);
			head = head->next;
		}
	}
}

void PrintAll(CarNode* head)
{
	while (head)
	{
		PrintCar(head);
		FuelNode* temp = head->fuels;
		while (temp)
		{
			PrintFuel(&(temp->fuel));
			temp = temp->next;
		}
		head = head->next;
	}
}

CarNode* FindCarNodeById(CarNode* head, int id)
{
	while (head)
	{
		if (head->car.id == id)
			return head;
		head = head->next;
	}
}

void AddFuelNodeToCarNode(CarNode* car, Fuel newFuel)
{
	if (car->fuels == NULL)  // It is the first Fuels node
	{
		FuelNode* fn = (FuelNode*)malloc(sizeof(FuelNode));
		if (fn)
		{
			fn->fuel.date.day = newFuel.date.day;
			fn->fuel.date.month = newFuel.date.month;
			fn->fuel.date.year = newFuel.date.year;
			fn->fuel.id = newFuel.id;
			fn->fuel.liters = newFuel.liters;
			fn->fuel.mileage = newFuel.mileage;
			fn->next = NULL;
			car->fuels = fn;
			return;
		}
	}

	FuelNode* temp = car->fuels;
	while (temp->next)
	{
		temp = temp->next;
	}

	FuelNode* fn = (FuelNode*)malloc(sizeof(FuelNode));
	if (fn)
	{
		fn->fuel.date.day = newFuel.date.day;
		fn->fuel.date.month = newFuel.date.month;
		fn->fuel.date.year = newFuel.date.year;
		fn->fuel.id = newFuel.id;
		fn->fuel.liters = newFuel.liters;
		fn->fuel.mileage = newFuel.mileage;
		fn->next = NULL;
		temp->next = fn;
		return;
	}

}

void LoadAllFuelsFromFile(CarNode* head, FILE* fp)
{
	Fuel zapravka;
	while (fscanf(fp, "%d %d.%d.%d %d %d", &zapravka.id, &zapravka.date.year, &zapravka.date.month, &zapravka.date.day, &zapravka.liters, &zapravka.mileage) == 6)
	{
		CarNode* car = FindCarNodeById(head, zapravka.id);
		AddFuelNodeToCarNode(car, zapravka);
	}
	fclose(fp);
}


float getAverageConsumptionByCarId(CarNode* head, int id)
{
	CarNode* car = FindCarNodeById(head, id);
	if (car->fuels == NULL) return -1;
	if (car->fuels->next == NULL) return -1;

	int mileage_start = car->fuels->fuel.mileage;
	int total_liters = 0;
	FuelNode* fn = car->fuels;
	while (fn->next != NULL)
	{
		total_liters += fn->fuel.liters;
		fn = fn->next;
	}
	int mileage_end = fn->fuel.mileage;
	return (float)total_liters / (mileage_end - mileage_start) * 100;
}

void PrintConsumptionByCar(CarNode* head, CarNode* car)
{
	float consumption = getAverageConsumptionByCarId(head, car->car.id);
	if (consumption == -1)
		printf("- not enough data to calculate the consumption\n");
	else
		printf("- the average consumption is %lf liters per 100 km\n", consumption);
}

void PrintAverageConsumptionForAllCars(CarNode* head)
{
	CarNode* temp = head;
	while (temp)
	{
		PrintCar(temp);
		PrintConsumptionByCar(head, temp);
		temp = temp->next;
	}
}


int Services(CarNode* head, int id)
{
	CarNode* car = FindCarNodeById(head, id);
	FuelNode* fn = car->fuels;
	if (fn == NULL)
		return -1;

	while (fn->next != NULL)
	{
		fn = fn->next;
	}

	if ((fn->fuel.mileage % 20000) > 15000)
		return (20000- fn->fuel.mileage % 20000);
	return -1;
}

void AddNewReFuel(CarNode* head, int id)
{
	CarNode* car = FindCarNodeById(head, id);
	Fuel NewFuel;
	NewFuel.id = id;
	printf("print year of Fueling: ");
	scanf("%d", &NewFuel.date.year);
	printf("print month of Fueling: ");
	scanf("%d", &NewFuel.date.month);
	printf("print day of Fueling: ");
	scanf("%d", &NewFuel.date.day);
	printf("print liters of Fueling: ");
	scanf("%d", &NewFuel.liters);
	printf("print mileage of Fueling: ");
	scanf("%d", &NewFuel.mileage);
	AddFuelNodeToCarNode(car, NewFuel);
}

void SaveToFile(CarNode* head)
{
	FILE* fp;
	fp = fopen("C:\\Users\\akopa\\OneDrive\\Đŕáî÷čé ńňîë\\My education BME\\HW Prog\\cars.txt", "w");
	FILE* fpF;
	fpF = fopen("C:\\Users\\akopa\\OneDrive\\Đŕáî÷čé ńňîë\\My education BME\\HW Prog\\Refueling.txt", "w");
	if (fp == NULL || fpF == NULL) // Check do we have file or no?
	{
		printf("No Files can be created.");
		return;
	}
	CarNode* tmp = head;
	while (tmp)
	{
		while (tmp->fuels)
		{
			fprintf(fpF, "%d %d.%d.%d %d %d\n", tmp->fuels->fuel.id, tmp->fuels->fuel.date.year, tmp->fuels->fuel.date.month, tmp->fuels->fuel.date.day, tmp->fuels->fuel.liters, tmp->fuels->fuel.mileage);
			tmp->fuels = tmp->fuels->next;
		}
		fprintf(fp, "%d %s %s %s\n", tmp->car.id, tmp->car.plate, tmp->car.make, tmp->car.model);
		tmp = tmp->next;
	}
	fclose(fp);
	fclose(fpF);
}

int userInput()
{
	int choice;

	printf("===========================\n");
	printf("(1). View all cars\n");
	printf("(2). View fueling data for all cars\n");
	printf("(3). Get average consumption for all cars\n");
	printf("(4). Add new car\n");
	printf("(5). Add new fueling data for a car\n");
	printf("(6). Get Servicing data for a car\n");
	printf("(7). Save all data to file\n");
	printf("(8). Exit\n");
	printf("===========================\n\n");

	printf("Enter your choice: \n");
	scanf("%d", &choice);

	return choice;
}

char SelMenu(int sel, CarNode* CarsHead)
{
	int carID;
	switch (sel)
	{
	case 1:
		PrintCars(CarsHead);
		break;

	case 2:
		PrintAll(CarsHead);
		break;

	case 3:
		PrintAverageConsumptionForAllCars(CarsHead);
		break;
	case 4:
		AddNewCarFromUserInput(CarsHead);
		break;
	case 5:
		PrintCars(CarsHead);
		scanf("%d", &carID);
		printf("Fueling data for the selected car:\n");
		FuelNode* temp1;
		temp1 = FindCarNodeById(CarsHead, carID)->fuels;
		if (temp1 == NULL)
			printf("This car has no fuel entries yet.");
		else
		{
			while (temp1)
			{
				PrintFuel(&(temp1->fuel));
				temp1 = temp1->next;
			}
		}
		AddNewReFuel(CarsHead, carID);
		break;

	case 6:
	{
		CarNode* cntemp;
		cntemp = CarsHead;
		printf("The following cars must soon go to service in less than 3000 km:\n");
		while (cntemp)
		{
			if (Services(CarsHead, cntemp->car.id) > 0)
			{
				PrintCar(cntemp);
				printf("- must go to service in %d km\n", Services(CarsHead, cntemp->car.id));
			}
			cntemp = cntemp->next;
		}
		break;
	}
	case 7:
	{
		FuelNode* fn;
		fn = CarsHead->fuels;
		SaveToFile(CarsHead, fn);
		break;
	}
	case 8:
		return;
	default:
		printf("Wrong menu item selected.\n");
	}

	printf(". . .\n");
	printf("Do you want to continue? Y-yes, N-no\n");
	char cont;
	while (cont = getchar() != '\n');
	scanf("%c", &cont);
	return cont;

}


int main()
{
	CarNode* CarsHead = NULL; //Must put our pointer of head to NULL

	FILE* fp; //Pointer of file 

	/*int carID = 0;*/

	fp = fopen("C:\\Users\\akopa\\OneDrive\\Đŕáî÷čé ńňîë\\My education BME\\HW Prog\\cars.txt", "r");

	//We must open the file of cars to get this to list

	if (fp == NULL) // Check do we have file or no?
	{
		printf("No File");
		return 1;
	}

	Car vehicle;

	while (fscanf(fp, "%d %s %s %s", &vehicle.id, vehicle.plate, vehicle.make, vehicle.model) == 4)
	{
		CarsHead = AddNodeToCarList(CarsHead, &vehicle);
	}
	fclose(fp);

	fp = fopen("C:\\Users\\akopa\\OneDrive\\Đŕáî÷čé ńňîë\\My education BME\\HW Prog\\refueling.txt", "r");

	//We must open the file of cars to get this to list

	if (fp == NULL) // Check do we have file or no?
	{
		printf("No File ");
		return 1;
	}
	else
	{
		LoadAllFuelsFromFile(CarsHead, fp);
	}

	int sel;
	char cont = 'y';
	while (cont == 'y' || cont == 'Y')
	{
		system("CLS");
		sel = userInput();
		cont = SelMenu(sel, CarsHead);
	}
	fclose(fp); //Don't forget to close the file after reading 

	return 0;

}
