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
using namespace std;

#include "track.h"
#include "sqlite3_helper.h"

Track::Track(const int aTrackId, const int albumID, const int aSongID, const int trackNumber, const string & anMp3FileName ){
	//cout << "Track(int, Song*, string&)" << endl;
	id = aTrackId;
	albumid = albumID;
	songid = aSongID;
	tracknumber = trackNumber;
	mp3FileName = anMp3FileName;
}
//Track::Track(const Track & aTrack){
//	cout << "Track(const Track & aTrack)" << endl;
//	cout << "ERROR: Track(const Track & aTrack) --should never run" << endl;
//}
Track::~Track(){
	//cout << "~Track(void)" << endl;
}
int Track::getID(){return id;}
int Track::getAlbumID() { return albumid; }
int Track::getSongID() { return songid; }
int Track::getTrackNumber(){ return tracknumber; }

bool Track::getSong(Song &song){

	Sqlite3Helper& db = Sqlite3Helper::get_instance();
	return SQLITE_OK == db.findSongByID(songid, song);
}
string Track::getMp3FileName(){return mp3FileName;}

string Track::toString()const {
	Song song;
	Sqlite3Helper& db = Sqlite3Helper::get_instance();
	if (SQLITE_OK != db.findSongByID(songid, song)) {
		return "";
	}
	string title = song.getTitle();
	return to_string(id) + ": " + title + " mp3: " + mp3FileName;
}

ostream & operator<<(ostream & out, const Track & aTrack){
	out << aTrack.toString() << endl;
	return out;
}
