Varje mapp i denna mapp (SimulinkMPCtest) inneh�ller olika verisioner av
 implementerade MPC. F�r att kunna k�ra dem s� �r det b�st att bara ha den
 aktuella mappen i sin path. Annar h�nder konstiga saker som jag inte 
kan f�rklara...

Den mest kompletta simuleringen �r Simulink_MPC_nonlinear_gainsheduling_kalman.
Den simulerar p� olinj�r process och uppdaterar A i varje itteration i MPCn.
For att skatta tillst�nden anv�nds ett extended kalman filter. 
Brus p� m�tningarna ger snabbt v�ldigt mycket s�mmre reglering. Vi beh�ver nog 
justera s� att det blir lite mer robust.

Saker som beh�ver l�ggas till:

*Vi beh�ver nog ha vilkoren p� u som umin<u<umax ist f�r u<abs(umax).
eftersom vi antagligen inte kan v�nda p� rotations riktningen p� propellerna.

*constraints p� tillst�nden

*L�gga in ett load disturbance tillst�nd f�r integral verkan.

*Justera alla konstnads parametrar f�r en mer robust reglering. 

*Kanske �ka prediktions horizonten? isf m�ste vi tunna ut p� summan 
och bara optimera p� vartannat sample f�r vi �r p� gr�nsen till vad CVXgen 
klarar av nu.




 
