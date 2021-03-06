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

#include <math.h>
#include <stdint.h>
#include <stdlib.h>

#include <unistd.h>

#include <iostream>
#include <set>
#include <stdexcept>

#include <boost/thread.hpp>

#define BLOCK_SIZE	(1024 * 400)

using namespace boost;
using namespace std;

mutex m_mutex_stdout;

void do_something( void );

int main( int argc, char **argv ) {
	uint8_t			*ptr;
	int				i;
	set<thread*>	list;
	set<uint8_t*>	dummy;

	while ( 1 ) {
		try {
			ptr = (uint8_t *) calloc( BLOCK_SIZE, 1 );
			if ( ptr == NULL ) throw runtime_error( "malloc failed" );
			dummy.insert( ptr );
			for ( i = 0; i < BLOCK_SIZE; i++ ) {
				ptr[i] = (uint8_t) i;
			}

			list.insert( new thread( do_something ) );
		} catch ( const std::exception &e ) {
			cout << e.what() << endl;
			break;
		}
		sleep( 1 );
		if ( list.size() > 300 ) break;
	}

	cout << "list has " << list.size() << " elements" << endl;

	for ( set<thread*>::iterator it = list.begin(); it != list.end();
			++it )
	{
		(*it)->join();
		list.erase( it );
	}

	for ( set<uint8_t*>::iterator it = dummy.begin(); it != dummy.end();
			++it )
	{
		free( (*it) );
		dummy.erase( it );
	}

	return EXIT_SUCCESS;
}

void do_something( void ) {
	int				i, j, rand_sec;
	unsigned int	act_sec;
	double			res;

	for ( i = 0; i < 1000; i++ ) {
		for ( j = 0; j < 100; j++ ) {
			res = sin( i ) + cos( i );
		}
		this_thread::yield();
	}

	rand_sec = rand() % 200 + 200;
	act_sec = sleep( rand_sec );

	{
		lock_guard<mutex> g(m_mutex_stdout);
		cout << "thread " << this_thread::get_id() << " should sleep "
				<< rand_sec << " and returned " << act_sec << " ..."
				<< endl;
	}
}

/* vim: set noet sts=0 ts=4 sw=4 sr: */
