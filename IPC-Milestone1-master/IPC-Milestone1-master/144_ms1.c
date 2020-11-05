#include <stdio.h>
// tools
void welcome(void);
void printTitle(void);
void printFooter(double gTotal);
void flushKeyboard(void);
void pause(void);
int getInt(void);
double getDouble(void);
int getIntLimited(int lowerLimit, int upperLimit);
double getDoubleLimited(double lowerLimit, double upperLimit);

// app interface
int yes(void);
void GroceryInventorySystem(void);
int menu(void);

// code your functions here:

//welcome() prints the welcome message
void welcome(void) {
	printf("---=== Grocery Inventory System ===---\n");
}

//printTitle prints the titles of items
void printTitle(void) {
	printf("Row |SKU| Name               | Price |Taxed| Qty | Min |   Total   |Atn\n");
	printf("----+---+--------------------+-------+-----+-----+-----+-----------+---\n");
}

//prints the footer line 
void printFooter(double gTotal) {
	printf("-------------------------------------------------------+---------------\n");
	if (gTotal > 0) {
		printf("\t\t\t\t\t  Grand Total: |%12.2lf\n",gTotal);
	}
}
//flushKeyboard clears the input buffer.....
void flushKeyboard(void) {
	while (getchar() != '\n')
		;             //intentional empty statement
}

//pause() function pauses the execution unless user presses <ENTER>
void pause(void) {
	printf("Press <ENTER> to continue...");
	flushKeyboard();	
}




//getInt() accepts a valid integer
int getInt(void) {
	int rc, value, keepTrying = 0; 
	char after;                             //stores trailing charater in variable after
	do {
		rc = scanf("%d%c", &value, &after); //rc is zero if the first character is not integer.
		if (rc == 0) {
			printf("Invalid integer, please try again: ");
			flushKeyboard();
		}
		else if (after != '\n') {
			printf("Invalid integer, please try again: ");
			flushKeyboard();
		}
		else {
			keepTrying = 1; //flag value changes to exit loop if the integer is valid 			
			//return value;   //returns the valid integer to the calling function
		}
	} while (keepTrying == 0);
	return value;
}

//getIntLimited() accepts an integer between the limits
int getIntLimited(int lowerLimit, int upperLimit) {
	int integer,flag=0;
	do {
		integer = getInt();      //calls getInt() to get an integer,stores in variable called integer
		if (integer >= lowerLimit && integer <= upperLimit) {
			flag = 1;
		}
		else {
			printf("Invalid value, %d < value < %d: ", lowerLimit, upperLimit);
		}
	} while (integer < lowerLimit || integer >upperLimit);  // goes into the loop again if out of limits
return integer;      //returns integer if it is between the limits
}

//getDouble() accepts a valid double value
double getDouble(void) {
	int keepTrying = 0;  
	char after;
	double rc, value;
	do {
    	rc = scanf("%lf%c", &value, &after); //stores the user input in variable value
		if (rc == 0) {
			printf("Invalid number, please try again: "); //prints error message if the first character read is not an integer
			flushKeyboard();  //clears keyboard before taking user input again
		}
		else if (after != '\n') {
			printf("Invalid number, please try again: ");  //prints error message if there are trailing characters
			flushKeyboard();
		}
		else {
			keepTrying = 1;  //flag value changes to exit loop if the value is valid double
		}
	} while (keepTrying == 0);
	return value;
}

//getDoubleLimited function accepts a value between the limits of its parameters
double getDoubleLimited(double lowerLimit, double upperLimit) {
	int flag;
	double float_value;
	do {
		float_value = getDouble();    //calls getDouble function to get double value
		if (float_value >= lowerLimit && float_value <= upperLimit) {
			flag = 1;
		}
		else {
			printf("Invalid value, %.6lf< value < %.6lf: ", lowerLimit, upperLimit);
		}
	} while (float_value < lowerLimit || float_value > upperLimit); //continues again if the value is out of limits
return float_value;       //returns the value if it is within limits
}

//heart of the function
void GroceryInventorySystem(void) {
	int returnedValue, yesNo, flag = 0;
	welcome();
	do {
		returnedValue = menu();   //calls menu function to display options and holds the returned option in a variable called returnedValue
		switch (returnedValue) {
		case 1:
			printf("List Items under construction!\n"); //prints the respective option for case 1
			pause();  //calls pause function to halt until user presses <ENTER>
			break;
		case 2:
			printf("Search Items under construction!\n");
			pause();
			break;
		case 3:
			printf("Checkout Item under construction!\n");
			pause();
			break;
		case 4:
			printf("Stock Item under construction!\n");
			pause();
			break;
		case 5:
			printf("Add/Update Item under construction!\n");
			pause();
			break;
		case 6:
			printf("Delete Item under construction!\n");
			pause();
			break;
		case 7:
			printf("Search by name under construction!\n");
			pause();
			break;
		case 0:
			printf("Exit the program? (Y)es/(N)o: ");
			yesNo = yes();     //calls yes function to ask user to exit or not and holds the returned value in yesNo variable
			if (yesNo == 1) {
				flag = 1;      //flag changes to exit the loop when yes function returns 1
			}
			break;
		default:
			break;
		}
	} while (flag == 0);    
}

//yes() checks if the user wants to continue or not
int yes(void) {
	int flag = 0;
	char temp_char;          // variable declaration for temporary character storage
	char character;
	do {
		int n = 0;           //number of characters initialized to zero
		while ((temp_char = getchar()) && temp_char!= '\n') {      
			n++;             
			character = temp_char;  //puts the character obtained from getchar() to a variable named character
		}
		if ((character == 'Y' || character == 'y') && n == 1) {
			flag = 1;  //flag value changes if the input character matches Y or y
		}
		else if ((character == 'N' || character == 'n') && n == 1) {
			flag = 2;  //flag value changes if the input charater matches N or n
		}
		else {
			printf("Only (Y)es or (N)o are acceptable: ");
		}
	} while (flag == 0);
	return flag;  //returns 1 if Y or y matched and returns 2 if N or n matched
}

int menu(void) {
	int option;   //variable to hold the user input for options
	printf("1- List all items\n");
	printf("2- Search by SKU\n");
	printf("3- Checkout an item\n");
	printf("4- Stock an item\n");
	printf("5- Add new item or update item\n");
	printf("6- delete item\n");
	printf("7- Search by name\n");
	printf("0- Exit program\n");
	option = getIntLimited(0, 7); //calls the getIntLimited function to check the number between 0 and 7
	return option;  //returns the number to GroceryInventorySystem function
}
