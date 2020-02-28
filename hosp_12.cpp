//This is my CBSE 12th project on hospital database management
//This is programmed in cpp03


#include<fstream.h>
#include<conio.h>
#include<stdio.h>
#include<string.h>
#include<process.h>
#include<dos.h>

class patient
{
	int pid,room,age;
	char name[30],sex[15],bg[5],p_doc[30];
	char disease[30],cond[20];

	public:

	void get_gender();
	void get_bg();
	void assign_room();
	void appoint_doc();
	void get_info(int);
	void disp()
	{
		cout<<"\n\nPatient id : "<<pid<<"\t\tPatient name : "<<name<<"\nBlood Group : "<<bg<<"\tAge : "<<age<<"\t Sex : "<<sex;
		cout<<"\nDisease : "<<disease<<"\t\tCondition : "<<cond;
		cout<<"\nRoom no. : "<<room;
		cout<<"\nDoctor : "<<p_doc;
		cout<<"\n\n";
	}
	int ret_pid()
	{	return(pid);
	}
	int ret_room()
	{	return(room);
	}
	char* ret_doc()
	{	return(p_doc);
	}
	void cancel()
	{	p_doc[0]='\0';
	}
	void modify();
}p;

class staff
{
	char name[30],pos[15];
	int id;
	char speciality[30];
	long pno,salary;

	public:

	void get_pos();
	void get_info(int);
	void disp()
	{	cout<<"\nName : "<<name<<"\t\tID : "<<id<<"\nPosition : "<<pos;
		if(strcmpi(pos,"Doctor")==0)
			cout<<"\t\t Speciality : "<<speciality;
		cout<<"\nSalary : "<<salary<<"\t\tContact no. : "<<pno;
	}
	void modify();
	int ret_id()
	{	return(id);
	}
	char* ret_p()
	{	return(pos);
	}
	char* ret_name()
	{	return(name);
	}
}s;

class room
{
	int rno,price;
	char avail[15],type[10];

	public:

	void get_info(int);
	void disp()
	{	cout<<"\n"<<rno<<"\t"<<type<<"\t"<<price<<"\t"<<avail;
	}
	int ret_no()
	{	return rno;
	}
	char* ret_avail()
	{	return(avail);
	}
	int ret_price()
	{	return(price);
	}
	void change()
	{	strcpy(avail,strcmpi(avail,"available")?"available":"unavailable");
	}
}r;


void patient::get_info(int a)
{
	assign_room();
	pid=a;
	p_doc[0]='\0';
	cout<<"Enter patient name :";
	gets(name);
	get_gender();
	get_bg();
	cout<<"Enter age:";
	cin>>age;
	cout<<"Enter Disease :";
	gets(disease);
	cout<<"Enter condition of the patient :";
	gets(cond);

}

void patient::get_gender()
{
	int ch;
	cout<<"\nSex :\n 1.Male\n 2.Female\n 3.Transgender\n";
	while(1)
	{
		cin>>ch;
		if(ch==1)
		{	strcpy(sex,"Male");
			break;
		}
		else if(ch==2)
		{	strcpy(sex,"Female");
			break;
		}
		else if(ch==3)
		{	strcpy(sex,"Transgender");
			break;
		}
		else
		{	cout<<"Wrong choice..\nPlease enter again:";
		}
	}
}

void patient::get_bg()
{
	cout<<"\nEnter Blood Group :";
	while(1)
	{
		gets(bg);
		if(strcmp(bg,"A+")&&strcmp(bg,"A-")&&strcmp(bg,"B+")&&strcmp(bg,"B-")&&strcmp(bg,"O+")&&strcmp(bg,"O-")&&strcmp(bg,"AB+")&&strcmp(bg,"AB-"))
			cout<<"Enter a valid group :";
		else
			break;       	}
}

void patient::assign_room()
{
	int flag=0,n;
	while(flag==0)
	{       fstream file("Room.DAT",ios::binary|ios::in|ios::out);
		cout<<"Enter room no. from one of the above diplayed :";
		cin>>n;
		while(file.read((char*)&r,sizeof(r)))
		{	if(n==r.ret_no()&&strcmpi(r.ret_avail(),"available")==0)
			{	flag=1;
				r.change();
				file.seekp((file.tellg()-sizeof(r)),ios::beg);
				file.write((char*)&r,sizeof(r));
				break;
			}
		}
		file.close();
	}
	room=n;
}

