/*----------------------------------------------------------------------------
	Program : PrintFuncs.c
	Author  : Tom Stevelt
	Date    : 2023-2024
	Synopsis: GA printing functions.
	Return  : 
----------------------------------------------------------------------------*/
// 	Copyright © 2023-2024 Tom Stevelt
// 	Tom Stevelt <tstevelt@silverhammersoftware.com>
// 	This software is free software; you can redistribute it and/or modify
// 	it under the terms of the MIT license. See LICENSE for details.

#include	"GenMealPlan.h"

void PrintIndividual ( POP_RECORD *Individual, int Marker )
{
	for ( int xm = 0; xm < Individual->MealCount; xm++ )
	{
		if ( Marker > 0 && Marker == xm )
		{
			printf ( " | " );
		}
		printf ( " %4ld", Individual->MealArray[xm].Fid );
	}
	printf ( "\n" );
}

void PrintGeneration ( int Generation )
{
	if ( Verbose )
	{
		if ( Generation  == 0 || Generation == Generations - 1 )
		{
			printf ( "GENERATION %d\n", Generation + 1 );
		}
	}

	MinScore = MaxScore = PopArray[0].MealScore;

	/*----------------------------------------------------------
		last one never get selected for breeding, so do not print
		or use in stats.
	----------------------------------------------------------*/
	for ( int xp = 0; xp < PopCount - 1; xp++ )
	{
		if ( Verbose )
		{
			if ( Generation  == 0 || Generation == Generations - 1 )
			{
				printf ( "%4d:", xp );
				for ( int xm = 0; xm < PopArray[xp].MealCount; xm++ )
				{
					printf ( " %4ld", PopArray[xp].MealArray[xm].Fid );
				}
				printf ( " = %.4f\n", PopArray[xp].MealScore );
			}
		}
		if ( MinScore > PopArray[xp].MealScore )
		{
			MinScore = PopArray[xp].MealScore;
		}
		if ( MaxScore < PopArray[xp].MealScore )
		{
			MaxScore = PopArray[xp].MealScore;
		}
	}
	if ( Verbose && (Generation % 50 == 0))
	{
		printf ( "Gen %d Min %.4f Max %.4f Diff %.4f\n", Generation, MinScore, MaxScore, MaxScore - MinScore );
	}
}
