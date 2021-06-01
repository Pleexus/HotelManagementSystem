#include<iostream.h>
#include<conio.h>
#include<fstream.h>
#include<stdio.h>
#include<process.h>
#include<string.h>
#include<iomanip.h>

//***************** CLASS ROOM *******************************************
// Class to represent a room category
class Room
{
	char Roomtype[30];
	int price;
	int room_left;
	int r[20];

public:
	Room()
	{
		for (int i=0; i<20; i++)
		{
			r[i]= i+1;
		}
	}

	void getdata();
	void showdata();
	char* retroom()	//returns Roomtype
	{
		return Roomtype;
	}
	int retprice() // returns room price
	{
		return price;
	}
	int roomavail() //returns the first available room number or -1 if none are available
	{
		for (int i=0; i<20; i++)
		{
			if (r[i] !=0 )
				return r[i];
		}
		return -1;
	}
	void giveroom() // Checkin into the first available room
	{
		room_left--;
		for (int i=0; i<20; i++)
		{
			if (r[i] !=0)
			{
				r[i]=0;
				break;
			}
		}
	}
	void incr_rooms() // Increase room_left by 1
	{
		room_left++;
	}
	void mark_avail(int rno) // Checkout of room rno and mark it available
	{
		r[rno-1] = rno;
	}
	void showtariff() // Shows the price of the room
	{
		cout<<"\n"<<setw(15)<<Roomtype<<setw(20)<<price;
	}

};

// Read in information about a room category
void Room::getdata()
{
	cout<<"\n\n Enter Room Category Information";
	cout<<"\n *******************************";
	cout<<"\n\nEnter Roomtype: ";
	gets(Roomtype);
	cout<<"\n\n Enter Price: ";
	cin>>price;
	room_left = 20;
	for(int i=0; i<20; i++)
	{
		r[i] = i+1;
	}
}

// Display information about a room category
void Room::showdata()
{
	cout<<"\n\n Room information";
	cout<<"\n ****************";
	cout<<"\n\n RoomType: "<<Roomtype;
	cout<<"\n\n Price: "<<price;
	cout<<"\n\n Room available: "<<room_left;
	cout<<"\n\n Free Room numbers are : \n";
	for(int i=0; i<20; i++)
	{
		if(r[i]!=0)
		{
			cout<<r[i] << "\t";
		}
	}
}
//***************** END OF CLASS ROOM **************************************

//***************** ADMIN MENU FUNCTIONS ***********************************
// File handling functions for class room

// Function to delete a roomtype record
void room_delrecord()
{
	clrscr();
	char roomtype[20];
	cout<<"\n\n Enter roomtype of the room that is to be deleted: ";
	gets(roomtype);
	ifstream fin;
	fin.open("Room.dat",ios::binary);
	ofstream fout;
	fout.open("R_New.dat",ios::binary);

	Room r;
	int found=0;
	while(1)
	{
		fin.read((char*)&r, sizeof(r));
		if (fin.eof())
		break;
		if (strcmpi(r.retroom(),roomtype)==0)
		{
			found=1;
		}
		else
		{
			fout.write((char*)&r,sizeof(r));
		}
	}
	fin.close();
	fout.close();
	remove("Room.dat");
	rename("R_New.dat","Room.dat");
	if(found==0)
	{
		cout<<"\n\n Room record not found!";
	}
	else
	{
		cout<<"\n\n Room record found and deleted!";
	}
	getch();
}

// function to modify a room type record
void room_modify()
{
	clrscr();
	fstream finout;
	finout.open("Room.dat",ios::binary|ios::in|ios::out);
	char roomtype[20];
	cout<<"\n\n Enter the roomtype whose record is to be modified: ";
	gets(roomtype);
	int found=0;
	Room r;
	while(1)
	{
		finout.read((char*)&r,sizeof(r));
		if (finout.eof())
		break;
		if(strcmpi(r.retroom(),roomtype)==0)
		{
			found=1;
			r.getdata();
			int pos= finout.tellg()-sizeof(r);
			finout.seekp(pos);
			finout.write((char*)&r,sizeof(r));
		}
	}
	finout.close();
	if(found==0)
	{
		cout<<"\n Record for modification not found!";
	}
	else
	{
		cout<<"\n Record modified!";
	}
	getch();
}

