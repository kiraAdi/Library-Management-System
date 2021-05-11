#include <iostream>
#include<string>
#include<stdlib.h>
#include<fstream>
#include<cstring>
#include<sstream>
#include<ctime>
#include<string.h>
#include <cstdio>
#include <iomanip>
#include<bits/stdc++.h>
#include<regex>
using namespace std;
#define MAX 200

int i=0,j=0,k1,k2,k3,k=0;
string users[MAX];
string passw[MAX];
int stud[MAX];
string cho;
string lineu,linep,lines,temp,temp1;

class login
{
private:
  string user;
  string pass;
public:
  int check();
  string regis();
  void disp();
  void change_pass();
  void exit();
  void append();
  int initial();
};

class book
{
private:
    int number;
public:
    void due_details();
    void check_in();
    void check_out();
    void date_enroll();
    void reset_enroll();
};

class student
{
private:
    string stu_name;
    int stu_id;
public:
    void add_stu();
    int edit_stu();
    void view_det(int w);
    void list_ofall();
    int initial();
};

/// Add student to database for able to issue books
void student :: add_stu()
{
  cout<<"----------------------"<<endl;
  cout<<"Enter the name of student to add: ";
  cin>>stu_name;
  cout<<"Enter the student ID(only numbers): ";
  cin>>stu_id;
  cout<<"----------------------"<<endl;
  fstream studentfile("stu.txt",ios::app);
  studentfile<<stu_name<<" ";
  studentfile<<stu_id<<endl;
  stud[k]=stu_id;
  studentfile.close();
  k=k+1;
}

/// View the details of particular student
void student :: view_det(int w)
{
  time_t tt;
  struct tm * ti;
  time (&tt);
  ti = localtime(&tt);
  time_t now = time(0);
  struct tm *ltm = localtime(&now);

  fstream studentfile("stu.txt",ios::in);

  cout<<endl;
  int y=0;
  while(y<k)
  {
    if(stud[y]==w)
    {
      break;
    }
    y++;
  }
  y=y+1;
  if(y==k+1)
  {
    cout<<"----------------------"<<endl;
    cout<<"Not found"<<endl;
    cout<<"----------------------"<<endl;
  }
  else
  {
    cout<<"----------------------"<<endl;
    cout<<"The entered ID is in line no.: "<<y<<endl;
    fstream studentfile("stu.txt",ios::in);
    int lineno=0;
    do
    {
        if (lineno == y)
        {
            cout <<"Student name and ID: "<<lines<< endl;
            cout<<"----------------------"<<endl;
            break;
        }
        lineno++;

    }
    while(getline(studentfile,lines));
    fstream file ("book.txt",ios::in);
    string str;
    cout<<"The list of checked out books under ID: "<<w<<endl;
    while(getline(file,str))
    {
      smatch matches;
      regex reg2("([0-9]+)");
      regex_search(str,matches,reg2);
      if(matches.str(1)==to_string(w))
      {
        regex reg("[0-9]+ (.*)");
        sregex_iterator currentmatch(str.begin(),str.end(),reg);
        sregex_iterator lastmatch;
        
        while(currentmatch!=lastmatch)
        {
            smatch match=*currentmatch;
            cout<<matches.str(1)<<": "<<match.str()<<endl;

            smatch mat;
            regex rew("[0-9A-Za-z .]*([0-9][0-9]/[0-9][0-9]/[0-9][0-9][0-9][0-9])");
            regex_search(str,mat,rew);
            if(regex_search(str,mat,rew))
            {
              string k;
              k=mat.str(1);

              // Checking for fine starts //
              int date1,month1,year1;
              smatch date2;smatch month2;smatch year2;
              regex reg1("([0-9][0-9])/[0-9][0-9]/[0-9][0-9][0-9][0-9]");
              regex reg2("[0-9][0-9]/([0-9][0-9])/[0-9][0-9][0-9][0-9]");
              regex reg3("[0-9][0-9]/[0-9][0-9]/([0-9][0-9][0-9][0-9])");
              regex_search(k,date2,reg1);
              regex_search(k,month2,reg2);
              regex_search(k,year2,reg3);
              int temp_date,temp_month,temp_year;
              smatch matches;
              regex reg("([0-9][0-9]/[0-9][0-9]/[0-9][0-9][0-9][0-9])");
              regex_search(k,matches,reg);

              if(regex_search(k,matches,reg))
              {
                if(stoi(year2[1]) < 1900+ltm->tm_year)
                {
                  cout<<"---> Passed by year. Huge Fine has to be paid for this book"<<endl;
                }
                else if(stoi(year2[1]) > 1900+ltm->tm_year)
                {
                  cout<<"---> The check in date will come soon. No need to worry"<<endl;
                }
                else
                {
                  if(stoi(month2[1]) < 1+ltm->tm_mon)
                  {
                    cout<<"---> Passed by month. Huge Fine has to be paid for this book"<<endl;
                  }
                  else if(stoi(month2[1]) > 1+ltm->tm_mon)
                  {
                    cout<<"---> The check in date will come soon. No need to worry"<<endl;
                  }
                  else
                  {
                    if(stoi(date2[1]) < ltm->tm_mday)
                    {
                      cout<<"---> Passed by date. Fine has to be paid for the this book"<<endl;
                    }
                    else if(stoi(date2[1]) > ltm->tm_mday)
                    {
                      cout<<"---> The check in date will come soon. No need to worry"<<endl;
                    }
                    else
                    {
                      cout<<"---> The book has been issued today !!"<<endl;
                    }
                  }
                }
              }
              // Checking for fine ends //

            }

            
            currentmatch++;
        }
        
      }
    }
    cout<<"----------------------"<<endl;
    cout<<endl;
    file.close();
  }
    
}

