// FemmeDocCore.cpp : implementation of the CFemmeDocCore class
//

 
#include "stdafx.h"
#include <Windows.h>
#include <math.h>
#include <string.h>]
#include <atlstr.h>
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include "belasolv.h"
#include "belasolvDlg.h"
#include "mesh.h"
#include "spars.h"
#include "FemmeDocCore.h"


#pragma region Constructor/Destructor

CFemmeDocCore::CFemmeDocCore()
{
	TheView = NULL;
	Precision = NULL;
	LengthUnits = NULL;
	ProblemType = NULL;
	Coords = NULL;
	BandWidth = NULL;
	NumNodes = NULL;
	NumEls = NULL;
	NumBlockProps = NULL;
	NumPBCs = NULL;
	NumLineProps = NULL;
	NumPointProps = NULL;
	NumCircProps = NULL;
	NumBlockLabels = NULL;

	meshnode = NULL;
	meshele = NULL;
	blockproplist = NULL;
	lineproplist = NULL;
	nodeproplist = NULL;
	circproplist = NULL;
	labellist = NULL;
	pbclist = NULL;
	PathName = NULL;

	extRo = extRi = extZo = NULL;
}



CFemmeDocCore::~CFemmeDocCore()
{
	CleanUp();
}

#pragma endregion



#pragma region CFemmeDocCore Methods

///<summary> This function clears all of the memory. It performs memory managment </summary>
void CFemmeDocCore::CleanUp()
{
	if (meshnode != NULL)
		free(meshnode);

	if (meshele != NULL)
		free(meshele);

	if (blockproplist != NULL)
		free(blockproplist);

	if (lineproplist != NULL)
		free(lineproplist);

	if (nodeproplist != NULL)
		free(nodeproplist);

	if (circproplist != NULL)
		free(circproplist);

	if (labellist != NULL)
		free(labellist);

	if (pbclist != NULL)
		free(pbclist);
}



char* StripKey(char *c)
{
	char *d;
	int i, k;

	// Gets the length of the string c
	k = (int)strlen(c);

	for (i = 0; i < k; i++) 
	{
		if (c[i] == '=') 
		{
			d = c + i + 1;
			return d;
		}
	}

	return c + k;
}



