/**********
Copyright 1990 Regents of the University of California.  All rights reserved.
Author: 1985 Wayne A. Christopher, U. C. Berkeley CAD Group
**********/

/*
 * Stuff for the terminal and node symbol tables.
 * Defined: INPtabInit, INPinsert, INPtermInsert, INPtabEnd
 */

#include "spice.h"
#include <stdio.h> /* Take this out soon. */
#include "ifsim.h"
#include "iferrmsg.h"
#include "inpdefs.h"
#include "cpstd.h"
#include "fteext.h"
#include "util.h"
#include "suffix.h"

#ifdef __STDC__
static int hash(char *, int);
#else /* stdc */
static int hash();
#endif /* stdc */
static int local_remove();



/*
	Allocates and initializes the symbol tables.
	numlines is an approximation to the size of the input and is used to pre-allocate most of the table
*/
///<param name = "*numlines"> Approximate number of input lines </param>
INPtables *INPtabInit(int numlines)
{
	INPtables *tab;

	tab = (INPtables *)tmalloc(sizeof(INPtables));
	tab->INPsymtab = (struct INPtab **) tmalloc((numlines / 4 + 1) * sizeof(struct INPtab *));
	ZERO(tab->INPsymtab, (numlines / 4 + 1) * sizeof(struct INPtab *));
	tab->INPtermsymtab = (struct INPnTab **) tmalloc(numlines * sizeof(struct INPnTab *));
	ZERO(tab->INPtermsymtab, numlines * sizeof(struct INPnTab *));
	tab->INPsize = numlines / 4 + 1;
	tab->INPtermsize = numlines;
	return(tab);
}



/*
	Is used to place the name of a node or a current equation into the symbol table.
	The nmae is first checked for uniqueness, and if it is not unique, is discarded and the existing node's
	information is returned.
	If the name is new, then a call is made to the simulator's newNode function
	with the resulting node pointer saved in the symbol table and returned to the caller
*/
///<param name = "*ckt"> The current circuit </param>
///<param name = "**token"> The name to insert </param>
///<param name = "*tab"> The current symbol table </param>
///<param name = "**node"> The node structure to return </param>
int INPtermInsert(GENERIC *ckt, char **token, INPtables *tab, GENERIC**node)
{
	int key;
	int error;
	struct INPnTab *t;

	key = hash(*token, tab->INPtermsize);
	for (t = tab->INPtermsymtab[key]; t; t = t->t_next)
	{
		if (!strcmp(*token, t->t_ent))
		{
			FREE(*token);
			*token = t->t_ent;

			if (node)
				*node = t->t_node;

			return(E_EXISTS);
		}
	}
	t = (struct INPnTab *) tmalloc(sizeof(struct INPnTab));

	if (t == (struct INPnTab*)NULL)
		return(E_NOMEM);

	ZERO(t, struct INPnTab);
	error = (*(ft_sim->newNode))(ckt, &t->t_node, *token);

	if (error)
		return(error);

	if (node)
		*node = t->t_node;

	t->t_ent = *token;
	t->t_next = tab->INPtermsymtab[key];
	tab->INPtermsymtab[key] = t;
	return(OK);
}



/*
	Almost identical to INPtermInsert but the node passed in is an existing node
	pointer which should be used instead of calling the newnode function to create a node pointer
*/
///<param name = "*ckt"> The current circuit </param>
///<param name = "**token"> Token representing node name </param>
///<param name = "*tab"> Current symbol table </param>
///<param name = "**node"> Node structure to associate with name </param>
int INPmkTerm(GENERIC *ckt, char **token, INPtables *tab, GENERIC**node)
{
	int key;
	struct INPnTab *t;

	key = hash(*token, tab->INPtermsize);
	for (t = tab->INPtermsymtab[key]; t; t = t->t_next)
	{
		if (!strcmp(*token, t->t_ent))
		{
			FREE(*token);
			*token = t->t_ent;

			if (node)
				*node = t->t_node;

			return(E_EXISTS);
		}
	}
	t = (struct INPnTab *) tmalloc(sizeof(struct INPnTab));

	if (t == (struct INPnTab*)NULL)
		return(E_NOMEM);

	ZERO(t, struct INPnTab);
	t->t_node = *node;
	t->t_ent = *token;
	t->t_next = tab->INPtermsymtab[key];
	tab->INPtermsymtab[key] = t;
	return(OK);
}



