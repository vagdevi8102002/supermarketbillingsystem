#include<iomanip>
#include<iostream>
#include<fstream>
#include<cstdlib>
#include<string.h>
#include<stdio.h>
#include<conio.h>
#include<windows.h>
#include<time.h>
using namespace std;

fstream file;
//*****Global Functions*****//
void time()
{ 
    time_t tim;  //create variable
    time(&tim);  //pass variable to time function
    cout<<ctime(&tim);
}

void printstars() //for printing the stars as shown
{
    cout<<setw(55)<<"****************************\n"<<endl;

}

void display_nce()
{
    cout<<setw(51)<<"______________________"<<endl;
    cout<<setw(51)<<"|SUN_CITY SUPERMARKET|"<<endl;
    cout<<setw(51)<<"|____________________|"<<endl;
    printstars();
}

//********************//

//*****Class User*****//
class user
{
  private:
    char username[20];
    char password[20];
public:
    void add_user()
    {
    	char cpassword[20];
        cout<<"\n\n\t\t\tADD USER\n\n";
        cout<<"\n\t\tEnter the username and password\n";
        cout<<"\tUsername  :  ";
        cin>>username;
        cout<<"\tPassword  :  ";
        cin>>password;
        cout<<"\t Confirm Password  :  ";
        cin>>cpassword;
        if(strcmp(password,cpassword)==0)
        {
        file.open("user.txt",ios::app|ios::out);
        file.write(reinterpret_cast<char*>(this),sizeof(*this));
        file.close();
    	}
    	else
    	cout<<"Password does not match";
    	getch();
    }

    int verify()
    {
        display_nce();
        char u[20];
        char pass[20];
    	int i=0;
    	char a;
        int count=0;
        cout<<"\n\t\tPlease Enter the username and password\n";
        cout<<"\tUsername  :  ";
        cin>>u;
        cout<<"\tPassword  :  ";
    	for(;;)//infinte loop
    	{
        a=getch();
        if((a>='a'&&a<='z')||(a>='A'&&a<='Z')||(a>='0'&&a<='9'))
        {
            pass[i]=a;
            ++i;
            cout<<"*";
        }
        if(a=='\b'&&i>=1)
        {
            cout<<"\b \b";
            --i;
        }
        if(a=='\r')
        {
            pass[i]='\0';
            break;
        }
    	}
        file.open("user.txt",ios::in);
        file.seekg(0);
        file.read(reinterpret_cast<char*>(this),sizeof(*this));
        while(!file.eof())
        {
            if(strcmp(username,u)==0)
            {
                if(strcmp(password,pass)==0)
                {
                    count=1;
                }
            }
            file.read(reinterpret_cast<char*>(this),sizeof(*this));

        }
        file.close();
        return(count);
        }


};


//****Class Customer***//


class customer
{
    private:
        string fname;
        char add[50];
        string cn;

    public:
        void c_read();
        void c_display();
		bool isDigit(char);
		bool isAlpha(char);
};
bool customer::isDigit(char ch) 
{
    if (ch >= '0' && ch <= '9')
        return true;
    return false;
}
bool customer::isAlpha(char ch)
{
	if(ch>='A'&&ch<='Z'||ch>='a'&&ch<='z')
		return true;
	return false;
}
void customer::c_read()
{
    display_nce();
    cin.get();
    while(1)
    {
    	int f=0;
    	cout<<"Enter full name of the customer   :";
    	cin>>fname;
    	int length=fname.length();
    	for (int i = 0; i < length; i++) 
		{
        	if (isDigit(fname[i]))
			{
				cout<<"\nNumbers not allowed in name\n";
				cout<<"\nReenter your name please\n";
				f=1;
				break;
        	}
    	}
    	if(f==0)
    	break;
	}
    cin.get();
    cout<<"Enter address of the customer     :";
    cin.getline(add,50);
    while(1)
    {
    	int f=0;
    	cout<<"Enter contact no. of the customer :";
    	cin>>cn;
    	int length=cn.length();
    	for (int i = 0; i < length; i++) 
		{
        	if (isAlpha(cn[i]))
			{
				cout<<"\nAlphabets not allowed in contact number\n";
				cout<<"\nReenter your contact number please\n";
				f=1;
				break;
        	}
    	}
    	if(f==0)
    	break;
	}
    
}