void patient::appoint_doc()
{
	int flag=0,n,c=0;
	ifstream infile("Staff.DAT",ios::binary);
	while(infile.read((char*)&s,sizeof(s)))
	{
		if(strcmpi(s.ret_p(),"Doctor")==0)
		{	s.disp();
			c++;
		}
	}
	infile.close();
	if(c==0)
	{
		cout<<"No Doctors Available..";
	}
	else
	{	while(flag==0)
		{
			ifstream in("Staff.DAT",ios::binary);
			cout<<"\n\nEnter the id of doctor(displayed above) for appointment :";
			cin>>n;
			while(in.read((char*)&s,sizeof(s)))
			{       if((s.ret_id()==n)&&strcmpi(s.ret_p(),"Doctor")==0)
				{       strcpy(p_doc,s.ret_name());
					flag=1;
					break;
				}
			}
			infile.close();
		}
	}
}

void patient::modify()
{
	char ch;
	disp();
	cout<<"\nWhich attribute you want to modify :";
	cout<<"\n 1.Name\n 2.Condition\n 3.Blood Group\n 4.Sex\n 5.Age";
	cout<<"\nEnter ur choice : ";
	cin>>ch;
	switch(ch)
	{
		case '1':cout<<"\nEnter name : ";
			gets(name);
			break;
		case '2':cout<<"\nEnter condition : ";
			 gets(cond);
			 break;
		case '3':get_bg();
			 break;
		case '4':get_gender();
			 break;
		case '5':cout<<"\nEnter age : ";
			 cin>>age;
			 break;
		default:cout<<"\nWrong choice..";
	}
}


void staff::get_info(int a)
{
	cout<<"\nEnter name:";
	gets(name);
	id=a;
	get_pos();
	cout<<"\nEnter salary:";
	cin>>salary;
	cout<<"\nEnter contact no.:";
	cin>>pno;
}

void staff::get_pos()
{
	int ch;
	cout<<"\nEnter poition :";
	cout<<"\n 1.Doctor\n 2.Nurse\n 3.Cleaner\n 4.Other\n";
	while(1)
	{
		cin>>ch;
		if(ch==1)
		{	strcpy(pos,"Doctor");
			cout<<"\nEnter speciality :";
			gets(speciality);
			break;
		}
		else if(ch==2)
		{	strcpy(pos,"Nurse");
			break;
		}
		else if(ch==3)
		{	strcpy(pos,"Cleaner");
			break;
		}
		else if(ch==4)
		{       cout<<"\nEnter the position :";
			gets(pos);
			break;
		}
		else
		{       cout<<"\nPlease enter correct option";
		}
	}
}

void staff::modify()
{
	char ch;
	disp();
	cout<<"\nWhich attribute you want to modify :";
	cout<<"\n 1.Name\n 2.Postion & Speciality\n 3.Salary\n 4.Contact No.";
	cout<<"\nEnter ur choice : ";
	cin>>ch;
	switch(ch)
	{
		case '1':cout<<"\nEnter name : ";
			 gets(name);
			 break;
		case '2':if(strcmpi(pos,"Doctor")==0)
			 {	cout<<"\nCan change only speciality for doctors";
				cout<<"\nEnter speciality : ";
				gets(speciality);
			 }
			 else
				get_pos();
			 break;
		case '3':cout<<"\nEnter salary : ";
			 cin>>salary;
			 break;
		case '4':cout<<"\nEnter new contact no. : ";
			 cin>>pno;
			 break;
		default:cout<<"\nWrong choice..";
	}
}

void room::get_info(int a)
{
	int ch;
	rno=a;
	cout<<"\nSelect type:\n 1. General\n 2. V.I.P.\n 3. ICU\n";
	while(1)
	{
		cin>>ch;
		if(ch==1)
		{	strcpy(type,"General");
			price=1000;
			break;
		}
		else if(ch==2)
		{	strcpy(type,"V.I.P");
			price=2500;
			break;
		}
		else if(ch==3)
		{	strcpy(type,"ICU");
			price=4000;
			break;
		}
		else
			cout<<"Wrong choice";
	}
	strcpy(avail,"available");
}


