//
//  DiffDistance.cpp
//  libdxf
//
//  Created by Uwe Runtemund on 17.12.13.
//  Copyright (c) 2013 Jameo Software. All rights reserved.
//

#include "Precompiled.h"

using namespace jm;

DiffDistance::DiffDistance()
{
	diagonal = NULL;
	distance = 0;
	calc = 0;
}


void DiffDistance::Clear()
{
	if(diagonal != NULL)
	{
		delete diagonal;
		diagonal = NULL;
	}
	u.clear();
	v.clear();
	distance = 0;
	calc = 0;
}

void DiffDistance::AddU(Object* obj)
{
	u.push_back(obj);
}

void DiffDistance::AddV(Object* obj)
{
	v.push_back(obj);
}

DiffBacktrace* DiffDistance::Solve()
{
	m = u.size();
	n = v.size();


	//Speed-Up: Durch Betrachtung der Diagonalen....
	//http://www.csse.monash.edu.au/~lloyd/tildeStrings/Alignment/92.IPL.html
	//

	//Berechnung nach:
	// http://de.wikipedia.org/wiki/Levenshtein-Distanz
	// http://en.wikipedia.org/wiki/Levenshtein_distance


	// which is the diagonal containing the bottom R.H. element?
	int lba = (int)(v.size() - u.size());

	DiffDiag* main = new DiffDiag(this, &u, &v, 0);


	if(lba >= 0)
	{
		diagonal = main;
		for(int i = 0; i < lba; i++)
			diagonal = diagonal->GetAbove();
	}
	else
	{
		diagonal = main->GetBelow();
		for(int i = 0; i < ~lba; i++)
			diagonal = diagonal->GetAbove();
	}

	distance = diagonal->GetEntry((int)std::min(m, n));

	unsigned long sz=m*n;
	std::cout << "Distance " << distance << std::endl;
	std::cout << "Calcucalted " << calc << "/" << sz << ": " << (calc*100.0/((double)sz)) << "%" << std::endl;

	int i = (int) std::min(m, n);
	return DiffBacktrace::Backtrace(diagonal, i);
}


uint32 DiffDistance::GetDistance()
{
	return distance;
}


