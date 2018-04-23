import java.io.PrintWriter;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.net.InetAddress;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.Scanner;

public class MyServerSocket {
    private ServerSocket server;
    private static Opcom opcom;
    public MyServerSocket(int portNumber) throws Exception {
          this.server = new ServerSocket(portNumber, 1, InetAddress.getLocalHost());
    }
    private void listen() throws Exception {
        String data = null;
        Socket client = this.server.accept();
        String clientAddress = client.getInetAddress().getHostAddress();
        System.out.println("\r\nNew connection from " + clientAddress);

        BufferedReader in = new BufferedReader(
                new InputStreamReader(client.getInputStream()));
				PrintWriter out = new PrintWriter(client.getOutputStream());
                double time = 0;
        PlotData pdTheta;
        PlotData pdPhi;
        while ( (data = in.readLine()) != null ) {
            time += 0.5;   //0.005;
            Scanner sc = new Scanner(data);
            double phi = sc.nextDouble(),
                   theta = sc.nextDouble(),
                   phiref = sc.nextDouble(),
                   thetaref = sc.nextDouble();
                   pdTheta = new PlotData();
                   pdTheta.y = theta;
                   pdTheta.ref = thetaref;
                   pdTheta.x = time;
                   opcom.putThetaDataPoint(pdTheta);
                   pdPhi = new PlotData();
                   pdPhi.y = phi;
                   pdPhi.ref = phiref;
                   pdPhi.x = time;
                   opcom.putThetaDataPoint(pdPhi);


            /*
						String type = data.getClass().getName();
            System.out.println("\r\nMessage from " + clientAddress + ": " + data + "\nMessage type: " + type);
						out.println("\r\nYou sent: " + data + "\nMessage type: " + type);
						out.flush();*/
				}
    }
    public InetAddress getSocketAddress() {
        return this.server.getInetAddress();
    }

    public int getPort() {
        return this.server.getLocalPort();
    }
    public static void main(String[] args) throws Exception {
        MyServerSocket app = new MyServerSocket(2018);
        System.out.println("\r\nRunning Server: " +
                "Host=" + app.getSocketAddress().getHostAddress() +
                " Port=" + app.getPort());

        opcom = new Opcom();
        opcom.initializeGUI();
        opcom.start();
        app.listen();

    }
}