/*
	A special case of INPtermInsert used only when creating the ground node of the circuit.
*/
///<param name = "*ckt"> Current circuit </param>
///<param name = "**token"> Token representating ground node </param>
///<param name = "*tab"> Current symbol table </param>
///<param name = "**node"> Returned node structure for ground node </param>
int INPgndInsert(GENERIC *ckt, char **token, INPtables *tab, GENERIC**node)
{
	int key;
	int error;
	struct INPnTab *t;

	key = hash(*token, tab->INPtermsize);
	for (t = tab->INPtermsymtab[key]; t; t = t->t_next)
	{
		if (!strcmp(*token, t->t_ent))
		{
			FREE(*token);
			*token = t->t_ent;
			if (node) *node = t->t_node;
			return(E_EXISTS);
		}
	}
	t = (struct INPnTab *) tmalloc(sizeof(struct INPnTab));

	if (t == (struct INPnTab*)NULL)
		return(E_NOMEM);

	ZERO(t, struct INPnTab);

	error = (*(ft_sim->groundNode))(ckt, &t->t_node, *token);

	if (error)
		return(error);

	if (node)
		*node = t->t_node;

	t->t_ent = *token;
	t->t_next = tab->INPtermsymtab[key];
	tab->INPtermsymtab[key] = t;
	return(OK);
}



/*
	Inserts a single token into the general symbol table
*/
///<param name = "**token"> Token to put in table </param>
///<param name = "*tab"> Current table pointer </param>
int INPinsert(char **token, INPtables *tab)
{
	struct INPtab *t;
	int key;

	key = hash(*token, tab->INPsize);

	for (t = tab->INPsymtab[key]; t; t = t->t_next)
	{
		if (!strcmp(*token, t->t_ent))
		{
			FREE(*token);
			*token = t->t_ent;
			return(E_EXISTS);
		}
	}

	t = (struct INPtab *) tmalloc(sizeof(struct INPtab));
	if (t == (struct INPtab*)NULL)
		return(E_NOMEM);

	ZERO(t, struct INPtab);
	t->t_ent = *token;
	t->t_next = tab->INPsymtab[key];
	tab->INPsymtab[key] = t;
	return(OK);
}



/* remove 'token' from the symbol table */
int INPremove(char *token, INPtables *tab)
{
	struct INPtab *t, **prevp;
	int key;

	key = hash(token, tab->INPsize);
	prevp = &tab->INPsymtab[key];

	for (t = *prevp; t && token != t->t_ent; t = t->t_next)
		prevp = &t->t_next;
	
	if (!t)
		return OK;

	*prevp = t->t_next;
	tfree(t->t_ent);
	tfree(t);

	return OK;
}



/* remove 'token' from the symbol table */
int INPremTerm(char *token, INPtables *tab)
{
	struct INPnTab *t, **prevp;
	int key;

	key = hash(token, tab->INPtermsize);
	prevp = &tab->INPtermsymtab[key];

	for (t = *prevp; t && token != t->t_ent; t = t->t_next)
		prevp = &t->t_next;

	if (!t)
		return OK;

	*prevp = t->t_next;
	tfree(t->t_ent);
	tfree(t);

	return OK;
}



/* Free the space used by the symbol tables. */
void INPtabEnd(INPtables *tab)
{
	struct INPtab *t, *lt;
	struct INPnTab *n, *ln;
	int i;

	for (i = 0; i < tab->INPsize; i++)
	{
		for (t = tab->INPsymtab[i]; t; t = lt) 
		{
			lt = t->t_next;
			FREE(t);    /* But not t_ent ! */
		}
	}
		
	FREE(tab->INPsymtab);

	for (i = 0; i < tab->INPtermsize; i++)
	{
		for (n = tab->INPtermsymtab[i]; n; n = ln)
		{
			ln = n->t_next;
			FREE(n);    /* But not t_ent ! */
		}
	}
		
	FREE(tab->INPtermsymtab);
	FREE(tab);
	return;
}



/*
	Computes a hash function in the range 0 to tsize from the given name to make the symbol
	table operation more efficient
*/
///<param name = "*name"> Name to hash </param>
///<param name = "tsize"> Size of hash table </param>
static int hash(char *name, int tsize)
{
	char *s;
	register int i = 0;

	for (s = name; *s; s++)
		i += *s;

	return (i % tsize);
}

