/*
Developer: Brandon Cox
Title: Store Program
Date: 11/28/2023
Description: A store based program that asks a user if they want to purcahse video games.
Program will present a menu of video games from a .txt file for purchase and its information.
The program will let the user add new games to the store. Afterwhich it will allow the user
to purchase individual video games for a dedicated group of individuals and output a cart
for each game purchased, how many of each game purchased, and total for the entire cart for each customer.
The program will then prompt the user to access the manager report, which will require a password.
The program then provides data for the overall revenue from the day and a total revenue loss on any game that was
attempted to be purchased and was out of stock. The manager report will also show every game and the quantity
the store has in stock for each game. Following this the program will prompt the user asking if they wany to buy
more quantity for any game in the store. The user can then add more quantity which will then add any and all
data from the program back into a .txt file.
*/

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

class Item	//Holds all data for different games
{
private:					//Private data members that hold object data variables
	string name;			//Holds name of game
	double price = 0.0;		//Price of game
	int quantity = 0;		//Quantity of games
	string genre;			//Game genre
	char rating = 'E';		//Game rating
	int gameCount = 1;		//Game Number for output
	int quantityLoss = 0;   //Quantity of the game attmempted to purchase out of stock
	double priceLoss = 0.0; //Revenue loss of the individual game attempted to purchase out of stock
	double totalLoss = 0.0; //Total loss of every game attempted to purchase out of stock
	double totalPay = 0.0;  //Total amount customer has to pay

public:						//Public data and functions		
	Item()					//Default constructor
	{
		name = "";
		price = 0.0;
		quantity = 0;
		genre = "";
		rating = 'E';
		gameCount = 1;
		quantityLoss = 0;
		priceLoss = 0.0;
		totalLoss = 0.0;
		totalPay = 0.0;
	}
							//Additional secondary constructor
	Item(string name, double price, int quantity, string genre, char rating) {
		this->name = name;
		this->price = price;
		this->quantity = quantity;
		this->genre = genre;
		this->rating = rating;
	}
							//All setter function for just game data
	void allGameSetters(string name, double price, int quantity, string genre, char rating)
	{
		this->name = name;
		this->price = price;
		this->quantity = quantity;
		this->genre = genre;
		this->rating = rating;
	}
							//Individual setter functions that allocates data to class variables
	void setName(string name)
	{
		this->name = name;
	}
	void setPrice(double price)
	{
		this->price = price;
	}
	void setQuantity(int quantity)
	{
		this->quantity = quantity;
	}
	void setGenre(string genre) {
		this->genre = genre;
	}
	void setRating(char rating)
	{
		this->rating = rating;
	}
	void setQuantityLoss(int quantityLoss)
	{
		this->quantityLoss = quantityLoss;
	}
	void setPriceLoss(double priceLoss)
	{
		this->priceLoss = priceLoss;
	}
	void setGameCount(int gameCount)
	{
		this->gameCount = gameCount;
	}
	void setTotalLoss(double totalLoss)
	{
		this->totalLoss = totalLoss;
	}
	void setTotalPay(double totalPay)
	{
		this->totalPay = totalPay;
	}
			//All class getter functions
	string getName()
	{
		return name;
	}
	double getPrice()
	{
		return price;
	}
	int getQuantity()
	{
		return quantity;
	}
	string getGenre()
	{
		return genre;
	}
	char getRating()
	{
		return rating;
	}
	int getQuantityLoss()
	{
		return quantityLoss;
	}
	double getPriceLoss()
	{
		return priceLoss;
	}
	int getGameCount()
	{
		return gameCount;
	}
	double getTotalLoss()
	{
		return totalLoss;
	}
	double getTotalPay()
	{
		return totalPay;
	}
			//Item class prototypes
	void printItemLoss();
	void printGameNumber();
	void printMenu();
	void printTotalLoss(vector<Item> videoGames);
	void printCartTotal(vector<Item> videoGames);
	void printTotalRevenue(vector<Item> videoGames);
	void printManagerQuantity();
	int outputFile(vector<Item>& videoGames);
};

