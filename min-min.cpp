/***
//// Last Build : date of submission
//// Compiler   : VS2022
//// Programmer : Chong Min Kee
//// Capability : Implementing a variable size record.
//// Function   : add, search, delete, modify, display records
***/


/////////////     Includes    /////////////

#include <cstdlib> // system()
#include <conio.h> // getch()
#include <fstream>
#include <sys\stat.h> // stat(status of a file)
#include <iostream>
#include <string>
#include<regex>
#include<stdio.h>
using namespace std;


/////////////     Data types    /////////////
int RegistrationID = 1000;
int searCustomerID;

struct Passenger_Record // Passenger record; is the structName
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

#define PASSENGER_FILE_NAME "Passenger.txt" // name of the database file to store Passenger informations

Passenger_Record Passenger; //variable declaration of Passenger
char     choice; // for choice in menu
fstream* fs = NULL, * fs1 = NULL;// file streams for files : fs -> 'Passenger', fs1 -> 'temp'
bool     deletion = false; // if any record has been deleted


/////////////     Function Prototypes    /////////////

void closeFile(fstream*); // closes a file with its pointer, then deletes the file pointer
bool isFileExist(const char*); // check if a file exists

// Function prototypes
bool isValidEmail(const string& email);
bool isValidNumber(const string& number);
//...

//Function to validate email address
bool isValidEmail(const string& email)
{
	//!Regular expression to validate email address
	const regex pattern(R"(([^@\s]+)@((?:[-a-z0-9]+\.)+[a-z]{2,}))");
	return regex_match(email, pattern);
}

