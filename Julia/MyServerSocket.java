import java.io.PrintWriter;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.net.InetAddress;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.Scanner;
import java.lang.*;

public class MyServerSocket {
    private ServerSocket server;
    private static Opcom opcom;
    private double phi;
    private double theta;
    private double phiref;
    private double thetaref;
    private String data;
    private PlotData pdTheta;
    private PlotData pdPhi;

    public MyServerSocket(int portNumber) throws Exception {
        this.server = new ServerSocket(portNumber, 1, InetAddress.getLocalHost());
    }
    private void listen() throws Exception {
        Socket client = this.server.accept();
        String clientAddress = client.getInetAddress().getHostAddress();
        System.out.println("\r\nNew connection from " + clientAddress);

        BufferedReader in = new BufferedReader(
        new InputStreamReader(client.getInputStream()));
        PrintWriter out = new PrintWriter(client.getOutputStream());
        long dtime = System.currentTimeMillis();

        readIn(in);
        long h = System.currentTimeMillis();
        plot(0);
        long time = 0;
        while (true) {
            readIn(in);
            dtime = System.currentTimeMillis() - h;
            h = System.currentTimeMillis();
            time = time + dtime;
            plot(time/1000.0);
        }
    }


    private void readIn(BufferedReader in) {
        try {
            this.data = in.readLine();
        }catch(Exception e) {
            System.out.println(e);
        }
        String[] parts = data.split("/");
        this.phi = Double.parseDouble(parts[0]);
        this.theta = Double.parseDouble(parts[1]);
        this.phiref = Double.parseDouble(parts[2]);
        this.thetaref = Double.parseDouble(parts[3]);
    }

    private void plot(double dtime) {
        pdTheta = new PlotData();
        pdTheta.y = theta;
        pdTheta.ref = thetaref;
        pdTheta.x = dtime;
        pdPhi = new PlotData();
        pdPhi.y = phi;
        pdPhi.ref = phiref;
        pdPhi.x = dtime;
        opcom.putThetaDataPoint(pdTheta);
        opcom.putPhiDataPoint(pdPhi);
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