/// Edit the details of particular student (issue or return)
int student :: edit_stu()
{ 
  cout<<'\n';
  int id_temp;
  cout<<"----------------------"<<endl;
  cout<<"Enter the student ID: ";
  cin>>id_temp;
  int i=0;
  while(i<MAX)
  {
    if(id_temp==stud[i])
    {
      k3=id_temp;
      cout<<"----------------------"<<endl;
      cout<<"1:Issue (check out) a book\n2:Return (check in) a book\n";
      book b;
      int choice2;
      cin>>choice2;
      switch(choice2)
      {
        case 1:
        {
          b.check_out();
          break;
        }
        case 2:
        {
          b.check_in();
          break;
        }
        default:
        {
          cout<<"----------------------"<<endl;
          cout<<"Incorrect entry"<<endl;
          cout<<"----------------------"<<endl;
          break;
        }
      }

      break;
    }
    else
    {
      i++;
    }
    if(i==MAX)
    {
      cout<<"----------------------"<<endl;
      cout<<"No student found"<<endl;
      cout<<"----------------------"<<endl;
    }
  }

  return k3;
}

/// Check out of book (issuing the book)
void book :: check_out()
{
  string book;
  fstream booklist("book.txt",ios::app | ios::out);
  cout<<"----------------------"<<endl;
  cout<<"Enter the number books to be issued: ";
  cin>>number;
  int i=0;
  cin.ignore();
  time_t tt;
  struct tm * ti;
  time (&tt);
  ti = localtime(&tt);
  cout<<"----------------------"<<endl;
  cout << "Issue Day, Date and Time is: " <<endl;
  cout<<"Day Month Date Time Year"<<endl;
  cout<<asctime(ti);
  cout<<"----------------------"<<endl;
  time_t now = time(0);
  struct tm *ltm = localtime(&now);
  int upload_temp;
  char upload[50];
  upload_temp=sprintf(upload,"%02d/%02d/%04d",ltm->tm_mday,1+ltm->tm_mon,1900 + ltm->tm_year);

  while(i<number)
  {
    cout<<"----------------------"<<endl;
    cout<<"Enter the name of book: ";
    getline(cin,book);
    booklist<<k3<<" "<<book<<" "<<upload<<endl;
    i++;
  }
  cout<<"----------------------"<<endl;
  cout<<"Books issued"<<endl;
  cout<<"----------------------"<<endl;
  booklist.close();
}

