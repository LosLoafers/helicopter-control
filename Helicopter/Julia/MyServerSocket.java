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
    private double u1;
    private double u2;
    private PlotData in1;
    private PlotData in2;
    public static boolean action;
    //private static boolean t = true;


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

            if(in.ready()){
                Opcom.reset.setEnabled(false);
                readIn(in);
                dtime = System.currentTimeMillis() - h;
                h = System.currentTimeMillis();
                time = time + dtime;
                plot(time/1000.0);
            } else if(System.currentTimeMillis()-h > 100){
                Opcom.reset.setEnabled(true);
            }
            if(action){
                
                break;
            }

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
        this.u1 = Double.parseDouble(parts[4]);
        this.u2 = Double.parseDouble(parts[5]);
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
        in1 = new PlotData();
        in1.y = u1;
        in1.x = dtime;
        in2 = new PlotData();
        in2.y = u2;
        in2.x = dtime;
        opcom.putu1DataPoint(in1);
        opcom.putu2DataPoint(in2);
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
        while(true){

            opcom = new Opcom();
            opcom.initializeGUI();
            opcom.start();
            action = false;
            app.listen();
    }

    }
}