//Function to append a room type record
void room_append()
{
	clrscr();
	ofstream fout("Room.dat",ios::binary|ios::app);

	if(!fout)
	{
		   cout<<"\n Error in open";
		   getch();
		   return;
	}
	Room tmp;
	while(1)
	{
		cout<<"\n\n Enter Room details ";
		tmp.getdata();
		fout.write((char*)&tmp,sizeof(tmp));
		char choice;
		cout<<"\n Do you want to enter more entries[Y/N]: ";
		cin>>choice;
		if(choice=='N'||choice=='n')
		{
			break;
		}
	}
	cout<<"\n Press any key to continue!!";
	getch();
	fout.close();
}

//Function to display all room type record
void room_display()
{
	clrscr();
	ifstream fout("Room.dat",ios::binary);
	if(!fout)
	{
		cout<<"\n Error in open ";
		getch();
		return;
	}
	Room r;
	cout<<"\n File as follows: ";
	while(1)
	{	fout.read((char*)&r,sizeof(r));
		if(fout.eof())
		{
			break;
		}
		r.showdata();
		getch();

	}
	fout.close();
}

//Function to display one room type record
void room_displayone()
{
	clrscr();
	ifstream fout("Room.dat",ios::binary);
	if(!fout)
	{
		cout<<"\n Error in open ";
		getch();
		return;
	}
	char roomtype[20];
	cout<<"\n\n Enter the roomtype to display: ";
	gets(roomtype);
	Room r;
	int found=0;
	while(1)
	{	fout.read((char*)&r,sizeof(r));
		if(fout.eof())
		{
			break;
		}
		if(strcmpi(r.retroom(),roomtype)==0)
		{
			found=1;
			cout<<"\n\n Room is as follows: ";
			r.showdata();
		}
	}
	fout.close();
	if(found==0)
	{
		cout<<"\n\n Roomtype not found";
	}
	getch();
}
// Function to print the admin menu
void admin_menu()
{
	int choice;
	while(choice!=5)
	{
		clrscr();
		cout<<"\n\t\t\t\t**********************";
		cout<<"\n\t\t\t\t ADMINISTRATOR'S MENU ";
		cout<<"\n\t\t\t\t**********************";
		cout<<"\n\n\n\t\t\t1.Add a new room type";
		cout<<"\n\t\t\t2.Modify a room type information";
		cout<<"\n\t\t\t3.Delete a room type information";
		cout<<"\n\t\t\t4.Display information about a room type";
		cout<<"\n\t\t\t5.Display information about all room types";
		cout<<"\n\t\t\t6.Return";

		cout<<"\n\n\t\t\tEnter Your Choice: ";
		cin>>choice;

		switch(choice)
		{
			case 1: room_append();
					break;
			case 2: room_modify();
					break;
			case 3: room_delrecord();
					break;
			case 4: room_displayone();
					break;
			case 5: room_display();
					break;
			case 6: return;
			default:{
					cout<<"\n\n\t\t\tWrong choice!";
					cout<<"\n\t\t\tPress any key to continue!";
					getch();
					}
		} // end of switch
	} // end of while
}
//***************** END OF ADMIN MENU FUNCTIONS *************************

//***************** CLASS CUSTOMER **************************************

class cust
{
	char cname[20];
	char address[100];
	char phone[11];
	char roomtype[20];
	int roomno;
 public:void getdata();
	void showdata();
	char* retname()
	{
		return cname;
	}
	char* retroom()
	{
		return roomtype;
	}
	int retrno()
	{
		return roomno;
	}
	void setroomno(int r)
	{
		roomno = r;
	}
};

void cust::getdata()
{
	cout<<"\n\n Enter Customer Detalils";
	cout<<"\n ***********************";
	cout<<"\n\n Name: ";
	gets(cname);
	cout<<"\n\n Address: ";
	gets(address);
	cout<<"\n\n Phone Number: ";
	gets(phone);
	cout<<"\n\n RoomType: ";
	gets(roomtype);
}
void cust::showdata()
{
	cout<<"\n\n Customer Details";
	cout<<"\n ****************";
	cout<<"\n\n Name: "<<cname;
	cout<<"\n\n Address : "<<address;
	cout<<"\n\n Phone Number: "<<phone;
	cout<<"\n\n Room Type: "<<roomtype;
	cout<<"\n\n Room Number: "<<roomno;
}
//***************** END OF CLASS CUSTOMER ********************************