void add_room()
{
	int n;
	char ch='y';
	while(ch=='y'||ch=='Y')
	{
		cout<<"Room information :\n";
		B:
		ifstream infile("Room.DAT",ios::binary);
		cout<<"\nEnter room no :";
		cin>>n;
		while(infile.read((char*)&r,sizeof(r)))
		{	if(r.ret_no()==n)
			{	cout<<"\nA similar room no. exists.";
				cout<<"\nPlease enter a different no.";
				goto B;
			}
		}
		infile.close();
		r.get_info(n);
		ofstream out("Room.DAT",ios::binary|ios::app);
		out.write((char*)&r,sizeof(r));
		out.close();
		cout<<"\nWish to continue(y/n):";
		cin>>ch;
	}
}


void admit_patient()
{
	int n,c;
	char ch='y';
	while(ch=='y'||ch=='Y')
	{
		c=0;
		cout<<"Patient information :\n";
		A:
		ifstream infile("Patient.DAT",ios::binary);
		cout<<"\nEnter patient id : ";
		cin>>n;
		while(infile.read((char*)&p,sizeof(p)))
		{
			if(p.ret_pid()==n)
			{	cout<<"\nA patient with similar id is admitted.";
				cout<<"\nPlease enter a different no...";
				goto A;
			}
		}
		infile.close();
		ifstream in("Room.DAT",ios::binary);
		cout<<"\nAvailable rooms : \n";
		while(in.read((char*)&r,sizeof(r)))
		{	if(strcmpi(r.ret_avail(),"available")==0)
			{	r.disp();
				cout<<"\n";
				c++;
			}
		}
		in.close();
		if(c==0)
		{	cout<<"NoNe";
			cout<<"\nPlease add a room...";
			break;
		}
		p.get_info(n);
		ofstream out("Patient.DAT",ios::binary|ios::app);
		out.write((char*)&p,sizeof(p));
		cout<<"\nWish to continue(y/n):";
		out.close();
		cin>>ch;
	}
}


void add_staff()
{
	int n;
	char ch='y';
	while(ch=='y'||ch=='Y')
	{
		cout<<"Staff information :\n";
		C:
		ifstream infile("Staff.DAT",ios::binary);
		cout<<"\nEnter staff id : ";
		cin>>n;
		while(infile.read((char*)&s,sizeof(s)))
		{	if(s.ret_id()==n)
			{	cout<<"\nA staff with similar id works.";
				cout<<"\nEnter a differnet no.";
				goto C;
			}
		}
		s.get_info(n);
		ofstream out("Staff.DAT",ios::binary|ios::app);
		out.write((char*)&s,sizeof(s));
		cout<<"\nWish to continue(y/n):";
		cin>>ch;
		out.close();
	}
}

void appointment()
{
	int n,flag=0;
	cout<<"\nEnter patient id : ";
	cin>>n;
	fstream file("Patient.DAT",ios::binary|ios::in|ios::out);
	while(file.read((char*)&p,sizeof(p)))
	{
		if(p.ret_pid()==n)
		{	p.appoint_doc();
			file.seekp(file.tellg()-sizeof(p),ios::beg);
			file.write((char*)&p,sizeof(p));
			cout<<"\nThe appointment has been scheduled..";
			flag=1;
			break;
		}
	}
	if(flag==0)
		cout<<"\nNo such patient found..";
	file.close();
}


void search_p()
{
	int n,flag=0;
	cout<<"\nEnter patient id : ";
	cin>>n;
	ifstream infile("Patient.DAT",ios::binary);
	while(infile.read((char*)&p,sizeof(p))&&flag==0)
	{
		if(p.ret_pid()==n)
		{	p.disp();
			flag=1;
		}
	}
	if(flag==0)
		cout<<"\nNo such patient found..";
	infile.close();
}


void search_s()
{
	int n,flag=0;
	cout<<"\nEnter staff id : ";
	cin>>n;
	ifstream infile("Staff.DAT",ios::binary);
	while(infile.read((char*)&s,sizeof(s))&&flag==0)
	{
		if(s.ret_id()==n)
		{	s.disp();
			flag=1;
		}
	}
	if(flag==0)
		cout<<"\nNo such staff found..";
	infile.close();
}

