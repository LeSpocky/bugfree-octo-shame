/*******************************************************************//**
 *	@file	test_push_pop.c
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
	struct list	*list = NULL;

	list = list_create();
	if ( list == NULL ) {
		(void) fputs( "Failed to create list!\n", stderr );
		return EXIT_FAILURE;
	}

	list_push( list, 1 );
	if ( list_last( list ) != 1 ) {
		(void) fputs( "Wrong last value!\n", stderr );
		return EXIT_FAILURE;
	}

	list_push( list, 2 );
	if ( list_last( list ) != 2 ) {
		(void) fputs( "Wrong last value!\n", stderr );
		return EXIT_FAILURE;
	}

	list_push( list, 3 );
	if ( list_last( list ) != 3 ) {
		(void) fputs( "Wrong last value!\n", stderr );
		return EXIT_FAILURE;
	}

	if ( list_count( list ) != 3 ) {
		(void) fputs( "Wrong count on push!\n", stderr );
		return EXIT_FAILURE;
	}

	val = list_pop( list );
	if ( val != 3 ) {
		(void) fputs( "Wrong value on pop!\n", stderr );
		return EXIT_FAILURE;
	}

	val = list_pop( list );
	if ( val != 2 ) {
		(void) fputs( "Wrong value on pop!\n", stderr );
		return EXIT_FAILURE;
	}

	val = list_pop( list );
	if ( val != 1 ) {
		(void) fputs( "Wrong value on pop!\n", stderr );
		return EXIT_FAILURE;
	}

	if ( list_count( list ) != 0 ) {
		(void) fputs( "Wrong count after pop!\n", stderr );
		return EXIT_FAILURE;
	}

	list_destroy( list );

	return EXIT_SUCCESS;
}

/* vim: set noet sts=0 ts=4 sw=4 sr: */
