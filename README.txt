Struttura progetto 
le msg queue sono semplici code bloccanti come nei semafori organizzate tramite id.
i messaggi vengono inseriti nelle queue quindi vanno implementat get e put, come nei semafori 
devo creare open close e unlink 

Test 
i test creeranno più code che scambiano messaggi di un qualche tipo


Diario tesi 
giorno 1 :
implementato il mqueue.c e .h nei quali ho definito la struttura della mqueue e le funzioni di alloc free e init, aggiunte le sys call al.h.
va crato il mq descriptor.h e aggiornato il mqueue.h aggiungendo il byid.

giorno 2 :
aggiornati tutti i .h e aggiunte le sys call e cose di questo tipo per poter procedere con la programmazione delle funzioni

giorno 3 : 
debug di tutto e compila, ho modificato mqueue.c e ho sistemato tutte quanti i problemi relativi a disastros.c e modificato gli errori nelle constants.

giorno 4 : 

finito il debug e creazione mq close e relativo debug 

giorno 5 : 
modificate varie cose controllare il make perchè non compila 