/// Printing all Students who have took membership
void student :: list_ofall()
{
  cout<<"----------------------"<<endl;
  string alpha("");
  string num("");
  fstream studentfile("stu.txt",ios::in);
  string temp;
  while(getline(studentfile,temp))
  {
    for (int i=0; i<temp.length(); i++)
    {

      if((temp[i] >= 'A' && temp[i] <= 'Z') ||
              (temp[i] >= 'a' && temp[i] <= 'z') ||
              (temp[i]==' '))
      {
          alpha=alpha+temp[i];

      }
      if (isdigit(temp[i]))
      {
        num=num+temp[i];

      }
    }
    cout<<"Student name: "<<alpha <<"---";
    cout<<"Student ID: "<<num << endl;
    num="";
    alpha="";

  }
  cout<<"----------------------"<<endl;
  studentfile.close();
}

/// Check in of book by student (Returning the book)
void book :: check_in()
{
  string stri;
  string str,ee[MAX];
  int h;
  int j=0;
  fstream file("book.txt",ios::in);
  while(getline(file,str))
  {
      smatch matches;
      regex reg2("([0-9]+)");
      regex_search(str,matches,reg2);
      if(matches.str(1)==to_string(k3))
      {
        regex reg("[0-9]+ (.*)");
        sregex_iterator currentmatch(str.begin(),str.end(),reg);
        sregex_iterator lastmatch;
        while(currentmatch!=lastmatch)
        {
            smatch match=*currentmatch;
            ee[j]=match.str();
            currentmatch++;
        }
        j++;
      }
  }
  file.close();
  if(j==0)
  {
    cout<<"----------------------"<<endl;
    cout<<"No entry found in that ID"<<endl;
    cout<<"----------------------"<<endl;
  }
  else
  {
    cout<<"----------------------"<<endl;
    cout<<"what do u want to remove in: "<<endl;
    for (int i=0;i<j;i++)
    {
      cout<<i+1<<": "<<ee[i]<<endl;
    }
    cout<<"----------------------"<<endl;
    cin>>h;
    int i;
    int c=0;
    for(i=0;i<j;i++)
    {
      if(ee[i]!=ee[h-1])
      {
        c++;
      }
      else
      {
        fstream f("book.txt",ios::in);
        fstream temp("temp.txt",ios::out);
        while (getline(f, stri))
        {
        if (stri != ee[h-1])
        {
            temp<<stri<<endl;
        }
        }
        f.close();
        temp.close();
        remove("book.txt");
        rename("temp.txt","book.txt");
      }
    }
    
    if(c==j)
    {
      cout<<"----------------------"<<endl;
      cout<<"Not found"<<'\n';
      cout<<"----------------------"<<endl;
    }
    else
    {
      cout<<"----------------------"<<endl;
      cout<<"Removed successfully"<<'\n';
      cout<<"----------------------"<<endl;
    }
  }

}

/// Initializing (the code that runs first of all)
int student :: initial()
{
	ifstream studentfile("stu.txt");
  if(studentfile.is_open())
  {
    string lines;
    while(!studentfile.eof())
    {
      getline(studentfile,lines);
        stringstream ss(lines);
        string tem;
        int fou;
        while(ss>>temp)
        {
          if(stringstream(temp) >> fou)
          {
            stud[k]=fou;

          }

        }
        k++;
    }
    k=k-1;
  }
  else
  {
    k=0;
  }

  studentfile.close();

  return k;
}

/// Initializing (the code that runs first of all)
int login :: initial()
{
	fstream passfile("abc.txt");
	fstream userfile("xyz.txt");
	
    if(userfile.is_open())
    {
      while(!userfile.eof())
      {
          getline(userfile,lineu);
          users[i]=lineu;
          i++;
      }
      i=i-1;
    }
    else
    {
      i=0;
    }
    userfile.close();

    if(passfile.is_open())
    {
      while(!passfile.eof())
      {
          getline(passfile,linep);
          passw[j]=linep;
          j++;
      }
      j=j-1;
    }
    else
    {
      j=0;
    }
    passfile.close();

  return i;
  return j;
}

