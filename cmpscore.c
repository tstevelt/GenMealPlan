/*----------------------------------------------------------------------------
	Program : cmpscore.c
	Author  : Tom Stevelt
	Date    : 2023-2024
	Synopsis: comparison function for qsort/bsearch
	Return  : 
----------------------------------------------------------------------------*/
// 	Copyright © 2023-2024 Tom Stevelt
// 	Tom Stevelt <tstevelt@silverhammersoftware.com>
// 	This software is free software; you can redistribute it and/or modify
// 	it under the terms of the MIT license. See LICENSE for details.
#include	"GenMealPlan.h"

int cmpscore ( POP_RECORD *a, POP_RECORD *b )
{
	if ( a->MealScore < b->MealScore )
	{
		return ( -1 );
	}
	if ( a->MealScore > b->MealScore )
	{
		return ( 1 );
	}
	return ( 0 );
}
