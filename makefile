OBJ = main.o mytunes.o UI.o command.o str_util.o playlist.o recording.o recordings.o song.o songs.o track.o tracks.o user.o users.o sqlite3.o sqlite3_helper.o

mytunes: $(OBJ)
	g++ -std=c++11 -o mytunes $(OBJ) -lpthread -ldl

main.o:	main.cpp
	g++ -c -std=c++11 main.cpp

mytunes.o:	mytunes.cpp mytunes.h UI.h
	g++ -c -std=c++11 mytunes.cpp

UI.o:	UI.cpp UI.h
	g++ -c -std=c++11 UI.cpp

command.o:	command.cpp command.h
	g++ -c -std=c++11 command.cpp

str_util.o:	str_util.cpp str_util.h
	g++ -c -std=c++11 str_util.cpp

playlist.o: playlist.cpp track.h playlist.h
	g++ -c -std=c++11 playlist.cpp

recording.o: recording.cpp track.h recording.h
	g++ -c -std=c++11 recording.cpp

recordings.o: recordings.cpp recordings.h recording.h
	g++ -c -std=c++11 recordings.cpp

song.o: song.cpp song.h
	g++ -c -std=c++11 song.cpp

songs.o: songs.cpp song.h songs.h
	g++ -c -std=c++11 songs.cpp

track.o: track.cpp track.h song.h
	g++ -c -std=c++11 track.cpp

tracks.o: tracks.cpp tracks.h track.h
	g++ -c -std=c++11 tracks.cpp

user.o: user.cpp user.h
	g++ -c -std=c++11 user.cpp

users.o: users.cpp users.h user.h
	g++ -c -std=c++11 users.cpp

sqlite3.o: sqlite3.c sqlite3.h
	gcc -c sqlite3.c sqlite3.h

sqlite3_helper.o: sqlite3_helper.cpp sqlite3_helper.h
	g++ -c -std=c++11 sqlite3_helper.cpp

clean:
	rm -f $(OBJ) mytunes
