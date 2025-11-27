# Technical expectations
 ###    Spatial accuracy and granularity. What is the precision you can create a dot at a given coordinate? What is the minimum size of this dot?
 La précision est la ganularité de l'affichage sont intimement liée aux demandes calculatoire du programme d'affichage est la vitesse du moteur. Un programme plus lent diminue la fréquence de rafraichissement du buffer d'affichage et donc des LED, en contrepartie un moteur plus lent laisse plus de temps pour l'affichage d'une position donné. Pour un affichage d'une image, la précision peut aller jusqu'à 2°. Pour un programme affichant seulement un point singulier, il est possible de descendre à une précision de <INSERER PRECISION ICI>

 ###    Temporal accuracy and granularity. What is the LEDs refreshing frequency ? What is the granularity you can reach to measure the boards's rotation duration?

 ###    What is the board's rotating speed? Quantify its stability

 ###    Time estimation accuracy. If you start with a perfect time, how much will it drift after 6 month of use?

 ###  Code efficiency. What is the cost (in time and in number of cycles) of your interrupts? Of a floating multiplication and division? Of an integer multiplication and division?

 ###  How much memory do you use? How much is left? What are different types of memory available and what are they used for?
