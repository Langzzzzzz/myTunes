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

#include "recordings.h"
#include "recording.h"
#include "sqlite3_helper.h"
Recordings::Recordings(){
}
Recordings::~Recordings(void){

}
void Recordings::getCollection(vector<Recording> collection){
	const char * sql = "SELECT * FROM recordings";
	Sqlite3Helper& db = Sqlite3Helper::get_instance();
	db.queryRecordings(sql, collection);
}
//
//vector<Recording*>::iterator Recordings::findPosition(Recording & aRecording){
//	for (vector<Recording*>::iterator it = collection.begin() ; it != collection.end(); ++it)
//		if(*it == &aRecording) return it;
//	return collection.end();
//}
bool Recordings::findByID(int anID, Recording &recording){
	Sqlite3Helper& db = Sqlite3Helper::get_instance();
	return SQLITE_OK == db.findRecordingByID(anID, recording);
}
void Recordings::add(Recording & aRecording){
	ostringstream   sql;
	sql << "INSERT INTO recordings (id,title,artist,producer,year) VALUES ("
		<< aRecording.getID()<<",'"
		<< aRecording.getTitle() << "','"
		<< aRecording.getArtist() << "','"
		<< aRecording.getProducer() << "',"
		<< aRecording.getYear()
		<< ")";
	Sqlite3Helper& db = Sqlite3Helper::get_instance();
	db.executeNonQuery(sql.str().c_str());
}
void Recordings::remove(Recording & aRecording){
	ostringstream   sql;
	sql << "DELETE FROM recordings WHERE id=" << aRecording.getID();
	Sqlite3Helper& db = Sqlite3Helper::get_instance();
	db.executeNonQuery(sql.str().c_str());
}
void Recordings::showOn(UI & view)  {
  view.printOutput("Recordings:");
  vector<Recording> recordings;
  const char * sql = "SELECT * FROM recordings";
  Sqlite3Helper& db = Sqlite3Helper::get_instance();
  db.queryRecordings(sql, recordings);
  for (int i = 0; i < recordings.size(); i++) {
	  view.printOutput((recordings[i]).toString());

  }
}
void Recordings::showOn(UI & view, int memberID)  {
  view.printOutput("Recording:");
  Recording recording;
  
  if (findByID(memberID, recording)) {
	  view.printOutput(recording.toString());
  }
}
