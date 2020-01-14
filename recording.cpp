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

#include "recording.h"
#include "sqlite3_helper.h"

Recording::Recording(const string & aTitle,
           const string & anArtist,
           const string & aProducer,
           const string & aYear,
		   const int anID){
	//cout << "Recording(string&, string&, String&, String&, int)" << endl;
	title = aTitle;
	artist = anArtist;
	producer = aProducer;
	year = aYear;
	id = anID;
	//tracks = vector<Track*>(MAX_NUMBER_OF_TRACKS, NULL);
}
//Recording::Recording(const Recording & aRecording){
//	cout << "Recording(const Recording & aRecording)" << endl;
//	cout << "ERROR: Recording(const Recording & aRecording) --should never run" << endl;
//}
Recording::~Recording(){
	//cout << "~Recording(void)" << endl;
}
int Recording::getID(){return id;}
string Recording::getTitle()const { return title; }
string Recording::getArtist()const { return artist; }
string Recording::getProducer()const { return producer; }
string Recording::getYear()const { return year; }


void Recording::getTracks(vector<Track> &tracks)const{

	ostringstream   sql;
	sql << "SELECT * FROM tracks WHERE albumID = "
		<< id;
	Sqlite3Helper& db = Sqlite3Helper::get_instance();
	db.queryTracks(sql.str().c_str(), tracks);
}

//vector<Track*>::iterator Recording::findPosition(Track & aTrack){
//	for (vector<Track*>::iterator it = tracks.begin() ; it != tracks.end(); ++it)
//		if(*it == &aTrack) return it;
//	return tracks.end();
//}

//void Recording::addTrack(Track & aTrack, int position){
//	//add track if it does not already exist
//	vector<Track*>::iterator itr = findPosition(aTrack);
//	if(itr == tracks.end()) {
//		if(position >=0 && position < MAX_NUMBER_OF_TRACKS)
//		   tracks[position] = &aTrack;
//	}
//}

void Recording::removeTrack(Track & aTrack){
	ostringstream   sql;
	sql << "DELETE FROM tracks WHERE tid=" 
		<< aTrack.getID()
		<<" AND albumID="
		<<id;
	Sqlite3Helper& db = Sqlite3Helper::get_instance();
	db.executeNonQuery(sql.str().c_str());
}

string Recording::toString()const {
	string indent = "     ";
	string s;
	s.append(to_string(id) + " " + title + " " + artist + " " + producer + " " + year);
	s.append("\n");
	s.append(indent + "Tracks:\n");
	vector<Track> tracks;
	getTracks(tracks);
	for (vector<Track*>::size_type i = 0 ; i < tracks.size(); i++){
		   s.append(indent + to_string(i) + " " + (tracks[i]).toString() + "\n");
	}
	return s;
}

ostream & operator<<(ostream & out, const Recording & aRecording){
	out << aRecording.toString() << endl;
	return out;
}
