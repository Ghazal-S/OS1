import socket
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect(('localhost', 50000))
message = input()
s.sendall(message)
data = s.recv(1024)
s.close()
