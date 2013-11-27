/*******************************************************************//**
 *	@file	main.c
 *
 *	@brief	bugfree-octo-shame aka testing a double linked list and how
 *			much threads we can create …
 *
 *	@details	We want to test how much threads a Linux system can
 *				create and keep running. For this we spawn threads and
 *				let the main program watch the action. The information
 *				about the threads is stored in a double linked list.
 *
 *	@author	Alexander Dahl <post@lespocky.de>
 *
 *	@copyright	2013 Alexander Dahl
 *
 *	This file is part of bugfree-octo-shame.
 *
 *	_bugfree-octo-shame_ is free software: you can redistribute it
 *	and/or modify it under the terms of the GNU General Public License
 *	as published by the Free Software Foundation, either version 3 of
 *	the License, or (at your option) any later version.
 *
 *	_bugfree-octo-shame_ is distributed in the hope that it will be
 *	useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 *	of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 *	General Public License for more details.
 *
 *	You should have received a copy of the GNU General Public License
 *	along with _bugfree-octo-shame_. If not, see
 *	<http://www.gnu.org/licenses/>.
 **********************************************************************/

#include <errno.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <pthread.h>
#include <unistd.h>

#include "list.h"

void *do_something( void *arg );

int main( int argc, char **argv ) {
	bool		run = true;
	int			err, max_thread_count = 0, prev_thread_count = 0;
	void		*retval;
	pthread_t	id;
	struct list	*list;
	struct node	*cur, *node;

	list = list_create();
	if ( list == NULL ) {
		(void) fputs( "Failed to create list!\n", stderr );
		return EXIT_FAILURE;
	}

	srand( time( NULL ) );

	while ( run ) {
		/*	create a new thread and put it into our list	*/
		err = pthread_create( &id, NULL, do_something, NULL );
		if ( err == EAGAIN ) {
//			(void) fprintf( stderr,
//					"Insufficient resources for creating new thread!\n" );
		} else if ( err ) {
			(void) fprintf( stderr, "Error (%i) creating thread!\n", err );
			break;
		} else {
			list_push( list, id );
			(void) printf( "Created thread with id %u ...\n", id );
		}

		/*	go through our list and search for joinable threads	*/
		for ( cur = node = list->first; node; cur = node = node->next ) {
			err = pthread_tryjoin_np( cur->value, &retval );
			if ( err == EBUSY ) {
				/*	thread still running, proceed to next	*/
//				(void) printf(
//						"Thread %u still running, proceeding to next ...\n",
//						cur->value );
				continue;
			} else if ( err ) {
				/*	abort if something goes wrong	*/
				(void) fprintf( stderr,
						"Error (%i) joining thread %u!\n",
						err, cur->value );
				run = false;
				break;
			} else {
				/*	remove from list	*/
				(void) printf(
						"Joined thread %u and removed from list ...\n",
						cur->value );
				(void) list_remove( list, cur );
			}
		}

		/*	print statistics	*/
		if ( prev_thread_count != list_count( list ) ) {
			(void) printf( "Threads running: %i\n", list_count( list ) );
			prev_thread_count = list_count( list );
			if ( list_count( list ) > max_thread_count ) {
				max_thread_count = list_count( list );
			}
		}
	}

	/*	join remaining threads	*/
	(void) printf( "Joining %i remaining threads ...\n",
			list_count( list ) );
	while ( id = list_pop( list ) ) {
		err = pthread_join( id, &retval );
		if ( err ) {
			(void) fprintf( stderr, "Error (%i) joining thread %u!\n",
					err, id );
		} else {
			(void) printf( "Joined thread %u ...\n", id );
		}
	}

	list_destroy( list );

	return EXIT_SUCCESS;
}

void *do_something( void *arg ) {
	int				rand_sec;
	unsigned int	act_sec;

	rand_sec = rand() % 30 + 30;
	act_sec = sleep( rand_sec );
//	(void) printf( "thread %u should sleep %i and returned %u ...\n",
//			pthread_self(), rand_sec, act_sec );

	return NULL;
}

/* vim: set noet sts=0 ts=4 sw=4 sr: */