void customer::c_display()
{
            cout<<"Customer Name     :  "<<fname<<endl;
            cout<<"Customer Address  :  "<<add<<endl;
            cout<<"Contact no.       :  "<<cn<<endl;
}
//*************************//

//*****Class Product********//

class product : public user
{
    protected:
    unsigned int id;
    char name[50];
    float rate;
    float dis;
 public:
	void create_product();
    void show_product();
    void display_all();
    void display_sp();
    void price_list();
    void modify_product();
    void delete_product();
    void fread()
    {
        file.read(reinterpret_cast<char*>(this),sizeof(*this));
    }
    void admin_menu();
};


void product::create_product()
{
	cout<<"\nEnter the product ID of the product : ";
    cin>>id;
    cout<<"\nEnter the Name of the product       : ";
    cin>>name;
    cout<<"\nEnter the Rate of the product      : ";
    cin>>rate;
    cout<<"\nEnter the Discount (%)              : ";
    cin>>dis;
    file.open("product.dat",ios::app|ios::out);
    file.write(reinterpret_cast<char*>(this),sizeof(*this));
    file.close();
    cout<<"\n\nThe Product Has Been Created.";
    getch();
}

void product::show_product()
{
    cout<<"***********";
    cout<<"\nProduct ID : "<<id;
    cout<<"\nName       : "<<name;
    cout<<"\nRate       : "<<"Rs. "<<rate;
    cout<<"\nDiscount   : "<<dis<<"%";
    cout<<"\n***********";
    }

void product::display_all()
{
    cout<<"\n\n\n\t\tDISPLAYING ALL RECORD\n\n";
    file.open("product.dat",ios::in);
    file.seekg(0);
    file.read(reinterpret_cast<char*>(this),sizeof(*this));
    while(!file.eof())
	{
        show_product();
        file.read(reinterpret_cast<char*>(this),sizeof(*this));
        cout<<"\n\n====================================\n\n";

	 }
	 file.close();
    getch();
}

void product::display_sp()
{
    int n,flag=0;
    cout<<"Enter the product id of the product to be displayed : ";
    cin>>n;
    file.open("product.dat",ios::in);
    file.seekg(0);
    while(!file.eof())
	{
	    file.read(reinterpret_cast<char*>(this),sizeof(*this));
	    if(id==n)
		{
		 system("cls");
		 show_product();
		 flag=1;
		}
	}
	file.close();
    if(flag==0)
    cout<<"\n\nRecord doesnot exist";
    getch();
}

void product::price_list()
{
    file.open("product.dat",ios::in);
    cout<<"====================================================\n";
    cout<<"\t\t\t\tProduct MENU\n";
    cout<<"====================================================\n";
    cout<<"Product ID\t\tNAME\t\tPRICE\n";
    file.seekg(0);
    file.read(reinterpret_cast<char*>(this),sizeof(*this));
    while(!file.eof())
    {
        cout<<id<<"\t\t\t"<<name<<"\t\t"<<rate<<endl;
        file.read(reinterpret_cast<char*>(this),sizeof(*this));
    }
    file.close();
    getch();
}

void product::modify_product()
{
    int n,pos,flag=0;
    cout<<"\n\nEnter the product ID of the product to modify : ";
    cin>>n;
    file.open("product.dat",ios::in|ios::out);
    while(!file.eof())
	{
        file.read(reinterpret_cast<char*>(this),sizeof(*this));
        if(id==n)
        {
            show_product();
            pos=int(-1*sizeof(*this));
            file.seekp(pos,ios::cur);
            cout<<"\nEnter the product ID of the product : ";
            cin>>id;
            cout<<"\nEnter the Name of the product       : ";
            cin>>name;
            cout<<"\nEnter the Rate of the product      : ";
            cin>>rate;
            cout<<"\nEnter the Discount (%)              : ";
            cin>>dis;
            file.write(reinterpret_cast<char*>(this),sizeof(*this));
            cout<<"\n\n\t Record Updated";
            flag=1;
         }
    }
    file.close();
    if(flag==0)
    cout<<"\n\nSorry! Record Not Found ";
    getch();
}