class Cart	//Holds customer cart data
{
private:	//Private data members that hold object data variables
	string purchaseName;	//Name of game customer purchases
	int purchaseQuantity;	//Quantity number customer purchases for each game
	double gameTotal;		//Total price of the individual game times the purchase quantity

public:				//Public data and functions		
	Cart()			//Default consutructor
	{
		purchaseName = "";
		purchaseQuantity = 0;
		gameTotal = 0.0;
	}
					//Additional secondary constructor
	Cart(string purchaseName, int purchaseQuantity, double gameTotal) {
		this->purchaseName = purchaseName;
		this->purchaseQuantity = purchaseQuantity;
		this->gameTotal = gameTotal;
	}
					//All setter function for cart data
	void setAllCartData(string purchaseName, int purchaseQuantity, double gameTotal)
	{
		this->purchaseName = purchaseName;
		this->purchaseQuantity = purchaseQuantity;
		this->gameTotal = gameTotal;
	}
					//Individual setter functions that allocates data to class variables
	void setPurchaseName(string purchaseName)
	{
		this->purchaseName = purchaseName;
	}
	void setPurchaseQuantity(int purchaseQuantity)
	{
		this->purchaseQuantity = purchaseQuantity;
	}
	void setGameTotal(double gameTotal)
	{
		this->gameTotal = gameTotal;
	}
					//All class getter functions
	string getPurchaseName()
	{
		return purchaseName;
	}
	int getPurchaseQuantity()
	{
		return purchaseQuantity;
	}
	double getGameTotal()
	{
		return gameTotal;
	}
					//Cart class prototypes
	void printCustomerNumber(int customerCart);
	void printCustomerCart();
};

					//Function prototypes
void outputLoss(vector<Item> videoGames);
Item gameCreator(ifstream& inFS);
void gamePurchase(vector<Item>& videoGames, vector<Cart> cartData);
void outputCart(vector<Cart> cartData, vector<vector<Cart>> groupCart, vector<Item> videoGames);
Cart cartCreator(string purchaseName, int purchaseQuantity, double gameTotal);
void managerReport(vector<Item> videoGames);
void buyQuantity(vector<Item> videoGames);
void outputInventory(vector<Item> videoGames);
int addGame(vector<Item>& videoGames, ifstream& inFS);

