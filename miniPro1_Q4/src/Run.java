import java.io.IOException;
import java.util.Scanner;

//"127.0.0.1"
public class Run {
    public static void main(String[] args) throws IOException {
        System.out.println("Enter the IP address of a machine running the capitalize server:");
        Scanner scanner = new Scanner(System.in);
        String serverAddress = scanner.nextLine();
        String command = scanner.next();
        Client client1 = new Client(serverAddress);

    }
}