//Function to validate number
bool isValidNumber(const string& number)
{
	//! Regular expression to validate phone number
	const regex pattern(R"(\d{10})");
	return regex_match(number, pattern);
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
			cout << "\t\t\t\t\t    Welcome To Malaysia Airlines  \n\n" << endl;
			cout << "\n";
			cout << "\t\t\t\t\t             Main Menu              " << endl;
			cout << "\t\t\t\t\t____________________________________" << endl;
			cout << "\t\t\t\t\t\t< Passenger Database > \n\n";
			cout << "\t\t\t\t           (1) Add     a new Record \n";
			cout << "\t\t\t\t           (2) Search an existing Record\n";
			cout << "\t\t\t\t           (3) Update an existing Record\n";
			cout << "\t\t\t\t           (4) Delete an existing Record \n";
			cout << "\t\t\t\t           (5) Display Records \n";
			cout << "\t\t\t\t           (6) Exit \n\n";
			cout << "\t\t\t\t           Enter a choice (1-6) : " << flush;
			choice = _getch();
		} while (choice < '1' || choice > '6'); // while we have no good(between 1 and 5), show menu again

		system("cls");

		// to modify, delete or display records, database file should exist, then we have some records           
		if (choice == '2' || choice == '3' || choice == '4' || choice == '5')
		{
			if (!isFileExist(PASSENGER_FILE_NAME)) // if database file doesn't exist
			{
				cout << "\n\t\t\t\t\tDatabase file ('" << PASSENGER_FILE_NAME << "') doesn't exist, then there are no records." << endl;
				system("pause");
				continue; // show the menu again
			}
		}

		switch (choice)
		{
			long long int recs_num; // number of records before the record for modifying(deletion)
			int PassengerRegistrationID;

		case '1': ////// Add Record //////

			system("cls");
			cout << "\t\t\t\t\t    Welcome To Malaysia Airlines  \n" << endl;
			cout << "\t\t\t\t\t____________________________________" << endl;
			cout << "\n";
			cout << "\t\t\t\t---------------------------------------------------";
			cout << "\n\t\t\t\t|" << "           #New Passenger Registration#" << "           |" << endl;
			cout << "\t\t\t\t|" << "           #For Flight Ticket Registration#" << "      |" << endl;
			cout << "\t\t\t\t|" << "           #Add Record#" << "                          |" << endl;
			cout << "\t\t\t\t---------------------------------------------------";
			cout << "\n";
			cout << "\n";

			cout << "\t\t\t\t\t\t< Entering a new record > ";
			cout << "\n\t\t\t\tEnter the following informations for the new record : ";
			Passenger.RegistrationID = ++RegistrationID;
			cout << "\n\t\t\t\t\tRegistrationID    :" << Passenger.RegistrationID << endl;
			if (output.open("id.txt"), ios::out)
			{
				output << RegistrationID;
			}
			else
				cout << "\t\t\t\t\tthe file is empty.";
			output.close();
			cout << endl;

			cout << "\t\t\t\t\t1) Name:";
			getline(cin, Passenger.Name);//getline only for string data type
			while (Passenger.Name.find_first_of("qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM") == string::npos)
			{
				cout << "\n\t\t\t\tInvalid Input!Please Enter In A Valid Name!" << endl;
				cout << "\t\t\t\t\tName :";
				getline(cin, Passenger.Name);
			}

			cout << "\t\t\t---------------------------------------------------------------------" << endl;

			cout << "\t\t\t\t\t2) Nationality:" << "\n";
			cout << "\t\t\t\t\t(1)Malaysian" << endl;
			cout << "\t\t\t\t\t(2)Non-Malaysian" << endl;
			cout << "\t\t\t\t\tEnter A Choice(1/2):";
			cin >> Passenger.Nationality;

			while ((Passenger.Nationality != "1") && (Passenger.Nationality != "2"))
			{
				cout << "\n\t\t\t\t\tInvalid!Please Enter Again!" << endl;
				cout << "\t\t\t\t\tEnter A Choice(1/2):";
				cin >> Passenger.Nationality;
			}

			if (Passenger.Nationality == "1")
			{
				Passenger.Nationality = "Malaysian";
				cout << "\n\t\t\t\t\tNationality:" << Passenger.Nationality << endl;
				cout << "\t\t\t\t\tICNumber" << "(Ex.000000-00-0000):";
				cin >> Passenger.ICNumber;

				if (Passenger.ICNumber[11] % 2 == 0)//Even number
					cout << "\t\t\t\t\tGender : Female";
				else//Odd number
					cout << "\t\t\t\t\tGender : Male";
				cout << endl;

				Passenger.BirthDate = Passenger.ICNumber.substr(4, 2) + "/" + Passenger.ICNumber.substr(2, 2) + "/" + Passenger.ICNumber.substr(0, 2);

				cout << "\t\t\t\t\tBirthDate :" << Passenger.BirthDate << endl;
			}

			else if (Passenger.Nationality == "2")
			{
				Passenger.Nationality = "Non-Malaysian";
				cout << "\n\t\t\t\t\tNationality:" << Passenger.Nationality << endl;
				cout << "\t\t\t\t\tPassport Number :" << "(Ex.A123456):" ;
				cin >> Passenger.PassportNumber;

				while ((Passenger.PassportNumber.size() != 10) || (Passenger.PassportNumber.find_first_of("1234567890") == string::npos))
				{
					cout << "\n\t\t\t\tInvalid Input!Please Enter In A Valid Passport Number!" << endl;
					cout << "\t\t\t\t\tPassport Number :";
					cin >> Passenger.PassportNumber;

				}
				cout << "\t\t\t\t\tExpiry Date :";
				cin >> Passenger.ExpiryDate;
				cout << "\t\t\t\t\tAge :";
				cin >> Passenger.Age;
				cout << "\t\t\t\t\tGender :";
				cin >> Passenger.Gender;
				cout << endl;
			}

			cout << "\t\t\t---------------------------------------------------------------------" << endl;

			cout << "\t\t\t\t\t3)Email Address :" << "(Ex.ali123456@gmail.com) :";
			cin >> Passenger.EmailAddress;
			while (!isValidEmail(Passenger.EmailAddress))
			{
				cout << "\t\t\t\t\tInvalid Email Address!Please Enter A Valid Email Address :";
				cin >> Passenger.EmailAddress;
			}

			cout << "---------------------------------------------------------------------" << endl;

			cout << "\t\t\t\t\t4) Phone Number :" << "(Ex.0112223333):";
			cin >> Passenger.PhoneNumber;
			while (!isValidNumber(Passenger.PhoneNumber))
			{
				cout << "\n\t\t\t\t\tInvalid Input!Please Enter In A Valid Phone Number!" << endl;
				cout << "\t\t\t\t\tPhone Number :";
				cin >> Passenger.PhoneNumber;
			}
			cout << "\t\t\t---------------------------------------------------------------------" << endl;

			cout << "\t\t\t\t\t5)Journey:" << endl;
			cout << "\t\t\t\t\t(1)One Way" << endl;
			cout << "\t\t\t\t\t(2)Round Trip" << endl;
			cout << "\t\t\t\t\tEnter A Choice(1/2) :";
			cin >> Passenger.Journey;

			while ((Passenger.Journey != "1") && (Passenger.Journey != "2"))
			{
				cout << "\t\t\t\t\tInvalid!Please enter again!" << endl;
				cout << "\t\t\t\t\tEnter A Choice(1/2) :";
				cin >> Passenger.Journey;
			}

			if (Passenger.Journey == "1")
			{
				Passenger.Journey = "One Way";
				cout << "\t\t\t\t\tJourney :" << Passenger.Journey << endl;
				cout << "\t\t\t\t\tDateOfBooking(DD-MM-YYYY)" << endl;
				cout << "\t\t\t\t\tEnter Your Flight Date" << endl;
				cout << "\t\t\t\t\tDay :";
				cin >> Passenger.Day;
				cout << "\t\t\t\t\tMonth :";
				cin >> Passenger.Month;
				cout << "\t\t\t\t\tYear :";
				cin >> Passenger.Year;

				cout << "\t\t\t\t\tDateOfBooking:" << Passenger.Day << "/" << Passenger.Month << "/" << Passenger.Year << endl;
			}

			if (Passenger.Journey == "2")
			{
				Passenger.Journey = "\t\t\t\t\tRound Trip";
				cout << "\t\t\t\t\tJourney:" << Passenger.Journey << endl;
				cout << "\t\t\t\t\tDateOfFirstFlightBooking(DD-MM-YYYY)" << endl;
				cout << "\t\t\t\t\tEnter Your First Flight Date" << endl;
				cout << "\t\t\t\t\tDay :";
				cin >> Passenger.FirstFlightDay;
				cout << "\t\t\t\t\tMonth :";
				cin >> Passenger.FirstFlightMonth;
				cout << "\t\t\t\t\tYear :";
				cin >> Passenger.FirstFlightYear;

				cout << "\t\t\t\t\tDateOfSecondFlightBooking(DD - MM - YYYY)" << endl;
				cout << "\t\t\t\t\tEnter Your Second Flight Date" << endl;
				cout << "\t\t\t\t\tDay :";
				cin >> Passenger.SecondFlightDay;
				cout << "\t\t\t\t\tMonth :";
				cin >> Passenger.SecondFlightMonth;
				cout << "\t\t\t\t\tYear :";
				cin >> Passenger.SecondFlightYear;

				cout << "\t\t\t\t\tFirstFlight:" << Passenger.FirstFlightDay << "/" << Passenger.FirstFlightMonth << "/" << Passenger.FirstFlightYear << endl;
				cout << "\t\t\t\t\tSecondFlight:" << Passenger.SecondFlightDay << "/" << Passenger.SecondFlightMonth << "/" << Passenger.SecondFlightYear << endl;
			}

			cout << "\t\t\t---------------------------------------------------------------------" << endl;

			cout << "\t\t\t\t\t6)Seat:" << endl;
			cout << "\t\t\t\t\t(1)First Class" << endl;
			cout << "\t\t\t\t\t(2)Business Class" << endl;
			cout << "\t\t\t\t\t(3)Economy Class" << endl;
			cout << "\t\t\t\t\tEnter A Chioce :";
			cin >> Passenger.Seat;

			while ((Passenger.Seat != "1") && (Passenger.Seat != "2") && (Passenger.Seat != "3"))
			{
				cout << "\t\t\t\t\tInvalid!Please enter again!" << endl;
				cout << "\t\t\t\t\tEnter A Choice(1/2/3) :";
				cin >> Passenger.Seat;
			}
			if (Passenger.Seat == "1")
			{
				Passenger.Seat = "First Class";
				cout << "\t\t\t\t\tSeat :" << Passenger.Seat << endl;
			}
			if (Passenger.Seat == "2")
			{
				Passenger.Seat = "Business Class";
				cout << "\t\t\t\t\tSeat :" << Passenger.Seat << endl;
			}
			if (Passenger.Seat == "3")
			{
				Passenger.Seat = "Economy Class";
				cout << "\t\t\t\t\tTypeOfSeat :" << Passenger.Seat << endl;
			}


			//Don't touch after this line
			Passenger.deleted = 0;

			fs = new fstream(PASSENGER_FILE_NAME, ios::out | ios::app | ios::binary);

			if (!fs)
			{
				cout << "\n Can't open or create '" << PASSENGER_FILE_NAME << "' file" << endl;
				system("pause");
				break;
			}

			cout << "\n\t\t\t\tDo you want to save this record?(1=Yes 2=No 3=Save and Add):";
			char comfirm;
		loopadd:
			cin >> comfirm;
			cin.ignore();
			system("cls");

			if (comfirm == '1')
			{
				fs->write((char*)&Passenger, sizeof(Passenger));
				closeFile(fs);
				goto mainmenu;
				break;

			}
			if (comfirm == '2')
			{
				cout << "\n\t\t\t\t\tRecord not added." << endl;
				system("pause");
				goto mainmenu;
				break;
			}
			if (comfirm == '3')
			{
				fs->write((char*)&Passenger, sizeof(Passenger));
				closeFile(fs);
				goto loopadd;
				break;

			}
			else
			{
				cout << "\n\n\t\t\t\tInvalid Input!Please enter(1=Yes,2=No,3=Save and Add)To Comfirm Add Record.";
				cout << "\n\t\t\t\tDo you want to add this record?(1=Yes,2=No,3=Save and Add):";
				goto loopadd;
			}
			
		case '2': ////// Search Record //////

			system("color 2");
			system("cls");
			cout << "\t\t\t\t\t    Welcome To Malaysia Airlines  \n" << endl;
			cout << "\t\t\t\t\t____________________________________" << endl;
			cout << "\n";
			cout << "\t\t\t\t---------------------------------------------------";
			cout << "\n\t\t\t\t|" << "           #New Passenger Registration#" << "           |" << endl;
			cout << "\t\t\t\t|" << "           #For Flight Ticket Registration#" << "      |" << endl;
			cout << "\t\t\t\t|" << "           #Search Record#" << "                       |" << endl;
			cout << "\t\t\t\t---------------------------------------------------";
			cout << "\n";
			cout << "\n";
			
			cout << "\n\t\t\t\t\tEnter Passenger ID that you search:";
			cin >> searCustomerID;
			cin.ignore();

			fs = new fstream(PASSENGER_FILE_NAME, ios::in | ios::binary);

			if (!fs)
			{
				cout << "\n\t\t\t\t\tCan't open or create" << PASSENGER_FILE_NAME << "' file" << endl;
				system("pause");
				break;
			}

			recs_num = -1;
			while (fs->read((char*)&Passenger, sizeof(Passenger)))
			{
				recs_num++;

				if (searCustomerID == Passenger.RegistrationID && !Passenger.deleted)/*if user deleted an customer then added another
				one with the same ID in the same instance of program runs, deleted customer is still there, then we should go
				through all the file*/
					break;
			}

			if (fs->eof())//if(the record is not in the file || it's there but it's deleted
			{
				cout << "\n\t\t\t\tYour specified Passenger doesn't exist in file." << endl;
				closeFile(fs);
				system("pause");
				goto mainmenu;
				break;
			}

			fs->seekp(sizeof(Passenger) * recs_num, ios::beg);//go to the searched

			fs->read((char*)&Passenger, sizeof(Passenger));//display the searched record

			if (!Passenger.deleted)
			{
				cout << "\n";
				cout << "\t\t\t\t\tRegistration ID :" << Passenger.RegistrationID << "\n";
				cout << "\t\t\t\t\tName :" << Passenger.Name << "\n";
				if (Passenger.Nationality == "1")
				{
					cout << "\t\t\t\t\tNationality :" << Passenger.Nationality << endl;
					cout << "\t\t\t\t\tICNumber" << "(Ex.000000-00-0000)" << Passenger.ICNumber;

					if (Passenger.ICNumber[11] % 2 == 0)//Even number
						cout << "\t\t\t\t\tGender: Female";
					else//Odd number
						cout << "\t\t\t\t\tGender: Male";
					cout << endl;

					Passenger.BirthDate = Passenger.ICNumber.substr(4, 2) + "/" + Passenger.ICNumber.substr(2, 2) + "/" + Passenger.ICNumber.substr(0, 2);

					cout << "\t\t\t\t\tBirthDate :" << Passenger.BirthDate << endl;
				}

				else if (Passenger.Nationality == "2")
				{
					Passenger.Nationality = "Non-Malaysian";
					cout << "\t\t\t\t\tNationality :" << Passenger.Nationality << endl;
					cout << "\t\t\t\t\tPassport Number" << "(Ex.A123456):" << Passenger.PassportNumber;
					cout << "\t\t\t\t\tExpiry Date :" << Passenger.ExpiryDate << "\n";
					cout << "\t\t\t\t\tAge :" << Passenger.Age << "\n";
					cout << "\t\t\t\t\tGender" << Passenger.Gender << "\n";
				}

				cout << "\t\t\t\t\tEmail Address :" << Passenger.EmailAddress << "\n";
				cout << "\t\t\t\t\tPhone Number :" << Passenger.PhoneNumber << "\n";

				if (Passenger.Journey == "1")
				{
					cout << "\t\t\t\t\tDateOfBooking :" << Passenger.Day << "/" << Passenger.Month << "/" << Passenger.Year << endl;
				}

				else if (Passenger.Journey == "2")
				{
					cout << "\t\t\t\t\tDate Of First Flight Booking :" << "\n" << Passenger.FirstFlightDay << "/" << Passenger.FirstFlightMonth << "/" << Passenger.FirstFlightYear << endl;
					cout << "\t\t\t\t\tDate Of Second Flight Booking :" << "\n" << Passenger.SecondFlightDay << "/" << Passenger.SecondFlightMonth << "/" << Passenger.SecondFlightYear << endl;
				}

				cout << "\t\t\t\t\tTypeOfSeat :" << Passenger.Seat << "\n";
			}

			cout << "\n\t\t\t\t\tTo return to menu";
			system("pause");
			closeFile(fs);
			goto mainmenu;
			break;



		case '3': ////// Update Record //////

			system("color 5");
			system("cls");
			cout << "\t\t\t\t\t    Welcome To Malaysia Airlines  \n" << endl;
			cout << "\t\t\t\t\t____________________________________" << endl;
			cout << "\n";
			cout << "\t\t\t\t---------------------------------------------------";
			cout << "\n\t\t\t\t|" << "           #New Passenger Registration#" << "           |" << endl;
			cout << "\t\t\t\t|" << "           #For Flight Ticket Registration#" << "      |" << endl;
			cout << "\t\t\t\t|" << "           #Update Record#" << "                       |" << endl;
			cout << "\t\t\t\t---------------------------------------------------";
			cout << "\n";
			cout << "\n";
		
			cout << "\n\t\t\t\tEnter Passenger ID, that you want modify its information : ";
			cin >> searCustomerID;
			cin.ignore();

			fs = new fstream(PASSENGER_FILE_NAME, ios::in | ios::out | ios::binary);

			if (!fs)
			{
				cout << "\n\t\t\t\t\tCan't open or create '" << PASSENGER_FILE_NAME << "' file" << endl;
				system("pause");

				break;
			}

			recs_num = -1;

			while (fs->read((char*)&Passenger, sizeof(Passenger)))
			{
				recs_num++;

				if (searCustomerID == Passenger.RegistrationID && !Passenger.deleted)/*if user deleted an customer then added another  one with the same ID in the same instance of program runs,
		delected customer is still here, then we should go thbrough all this file*/
					break;
			}

			if (fs->eof()) // if (the record is not in the file || it's there but it's deleted)
			{
				cout << "\n\t\t\t\tYour specified Passenger doesn't exist in file." << endl;
				closeFile(fs);
				system("pause");
				goto mainmenu;
				break;
			}
		UpdateList:

			cout << "\t\t\t\t\tSelect specific record to update:\n";
			cout << "\t\t\t\t\t1.Name :" << Passenger.Name << "\n";

			if (Passenger.Nationality == "1")
			{
				cout << "\t\t\t\t\t2.Nationality :Malaysian" << "\n";
				cout << "\t\t\t\t\t3.IC Number :" << Passenger.ICNumber << "\n";//IC Number will detect the Gender and birthdate

			}
			else
			{
				cout << "\t\t\t\t\t2.Nationality :Non-malaysian" << "\n";
				cout << "\t\t\t\t\t3.Passport Number :" << Passenger.PassportNumber << "\n";
				cout << "\t\t\t\t\t4.Expiry Date:" << Passenger.ExpiryDate << "\n";
				cout << "\t\t\t\t\t5.Age :" << Passenger.Age << "\n";
				cout << "\t\t\t\t\t6.Gender :" << Passenger.Gender << "\n";
			}

			cout << "\t\t\t\t\t7.Email Address :" << Passenger.EmailAddress << "\n";
			cout << "\t\t\t\t\t8.Phone Number :" << Passenger.PhoneNumber << "\n";
			cout << "\t\t\t\t\t9.Journey :" << Passenger.Journey << "\n";

			if (Passenger.Journey == "1")
			{
				cout << "\t\t\t\t\t10.DateOfBooking :" << Passenger.Day << "/" << Passenger.Month << "/" << Passenger.Year << endl;
			}

			else if (Passenger.Journey == "2")
			{
				cout << "\t\t\t\t\t11.Date Of First Flight Booking :" << "\n" << Passenger.FirstFlightDay << "/" << Passenger.FirstFlightMonth << "/" << Passenger.FirstFlightYear << endl;
				cout << "\t\t\t\t\t12.Date Of Second Flight Booking :" << "\n" << Passenger.SecondFlightDay << "/" << Passenger.SecondFlightMonth << "/" << Passenger.SecondFlightYear << endl;
			}

			cout << "\t\t\t\t\t1.Type Of Seat :" << Passenger.Seat << "\n";

			fs->seekp(sizeof(Passenger) * recs_num, ios::beg); // go to the first of the record to be modified
			fs->write((char*)&Passenger, sizeof(Passenger));

			closeFile(fs);

			cout << "\n\t\t\t\t\tRecord is modified." << endl;
			system("pause");
			closeFile(fs);
			goto mainmenu;
			break;


		case '4': ////// Delete Record //////

			system("color 6");
			system("cls");
			cout << "\t\t\t\t\t    Welcome To Malaysia Airlines  \n" << endl;
			cout << "\t\t\t\t\t____________________________________" << endl;
			cout << "\n";
			cout << "\t\t\t\t---------------------------------------------------";
			cout << "\n\t\t\t\t|" << "           #New Passenger Registration#" << "           |" << endl;
			cout << "\t\t\t\t|" << "           #For Flight Ticket Registration#" << "      |" << endl;
			cout << "\t\t\t\t|" << "           #Delete Record#" << "                       |" << endl;
			cout << "\t\t\t\t---------------------------------------------------";
			cout << "\n";
			cout << "\n";
		
			cout << "\n\t\t\t\tEnter Passenger ID that you want to delete for its information : ";
			cin >> searCustomerID;
			cin.ignore();

			fs = new fstream(PASSENGER_FILE_NAME, ios::in | ios::out | ios::binary);

			if (!fs)
			{
				cout << "\n\t\t\t\t\tCan't open or create '" << PASSENGER_FILE_NAME << "' file." << endl;
				system("pause");
				break;
			}

			recs_num = -1;

			while (fs->read((char*)&Passenger, sizeof(Passenger)))
			{
				recs_num++;

				if (Passenger.RegistrationID == Passenger.RegistrationID && !Passenger.deleted) // if user deleted an Passenger then added another one with the same ID in the same instance of program runs, deleted Passenger is still there, then we should go through all the file
					break;
			}

			if (fs->eof()) // if (the record is not in the file || it's there but it's deleted)
			{
				cout << "\n\t\t\t\tYour specified Passenger doesn't exist in database file." << endl;
				closeFile(fs);
				system("pause");
				break;
			}

			Passenger.deleted = 1;

			fs->seekp(sizeof(Passenger) * recs_num, ios::beg);
			fs->write((char*)&Passenger, sizeof(Passenger));

			closeFile(fs);

			deletion = true; // we have some deleted records
			cout << "\n\t\t\t\t\tRecord is deleted." << endl;

			system("pause");
			goto mainmenu;
			break;


		case '5': // Display Records

			system("color 7");
			system("cls");
			cout << "\t\t\t\t\t    Welcome To Malaysia Airlines  \n" << endl;
			cout << "\t\t\t\t\t____________________________________" << endl;
			cout << "\n";
			cout << "\t\t\t\t---------------------------------------------------";
			cout << "\n\t\t\t\t|" << "           #New Passenger Registration#" << "           |" << endl;
			cout << "\t\t\t\t|" << "           #For Flight Ticket Registration#" << "      |" << endl;
			cout << "\t\t\t\t|" << "           #Display Record#" << "                      |" << endl;
			cout << "\t\t\t\t---------------------------------------------------";
			cout << "\n";
			cout << "\n";
			
			fs = new fstream(PASSENGER_FILE_NAME, ios::in | ios::binary);

			if (!fs)
			{
				cout << "\n\t\t\t\t\tCan't open or create '" << PASSENGER_FILE_NAME << "' file." << endl;
				system("pause");
				break;
			}

			while (fs->read((char*)&Passenger, sizeof(Passenger))) // display records
			{
				if (!Passenger.deleted)
				{
					cout << "\n";
					cout << "\t\t\t\t\tRegistration ID :" << Passenger.RegistrationID << "\n";
					cout << "\t\t\t\t\tName :" << Passenger.Name << "\n";
					if (Passenger.Nationality == "1")
					{
						cout << "\t\t\t\t\tNationality :" << Passenger.Nationality << endl;
						cout << "\t\t\t\t\tICNumber" << "(Ex.000000-00-0000)" << Passenger.ICNumber;

						if (Passenger.ICNumber[11] % 2 == 0)//Even number
							cout << "\t\t\t\t\tGender : Female";
						else//Odd number
							cout << "\t\t\t\t\tGender : Male";
						cout << endl;

						Passenger.BirthDate = Passenger.ICNumber.substr(4, 2) + "/" + Passenger.ICNumber.substr(2, 2) + "/" + Passenger.ICNumber.substr(0, 2);

						cout << "\t\t\t\t\tBirthDate :" << Passenger.BirthDate << endl;
					}

					else if (Passenger.Nationality == "2")
					{
						Passenger.Nationality = "Non-Malaysian";
						cout << "\t\t\t\t\tNationality :" << Passenger.Nationality << endl;
						cout << "\t\t\t\t\tPassport Number :" << "(Ex.A123456):" << Passenger.PassportNumber;
						cout << "\t\t\t\t\tExpiry Date :" << Passenger.ExpiryDate << "\n";
						cout << "\t\t\t\t\tAge :" << Passenger.Age << "\n";
						cout << "\t\t\t\t\tGender :" << Passenger.Gender << "\n";
					}

					cout << "\t\t\t\t\tEmail Address :" << Passenger.EmailAddress << "\n";
					cout << "\t\t\t\t\tPhone Number :" << Passenger.PhoneNumber << "\n";

					if (Passenger.Journey == "1")
					{
						cout << "\t\t\t\t\tDateOfBooking :" << Passenger.Day << "/" << Passenger.Month << "/" << Passenger.Year << endl;
					}

					else if (Passenger.Journey == "2")
					{
						cout << "\t\t\t\t\tDate Of First Flight Booking :" << "\n" << Passenger.FirstFlightDay << "/" << Passenger.FirstFlightMonth << "/" << Passenger.FirstFlightYear << endl;
						cout << "\t\t\t\t\tDate Of Second Flight Booking :" << "\n" << Passenger.SecondFlightDay << "/" << Passenger.SecondFlightMonth << "/" << Passenger.SecondFlightYear << endl;
					}

					cout << "\t\t\t\t\tTypeOfSeat :" << Passenger.Seat << "\n";

				}

			}

			////// Print Flight Ticket records...

			cout << "\n\t\t\t\t\tTo see menu, ";
			system("pause");
			closeFile(fs);
			goto mainmenu;
			break;

		case '6': // Exit

			system("color 8");
			system("cls");
			cout << "\t\t\t\t\t    Welcome To Malaysia Airlines  \n" << endl;
			cout << "\t\t\t\t\t____________________________________" << endl;
			cout << "\n";
			cout << "\t\t\t\t---------------------------------------------------";
			cout << "\n\t\t\t\t|" << "           #New Passenger Registration#" << "           |" << endl;
			cout << "\t\t\t\t|" << "           #For Flight Ticket Registration#" << "      |" << endl;
			cout << "\t\t\t\t|" << "           #Exit#" << "                                |" << endl;
			cout << "\t\t\t\t---------------------------------------------------";
			cout << "\n";
			cout << "\n";

			if (deletion) // if there is any deletion, then update database file (create a new temp file that doesn't have deleted records, then remove the old database file and rename temp file to database file name)
			{
				cout << "\n\t\t\t\t\tUpdating '" << PASSENGER_FILE_NAME << "' File..." << endl;

				fs = new fstream(PASSENGER_FILE_NAME, ios::in | ios::binary);
				if (!fs)
				{
					cout << "\n\t\t\t\t\tCan't open '" << PASSENGER_FILE_NAME << "' file, then Updating is incomplete." << endl;
					system("pause");

					system("cls");
					return 1;
				}

				fs1 = new fstream("temp", ios::out | ios::binary);
				if (!fs1)
				{
					cout << "\n\t\t\t\tCan't create temp file, then Updating is incomplete." << endl;
					system("pause");

					closeFile(fs);
					system("cls");
					return 1;
				}

				// write nondeleted records to the temp file
				while (fs->read((char*)&Passenger, sizeof(Passenger)))
					if (!Passenger.deleted)
						fs1->write((char*)&Passenger, sizeof(Passenger));

				closeFile(fs);
				closeFile(fs1);

				if (remove(PASSENGER_FILE_NAME) == -1) // if there is an error
				{
					cout << "\n\t\t\t\t\tCan't delete '" << PASSENGER_FILE_NAME << "' file, then Updating is incomplete." << endl;
					system("pause");

					system("cls");
					return 1;
				}


				struct stat st; // to check size of the temp file
				int res = stat("temp", &st);

				if (st.st_size == 0) // if all of records are deleted then the temp file size is zero                        
					remove("temp"); // we have no records, then no database file is needed, just delete the temp file
				else
					if (rename("temp", PASSENGER_FILE_NAME))
					{
						cout << "\n\t\t\t\tCan't rename temp file, then Updating is incomplete." << endl;
						system("pause");

						system("cls");
						return 1;
					}

				cout << "\n\t\t\t\t\tUpdating database file completed." << endl;
				system("pause");
			}

			//Exit Splash Screen

			system("color 17");
			system("cls");
			cout << "\n";
			cout << "\t\t\t\t\t*This Registration System*" << endl;
			cout << "\t\t\t\t\t*Is Created By*" << endl;
			cout << "\t\t\t\t\t*Chong Min Kee*" << endl;
			cout << "\t\t\t\t\t*Hope To See You Again*" << endl;
			cout << "\t\t\t\t\t*Have A Nice Day.Goodbye!";
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