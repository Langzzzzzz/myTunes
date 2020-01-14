Author: Zhenqing Lang
        Payton Pei

### Compile Instruction:
  just type make
  <br>and you may start testing our programme
  <br>use valgrind ./mytunes to test memory leak problem
  <br>use .read script.txt to run our simulated script.

### Command
        add //add data to collections
            //add recordings
            add -r recording_id title artist producer year
            add -r 103 "Beatles For Sale" "Beatles" "George Martin" 1964
            //add songs
            add -s song_id title composer //add song
            add -s 1001 "Misery" "Paul McCartney, John Lennon"
            //add tracks
            add -t track_id album_id song_id track_number
            add -t 10 100 1000 1

            //OPTIONAL REV 3 --YOU DON'T NEED TO SUPPORT THIS IN YOUR ASSIGNMENT #2
            //add track (audio) represents a song but is not yet associated with an album (recording)
            add -t track_id null song_id
            add -t 10 null 1000
            //add track (audio) representing a song and auto-allocate a track number for it
            add -t ? null song_id
            add -t ? null 1000
            //END OPTIONAL REV 3 

            //add users
            add -u user_id name
            add -u ajones "Anne Jones"
            //add playlists
            add -p user_id, playlist_name
            add -p ajones "Driving Songs"
            //add playlist tracks
            add -l user_id playlist_name track_id
            add -l gjones "mysongs" 1

        delete  //delete data from collections
            delete -s song_id //delete song based on song id (based on title, composer etc.)
            delete -s track_id -p playlist_name -u user_name //DEPRECATED delete track from playlist
            delete -t track_id -p playlist_name -u user_name //delete track from playlist
            delete -Global -s track_id -p playlist_name -u user_name  //DEPRECATED but still supported
            delete -Global -t track_id -p playlist_name -u user_name
            delete -r recording_id //delete recording 
            delete -u user_id //delete user
            delete -p playist_name -u user_id //delete user playlist
            delete -t track_id  //delete track

        show    //show entries in collections
            show songs
            show users
            show playlists -u user_id
            show songs -u user_id -p playlist_name
            show recordings
            show tracks

        UI SHELL COMMANDS (start with a dot):

        .quit   //quit the application

        .read   //read a script file
                .read filename

        .log    //log commands and output
                //THIS DOT COMMAND IS SCRIPTABLE
                .log clear //clear the logs
                .log start //begin logging commands only
                .log start_output //begin logging output only
                .log start_both  //begin logging commands and output
                .log stop //stop logging
                .log save filename //save log to filename
                .log show //display current log contents on console

        .help   //show this help menu

        //   //comments
             Any input starting with "//" or any output
             starting with "//" is treated as a comment.
             If input on CLI the comment will be written to log file.
             Comments may appear in command script file.

        DEVELOPER COMMANDS (NOT FOR PRODUCTION):
        //These provide are to test certain developer functions
        .trim    //trim the argument
                .trim "  a   day ago" //a day ago
        .startsWith    //test string prefix
                .startsWith "Hello" "Hel" //true
        .endsWith    //test string suffix
                .endsWith "Hello" "llo" //true
        .toTitleCase    //returns title cased string
                .toTitleCase "the girl from ipanema" //Girl From Ipanema, The
