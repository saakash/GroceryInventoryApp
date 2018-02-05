/*Name: Aakash Shrestha
Student ID: 140051160
IPC 144
Section: Q
Final Project Milestone 4
Date: 05 Apr 2017
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

// Define statements:
#define LINEAR 1
#define FORM 0

#define STOCK 1
#define CHECKOUT 0
//#define MAX_ITEM_NO 21
#define MAX_QTY 999
#define SKU_MAX 999
#define SKU_MIN 100
#define MAX_ITEM_NO 500
#define DATAFILE "items.txt"

// Constant TAX value:
const double TAX = 0.13;

// Item structure:

struct Item {
	double price;
	int sku;
	int isTaxed;
	int quantity;
	int minQuantity;
	char name[21];
};

/* ---=== Function Prototypes Milestone 1 ===--- */

void welcome(void);
void printTitle(void);
void printFooter(double gTotal);
void flushKeyboard(void);
void pause(void);
int getInt(void);
double getDouble(void);
int getIntLimited(int lowerLimit, int upperLimit);
double getDoubleLimited(double lowerLimit, double upperLimit);
int yes(void);
void GroceryInventorySystem(void);
int menu(void);

/* ---=== Function Prototypes Milestone 2 ===--- */

double totalAfterTax(struct Item item);
int isLowQuantity(struct Item item);
struct Item itemEntry(int sku);
void displayItem(struct Item item, int linear);
void listItems(const struct Item item[], int NoOfItems);
int locateItem(const struct Item item[], int NoOfRecs, int sku, int* index);

/* ---=== Function Prototypes Milestone 3 ===--- */

void search(const struct Item item[], int NoOfRecs);
void updateItem(struct Item* itemptr);
void addItem(struct Item item[], int *NoOfRecs, int sku);
void addOrUpdateItem(struct Item item[], int* NoOfRecs);
void adjustQuantity(struct Item item[], int NoOfRecs, int stock);

/* ---=== Function Prototypes Milestone 4 ===--- */

void saveItem(struct Item item, FILE* dataFile);
int loadItem(struct Item* item, FILE* dataFile);
int saveItems(const struct Item item[], char fileName[], int NoOfRecs);
int loadItems(struct Item item[], char fileName[], int* NoOfRecsPtr);
void redundancy(const struct Item* item,char fileName[],int NoRecs);

/* ---=== Function Implementations Milestone 1 ===--- */

void welcome(void) {
	printf("---=== Grocery Inventory System ===---\n");
}

//printTitle prints the titles of items
void printTitle(void) {
	printf("Row |SKU| Name               | Price  |Taxed| Qty | Min |   Total    |Atn\n");
	printf("----+---+--------------------+--------+-----+-----+-----+------------|---\n");
}

//prints the footer line 
void printFooter(double gTotal) {
	printf("--------------------------------------------------------+----------------\n");
	if (gTotal > 0) {
		printf("                                           Grand Total: |%12.2lf\n", gTotal);
	}
}

//flushKeyboard clears the input buffer
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
	int integer, flag = 0;
	do {
		integer = getInt();      //calls getInt() to get an integer,stores in variable called integer
		if (integer >= lowerLimit && integer <= upperLimit) {
			flag = 1;
		}
		else {
			printf("Invalid value, %d < value < %d: ", lowerLimit, upperLimit);
		}
	} while (flag == 0);  // goes into the loop again if out of limits
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
	} while (flag == 0); //continues again if the value is out of limits
	return float_value;       //returns the value if it is within limits
}