void product::delete_product()
{
	int n,f=0;
	char ch;
	file.open("product.dat",ios::in);
	fstream file2("temp.dat",ios::out);
	cout<<"\n\n\n\tDelete Record";
	cout<<"\n\nEnter the Product id of the Product to Delete  :  ";
    cin>>n;
    file.seekg(0);
    while(!file.eof())
    {
    	file.read(reinterpret_cast<char*>(this),sizeof(*this));
    	if(file.eof())
    	break;
    	if(id==n)
    	{
    		f=1;
    		show_product();
    		cout<<"\nDo you want to delete this record(y/n)\n";
    		cin>>ch;
    		if(ch=='Y'||ch=='y')
    		{
    			f=1;
			}
			else
			{
				f=2;
				file2.write(reinterpret_cast<char*>(this),sizeof(*this));
			}
		}
		else
		{
			file2.write(reinterpret_cast<char*>(this),sizeof(*this));
		}
	}
	if(f==0)
	cout<<"\nRecord Not Found";
	else
	{
		if(f==2)
		cout<<"\nRecord found but not deleted\n";
		else
		cout<<"\nRecord succesfully deleted";
	}
	file.close();
	file2.close();
	remove("product.dat");
	rename("temp.dat","product.dat");
	getch();
}

void product::admin_menu()
{
  char ch;
  while(1)
  {
    system("cls");
    cout<<"\n\n\t1.CREATE PRODUCT";
    cout<<"\n\t2.DISPLAY ALL PRODUCTS";
    cout<<"\n\t3.DISPALY SPECIFIC PRODUCT";
    cout<<"\n\t4.MODIFY PRODUCT";
    cout<<"\n\t5.DELETE PRODUCT";
    cout<<"\n\t6.DISPLAY PRICE LIST";
    cout<<"\n\t7.ADD USER";
    cout<<"\n\t8.BACK TO MAIN MENU";
    cout<<"\n\n\n\tEnter Your Choice : ";
    cin>>ch;
    switch(ch)
    {
        case '1':
            system("cls");
            system("COLOR 30");
            display_nce();
            create_product();
            break;
        case '2':
            system("cls");
            system("COLOR ea");
            display_nce();
            display_all();
            break;
        case '3':
            system("cls");
            system("COLOR 40");
            display_nce();
            display_sp();
            break;
        case '4':
            system("cls");
            system("COLOR b2");
            display_nce();
            modify_product();
            break;
        case '5':
            system("cls");
            system("COLOR 2e");
            display_nce();
            delete_product();
            break;
        case '6':
            system("cls");
            system("COLOR b4");
            display_nce();
            price_list();
            break;
        case '7':
            system("cls");
            system("COLOR 5f");
            display_nce();
            user::add_user();
            break;
        case '8':
        	system("COLOR 5f");
            goto leave;
            break;
        default:cout<<"Invalid Choice";
       }
       system("COLOR cf");
  }
  leave:
  cout<<" ";
}


//********************//

//******Class  BILL*******//

class bill : public product , public customer
{
  private :
    int  order_arr[50],quan[50];
    float amt,damt,total;
  public :
  	bill()
  	{
  		total=0;
	  }
    void place_order()
    {
        int n,count=0;
        system("cls");
        customer::c_read();
        system("cls");
        system("COLOR 5f");
        display_nce();
        cout<<"\n"<<setw(30)<<"How many items are there?";
        cin>>n;
        cout<<setw(25)<<"************\n";
        total=0;
        for(int i=0;i<n;i++)
        {
            cout<<"\n\nEnter the Product ID of the Product "<<i+1<<"  :  ";
            cin>>order_arr[i];
            cout<<"\nEnter the quantity of Product "<<i+1<<"  :  ";
            cin>>quan[i];
        }
        system("cls");
        system("COLOR f0");
        display_nce();
        cout<<"\n\n\t\t\t************INVOICE*************\n\n";
        cout<<setw(80);
        time(); 
        customer::c_display();
        cout<<"\n\n\n";
        cout<<"\nPr ID";
		cout<<setw(10)<<"Pr Name";
		cout<<setw(10)<<"Quantity"; 
		cout<<setw(10)<<"Price"; 
		cout<<setw(10)<<"Amount"; 
		cout<<setw(15)<<"Amount after discount";
        for(int x=0;x<n;x++)
        {
            file.open("product.dat",ios::in);
            file.seekg(0);
            product::fread();
            while(!file.eof())
            {
                if(id==order_arr[x])
                {
                    amt=rate*quan[x];
                    damt=amt-((amt*dis)/100);
                    cout<<"\n"<<order_arr[x];
					cout<<setw(10)<<name;
					cout<<setw(10)<<quan[x]; 
					cout<<setw(10)<<rate; 
					cout<<setw(10)<<amt; 
					cout<<setw(15)<<damt;
                    total+=damt;
                }
                product::fread();

            }
            file.close();
        }
        cout<<"\n\n===============================================================================";
        if(total>=2000)
        {
			cout<<"\n\n\t\t\t\t\t\t\t\tAdditional 5% discount";
        	total=total-(0.05*total);
    	}
        cout<<"\n\n\t\t\t\t\t\t\t\tTOTAL = "<<total;
        getch();
        }
};
//******************//
void display_main()
{
    display_nce();
    cout<<setw(45)<<"\t\t _________________"<<endl;
    cout<<setw(46)<<"\t\t|***MAIN   MENU***|"<<endl;
    cout<<setw(46)<<"\t\t|_________________|"<<endl;
    cout<<"\n";
    cout<<setw(60);
    cout<<"\n\t\t<1>Place Order"<<
          "\n\t\t<2>Admin Panel"<<
          "\n\t\t<3>Log out"<<
          "\n\t\t<4>Exit"<<endl;

}