/// <summary> This function will open a .fee file specificed in path name property </summary>
/// <returns> Returns true if the process succeeds </returns>
BOOL CFemmeDocCore::OnOpenDocument()
{
	FILE *fp;
	int k;
	char fileName[1024], q[1024], charaterStream[1024];
	char *v;
	CPointProp	  PProp;
	CBoundaryProp BProp;
	CMaterialProp MProp;
	CCircuit	  CProp;
	CBlockLabel   blk;

	if (sizeof(PathName) <= 1024)// Prevents a path name of greater then 1024 from being copied 
	{
		sprintf(fileName, "%s.fee", PathName);// This copies Pathname into the char array filename with formatting
		if ((fp = fopen(fileName, "rt")) == NULL)// fopen opens the file name stored in filename and opens it with read permissions
		{
			/* fopen will return a boolean if it succeeds or fails */
			fprintf(stderr, "Couldn't read from specified .fee file\n");
			return FALSE;
		}
	}
	else
	{
		fprintf(stderr, "Path Name too long\n");
		return FALSE;
	}


	// define some defaults
	Precision = 1.e-08;
	Depth = -1;
	ProblemType = 0;
	Coords = 0;
	NumPointProps = 0;
	NumLineProps = 0;
	NumBlockProps = 0;
	NumCircProps = 0;

	/*
		Opens the file and parses through the file, reading in the data such as precision, depth, coords
		This will read charaters from the stream fp into the characterStream data.
		1024 is the maximum number of charaters. Fgets will continue reading the line until it hits a newline character.
		EOF is obtained when fgets returns NULL
	*/
	while (fgets(charaterStream, 1024, fp) != NULL)
	{
		int qSize = 0;
		// This line will "transfer" charaters over from characterStream into q until a specific format is hit. IN this case, it is the whitespace (indicated by %s)
		sscanf(charaterStream, "%s", q);
		qSize = sizeof(q);

		/*
			Parsing the file for precision
			This will compare the q string with [precision] to see if it is the precision data
			The sizeof comparison is to ensure that strcmp will not go out of bounds on memory
		*/
		if ((qSize == 11) && (strcmp(q, "[precision]") == 0))
		{
			// This will scan through the charaterStream and when the scan hit numbers, store them into the precision data
			v = StripKey(charaterStream);
			sscanf(v, "%lf", &Precision);
			q[0] = NULL;// Erase the contents of q
			continue;
		}

		// Units of length used by the problem
		if ((qSize == 13) && (strcmp(q, "[lengthunits]") == 0))
		{
			v = StripKey(charaterStream);
			// TODO: add in code here that will delete contents from the q array
			// This line will "transfer" charaters over from v into q (erasing contents until a specific format is hit. IN this case, it is the whitespace (indicated by %s)
			sscanf(v, "%s", q);
			qSize = sizeof(q);
			if ((qSize == 6) && (strcmp(q, "inches") == 0))
				LengthUnits = 0;
			else if ((qSize == 11) && (strcmp(q, "millimeters") == 0))
				LengthUnits = 1;
			else if ((qSize == 11) && (strcmp(q, "centimeters") == 0))
				LengthUnits = 2;
			else if ((qSize == 4) && (strcmp(q, "mils") == 0))
				LengthUnits = 4;
			else if ((qSize == 6) && (strcmp(q, "microns") == 0))
				LengthUnits = 5;
			else if ((qSize == 6) && (strcmp(q, "meters") == 0))
				LengthUnits = 3;
			q[0] = NULL;
			continue;
		}

		// Depth for 2D planar problems;
		if ((qSize == 7) && (strcmp(q, "[depth]") == 0))
		{
			v = StripKey(charaterStream);// Scans the charaterStream until a number is hit
			sscanf(v, "%lf", &Depth);// This will take the numbers stored in v and convert them into a floating value and store in Depth
			q[0] = NULL;
			continue;
		}

		// Problem Type (planar or axisymmetric)
		if ((qSize == 13) && (strcmp(q, "[problemtype]") == 0))
		{
			v = StripKey(charaterStream);
			sscanf(v, "%s", q);
			qSize = sizeof(q);

			if ((qSize == 6) && (strcmp(q, "planar") == 0))
				ProblemType = 0;
			else if ((qSize == 12) && (strcmp(q, "axisymmetric") == 0))
				ProblemType = 1;

			q[0] = NULL;
			continue;
		}

		// Coordinates (cartesian or polar)
		if ((qSize == 13) && (strcmp(q, "[coordinates]") == 0))
		{
			v = StripKey(charaterStream);
			sscanf(v, "%s", q);
			qSize = sizeof(q);

			if ((qSize == 9) && (strcmp(q, "cartesian") == 0))
				Coords = 0;
			else if ((qSize == 5) && (strcmp(q, "polar") == 0))
				Coords = 1;

			q[0] = NULL;
			continue;
		}

		// properties for axisymmetric external region
		if ((qSize == 7) && (strcmp(q, "[extzo]") == 0))
		{
			v = StripKey(charaterStream);
			sscanf(v, "%lf", &extZo);// The %lf indicates a double *
			q[0] = NULL;
			continue;
		}

		if ((qSize == 7) && (strcmp(q, "[extro]") == 0))
		{
			v = StripKey(charaterStream);
			sscanf(v, "%lf", &extRo);
			q[0] = NULL;
			continue;
		}

		if ((qSize == 7) && (strcmp(q, "[extri]") == 0))
		{
			v = StripKey(charaterStream);
			sscanf(v, "%lf", &extRi);
			q[0] = NULL;
			continue;
		}

		// Point Properties
		if ((qSize == 12) && (strcmp(q, "[pointprops]") == 0))
		{
			v = StripKey(charaterStream);
			sscanf(v, "%i", &k);

			if (k > 0)
				nodeproplist = (CPointProp *)calloc(k, sizeof(CPointProp));// Creates an array with k number of elements and sizeof(CPOINTPROP) long. Initilizes all elements to 0 

			q[0] = NULL;
			continue;
		}

		if ((qSize == 11) && (strcmp(q, "<beginpoint>") == 0))
		{
			PProp.V = 0;
			PProp.qp = 0;
			q[0] = NULL;
			continue;
		}

		if ((qSize == 4) && (strcmp(q, "<vp>") == 0))
		{
			v = StripKey(charaterStream);
			sscanf(v, "%lf", &PProp.V);
			q[0] = NULL;
			continue;
		}

		if ((qSize == 4) && (strcmp(q, "<qp>") == 0))
		{
			v = StripKey(charaterStream);
			sscanf(v, "%lf", &PProp.qp);
			q[0] = NULL;
			continue;
		}

		if ((qSize == 9) && (strcmp(q, "<endpoint>") == 0))
		{
			nodeproplist[NumPointProps] = PProp; // Stores the property of the last point in the 0th element
			NumPointProps++;// Counter for determining number of property points in the array
			q[0] = NULL;
			continue;
		}

		// Boundary Properties;
		if ((qSize == 11) && (strcmp(q, "[bdryprops]") == 0))
		{
			v = StripKey(charaterStream);
			sscanf(v, "%i", &k);

			if (k > 0)
				lineproplist = (CBoundaryProp *)calloc(k, sizeof(CBoundaryProp));

			q[0] = NULL;
			continue;
		}

		if ((qSize == 11) && (strcmp(q, "<beginbdry>") == 0))
		{
			BProp.BdryFormat = 0;
			BProp.V = 0;
			BProp.qs = 0;
			BProp.c0 = 0;
			BProp.c1 = 0;
			q[0] = NULL;
			continue;
		}

		if ((qSize == 10) && (strcmp(q, "<bdrytype>") == 0))
		{
			v = StripKey(charaterStream);
			sscanf(v, "%i", &BProp.BdryFormat);// %i means the number is an interger
			q[0] = NULL;
			continue;
		}

		if ((qSize == 4) && (strcmp(q, "<vs>") == 0))
		{
			v = StripKey(charaterStream);
			sscanf(v, "%lf", &BProp.V);
			q[0] = NULL;
			continue;
		}

		if ((qSize == 4) && (strcmp(q, "<qs>") == 0))
		{
			v = StripKey(charaterStream);
			sscanf(v, "%lf", &BProp.qs);
			q[0] = NULL;
			continue;
		}

		if ((qSize == 4) && strcmp(q, "<c0>") == 0)
		{
			v = StripKey(charaterStream);
			sscanf(v, "%lf", &BProp.c0);
			q[0] = NULL;
			continue;
		}

		if ((qSize == 4) && (strcmp(q, "<c1>") == 0))
		{
			v = StripKey(charaterStream);
			sscanf(v, "%lf", &BProp.c1);
			q[0] = NULL;
			continue;
		}

		if ((qSize == 9) && (strcmp(q, "<endbdry>") == 0))
		{
			lineproplist[NumLineProps] = BProp;
			NumLineProps++;
			q[0] = NULL;
			continue;
		}

		// Block Properties;
		if ((qSize == 12) && (strcmp(q, "[blockprops]") == 0))
		{
			v = StripKey(charaterStream);
			sscanf(v, "%i", &k);

			if (k > 0)
				blockproplist = (CMaterialProp *)calloc(k, sizeof(CMaterialProp));

			q[0] = NULL;
			continue;
		}

		if ((qSize == 12) && (strcmp(q, "<beginblock>") == 0))
		{
			MProp.ex = 1;
			MProp.ey = 1;			// permittivity, relative
			MProp.qv = 1;			// charge density, C/m^3
			q[0] = NULL;
			continue;
		}

		if ((qSize == 4) && (strcmp(q, "<ex>") == 0))
		{
			v = StripKey(charaterStream);
			sscanf(v, "%lf", &MProp.ex);
			q[0] = NULL;
			continue;
		}

		if ((qSize == 4) && (strcmp(q, "<ey>") == 0))
		{
			v = StripKey(charaterStream);
			sscanf(v, "%lf", &MProp.ey);
			q[0] = NULL;
			continue;
		}

		if ((qSize == 6) && (strcmp(q, "<qv>") == 0))
		{
			v = StripKey(charaterStream);
			sscanf(v, "%lf", &MProp.qv);
			q[0] = NULL;
			continue;
		}

		if ((qSize == 9) && (strcmp(q, "<endblock>") == 0))
		{
			blockproplist[NumBlockProps] = MProp;
			NumBlockProps++;
			q[0] = NULL;
			continue;
		}

		// Conductor Properties
		if ((qSize == 16) && (strcmp(q, "[conductorprops]") == 0))
		{
			v = StripKey(charaterStream);
			sscanf(v, "%i", &k);

			if (k > 0)
				circproplist = (CCircuit *)calloc(k, sizeof(CCircuit));

			q[0] = NULL;
			continue;
		}

		if ((qSize == 16) && (strcmp(q, "<beginconductor>") == 0))
		{
			CProp.V = 0;
			CProp.q = 0;
			CProp.CircType = 0;
			q[0] = NULL;
			continue;
		}

		if ((qSize == 4) && (strcmp(q, "<vc>") == 0))
		{
			v = StripKey(charaterStream);
			sscanf(v, "%lf", &CProp.V);
			q[0] = NULL;
			continue;
		}

		if ((qSize == 4) && (strcmp(q, "<qc>") == 0))
		{
			v = StripKey(charaterStream);
			sscanf(v, "%lf", &CProp.q);
			q[0] = NULL;
			continue;
		}

		if ((qSize == 15) && (strcmp(q, "<conductortype>") == 0))
		{
			v = StripKey(charaterStream);
			sscanf(v, "%i", &CProp.CircType);
			q[0] = NULL;
			continue;
		}

		if ((qSize == 14) && (strcmp(q, "<endconductor>") == 0))
		{
			circproplist[NumCircProps] = CProp;
			NumCircProps++;
			q[0] = NULL;
			continue;
		}

		// read in regional attributes
		if ((qSize == 13) && (strcmp(q, "[numblocklabels]") == 0))
		{
			int i;
			v = StripKey(charaterStream);
			sscanf(v, "%i", &k);

			if (k > 0)
				labellist = (CBlockLabel *)calloc(k, sizeof(CBlockLabel));

			NumBlockLabels = k;

			for (i = 0; i < k; i++)
			{
				fgets(charaterStream, 1024, fp);
				sscanf(charaterStream, "%lf	%lf	%i	%lf	%i	%i", &blk.x /* The x point */, &blk.y /* The y point */, &blk.BlockType,
					&blk.MaxArea, &blk.InGroup, &blk.IsExternal);
				blk.IsDefault = blk.IsExternal & 2;
				blk.IsExternal = blk.IsExternal & 1;
				blk.BlockType--;
				labellist[i] = blk;
			}
			q[0] = NULL;
			continue;
		}
	}

	fclose(fp);

	return TRUE;
}



