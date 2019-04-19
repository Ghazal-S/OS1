

import socket
import sys
import select

s = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
s.connect(('localhost', 50000))
#sys.stdout.write('your message: ')
#sys.stdout.flush()
while True:
    r, w, x = select.select([sys.stdin, s], [], [])
    if not r:
        continue
    if r[0] is sys.stdin:
        message = raw_input()
        s.send(message)

    else:
        data = s.recv(1024)
        print "message from server:" , data

