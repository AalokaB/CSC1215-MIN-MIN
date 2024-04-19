/*
//// Last Build : date of submission
//// Compiler   : VS2022
//// Programmer : Chong Min Kee
//// Capability : Implementing a variable size record.
//// Function   : add, search, delete, modify, display records
*/


/////////////     Includes    /////////////

#include <cstdlib> // system()
#include <conio.h> // getch()
#include <fstream>
#include <sys\stat.h> // stat(status of a file)
#include <iostream>
#include <string>
#include<regex>
#include <iostream>
using namespace std;


/////////////     Data types    /////////////
int RegistrationID = 1000;
int searCustomerID;

struct Customer_Record // Customer record; is the structName
{
	//define all variables after this line
	//30th january 2024
	int RegistrationID;
	string Name;
	string Nationality;
	string ICNumber;
	string BirthDate;
	string PassportNumber;
	string ExpiryDate;
	int Age;
	string Gender;
	string EmailAddress;
	string PhoneNumber;
	string Journey;
	int Day;
	int Month;
	int Year;
	int FirstFlightDay;
	int FirstFlightMonth;
	int FirstFlightYear;
	int SecondFlightDay;
	int SecondFlightMonth;
	int SecondFlightYear;
	string Seat;

	//Don't touch after this line
	bool deleted;
};


/////////////     Variable Declarations & Constants /////////////

#define CUSTOMER_FILE_NAME "Customers.txt" // name of the database file to store Customers informations

Customer_Record Customer; //variable declaration of Customer
char     choice; // for choice in menu
fstream* fs = NULL, * fs1 = NULL;// file streams for files : fs -> 'Customer', fs1 -> 'temp'
bool     deletion = false; // if any record has been deleted


/////////////     Function Prototypes    /////////////

void closeFile(fstream*); // closes a file with its pointer, then deletes the file pointer
bool isFileExist(const char*); // check if a file exists

// Function prototypes
bool isValidEmail(const string& email);
//...

//Function to validate email address
bool isValidEmail(const string& email)
{
	//Regular expression to validate email address
	const regex pattern(R"(([^@\s]+)@((?:[-a-z0-9]+\.)+[a-z]{2,}))");
	return regex_match(email, pattern);
}


