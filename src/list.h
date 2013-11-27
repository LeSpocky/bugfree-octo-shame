/*******************************************************************//**
 *  @file   list.h
 *
 *  @brief  declarations for a double linked list containing pthread_t
 *          as values
 *
 *  @author Alexander Dahl <post@lespocky.de>
 *
 *  @copyright  2013 Alexander Dahl
 *
 *  This file is part of bugfree-octo-shame.
 *
 *  _bugfree-octo-shame_ is free software: you can redistribute it
 *  and/or modify it under the terms of the GNU General Public License
 *  as published by the Free Software Foundation, either version 3 of
 *  the License, or (at your option) any later version.
 *
 *  _bugfree-octo-shame_ is distributed in the hope that it will be
 *  useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 *  of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 *  General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Foobar. If not, see <http://www.gnu.org/licenses/>.
 **********************************************************************/

#ifndef _LIST_H_
#define _LIST_H_

#include <pthread.h>

#define list_count(A)   ((A)->count)
#define list_first(A)   ((A)->first != NULL ? (A)->first->value : NULL)
#define list_last(A)    ((A)->last != NULL ? (A)->last->value : NULL)

struct node {
    struct node *prev;
    struct node *next;
    pthread_t   value;
};

struct list {
    int         count;
    struct node *first;
    struct node *last;
};

struct list* list_create( void );

/**
 *  Free list elements itself and free list then.
 *
 *  @attention  You have to ensure to free the values inside before!
 *
 *  @param[in]  *list   pointer to list
 */
void list_destroy( struct list *list );

void list_push( struct list *list, pthread_t value );
pthread_t list_pop( struct list *list );

pthread_t list_remove( struct list *list, struct node *node );

#endif /* _LIST_H_ */
