import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import se.lth.control.*;
import se.lth.control.plot.*;
import java.net.InetAddress;
import java.net.ServerSocket;
import java.net.Socket;



class Reader extends Thread {

       private Opcom opcom;

       private boolean doIt = true;

       public Reader(Opcom opcom) {

              this.opcom = opcom;

       }

       /** Stops the thread. */
       private void stopThread() {
              doIt = false;
       }
}

public class Opcom {

       private PlotterPanel measurementPlotter;
       private PlotterPanel controlPlotter; // has internal thread

       private JFrame frame;

       // Declaration of panels.
       private BoxPanel plotterPanel;

       private double range = 10.0; // Range of time axis
       private int divTicks = 5;    // Number of ticks on time axis
       private int divGrid = 5;     // Number of grids on time axis

       private boolean hChanged = false;

       public Opcom() {
              measurementPlotter = new PlotterPanel(2, 4); // Two channels
              controlPlotter = new PlotterPanel(1, 4);
       }

       public void start() {
              measurementPlotter.start();
              controlPlotter.start();
       }

       /** Stops the threads. */
       public void stopThread() {
              measurementPlotter.stopThread();
              controlPlotter.stopThread();
       }

       public void initializeGUI() {
              // Create main frame.
              frame = new JFrame("Helicopter");

              // Create a panel for the two plotters.
              plotterPanel = new BoxPanel(BoxPanel.VERTICAL);

              measurementPlotter.setYAxis(180, -90, 6, 6);
              measurementPlotter.setXAxis(range, divTicks, divGrid);
              measurementPlotter.setTitle("Position and refrence (vertical)");
              plotterPanel.add(measurementPlotter);
              plotterPanel.addFixed(10);
              controlPlotter.setYAxis(360, -180, 4, 4);
              controlPlotter.setXAxis(range, divTicks, divGrid);
              controlPlotter.setTitle("Position and refrence (horizontal)");
              plotterPanel.add(controlPlotter);

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




       public static void main(String[] argv) {
              Opcom opcom = new Opcom();
              opcom.initializeGUI();
              Reader reader = new Reader(opcom);
              opcom.start();
       }
}
