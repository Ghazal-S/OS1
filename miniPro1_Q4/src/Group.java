import java.util.ArrayList;

public class Group {
ArrayList<String> clients = new ArrayList<>();
String ID;
public Group(String ID){
    this.ID = ID;
}

    public ArrayList<String> getClients() {
        return clients;
    }

    public void setClients(ArrayList<String> clients) {
        this.clients = clients;
    }

    public String getID() {
        return ID;
    }

    public void setID(String ID) {
        this.ID = ID;
    }

    public void addClient(String client){
    clients.add(client);
}
    public void removeClient(String client){
    clients.remove(client);
    }
}
