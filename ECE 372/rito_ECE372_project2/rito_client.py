import time
import socket
import sys
import signal
import os.path


USAGE_STRING = "usage: python3 chatserv.py [hostname] [control_port] [data_port] [command] or\n" + \
               "python3 chatserv.py [hostname] [control_port] [data_port] [command] [filename]"

VALID_YES_RESPONSES = ["", "Y", "y"]
BUFFER_SIZE = 256

class FTClient:
    def __init__(self, hostname, control_port, data_port, command, filename=None):
        super(FTClient, self).__init__()
        
        self.control_socket = None  # type: socket.socket
        self.data_socket = None  # type: socket.socket
        self.receive_socket = None  # type: socket.socket
        self.hostname = str(hostname)
        self.control_port = int(control_port)
        self.command = str(command)
        self.data_port = int(data_port)
        self.filename = str(filename)

        # ########## Create and connect to the sever on the control port ##########
        self.control_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.control_socket.connect((self.hostname, self.control_port))

        # ########## Setup and listen to the data socket for later ##########
        self.data_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.data_socket.bind((self.hostname, self.data_port))
        self.data_socket.listen(5)
        
        while 1:
            if command == '-g':
                self.control_socket.send(bytes(str(self.filename[:256]), "utf-8"))
                with open(self.filename, 'wb') as self.f:
                    print('file opened')
                    while True:
                        #print('receiving data...')
                        data = self.control_socket.recv(BUFFER_SIZE)
                        print('data=%s', (data))
                        if not data:
                            self.f.close()
                            print('file close()')
                            break
                        # write data to a file
                        self.f.write(data)
                        
                    self.f.close()
                        
            elif command == '-1':
                self.filename = 'dir_list'
                self.control_socket.send(bytes(str(self.filename[:256]), "utf-8"))
                print(self.filename)
                with open('Server Directory', 'wb') as self.f:
                    print('file opened')
                    while True:
                        #print('receiving data...')
                        data = self.control_socket.recv(BUFFER_SIZE)
                        print('data=%s', (data))
                        if not data:
                            self.f.close()
                            print('file close()')
                            break
                        # write data to a file
                        self.f.write(data)
                        
                    self.f.close()
            
            self.control_socket.close()
            exit()
            
            
if __name__ == "__main__":
    # ########## Get the number of command line arguments ##########
    num_args = len(sys.argv)

    # ########## If we don't have the right number of arguments, exit ##########
    if num_args < 5 or num_args > 6:
        print("Not enough arguments. Exiting...")
        print(USAGE_STRING)
        exit()

    # ########## Make an instance of the file transfer client with the correct arguments ##########
    if num_args == 5:
        FTClient(hostname=sys.argv[1], control_port=sys.argv[2], data_port=sys.argv[3], command=sys.argv[4])
    elif num_args == 6:
        FTClient(hostname=sys.argv[1], control_port=sys.argv[2], data_port=sys.argv[3], command=sys.argv[4], filename=sys.argv[5])

