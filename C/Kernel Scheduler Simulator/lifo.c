#include "./shared.h"
#include "./scheduler.h"


/* to implement priority scheduling, you may want to change the following */

PCB_entry      *ready_q; /* global since it is shared among the
                          * various scheduler functions.
                          * 
                          * This is the actual "wait queue" in the simulation
                          * if this was C++ it would be an object
                          */
/*
 * file name lifo.c
 *
 * The functions in this file implement a "last-in -- first-out"
 * scheduling scheme. By any criterion, this is a remarkably
 * *bad* scheduling strategy. But it does provide an example of
 * the functions that need to be implemented to make the simulation
 * work
 *
 * Functions provided and brief descriptions:
 *
 * PCB_entry * schedule_next (void) - returns next process for CPU
 * 
 * int insert_new (PCB_entry * proc) - insert new process into queue
 *
 * void list_q (void) - debugging function lists queue contents
 *
 * int re_insert (PCB_entry * proc, int run_time) - put process back
 *                 into correct queue after a run on the CPU 
 *
 * int init_q (void) - initialise queue(s)
 *
 */

/*
 * Function Schedule_next: Last-in -- first-out
 * 
 * Called by the central simulation system Returns a 
 * pointer to the PCB entry for the "process" that 
 * should be put on the CPU next
 * 
 */
PCB_entry *
schedule_next (void)
{
   PCB_entry *temp;
   /* if ready_q is null, there are no processes in the system */
   if (ready_q == NULL)
     {
	return NULL;
     }
   else
     {
	temp = ready_q;
	/*
	 * for LIFO simply return the first process in the
	 * queue
	 */
	ready_q = ready_q->f_link;
	if (ready_q != NULL)	/* don't try to de-reference a NULL
				 * pointer */
	   ready_q->b_link = NULL;	/* first process in the queue
					 * always has a NULL back
					 * link */
	temp->f_link = NULL;	/* just to be tidy -- set both links
				 * in the PCB */
	/* entry that will be returned to NULL */
	temp->b_link = NULL;
	return temp;
     }
}

/*
 * Function insert_new: Non-preemptive round-robin
 * 
 * Insert a new "process" into the scheduling queue
 * 
 * Accepts a pointer to a PCB entry that will be inserted
 * into the queue returns either OK or NotOK to indicate 
 * success or failure
 * 
 * Since this is LIFO scheduling, the new process is
 * simply slotted in at the front of the queue
 * 
 */
int
insert_new (PCB_entry * proc)
{
   /*
    * PCB_entry *next, *prev;
    * Above is required if code to "walk" the linked list
    * is needed. Not required for LIFO since the insert is
    * always at the head.
    */

   if (ready_q == NULL)
     {				/* no entries in table */
	ready_q = proc;		/* insert at the head of the list */
	proc->b_link = NULL;
	proc->f_link = NULL;
	return OK;
     }
   else
     {
        proc->f_link = ready_q; /* Point new head forward link to old head */
        ready_q->b_link = proc; /* current head of list back link  */
                                /* to new head of list */
        proc->b_link = NULL;    /* New head of list back link NULL */
        ready_q = proc;         /* Set head of list pointer */
	return OK;
     }
#pragma error_messages (off,E_STATEMENT_NOT_REACHED)
   return NotOK; /* this is not really needed, but is here to be defensive */
#pragma error_messages (on,E_STATEMENT_NOT_REACHED)

}

/*
 * Function list_q
 * 
 * essentially a debugging function to list the current
 * contents of the ready queue for the LIFO implimentation
 *
 * Implementation of this function is optional but highly 
 * recommended
 */

void
list_q (void)
{
   PCB_entry *next;

   next = ready_q;

   fprintf (stderr, "\n current state of the ready queue\n");

   next = ready_q;
   while (next != NULL)
     {				/* traverse to the end of the list */
	fprintf (stderr, "%d\t", next->pid);
	next = next->f_link;
     }
   fprintf (stderr, "\n\n");
}


/*
 * Function re_insert: LIFO
 * 
 * a function to insert a process back into the queue
 * following a run on the CPU. Depending on the
 * scheduling algorithm chosen this would need to
 * do a lot more. In a priority algorithm with boost
 * and reduction, it would need to look at the
 * percentage of the quantum that the process used
 * and determine if a change to the priority was
 * required. Also, in implementing a mulitlevel
 * priority scheme, a variation of the ready_q
 * pointer would be required. The simplest method
 * would be an array of pointers with one element
 * for each priority level.
 *
 * Not that, in this case it is identical to the
 * insert_new code
 */
int
re_insert (PCB_entry * proc, int run_time)
{
   /*
    * PCB_entry *next, *prev;
    * Above is required if code to "walk" the linked list
    * is needed. Not required for LIFO since the insert is
    * always at the head.
    */
   /*
    * With a multi-level queue scheme, you would need code
    * to determins which queue to insert the process
    * Relatively minor effort would be required to change
    * to multi-level queues if this is managed as an
    * array of pointers and one pointer per queue.
    */
   if (ready_q == NULL)
     {				/* no entries in table */
	ready_q = proc;
	proc->b_link = NULL;
	proc->f_link = NULL;
	return OK;
     }
   else
     {
        proc->f_link = ready_q; /* Point new head forward link to old head */
        ready_q->b_link = proc; /* current head of list back link  */
                                /* to new head of list */
        proc->b_link = NULL;    /* New head of list back link NULL */
        ready_q = proc;         /* Set head of list pointer */
	return OK;
     }
#pragma error_messages (off,E_STATEMENT_NOT_REACHED)
   return NotOK; /* this is not really needed, but is here to be defensive */
#pragma error_messages (on,E_STATEMENT_NOT_REACHED)
}


/*
 * Function init_q: LIFO
 * 
 * Initialises the ready queue
 * 
 * Written as a function so that, if the ready_q
 * becomes an array of pointers, the initialisation
 * can be changed without re-building the main part
 * of the simulator
 */

int
init_q (void)
{
   ready_q = NULL;
   return OK;
}



/*
 * function end_run () 
 * Insert code to do any end of processing tasks for the
 * functions written by the student
 */
int end_run(void)
{

   fprintf(stderr, "This run had %d concurrent processes", Get_num_concurrent());
   return 0;
}