//*************** FUNCTIONS DEALING WITH CUSTOMER CHECK IN ************
// Allocates the first available room number from roomtype
// or returns -1 if no rooms are available
int search(char roomtype[30])
{
	// Open the room.dat file for reading and writing
	fstream finout;
	finout.open("Room.dat",ios::binary|ios::in|ios::out);
	int found=0;
	Room r;
	while(1)
	{
		finout.read((char*)&r,sizeof(r));   // read a record from the file
		if (finout.eof())
		break;
		if(strcmpi(r.retroom(),roomtype)==0) // if the roomtype matches
		{
			found=1;
			int avail = r.roomavail(); // Check if room is available for this roomtype
			if ( avail == -1 ) // If not, close file and return -1
			{
				finout.close();
				return -1;
			}
			// Room is available, mark it given
			r.giveroom();
			int pos= finout.tellg()-sizeof(r);
			finout.seekp(pos);

			finout.write((char*)&r,sizeof(r));  //Write modified roomtype info in file
			finout.close();
			return  avail;
		}
	}
	if ( found == 0 )
		return -1;
}
// Function to write customer check in data in customer.dat
void writecust(cust tmp)
{
	ofstream fout("Customer.dat",ios::binary|ios::app);

	if(!fout)
	{
		   cout<<"\n Error in open";
		   getch();
		   return;
	}
	fout.write((char*)&tmp,sizeof(tmp));

	fout.close();
}

// Function to implement customer check in
void checkin()
{
	clrscr();
	cust c;
	// Read in customer data including roomtype
	c.getdata();

	// Check if a room is available for this roomtype
	int ret= search(c.retroom());
	if(ret==-1)
	{
		cout<<"\n\n Sorry! No room in this category are available";
	}
	else
	{
		cout<<"\n\n You have checked in room number: "<<ret;
		c.setroomno(ret);
		writecust(c);
	}
	getch();
}
//*************** FUNCTIONS DEALING WITH CUSTOMER CHECK IN ************

//*************** FUNCTIONS DEALING WITH CUSTOMER CHECK OUT ************
// Search for record with roomtype as rt and room number as rn
// in the customer.dat file
int searchroom(char rt[30], int rn)
{
	ifstream fin("customer.dat",ios::binary);
	if(!fin)
	{
		cout<<"\n Error in open";
		getch();
		return -1;
	}
	cust c;
	while(1)
	{
		fin.read((char*)&c,sizeof(c));
		if(fin.eof())
		break;
		if( strcmpi(c.retroom(),rt)==0 && c.retrno()==rn)
		{
			fin.close();
			return 1;
		}
	}
	fin.close();
	return -1;
}

// Function that searches for record with roomtype = rtr in room.dat
// file and returns the price corresponding to that roomtype
int getprice(char rtr[30])
{
	ifstream fin("Room.dat",ios::binary);
	if(!fin)
	{
		cout<<"\n Error in open";
		getch();
		return -1;
	}
	Room r;
	while(1)
	{
		fin.read((char*)&r,sizeof(r));
		if(fin.eof())
		break;
		if( strcmpi(r.retroom(),rtr)==0)
		{
			fin.close();
			return r.retprice();
		}
	}
	fin.close();
	return -1;
}

// Function that deletes the record from customer.dat in which
// roomtype = rtd and room number = rnd
void delcust (char rtd[30], int rnd)
{
	ifstream fin;
	fin.open("Customer.dat",ios::binary);
	ofstream fout;
	fout.open("New.dat",ios::binary);

	cust s;
	int found=0;
	while(1)
	{
		fin.read((char*)&s, sizeof(s));
		if (fin.eof())
		break;
		if (strcmpi(s.retroom(),rtd)==0 && s.retrno()==rnd)
		{
			found=1;
		}
		else
		{
			fout.write((char*)&s,sizeof(s));
		}
	}
	fin.close();
	fout.close();
	remove("Customer.dat");
	rename("New.dat","Customer.dat");
	if(found==0)
	{
		cout<<"\n Customer checkin record not found!";
	}
	else
	{
		cout<<"\n Customer has checked out and record has been deleted!";
	}
	getch();
}

// Function that searches for record with roomtype = rtn in room.dat file
// and marks room number rnm as available
void moodroom(char rtm[30], int rnm)
{

	fstream finout;
	finout.open("Room.dat",ios::binary|ios::in|ios::out);

	int found=0;
	Room r;
	while(1)
	{
		finout.read((char*)&r,sizeof(r));
		if (finout.eof())
		break;
		if(strcmpi(r.retroom(),rtm)==0)
		{
			found=1;
			r.incr_rooms();
			r.mark_avail(rnm);
			int pos= finout.tellg()-sizeof(r);
			finout.seekp(pos);
			finout.write((char*)&r,sizeof(r));
		}
	}
	finout.close();
	if(found==0)
	{
		cout<<"\n Record for modification not found!";
	}
	else
	{
		cout<<"\n Room marked as free in the database";
	}
	getch();
}

