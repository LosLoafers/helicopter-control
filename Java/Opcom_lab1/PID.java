// PID class to be written by you
public class PID {
	// Current PID parameters
	private PIDParameters p;
	private double yold = 0;
	private double e;
	private double v;
	private double I;
	private double D;
	// Constructor
	public PID(String name){
		PIDParameters p = new PIDParameters();
		p.Beta = 1.0;
		p.H = 0.02;
		p.integratorOn = false;
		p.K = -0.2;
		p.Ti = 0.0;
		p.Tr = 10.0;
		p.Td = 1.15;
		p.N = 7;
		new PIDGUI(this, p, name);
		setParameters(p);

		this.I = 0.0;
		this.v = 0.0;
		this.e = 0.0;
		this.D = 0.0;
	}

	// Calculates the control signal v.
	// Called from BallAndBeamRegul.
	public synchronized double calculateOutput(double y, double yref){
		D = (p.Td/(p.Td + p.N*p.H))*D - (p.K*p.Td*p.N/(p.Td+p.N*p.H))*(y-yold);
		this.e = yref - y;
		this.v = p.K*(p.Beta*yref-y) + I + D;
		yold = y;
		return this.v;
	}

	// Updates the controller state.
	// Should use tracking-based anti-windup
	// Called from BallAndBeamRegul.
	public synchronized void updateState(double u){
		if (p.integratorOn) {
			I=I+p.K*p.H*e/p.Ti + (p.H/p.Tr)*(u-v);
		} else{
			I = 0.0;
		}
	}

	// Returns the sampling interval expressed as a long.
	// Explicit type casting needed.
	public synchronized long getHMillis(){
		return (long)(p.H*1000);
	}

	// Sets the PIDParameters.
	// Called from PIDGUI.
	// Must clone newParameters.
	public synchronized void setParameters(PIDParameters newParameters){
		p = (PIDParameters)newParameters.clone();
		if (!p.integratorOn) {
			I = 0.0;
		}
	}

	public synchronized PIDParameters getParameters(){
		return p;
	}
	public synchronized void reset(){
		p.Beta = 1.0;
		p.H = 0.02;
		p.integratorOn = false;
		p.K = -0.2;
		p.Ti = 0.0;
		p.Tr = 10.0;
		p.Td = 1.15;
		p.N = 7;
		setParameters(p);

		this.I = 0.0;
		this.v = 0.0;
		this.e = 0.0;
		this.D = 0.0;
		this.yold = 0;
	}
}
