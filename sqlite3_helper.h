#pragma once
#include <string>
#include <vector>
#include "sqlite3.h"
#include "recording.h"
#include "song.h"
#include "user.h"
#include "track.h"
#include "playlist.h"
using namespace std;

class Sqlite3Helper
{
public:
	Sqlite3Helper();
	~Sqlite3Helper();
	Sqlite3Helper(const Sqlite3Helper&) = delete;
	Sqlite3Helper& operator=(const Sqlite3Helper&) = delete;
	static Sqlite3Helper& get_instance() {
		static Sqlite3Helper instance;
		return instance;

	}
	int executeNonQuery(const char *sql);
	int ExecuteScalar(const char *sql, int &value);
	int ExecuteScalar(const char *sql, string &value);

	int querySongs(const char *sql, vector<Song> &songs);
	int findSongByID(const int id, Song &song);
	int queryRecordings(const char *sql, vector<Recording> &recordings);
	int findRecordingByID(const int id, Recording &recording);
	int queryUsers(const char *sql, vector<User> &Users);
	int findUserByID(const string& id, User &user);
	int queryTracks(const char *sql, vector<Track> &tracks);
	int findTrackByID(const int id, Track &track);
	int queryPlaylists(const char *sql, vector<Playlist> &playlists);
	int findPlaylistByName(const string & aPlaylistName, Playlist &playlist);
private:
	sqlite3 *db;
};

