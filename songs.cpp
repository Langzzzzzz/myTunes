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

#include "songs.h"

#include "sqlite3_helper.h"

Songs::Songs(){
}
Songs::~Songs(void){

}

bool Songs::findByID(int anID, Song &song){
	Sqlite3Helper& db = Sqlite3Helper::get_instance();
	return SQLITE_OK == db.findSongByID(anID, song);
	
}
void Songs::add(Song & aSong){
	ostringstream   sql;
	sql << "INSERT INTO songs (sid,title,composer) VALUES(" 
		<< aSong.getID()<<",'"
		<<aSong.getTitle()<<"','"
		<<aSong.getComposer()
		<<"')";
	Sqlite3Helper& db = Sqlite3Helper::get_instance();
	db.executeNonQuery(sql.str().c_str());
}
void Songs::remove(Song & aSong){
	ostringstream   sql;
	sql << "DELETE FROM songs WHERE sid=" << aSong.getID();
	Sqlite3Helper& db = Sqlite3Helper::get_instance();
	db.executeNonQuery(sql.str().c_str());
}

void Songs::showOn(UI & view) {
	view.printOutput("Songs:");
	vector<Song> songs;
	const char * sql = "SELECT * FROM songs";
	Sqlite3Helper& db = Sqlite3Helper::get_instance();
	db.querySongs(sql, songs);
	for (int i = 0; i < songs.size(); i++) {
		view.printOutput((songs[i]).toString());

	}
}

void Songs::showOn(UI & view, int memberID)  {
  view.printOutput("Song:");
  Song song;
  if (findByID(memberID, song)) {
	  view.printOutput(song.toString());
  }
}
