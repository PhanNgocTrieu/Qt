#pragma once
#ifndef __MANINFORTABLE_H__
#define __MANINFORTABLE_H__

#include "Table.h"
#include <iostream>
#include <vector>
#include <iomanip>
#include <QString>

class manInforTable : public Tables
{
	static int manID;
	std::vector<ManInfor> mManInfor;
    std::string dirToDB;
	
public:
	
	ManInfor manInformation;
    manInforTable() {}
	manInforTable(const std::string& dirDB);
	~manInforTable();

    // Get-set
    void setDir(const std::string& dirToDB);
    std::string getDir();

    // DB
    void connectToDB();

	// Table
	void createTable();
	void droptable();

	// Values
	void insertValues();
	void insertValuesAuto();
	void deleteValues();
	void updateValues();
	void filterValues();
	void displayTable();


	// static
	static void increasingID();
	static int getManID();

public:
    void takeManInFor(const ManInfor& _inforOfMan);
};

std::string plusPassing(std::vector<std::string> passing);




#endif // !__MANINFORTABLE_H__

