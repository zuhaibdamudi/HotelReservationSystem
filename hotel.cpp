#include<iostream>
#include<curses.h>
#include<fstream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
// #include<process.h>
#include<time.h>
float tnoofrooms=100;

using namespace std;

class staff
{
	public:
	float id;
	char name[30],role[20];
	int age;
    void enter();
    
    void display()
    {
        cout<<id<<"\t\t"<<name<<"\t\t"<<age<<"\t\t"<<role<<endl;
    }
}s;

void staff::enter()
{
    cout<<endl;
    cout<<"ID: ";
    cin>>id;
    cout<<"Name: ";
    cin>>name;
    cout<<"Age: ";
    cin>>age;
    cout<<"Position: ";
    cin>>role;
}

class customer
{
	int id,noofrooms,noofdays;
	char name[30],roomtype[10],chkin[20],chkout[20];
	float amount,rate,total;

	public:
        int returnid()
        {
            return id;
        }
        float returnrate()
        {
            return rate;
        }
        char* returnname()
        {
            return name;
        }
        int returnnoofrooms()
        {
            return noofrooms;
        }
        int returnnoofdays()
        {
            return noofdays;
        }
        
        void Calc_amt()
        {
            if(strcmp(roomtype,"standard")==0)
                rate=1000;
            else if(strcmp(roomtype,"deluxe")==0)
                rate=2000;
            else if(strcmp(roomtype,"suite")==0)
                rate=4000;
            
            amount=noofrooms*rate;
        }
        
        float amt()
        {
            return amount;
        }
        
        char* returnchkout()
        {
            return chkout;
        }

        void enter()
        {
            int id1;
            cout<<"\nNAME:"<<endl;
            cin>>name;
            cout<<"\nNATIONAL ID: "<<endl;
            cin>>id;
            cout<<"Enter Check-In Date:"<<endl;
            cin>>chkin;
            cout<<"Enter Check-Out Date:"<<endl;
            cin>>chkout;
            cout<<"Enter Number of Days of Stay :"<<endl;
            cin>>noofdays;
            cout<<"No of rooms: "<<endl;
            cin>>noofrooms;
            if(noofrooms<=tnoofrooms)
            {
                tnoofrooms=tnoofrooms-noofrooms;
                cout<<"\nEnter type of room (deluxe, standard, suite) :"<<endl;
                cin>>roomtype;
                if(strcmp(roomtype,"deluxe")==0||strcmp(roomtype,"standard")==0||strcmp(roomtype,"suite")==0)
                    cout<<"Booking successful"<<endl;
                else
                {
                    cout<<"Booking Unsuccessful"<<endl;
                    cout<<"Enter type of room again (deluxe, standard, suite) :"<<endl;
                    cin>>roomtype;
                    if(strcmp(roomtype,"deluxe")==0||strcmp(roomtype,"standard")==0||strcmp(roomtype,"suite")==0)
                    cout<<"Booking successful"<<endl;
                    else if(strcmp(roomtype,"deluxe")!=0||strcmp(roomtype,"standard")!=0||strcmp(roomtype,"suite")!=0)
                    cout<<"Go back and try again from the beginning"<<endl;
                    cout<<"Enter your NATIONAL ID again :"<<endl;
                    cin>>id1;
                    fstream f,temp;
                    f.open("list.dat",ios::in|ios::binary);
                    temp.open("temp.dat",ios::out|ios::binary);
                    
                    while(strcmp(roomtype,"deluxe")!=0 || strcmp(roomtype,"standard")!=0 || strcmp(roomtype,"suite") != 0)
                    {
                        // if(cus.returnid()!=id1)
                        //     temp.write((char*)&cus,sizeof(cus));
                        break;
                    }
                    remove("list.dat");
                    rename("temp.dat","list.dat");
                }
                
                Calc_amt();
            }
            else
            {
                cout<<"No of rooms not available"<<endl;
                cout<<"Booking Unsuccessful go back and try again"<<endl;
            }
        }

