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

#include "track.h"
#include "tracks.h"
#include "sqlite3_helper.h"
Tracks::Tracks(){
}
Tracks::~Tracks(void){
	//for(int i=0; i<collection.size(); i++)
	//	delete collection[i]; //delete Tracks in this container
}
void Tracks::getCollection(vector<Track> collection){
	const char * sql = "SELECT * FROM tracks";
	Sqlite3Helper& db = Sqlite3Helper::get_instance();
	db.queryTracks(sql, collection);
}

//vector<Track*>::iterator Tracks::findPosition(Track & aTrack){
//	for (vector<Track*>::iterator it = collection.begin() ; it != collection.end(); ++it)
//		if(*it == &aTrack) return it;
//	return collection.end();
//}
bool Tracks::findByID(int anID, Track& track){

	Sqlite3Helper& db = Sqlite3Helper::get_instance();
	return SQLITE_OK ==  db.findTrackByID(anID, track);

}
void Tracks::add(Track & aTrack){
	ostringstream   sql;
	sql << "INSERT INTO tracks (tid,albumID,songID,track_number) VALUES("
		<< aTrack.getID()<<","
		<< aTrack.getAlbumID() << ","
		<< aTrack.getSongID() << ","
		<< aTrack.getTrackNumber()
		<< ")";
	Sqlite3Helper& db = Sqlite3Helper::get_instance();
	db.executeNonQuery(sql.str().c_str());
}
void Tracks::remove(Track & aTrack){
	ostringstream   sql;
	sql << "DELETE FROM tracks WHERE tid=" << aTrack.getID();
	Sqlite3Helper& db = Sqlite3Helper::get_instance();
	db.executeNonQuery(sql.str().c_str());
}
void Tracks::showOn(UI & view) {
  view.printOutput("Tracks:");
  vector<Track> tracks;
  const char * sql = "SELECT * FROM tracks";
  Sqlite3Helper& db = Sqlite3Helper::get_instance();
  db.queryTracks(sql, tracks);
  for (int i = 0; i < tracks.size(); i++) {
	  view.printOutput((tracks[i]).toString());
  }
}

void Tracks::showOn(UI & view, int memberID)  {
  view.printOutput("Track:");
  Track track;
  if (findByID(memberID, track)) {
	  view.printOutput(track.toString());
  }
}