/// Registering a user to control the whole system
string login :: regis()
{
    ifstream userfile("xyz.txt");
    cout<<"----------------------"<<endl;
    cout<<"Do u have an account? yes or no"<<endl;
    cin>>cho;
    if(cho=="yes")
    {
      cin.ignore();
      check();

    }
    else if(cho=="no")
    {
      cout<<"----------------------"<<endl;
      cout<<"Type your New Username: "<<endl;
      cin.ignore();
      getline(cin,user);
      k2=0;
      while(getline(userfile,lineu))
      {
        if(lineu==user)
        {
          k2++;
        }
      }
      userfile.close();
      fstream passfile("abc.txt",ios::app|ios::out);
      fstream userfi("xyz.txt",ios::app|ios::out);
      if(k2==1)
      {
        cout<<"----------------------"<<endl;
        cout<<"Same username existing in database\nPlease use another username to register"<<endl;
        cout<<"----------------------"<<endl;
        regis();
      }
      else
      {
        userfi<<user<<endl;
        users[i]=user;
        cout<<"----------------------"<<endl;
        cout<<"Type your New Password: "<<endl;
        getline(cin,pass);
        passfile<<pass<<endl;
        passw[j]=pass;
        cout<<"----------------------"<<endl;
        cout<<endl<<"Registered successfully"<<endl;
        cout<<"----------------------"<<endl;
        check();
      }
      passfile.close();
      userfi.close();

    }
    else
    {
      cout<<"----------------------"<<endl;
      cout<<"Invalid Entry"<<endl<<endl;
      cout<<"----------------------"<<endl;
      regis();
    }

    return cho;
}

/// Check for the credentials while logging in
int login :: check()
{
  cout<<"----------------------"<<endl;
  cout<<"enter the username: ";
  getline(cin,user);
  k1=0;
  do
  {
    if(user==users[k1])
    {
      cout<<"----------------------"<<endl;
      cout<<"enter the password: "<<endl;
      cout<<"if you have forgot the password, type forget"<<endl;
      getline(cin,pass);
      if(pass==passw[k1])
      {
        cout<<endl;
        cout<<"----------------------"<<endl;
        cout<<"You are now logged in"<<endl;
        cout<<"----------------------"<<endl;
        break;

      }
      else if(pass=="forget")
      {
        cout<<"----------------------"<<endl;
        cout<<"enter the same username again"<<endl;
        getline(cin,temp1);
        if(temp1==users[k1])
        {
          cout<<endl;
          cout<<"----------------------"<<endl;
          cout<<"You are now logged in"<<endl;
          cout<<"----------------------"<<endl;
          pass=passw[k1];
          break;
        }
        else
        {
          cout<<"----------------------"<<endl;
          cout<<"Incorrect entry sorry"<<endl;
          cout<<"----------------------"<<endl;
          _Exit(0);
        }
        pass=passw[k1];
      }
      else
      {
        cout<<"----------------------"<<endl;
        cout<<"Incorrect password"<<endl;
        cout<<"----------------------"<<endl;
        _Exit(0);
      }

    }
    k1++;

  }
  while(k1<MAX);
  if(k1==MAX)
  {
    cout<<"----------------------"<<endl;
    cout<<"User doesnt exist"<<endl;
    cout<<"----------------------"<<endl;
    exit();
  }
  cout<<"The serial number of username and password in the text file is: "<<k1+1<<endl<<endl;
  return k1;

}

/// Change the password if user wants after logging in
void login :: change_pass()
{
    string pass1;
    cout<<endl;

    cin.ignore();
    if(k1==i)
    {
      cout<<"----------------------"<<endl;
      cout<<"You cannot change your password at this moment"<<'\n';
      cout<<"Try to change when you login with same credentials the next time"<<endl;
      cout<<"----------------------"<<endl;
    }
    else
    {
      cout<<"----------------------"<<endl;
      cout<<"Type your old password here: "<<endl;
      getline(cin,temp);
      ofstream fileout("xyz1.txt");
      ifstream filein("abc.txt",ios::app);
      if(temp!=pass)
      {
        cout<<"----------------------"<<endl;
        cout<<"You have typed an incorrect password"<<endl;
        cout<<"----------------------"<<endl;
        filein.close();
        fileout.close();
      }
      else
      {
        cout<<"----------------------"<<endl;
        cout<<"Type the new password"<<endl;
        getline(cin,pass1);
        for(k2=0;k2<j;k2++)
        {
          if(passw[k2]==pass)
          {
              // the line is k2+1
              for(int y=0;y<k1;++y)
              {
                  getline(filein,linep);
                  fileout<<linep<<endl;
              }

              fileout<<pass1<<endl;
              if(cho=="yes")
              {
                for(int y=k1+1;y<j;y++)
                {
                    fileout<<passw[y]<<endl;
                }
              }
              else if(cho=="no")
              {
                for(int y=k1+1;y<j+1;y++)
                {
                    fileout<<passw[y]<<endl;
                }
              }

              passw[k2]=pass1;
          }
        }
        filein.close();
        fileout.close();

        remove("abc.txt");
        rename("xyz1.txt","abc.txt");
        pass=pass1;
      }
      cout<<"----------------------"<<endl;
      cout<<"Password updated successfully"<<endl;
      cout<<"----------------------"<<endl;
    }
    disp();
}

