To run the Julia implementation on the real processes do the following in the given order:
(The java plotter must running before Julia start because it provides a TCP connection)

1. Start up 2 terminals.
2. cd to FINAL/Julia/Java/ in one terminal.
3. if there are no .class files in the directory compile the .java files by typing:
	javac -classpath .:regler.jar *.java
4. start MyServerSocket by typing:
	java -classpath .:regler.jar MyServerSocket
   A window with plots should appear.
5. cd to FINAL/Julia/ in the other terminal.
6. start julia with 2 workers by typing:
	julia -p 2
7. in julia type: (This will take a while)
	using LabProcesses
8. turn on the helicopter on the big button on the front.
9. when 7. is complete (takes around 2min), run the process by typing into julia:
	include("heli3.jl")
10. OBS! to abort, if the process goes crazy or you are done, type into julia:
	@everywhere wsr=false
   If this does not work, turn the helicopter off and run the reset script by typing into julia:
	include("reset.jl")
   Start the helicopter again. Repeat if it did not work. It is a bit weird sometimes.
11. OBS! Do not turn off julia if you want to keep running the helicopter as you will need to repeat 6. every time julia restarts which is quite annoying. It is possible to make an image file for LabProcesses but it is not allowed on for students on the student computers.


GOOD LUCK!