void show_patient()
{
	ifstream infile("Patient.DAT",ios::binary);
	while(infile.read((char*)&p,sizeof(p)))
	{	p.disp();
	}
	infile.close();
}

void show_staff()
{
	ifstream infile("Staff.DAT",ios::binary);
	while(infile.read((char*)&s,sizeof(s)))
	{	s.disp();
	}
	infile.close();
}

void show_room()
{
	ifstream infile("Room.DAT",ios::binary);
	while(infile.read((char*)&r,sizeof(r)))
	{	r.disp();
	}
	infile.close();
}




void modify_p()
{
	int n,flag=0;
	cout<<"\nEnter ID of the patient : ";
	cin>>n;
	fstream file("Patient.DAT",ios::binary|ios::in|ios::out);
	while(file.read((char*)&p,sizeof(p)))
	{	if(p.ret_pid()==n)
		{	p.modify();
			flag=1;
			file.seekp(file.tellg()-sizeof(p),ios::beg);
			file.write((char*)&p,sizeof(p));
			break;
		}
	}
	if(flag==0)
		cout<<"\nPatient not found.";
	file.close();
}

void modify_s()
{
	int n,flag=0;
	cout<<"\nEnter ID of the staff : ";
	cin>>n;
	fstream file("Staff.DAT",ios::binary|ios::in|ios::out);
	while(file.read((char*)&s,sizeof(s)))
	{	if(s.ret_id()==n)
		{	s.modify();
			flag=1;
			file.seekp(file.tellg()-sizeof(s),ios::beg);
			file.write((char*)&s,sizeof(s));
			break;
		}
	}
	if(flag==0)
		cout<<"\nStaff not found.";
	file.close();
}

void discharge()
{
	int n,flag=0,r_charge,charge;
	ifstream infile("Patient.DAT",ios::binary);
	ofstream out("Temp.DAT",ios::binary);
	fstream file("Room.DAT",ios::binary|ios::in|ios::out);
	cout<<"\nEnter ID of the patient to dicharge : ";
	cin>>n;
	while(infile.read((char*)&p,sizeof(p)))
	{	if(p.ret_pid()!=n)
			out.write((char*)&p,sizeof(p));
		else
		{	while(file.read((char*)&r,sizeof(r)))
			{	if(r.ret_no()==p.ret_room())
				{	r.change();
					r_charge=r.ret_price();
					file.seekp(file.tellg()-sizeof(r),ios::beg);
					file.write((char*)&r,sizeof(r));
					break;
				}
			}
			flag=1;
		}
	}
	if(flag==0)
		cout<<"\nPatient not found..";
	else
	{	cout<<"\nEnter medical, appointment, operational, etc. charges : ";
		cin>>charge;
		cout<<"\nTotal Bill : "<<(r_charge+charge);
		cout<<"\nPlease pay the bill and the patient will be soon discharged..";
	}
	infile.close();
	out.close();
	file.close();
	remove("Patient.DAT");
	rename("Temp.DAT","Patient.DAT");
}


void remove_Staff()
{
	int n,flag=0;
	ifstream infile("Staff.DAT",ios::binary);
	ofstream out("Temp.DAT",ios::binary);
	fstream file("Patient.DAT",ios::binary|ios::in|ios::out);
	cout<<"\nEnter ID of the staff to remove : ";
	cin>>n;
	while(infile.read((char*)&s,sizeof(s)))
	{	if(s.ret_id()!=n)
			out.write((char*)&s,sizeof(s));
		else
		{       if(strcmpi(s.ret_p(),"Doctor")==0)
			{
				while(file.read((char*)&p,sizeof(p)))
				{	if(!strcmpi(p.ret_doc(),s.ret_name()))
					{	p.cancel();
						file.seekp(file.tellg()-sizeof(p),ios::beg);
						file.write((char*)&p,sizeof(p));
						break;
					}
				}
			}
			flag=1;
		}
	}
	if(flag==0)
		cout<<"\nStaff not found..";
	else
		cout<<"\nThe staff has been removed.";
	infile.close();
	out.close();
	file.close();
	remove("Staff.DAT");
	rename("Temp.DAT","Staff.DAT");

}


