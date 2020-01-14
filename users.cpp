/* * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                   */
/*  Program:  MyTunes Music Player                   */
/*  Author:   (c) 2019 Louis Nel                     */
/*  All rights reserved.  Distribution and           */
/*  reposting, in part or in whole, requires         */
/*  written consent of the author.                   */
/*                                                   */
/*  COMP 2404 students may reuse this content for    */
/*  their course assignments without seeking consent */
/* * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <iostream>
#include <string>
#include <vector>
using namespace std;

#include "user.h"
#include "users.h"
#include "sqlite3_helper.h"
Users::Users(){
}
Users::~Users(void){
	//for(int i=0; i<collection.size(); i++)
	//   delete collection[i]; //delete Users in this container
}
 void Users::getCollection(vector<User>& collection){
	const char * sql = "SELECT * FROM users";
	Sqlite3Helper& db = Sqlite3Helper::get_instance();
	db.queryUsers(sql, collection);
}

//User * Users::findByID(int anID) {
//	for (vector<User*>::iterator itr = collection.begin() ; itr != collection.end(); ++itr)
//		if((*itr)->getID() == anID) return *itr;
//	return NULL;
//}
bool Users::findByUserID(const string & aUserID, User& user) {
	
	ostringstream   sql;
	sql << "SELECT * FROM users WHERE user_id='" << aUserID<<"'";
	Sqlite3Helper& db = Sqlite3Helper::get_instance();
	return SQLITE_OK == db.findUserByID(aUserID, user);
}
//vector<User*>::iterator Users::findPosition(User & aUser)  {
//	for (vector<User*>::iterator it = collection.begin() ; it != collection.end(); ++it)
//		if(*it == &aUser) return it;
//	return collection.end();
//}

void Users::add(User & aUser){
	ostringstream   sql;
	sql << "INSERT INTO users (user_id,name) VALUES('"
		<< aUser.getUserID()<<"','"
		<< aUser.getName()
		<< "')";
	Sqlite3Helper& db = Sqlite3Helper::get_instance();
	db.executeNonQuery(sql.str().c_str());
}
void Users::remove(User & aUser){
	aUser.remove();
	ostringstream   sql;
	Sqlite3Helper& db = Sqlite3Helper::get_instance();
	sql << "DELETE FROM users WHERE user_id='"
		<< aUser.getUserID()
		<<"'";
	db.executeNonQuery(sql.str().c_str());
}
void Users::showOn(UI & view) {
  view.printOutput("Users:");
  vector<User> users;
  const char * sql = "SELECT * FROM users";
  Sqlite3Helper& db = Sqlite3Helper::get_instance();
  db.queryUsers(sql, users);
  for (int i = 0; i < users.size(); i++) {
	  view.printOutput((users[i]).toString());
  }
}
void Users::showOn(UI & view, const string & memberID) {
  view.printOutput("User:");
  User  user;
  if (findByUserID(memberID, user)) {
	  view.printOutput(user.toString());
  }
}
