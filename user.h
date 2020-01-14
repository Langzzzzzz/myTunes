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

#ifndef _User_H
#define _User_H

#include <ostream>
#include <string>
#include <vector>

#include "playlist.h"

class User {
	/*
	User represents an application user.
	*/
	public:
	User() {}
	User(const string & aUserID,
	          const string & aName);
	~User(void);
    int getID();
    string getUserID();
	string getName()const;
	bool findPlaylist(const string & aPlaylistName, Playlist &playlist);
	void removePlaylist(Playlist & aPlayList);
	void addPlaylist(Playlist & aPlayList);
	void removeTrack(Track & aTrack);
	void remove();
    string toString() const;

	private:
	static int nextUserNumericID;
	int id; //numeric id for uniformity with other model classes
	string userid;
	string name;
	//vector<Playlist*> playlists;
	//vector<Playlist*>::iterator findPosition(Playlist & aPlaylist);
	//User(const User & aUser); //hide copy constructor in private section
};

ostream & operator<<(ostream & out, const User & aUser);

#endif