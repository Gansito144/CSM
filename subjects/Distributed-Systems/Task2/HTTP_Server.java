import java.io.*;
import java.util.*;
import java.lang.*;
import java.net.*;

public class HTTP_Server{
    public static void main(String[] args) throws Exception {
	try {
        // socket creation
        int port = 1989;
        ServerSocket serverSocket = new ServerSocket(port);
        System.err.println("Server running in port : " + port);
        // repeatedly wait for connections, and process
        while (true) {
            // you are stuck on waiting for a client request
            Socket clientSocket = serverSocket.accept();
            System.err.println("New client, process it");
            Connection c = new Connection(clientSocket);
        }
    } catch(IOException e) {
        System.out.println(e.getMessage());
	}
    }
}

class Connection extends Thread {
    BufferedReader in;
    BufferedWriter out;
    Socket clientSocket;
    public Connection (Socket nClientSocket) {
        try {
            // opening flow
            clientSocket = nClientSocket;
            in = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
            out = new BufferedWriter(new OutputStreamWriter(clientSocket.getOutputStream()));
            this.start();
        }
        catch(IOException e) {
            System.out.println(e.getMessage());
        }
    }
    public void run() {
        try {
            // Each time data is read from the network is the reference
            // on the writing flow. the read data is returned to exactly
            // the same client.

            String str;
            while ((str = in.readLine()) != null) {
                if (str.isEmpty()) {
                    break;
                }
                System.out.println(str);
            }
            
            Date today = new Date();
            String httpResponse = "HTTP/1.1 200 OK\r\n\r\n" + today;
            out.write(httpResponse);

            // Flow is closed.
            System.err.println("Connecting completed");
        }
        catch(IOException e) {
            System.out.println(e.getMessage());
        }
        finally{
            try {
                out.close();
                in.close();            
                clientSocket.close();
            }
            catch (IOException e){
                System.out.println(e.getMessage());
            }
        }
    }
}
