Varje mapp i denna mapp (SimulinkMPCtest) inneh�ller olika verisioner av
 implementerade MPC. F�r att kunna k�ra dem s� �r det b�st att bara ha den
 aktuella mappen i sin path. Annar h�nder konstiga saker som jag inte 
kan f�rklara...

Den mest kompletta simuleringen �r Simulink_MPC_nonlinear_gainsheduling_kalman_itegralact.
Den simulerar p� olinj�r process och uppdaterar A i varje itteration i MPCn.
For att skatta tillst�nden anv�nds ett extended kalman filter. 
Brus p� m�tningarna ger snabbt s�mmre reglering. Vi beh�ver nog 
justera s� att det blir lite mer robust. Integratorn �r inte heller speciellt bra justerad.

Det finns �ven en verision som tar h�nsyn till att theta har ett stopp. dvs armen stannar 
i en viss vinkel. I vanliga fall hade kalmanfiltret bettet sig v�ldigt konstigt d�r 
men eftersom modelen inte st�mmer. Nu finns det med b�de i kalman modellen och process 
modellen. Det g�r ocks� att det blir v�ldigt l�tt att starta processen d� det inte
beh�vs n�gon start sekvens f�r att f� upp armen. Om det nu funkar p� verkliga processen....

Saker som beh�ver l�ggas till:

*Vi beh�ver nog ha vilkoren p� u som umin<u<umax ist f�r u<abs(umax).
eftersom vi antagligen inte kan v�nda p� rotations riktningen p� propellerna.

*constraints p� tillst�nden

*L�gga in ett load disturbance tillst�nd f�r integral verkan.

*Justera alla konstnads parametrar f�r en mer robust reglering. 

*Kanske �ka prediktions horizonten? isf m�ste vi tunna ut p� summan 
och bara optimera p� vartannat sample f�r vi �r p� gr�nsen till vad CVXgen 
klarar av nu.




 