//heart of the function
void GroceryInventorySystem(void) {
	struct Item item[MAX_ITEM_NO];
	int status,no_of_records=0,returnedValue, yesNo,flag = 0;
	welcome();
	status = loadItems(item,DATAFILE,&no_of_records);
	if (status == 0) {
		printf("Could not read from %s.\n", DATAFILE);
	}
	do {
		returnedValue = menu();   //calls menu function to display options and holds the returned option in a variable called returnedValue
		switch (returnedValue) {
		case 1:
			printf("List Items under construction!\n"); //prints the respective option for case 1
			listItems(item,no_of_records);
			pause();  //calls pause function to halt until user presses <ENTER>
			break;
		case 2:
			printf("Search Items under construction!\n");
			search(item, no_of_records);
			pause();
			break;
		case 3:
			printf("Checkout Item under construction!\n");
			adjustQuantity(item, no_of_records, CHECKOUT);
			redundancy(item, DATAFILE, no_of_records);
			/*saveResult = saveItems(item, DATAFILE, no_of_records);
			if (saveItems == 0) {
				printf("Could not read from %s.\n", DATAFILE);
			}
			pause();*/
			break;
		case 4:
			printf("Stock Item under construction!\n");
			adjustQuantity(item, no_of_records, STOCK);
			redundancy(item, DATAFILE, no_of_records);
			/*saveResult = saveItems(item, DATAFILE, no_of_records);
			if (saveItems == 0) {
				printf("Could not read from %s.\n", DATAFILE);
			}
			pause();*/
			break;
		case 5:
			printf("Add/Update Item under construction!\n");
			addOrUpdateItem(item, &no_of_records);
			redundancy(item, DATAFILE, no_of_records);
			/*saveResult = saveItems(item, DATAFILE, no_of_records);
			if (saveItems == 0) {
				printf("Could not read from %s.\n", DATAFILE);
			}
			pause();*/
			break;
		case 6:
			printf("Not implemented!\n");
			pause();
			break;
		case 7:
			printf("Not implemented!\n");
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
		while ((temp_char = getchar()) && temp_char != '\n') {
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


/* ---=== Function Implementations Milestone 2 ===--- */

//calculates total price of item after adding tax if applicable
double totalAfterTax(struct Item item) {
	double totalPrice = 0.00;
	if (item.isTaxed == 1) {           //if isTaxed is true i.e 1, tax is added to price
		totalPrice = item.price*item.quantity + TAX*(item.price*item.quantity);
	}
	else {                             // is isTaced is false, total price is just quantity times unit price
		totalPrice = item.price*item.quantity;
	}
	return totalPrice;
}

//this function checks if the quantity of item is less than minimum quantity
int isLowQuantity(struct Item item) {
	int isMin = 0;
	if (item.quantity <= item.minQuantity) {
		isMin = 1;
	}
	return isMin;
}

// this function takes data input for a given sku
struct Item itemEntry(int sku) {
	struct Item item;
	item.sku = sku;     //takes the sku of argument as its own sku
	printf("        SKU: %d\n", item.sku);
	printf("       Name: ");
	scanf("%[^\n]s", item.name);    // reads name
	flushKeyboard();                //flushes keyboard
	printf("      Price: ");
	item.price = getDoubleLimited(0.01,1000.00);       //calls getDouble function to read a valid double value for price
	printf("   Quantity: ");
	item.quantity = getIntLimited(1,MAX_QTY);       //calls getInt function to get an integer quantity
	printf("Minimum Qty: ");
	item.minQuantity = getIntLimited(0,100);    //gets integer value for minimum quantity
	printf("   Is Taxed: ");
	int yesNo = yes();              //calls yes function to check which returns 1 if true and 2 if false
	if (yesNo == 1) {
		item.isTaxed = 1;           //isTaxed of item is assigned 1 if returns true from yes function
	}
	else {
		item.isTaxed = 0;           //isTaxed of item is assigned 0 if false
	}
	return item;
}

//displayItem() displays the information of items

void displayItem(struct Item item, int linear) {

	int check = isLowQuantity(item);  //calls isLowQuantity if the quantity is less than minimum quantity

	if (linear == 1) {    //displays information linearly
		if (check == 0 && item.isTaxed == 0) {  //if quantity is not below minimum quantity and tax not applicable
			printf("|%3d|%-20s|%8.2lf|   No| %3d | %3d |%12.2lf|\n", item.sku, item.name, item.price, item.quantity, item.minQuantity, totalAfterTax(item));
		}
		else if (check == 0 && item.isTaxed == 1) {  //if quantity is not below minimum quantity and tax applicable
			printf("|%3d|%-20s|%8.2lf|  Yes| %3d | %3d |%12.2lf|\n", item.sku, item.name, item.price, item.quantity, item.minQuantity, totalAfterTax(item));
		}
		else if (check == 1 && item.isTaxed == 0) {  //if quantity is below minimum quantity and tax not applicable
			printf("|%3d|%-20s|%8.2lf|   No| %3d | %3d |%12.2lf|***\n", item.sku, item.name, item.price, item.quantity, item.minQuantity, totalAfterTax(item));
		}
		else if (check == 1 && item.isTaxed == 1) {  //if quantity is below minimum quantity and tax applicable
			printf("|%3d|%-20s|%8.2lf|  Yes| %3d | %3d |%12.2lf|***\n", item.sku, item.name, item.price, item.quantity, item.minQuantity, totalAfterTax(item));
		}
	}
	else if (linear == 0) {   //prints information vertically

		if (check == 0 && item.isTaxed == 0) {  //if quantity is not below minimum quantity and tax not applicable
			printf("        SKU: %-d\n", item.sku);
			printf("       Name: %s\n", item.name);
			printf("      Price: %-.2lf\n", item.price);
			printf("   Quantity: %-d\n", item.quantity);
			printf("Minimum Qty: %-d\n", item.minQuantity);
			printf("   Is Taxed: No\n");
		}
		else if (check == 0 && item.isTaxed == 1) {  //if quantity is not below minimum quantity and tax applicable
			printf("        SKU: %-d\n", item.sku);
			printf("       Name: %s\n", item.name);
			printf("      Price: %-.2lf\n", item.price);
			printf("   Quantity: %-d\n", item.quantity);
			printf("Minimum Qty: %-d\n", item.minQuantity);
			printf("   Is Taxed: Yes\n");
		}
		else if (check == 1 && item.isTaxed == 0) {  //if quantity is below minimum quantity and tax not applicable
			printf("        SKU: %-d\n", item.sku);
			printf("       Name: %s\n", item.name);
			printf("      Price: %-.2lf\n", item.price);
			printf("   Quantity: %-d\n", item.quantity);
			printf("Minimum Qty: %-d\n", item.minQuantity);
			printf("   Is Taxed: No\n");
			printf("WARNING: Quantity low, please order ASAP!!!\n");
		}
		else if (check == 1 && item.isTaxed == 1) {  //if quantity is below minimum quantity and tax applicable
			printf("        SKU: %-d\n", item.sku);
			printf("       Name: %s\n", item.name);
			printf("      Price: %-.2lf\n", item.price);
			printf("   Quantity: %-d\n", item.quantity);
			printf("Minimum Qty: %-d\n", item.minQuantity);
			printf("   Is Taxed: Yes\n");
			printf("WARNING: Quantity low, please order ASAP!!!\n");
		}
	}
}

// lists the items and grand total

void listItems(const struct Item item[], int NoOfItems) {
	int i = 0;
	double grandTotal = 0;
	printTitle();
	for (i = 0; i < NoOfItems; i++) {
		printf("%-4d", i + 1);
		displayItem(item[i], 1);
		grandTotal += totalAfterTax(item[i]);  //calculates grand total of price of all items
	}
	printFooter(grandTotal);   // prints the footer
}

//this function locates the item search matching given sku

int locateItem(const struct Item item[], int NoOfRecs, int sku, int* index) {

	int i = 0, flag = 0;
	for (i = 0; i < NoOfRecs && flag == 0; i++) {   //searches over the number of records till a match is found,does not go over after a match id found
		if (item[i].sku == sku) {
			*index = i;      //index takes the index value of array when sku matches
			flag = 1;		 
		}
	}
	return flag;		//returns 1 if match found and 0 if not found
}


/* ---=== Function implementations for milestone 3 ===--- */

//search() function searches the whole array of items prompting sku from user
void search(const struct Item item[], int NoOfRecs) {
	int sku, flag, searchIndex;
	printf("Please enter the SKU: ");   //prompting user for sku
	sku = getIntLimited(SKU_MIN, SKU_MAX);  //getIntLimited function is called to get the sku between the required limit
	flag = locateItem(item, NoOfRecs, sku, &searchIndex);  //calls locateItem() function to locate the item
	if (flag == 0) {
		printf("Item not found!\n");   //item could not be located if zero is returned
	}
	else {
		displayItem(item[searchIndex], FORM);  //calls displayItem() function in FORM format to display the located item
	}
}

//updateItem() function updates the details of the item
void updateItem(struct Item* itemptr) {
	int yesNo;
	struct Item instance;    //creating new Item
	printf("Enter new data:\n");
	instance = itemEntry(itemptr->sku); //calls itemEntry() function to get the details, sku is sent as a parameter
	printf("Overwrite old data? (Y)es/(N)o: ");
	yesNo = yes();
	if (yesNo == 1) {
		*itemptr = instance;     //item pointer updates the newly entered data if user confirms
		printf("--== Updated! ==--\n");
	}
	else {
		printf("--== Aborted! ==--\n");  //displays aborted if user presses no
	}
}

//addItem() function adds the new item in the struct of items at the end of items
void addItem(struct Item item[], int *NoOfRecs, int sku) {
	int yesNo;
	struct Item new;   //creating new Item
	if (*NoOfRecs >= MAX_ITEM_NO) {   //checking if the number of items does not exceed limit
		printf("Can not add new item; Storage Full!\n");
	}
	else {
		new = itemEntry(sku);  //getting the inputs for the new item
		printf("Add Item? (Y)es/(N)o: ");
		yesNo = yes();
		if (yesNo == 1) {
			item[*NoOfRecs] = new;   //assigns the new item to the last record of the item list
			*NoOfRecs = *NoOfRecs + 1; //incrementing the size of number of records
			printf("--== Added! ==--\n");
		}
		else {
			printf("--== Aborted! ==--\n");
		}
	}
}

//addOrUpdateItem() function either adds or updates the item depending on SKU is found or not
void addOrUpdateItem(struct Item item[], int* NoOfRecs) {
	int sku, flag, searchIndex, yesNo;
	printf("Please enter the SKU: ");
	sku = getInt();  //sku is read through getInt() function
	flag = locateItem(item, *NoOfRecs, sku, &searchIndex);  //calls locateItem() function to check item's existence
	if (flag == 1) {
		displayItem(item[searchIndex], FORM);   //displays the item if foundin the array of items
		printf("Item already exists, Update? (Y)es/(N)o: ");
		yesNo = yes();
		if (yesNo == 1) {
			updateItem(&item[searchIndex]);  //calls update() function to update the item which already exists
		}
		else {
			printf("--== Aborted! ==--\n");
		}
	}
	else {
		addItem(item, NoOfRecs, sku);   //calls add() function to add the item if it is not found in the existing list
	}
}

//adjustQuantity() function updates the quantity of the particular item
void adjustQuantity(struct Item item[], int NoOfRecs, int stock) {
	int sku, flag, searchIndex, value, min;
	char name1[15] = "to stock";
	char name2[15] = "to checkout";
	printf("Please enter the SKU: ");
	sku = getInt();				//gets user input for sku
	flag = locateItem(item, NoOfRecs, sku, &searchIndex); //tries locating the item in the array
	if (flag == 0) {
		printf("SKU not found in storage!\n");
	}
	else {
		displayItem(item[searchIndex], FORM);
		if (stock == STOCK) {   //to keep the items on stock
			printf("Please enter the quantity %s; Maximum of %d or 0 to abort: ", name1, MAX_QTY - item[searchIndex].quantity);
							//maximum quantity minus the available quantity is the amount of quantity that can be added to stock													
			value = getIntLimited(0, MAX_QTY - item[searchIndex].quantity);
							//makes sure the value is between 0 to the amount available for stocking   
		}
		else {		
			printf("Please enter the quantity %s; Maximum of %d or 0 to abort: ", name2, item[searchIndex].quantity);
							//item[searchIndex].quantity is the quantity of item available  that can be checked out
			value = getIntLimited(0, item[searchIndex].quantity);

		}

		if (value == 0) {                   //appropriate message displayed if user presses zero
			printf("--== Aborted! ==--\n");
		}
		else {                              //if user presses non zero
			if (stock == STOCK) {
				item[searchIndex].quantity += value;   //adds the entered value of quantity of item to its existing quantity
				printf("--== Stocked! ==--\n");        //prints appropriate message
			}
			else if (stock == CHECKOUT) {
				item[searchIndex].quantity -= value;   //decreases the quantity of item subtracting the quantities that are checked out
				printf("--== Checked out! ==--\n");    //prints appropriate message of checked out

			}
			min = isLowQuantity(item[searchIndex]);    //checks if the quantity of item comes below the minimum quantity
			if (min == 1) {                            //if it is below the minimum quantity, an appropriate message is displayed
				printf("Quantity is low, please reorder ASAP!!!\n");
			}
		}

	}
}

/* ---=== Function Implementations Milestone 4 ===--- */

//saveItem() function writes the content of an item into the file.
void saveItem(struct Item item, FILE* dataFile) {

		fprintf(dataFile, "%d,%d,%d,%.2lf,%d,%s\n", item.sku,item.quantity,item.minQuantity,item.price,item.isTaxed,item.name);		
												//writes a line of record with comma separation
}

//loadItem() function reads all the contents of an item from a file 
int loadItem(struct Item* item, FILE* dataFile) {
	int return_value = 0;    //variable to hold the number of successfully read fields of a record from a file
	if (dataFile != NULL) {
		return_value = fscanf(dataFile, "%d,%d,%d,%lf,%d,%[^\n]%*c", &item->sku,&item->quantity,&item->minQuantity,&item->price,&item->isTaxed,item->name );
							 //reads from dataFile the contents and stores them in the item structure pointed by the file pointer
                             
	}
	else {
		printf("could not open file\n");
	}
	return  return_value;    //returns number equal to read fields of a record, 0 in case of values not read
}

//saveItems() function calls saveItem function iteratively to save all for a given number of records
int saveItems(const struct Item item[], char fileName[], int NoOfRecs) {
	int i,save_status = 0;
	FILE *fp = NULL;
	fp = fopen(fileName, "w");          //opening a file in writing mode to write into file
	if (fp != NULL) {
		for (i = 0; i < NoOfRecs; i++) {
			saveItem(item[i], fp);      //calls saveItem function over NoOfRecs to save all records
		}
		save_status = 1;                //save_status is set 1 if successfull
		fclose(fp);
	}
	else {
		printf("could not open file\n");
	}
	return save_status;                 //returns 1 for true status of writing and 0 for false or error
}

//loadItems() function calls loadItem function to read all the records
int loadItems(struct Item item[], char fileName[], int* NoOfRecsPtr) {
	int load_status=0,count=0;
	FILE *fp = NULL;
	fp = fopen(fileName, "r");      //opens file for reading mode
	if (fp != NULL) {
		while (loadItem(&item[count], fp) == 6) {  //calls the loadItem function to load items till it loads successfully 6 fields of records
			count ++;             //count is increased by one for every iteration to count the successfully read records
	}
		load_status = 1;          //load_status is set 1 if records are read
		*NoOfRecsPtr=count;       //NoOfRecs pointer is set to the total number of records read
		fclose(fp);
	}
	else {
		printf("could not open the file\n");
	}
	return load_status;           //returns 1 as true and 0 for false
}

void redundancy(const struct Item* item,char fileName[],int NoRecs) {
	int result = 0;
	result = saveItems(item, DATAFILE, NoRecs);
	if (result == 0) {
		printf("Could not read from %s.\n", DATAFILE);
	}
	pause();
}

// main function()
int main() {
	GroceryInventorySystem();
	return 0;
}