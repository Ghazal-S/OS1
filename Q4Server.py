import select, socket, sys, Queue,re
from collections import defaultdict
server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server.setblocking(0)
server.bind(('localhost', 50000))
server.listen(5)
inputs = [server]
outputs = []
message_queues = {}
groups = defaultdict(list)

while inputs:
    readable, writable, exceptional = select.select(
        inputs, outputs, inputs)
    for s in readable:
        if s is server:
            connection, client_address = s.accept()
            connection.setblocking(0)
            inputs.append(connection)
            message_queues[connection] = Queue.Queue()
        else:
            data = s.recv(1024)
            if data:
                print 'received "%s" from %s.' % (data, s.getpeername())
                if data.split("[")[0] == "join" :
                    groups[data.split("[")[1]].append(s)
                elif data.split("[")[0] == "send" :
                    for client in groups[(data.split("[")[1])]:
                            message_queues[client].put((data.split("[")[2]))
                elif data.split("[")[0] == "leave" :
                    groups[data.split("[")[1]].remove(s)
                elif data.split("[")[0] == "quit" :
                    s.close()

                        
                if s not in outputs:
                    outputs.append(s)
            else:
                if s in outputs:
                    outputs.remove(s)
                inputs.remove(s)
                s.close()
                del message_queues[s]

    for s in writable:
        try:
            next_msg = message_queues[s].get_nowait()
        except Queue.Empty:
            outputs.remove(s)
        else:
            print 'sending "%s" to %s' % (next_msg, s.getpeername())
            s.send(next_msg)

    for s in exceptional:
        inputs.remove(s)
        if s in outputs:
            outputs.remove(s)
        s.close()
        del message_queues[s]