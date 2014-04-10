/*******************************************************************//**
 *	@file	main.cpp
 *
 *	@brief	bugfree-octo-shame-boost aka how much boost threads we can create …
 *
 *	@details	We want to test how much threads a Linux system can
 *				create and keep running. For this we spawn threads and
 *				let the main program watch the action.
 *
 *	@author	Alexander Dahl <post@lespocky.de>
 *
 *	@copyright	2014 Alexander Dahl
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

#include <stdlib.h>

#include <unistd.h>

void *do_something( void *arg );

int main( int argc, char **argv ) {

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
