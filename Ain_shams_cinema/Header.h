#pragma once
#include <iostream>
#include<fstream>
#include <iomanip>
#include <conio.h>
#include <stdio.h>
#include <ctype.h>
#include <comutil.h>
#include <dos.h>
#include <cstring>
#include <sstream>
#include <regex>
#include <tchar.h>
#include <Windows.h>
/////

#include<cstdio>
#include<cmath>
#include <string>
#include <msclr\marshal_cppstd.h>
#include <ctime>
#include<cmath>
#define ticket_price 100
#include"MyForm.h"

#include "EASendMailObj.tlh"

using namespace EASendMailObjLib;


const int ConnectNormal = 0;
const int ConnectSSLAuto = 1;
const int ConnectSTARTTLS = 2;
const int ConnectDirectSSL = 3;
const int ConnectTryTLS = 4;


using namespace std;

int hour = 13;
int mn = 00;
int count_tickets = 0;
string email, pass, First_name;
int discounted_price;


struct description {
	string movie_name;
	string director;
	string actor1;
	string actor2;
	string actor3;
	string describe;
	string movie_type;
	string rating;
};
struct screen_info {
	string theater_ID;
	string capacity;
	string reserved_seats;
	string booked;
	string booked_chairs[24] = {};
	
};
struct tim {
	string ti;
};
struct movie {
	description ds;
	screen_info sc;
	tim t;
};
struct User {
	string Fname,Lname, Password, Email, Phone, Age,noDiscount="0";

}us[100];
movie mov[12];
//###################### NEW FUNCTION ########################
string convertintintostr(int s) {//function to convert integer into string to help in editing file
	ostringstream result; //abdo
	result << s;
	return result.str();
}
//###################### NEW FUNCTION ########################
int covertstrtoint(string s) { //function to convert string into integer to help in editing file
	int result = 0; //abdo
	for (int i = 0; i < s.length(); i++) {
		result = (result * 10) + (s[i] - '0');
	}
	return result;
}
//###################### NEW FUNCTION #########################
void ReadFile() { //ammar
	ifstream myfile;
	myfile.open("file.txt");
	for (int NoMovie = 0; NoMovie < 12; NoMovie++) {
		int cntLine = 0;
		if (myfile.is_open()) { //to check file is open
			
			string line;
			while (getline(myfile, line)) //to save info from file in struct of movie
			{
				//cntLine = cntLine % 13;
				if (line != "!!!")                     //to check if he end film info 
				{
					if (cntLine == 0)
						mov[NoMovie].ds.movie_name = line;
					else if (cntLine == 1)
						mov[NoMovie].ds.director = line;
					else if (cntLine == 2)
						mov[NoMovie].ds.actor1 = line;
					else if (cntLine == 3)
						mov[NoMovie].ds.actor2 = line;
					else if (cntLine == 4)
						mov[NoMovie].ds.actor3 = line;
					else if (cntLine == 5)
						mov[NoMovie].ds.movie_type = line;
					else if (cntLine == 6)
						mov[NoMovie].ds.describe = line;
					else if (cntLine == 7)
						mov[NoMovie].ds.rating = line;
					else if (cntLine == 8)
						mov[NoMovie].sc.theater_ID = line;
					else if (cntLine == 9)
						mov[NoMovie].t.ti = line;
					else if (cntLine == 10)
						mov[NoMovie].sc.capacity = line;
					else if (cntLine == 11)
						mov[NoMovie].sc.reserved_seats = line;
					else if (cntLine == 12)
						mov[NoMovie].sc.booked = line;
				}
				else {
					break;
				}
				cntLine++;                          // to go to next line in file  
			}
		}
	}
	myfile.close();
}
//###################### NEW FUNCTION #########################
void add_chair(string moviename, string time, string chair) {//samy
	for (int i = 0; i < 12; i++) {
		if (mov[i].ds.movie_name == moviename && mov[i].t.ti == time) {
			for (int j = 0; j < 24; j++) {
				if (mov[i].sc.booked_chairs[j] == "") {
					mov[i].sc.booked_chairs[j] = chair;
					break;
				}
			}
		}
	}
}
//###################### NEW FUNCTION ##########################
void save_in_array() {//abdo
	for (int i = 0; i < 12; i++) {
		int intial = 0;
		for (int j = 0; j < mov[i].sc.booked.length(); j += 2) {
			mov[i].sc.booked_chairs[intial] = mov[i].sc.booked.substr(j, 2);
			intial++;
		}
	}
}
//###################### NEW FUNCTION ##########################
void capacity_minus(string moviename, string movietime) {//ziad
	for (int i = 0; i < 12; i++) {
		if (mov[i].ds.movie_name == moviename && mov[i].t.ti == movietime) {
			int x;
			x = stoi(mov[i].sc.capacity);
			x = x - 1;

			mov[i].sc.capacity = to_string(x);

		}
	}
}
//###################### NEW FUNCTION ##########################
void reserved_seats_plus(string name, string time) {//youssef
	int number;

	for (int i = 0; i < 12; i++) {
		if (name == mov[i].ds.movie_name && time == mov[i].t.ti) {
			number = stoi(mov[i].sc.reserved_seats) + 1;
			mov[i].sc.reserved_seats = to_string(number);
			break;
		}
	}
}
//###################### NEW FUNCTION ###########################
void Writefile() { //function to read the array of structure and save it into file "edit file"
	ofstream myfile; //abdo
	myfile.open("file.txt");
	for (int NoMovie = 0; NoMovie < 12; NoMovie++) {
		if (mov[NoMovie].ds.movie_name == " ") {
			break;
		}
		else {
			myfile << mov[NoMovie].ds.movie_name << endl;
			myfile << mov[NoMovie].ds.director << endl;
			myfile << mov[NoMovie].ds.actor1 << endl;
			myfile << mov[NoMovie].ds.actor2 << endl;
			myfile << mov[NoMovie].ds.actor3 << endl;
			myfile << mov[NoMovie].ds.movie_type << endl;
			myfile << mov[NoMovie].ds.describe << endl;
			myfile << mov[NoMovie].ds.rating << endl;
			myfile << mov[NoMovie].sc.theater_ID << endl;
			myfile << mov[NoMovie].t.ti << endl;
			myfile << mov[NoMovie].sc.capacity << endl;
			myfile << mov[NoMovie].sc.reserved_seats << endl;
			for (int i = 0; i<24; i++) {
				myfile << mov[NoMovie].sc.booked_chairs[i];
			}
			myfile << endl;
			myfile << "!!!" << endl;

		}
	}
	myfile.close();
}
//###################### NEW FUNCTION ###########################
bool check_ticket(string moviename, string time, string no_tickets) { //ziad
	int x = stoi(no_tickets);
	for (int i = 0; i < 12; i++) {
		if (mov[i].ds.movie_name == moviename && mov[i].t.ti == time) {
			int z = stoi(mov[i].sc.capacity);
			if (z >= x) {
				return true;
				
			}
			else {
				return false;
			}

		}
	}
}
//###################### NEW FUNCTION ###########################
bool check_in_array(string moviename, string time, string chair_name) {//moamen
	bool check = false;
	for (int i = 0; i < 12; i++) {
		if (mov[i].ds.movie_name == moviename && mov[i].t.ti == time) {
			for (int j = 0; j < 24; j++) {
				if (mov[i].sc.booked_chairs[j] == chair_name) {
					check = true;
				}

			}
		}
	}
	return check;
}
//###################### NEW FUNCTION ###########################
bool check_time(int h, int m, string s_time) //krkr
{
	int total_min = m + (h * 60);                                 //integer hours to minutes
	int str_hour_to_min = 0, xhour1 = 0, xhour2 = 0, xhour = 0, xmin1 = 0, xmin2 = 0;
	xmin1 = s_time[3] - 48;                                       //converting string to int
	xmin2 = s_time[4] - 48;
	xmin1 = (xmin1 * 10);                                         //converting index 3 in string from a number to 10 or 20 or 30...etc minutes
	xhour1 = s_time[0] - 48;                                      //converting string hours to int
	xhour2 = s_time[1] - 48;
	xhour1 = (xhour1 * 10);                                       //converting index 0 in string from a number to 10 or 20 or 30...etc hours
	xhour = xhour1 + xhour2;                                      //total hours
	str_hour_to_min = xhour * 60;                                 //string hours to minutes
	int total_min_str = xmin1 + xmin2 + str_hour_to_min;          //total minutes in the string
	if (total_min + 15 <= total_min_str)                          //for large difference
		return true;
	else if (abs(total_min - total_min_str) <= 15)                //condition for time difference
		return true;
	else
		return false;
}
//###################### NEW FUNCTION ###########################
void Read_UserFile() { //ziad
	ifstream read;
	read.open("Users.txt");
	if (read) {
		string line;
		getline(read, line);

		int z = covertstrtoint(line);
		getline(read, line);
		for (int i = 0; i < z; i++) {
			int cont_line = 2;
			while (getline(read, line)) {

				if (line != "!!!") {
					if (cont_line == 2) {
						us[i].Fname = line;
					}
					else if (cont_line == 3) {
						us[i].Lname = line;
					}
					else if (cont_line == 4) {
						us[i].Email = line;
					}
					else if (cont_line == 5) {
						us[i].Password = line;
					}
					else if (cont_line == 6) {
						us[i].Phone = line;
					}
					else if (cont_line == 7) {
						us[i].Age = line;
					}
					else if (cont_line == 8) {
						us[i].noDiscount = line;
					}
				}
				else {
					break;
				}
				cont_line++;
			}

		}

	}

	read.close();
}
//###################### NEW FUNCTION ###########################
void ForgetPassword(string email, string phone_number, string new_password) { //ziad
	ifstream read;
	read.open("Users.txt");
	string line;
	getline(read, line);
	int no_users = covertstrtoint(line);
	read.close();
	for (int i = 0; i < no_users; i++) {
		if (us[i].Email == email && us[i].Phone == phone_number) {
			us[i].Password = new_password;
		}
	}
}
//###################### NEW FUNCTION ###########################
int new_no_users1() { //abdo
	ifstream myfile2;
	string line;
	myfile2.open("Users.txt");
	getline(myfile2, line);
	int y = covertstrtoint(line);
	myfile2.close();
	return y + 1;
}
//###################### NEW FUNCTION ###########################
void write_user_file() { //krkr
	int num_rotate = new_no_users1();
	string no_users = convertintintostr(num_rotate);
	ofstream write;
	write.open("Users.txt");
	write << no_users << endl;
	write << "!!!" << endl;
	for (int i = 0; i < num_rotate; i++) {
		write << us[i].Fname << endl;
		write << us[i].Lname << endl;
		write << us[i].Email << endl;
		write << us[i].Password << endl;
		write << us[i].Phone << endl;
		write << us[i].Age << endl;
		write << us[i].noDiscount << endl;
		write << "!!!" << endl;
	}
	write.close();
}
//###################### NEW FUNCTION ###########################
void AddUser(string First,string last, string Email, string password, string phone, string age) { //abdo
	ifstream myfile2;
	string line;
	myfile2.open("Users.txt");
	getline(myfile2, line);
	int y = covertstrtoint(line);
	us[y].Fname = First;
	us[y].Lname = last;
	us[y].Password = password;
	us[y].Email = Email;
	us[y].Phone = phone;
	us[y].Age = age;
	myfile2.close();
	write_user_file();
}
//###################### NEW FUNCTION ###########################
bool CheckPhoneNo(string phone) { //abdo
	bool x = true;
	if (phone.length() != 11) {
		x = false;
	}
	else if (!(phone[0] == '0')) {
		x = false;
	}
	else if (!(phone[1] == '1')) {
		x = false;
	}
	else if (!((phone[2] == '0') || (phone[2] == '1') || (phone[2] == '2') || (phone[2] == '5'))) {
		x = false;
	}
	if (x) {
		for (int i = 3; i < phone.length(); i++) {
			if (!((phone[i] == '0') || (phone[i] == '1') || (phone[i] == '2') || (phone[i] == '3') || (phone[i] == '4') || (phone[i] == '5') || (phone[i] == '6') || (phone[i] == '7') || (phone[i] == '8') || (phone[i] == '9'))) {
				x = false;
			}
		}
	}
	return x;
}
//###################### NEW FUNCTION ###########################
bool check_login_mail(string mail) { //krkr
	bool check = false;
	ifstream read_no_users;
	read_no_users.open("Users.txt");
	string number_of_users;
	getline(read_no_users, number_of_users);
	int number_user_rotate = covertstrtoint(number_of_users);
	read_no_users.close();
	for (int i = 0; i < number_user_rotate; i++) {
		if (mail == us[i].Email) {
			check = true;
			break;
		}
	}
	return check;
}
//###################### NEW FUNCTION ###########################
bool check_mail(string mail) //ammar
{
	string username, domain;
	int lastAt = -1, lastDot = -1;
	for (int se = mail.size() - 1; se >= 0; se--)
	{
		if (mail[se] == '.' && lastDot == -1)
			lastDot = se;
		if (mail[se] == '@' && lastAt == -1)
			lastAt = se;
	}
	bool valid = true;;
	if (lastDot > lastAt && lastAt != -1 && lastDot != -1 && lastAt != 0 && (mail.size() - (lastDot + 1)) > 1)
	{
		domain = mail.substr(lastAt, mail.size());
		for (int idx = 0; idx < domain.size(); idx++)
		{
			if (domain[idx] >= 32 && domain[idx] != '.' && domain[idx] != '-' && domain[idx] <= 47 || domain[idx] >= 58 && domain[idx] <= 63 || domain[idx] >= 91 && domain[idx] <= 94 || domain[idx] == 96 || domain[idx] >= 123 && domain[idx] <= 127)
				return false;
			if (idx + 1 != domain.size()) {
				if (domain[idx] == '.' || domain[idx] == '-' || domain[idx] == '_') {
					if (idx == 0 && domain[idx] == '.' || domain[idx + 1] >= 32 && domain[idx + 1] <= 47 || domain[idx + 1] >= 58 && domain[idx + 1] <= 64 || domain[idx + 1] >= 91 && domain[idx + 1] <= 96 || domain[idx + 1] >= 123 && domain[idx + 1] <= 127) {
						return false;
					}
					if (idx == 0 && domain[idx] == '_' || domain[idx + 1] >= 32 && domain[idx + 1] <= 47 || domain[idx + 1] >= 58 && domain[idx + 1] <= 64 || domain[idx + 1] >= 91 && domain[idx + 1] <= 96 || domain[idx + 1] >= 123 && domain[idx + 1] <= 127) {
						return false;
					}
					if (idx == 0 && domain[idx] == '-' || domain[idx + 1] >= 32 && domain[idx + 1] <= 47 || domain[idx + 1] >= 58 && domain[idx + 1] <= 64 || domain[idx + 1] >= 91 && domain[idx + 1] <= 96 || domain[idx + 1] >= 123 && domain[idx + 1] <= 127) {
						return false;
					}
				}
			}
			else if (idx + 1 == domain.size() && domain[idx] == '.' || domain[idx] == '-' || domain[idx] == '_')
			{
				return false;
			}
		}
		username = mail.substr(0, lastAt);
		for (int idx = 0; idx < username.size(); idx++)
		{
			if (username[idx] >= 33 && username[idx] != '.' && username[idx] != '-' && username[idx] <= 47 || username[idx] >= 58 && username[idx] <= 64 || username[idx] >= 91 && username[idx] <= 94 || username[idx] == 96 || username[idx] >= 123 && username[idx] <= 127)
			{
				return false;
			}
			else {
				if (idx + 1 != username.size()) {
					if (username[idx] == '.' || username[idx] == '-' || username[idx] == '_') {
						if (idx == 0 && username[idx] == '.' || username[idx + 1] >= 32 && username[idx + 1] <= 47 || username[idx + 1] >= 58 && username[idx + 1] <= 64 || username[idx + 1] >= 91 && username[idx + 1] <= 96 || username[idx + 1] >= 123 && username[idx + 1] <= 127) {
							return false;
						}
						if (idx == 0 && username[idx] == '_' || username[idx + 1] >= 32 && username[idx + 1] <= 47 || username[idx + 1] >= 58 && username[idx + 1] <= 64 || username[idx + 1] >= 91 && username[idx + 1] <= 96 || username[idx + 1] >= 123 && username[idx + 1] <= 127) {
							return false;
						}
						if (idx == 0 && username[idx] == '-' || username[idx + 1] >= 32 && username[idx + 1] <= 47 || username[idx + 1] >= 58 && username[idx + 1] <= 64 || username[idx + 1] >= 91 && username[idx + 1] <= 96 || username[idx + 1] >= 123 && username[idx + 1] <= 127) {
							return false;
						}
					}
				}
				else if (idx + 1 == username.size() && username[idx] == '.' || username[idx] == '-' || username[idx] == '_')
				{
					return false;
				}
				valid = true;
			}
		}
		return true;
	}
	else
		return false;
}
//###################### NEW FUNCTION ###########################
bool checkPass(string email, string pass) { //ammar
	ifstream myfile;
	myfile.open("Users.txt");
	string line;
	getline(myfile, line);
	int tot = covertstrtoint(line);
	for (int user = 0; user < tot; user++)
	{
		if (us[user].Email == email && us[user].Password == pass)
			return true;
	}
	myfile.close();
	return false;
}
//###################### NEW FUNCTION ###########################
bool check_phone_exist(string phone_in_file) { //moamen
	bool check = true;
	string s;
	ifstream file;
	file.open("Users.txt");
	getline(file, s);

	for (int i = 0; i < covertstrtoint(s); i++) {
		if (us[i].Phone == phone_in_file) {
			check = false;
		}
	}
	file.close();
	return check;
}
//###################### NEW FUNCTION ###########################
bool check_age(string s) { //youssef

	bool check = true;

	if (s.length() == 2) {

		for (int i = 0; i < s.length(); i++) {

			if (isdigit(s[i]) == 0) {
				check = false;
				break;
			}


		}
		if (check) {
			int age = covertstrtoint(s);
			if (age < 100 && age>10)
				check = true;
			else
				check = false;
		}
	}
	else check = false;


	return check;

}
//###################### NEW FUNCTION ###########################
bool valid_password(string pass) { //samy
	if (pass.length() != 8) {
		return false;
	}
	else {
		return true;
	}
}
//###################### NEW FUNCTION ###########################
void Edit_password() { //samy
	string x = convertintintostr(new_no_users1());
	int no_user= covertstrtoint(x)-1;
	 x = convertintintostr(no_user);
	int num_rotate = covertstrtoint(x);
	ofstream write;
	write.open("Users.txt");
	write << x << endl;
	write << "!!!" << endl;
	for (int i = 0; i < num_rotate; i++) {
		write << us[i].Fname << endl;
		write << us[i].Lname << endl;
		write << us[i].Email << endl;
		write << us[i].Password << endl;
		write << us[i].Phone << endl;
		write << us[i].Age << endl;
		write << us[i].noDiscount << endl;
		write << "!!!" << endl;
	}
	write.close();
}
//###################### NEW FUNCTION ###########################
bool validName(string name) {
	for (int idx = 0; idx < name.size(); idx++) {
		if ((name[idx] < 'a' && name[idx] > 'Z') || name[idx] > 'z' || name[idx] < 'A')
			return false;
	}
	return true;
}
//###################### NEW FUNCTION ###########################
bool CheckFName(string first) {
	if (first.size() >= 3 && first.size() <= 12) {
		return true;
	}
	else {
		return false;
	}
}
//###################### NEW FUNCTION ###########################
bool CheckLName(string last) {
	if (last.size() >= 3 && last.size() <= 12) {
		return true;
	}
	else {
		return false;
	}
}
//###################### NEW FUNCTION ###########################
void discount_plus(string email, string pass) {
	ifstream read_no_users;
	read_no_users.open("Users.txt");
	string number_of_users;
	getline(read_no_users, number_of_users);
	int number_user_rotate = covertstrtoint(number_of_users);
	read_no_users.close();
	int x;
	for (int i = 0; i < number_user_rotate; i++) {
		if (us[i].Email == email && us[i].Password==pass) {
			x = covertstrtoint(us[i].noDiscount);
			x++;
			us[i].noDiscount = convertintintostr(x);
			break;
		}
	}
}
//###################### NEW FUNCTION ###########################
bool discount(string email, string pass) {
	ifstream read_no_users;
	read_no_users.open("Users.txt");
	string number_of_users;
	getline(read_no_users, number_of_users);
	int number_user_rotate = covertstrtoint(number_of_users);
	read_no_users.close();
	int x;
	for (int i = 0; i < number_user_rotate; i++) {
		if (us[i].Email == email && us[i].Password == pass) {
			x = covertstrtoint(us[i].noDiscount);
			if (x > 2) {
				return true;
			}
			else {
				return false;
			}
		}
	}
}
//###################### NEW FUNCTION ###########################
bool valid_dis(string email, string pass) {
	ifstream read_no_users;
	read_no_users.open("Users.txt");
	string number_of_users;
	getline(read_no_users, number_of_users);
	int number_user_rotate = covertstrtoint(number_of_users);
	read_no_users.close();
	int x;
	for (int i = 0; i < number_user_rotate; i++) {
		if (us[i].Email == email && us[i].Password == pass) {
			x = covertstrtoint(us[i].noDiscount);
			if (x == 2) {
				return true;
			}
			else {
				return false;
			}
		}
	}
}
//###################### NEW FUNCTION ###########################
string get_first(string email, string pass) {
	ifstream read_no_users;
	read_no_users.open("Users.txt");
	string number_of_users;
	getline(read_no_users, number_of_users);
	int number_user_rotate = covertstrtoint(number_of_users);
	read_no_users.close();
	for (int i = 0; i < number_user_rotate; i++) {
		if (us[i].Email == email && us[i].Password == pass) {
			return us[i].Fname;
		}
	}

}
//###################### NEW FUNCTION ###########################

