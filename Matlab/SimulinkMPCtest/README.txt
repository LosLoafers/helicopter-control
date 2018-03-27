Varje mapp i denna mapp (SimulinkMPCtest) innehåller olika verisioner av
 implementerade MPC. För att kunna köra dem så är det bäst att bara ha den
 aktuella mappen i sin path. Annar händer konstiga saker som jag inte 
kan förklara...

Den mest kompletta simuleringen är Simulink_MPC_nonlinear_gainsheduling_kalman_itegralact.
Den simulerar på olinjär process och uppdaterar A i varje itteration i MPCn.
For att skatta tillstånden används ett extended kalman filter. 
Brus på mätningarna ger snabbt sämmre reglering. Vi behöver nog 
justera så att det blir lite mer robust. Integratorn är inte heller speciellt bra justerad.

Det finns även en verision som tar hänsyn till att theta har ett stopp. dvs armen stannar 
i en viss vinkel. I vanliga fall hade kalmanfiltret bettet sig väldigt konstigt där 
men eftersom modelen inte stämmer. Nu finns det med både i kalman modellen och process 
modellen. Det gör också att det blir väldigt lätt att starta processen då det inte
behövs någon start sekvens för att få upp armen. Om det nu funkar på verkliga processen....

Saker som behöver läggas till:

*Vi behöver nog ha vilkoren på u som umin<u<umax ist för u<abs(umax).
eftersom vi antagligen inte kan vända på rotations riktningen på propellerna.

*constraints på tillstånden

*Lägga in ett load disturbance tillstånd för integral verkan.

*Justera alla konstnads parametrar för en mer robust reglering. 

*Kanske öka prediktions horizonten? isf måste vi tunna ut på summan 
och bara optimera på vartannat sample för vi är på gränsen till vad CVXgen 
klarar av nu.




 
