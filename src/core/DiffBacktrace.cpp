//
//  DiffBacktrace.cpp
//  libdwg
//
//  Created by Uwe Runtemund on 17.12.13.
//  Copyright (c) 2013 Jameo Software. All rights reserved.
//
#include "Precompiled.h"

using namespace jm;

DiffBacktrace::DiffBacktrace()
{
	size = 0;
	operation = kDiffStart;
	obj1 = NULL;
	obj2 = NULL;
	prev = NULL;
	next = NULL;
}

DiffBacktrace::DiffBacktrace(const DiffBacktrace &another)
{
	size = another.size;
	operation = another.operation;
	obj1 = another.obj1;
	obj2 = another.obj2;
	prev = another.prev;
	next = another.next;
}

DiffBacktrace::~DiffBacktrace()
{

	if(next != NULL)
	{
		delete next;
		next = NULL;
	}

}


void DiffBacktrace::Print()
{
	DiffBacktrace* step = this;

	DiffInfo di;

	do
	{
		di.Print(step->operation, step->obj1, step->obj2);
		step = step->next;
	}
	while(step != NULL);
}

DiffBacktrace* DiffBacktrace::Backtrace(DiffDiag* diag, uint32 i)
{
	bool loop = true;

	std::vector<DiffBacktrace*> stack;

	while(loop)
	{

		DiffOperation op;

		if(i == 0)
		{
			if(diag->GetOffset() == 0)
			{
				op = kDiffStart;
			}
			else if(diag->GetOffset() > 0)
			{
				op = kDiffAdd;
			}
			else
			{
				op = kDiffDelete;
			}
		}
		else if(diag->GetObjU(i)->Equals(diag->GetObjV(i)))
		{
			op = kDiffEqual;
		}
		else
		{
			Integer me = diag->GetEntry(i);
			Integer w = diag->GetLeftEntry(i);
			Integer nw = diag->GetEntry(i - 1);

			if(me == 1 + w)
			{
				if(diag->GetOffset() >= 0)
				{
					op = kDiffAdd;
				}
				else
				{
					op = kDiffDelete;
				}
			}
			else if(me == 1 + nw)
			{
				op = kDiffModified;
			}
			else
			{
				if(diag->GetOffset() >= 0)
				{
					op = kDiffDelete;
				}
				else
				{
					op = kDiffAdd;
				}
			}
		}

		DiffBacktrace* ret = new DiffBacktrace();

		ret->operation = op;
		switch(op)
		{
			case kDiffEqual:
				//			ret->last=Backtrace(diag,i-1);
				i--;
				break;

			case kDiffModified:
				//			ret->last=Backtrace(diag,i-1);
				ret->obj1 = diag->GetObjU(i);
				ret->obj2 = diag->GetObjV(i);
				i--;
				break;

			case kDiffAdd:
				if(diag->GetOffset() == 0)
				{
					//				ret->last=Backtrace(diag->GetBelow(),i-1);
					ret->obj1 = diag->GetObjV(i);
					diag = diag->GetBelow();
					i--;
				}
				else if(diag->GetOffset() >= 0)
				{
					//				ret->last=Backtrace(diag->GetBelow(),i);
					ret->obj1 = diag->GetObjV(i);
					diag = diag->GetBelow();
				}
				else
				{
					//				ret->last=Backtrace(diag->GetAbove(),i-1);
					ret->obj1 = diag->GetObjV(i);
					diag = diag->GetAbove();
					i--;
				}
				break;

			case kDiffDelete:
				if(diag->GetOffset() == 0)
				{
					//				ret->last =Backtrace(diag->GetAbove(),i-1);
					ret->obj1 = diag->GetObjV(i);
					diag = diag->GetAbove();
					i--;
				}
				else if(diag->GetOffset() >= 0)
				{
					//				ret->last =Backtrace(diag->GetAbove(),i-1);
					ret->obj1 = diag->GetObjV(i);
					diag = diag->GetAbove();
					i--;
				}
				else
				{
					//				ret->last =Backtrace(diag->GetBelow(),i);
					ret->obj1 = diag->GetObjV(i);
					diag = diag->GetBelow();
				}
				break;

			case kDiffStart:
				loop = false;
				break;

		}

		stack.push_back(ret);
	}

	DiffBacktrace* top = stack.back();
	stack.pop_back();

	DiffBacktrace* step = top;
	while(stack.size() > 0)
	{
		step->next = stack.back();
		stack.pop_back();
		step->next->prev = step;
		step = step->next;
	}

	return top;
}


DiffOperation DiffBacktrace::GetOperation()
{
	return operation;
}



