/**********
Copyright 1990 Regents of the University of California.  All rights reserved.
Author: 1985 Thomas L. Quarles
**********/

#include "spice.h"
#include <stdio.h>
#include "ifsim.h"
#include "cktdefs.h"
#include "util.h"
#include "sperror.h"
#include "suffix.h"


/*
	Used to try to find a specific instance pointer from as much or little information as
	the front end has available about it.
	Any of the variables may be used to help identifiy the instance except inst,
	which is the primary output variable from this routine.
	Any of the variables may be specified as NULL without affecting the success of CKTfndDev
	except ckt and name which must be specified.

	This function is used to allow the front end to find an instance pointer from whatever information
	it has available about the instance. The pointer pointed to by instPtr will be set to the necessary
	instance pointer if the information is sufficient and the instance is found, otherwise findlnstunce will
	return E - NOTFOUND. The information required to identify the instance is simply the minimum of the
	following needed to uniquely identify it, provided in any sensible combination. The more information
	provided, the more efficiently the instance can be found, with the most important infomation being
	described first. instUid is the unique identifier of the instance to be found and MUST be supplied.
	devZndex is a pointer to the (0 based) index into the device array in the IFsimulator structure of the
	description of this device type. If devIndex points to -1, it will be set to the comct value on return.
	modelPtr is the model pointer for the model this instance is thought to be an instance of. A value of
	NULL indicates the model pointer is not known. modelUid is the unique identifier of the model this
	instance is thought to be an instance of. A value of NULL indicates the model identifier is unknown.
*/
///<param = *ckt> Circuit to operate on </param>
///<param = *type> Type of device </param>
///<param = **inst> Found instance </param>
///<param = name> Name of instance to find </param>
///<param = *modPtr> Pointer to model of instance found </param>
///<param = modName> Name of model if known </param>
int CKTfndDev (GENERIC *Ckt, int *type, GENERIC **fast, IFuid name, GENERIC *modfast, IFuid modname)
{
    register CKTcircuit *ckt=(CKTcircuit *)Ckt;
    register GENinstance *here;
    register GENmodel *mods;

    if((GENinstance **)fast != (GENinstance **)NULL && *(GENinstance **)fast != (GENinstance *)NULL) 
	{
        /* already have  fast, so nothing much to do */
        /* just get & set type */
        if(type) 
			*type = (*((GENinstance**)fast))->GENmodPtr->GENmodType;
        
		return(OK);
    } 
    if(modfast) 
	{
        /* have model, just need device */
        mods = (GENmodel*)modfast;
        for(here = mods->GENinstances ; here != NULL; here = here->GENnextInstance) 
		{
            if (here->GENname == name) 
			{
                if(fast != NULL) 
					*(GENinstance **)fast = here;

                if(type) 
					*type = mods->GENmodType;

                return(OK);
            }
        }
        return(E_NODEV);
    }
    if(*type >=0 && *type < DEVmaxnum) 
	{
        /* have device type, need to find model & device */
        /* look through all models */
        for(mods=(GENmodel *)ckt->CKThead[*type]; mods != NULL ; mods = mods->GENnextModel) 
		{
            /* and all instances */
            if(modname == (char *)NULL || mods->GENmodName == modname) 
			{
                for(here = mods->GENinstances ; here != NULL; here = here->GENnextInstance) 
				{
                    if (here->GENname == name) 
					{
                        if(fast != 0) 
							*(GENinstance **)fast = here;

                        return(OK);
                    }
                }

                if(mods->GENmodName == modname) 
				{
                    return(E_NODEV);
                }
            }
        }
        return(E_NOMOD);
    } 
	else if(*type == -1) 
	{
        /* look through all types (UGH - worst case - take forever) */ 
        for(*type = 0;*type <DEVmaxnum;(*type)++) 
		{
            /* need to find model & device */
            /* look through all models */
            for(mods=(GENmodel *)ckt->CKThead[*type];mods!=NULL; mods = mods->GENnextModel) 
			{
                /* and all instances */
                if(modname == (char *)NULL || mods->GENmodName == modname) 
				{
                    for(here = mods->GENinstances ; here != NULL; here = here->GENnextInstance) 
					{
                        if (here->GENname == name) 
						{
                            if(fast != 0) *(GENinstance **)fast = here;
                            return(OK);
                        }
                    }
                    if(mods->GENmodName == modname) 
					{
                        return(E_NODEV);
                    }
                }
            }
        }
        *type = -1;
        return(E_NODEV);
    } 
	else 
		return(E_BADPARM);
}
