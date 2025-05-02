#pragma once
#include<iostream>
#include<string>
using namespace std;
class User {
private:
	int id;
	string email;
	string name;
	string password;
	string phone;
public:
	User(int id,string email,string name, string password,string phone);

};