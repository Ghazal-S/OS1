import java.io.*;
import java.net.Socket;
import java.util.ArrayList;
import java.util.Scanner;

public class Client {
    String str;
    int i;
    byte b;
    Socket clientSocket;
    Scanner userInputScanner;
    DataInputStream inFromServer;
    DataOutputStream outToServer;

    public Client(String s) {
        try {

            clientSocket = new Socket(s, 5000);
            System.out.println("connected");
            userInputScanner = new Scanner(System.in);
            String command = userInputScanner.next();
            inFromServer = new DataInputStream(new BufferedInputStream(clientSocket.getInputStream()));
            outToServer = new DataOutputStream(clientSocket.getOutputStream());
            while(true){
                sendServer(command);
                command = userInputScanner.next();
            }

        } catch (IOException e) {
            System.err.println("IOException:  " + e);
        }
    }

    public void sendServer(String str) {
        try {
            outToServer.writeUTF(str);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }


    public String fromServer() {
        try {
            str = inFromServer.readUTF();

        } catch (IOException e) {
            e.printStackTrace();
        }
        return str;
    }



}


