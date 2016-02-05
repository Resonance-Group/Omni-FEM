/**********
Copyright 1990 Regents of the University of California.  All rights reserved.
Author: 1985 Thomas L. Quarles
**********/

#ifndef INP
#define INP

    /* structure declarations used by either/both input package */

#include "ifsim.h"
#include "gendefs.h"
#include "inpptree.h"

/*
	This structure is used to contain data on all names defined 
	in the front end which are not equation names.
	The actual data structure is a hash table made up of linked
	lists of INPtab structure with matching hash values.
*/
struct INPtab {
	/*
		This is the character string which defines the name stored in this instance of the INPtab.
	*/
    char *t_ent;



	/*
		This contains a pointer to the next entry in the hash chain
	*/
    struct INPtab *t_next;
};




/*
	This structure is almost identcal to the INPtab structure, but us used for names
	corresponding to equations in the circuit such as node name or current equation
	names.
	The basic structure is the same, with a hash table of linked lists.
	The only difference is the data placed in the table and the presence of 1 additional 
	field in the structure.
*/
struct INPnTab {
	/*
	This element contains the pointer to the simulator's internal structure corresponding to this name
	*/
	GENERIC* t_node;



    char *t_ent;
	struct INPnTab *t_next;
};



/*
	This is the overall input package data structure.
	1 instance of this structure is allocated for each circuit to be parsed and
	passed to every input package routine to help it in parsing.
	
	Most of the fields of this structure are of the form defXmod.
	Each of these fileds points to a SPICE3 internal model structure whcih represents
	the default model used for the device of type X
*/
typedef struct sINPtables{
	/*
		INPsymtab is the hash table for non-equation names.
		This is an allocated array of pointers to the beginning of hash chains.
		The allocated array of pointers contains INPsize pointers.
	*/
    struct INPtab **INPsymtab;
	int INPsize;



	/*
		INPtermsymtab is the hash table for equation or terminal names.
		This is the allocated array of pointer to the beginning of INPtermsize hash chains
	*/
    struct INPnTab **INPtermsymtab;
    int INPtermsize;



    GENERIC *defAmod; // unused
    GENERIC *defBmod; // arbitrary source
    GENERIC *defCmod; // capacitor
    GENERIC *defDmod; // diode
    GENERIC *defEmod; // vcvs
    GENERIC *defFmod; // cccs
    GENERIC *defGmod; // vccs
    GENERIC *defHmod; // ccvs
    GENERIC *defImod; // independent current source
    GENERIC *defJmod; // JFET
    GENERIC *defKmod; // mutual inductor
    GENERIC *defLmod; // inductor
    GENERIC *defMmod; // MOSFET
    GENERIC *defNmod; // unused
    GENERIC *defOmod; // unused
    GENERIC *defPmod; // unused
    GENERIC *defQmod; // BJT
    GENERIC *defRmod; // resistor
    GENERIC *defSmod; // Voltage controlled switch
    GENERIC *defTmod; // transmission Line
    GENERIC *defUmod; // uniform RC line
    GENERIC *defVmod; // indepedent voltage source
    GENERIC *defWmod; // current controlled switch
    GENERIC *defYmod; // unused
    GENERIC *defZmod; // MESFET
} INPtables;



/*
	The card structure is used to hold the image of an input line and all data associated with it during parsing.
	Lines are read and broken into physical and logical lines.
	Physical lines are delimited by newine characters at their end.
	Logical lines are what results from conceternating continuation lines onto the lines they continue.
*/
typedef struct card{
	/*
		The line number associated with this card image.
		It is the line number associated with the physical line that the first character of the logical line came from. test
	*/
    int linenum;



	/*
		The logical text of the line.
		If this is a single logical line that was read as a signle physical line, this will be the exact line.
		If the logical line consists of multiple physical lines marked with continuation characters in column one, this
		will be the logical line after the continuation lines have been concatenated onto the lines they continue with
		the continuation character replaced by a single space.
	*/
    char *line;



	/*
		This is the text of any error messages that are associated with this logical line
	*/
    char *error;



	/*
		A pointer to the next card structure representing the next logical line in the input
	*/
    struct card *nextcard;



	/*
		If this pointer is not NULL, then this logical line is actually made up of several physical lines.
		This pointer will point to a linked list of the physical lines that make up the logical line.
		Each element of the linked list is a card structure as well, but in that list the line field is always a physical line, never a logical line, 
		nextcard points to the next physical line comprising the logical line and the actualLine pointer is always NULL.
	*/
    struct card *actualLine;
} card;