/*std::wstring Str2Wstr(const std::string& str)
{
	int size_needed = MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), NULL, 0);
	std::wstring wstrTo(size_needed, 0);
	MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), &wstrTo[0], size_needed);
	return wstrTo;
}*/
void send_mail(string mail,int op=1) {

	::CoInitialize(NULL);
	
	char arr[200];
	strcpy(arr, mail.c_str());
	const char* msg = arr; //use const char*, instead of char*
	wchar_t* wmsg = new wchar_t[strlen(msg) + 1]; //memory allocation
	mbstowcs(wmsg, msg, strlen(msg) + 1);
	delete[]wmsg;

	IMailPtr oSmtp = NULL;
	oSmtp.CreateInstance(__uuidof(EASendMailObjLib::Mail));
	oSmtp->LicenseCode = _T("TryIt");

	// Set your gmail email address
	oSmtp->FromAddr = _T("ainshamscinema@gmail.com");
	// Add recipient email address

	oSmtp->AddRecipientEx(wmsg, 0);

	if (op == 0) { //regestration

		// Set email subject
		oSmtp->Subject = _T("AinShams Cinema Registration Compeleted");
		// Set email body
		oSmtp->BodyText = _T("Dear Mr/Mrs,\n\nYou have successfully registered \n\nBest regards,\nAinShams Cinema");
	}
	else {
		// Set email subject
		oSmtp->Subject = _T("AinShams Cinema Booking Offer");
		// Set email body
		oSmtp->BodyText = _T("Dear Mr/Mrs,\n\nEnjoy your next time you book with a 20% OFF !!! \n\nBest regards,\nAinShamsCinema");
	}

	oSmtp->ServerAddr = _T("smtp.gmail.com");


	oSmtp->UserName = _T("ainshamscinema@gmail.com");


	oSmtp->Password = _T("sicpzferjuelkkdi");


	oSmtp->ServerPort = 465;


	oSmtp->ConnectType = ConnectSSLAuto;

	//_tprintf(_T("Start to send email via gmail account ...\r\n"));

	if (oSmtp->SendMail() == 0)
	{
		//_tprintf(_T("email was sent successfully!\r\n"));
	}
	else
	{
		//_tprintf(_T("failed to send email with the following error: %s\r\n"),
			//(const TCHAR*)oSmtp->GetLastErrDescription());
	}
}
//###################### NEW FUNCTION ###########################
void Write_current_user() {
	ifstream file;
	file.open("Users.txt");
	string line;
	getline(file, line);
	string no_user = line;
	int cnt = covertstrtoint(line);
	file.close();
	ofstream user;
	user.open("Users.txt");
	user << no_user << endl;
	user << "!!!" << endl;
	for (int i = 0; i < cnt; i++) {
		user << us[i].Fname << endl;
		user << us[i].Lname << endl;
		user << us[i].Email << endl;
		user << us[i].Password << endl;
		user << us[i].Phone << endl;
		user << us[i].Age << endl;
		user << us[i].noDiscount << endl;
		user << "!!!" << endl;
	}
	user.close();

}
