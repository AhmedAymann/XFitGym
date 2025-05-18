#pragma once
#include<iostream>
#include<QString.h>
using namespace std;

class User {
public:

	User();
	User(QString id,QString email,QString name, QString DateOFBirth);

	QString getId() const;
	QString getEmail() const;
	QString getName() const;
	QString getDateOfBirth() const;

	void setId(const QString& id) ;
	void setEmail(const QString& email) ;
	void setName(const QString& name) ;
	void setDateOfBirth(const QString& dob) ;

private:
	QString id;
	QString email;
	QString name;
	QString DateOFBirth;
};