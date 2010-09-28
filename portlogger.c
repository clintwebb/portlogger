// portlogger.c
// Clinton Webb (webb.clint@gmail.com)


#include <assert.h>
#include <event.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


// global variables 
char *g_filename = NULL;
char *g_listen = NULL;
char *g_target = NULL;
struct event_base *evbase = NULL;
struct event *sigint_event = NULL;


static void usage(void)
{
	printf("\nportlogger.\n\n");
	printf(" -f <filename>\n");
	printf(" -l <listen interface:port>\n");
	printf(" -t <target host:port>\n");
	printf("\n");
	exit(1);
}



static void sigint_handler(evutil_socket_t fd, short what, void *arg)
{
	// stop the listener.
	assert(0);
	
	// close the open sockets which dont have data pending.
	assert(0);
	
	// mark the connections that do have data pending (that they should close when data is finished sending).
	assert(0);
	

	// delete the signal events.
	assert(sigint_event);
	event_free(sigint_event);
	sigint_event = NULL;
}


int main(int argc, char **argv)
{
	int c;
	
///============================================================================
/// Command-line parsing
///============================================================================
	
	// Check the command-line parameters and put the information in global variables.
	while (-1 != (c = getopt(argc, argv, "f:l:t:h"))) {
		switch (c) {
			case 'f':
				assert(g_filename == NULL);
				g_filename = strdup(optarg);
				assert(g_filename);
				break;

			case 'l':
				assert(g_listen == NULL);
				g_listen = strdup(optarg);
				assert(g_listen);
				break;
				
			case 't':
				assert(g_target == NULL);
				g_target = strdup(optarg);
				assert(g_target);
				break;
			
			case 'h':
			default:
				usage();
				break;
		}
	}
	

	// make sure we have enough information to continue.
	if (g_listen == NULL) { 
		fprintf(stderr, "Insufficient parameters; require an interface and port to listen on (-h for help).\n");
		exit(1);
	}

	if (g_target == NULL) { 
		fprintf(stderr, "Insufficient parameters; require an target host and port to connect to (-h for help).\n");
		exit(1);
	}

	// we have the bare minimum of information.  We dont know if the information is valid yet, but it has at least been supplied.


///============================================================================
/// Initialization.
///============================================================================


	// initialise the event system
	assert(evbase == NULL);
	assert(event_get_version_number() == LIBEVENT_VERSION_NUMBER);
	evbase = event_base_new();
	assert(evbase);

	// initialise signal handlers.
	assert(evbase);
	sigint_event = evsignal_new(evbase, SIGINT, sigint_handler, NULL);
	event_add(sigint_event, NULL);
	assert(sigint_event);


///============================================================================
/// Main Event Loop.
///============================================================================
	
	// enter the processing loop.  This function will not return until there is
	// nothing more to do and the service has shutdown.  Therefore everything
	// needs to be setup and running before this point, especially the listener 
	// socket.
	// NOTE: Also, in order for this function to exit, the signal handlers will 
	// also have to be cleared.
	assert(evbase);
	event_base_dispatch(evbase);
	
///============================================================================
/// Shutdown
///============================================================================
	
	// at this point all the sockets have closed, and the listener has been closed.
	assert(evbase);
	event_base_free(evbase);
	evbase = NULL;
	
	// make sure signal handlers have been cleared.
	assert(sigint_event == NULL);

	
	// when we add the logging thread, this will need to flush the log, wait until the thread has re-joined, and close it out.
	assert(0);
	
	
	return(0);
}

