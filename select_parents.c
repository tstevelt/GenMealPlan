/*----------------------------------------------------------------------------
	Program : select_parents.c
	Author  : Tom Stevelt
	Date    : 2023-2024
	Synopsis: GA select parents for next generation
	Return  : 
----------------------------------------------------------------------------*/
// 	Copyright © 2023-2024 Tom Stevelt
// 	Tom Stevelt <tstevelt@silverhammersoftware.com>
// 	This software is free software; you can redistribute it and/or modify
// 	it under the terms of the MIT license. See LICENSE for details.

#include	"GenMealPlan.h"

void select_parents ( int *Parent1, int *Parent2 )
{
	int		r1, r2;

	r1 = r2 = random_range ( 0, PopCount-1 );
	
	while ( r1 == r2 )
	{
		r2 = random_range ( 0, PopCount-1 );
	}

	/*----------------------------------------------------------
		like golf, lowest score is best.
	----------------------------------------------------------*/
	if ( PopArray[r1].MealScore < PopArray[r2].MealScore )
	{
		*Parent1 = r1;
	}
	else
	{
		*Parent1 = r2;
	}

	do
	{
		r1 = r2 = random_range ( 0, PopCount-1 );
		
		while ( r1 == r2 )
		{
			r2 = random_range ( 0, PopCount-1 );
		}

		if ( PopArray[r1].MealScore < PopArray[r2].MealScore )
		{
			*Parent2 = r1;
		}
		else
		{
			*Parent2 = r2;
		}

	} while ( *Parent1 == *Parent2 );
}