/// Display the credentials
void login :: disp()
{
  cout<<"----------------------"<<endl;
  cout<<"Username: "<<user<<endl;
  cout<<"Password: "<<pass<<endl;
  cout<<"----------------------"<<endl;
}

/// Exit the portal
void login :: exit()
{
    _Exit(0);
}

/// Main function starts
int main()
{
  cout<<i<<" "<<j<<" "<<k<<" "<<'\n';
  int choice,choice1;
  login l;
  student s;
  s.initial();
  cout<<"----------------------"<<endl;
  cout<<endl;
  cout<<"The student ID stored are: "<<endl;
  for(k2=0;k2<k;k2++)
  {
    cout<<stud[k2]<<endl;
  }
  l.initial();
  cout<<"----------------------"<<endl;
  cout<<endl;
  cout<<"The passwords stored are: "<<endl;
  for(k2=0;k2<j;k2++)
  {
    cout<<passw[k2]<<endl;
  }
  cout<<"----------------------"<<endl;
  cout<<endl;
  cout<<"The usernames stored are: "<<endl;
  for(k2=0;k2<i;k2++)
  {
    cout<<users[k2]<<endl;
  }
  cout<<"----------------------"<<endl;
  cout<<endl;
  cout<<i<<" "<<j<<" "<<k<<" "<<'\n';
  l.regis();
  for(;;)
  {
    cout<<"----------------------"<<endl;
    cout<<"1:Change password\n2:Display details\n3:Exit from 1st portal\n  and enter into 2nd portal"<<endl;
    cout<<"----------------------"<<endl;
    cin>>choice;
    switch (choice)
    {
      case 1:
      {
        l.change_pass();
        break;
      }
      case 2:
      {
        l.disp();
        break;
      }
      case 3:
      {
        cout<<"----------------------"<<endl;
        cout<<"1:Add a student to database\n2:Edit the details of a student\n3:View the details of a particular student\n4:View all enrolled students for library books\n5:Exit portal"<<endl;
        cout<<"----------------------"<<endl;
        cin>>choice1;
        switch(choice1)
        {
          case 1:
          {
            s.add_stu();
            cout<<endl;
            cout<<"----------------------"<<endl;
            cout<<"The data in the student file is:"<<endl;
            s.list_ofall();
            cout<<"----------------------"<<endl;
            cout<<endl;
            break;
          }
          case 2:
          {
            cout<<"----------------------"<<endl;
            cout<<"Processing...."<<'\n';
            cout<<"----------------------"<<endl;
            s.edit_stu();
            break;
          }
          case 3:
          {
            int q;
            cout<<"----------------------"<<endl;
            cout<<"Enter the ID of student to view the details"<<endl;
            cin>>q;
            s.view_det(q);
            break;
          }
          case 4:
          {
            s.list_ofall();
            break;
          }
          case 5:
          {
            _Exit(0);
            break;
          }
          default:
          {
            cout<<"----------------------"<<endl;
            cout<<"Incorrect entry"<<endl;
            cout<<"----------------------"<<endl;
            break;
          }
        }

        break;
      }
      default:
      {
        cout<<"----------------------"<<endl;
        cout<<"Incorrect entry"<<endl;
        cout<<"----------------------"<<endl;
        break;
      }
    }
  }
  return 0;
}
