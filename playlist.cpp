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

#include "playlist.h"
#include "sqlite3_helper.h"

Playlist::Playlist(const string & aPlaylistName){
	cout << "Playlist(string&)" << endl;
	name = aPlaylistName;
}
//Playlist::Playlist(const Playlist & aPlaylist){
//	cout << "Playlist(const Playlist & aPlaylist)" << endl;
//	cout << "ERROR: Playlist(const Playlist & aPlaylist) --should never run" << endl;
//}

Playlist::~Playlist(){
	cout << "~Playlist(void)" << endl;
}
int Playlist::getID(){return -1;}
string Playlist::getName(){return name;}

void Playlist::getTracks(vector<Track>& tracks){

	ostringstream   sql;
	sql << "SELECT tracks.tid,tracks.albumID,tracks.songID,tracks.track_number FROM tracks,playlist_tracks WHERE playlist_tracks.playlist_name='"
		<< name
		<< "' AND tracks.tid = playlist_tracks.track_id";
	Sqlite3Helper& db = Sqlite3Helper::get_instance();
	db.queryTracks(sql.str().c_str(), tracks);
}

//vector<Track*>::iterator Playlist::findPosition(Track & aTrack){
//	for (vector<Track*>::iterator itr = tracks.begin() ; itr != tracks.end(); ++itr)
//		if(*itr == &aTrack) return itr;
//	return tracks.end();
//}

void Playlist::addTrack(Track & aTrack){

	ostringstream   sql;
	sql << "INSERT INTO playlist_tracks(user_id, playlist_name, track_id) VALUES ((SELECT user_id FROM playlists WHERE playlist_name = '"
		<< name
		<<"'), '"
		<< name
		<<"', "
		<< aTrack .getID()
		<<")";
	Sqlite3Helper& db = Sqlite3Helper::get_instance();
	db.executeNonQuery(sql.str().c_str());
}

void Playlist::removeTrack(Track & aTrack){
	ostringstream   sql;
	sql << "DELETE FROM track WHERE tid=" << aTrack.getID();
	Sqlite3Helper& db = Sqlite3Helper::get_instance();
	db.executeNonQuery(sql.str().c_str());
}

string Playlist::toString()const {
	string indent = "     ";
	string s;
	s.append(name);
	s.append("\n");
	s.append(indent + indent + "Playlist Tracks:\n");
	vector<Track> tracks;
	ostringstream   sql;
	sql << "SELECT tracks.tid,tracks.albumID,tracks.songID,tracks.track_number FROM tracks,playlist_tracks WHERE playlist_tracks.playlist_name='"
		<< name
		<< "' AND tracks.tid = playlist_tracks.track_id";
	Sqlite3Helper& db = Sqlite3Helper::get_instance();
	db.queryTracks(sql.str().c_str(), tracks);
	for (vector<Track>::size_type i = 0 ; i < tracks.size(); i++){
		   s.append(indent + indent + to_string(i) + " " + (tracks[i]).toString() + "\n");
	}

	return s;
}

ostream & operator<<(ostream & out, const Playlist & aPlaylist){
	out << aPlaylist.toString() << endl;
	return out;
}
