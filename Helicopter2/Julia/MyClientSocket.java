import java.io.*;
import java.net.*;
import java.util.Scanner;

public class MyClientSocket {
	private Socket clientSocket;
	private DataOutputStream os;
	private Scanner scan;

	public MyClientSocket(int port) throws IOException, UnknownHostException{
		clientSocket = new Socket(InetAddress.getLocalHost(),port);
		os = new DataOutputStream(clientSocket.getOutputStream());
	}

	private void send() throws IOException, UnknownHostException{
		String data;
		scan = new Scanner(System.in);
		int count = 1;
		 	while(true) {
			 	data = getData();
				if(data.equals("close;")) {
					break;
				}
				os.write(data.getBytes("UTF-8"));
				System.out.println(data + " was sent to server.");
		 }
		os.close();
		clientSocket.close();
		System.out.println("Connection terminated");
	}
	// Hämtar data från java app.
	private String getData() {
		System.out.println("Ready to receive data");
		return scan.nextLine() + ";";
	}

	public static void main(String[] args) {
		try{
			MyClientSocket client = new MyClientSocket(2018);
			client.send();
		} catch(IOException e) {
			System.err.println("Something went wrong: " + e);
		}
	}
}