// Function to implement customer checkout
void checkout()
{
	clrscr();
	char Roomtype[30];
	int room_no;

	// Ask the user for his room type and room number
	cout<<"\n Enter roomtype: ";
	cin>>Roomtype;
	cout<<"\n Enter room number: ";
	cin>>room_no;

	//Search for a record with this room info in cust.dat
	int ret= searchroom(Roomtype,room_no);

	//If not found return error
	if(ret==-1)
	{
		cout<<"\n No customer in this room.";
		return;
	}

	// Read in days of stay
	int daysofstay;
	cout<<"\n Enter number of day that customer stayed in the hotel: ";
	cin>>daysofstay;

	// Get room prime from room.dat file
	double price= getprice(Roomtype);


	// Display bill amount
	cout<<"\n Total Bill cost: "<<price*daysofstay;

	// Delete customer record from cust.dat file
	delcust(Roomtype, room_no);

	// Modify room.dat file to indicate that the room has been vacated
	moodroom (Roomtype,room_no);

	cout << "\n\n You have been successfully checked out";
	cout << "\n\n Thank you for staying in our hotel.";
	cout << "\n\n Hope you had a nice stay";
	getch();

}
//*************** END OF FUNCTIONS DEALING WITH CUSTOMER CHECK OUT **********
//*************** FUNCTIONS DEALING WITH ENQUIRY ****************************
void Tariff()
{
	clrscr();
	ifstream fout("Room.dat",ios::binary);
	if(!fout)
	{
		cout<<"\n Error in open ";
		getch();
		return;
	}
	Room r;
	cout<<"\n\n Room Tariff information follows : ";
	cout << "\n"<<setw(15)<<"ROOMTYPE"<<setw(20)<<"ROOM TARIFF/DAY";
	while(1)
	{	fout.read((char*)&r,sizeof(r));
		if(fout.eof())
		{
			break;
		}
		r.showtariff();
		getch();
	}
	fout.close();
}
void Roomavailability()
{
	clrscr();
	ifstream fout("Room.dat",ios::binary);
	if(!fout)
	{
		cout<<"\n Error in open ";
		getch();
		return;
	}
	char roomtype[20];
	cout<<"\n\n Enter the roomtype to display: ";
	gets(roomtype);
	Room r;
	int found=0;
	while(1)
	{	fout.read((char*)&r,sizeof(r));
		if(fout.eof())
		{
			break;
		}
		if(strcmpi(r.retroom(),roomtype)==0)
		{
			found=1;
			cout<<"\n\n Room is as follows: ";
			r.showdata();
		}
	}
	fout.close();
	if(found==0)
	{
		cout<<"\n\n Roomtype not available";
	}
	getch();
}
void CustomerEnquiry()
{
	clrscr();
	ifstream fout("Customer.dat",ios::binary);
	if(!fout)
	{
		cout<<"\n Error in open ";
		getch();
		return;
	}
	char cname[20];
	cout<<"\n\n Enter the name of the customer to display: ";
	gets(cname);
	cust c;
	int found=0;
	while(1)
	{	fout.read((char*)&c,sizeof(c));
		if(fout.eof())
		{
			break;
		}
		if(strcmpi(c.retname(),cname)==0)
		{
			found=1;
			cout<<"\n\n Customer details is as follows: ";
			c.showdata();
		}
	}
	fout.close();
	if(found==0)
	{
		cout<<"\n\n Customer details not found";
	}
	getch();
}
void Roomenquiry()
{
	clrscr();
	ifstream fout("Customer.dat",ios::binary);
	if(!fout)
	{
		cout<<"\n Error in open ";
		getch();
		return;
	}
	char Roomtype[20];
	cout<<"\n\n Enter the Roomtype: ";
	gets(Roomtype);
	int rn;
	cout<<"\n\n Enter room number: ";
	cin>>rn;
	cust c;
	int found=0;
	while(1)
	{	fout.read((char*)&c,sizeof(c));
		if(fout.eof())
		{
			break;
		}
		if(strcmpi(c.retroom(),Roomtype)==0 && c.retrno()==rn)
		{
			found=1;
			cout<<"\n\n Room details is as follows: ";
			c.showdata();
		}
	}
	fout.close();
	if(found==0)
	{
		cout<<"\n\nThis Room is available.";
	}
	getch();
}
void display()
{
	clrscr();
	ifstream fout("Customer.dat",ios::in);
	if(!fout)
	{
		cout<<"\n Error in open ";
		getch();
		return;
	}
	cust s;
	cout<<"\n File as follows: ";
	while(1)
	{	fout.read((char*)&s,sizeof(s));
		if(fout.eof())
		{
			break;
		}
		s.showdata();

	}
	fout.close();
	getch();
}

