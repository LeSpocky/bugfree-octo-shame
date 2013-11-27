/*******************************************************************//**
 *	@file	test_remove.c
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

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include <pthread.h>

#include "list.h"

int main( int argc, char **argv ) {
	pthread_t	val;
	struct list *list = NULL;

	/*	remove first element	*/
	list = list_create();
	if ( list == NULL ) {
		(void) fputs( "Failed to create list!\n", stderr );
		return EXIT_FAILURE;
	}

	list_push( list, 1 );
	list_push( list, 2 );
	list_push( list, 3 );

	val = list_remove( list, list->first );
	if ( val != 1 ) {
		(void) fputs( "Wrong removed element!\n", stderr );
		return EXIT_FAILURE;
	}
	if ( list_count( list ) != 2 ) {
		(void) fputs( "Wrong count after remove!\n", stderr );
		return EXIT_FAILURE;
	}
	if ( list_first( list ) != 2 ) {
		(void) fputs( "Wrong first after remove!\n", stderr );
		return EXIT_FAILURE;
	}
	if ( list_last( list ) != 3 ) {
		(void) fputs( "Wrong last after remove!\n", stderr );
		return EXIT_FAILURE;
	}

	list_destroy( list );

	/*	remove middle element	*/
	list = list_create();
	if ( list == NULL ) {
		(void) fputs( "Failed to create list!\n", stderr );
		return EXIT_FAILURE;
	}

	list_push( list, 1 );
	list_push( list, 2 );
	list_push( list, 3 );

	val = list_remove( list, list->first->next );
	if ( val != 2 ) {
		(void) fputs( "Wrong removed element!\n", stderr );
		return EXIT_FAILURE;
	}
	if ( list_count( list ) != 2 ) {
		(void) fputs( "Wrong count after remove!\n", stderr );
		return EXIT_FAILURE;
	}
	if ( list_first( list ) != 1 ) {
		(void) fputs( "Wrong first after remove!\n", stderr );
		return EXIT_FAILURE;
	}
	if ( list_last( list ) != 3 ) {
		(void) fputs( "Wrong last after remove!\n", stderr );
		return EXIT_FAILURE;
	}

	list_destroy( list );

	/*	remove last element	*/
	list = list_create();
	if ( list == NULL ) {
		(void) fputs( "Failed to create list!\n", stderr );
		return EXIT_FAILURE;
	}

	list_push( list, 1 );
	list_push( list, 2 );
	list_push( list, 3 );

	val = list_remove( list, list->last );
	if ( val != 3 ) {
		(void) fputs( "Wrong removed element!\n", stderr );
		return EXIT_FAILURE;
	}
	if ( list_count( list ) != 2 ) {
		(void) fputs( "Wrong count after remove!\n", stderr );
		return EXIT_FAILURE;
	}
	if ( list_first( list ) != 1 ) {
		(void) fputs( "Wrong first after remove!\n", stderr );
		return EXIT_FAILURE;
	}
	if ( list_last( list ) != 2 ) {
		(void) fputs( "Wrong last after remove!\n", stderr );
		return EXIT_FAILURE;
	}

	list_destroy( list );

	return EXIT_SUCCESS;
}

/* vim: set noet sts=0 ts=4 sw=4 sr: */
