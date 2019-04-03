import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.ArrayList;


public class Server {



    public static void main(String[] args) throws Exception {
        ArrayList<DataInputStream> inFromClient = new ArrayList<>();
        ArrayList<DataOutputStream> outToClient = new ArrayList<>();
        ArrayList<Group> groups = new ArrayList<>();
        ArrayList<String> clients = new ArrayList<>();
        int clientNumber = 0;
        try (ServerSocket server = new ServerSocket(5000)) {
            while (true) {
                System.out.println("Waiting for a client to connect...");
                Capitalizer c = new Capitalizer(server.accept(), clientNumber++);
                clients.add(c.getter());
                inFromClient.add(c.getIn());
                outToClient.add(c.getOut());
                c.start();

            }
        }
    }
}

class Capitalizer extends Thread {

    ArrayList<Group> groups = new ArrayList<>();
    private int clientNumber;
    private DataInputStream in;
    private DataOutputStream out;
    private Socket connectionSocket;

    public Capitalizer(Socket socket, int clientNumber) {
        connectionSocket = socket;
        this.clientNumber = clientNumber;
        System.out.println("New client #" + clientNumber + " connected at " + socket);
        System.out.println(socket.getPort());
        System.out.println(socket.getInetAddress().getHostAddress());

    }

    public String getter() {
        return connectionSocket.getInetAddress().getHostAddress();
    }

    public DataInputStream getIn() {
        return in;
    }

    public DataOutputStream getOut() {
        return out;
    }

    public void run() {
        try {

            in = new DataInputStream(new BufferedInputStream(connectionSocket.getInputStream()));
            out = new DataOutputStream(connectionSocket.getOutputStream());
            System.out.println("client accepted");


            while (true) {
                String line = in.readUTF();
                String[] splitted = line.split("[|]");
                if (line.startsWith("Join"))  {
                    for(Group group:groups){
                        if(group.getID() == splitted[1]){
                            group.addClient(this.getter());
                        }
                    }

                }

                if (line.startsWith("Send")) {


                }

                if (line.startsWith("Leave")) {
                    for(Group group:groups){
                        if(group.getID() == splitted[1]){
                            group.removeClient(this.getter());
                        }
                    }

                }
                if (line.startsWith("Quit")) {
                    connectionSocket.close();
                }



            }


        } catch (IOException e) {
            System.err.println("IOException:  " + e);
        } finally {
            try {
                connectionSocket.close();
            } catch (IOException e) {
            }
            System.out.println("Connection with client #" + clientNumber + " closed");
        }
    }




}