void start_screen()
{
   string str1,str2,str3,str4,str5,str6;
    str1="A PROJECT ON";
    str2="SUPER MARKET BILLING SYSTEM";
    str3="MADE BY:";
    str4="TANU ANEJA                 20BCS4177";
    str5="SREE VAGDEVI KANDUKURI     20BCS4182";
    str6="SHIVANG                    20BCS4149";
    cout<<"\n\n\n\n\t\t\t\t";
    for(int i=0;i<13;i++)
    {
        cout<<str1[i];
        Sleep(200);
    }
    cout<<"\n\n\t\t\t";
    for(int i=0;i<28;i++)
    {
        cout<<str2[i];
        Sleep(200);
    }
    system("cls");
    cout<<"\n\n\n\t\t\t******************************"<<
    "\n\t\t\t*A PROJECT ON                *"<<
    "\n\t\t\t*                            *"<<
    "\n\t\t\t*SUPER MARKET BILLING SYSTEM *"<<
    "\n\t\t\t******************************\n";
    Sleep(1000);
    cout<<"\n\n\t\t\t";
    for(int i=0;i<8;i++)
    {
        cout<<str3[i];
        Sleep(200);
    }
    cout<<"\n\n\t\t\t";
    for(int i=0;i<36;i++)
    {
        cout<<str4[i];
        Sleep(200);
    }
    cout<<"\n\n\t\t\t";
    for(int i=0;i<36;i++)
    {
        cout<<str5[i];
        Sleep(200);
    }
    cout<<"\n\n\t\t\t";
    for(int i=0;i<36;i++)
    {
        cout<<str6[i];
        Sleep(200);
    }
    Sleep(1000);
 }
//*****MAIN PROGRAM*****//

int main()
{

    int choice,ch,v;
    user ur;
    product pr;
    bill bi;
    system("COLOR b4");
    start_screen();
    system("cls");
    main:
    for(int c=1;c<=3;c++)
    {
    	system("COLOR a0");
        v=ur.verify();
        if(v==1)
        {
			system("COLOR 5f");
        while(1)
        {
            system("cls");
            display_main();
            cout<<"\n\t\tEnter your choice  :  ";
            cin>>choice;
            switch(choice)
            {
                case 1:
                    system("cls");
                    system("COLOR 34");
                    bi.place_order();
                    break;

                case 2:
                    system("cls");
                    system("COLOR cf");
                    display_nce();
                    pr.admin_menu();
                    break;

                case 3:
                    system("cls");
                    goto main;
                    break;
                case 4:
                    exit(0);
                    break;

                default :
                    cout<<"Invalid choice";
                }
            system("COLOR 5f");    
            }

        }
        else
        {
            cout<<"\n\n\tWrong username or password.\n\n"<<endl;
            printstars();
            cout<<"\n\n\t You have "<<3-c<<" chances left.";
            getch();
            system("cls");
        }
    }
    return 0;
}