/////////////     Main    /////////////
int main()
{
    system("color 1");
	ifstream input;
	input.open("id.txt"), ios::in;
	input >> RegistrationID;
	ofstream output;

	while (true)
	{
		do ////// Menu //////
		{
			system("cls"); // clear screen
			mainmenu:
			cout << "\n    < Customers Database > \n\n";
			cout << "(1) Add     a new Record \n";
			cout << "(2) Search an existing Record\n";
			cout << "(3) Update an existing Record\n";
			cout << "(4) Delete an existing Record \n";
			cout << "(5) Display Records \n";
			cout << "(6) Exit \n\n";
			cout << " Enter a choice (1-5) : " << flush;
			choice = _getch();
		} while (choice < '1' || choice > '6'); // while we have no good(between 1 and 5), show menu again

		system("cls");

		// to modify, delete or display records, database file should exist, then we have some records           
		if (choice == '2' || choice == '3' || choice == '4' || choice == '5')
		{
			if (!isFileExist(CUSTOMER_FILE_NAME)) // if database file doesn't exist
			{
				cout << "\n Database file ('" << CUSTOMER_FILE_NAME << "') doesn't exist, then there are no records." << endl;
				system("pause");
				continue; // show the menu again
			}
		}

		switch (choice)
		{
			long long int recs_num; // number of records before the record for modifying(deletion)
			int CustomerRegistrationID;

		case '1': ////// Add Record //////

			cout << "\n\t\t < Entering a new record > ";
			cout << "\n   Enter the following informations for the new record : ";
			Customer.RegistrationID = ++RegistrationID;
			cout << "\nRegistrationID    :" << Customer.RegistrationID << endl;
			if (output.open("id.txt"), ios::out)
			{
				output << RegistrationID;
			}
			else
				cout << "the file is empty.";
			output.close();
			cout << endl;

			cout << "1) Name:";
			getline(cin, Customer.Name);//getline only for string data type
			while (Customer.Name.find_first_of("qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM") == string::npos)
			{
				cout << "\nInvalid Input!Please Enter In A Valid Name!" << endl;
				cout << "Name :";
				getline(cin, Customer.Name);
			}

			cout << "---------------------------------------------------------------------" << endl;

			cout << "2) Nationality:"<<"\n";
			cout << "(1)Malaysian" << endl;
			cout << "(2)Non-Malaysian" << endl;
			cout << "Enter A Choice(1/2):";
			cin >> Customer.Nationality;

			while ((Customer.Nationality != "1") && (Customer.Nationality != "2"))
			{
				cout << "Invalid!Please Enter Again!" << endl;
				cout << "Enter A Choice(1/2):";
				cin >> Customer.Nationality;
			}

			if (Customer.Nationality == "1")
			{
				Customer.Nationality = "Malaysian";
				cout << "Nationality:" << Customer.Nationality << endl;
				cout << "ICNumber" << "(Ex.000000-00-0000):";
				cin >> Customer.ICNumber;

				if (Customer.ICNumber[11] % 2 == 0)//Even number
					cout << "Gender: Female";
				else//Odd number
					cout << "Gender: Male";
				cout << endl;

				Customer.BirthDate = Customer.ICNumber.substr(4, 2) + "/" + Customer.ICNumber.substr(2, 2) + "/" + Customer.ICNumber.substr(0, 2);

				cout << "BirthDate :" << Customer.BirthDate << endl;
			}

			else if (Customer.Nationality == "2")
			{
				Customer.Nationality = "Non-Malaysian";
				cout << "Nationality:" << Customer.Nationality << endl;
				cout << "Passport Number" << "(Ex.A123456):";
				cin >> Customer.PassportNumber;

				while ((Customer.PassportNumber.size() != 10) || (Customer.PassportNumber.find_first_of("1234567890") == string::npos))
				{
					cout << "\nInvalid Input!Please Enter In A Valid Passport Number!" << endl;
					cout << "Passport Number :";
					cin >> Customer.PassportNumber;

				}
				cout << "Expiry Date :";
				cin >> Customer.ExpiryDate;
				cout << "Age :";
				cin >> Customer.Age;
				cout << "Gender :";
				cin >> Customer.Gender;
				cout << endl;
			}

			cout << "---------------------------------------------------------------------" << endl;

			cout << "3)Email Address:";
			cin >> Customer.EmailAddress;
			while (!isValidEmail(Customer.EmailAddress))
			{
				cout << "Invalid Email Address!Please Enter A Valid Email Address:";
				cin >> Customer.EmailAddress;
			}

			cout << "---------------------------------------------------------------------" << endl;

			cout << "4) Phone Number:";
			cin >> Customer.PhoneNumber;
			while ((Customer.PhoneNumber.size() != 10) || (Customer.PhoneNumber.find_first_of("0123456789") == string::npos))
			{
				cout << "\nInvalid Input!Please Enter In A Valid Phone Number!" << endl;
				cout << "Phone Number:";
				cin >> Customer.PhoneNumber;

			}
			cout << "---------------------------------------------------------------------" << endl;

			cout << "5)Journey:" << endl;
			cout << "(1)One Way" << endl;
			cout << "(2)Round Trip" << endl;
			cout << "Enter A Choice(1/2):";
			cin >> Customer.Journey;

			while ((Customer.Journey != "1") && (Customer.Journey != "2"))
			{
				cout << "Invalid!Please enter again!" << endl;
				cout << "Enter A Choice(1/2):";
				cin >> Customer.Journey;
			}

			if (Customer.Journey == "1")
			{
				Customer.Journey = "One Way";
				cout << "Journey:" << Customer.Journey << endl;
				cout << "DateOfBooking(DD-MM-YYYY)" << endl;
				cout << "Enter Your Flight Date" << endl;
				cout << "Day:";
				cin >> Customer.Day;
				cout << "Month";
				cin >> Customer.Month;
				cout << "Year";
				cin >> Customer.Year;

				cout << "DateOfBooking:" << Customer.Day << "/" << Customer.Month << "/" << Customer.Year << endl;
			}

			if (Customer.Journey == "2")
			{
				Customer.Journey = "Round Trip";
				cout << "Journey:" << Customer.Journey << endl;
				cout << "DateOfFirstFlightBooking(DD-MM-YYYY)" << endl;
				cout << "Enter Your First Flight Date" << endl;
				cout << "Day:";
				cin >> Customer.FirstFlightDay;
				cout << "Month";
				cin >> Customer.FirstFlightMonth;
				cout << "Year";
				cin >> Customer.FirstFlightYear;

				cout << "DateOfSecondFlightBooking(DD-MM-YYYY)" << endl;
				cout << "Enter Your Second Flight Date" << endl;
				cout << "Day:";
				cin >> Customer.SecondFlightDay;
				cout << "Month";
				cin >> Customer.SecondFlightMonth;
				cout << "Year";
				cin >> Customer.SecondFlightYear;

				cout << "FirstFlight:" << Customer.FirstFlightDay << "/" << Customer.FirstFlightMonth << "/" << Customer.FirstFlightYear << endl;
				cout << "SecondFlight:" << Customer.SecondFlightDay << "/" << Customer.SecondFlightMonth << "/" << Customer.SecondFlightYear << endl;
			}

			cout << "---------------------------------------------------------------------" << endl;

			cout << "6)Seat:" << endl;
			cout << "(1)First Class" << endl;
			cout << "(2)Business Class" << endl;
			cout << "(3)Economy Class" << endl;
			cout << "Enter A Chioce:";
			cin >> Customer.Seat;

			while ((Customer.Seat != "1") && (Customer.Seat != "2") && (Customer.Seat != "3"))
			{
				cout << "Invalid!Please enter again!" << endl;
				cout << "Enter A Choice(1/2/3):";
				cin >> Customer.Seat;
			}
			if (Customer.Seat == "1")
			{
				Customer.Seat = "First Class";
				cout << "Seat:" << Customer.Seat << endl;
			}
			if (Customer.Seat == "2")
			{
				Customer.Seat = "Business Class";
				cout << "Seat:" << Customer.Seat << endl;
			}
			if (Customer.Seat == "3")
			{
				Customer.Seat = "Economy Class";
				cout << "TypeOfSeat:" << Customer.Seat << endl;
			}


			//Don't touch after this line
			Customer.deleted = 0;

			fs = new fstream(CUSTOMER_FILE_NAME, ios::out | ios::app | ios::binary);

			if (!fs)
			{
				cout << "\n Can't open or create '" << CUSTOMER_FILE_NAME << "' file" << endl;
				system("pause");
				break;
			}

			fs->write((char*)&Customer, sizeof(Customer));

			closeFile(fs);

			cout << "\n Record added." << endl;
			system("pause");

			break;

		case '2': ////// Search Record //////

			system("cls");
			cout << "\n";
			cout << "\n";
			cout << "\t#New Customer Registration#" << endl;
			cout << "\t#For Flight Ticket Registration#" << endl;
			cout << "\t#Search Record#" << endl;

			cout << "\n";
			cout << "\n";
			cout << "\nEnter Customer ID that you search:";
			cin >> searCustomerID;
			cin.ignore();

			fs = new fstream(CUSTOMER_FILE_NAME, ios::in | ios::binary);

			if (!fs)
			{
				cout << "\n Can't open or create" << CUSTOMER_FILE_NAME << "' file" << endl;
				system("pause");
				break;
			}

			recs_num = -1;
			while (fs->read((char*)&Customer, sizeof(Customer)))
			{
				recs_num++;

				if (searCustomerID == Customer.RegistrationID && !Customer.deleted)/*if user deleted an customer then added another
				one with the same ID in the same instance of program runs, deleted customer is still there, then we should go
				through all the file*/
					break;
			}

			if (fs->eof())//if(the record is not in the file || it's there but it's deleted
			{
				cout << "\nYour specified Customer doesn't exist in file." << endl;
				closeFile(fs);
				system("pause");
				goto mainmenu;
				break;
			}

			fs->seekp(sizeof(Customer) * recs_num, ios::beg);//go to the searched

			fs->read((char*)&Customer, sizeof(Customer));//display the searched record

			if (!Customer.deleted)
			{
				cout << "\n";
				cout << "Registration ID :" << Customer.RegistrationID << "\n";
				cout << "Name :" << Customer.Name << "\n";
				if (Customer.Nationality == "1")
				{
					cout << "Nationality :" << Customer.Nationality << endl;
					cout << "ICNumber" << "(Ex.000000-00-0000)" << Customer.ICNumber;

					if (Customer.ICNumber[11] % 2 == 0)//Even number
						cout << "Gender: Female";
					else//Odd number
						cout << "Gender: Male";
					cout << endl;

					Customer.BirthDate = Customer.ICNumber.substr(4, 2) + "/" + Customer.ICNumber.substr(2, 2) + "/" + Customer.ICNumber.substr(0, 2);

					cout << "BirthDate :" << Customer.BirthDate << endl;
				}

				else if (Customer.Nationality == "2")
				{
					Customer.Nationality = "Non-Malaysian";
					cout << "Nationality :" << Customer.Nationality << endl;
					cout << "Passport Number" << "(Ex.A123456):" << Customer.PassportNumber;
					cout << "Expiry Date :" << Customer.ExpiryDate << "\n";
					cout << "Age :" << Customer.Age << "\n";
					cout << "Gender" << Customer.Gender << "\n";
				}

				cout << "Email Address :" << Customer.EmailAddress << "\n";
				cout << "Phone Number :" << Customer.PhoneNumber << "\n";

				if (Customer.Journey == "1")
				{
					cout << "DateOfBooking:" << Customer.Day << "/" << Customer.Month << "/" << Customer.Year << endl;
				}

				else if (Customer.Journey == "2")
				{
					cout << "Date Of First Flight Booking:" << "\n" << Customer.FirstFlightDay << "/" << Customer.FirstFlightMonth << "/" << Customer.FirstFlightYear << endl;
					cout << "Date Of Second Flight Booking:" << "\n" << Customer.SecondFlightDay << "/" << Customer.SecondFlightMonth << "/" << Customer.SecondFlightYear << endl;
				}

				cout << "TypeOfSeat:" << Customer.Seat << "\n";
			}

			cout << "\n To return to menu";
				system("pause");
				closeFile(fs);
			goto mainmenu;
			break;



		case '3': ////// Modify Record //////

			system("cls");
			cout << "\t#New Customer  Registration#" << endl;
			cout << "\t#For Flight Ticket Registration#" << endl;
			cout << "\t#Modify Record#" << endl;
			cout << "\n Enter Customer ID, that you want modify its information : ";
			cin >> searCustomerID;

			fs = new fstream(CUSTOMER_FILE_NAME, ios::in | ios::out | ios::binary);

			if (!fs)
			{
				cout << "\n Can't open or create '" << CUSTOMER_FILE_NAME << "' file" << endl;
				system("pause");

				break;
			}

			recs_num = -1;

			while (fs->read((char*)&Customer, sizeof(Customer)))
			{
				recs_num++;

				if (searCustomerID == Customer.RegistrationID && !Customer.deleted)/*if user deleted an customer then added another  one with the same ID in the same instance of program runs,
		delected customer is still here, then we should go thbrough all this file*/
					break;
			}

			if (fs->eof()) // if (the record is not in the file || it's there but it's deleted)
			{
				cout << "\n Your specified Customer doesn't exist in file." << endl;
				closeFile(fs);
				system("pause");
				goto mainmenu;
				break;
			}
		UpdateList:

			cout << "Select specific record to update:\n";
			cout << "1.Name :" << Customer.Name << "\n";

			if (Customer.Nationality == "1")
			{
				cout << "2.Nationality :Malaysian" << "\n";
				cout << "3.IC Number :" << Customer.ICNumber << "\n";//IC Number will detect the Gender and birthdate

			}
			else
			{
				cout << "2.Nationality :Non-malaysian" << "\n";
				cout << "4.Passport Number :" << Customer.PassportNumber << "\n";
				cout << "5.Expiry Date:" << Customer.ExpiryDate << "\n";
				cout << "6.Age :" << Customer.Age << "\n";
				cout << "7.Gender :" << Customer.Gender << "\n";
			}

			cout << "7.Email Address :" << Customer.EmailAddress << "\n";
			cout << "8.Phone Number " << Customer.PhoneNumber << "\n";
			cout << "9.Journey" << Customer.Journey << "\n";

			if (Customer.Journey == "1")
			{
				cout << "10.DateOfBooking:" << Customer.Day << "/" << Customer.Month << "/" << Customer.Year << endl;
			}

			else if (Customer.Journey == "2")
			{
				cout << "11.Date Of First Flight Booking:" << "\n" << Customer.FirstFlightDay << "/" << Customer.FirstFlightMonth << "/" << Customer.FirstFlightYear << endl;
				cout << "12.Date Of Second Flight Booking:" << "\n" << Customer.SecondFlightDay << "/" << Customer.SecondFlightMonth << "/" << Customer.SecondFlightYear << endl;
			}

			cout << "11.Type Of Seat :" << Customer.Seat << "\n";

			fs->seekp(sizeof(Customer) * recs_num, ios::beg); // go to the first of the record to be modified
			fs->write((char*)&Customer, sizeof(Customer));

			closeFile(fs);

			cout << "\n Record is modified." << endl;
			system("pause");
			closeFile(fs);
			goto mainmenu;
			break;


		case '4': ////// Delete Record //////

			cout << "\t#New Customer  Registration#" << endl;
			cout << "\t#For Booking Flight Ticket Registration#" << endl;
			cout << "\t#Delete Record#" << endl;

			cout << "\n Enter Customer ID that you want to delete for its information : ";
			cin >> searCustomerID;
			cin.ignore();

			fs = new fstream(CUSTOMER_FILE_NAME, ios::in | ios::out | ios::binary);

			if (!fs)
			{
				cout << "\n Can't open or create '" << CUSTOMER_FILE_NAME << "' file." << endl;
				system("pause");
				break;
			}

			recs_num = -1;

			while (fs->read((char*)&Customer, sizeof(Customer)))
			{
				recs_num++;

				if (Customer.RegistrationID == Customer.RegistrationID && !Customer.deleted) // if user deleted an Customer then added another one with the same ID in the same instance of program runs, deleted Customer is still there, then we should go through all the file
					break;
			}

			if (fs->eof()) // if (the record is not in the file || it's there but it's deleted)
			{
				cout << "\n Your specified Customer doesn't exist in database file." << endl;
				closeFile(fs);
				system("pause");
				break;
			}

			Customer.deleted = 1;

			fs->seekp(sizeof(Customer) * recs_num, ios::beg);
			fs->write((char*)&Customer, sizeof(Customer));

			closeFile(fs);

			deletion = true; // we have some deleted records
			cout << "\n Record is deleted." << endl;

			system("pause");
			goto mainmenu;
			break;


		case '5': // Display Records

			cout << "\t#New Customer  Registration#" << endl;
			cout << "\t#For Booking Flight Ticket Office#" << endl;
			cout << "\t#Display Record#" << endl;


			fs = new fstream(CUSTOMER_FILE_NAME, ios::in | ios::binary);

			if (!fs)
			{
				cout << "\n Can't open or create '" << CUSTOMER_FILE_NAME << "' file." << endl;
				system("pause");
				break;
			}

			while (fs->read((char*)&Customer, sizeof(Customer))) // display records
			{
				if (!Customer.deleted)
				{
					cout << "\n";
					cout << "Registration ID :" << Customer.RegistrationID << "\n";
					cout << "Name :" << Customer.Name << "\n";
					if (Customer.Nationality == "1")
					{
						cout << "Nationality :" << Customer.Nationality << endl;
						cout << "ICNumber" << "(Ex.000000-00-0000)" << Customer.ICNumber;

						if (Customer.ICNumber[11] % 2 == 0)//Even number
							cout << "Gender: Female";
						else//Odd number
							cout << "Gender: Male";
						cout << endl;

						Customer.BirthDate = Customer.ICNumber.substr(4, 2) + "/" + Customer.ICNumber.substr(2, 2) + "/" + Customer.ICNumber.substr(0, 2);

						cout << "BirthDate :" << Customer.BirthDate << endl;
					}

					else if (Customer.Nationality == "2")
					{
						Customer.Nationality = "Non-Malaysian";
						cout << "Nationality :" << Customer.Nationality << endl;
						cout << "Passport Number" << "(Ex.A123456):" << Customer.PassportNumber;
						cout << "Expiry Date :" << Customer.ExpiryDate << "\n";
						cout << "Age :" << Customer.Age << "\n";
						cout << "Gender" << Customer.Gender << "\n";
					}

					cout << "Email Address :" << Customer.EmailAddress << "\n";
					cout << "Phone Number :" << Customer.PhoneNumber << "\n";

					if (Customer.Journey == "1")
					{
						cout << "DateOfBooking:" << Customer.Day << "/" << Customer.Month << "/" << Customer.Year << endl;
					}

					else if (Customer.Journey == "2")
					{
						cout << "Date Of First Flight Booking:" << "\n" << Customer.FirstFlightDay << "/" << Customer.FirstFlightMonth << "/" << Customer.FirstFlightYear << endl;
						cout << "Date Of Second Flight Booking:" << "\n" << Customer.SecondFlightDay << "/" << Customer.SecondFlightMonth << "/" << Customer.SecondFlightYear << endl;
					}

					cout << "TypeOfSeat:" << Customer.Seat << "\n";

				}

			}

			////// Print Flight Ticket records...

			cout << "\n To see menu, ";
			system("pause");
			closeFile(fs);
			goto mainmenu;
			break;

		case '6': // Exit

			if (deletion) // if there is any deletion, then update database file (create a new temp file that doesn't have deleted records, then remove the old database file and rename temp file to database file name)
			{
				cout << "\n Updating '" << CUSTOMER_FILE_NAME << "' File..." << endl;

				fs = new fstream(CUSTOMER_FILE_NAME, ios::in | ios::binary);
				if (!fs)
				{
					cout << "\n Can't open '" << CUSTOMER_FILE_NAME << "' file, then Updating is incomplete." << endl;
					system("pause");

					system("cls");
					return 1;
				}

				fs1 = new fstream("temp", ios::out | ios::binary);
				if (!fs1)
				{
					cout << "\n Can't create temp file, then Updating is incomplete." << endl;
					system("pause");

					closeFile(fs);
					system("cls");
					return 1;
				}

				// write nondeleted records to the temp file
				while (fs->read((char*)&Customer, sizeof(Customer)))
					if (!Customer.deleted)
						fs1->write((char*)&Customer, sizeof(Customer));

				closeFile(fs);
				closeFile(fs1);

				if (remove(CUSTOMER_FILE_NAME) == -1) // if there is an error
				{
					cout << "\n Can't delete '" << CUSTOMER_FILE_NAME << "' file, then Updating is incomplete." << endl;
					system("pause");

					system("cls");
					return 1;
				}


				struct stat st; // to check size of the temp file
				int res = stat("temp", &st);

				if (st.st_size == 0) // if all of records are deleted then the temp file size is zero                        
					remove("temp"); // we have no records, then no database file is needed, just delete the temp file
				else
					if (rename("temp", CUSTOMER_FILE_NAME))
					{
						cout << "\n Can't rename temp file, then Updating is incomplete." << endl;
						system("pause");

						system("cls");
						return 1;
					}

				cout << "\n Updating database file completed." << endl;
				system("pause");
			}

			//Exit Splash Screen
			system("cls");
			cout << "\n";
			cout << "\t*This registration system*" << endl;
			cout << "\t*is created by*" << endl;
			cout << "\t*Chong Min Kee*" << endl;
			cout << "\t*Hope To See Ypu Again*" << endl;
			cout << "\t*Have A Nice Day.Goodbye!";
			return 0;

			break;
		} // end 'switch'
	} // end 'while'

	return 0;
} // end 'main()'


/////////////     Function Definitions    /////////////

void closeFile(fstream* fs)
{
	fs->close(); // close the file
	delete fs;
	fs = NULL;
}


bool isFileExist(const char* file_name)
{
	struct stat st; // to check status of file
	int res = stat(file_name, &st);
	return (res == 0); // if file exists     
}