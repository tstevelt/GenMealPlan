/*----------------------------------------------------------------------------
	Program : initpop.c
	Author  : Tom Stevelt
	Date    : 2023-2024
	Synopsis: Initialize GA population
	Return  : 
----------------------------------------------------------------------------*/
// 	Copyright © 2023-2024 Tom Stevelt
// 	Tom Stevelt <tstevelt@silverhammersoftware.com>
// 	This software is free software; you can redistribute it and/or modify
// 	it under the terms of the MIT license. See LICENSE for details.

#include	"GenMealPlan.h"

static int cmprec ( FOOD_RECORD *a, FOOD_RECORD *b )
{
	if ( a->Sort < b->Sort )
	{
		return ( -1 );
	}
	if ( a->Sort > b->Sort )
	{
		return ( 1 );
	}
	return ( 0 );
}

static void shuffle ()
{
	for ( int ndx = 0; ndx < FoodCount; ndx++ )
	{
		FoodArray[ndx].Sort = d_random ();
	}
	qsort ( FoodArray, FoodCount, sizeof(FOOD_RECORD), (int(*)()) cmprec );
}

#define		POP_CHUNK	100

void initpop ()
{
	int		MajorIndex;
	int		MealSize;
	int		xf;

	SameCrossCount = DiffCrossCount = NoCrossCount = MutateCount = 0;

	seed_random_with_usec ();
	shuffle ();

	if (( PopArray = calloc ( POP_CHUNK, sizeof(POP_RECORD) )) == NULL )
	{
		printf ( "calloc pop_array failed\n" );
		exit ( 1 );
	}
	PopSize = POP_CHUNK;

	xf = 0;
	PopCount = 0;

	for  ( MealSize = MinFoods; MealSize <= MaxFoods; MealSize++ )
	{
		if ( xf + MealSize >= FoodCount )
		{
			shuffle ();
			xf = 0;
		}

#ifdef DEBUG
		printf ( "MealSize %d\n", MealSize );
#endif

		for ( MajorIndex = 0; MajorIndex < MajorCount; MajorIndex++ )
		{
			if ( xf + MealSize >= FoodCount )
			{
				shuffle ();
				xf = 0;
			}

#ifdef DEBUG
			printf ( "MajorIndex %d\n", MajorIndex );
#endif

			for ( ; xf + MealSize < FoodCount; )
			{
				if ( PopCount >= PopSize )
				{
					PopSize += POP_CHUNK;
					if (( PopArray = realloc ( PopArray, PopSize * sizeof(POP_RECORD) )) == NULL )
					{
						printf ( "realloc pop_array failed\n" );
						exit ( 1 );
					}
				}

				PopArray[PopCount].MealCount = MealSize;
				for ( int xm = 0; xm < MealSize; xm++ )
				{
					memcpy ( &PopArray[PopCount].MealArray[xm], &FoodArray[xf++], sizeof(FOOD_RECORD) );
				}
				PopArray[PopCount].MealScore = obj_func ( &PopArray[PopCount] );

				PopCount++;
			}
		}
	}

	qsort ( PopArray, PopCount, sizeof(POP_RECORD), (int(*)()) cmpscore );

	if ( Verbose )
	{
		printf ( "Population count %d\n", PopCount );
	}
}