        void display()
        {
            cout<<"NATIONAL ID :"<<id<<endl;
            cout<<"NAME :"<<name<<endl;
            cout<<"RATE :"<<rate<<endl;
            cout<<"NO.OF ROOMS :"<<noofrooms<<endl;
            cout<<"NO.OF DAYS :"<<noofdays<<endl;
            cout<<"CHECK-IN DATE :"<<chkin<<endl;
            cout<<"CHECK-OUT DATE :"<<chkout<<endl;
            cout<<"ROOM TYPE :"<<roomtype<<endl;
            cout<<endl;
        }
}cus;

void create_staff()
{
	system("clear");

	int n;
	cout<<"Enter the number of staffs to add to list = ";
	cin>>n;
	ofstream f;
	f.open("masterfile.dat",ios::out|ios::binary);
	cout<<"\nEnter the details"<<":"<<endl;
	
    for(int i=1;i<=n;i++)
	{

		s.enter();
		f.write((char*)&s,sizeof(s));
	}
	cout<<"\nStaff(s) successfully appointed!!\n";
	f.close();
	int ch = cin.get();
}

void append_staff()
{
	system("clear");

	int n;
	cout<<"Enter the number of staffs to appoint = ";
	cin>>n;
	ofstream f;
	f.open("masterfile.dat",ios::app|ios::binary);
	cout<<"\nEnter the details"<<":"<<endl;
	
    for(int i=1;i<=n;i++)
	{
		s.enter();
		f.write((char*)&s,sizeof(s));
	}
	
    cout<<"\nStaff(s) successfully appointed!!\n";
	f.close();
	int ch = cin.get();
}

void display_staff()
{
	system("clear");

	ifstream f;
	cout<<"\t\t\t\tStaff List\n";
	f.open("masterfile.dat",ios::binary);
	cout<<endl;
	cout<<"________________________________________________________________________________\n";
	cout<<"ID\t\tName\t\tAge\t\tPosition"<<endl;
	cout<<"________________________________________________________________________________\n";
	while(f.read((char*)&s,sizeof(s)))
		s.display();
	f.close();
	int ch = cin.get();
}

void search_staff()
{
	system("clear");
	int id;
	cout<<"Enter the ID of the staff to search = ";
	cin>>id;

	ifstream f("masterfile.dat",ios::binary);
	
    while(f.read((char*)&s,sizeof(s)))
		if(s.id==id)
		{
			cout<<"\nStaff found!!\n\n";
			cout<<"Details:\n";
			cout<<"ID = "<<s.id<<endl;
			cout<<"Name = "<<s.name<<endl;
			cout<<"Age = "<<s.age<<endl;
			cout<<"Position = "<<s.role<<endl;
		}
		else
	    	cout<<"\nStaff not found!!\n";
	
    f.close();
	int ch = cin.get();
}

void modify_staff()
{
	system("clear");
	fstream f1,f2;
	f1.open("masterfile.dat",ios::in|ios::binary);
	f2.open("temp.dat",ios::out|ios::binary);

	int id;
	cout<<"\nEnter the ID of the staff to modify = ";
	cin>>id;
	while(f1.read((char*)&s,sizeof(s)))
	{
		if(s.id==id)
		{
			cout<<"\nEnter the new details:\n";
			s.enter();
			cout<<"\nDetails modified!!\n";
		}
		f2.write((char*)&s,sizeof(s));
	}
	if(s.id!=id)
		cout<<"\nStaff not found";

	f1.close();f2.close();
	remove("masterfile.dat");
	rename("temp.dat","masterfile.dat");
	int ch = cin.get();
}

void delete_staff()
{
	system("clear");
	fstream f1,f2;
	f1.open("masterfile.dat",ios::in|ios::binary);
	f2.open("temp.dat",ios::out|ios::binary);
	int id;
	cout<<"\nEnter the ID of the staff to dismiss = ";
	cin>>id;
	while(f1.read((char*)&s,sizeof(s)))
	{
		if(s.id!=id)
		{
		f2.write((char*)&(s),sizeof(s));
		cout<<"\nStaff Dismissed!";
		}
	}

	f1.close();f2.close();
	remove("masterfile.dat");
	rename("temp.dat", "masterfile.dat");
	int ch = cin.get();
}