void pMenu()
{
	clrscr();
	int ch;
	do
	{       clrscr();
		cout<<"\n\n\t\tPATIENT DATABASE..";
		cout<<"\n 01. ADMIT PATIENT";
		cout<<"\n 02. DISPLAY ALL PATIENTS' INFO";
		cout<<"\n 03. APPOINT DOCTOR";
		cout<<"\n 04. SEARCH PATIENT";
		cout<<"\n 05. DISCHARGE PATIENT";
		cout<<"\n 06. MODIFY PATIENT";
		cout<<"\n 07. RETURN TO MAIN MENU";
		cout<<"\n Please Select Your Option(1-7) : ";
		cin>>ch;
		switch(ch)
		{
			case 1:clrscr();
				 admit_patient();
				 getch();
				 break;

			case 2:clrscr();
				 show_patient();
				 getch();
				 break;

			case 3:clrscr();
				 appointment();
				 getch();
				 break;

			case 4:clrscr();
				 search_p();
				 getch();
				 break;

			case 5:clrscr();
				 discharge();
				 getch();
				 break;

			case 6:clrscr();
				  modify_p();
				  getch();
				  break;

			case 7:cout<<"\n\nReturning To Main Menu.";
				  delay(500);
				  break;

			default:cout<<"\nWrong Choice.";
				  getch();

		}
	}while(ch!=7);
}

void sMenu()
{
	clrscr();
	int ch;
	do
	{       clrscr();
		cout<<"\n\n\t\tSTAFF DATABASE..";
		cout<<"\n 01. ADD STAFF";
		cout<<"\n 02. DISPLAY ALL STAFF INFO";
		cout<<"\n 03. SEARCH STAFF";
		cout<<"\n 04. REMOVE STAFF";
		cout<<"\n 05. MODIFY STAFF";
		cout<<"\n 06. RETURN TO MAIN MENU";
		cout<<"\n Please Select Your Option(1-6) : ";
		cin>>ch;
		switch(ch)
		{
			case 1:clrscr();
				 add_staff();
				 getch();
				 break;

			case 2:clrscr();
				 show_staff();
				 getch();
				 break;

			case 3:clrscr();
				 search_s();
				 getch();
				 break;

			case 4:clrscr();
				 remove_Staff();
				 getch();
				 break;

			case 5:clrscr();
				 modify_s();
				 getch();
				 break;

			case 6:cout<<"\n\nReturning To Main Menu";
				 delay(500);
				 break;

			default:cout<<"Wrong Choice";
				 getch();

		}
	}while(ch!=6);
}

void rMenu()
{
	clrscr();
	int ch;
	do{
		clrscr();
		cout<<"\n\n\t\tROOM DATABASE..";
		cout<<"\n 01. ADD ROOM";
		cout<<"\n 02. DISPLAY ROOMS' INFORMATION";
		cout<<"\n 03. RETURN TO MAIN MENU";
		cout<<"\n Please Select Your Option(1-3) : ";
		cin>>ch;
		switch(ch)
		{
			case 1:clrscr();
				 add_room();
				 getch();
				 break;

			case 2:clrscr();
				 show_room();
				 getch();
				 break;

			case 3:cout<<"\n\nReturning To Main Menu.";
				  delay(500);
				  break;

			default:cout<<"\nWrong Choice.";
				  getch();

		}
	}while(ch!=3);
}



void main()
{
	clrscr();
	int ch,i;
	do
	{
		clrscr();
		cout<<"\n\n\t\t\t HOSPITAL MANAGEMENT SYSTEM...\n";
		cout<<"\n\n\t\t MAIN MENU \n";
		cout<<"\n 01. PATIENT DATABASE";
		cout<<"\n 02. STAFF DATABASE";
		cout<<"\n 03. ROOM DATABASE";
		cout<<"\n 04. EXIT";
		cout<<"\n Please Select Your Option(1-4) : ";
		cin>>ch;
		switch(ch)
		{
			case 1:pMenu();
				 break;

			case 2:sMenu();
				 break;

			case 3:rMenu();
				 break;

			case 4:cout<<"\n\n\t\t\t\t Quitting";
				 for(i=0;i<3;i++)
				 {
					delay(400);
					cout<<".";
				  }
				  delay(400);
				  exit(0);

			default :cout<<"\nWrong Choice\n";
				  getch();
		}
	}while(ch!=4);
}