/// <summary> This function will open multiple files (mesh file, BC file, etc.) and load the data into matrices. This sets up the problem to be solved</summary>
/// <returns> Returns true if the process succeeds </returns>
BOOL CFemmeDocCore::LoadMesh()
{
	int i, j, k, q, n0, n1, n;
	char infile[256];
	FILE *fp;
	char s[1024];
	double c[] = { 25.4,1.,10.,1000.,0.0254,0.001 };
	CNode node;

	//read meshnodes;
	sprintf(infile, "%s.node", PathName);
	if ((fp = fopen(infile, "rt")) == NULL)// Open the mesh file
	{
		return FALSE;
	}

	fgets(s, 1024, fp);// Gets the first 1024 characters
	sscanf(s, "%i", &k); // scan and transfer until an integer is found
	NumNodes = k;

	meshnode = (CNode *)calloc(k, sizeof(CNode));// Create a array with k elements and sizeof(CNODE) long.

	for (i = 0; i < k; i++)
	{
		fscanf(fp, "%i", &j);// Reads data from the stream and stores the integer (%i) into j
		fscanf(fp, "%lf", &node.x);// Reads data from the stream and stores the double (%lf) into node.x This extracts the nodes x point
		fscanf(fp, "%lf", &node.y);
		fscanf(fp, "%i", &n);

		if (n > 1)
		{
			// strip off point BC number;
			j = n & 0xffff;
			j = j - 2;
			if (j < 0)
				j = -1;

			// strip off Conductor number
			n = (n - (n & 0xffff)) / 0x10000 - 1;
		}
		else
		{
			j = -1;
			n = -1;
		}
		node.bc = j;
		node.InConductor = n;

		// convert all lengths to internal working units of mm
		node.x *= c[LengthUnits];
		node.y *= c[LengthUnits];

		meshnode[i] = node;
	}

	fclose(fp);// Closes the .node file

	//read in periodic boundary conditions
	// TODO: Get clarification of everything under this line
	sprintf(infile, "%s.pbc", PathName);
	if ((fp = fopen(infile, "rt")) == NULL)
	{
		return FALSE;
	}

	fgets(s, 1024, fp);
	sscanf(s, "%i", &k); NumPBCs = k;

	if (k != 0)
		pbclist = (CCommonPoint *)calloc(k, sizeof(CCommonPoint));

	CCommonPoint pbc;
	for (i = 0; i < k; i++)
	{
		fscanf(fp, "%i", &j);
		fscanf(fp, "%i", &pbc.x);
		fscanf(fp, "%i", &pbc.y);
		fscanf(fp, "%i", &pbc.t);
		pbclist[i] = pbc;
	}
	fclose(fp);

	// read in elements;
	sprintf(infile, "%s.ele", PathName);
	if ((fp = fopen(infile, "rt")) == NULL)
	{
		return FALSE;
	}
	fgets(s, 1024, fp);
	sscanf(s, "%i", &k); NumEls = k;

	meshele = (CElement *)calloc(k, sizeof(CElement));
	CElement elm;

	int defaultLabel = 0;

	for (i = 0, defaultLabel = -1; i < NumBlockLabels; i++)
	{
		if (labellist[i].IsDefault)
			defaultLabel = i;
	}


	for (i = 0; i < k; i++)
	{
		fscanf(fp, "%i", &j);
		fscanf(fp, "%i", &elm.p[0]);
		fscanf(fp, "%i", &elm.p[1]);
		fscanf(fp, "%i", &elm.p[2]);
		fscanf(fp, "%i", &elm.lbl);
		elm.lbl--;
		if (elm.lbl < 0) elm.lbl = defaultLabel;
		if (elm.lbl < 0)
		{
			CString msg;
			msg = "Material properties have not been defined for\n";
			msg += "all regions. Press the \"Run Mesh Generator\"\n";
			msg += "button to highlight the problem regions.";
			MsgBox(msg);
			fclose(fp);
			sprintf(infile, "%s.ele", PathName);	DeleteFile(infile);
			sprintf(infile, "%s.node", PathName);	DeleteFile(infile);
			sprintf(infile, "%s.pbc", PathName);	DeleteFile(infile);
			sprintf(infile, "%s.poly", PathName);	DeleteFile(infile);
			sprintf(infile, "%s.edge", PathName);	DeleteFile(infile);
			exit(1);
		}
		// look up block type out of the list of block labels
		elm.blk = labellist[elm.lbl].BlockType;

		meshele[i] = elm;
	}
	fclose(fp);

	// initialize edge bc's and element permeabilities;
	for (i = 0; i < NumEls; i++)
		for (j = 0; j < 3; j++)
			meshele[i].e[j] = -1;

	// read in edges to which boundary conditions are applied;

		// first, do a little bookkeeping so that element
		// associated with a give edge can be identified fast
	int *nmbr;
	int **mbr;

	nmbr = (int *)calloc(NumNodes, sizeof(int));

	// Make a list of how many elements that tells how
	// many elements to which each node belongs.
	for (i = 0; i < NumEls; i++)
	{
		for (j = 0; j < 3; j++)
			nmbr[meshele[i].p[j]]++;
	}

	// mete out some memory to build a list of the
	// connectivity...
	mbr = (int **)calloc(NumNodes, sizeof(int *));
	for (i = 0; i < NumNodes; i++)
	{
		mbr[i] = (int *)calloc(nmbr[i], sizeof(int));
		nmbr[i] = 0;
	}

	// fill up the connectivity information;
	for (i = 0; i < NumEls; i++)
	{
		for (j = 0; j < 3; j++)// The three here indicates three points on a triangle
		{
			k = meshele[i].p[j];
			mbr[k][nmbr[k]] = i;
			nmbr[k]++;
		}
	}


	sprintf(infile, "%s.edge", PathName);

	if ((fp = fopen(infile, "rt")) == NULL)
	{
		return FALSE;
	}

	fscanf(fp, "%i", &k);	// read in number of lines

	fscanf(fp, "%i", &j);	// read in boundarymarker flag;
	for (i = 0; i < k; i++)
	{
		fscanf(fp, "%i", &j);
		fscanf(fp, "%i", &n0);
		fscanf(fp, "%i", &n1);
		fscanf(fp, "%i", &n);

		// BC number;
		if (n < 0)
		{
			n = (-n);
			j = (n & 0xffff) - 2;
			if (j < 0) j = -1;

			// Conductor number;
			n = (n - (n & 0xffff)) / 0x10000 - 1;
			if (n >= 0)
			{
				meshnode[n0].InConductor = n;
				meshnode[n1].InConductor = n;
			}
		}
		else
			j = -1;

		if (j >= 0)
		{
			// search through elements to find one containing the line;
			// set corresponding edge equal to the bc number
			for (q = 0, n = FALSE; q < nmbr[n0]; q++)
			{
				elm = meshele[mbr[n0][q]];

				if ((elm.p[0] == n0) && (elm.p[1] == n1))
				{
					elm.e[0] = j;
					n = TRUE;
				}

				if ((elm.p[0] == n1) && (elm.p[1] == n0))
				{
					elm.e[0] = j;
					n = TRUE;
				}

				if ((elm.p[1] == n0) && (elm.p[2] == n1))
				{
					elm.e[1] = j;
					n = TRUE;
				}

				if ((elm.p[1] == n1) && (elm.p[2] == n0))
				{
					elm.e[1] = j;
					n = TRUE;
				}

				if ((elm.p[2] == n0) && (elm.p[0] == n1))
				{
					elm.e[2] = j;
					n = TRUE;
				}

				if ((elm.p[2] == n1) && (elm.p[0] == n0))
				{
					elm.e[2] = j;
					n = TRUE;
				}

				meshele[mbr[n0][q]] = elm;

				//this is a little hack: line charge distributions should be applied
				//to at most one element;
				if ((lineproplist[j].BdryFormat == 2) && (n))
					q = nmbr[n0];
			}
		}

	}
	fclose(fp);

	// free up the connectivity information
	free(nmbr);

	for (i = 0; i < NumNodes; i++)
		free(mbr[i]);

	free(mbr);

	// clear out temporary files
	sprintf(infile, "%s.ele", PathName);	DeleteFile(infile);
	sprintf(infile, "%s.node", PathName);	DeleteFile(infile);
	sprintf(infile, "%s.pbc", PathName);	DeleteFile(infile);
	sprintf(infile, "%s.poly", PathName);	DeleteFile(infile);

	return TRUE;
}

#pragma endregion