#pragma once
#ifndef __ISOLATED_H__
#define __ISOLATED_H__

#include "Table.h"

class isolated : public Tables
{
private:
	static int isolatedID;
	std::vector<ISOLATED> mIsolatedInfor;
	std::string dirToDB;
public:
	
	ISOLATED isolatedInformation;
    isolated() {}
	isolated(const std::string& dirDB);
	~isolated();
	// Table
	void createTable();
	void droptable();

    // DB
    void connectToDB();

    // Get-set
    // Get-set
    void setDir(const std::string& dirToDB);
    std::string getDir();


	// Values
	void insertValues();
	void insertValuesAuto();
	void deleteValues();
	void updateValues();
	void filterValues();
	void displayTable();

	// Static
	static void increasingIsolated();
	static int getIsolatedID();

public:
	void takeIsolatedForm(const ISOLATED& _isoPlace);
};


#endif // !__ISOLATED_H__



