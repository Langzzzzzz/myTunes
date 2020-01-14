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
#include <sstream>
using namespace std;

#include "user.h"
#include "sqlite3_helper.h"

int User::nextUserNumericID = 1000;

User::User(const string & aUserID, const string & aName) {
	//cout << "User(string&, string&, int)" << endl;
	userid = aUserID;
	name = aName;
	id = nextUserNumericID++;
}
//User::User(const User & aUser) {
//	cout << "User(const User & aUser)" << endl;
//	cout << "ERROR: User(const User & aUser) --should never run" << endl;
//}
User::~User() {
	//cout << "~User(void)" << endl;
	//user objects own playlists
	//for(int i=0; i<playlists.size(); i++)
	//	delete playlists[i]; //delete playlists this user owns

}
int User::getID() { return id; }

string User::getUserID() { return userid; }
string User::getName()const { return name; }
//vector<Playlist*>::iterator User::findPosition(Playlist & aPlaylist){
//	for (vector<Playlist*>::iterator itr = playlists.begin() ; itr != playlists.end(); ++itr)
//		if(*itr == &aPlaylist) return itr;
//	return playlists.end();
//}

bool User::findPlaylist(const string & aPlaylistName, Playlist &playlist) {
	
	Sqlite3Helper& db = Sqlite3Helper::get_instance();
	return SQLITE_OK == db.findPlaylistByName(aPlaylistName, playlist);
}
void User::addPlaylist(Playlist & aPlaylist) {

	ostringstream   sql;
	sql << "INSERT INTO playlists (user_id,playlist_name) VALUES('"
		<< userid << "','"
		<< aPlaylist.getName()
		<< "')";
	Sqlite3Helper& db = Sqlite3Helper::get_instance();
	db.executeNonQuery(sql.str().c_str());
}

void User::removePlaylist(Playlist & aPlaylist) {

	ostringstream sql;
	
	Sqlite3Helper& db = Sqlite3Helper::get_instance();
	sql << "DELETE FROM playlists WHERE playlist_name='"
		<< aPlaylist.getName()
		<< "' AND user_id='"
		<< userid
		<< "'";
	db.executeNonQuery(sql.str().c_str());

	sql.str("");
	sql << "DELETE FROM playlist_tracks WHERE playlist_name='"
		<< aPlaylist.getName()
		<< "' AND user_id='"
		<< userid
		<< "'";
	db.executeNonQuery(sql.str().c_str());
}

void User::removeTrack(Track & aTrack) {
	ostringstream sql;
	Sqlite3Helper& db = Sqlite3Helper::get_instance();
	//sql << "SELECT COUNT(*) playlist_tracks WHERE playlist_name IN(SELECT playlist_name FROM playlists WHERE user_id='"
	//	<< userid << "') AND track_id="
	//	<< aTrack.getID();
	//int count = 0;
	//db.ExecuteScalar(sql.str().c_str(), count);
	//if (count <= 0) {
	//	return;
	//}
	//sql.clear();
	sql << "DELETE FROM playlist_tracks WHERE playlist_name IN(SELECT playlist_name FROM playlists WHERE user_id='"
		<< userid << "') AND track_id="
		<< aTrack.getID();

	db.executeNonQuery(sql.str().c_str());
}
void User::remove() 
{
	ostringstream sql;
	Sqlite3Helper& db = Sqlite3Helper::get_instance();

	sql << "DELETE FROM playlist_tracks WHERE user_id='"
		<< userid << "'";

	db.executeNonQuery(sql.str().c_str());
	sql.str("");
	sql << "DELETE FROM playlists WHERE user_id='"
		<< userid << "'";

	db.executeNonQuery(sql.str().c_str());
}
string User::toString()const {
	string indent = "     ";
	string s;
	s.append(userid + " " + name);
	s.append("\n");
	s.append(indent + "Playlists:\n");

	vector<Playlist> playlists;
	ostringstream   sql;
	sql << "SELECT * FROM playlists WHERE user_id='"
		<< userid
		<< "'";
	Sqlite3Helper& db = Sqlite3Helper::get_instance();
	db.queryPlaylists(sql.str().c_str(), playlists);

	for (vector<Playlist*>::size_type i = 0; i < playlists.size(); i++) {
		s.append(indent + to_string(i) + " " + (playlists[i]).toString() + "\n");
		s.append("\n");
	}

	return s;
}

ostream & operator<<(ostream & out, const User & aUser) {
	out << aUser.toString() << endl;
	return out;
}
