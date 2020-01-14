#include "sqlite3_helper.h"
#include <iostream>
#include <sstream>

Sqlite3Helper::Sqlite3Helper()
{
	int rc;
	const char * db_file_name = "beatles.db";
	rc = sqlite3_open(db_file_name, &db);
	if (rc) {
		cout << "ERROR: Could Not Open Database: "
			<< sqlite3_errmsg(db);
		cout << "\nEXITING\n";
	}
}


Sqlite3Helper::~Sqlite3Helper()
{
	sqlite3_close(db);
}

int Sqlite3Helper::executeNonQuery(const char *sql)
{
	sqlite3_stmt *stmt = NULL;
	int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

	if (result == SQLITE_OK) {
		result = sqlite3_step(stmt);
		if (result != SQLITE_DONE) {
			cout << sqlite3_errmsg(db) << endl;
		}
	}
	else {
		std::clog << sqlite3_errmsg(db) << endl;
	}
	sqlite3_finalize(stmt);
	return result;
}
int Sqlite3Helper::ExecuteScalar(const char *sql, int &value) {
	sqlite3_stmt *stmt = NULL;
	int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	if (result == SQLITE_OK) {
		while (sqlite3_step(stmt) == SQLITE_ROW) {
			value = sqlite3_column_int(stmt, 0);
			break;
		}
	}
	else {
		std::clog << sqlite3_errmsg(db) << endl;
	}
	sqlite3_finalize(stmt);
	return result;
}
int Sqlite3Helper::ExecuteScalar(const char *sql, string &value) {
	sqlite3_stmt *stmt = NULL;
	int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	if (result == SQLITE_OK) {
		while (sqlite3_step(stmt) == SQLITE_ROW) {
			value = (char*)sqlite3_column_text(stmt, 0);
			break;
		}
	}
	else {
		std::clog << sqlite3_errmsg(db) << endl;
	}
	sqlite3_finalize(stmt);
	return result;
}
int Sqlite3Helper::querySongs(const char *sql, vector<Song>& songs)
{
	sqlite3_stmt *stmt = NULL;
	int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	if (result == SQLITE_OK) {
		while (sqlite3_step(stmt) == SQLITE_ROW) {
			int id = sqlite3_column_int(stmt, 0);
			char *title = (char*)sqlite3_column_text(stmt, 1);
			char *composer = (char*)sqlite3_column_text(stmt, 2);
			songs.push_back(Song(title, composer, id));
		}
	}
	else {
		std::clog << sqlite3_errmsg(db) << endl;
	}
	sqlite3_finalize(stmt);
	return result;
}
int Sqlite3Helper::findSongByID(const int id, Song &song)
{
	ostringstream  sql;
	sql << "SELECT * FROM songs WHERE sid=" << id;
	sqlite3_stmt *stmt = NULL;
	int result = sqlite3_prepare_v2(db, sql.str().c_str(), -1, &stmt, NULL);
	if (result == SQLITE_OK) {
		while (sqlite3_step(stmt) == SQLITE_ROW) {
			int id = sqlite3_column_int(stmt, 0);
			char *title = (char*)sqlite3_column_text(stmt, 1);
			char *composer = (char*)sqlite3_column_text(stmt, 2);
			song = Song(title, composer, id);
			break;
		}
	}
	else {
		std::clog << sqlite3_errmsg(db) << endl;
	}
	sqlite3_finalize(stmt);
	return result;
}

int Sqlite3Helper::queryRecordings(const char *sql, vector<Recording> &recordings)
{
	sqlite3_stmt *stmt = NULL;
	int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	if (result == SQLITE_OK) {
		while (sqlite3_step(stmt) == SQLITE_ROW) {

			int id = sqlite3_column_int(stmt, 0);
			char *title = (char*)sqlite3_column_text(stmt, 1);
			char *artist = (char*)sqlite3_column_text(stmt, 2);
			char *producer = (char*)sqlite3_column_text(stmt, 3);
			int year = sqlite3_column_int(stmt, 4);
			recordings.push_back(Recording(title, artist, producer, to_string(year), id));
		}
	}
	else {
		std::clog << sqlite3_errmsg(db) << endl;
	}
	sqlite3_finalize(stmt);
	return result;
}
int Sqlite3Helper::findRecordingByID(const int id, Recording &recording)
{
	ostringstream  sql;
	sql << "SELECT * FROM recordings WHERE id=" << id;
	sqlite3_stmt *stmt = NULL;
	int result = sqlite3_prepare_v2(db, sql.str().c_str(), -1, &stmt, NULL);
	if (result == SQLITE_OK) {
		while (sqlite3_step(stmt) == SQLITE_ROW) {

			int id = sqlite3_column_int(stmt, 0);
			char *title = (char*)sqlite3_column_text(stmt, 1);
			char *artist = (char*)sqlite3_column_text(stmt, 2);
			char *producer = (char*)sqlite3_column_text(stmt, 3);
			int year = sqlite3_column_int(stmt, 4);
			recording = Recording(title, artist, producer, to_string(year), id);
			break;
		}
	}
	else {
		std::clog << sqlite3_errmsg(db) << endl;
	}
	sqlite3_finalize(stmt);
	return result;
}