/*
	The INPmodel structrue is used by the input parser package to hold information about a model 
	which occurs in the input. During pass one pointers to the lines containing ".MODEL" cards are saved in a linked list of these structure.
	During pass two of the parser, these lines are actually parsed as needed and pointers to the models created are stored in structure for 
	fast access.
	Currently, the head of the list of INPmodel structures is stored in a global variable, thus limiting the parser
	to having one circuit in progress at a time. This restriction should be removed in a future version of the parser.
*/
typedef struct sINPmodel{
    IFuid INPmodName;   /* uid of model */
    int INPmodType;     /* type index of device type */
    struct sINPmodel *INPnextModel;  /* link to next model */
    int INPmodUsed;     /* flag to indicate it has already been used */
    card *INPmodLine;   /* pointer to line describing model */
    GENERIC *INPmodfast;   /* high speed pointer to model for access */
} INPmodel;

/* listing types - used for debug listings */
#define LOGICAL 1
#define PHYSICAL 2

int IFnewUid(GENERIC*, IFuid*, IFuid, char*, int, GENERIC**);
int IFdelUid(GENERIC*, IFuid, int);
int INPaName(char*, IFvalue*, GENERIC*, int*, char*, GENERIC**, IFsimulator*, int*, IFvalue*);
int INPapName(GENERIC*, int, GENERIC*, char*, IFvalue*);
void INPcaseFix(char*);
char * INPdevParse(char**, GENERIC*, int, GENERIC*, double*, int*, INPtables*);
char *INPdomodel(GENERIC *,card*, INPtables*);
void INPdoOpts(GENERIC*, GENERIC*, card*, INPtables*);
char *INPerrCat(char *, char *);
char *INPerror(int);
double INPevaluate(char**, int*, int);
char * INPfindLev(char*, int*);
char * INPgetMod(GENERIC*, char*, INPmodel**, INPtables*);
int INPgetTok(char**, char**, int);
void INPgetTree(char**, INPparseTree**, GENERIC*, INPtables*);
IFvalue * INPgetValue(GENERIC*, char**, int, INPtables*);
int INPgndInsert(GENERIC*, char**, INPtables*, GENERIC**);
int INPinsert(char**, INPtables*);
int INPremove(char*, INPtables*);
int INPlookMod(char*);
int INPmakeMod(char*, int, card*);
char *INPmkTemp(char*);
void INPpas1(GENERIC*, card*, INPtables*);
void INPpas2(GENERIC*, card*, INPtables*, GENERIC *);
int INPpName(char*, IFvalue*, GENERIC*, int, GENERIC*);
int INPtermInsert(GENERIC*, char**, INPtables*, GENERIC**);
int INPmkTerm(GENERIC*, char**, INPtables*, GENERIC**);
int INPtypelook(char*);
void INP2B(GENERIC*, INPtables*, card*);
void INP2C(GENERIC*, INPtables*, card*);
void INP2D(GENERIC*, INPtables*, card*);
void INP2E(GENERIC*, INPtables*, card*);
void INP2F(GENERIC*, INPtables*, card*);
void INP2G(GENERIC*, INPtables*, card*);
void INP2H(GENERIC*, INPtables*, card*);
void INP2I(GENERIC*, INPtables*, card*);
void INP2J(GENERIC*, INPtables*, card*);
void INP2K(GENERIC*, INPtables*, card*);
void INP2L(GENERIC*, INPtables*, card*);
void INP2M(GENERIC*, INPtables*, card*);
void INP2O(GENERIC*, INPtables*, card*);
void INP2Q(GENERIC*, INPtables*, card*, GENERIC*);
void INP2R(GENERIC*, INPtables*, card*);
void INP2S(GENERIC*, INPtables*, card*);
void INP2T(GENERIC*, INPtables*, card*);
void INP2U(GENERIC*, INPtables*, card*);
void INP2V(GENERIC*, INPtables*, card*);
void INP2W(GENERIC*, INPtables*, card*);
void INP2Z(GENERIC*, INPtables*, card*);
int INP2dot(GENERIC*, INPtables*, card*, GENERIC*, GENERIC*);
INPtables *INPtabInit(int);
void INPkillMods(void);
void INPtabEnd(INPtables *);


#endif /*INP*/