int main()	//Main function for program starting point and execution
{
	ifstream inFS;					//creates input stream to take lines for .txt file
	vector<Item> videoGames;		//vector to hold all videoGame data from .txt file
	vector<Cart> cartData;			//vector to hold customer purchase data

	inFS.open("gameStockData.txt");	//opens .txt file

	if (!inFS.is_open()) //Returns error if file is not open
	{
		cout << "Could not open file gamestockdata.txt." << endl;
		return 1;
	}

	while (!inFS.fail()) //Adds object to vector if file did not fail
	{
		videoGames.push_back(gameCreator(inFS));	//Adds video game data to vector
	}

	if (!inFS.eof()) //Error handling if the file was not read fully
	{
		cout << "Input failure before reaching end of file." << endl;
	}

	inFS.close();	//Closes file

	for (int i = 0; i < videoGames.size() - 1; i++)	//Adds video game data to cart vector
	{
		cartData.push_back(cartCreator(videoGames[i].getName(), 0, 0.0));	//Adds the name of the video game and zero for quantity and price
	}																		//Setters will adjust the quantity and price in gamePurchase function

	//videoGames[0].setQuantity(0); //use to check if out of stock
	//videoGames[1].setQuantity(0); //use to check if out of stock
					//Function calls
	outputInventory(videoGames);
	addGame(videoGames, inFS);
	gamePurchase(videoGames, cartData);	//Calls gamePurchase which asks the user to buy games
	managerReport(videoGames);

	return 0;
}
/*
Allows user to input a new game manually
Paramaters: None
Returns an object
*/
Item inputItemKeyboard() {
	ofstream outFS;		//creates output stream to add lines for .txt file
	ostringstream junk; //String stream to capture garbage
	Item game;			//Creates Item Object
	string name;		//Used to input name of new game
	double price;		//Used to input price of new game
	int quantity;		//Used to input quantity of new game
	string genre;		//Used to input genre of new game
	char rating;		//Used to input rating of new game
				//Outputs to consol and user instantiation
	cout << "Please enter game data" << endl;
	cout << endl << "Name: ";
	cin.ignore();
	getline(cin, name);
	cout << endl << "Price: ";
	cin >> price;
	cout << endl << "Quantity: ";
	cin >> quantity;
	cin.ignore();
	cout << endl << "Genre: ";
	getline(cin, genre);
	cout << endl << "Rating: ";
	cin >> rating;
				
	game.allGameSetters(name, price, quantity, genre, rating); //object calls all game setter function

	//cout << "-" << setfill('-') << setw(40) << "-" << endl; //Line to seperate text for console readability
				//output stream to .txt file
	outFS.open("gameStockData.txt", std::ios_base::app); //opens text file to append data
	outFS << name << endl;
	outFS << price << endl;
	outFS << quantity << endl;
	outFS << genre << endl;
	outFS << rating << endl;
				//string stream to collect extra garbage
	junk << name << endl;
	junk << price << endl;
	junk << quantity << endl;
	junk << genre << endl;
	junk << rating << endl;
	junk.str("");	//clears string stream

	outFS.close();	//closses .txt file

	return game;		//returns object
}
/*
Used to input lines from .txt file
Paramaters: ifstream
Returns an object
*/
Item gameCreator(ifstream& inFS)
{								 
	string name;		//Holds name of game
	double price;		//Price of game
	int quantity;		//Quantity of games
	string genre;		//Game genre
	char rating;		//Game rating
	string junk;		//Clears garbage
	Item game;			//Creates Item Object
				//Input stream to program
	getline(inFS, name); 
	inFS >> price;
	inFS >> quantity;
	getline(inFS, junk);
	getline(inFS, genre);
	inFS >> rating;
	getline(inFS, junk);

	game.allGameSetters(name, price, quantity, genre, rating); 	//Object calls setter function

	return game;		//Returns object
}
/*
Used to set cart data and return object
Parameters: game name, quantity of games, and total of the price of the game
returns an object
*/
Cart cartCreator(string purchaseName, int purchaseQuantity, double gameTotal)
{
	Cart userCart;	//Creats Cart object

	userCart.setAllCartData(purchaseName, purchaseQuantity, gameTotal); //Sets all cart data

	return userCart;	//Returns object
}
/*
Outputs the game inventory as a menu
Parameters: vector of all video games
Returns nothing
*/
void outputInventory(vector<Item> videoGames)
{
	ostringstream outGameNumber; //Output stream for dynamic spacing
	int gameNumber = 1;			 //Used to hold the current game number as a title for each game
	int rightWidth = 0;			 //Dynamic spacing for right side
	int leftWidth = 0;			 //Dynamic spacing or left side
	int odd = 0;				 //Checks if number is odd, used for formatting
						//Header output
	cout << "|" << setfill('-') << setw(117) << right << "|" << endl;
	cout << "|" << setfill(' ') << setw(70) << " - Store Inventory - " << setw(47) << right << "|" << endl;	//Outputs title
	cout << "|" << setfill('-') << setw(117) << right << "|" << endl;
	cout << "|" << setfill(' ') << setw(32) << "Game " << gameNumber << setw(25) << "|";
	gameNumber++;		//Adds one to gameNumber
	cout << "|" << setfill(' ') << setw(27) << "Game " << gameNumber << setw(30) << "|";
	cout << endl << "|" << setw(58) << "|" << "|" << setw(58) << "|" << endl;
	gameNumber = 1;		//Sets gameNumber back to one for correct game number output

	for (int i = 0; i < videoGames.size(); i++)	//Loops through video game vector
	{
		if (odd == 1 && videoGames[i].getName() != "")	//Excecutes if odd variable is odd and video game name index is not empty
		{
			cout << endl << "|" << setfill('-') << setw(58) << "|" << "|" << setw(58) << "|" << endl; //Formatting
			if (videoGames[i].getName() != "")	//Executes if video game name index is not empty 
			{
				outGameNumber.str("");	//Clears string stream
				outGameNumber << "Game " << gameNumber;	//Sets string string
				string strGameNumber = outGameNumber.str();	//Turns string stream into full string
				leftWidth = 26 + strGameNumber.length();	//Sets left width for dynamic spacing
				rightWidth = 32 - strGameNumber.length();	//Sets right width for dynamic spacing

				cout << "|" << setfill(' ') << setw(leftWidth) << strGameNumber << setw(rightWidth) << "|"; //Outputs game number string
				gameNumber++;	//Adds one to gameNumber for correct game number
			}
			if (videoGames[i + 1].getName() != "")	//Executes if next game name index is not empty
			{
				outGameNumber.str("");	//Clears string stream
				outGameNumber << "Game " << gameNumber;	//Sets string string
				string strGameNumber = outGameNumber.str();	//Turns string string into full string
				leftWidth = 22 + strGameNumber.length();	//Sets left width for dynamic spacing
				rightWidth = 36 - strGameNumber.length();	//Sets right width for dynamic spacing

				cout << "|" << setfill(' ') << setw(leftWidth) << strGameNumber << setw(rightWidth) << "|";	//Outputs game number string
			}
			else //Executes if game name index is empty for menu formatting
			{
				cout << "|" << setfill(' ') << setw(28) << " " << setw(30) << "|";
			}

			cout << endl << "|" << setw(58) << "|" << "|" << setw(58) << "|" << endl; //Formatting
			gameNumber--;	//Subtracts one from game number for correct game number
		}

		odd = i % 2;	//Uses modulus on the current index of loop to set number to even or odd

		if (videoGames[i].getName() != "")	//Executes if game name is not empty
		{
			cout << "|";	//Adds for correct menu formatting
			videoGames[i].printMenu();		  //Prints object vector data
		}
		else if (videoGames[i].getName() == "" && gameNumber % 2 != 1) //Executes if game name is empty and gameNumber is not odd for correct formatting
		{
			cout << "|" << setfill(' ') << setw(28) << " " << setw(30) << "|"; //Formatting
		}

		gameNumber++; //Adds one to gameNumber for correct game number
	}

	cout << endl << "|" << setfill('-') << setw(58) << "|" << "|" << setw(58) << "|" << endl << endl; //Formatting
}
/*
Used to add a new game to video game vector
Parameters: video game vector and ifstream
Returns an integer as an exit status
*/
int addGame(vector<Item>& videoGames, ifstream& inFS)
{
	char add;	//Holds user input to enter loop to add games

	cout << "Do you need to add additional games?(y/n): ";
	cin >> add;	//Initilizes variable with user input
	cout << endl;	//Adds new line after user input

	while (add == 'y')	//Iterates until user does not enter 'y'
	{
		system("cls");  //Clears consol, commented out until final version of program
		outputInventory(videoGames);	//Outputs shop inventory and information
		inputItemKeyboard();			//Function that allows user to input game data
		videoGames.clear();				//Clears video game vector
		inFS.open("gameStockData.txt");	//Opens .txt file

		if (!inFS.is_open()) //Returns error if file is not open
		{
			cout << "Could not open file gamestockdata.txt." << endl;
			return 1;	//Returns 1 as an unsuccessful exit status
		}

		while (!inFS.fail()) //Adds object to vector if file did not fail
		{
			videoGames.push_back(gameCreator(inFS));	//Adds video game data to vector
		}

		if (!inFS.eof()) //Error handling if the file was not read fully
		{
			cout << "Input failure before reaching end of file." << endl;
		}

		inFS.close();	//closes .txt file

		system("cls");  //Clears consol, commented out until final version of program
		outputInventory(videoGames);	//Outputs shop inventory and information
		cout << "Do you need to add additional games?(y/n): ";
		cin >> add;	//Re-intilizes variable for loop condition
	}

	return 0;	//Returns 0 a successful exit status
}
/*
Used to purchase a game for customer and set data members
Parameters: video game vector and cart data vector
Returns nothing
*/
void gamePurchase(vector<Item>& videoGames, vector<Cart> cartData) 
{
	double totalPay = 0;	//Holds the total the user must pay
	int index = 0;			//Holds the index of the game
	int numberOfPeople = 0; //Holds the number of people purchasing games
	int gameChoice = 0;	//Used for user game choice selection
	vector<vector<Cart>> groupCart;	//2D vector to hold a vector of each game purchased
	Item output;	//object used to output new game data to .txt file to update store game quantity

	system("cls");  //Clears consol, commented out until final version of program
	cout << endl << "How many people are buying games today?: ";
	cin >> numberOfPeople;	//initilizes with user input
	system("cls");  //Clears consol, commented out until final version of program

	for (int i = 0; i < numberOfPeople; i++)	//loops for a total of the number of customers
	{
		gameChoice = -2;	//Resets gameChoice to enter loop

		for (int i = 0; i < cartData.size(); i++)	//loops through cartData
		{
			cartData[i].setPurchaseQuantity(0);	//Sets purchase quantity back to zero after appending carta data to group cart vector
			cartData[i].setGameTotal(0);		//Sets game total back to zero after appending carta data to group cart vector
		}

		while (gameChoice != -1)	//Runs loop until user enters 0
		{
			outputInventory(videoGames);	//Outputs shop inventory and information

			cout << "Input for Customer " << i + 1 << endl;
			cout << endl << "Current cart total: $" << fixed << setprecision(2) << totalPay << endl;	//Tells user there current cart total
			cout << endl << "Enter the game number the customer would like to purchase (1 - 10 or enter 0 to continue): ";
			cin >> gameChoice;	//Initilizes gameChoice with the choice of the game the user wants
			cout << endl;		//New line after user input for formatting

			index = gameChoice - 1;	//Subtracts one from gameChoice to hold correct index

			if (gameChoice != 0)	//Executes if user did not enter 0 to leave shop
			{
				if (videoGames[index].getQuantity() != 0)	//Executes if game quantity is not zero
				{
					videoGames[index].setQuantity(videoGames[index].getQuantity() - 1);	//Subtracts 1 from quantity
					videoGames[index].setTotalPay(videoGames[index].getTotalPay() + videoGames[index].getPrice()); //Adds game price to totalPay

					for (int i = 0; i < cartData.size(); i++) //Loops through cartData vector
					{
						if (cartData[i].getPurchaseName() == videoGames[index].getName()) //Executes if cartData index game name equals videoGames index game name 
						{
							cartData[i].setPurchaseQuantity(cartData[i].getPurchaseQuantity() + 1); //Adds 1 to purchase quantity
							cartData[i].setGameTotal(cartData[i].getGameTotal() + videoGames[index].getPrice()); //Adds index game price to cartData game total
						}
					}

					totalPay += videoGames[index].getPrice();	//Adds index game price to local totalPay
				}
				else if (videoGames[index].getQuantity() == 0)	//Executes if index game quantity is zero
				{
					videoGames[index].setQuantityLoss(videoGames[index].getQuantityLoss() - 1);	//Subtracts 1 from quantity loss
					videoGames[index].setPriceLoss(videoGames[index].getPriceLoss() + videoGames[index].getPrice()); //Adds index game price to price loss

					cout << endl << "Sorry that game is out of stock" << endl;
					cout << endl << "Press Enter to Continue...";	//Tells user to hit enter, this is so the user can see
					cin.ignore();									//The game is out of stock before the consol clears
					cin.ignore();		//Allows program to wait for user to read consol and press enter to continue
					cout << endl;
				}
			}
			else if (gameChoice == 0) //Runs if user enters 0 for gameChoice
			{
				gameChoice = -1;	//Sets gameChoice to -1 to break out of loops
			}
			system("cls");  //Clears consol, commented out until final version of program
		}

		groupCart.push_back(cartData); //Appends cartaData vector to groupCart vector
	}

	if (numberOfPeople != 0)	//Executes if user does not enter 0 for numberOfPeople
	{
		outputCart(cartData, groupCart, videoGames);	//Outputs cart for customers
		output.outputFile(videoGames);	//Updates .txt file for new game quantity after customer purchase
	}
}
/*
Outputs cart data
Parameters: cartData vector, groupCart vector, videoGames vector
Returns nothing
*/
void outputCart(vector<Cart> cartData, vector<vector<Cart>> groupCart, vector<Item> videoGames)
{
	Item totalPay;			//Creates Item object
	Cart customerNumber;	//Creates Cart object
	int customerCart = 1;	//Used to show the current cart for each customer

	cout << "|" << setw(52) << setfill('-') << "|" << endl; //Formatting

	for (auto& cartData : groupCart)	//Loops through the outer vector groupCart
	{
		customerNumber.printCustomerNumber(customerCart);	//Calls printCustomerNumber for dynamic spacing
		cout << "|" << setw(52) << setfill('-') << "|" << endl;	//Formatting
		for (Cart element : cartData)	//Loops through inner vector cartData
		{
			if (element.getPurchaseQuantity() != 0) //Executes if cartData index purchase quantity is not 0
			{
				element.printCustomerCart(); //Prints each game customer purchased and its data members
			}
		}

		customerCart++; //Adds 1 to customerCart for header
	}

	totalPay.printCartTotal(videoGames);	//Prints the total for each game of every customer
	cout << "|" << setw(52) << setfill('-') << "|" << endl;	//Formatting
}
/*
Outputs the revenue gained, potential revenue loss, and game quantities
Parameters: VideoGames vector
Returns nothing
*/
void managerData(vector<Item> videoGames)
{
	Item manager;	//Creates Item Object

	cout << endl << "|" << setfill('-') << setw(62) << "|" << endl;	//Formatting
	cout << "|" << setfill(' ') << setw(42) << " - Manager Report - " << setw(20) << "|" << endl; //Header

	manager.printTotalRevenue(videoGames);	//Prints total revenue from the day
	outputLoss(videoGames);		//Prints the loss of each game out of stock
						//Header
	cout << "|" << setfill('-') << setw(62) << "|" << endl;	
	cout << "|" << setfill(' ') << setw(42) << " - Quantity in Stock - " << setw(20) << "|" << endl;
	cout << "|" << setfill('-') << setw(62) << "|" << endl;	

	for (int i = 0; i < videoGames.size() - 1; i++) //Loops a total of the size of videoGames vector minus
	{
		manager.printGameNumber(); //Prints gameNumber for dynamic spacing
		videoGames[i].printManagerQuantity();	//Prints quantity of each game
		manager.setGameCount(manager.getGameCount() + 1);	//Adds one to gameCount for game number
	}
}
/*
Used to show manager data, adds security by adding a password, and prompts user if they want to add quantity to games
Parameters: videoGames vector
Returns nothing
*/
void managerReport(vector<Item> videoGames)
{
	string password;	//Holds user input for password
	char dataReport;	//Used for user input to enter data report
	char buyInventory;	//Used for user input to buy more game inventory

	cout << endl << "Press Enter To Continue...";
	cin.ignore();									
	cin.ignore();		//allows program to wait for user to read consol and press enter to continue
	system("cls");  //Clears consol, commented out until final version of program

	cout << endl << "Do you want to see the data report?(y/n): ";
	cin >> dataReport; //Initilizes dataReport with user input

	if (dataReport == 'y') //Executes if dataReport is 'y'
	{
		cout << endl << "Please enter manager password: ";
		cin >> password; //Initilizes password with user input

		if (password == "98765A") //Executes if password is "98765A"
		{
			system("cls");  //Clears consol, commented out until final version of program
			managerData(videoGames); //Prints all manager data
			cout << endl << "Do you need to purchase more inventory?(y/n): ";
			cin >> buyInventory; //Initilizes buyInventory with user input

			if (buyInventory == 'y') //Executes if buyInventory is 'y'
			{
				buyQuantity(videoGames); //Allows user to buy more inventory for games
			}
		}
		else //Executes if user did not enter 'y'
		{
			system("cls");  //Clears consol, commented out until final version of program
			cout << endl << "That was the incorect password, goodbye." << endl;
		}
	}
}
/*
Used to show manager data, adds security by adding a password, and prompts user if they want to add quantity to games
Parameters: videoGames vector
Returns nothing
*/
void outputLoss(vector<Item> videoGames)	//Outputs all the data for games attempted to purchase but out of stock
{														//Takes object vector videoGames and integer count by reference
	Item store;				//Creates Item object
	bool lossCheck = false;	//Used as a flag to print there was no loss
						//Header
	cout << "|" << setw(62) << setfill('-') << "|" << endl;
	cout << "|" << setfill(' ') << setw(51) << " - Profit loss from lack of game stock - " << setw(11) << "|" << endl;
	cout << "|" << setw(62) << setfill('-') << "|" << endl;

	for (int i = 0; i < videoGames.size(); i++)		//Loops through video game vector
	{
		if (videoGames[i].getQuantityLoss() != 0)	//checks if there games attempted for purchase but had zero stock 
		{
			videoGames[i].printItemLoss();		  //Prints object vector data of games that could have been purchased
			lossCheck = true;	//Sets flag to true
		}
	}

	if (lossCheck == true)	//Executes if lossCheck is true
	{
		store.printTotalLoss(videoGames); //prints total loss of every game that could have been sold
	}
	if (lossCheck == false)		//Executes if lossCheck is false
	{							//Footer
		cout << "|" << setfill(' ') << setw(59) << "There was no profit loss due to game stock quantity issues" << setw(3) << "|" << endl;
		cout << "|" << setw(62) << setfill('-') << "|" << endl;
		cout << "|" << setw(62) << setfill(' ') << "|" << endl;
		cout << "|" << setw(62) << "|" << endl;
	}
}
/*
Allows user to purchase more quantity for games
Parameters: videoGames vector
Returns nothing
*/
void buyQuantity(vector<Item> videoGames)
{
	int gameNumber = -1;		//Used for user to select a game	
	int purchaseQuantity;	//Used to hold user input to add to game quantity
	int index = 0;			//Used for vector index
	Item game;				//Creates Item object

	cout << endl << "Which game would you like purchase more stock?(Enter 0 to quit): ";
	cin >> gameNumber;	//Initilizes gameNumber with user input

	while (gameNumber != 0)	//Loops while true
	{
		index = gameNumber - 1;	//Subtracts one from gameChoice to hold correct index

		cout << endl << "How much would you like to buy?: ";
		cin >> purchaseQuantity;	//Initilizes purchaseQuantity with user input

		videoGames[index].setQuantity(videoGames[index].getQuantity() + purchaseQuantity);	//Adds purchase quantity to videoGames index quantity

		cout << endl << videoGames[index].getName() << " - New Quantity: " << videoGames[index].getQuantity() << endl;
		cout << endl << "Press Enter to Continue...";	
		cin.ignore();									
		cin.ignore();	//allows program to wait for user to read consol and press enter to continue
		cout << endl;

		system("cls");  //Clears consol, commented out until final version of program
		managerData(videoGames);	//Outputs all manager data

		cout << endl << "Which game would you like purchase more stock?(Enter 0 to quit): ";
		cin >> gameNumber;	//Initilizes gameNumber with user input
	}

	game.outputFile(videoGames);	//Updates .txt file for new game quantity
}
/*
Replaces .txt file with with videoGames vector data
Parameters: videoGames vector
Returns integer as an exit status
*/
int Item::outputFile(vector<Item>& videoGames)
{
	int i = 0;			//Used for index of videoGames vector
	ofstream outFS;		//Creates output stream to replace data in .txt file
	ostringstream junk; //String stream to hold garbage
	Item game;			//Creates Item Object
	outFS.open("gameStockData.txt");	//Opens .txt file

	if (!outFS.is_open()) //Executes if file does not open
	{
		cout << "Could not open file myoutfile.txt." << endl;
		return 1;	//Returns 1 as an unsuccessful exit status
	}

	for (; i < videoGames.size() - 1; i++) //Loops a total of the videoGames size minus 1
	{			
			//output stream to .txt file
		outFS << videoGames[i].name << endl;
		outFS << videoGames[i].price << endl;
		outFS << videoGames[i].quantity << endl;
		outFS << videoGames[i].genre << endl;
		outFS << videoGames[i].rating << endl;
	}
			//string stream for garbage
	junk << videoGames[i].name << endl;
	junk << videoGames[i].price << endl;
	junk << videoGames[i].quantity << endl;
	junk << videoGames[i].genre << endl;
	junk << videoGames[i].rating;
	junk.str(""); //Clears string stream

	outFS.close(); //Closes .txt file

	return 0; //Returns 0 as a successful exit status
}
/*
Used for dynamic spacing
Parameters: Any string used for ouput, an integer used for spacing alignment
Returns nothing
*/
void printSpacing(string output, int spacingNumber)
{
	int spacing = spacingNumber - output.length();	//Determines amount of spacing necessary

	if (spacing > 0)	//Executes as long as there is sufficient spacing, will reformat gameLabel
	{
		int leftSpacing = spacing / 2;			    //Establishes left spacing length(half of total)
		int rightSpacing = spacing - leftSpacing;   //Establishes right spacing length(total minus half)
		output = string(leftSpacing, ' ') + output + string(rightSpacing, ' '); //Formats string to include left and right spacing
	}

	cout << "|" << setfill(' ') << setw(spacingNumber) << output << "|" << endl; //Prints output with spacing
}
/*
Prints game number with dynamic spacing
Parameters: None
Returns nothing
*/
void Item::printGameNumber()
{
	int spacing = 61;

	ostringstream outGameNumber; //String stream used for dynmaic spacing
	outGameNumber << "  Game " << gameCount << "  ";   //Sets output to ostream
	string gameTitle = outGameNumber.str();			//sets game title to generated string
	printSpacing(gameTitle, spacing);	//Used for dynamic spacing
}
/*
Prints game menu
Parameters: None
Returns nothing
*/
void Item::printMenu()	//Outputs game object data to consol
{
	string rateDef;				//String for rating definition
	ostringstream outGameMenu;  //Output stream that operates on strings
			//If statements for rating type
	if (rating == 'M')
	{
		rateDef = " for Mature.";
	}
	else if (rating == 'T')
	{
		rateDef = " for Teen.";
	}
	else if (rating == 'E')
	{
		rateDef = " for Everyone.";
	}
	//Sets output to ostream
	outGameMenu << name << " - $" << fixed << setprecision(2) << price << " - " << genre << " - Rated " << rating << rateDef; //Initilizes string stream
	string gameMenu = outGameMenu.str();	//Turns string stream into full string
	int width = 57 - gameMenu.length();		//Used for dynamic spacing

	cout << " " << setfill(' ') << gameMenu << setw(width) << "|"; //Prints game menu
}
/*
Prints customer number with dynamic spacing
Parameters: integer that holds the number for the customer cart
Returns nothing
*/
void Cart::printCustomerNumber(int customerCart)
{
	ostringstream outCustomerNumber;		//Output stream for customer number

	outCustomerNumber << " Customer Cart: " << customerCart; //String stream used for dynmaic spacing
	string customerNumber = outCustomerNumber.str();	//Turns string stream into full string
	int width = 52 - customerNumber.length();	//Used for dynamic spacing

	cout << "|" << setfill(' ') << customerNumber << setw(width) << "|" << endl; //Prints customer number
}
/*
Prints customer cart with dynamic spacing
Parameters: None
Returns nothing
*/
void Cart::printCustomerCart()
{
	string customerCart;	//String for each part of customer cart
	ostringstream outCustomerCart;		//Output stream for customer cart

	outCustomerCart << "Game: " << purchaseName;	//String stream used for dynmaic spacing
	customerCart = outCustomerCart.str();	//Turns string stream into full string
	printSpacing(customerCart, 51);		//Used for dynamic spacing

	outCustomerCart.str("");
	outCustomerCart << "Quantity: " << purchaseQuantity;	//String stream used for dynmaic spacing
	customerCart = outCustomerCart.str();	//Turns string stream into full string
	printSpacing(customerCart, 51);		//Used for dynamic spacing

	outCustomerCart.str("");
	outCustomerCart << "Total: $" << fixed << setprecision(2) << gameTotal;	//String stream used for dynmaic spacing
	customerCart = outCustomerCart.str();	//Turns string stream into full string
	printSpacing(customerCart, 51);		//Used for dynamic spacing
	cout << "|" << setw(52) << setfill('-') << "|" << endl;	//Formatting
}
/*
Prints customer cart total with dynamic spacing
Parameters: None
Returns nothing
*/
void Item::printCartTotal(vector<Item> videoGames)
{
	ostringstream outTotalPay;	//Output stream for totalPay
	Item totalPayObject; //Creates Item object

	for (int i = 0; i < videoGames.size(); i++) //Loops total of videoGames vector size
	{
		totalPay += videoGames[i].getTotalPay(); //Adds videoGames total pay index to totalPay data member for each iteration
	}

	outTotalPay << " Cart Total: $" << fixed << setprecision(2) << totalPay;	//String stream used for dynmaic spacing
	string totalPayString = outTotalPay.str();	//Turns string stream into full string
	int width = 52 - totalPayString.length();	//Used for dynamic spacing

	cout << "|" << setfill(' ') << totalPayString << setw(width) << "|" << endl; //Prints totalPayString
}
/*
Prints game loss data with dynamic spacing
Parameters: None
Returns nothing
*/
void Item::printItemLoss()
{
	Item itemLossObject;	//Creates Item object
	string gameItemLoss;	//String for each part of item loss
	ostringstream outItemLoss;		//Output stream for item loss

	outItemLoss << "Title: " << name;	//String stream used for dynmaic spacing
	gameItemLoss = outItemLoss.str();	//Turns string stream into full string
	printSpacing(gameItemLoss, 61);		//Used for dynamic spacing

	outItemLoss.str("");
	outItemLoss << "Quantity Loss: " << quantityLoss;	//String stream used for dynmaic spacing
	gameItemLoss = outItemLoss.str();	//Turns string stream into full string
	printSpacing(gameItemLoss, 61);		//Used for dynamic spacing

	outItemLoss.str("");
	outItemLoss << "Total Price Loss: -$" << fixed << setprecision(2) << priceLoss;	//String stream used for dynmaic spacing
	gameItemLoss = outItemLoss.str();	//Turns string stream into full string
	printSpacing(gameItemLoss, 61);		//Used for dynamic spacing
	cout << "|" << setw(62) << setfill('-') << "|" << endl;	//Formatting
}
/*
Prints total revenue loss with dynamic spacing
Parameters: None
Returns nothing
*/
void Item::printTotalLoss(vector<Item> videoGames)
{
	ostringstream outTotalLoss;		//Output stream for output loss
	Item totalLossObject;	//Creates Item object

	for (int i = 0; i < videoGames.size(); i++)	//Loops total of videoGames vector size
	{
		totalLoss += videoGames[i].getPriceLoss();	//Adds videoGames price loss index to totalPay data member for each iteration
	}

	outTotalLoss << "Total Overall Loss: -$" << fixed << setprecision(2) << totalLoss;	//String stream used for dynmaic spacing
	string totalLoss = outTotalLoss.str();	//Turns string stream into full string
	printSpacing(totalLoss, 61);	//Used for dynamic spacing
	cout << "|" << setfill('-') << setw(62) << "|" << endl;	//Formatting
	cout << "|" << setfill(' ') << setw(62) << "|" << endl;	//Formatting
	cout << "|" << setw(62) << "|" << endl;	//Formatting
}
/*
Prints total revenue gain with dynamic spacing
Parameters: None
Returns nothing
*/
void Item::printTotalRevenue(vector<Item> videoGames)
{
	ostringstream outTotalRevenue;	//Output stream for total revenue
	Item manager;	//Creates Item object

	for (int i = 0; i < videoGames.size(); i++)	//Loops total of videoGames vector size
	{
		totalPay += videoGames[i].getTotalPay();	//Adds videoGames total pay index to totalPay data member for each iteration
	}

	outTotalRevenue << "Total Revenue From The Day: $" << fixed << setprecision(2) << totalPay;	//String stream used for dynmaic spacing
	string gameTotalRevenue = outTotalRevenue.str();	//Turns string stream into full string
					//Footer
	cout << "|" << setfill('-') << setw(62) << "|" << endl;
	printSpacing(gameTotalRevenue, 61);	//Used for dynamic spacing
	cout << "|" << setfill('-') << setw(62) << "|" << endl;
	cout << "|" << setfill(' ') << setw(62) << "|" << endl;
	cout << "|" << setw(62) << "|" << endl;
}
/*
Prints video game quantity with dynamic spacing
Parameters: None
Returns nothing
*/
void Item::printManagerQuantity()
{
	ostringstream outManagerData; //Output stream for game title

	outManagerData << name << " - Quantity: " << quantity;	//String stream used for dynmaic spacing
	string managerData = outManagerData.str();	//Turns string stream into full string
	printSpacing(managerData, 61);	//Used for dynamic spacing
	cout << "|" << setfill('-') << setw(62) << "|" << endl;	//Formatting
}


/*
Problems: I had many problems on this part of the project. Most notably making the menu two columns was probably the most difficult.
There was a series of small issues that I solved quickly, most of those issues consited of having problems with setters
and other small UI bugs. Something I still haven't figured out, is when I try to add a new game
or update the quantity for the games from the manager report and buy quantity functions the program wants to add
a couple of lines of garbage to the .txt file. I found a workaround for this which consisted of me creating a stringstream and
using it to take in the garbage and then clearing the stringstream. I know we talked a little bit about it when
we met up on teams in private. I'm not sure why it's happening but the workaround at least solves the issue
even if it isn't the best way of solving the bug. Also I know the manager report is kind of long when it outputs
to the console. I will try and fix this before the end of next week/end of the semester if I have time. I wanted to
submit this now to at least get early feedback if there is anything else I need to fix before the deadline and also
get points back from earlier submissions, particularly because I got an automatic zero from having that break
statement outside of a switch/if condition.
*/