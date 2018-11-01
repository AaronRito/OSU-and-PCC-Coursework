Aaron Rito
Cs372
Project 2 read-me


To run the program:

Server: Use the makefile to build the C project. To run the server use the command: ./rito_server [port]
Client: Usage: ./rito_client [IP(if on OSU flip server use 127.0.0.1)] [signal port] [data port] [command] [file name (if command is -g)]
It's best to use a different directory for the client....

Details:
The program runs per the specifications. Enter the command when starting the client to get directory listing or file. The server will create a new data connection
to handle up to N multithread clients at a time. 
If a file is duplicate name, the server will respond bad file name error and send no data. 
When listing the directory, the server will throw a bad file error afterwards (not sure why?), this can be ignored, the server will continue to listen for more clients.
Use cntrlC to quit the server. 

The client will write the data to the file name specified, or to a file called "Server Directory" if -1 command is used. 
The client will exit on its own. 

Extra Credit:
The program can send any type of file(text or binary).
The program can send and size of file(tested at 300kb).
The program can handle multiple clients at the same time. To test: send requests from multiple clients (you'll need 2 machines) (VERY HARD TO IMPLIMENT!)

Notes: The difficulty of the multi-threading is why my program is late.

Sources: https://github.com/caperren/CS372/tree/master/Project%202
https://cboard.cprogramming.com/linux-programming/78236-list-files-directory-without-folders.html 
 /home/mostafa/netprog/tcpsockex/getfile2_srv.c (click the pdf link)