/*******************************************************************//**
 *  @file   list.c
 *
 *  @brief  Implementation of a double linked list.
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
 *  of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Foobar. If not, see <http://www.gnu.org/licenses/>.
 **********************************************************************/

#include "list.h"

#include <assert.h>
#include <stddef.h>
#include <stdlib.h>

struct list* list_create( void ) {
    return calloc( 1, sizeof(struct list) );
}

void list_destroy( struct list *list ) {
    assert( list );
}

void list_clear( struct list *list ) {
    assert( list );
}

void list_clear_destroy( struct list *list ) {
    assert( list );

    list_clear( list );
    list_destroy( list );
}

void list_push( struct list *list, void *value ) {
    struct node *node = calloc( 1, sizeof(struct node) );

    /*  check   */
    assert( node );
    if ( node == NULL ) goto leave_list_push;

    node->value = value;

    if ( list->last == NULL ) {
        list->first = node;
        list->last = node;
    } else {
        list->last->next = node;
        node->prev = list->last;
        list->last = node;
    }

    list->count++;

leave_list_push:
    return;
}

void* list_pop( struct list *list ) {
    struct node *node;

    assert( list );

    node = list->last;
    return node != NULL ? list_remove( list, node ) : NULL;
}

void* list_remove( struct list *list, struct node *node ) {
    void *result = NULL;

    assert( list );
    assert( node );
    if ( list->first == NULL || list->last == NULL ) {
        goto leave_list_remove;
    }
    if ( node == NULL ) goto leave_list_remove;

    if ( node == list->first && node == list->last ) {
        list->first = NULL;
        list->last = NULL;
    } else if ( node == list->first ) {
        list->first = node->next;
        /*  TODO    check if this won't mess up the list or if was
         *          already messed up before!   */
        if ( list->first == NULL ) goto leave_list_remove;
        list->first->prev = NULL;
    } else if ( node == list->last ) {
        list->last = node->prev;
        /*  TODO    check if this won't mess up the list or if was
         *          already messed up before!   */
        if ( list->last == NULL ) goto leave_list_remove;
        list->last->next = NULL;
    } else {
        struct node *after = node->next;
        struct node *before = node->prev;
        after->prev = before;
        before->next = after;
    }

    list->count--;
    result = node->value;
    free( node );

leave_list_remove:
    return result;
}
