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

#ifndef _TRACK_H
#define _TRACK_H

#include <ostream>
#include <string>
using namespace std;

#include "song.h"

class Track {
	/*
	Track represents a audio recording of a single Song
	*/
	public:
	Track() {}
	Track(const int aTrackID, const int albumID, const int aSongID, const int trackNumber, const string & anMp3FileName = "Unknown" );
	~Track(void);
	int getID();
	int getAlbumID();
	int getSongID();
	int getTrackNumber();
    bool getSong(Song &song);
    string getMp3FileName();
	string toString() const;
	private:
	int id;
	int albumid;
	//Song * song; //song that tracks is a recording of
	int songid;
	int tracknumber;
	string mp3FileName;
	//Track(const Track & aTrack); //hide copy constructor in private section
};

ostream & operator<<(ostream & out, const Track & aTrack);

#endif