void create_customer()
{
	system("clear");
	fstream f,db;
	db.open("datab.dat",ios::out|ios::binary);
	f.open("list.dat",ios::out|ios::binary);
	cout<<" Number of rooms available="<<tnoofrooms<<endl;
	{
        cout<<"\n\n\t\t\t\tCustomer Booking\n";
        cout<<"\nEnter the details of the customer(s)"<<"\n";
        cus.enter();
        db.write((char*)&cus,sizeof(cus));
        f.write((char*)&cus,sizeof(cus));
	}
	f.close();
	db.close();
	int ch = cin.get();
}

void datab()
{
    int n;
    cout<<"How many previous customers detail do you want to view-"<<endl;
    cin>>n;
    fstream db;
    db.open("datab.dat",ios::in|ios::binary);
    system("clear");
    db.seekg(0,ios::beg);
    
    for(int i=0;i<n;i++)
        cus.display();
    
    int ch = cin.get();
    db.close();
}

void append_customer()
{
    system("clear");
	fstream f,db;
	db.open("datab.dat",ios::app|ios::binary);
	f.open("list.dat",ios::app|ios::binary);
	cout<<"\n\n\t\t\t\tCustomer Booking\n";
	cout<<" Number of rooms available="<<tnoofrooms<<endl;
	cout<<"\nEnter the details of the customer(s)"<<"\n";
	cus.enter();
	f.write((char*)&cus,sizeof(cus));
	db.write((char*)&cus,sizeof(cus));
	f.close();
	int ch = cin.get();
}

void modify_customer()
{
	system("clear");
	fstream f1,f2;
	f1.open("list.dat",ios::in|ios::binary);
	f2.open("temp.dat",ios::out|ios::binary);

	int id;
	cout<<"\nEnter the ID of the customer to modify = ";
	cin>>id;
	while(f1.read((char*)&cus,sizeof(cus)))
	{
		if(cus.returnid()==id)
		{
			cout<<"Enter the new details:\n";
			cus.enter();
			cout<<"\nDetails modified!\n";
		}
		else
		    cout<<"\nCustomer not found!!\n";
		f2.write((char*)&cus,sizeof(cus));
	}
	f1.close();f2.close();
	remove("list.dat");
	rename("temp.dat","list.dat");
	int ch = cin.get();
}

void display_bill()
{       
    float total,amount1,amount2,vat;
	int noofdays;
    time_t now=time(0);
	char* dt = ctime(&now);
	fstream f,temp;
    f.open("list.dat",ios::in|ios::binary);
    temp.open("temp.dat",ios :: out|ios::binary);
    {   
        int id;
		system("clear");
		cout<<"Enter the ID of the person checking out-"<<endl;
		cin>>id;
		cout<<"===========================================================================\n";
		cout<<"\t\t\t\tBILL\n";
		cout<<"===========================================================================\n";
		cout<<endl<<"DATE: "<<dt<<'\n'<<endl;
		while(f.read((char*)&cus,sizeof(cus)))
		{
            if(cus.returnid()==id)
		    {   
                tnoofrooms=tnoofrooms+cus.returnnoofrooms();
                cus.display();
                cout<<"________________________________________________________________________________\n";
                cout<<"VAT = 5%\n";
                noofdays=cus.returnnoofdays();
                amount1=cus.amt();
                amount2=amount1*noofdays;
                vat=0.05*amount2;
                cout<<"VAT ="<<vat<<endl;
                total=amount2+vat;
                cout<<"Total = "<<total<<endl;
                cout<<"*****************************************************************************\n";
                cout<<"\t\tThank You For The Stay. Visit Again!!\n";
                cout<<"*****************************************************************************\n";

                while(cus.returnid()!=id)
                {
                    temp.write((char*)&cus,sizeof(cus));
                }
                int ch = cin.get();
                f.close();
                temp.close();
		    }
	    }
        remove("list.dat");
        rename("temp.dat","list.dat");
	}
}