void enquiry()
{
	int choice;
	while(choice!=5)
	{
		clrscr();
		cout<<"\n\t\t\t\t**************";
		cout<<"\n\t\t\t\t ENQUIRY MENU ";
		cout<<"\n\t\t\t\t**************";
		cout<<"\n\n\n\t\t\t 1.Room Tariff Enquiry";
		cout<<"\n\t\t\t 2.Check Room availability";
		cout<<"\n\t\t\t 3.Room Enquiry";
		cout<<"\n\t\t\t 4.Display a customer's details";
		cout<<"\n\t\t\t 5.Return ";

		cout<<"\n\n\t\t\tEnter Your Choice: ";
		cin>>choice;

		switch(choice)
		{
			case 1: Tariff();
				break;
			case 2: Roomavailability();
				break;
			case 3: Roomenquiry();
				break;
			case 4: CustomerEnquiry();
				break;
			case 5: return;

			default:{
					cout<<"\n\n\t\t\tWrong choice!";
					cout<<"\n\t\t\tPress any key to continue!";
					getch();
					}
		} //end of switch
	} // end of while
}

//*************** END OF FUNCTIONS DEALING WITH ENQUIRY *********************

//*************** FUNCTIONS DEALING WITH HELP *******************************
void help()
{
	clrscr();
	cout<<"\n\t\t******** GUIDE TO USE THIS SOFTWARE ********";
	cout<<"\n\nThis is a hotel management software";
	cout<<"\n\nThe first option is the MAIN MENU gives the administrator access to the database/records of the hotel through which he/she can add/delete/modify/display the    room details.";
	cout<<"\n\nThe second option  is Checkin which checks the customer in the hotel.";
	cout<<"\n\nThe third option is Checkout which checks out the customer and gives the total  bill.";
	cout<<"\n\nThe fifth option is Exit which will quit the program after use.";
	getch();
}
//*************** END OF FUNCTIONS DEALING WITH HELP ************************
int password()
{
	char p[25];
	cout<<"\n\t\t\tEnter Password : ";
	int i = 0;
	while (1)
	{
		char ch = getch();		//getch- > reads without displaying on the screen
		putch('*');
		if ( ch == '\r' )
			break;
		p[i] = ch;
		i++;
	}
	p[i] = '\0';				//string terminator
	if (strcmp(p,"prajwal")==0)
	{
		return 1;
	}
	else
	{
		return -1;
	}
}
int getpassword()
{
	clrscr();
	char u[25];

	int ret=-1;
	int tries = 3;
	while(tries)
	{
		cout<<"\n\n\n\n\n\t\t\tEnter username : ";
		gets(u);

		if(strcmp(u,"admin")==0)
		{
			 ret=password();
			 break;
		}
		else
		{
			 cout<<"\n Wrong administrator, you have limited tries. ";
		}
		tries--;
	}
	return ret;
}

// Function for the administrator.
// First validates the administrator password.
// If the password is correct prints the game menu to allow him to select the game.
void access()
{
	int ret = getpassword();
	if ( ret == -1 )
	{
	      cout<<"\n\n\t\t\t ***Wrong password or username*** ";
	      getch();
	      return;

	}
	if( ret==1)
	{
		admin_menu();
	}
}
// Function to print the main menu
void main_menu()
{
	int choice;
	while(choice!=5)
	{
		clrscr();
		cout<<"\n\t\t\t\t***********";
		cout<<"\n\t\t\t\t MAIN MENU ";
		cout<<"\n\t\t\t\t***********";
		cout<<"\n\n\n\t\t\t1.Administrator";
		cout<<"\n\t\t\t2.Checkin";
		cout<<"\n\t\t\t3.Checkout";
		cout<<"\n\t\t\t4.Enquiry";
		cout<<"\n\t\t\t5.Help";
		cout<<"\n\t\t\t6.Exit";

		cout<<"\n\n\t\t\tEnter Your Choice: ";
		cin>>choice;

		switch(choice)
		{
			case 1: access();
				break;
			case 2: checkin();
				break;
			case 3: checkout();
				break;
			case 4: enquiry();
				break;
			case 5: help();
				break;
			case 6: exit(0);
				break;

			default:{
					cout<<"\n\n\t\t\tWrong choice!";
					cout<<"\n\t\t\tPress any key to continue!";
					getch();
				}
		} //end of switch
	} // end of while
}
// The main function
void main()
{
	clrscr();
	main_menu();    // Call Main menu
}

//Author- Prajwal bisht
// @Pleexus
