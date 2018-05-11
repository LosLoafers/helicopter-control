import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import se.lth.control.*;
import se.lth.control.plot.*;
import java.net.InetAddress;
import java.net.ServerSocket;
import java.net.Socket;


class PlotData implements Cloneable {
    double ref, y;
    double x; // holds the current time

    public Object clone() {
        try {
	    return super.clone();
        } catch (Exception e) {return null;}
    }
}
/*
class Reader extends Thread {

       private Opcom opcom;

       private MyServerSocket socket;



       private boolean doIt = true;

       public Reader(Opcom opcom) {

              this.opcom = opcom;


              try{
                     socket = new MyServerSocket(2018);
              }
              catch (Exception e){
                     System.out.println(e);
              }

       }

       // Stops the thread.
       private void stopThread() {
              doIt = false;
       }
}*/

public class Opcom {

       private PlotterPanel ThetaPlotter;
       private PlotterPanel PhiPlotter;
       private PlotterPanel u1Plotter;
       private PlotterPanel u2Plotter;


       private JFrame frame;

       // Declaration of panels.
       private BoxPanel plotterPanel;
       private BoxPanel top;
       private BoxPanel middle;
       private BoxPanel lower;

       public static JButton reset;

       private double range = 10.0; // Range of time axis
       private int divTicks = 5;    // Number of ticks on time axis
       private int divGrid = 5;     // Number of grids on time axis



       public Opcom() {
              ThetaPlotter = new PlotterPanel(2, 4); // Two channels
              PhiPlotter = new PlotterPanel(2, 4);
              u1Plotter = new PlotterPanel(1, 4);
              u2Plotter = new PlotterPanel(1, 4);
       }

       public void start() {
              ThetaPlotter.start();
              PhiPlotter.start();
              u1Plotter.start();
              u2Plotter.start();
       }

       /** Stops the threads. */
       public void stopThread() {
              ThetaPlotter.stopThread();
              PhiPlotter.stopThread();
              u1Plotter.stopThread();
              u2Plotter.stopThread();
       }

       public void initializeGUI() {
              // Create main frame.
              frame = new JFrame("Helicopter");

              // Create a panel for the two plotters.
              top = new BoxPanel(BoxPanel.HORIZONTAL);
              middle = new BoxPanel(BoxPanel.HORIZONTAL);
              plotterPanel = new BoxPanel(BoxPanel.VERTICAL);
              lower = new BoxPanel(BoxPanel.VERTICAL);
              ThetaPlotter.setYAxis(3, -1.5, 6, 6);
              ThetaPlotter.setXAxis(range, divTicks, divGrid);
              ThetaPlotter.setTitle("Position and refrence (vertical/Theta)");
              top.add(ThetaPlotter);
              top.addFixed(10);
              plotterPanel.addFixed(10);
              PhiPlotter.setYAxis(3.2, -1.6, 4, 4);
              PhiPlotter.setXAxis(range, divTicks, divGrid);
              PhiPlotter.setTitle("Position and refrence (horizontal/Phi)");
              top.add(PhiPlotter);
              u1Plotter.setYAxis(24, -12, 6, 6);
              u1Plotter.setXAxis(range, divTicks, divGrid);
              u1Plotter.setTitle("u1");
              middle.add(u1Plotter);
              middle.addFixed(10);
              u2Plotter.setYAxis(24, -12, 6, 6);
              u2Plotter.setXAxis(range, divTicks, divGrid);
              u2Plotter.setTitle("u2");
              middle.add(u2Plotter);

              reset = new JButton("Reset");
              reset.setEnabled(false);
              reset.addActionListener(new ActionListener() {
                     public void actionPerformed(ActionEvent e) {
                            frame.dispose();
                            MyServerSocket.action = true;

			}
		});

              lower.add(reset);
              lower.addFixed(10);
              plotterPanel.add(top);
              plotterPanel.add(middle);
              plotterPanel.add(lower);
              frame.add(plotterPanel);
              frame.addWindowListener(new WindowAdapter() {
                     public void windowClosing(WindowEvent e) {
                            //reader.shutDown();
                            stopThread();
                            System.exit(0);
                     }
              });

              // Set guiPanel to be content pane of the frame.
              frame.getContentPane().add(plotterPanel, BorderLayout.CENTER);

              // Pack the components of the window.
              frame.pack();

              // Position the main window at the screen center.
              Dimension sd = Toolkit.getDefaultToolkit().getScreenSize();
              Dimension fd = frame.getSize();
              frame.setLocation((sd.width-fd.width)/2, (sd.height-fd.height)/2);

              // Make the window visible.
              frame.setVisible(true);
       }
       /** Called by Reader to put a control signal data point in the buffer. */
       public synchronized void putPhiDataPoint(PlotData pd) {
                   double x = pd.x;
                   double y = pd.y;
                   double ref = pd.ref;
                   PhiPlotter.putData(x, y, ref);
       }

       /** Called by Reader to put a measurement data point in the buffer. */
       public synchronized void putThetaDataPoint(PlotData pd) {
                   double x = pd.x;
                   double y = pd.y;
                   double ref = pd.ref;
                   ThetaPlotter.putData(x, y, ref);
       }
       public synchronized void putu1DataPoint(PlotData pd) {
              double x = pd.x;
              double y = pd.y;

              u1Plotter.putData(x, y);
 }
 public synchronized void putu2DataPoint(PlotData pd) {
        double x = pd.x;
        double y = pd.y;

        u2Plotter.putData(x, y);
}




       /*public static void main(String[] argv) {
              Opcom opcom = new Opcom();
              opcom.initializeGUI();
              Reader reader = new Reader(opcom);
              opcom.start();
       }*/
}