int Sqlite3Helper::queryUsers(const char *sql, vector<User> &Users)
{
	sqlite3_stmt *stmt = NULL;
	int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	if (result == SQLITE_OK) {
		while (sqlite3_step(stmt) == SQLITE_ROW) {

			char *user_id = (char*)sqlite3_column_text(stmt, 0);
			char *name = (char*)sqlite3_column_text(stmt, 1);
			Users.push_back(User(user_id, name));
		}
	}
	else {
		std::clog << sqlite3_errmsg(db) << endl;
	}
	sqlite3_finalize(stmt);
	return result;
}
int Sqlite3Helper::findUserByID(const string& id, User &user)
{
	ostringstream  sql;
	sql << "SELECT * FROM users WHERE user_id=" << id;
	sqlite3_stmt *stmt = NULL;
	int result = sqlite3_prepare_v2(db, sql.str().c_str(), -1, &stmt, NULL);
	if (result == SQLITE_OK) {
		while (sqlite3_step(stmt) == SQLITE_ROW) {
			char *user_id = (char*)sqlite3_column_text(stmt, 0);
			char *name = (char*)sqlite3_column_text(stmt, 1);
			user = User(user_id, name);
			break;
		}
	}
	else {
		std::clog << sqlite3_errmsg(db) << endl;
	}
	sqlite3_finalize(stmt);
	return result;
}

int Sqlite3Helper::queryTracks(const char *sql, vector<Track> &tracks)
{
	sqlite3_stmt *stmt = NULL;
	int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	if (result == SQLITE_OK) {
		while (sqlite3_step(stmt) == SQLITE_ROW) {
			int tid = sqlite3_column_int(stmt, 0);
			int albumID = sqlite3_column_int(stmt, 1);
			int songID = sqlite3_column_int(stmt, 2);
			int track_number = sqlite3_column_int(stmt, 3);
			tracks.push_back(Track(tid, albumID, songID,track_number));
		}
	}
	else {
		std::clog << sqlite3_errmsg(db) << endl;
	}
	sqlite3_finalize(stmt);
	return result;
}
int Sqlite3Helper::findTrackByID(const int id, Track &track)
{
	ostringstream  sql;
	sql << "SELECT * FROM tracks WHERE tid=" << id;
	sqlite3_stmt *stmt = NULL;
	int result = sqlite3_prepare_v2(db, sql.str().c_str(), -1, &stmt, NULL);
	if (result == SQLITE_OK) {
		while (sqlite3_step(stmt) == SQLITE_ROW) {
			int tid = sqlite3_column_int(stmt, 0);
			int albumID = sqlite3_column_int(stmt, 1);
			int songID = sqlite3_column_int(stmt, 2);
			int track_number = sqlite3_column_int(stmt, 3);
			track = Track(tid, albumID, songID, track_number);
			break;
		}
	}
	else {
		std::clog << sqlite3_errmsg(db) << endl;
	}
	sqlite3_finalize(stmt);
	return result;
}

int Sqlite3Helper::queryPlaylists(const char *sql, vector<Playlist> &playlists)
{
	sqlite3_stmt *stmt = NULL;
	int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	if (result == SQLITE_OK) {
		while (sqlite3_step(stmt) == SQLITE_ROW) {
			char *playlist_name = (char*)sqlite3_column_text(stmt, 0);
			playlists.push_back(Playlist(playlist_name));
		}
	}
	else {
		std::clog << sqlite3_errmsg(db) << endl;
	}
	sqlite3_finalize(stmt);
	return result;
}

int Sqlite3Helper::findPlaylistByName(const string & aPlaylistName, Playlist &playlist)
{

	ostringstream  sql;
	sql << "SELECT * FROM playlists WHERE playlist_name='" << aPlaylistName<<"'";
	sqlite3_stmt *stmt = NULL;
	int result = sqlite3_prepare_v2(db, sql.str().c_str(), -1, &stmt, NULL);
	if (result == SQLITE_OK) {
		while (sqlite3_step(stmt) == SQLITE_ROW) {
			char *user_id = (char*)sqlite3_column_text(stmt, 0);
			char *playlist_name = (char*)sqlite3_column_text(stmt, 1);
			playlist = Playlist(playlist_name);
			break;
		}
	}
	else {
		std::clog << sqlite3_errmsg(db) << endl;
	}
	sqlite3_finalize(stmt);
	return result;
}