int main()
{

	int ch1,ch2,ch3;
	char user[30],pass[30];

	while(1)
	{
		system("clear");
		cout<<"*******************************************************************************\n";
		cout<<"\t\t\t\t HOTEL REGENCY\n";
		cout<<"*******************************************************************************\n\n";
        cout<<"Welcome to Hotel Regency. We are a branch of the Taj Group and is given a 5-star rating."<<endl;
        cout<<"We offer 3 various types of rooms and we also offer different facilities such as Wifi,"<<endl;
		cout<<"Play Area, Health Club, Emergency First Aid etc."<<endl;
        cout<<"For more contact in email address:    hregency@taj.com"<<endl;
        cout<<"\n\t\t\tHotel Billing System\n\n";
		cout<<"Who do you want to login as?\n";
		cout<<"1 - Administrator\n2 - Customer\n3 - Exit\nEnter = ";
		cin>>ch1;
		
        switch(ch1)
		{
			case 1: system("clear");
				cout<<"\nEnter the username and password:-\n";

				cout<<"Username: ";
				cin>>user;
				if(strcmp(user,"gfjz")!=0)
				{
					cout<<"\nUsername does not match!\n";
					int ch = cin.get();
					break;
				}
				else
					cout<<"Password: ";
                gets(pass);

				if(strcmp(pass,"hotel123")!=0)
				{
					cout<<"\nPassword does not match!\n";
					int ch = cin.get();
					break;
				}
				else
				{
					system("clear");
					cout<<"\t\t\tMENU\n\n";
					cout<<"1 - Create staff list\n2 - Append staff list\n3 - Search for a particlular staff\n4 - Display staff list\n5 - Modify staff details\n6 - Dismiss a staff\n7 - Back to login page\n";
					cout<<"Enter = ";
					cin>>ch2;
					switch(ch2)
					{
						case 1:create_staff();break;
						case 2:append_staff();break;
						case 3:search_staff();break;
						case 4:display_staff();break;
						case 5:modify_staff();break;
						case 6:delete_staff();break;
						case 7:break;
						default:cout<<"\nInvalid option!!!\n";
						int ch = cin.get();
					}

					while(ch2!=7)
					{
						system("clear");
						cout<<"\t\t\tMENU\n\n";
						cout<<"1 - Create staff list\n2 - Append staff list\n3 - Search for a particular staff\n4 - Display staff list\n5 - Modify staff details\n6 - Dismiss a staff\n7 - Back to login page\n";
						cout<<"Enter = ";
						cin>>ch2;
						switch(ch2)
						{
						case 1:create_staff();break;
						case 2:append_staff();break;
						case 3:search_staff();break;
						case 4:display_staff();break;
						case 5:modify_staff();break;
						case 6:delete_staff();break;
						case 7:break;
						default:cout<<"\nInvalid option!!!\n";int ch = cin.get();
						}
					}
				}
            
            case 2:
                system("clear");
                cout<<"\t\t\tMENU\n\n";
                cout<<"1 - Create customer details\n2 - Modify list\n3 - Display the bill\n4 - Add more customers\n5 - Show Database\n6 - Back to login page\nEnter = ";
                cin>>ch3;

                switch(ch3)
                {
                    case 1:create_customer();break;
                    case 2:modify_customer();break;
                    case 3:display_bill();break;
                    case 4:append_customer();break;
                    case 5:datab();break;
                    case 6:break;
                    default:cout<<"\nInvalid option!!!\n";
                    int ch = cin.get();
                }
                
                while(ch3!=5)
                {
                    system("clear");

                    cout<<"\t\t\tMENU\n\n";
                    cout<<"1 - Create customer details\n2 - Modify list\n3 - Display the bill\n4 - Add more customers\n5 - Show Database\n6 - Back to login page\nEnter = ";
                    cin>>ch3;

                    switch(ch3)
                    {
                        case 1:create_customer();break;
                        case 2:modify_customer();break;
                        case 3:display_bill();break;
                        case 4:append_customer();break;
                        case 5:datab();break;
                        case 6:break;
                        default:cout<<"\nInvalid option!!!\n";
                        int ch = cin.get();
                    }
                }

            case 3: 
                exit(0);
            default:
                cout<<"\nInvalid option!!!\n";
            
            int ch = cin.get();
		}
    }
}