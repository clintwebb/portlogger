// portlogger.c
// Clinton Webb (webb.clint@gmail.com)


#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


// global variables 
char *g_filename = NULL;
char *g_listen = NULL;
char *g_target = NULL;


static void usage(void)
{
	printf("\nportlogger.\n\n");
	printf(" -f <filename>\n");
	printf(" -l <listen interface:port>\n");
	printf(" -t <target host:port>\n");
	printf("\n");
	exit(1);
}
	


int main(int argc, char **argv)
{
	int c;
	
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



	return(0);
}

