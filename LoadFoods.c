/*----------------------------------------------------------------------------
	Program : LoadFoods.c
	Author  : Tom Stevelt
	Date    : 2023-2024
	Synopsis: Load either all foods or commonly used foods.
	Return  : 
----------------------------------------------------------------------------*/
// 	Copyright © 2023-2024 Tom Stevelt
// 	Tom Stevelt <tstevelt@silverhammersoftware.com>
// 	This software is free software; you can redistribute it and/or modify
// 	it under the terms of the MIT license. See LICENSE for details.

#include    "GenMealPlan.h"

#define		FOOD_CHUNK		100

static int EachFood ( XFOOD *ptr )
{
	if ( FoodSize == 0 )
	{
		if (( FoodArray = calloc ( FOOD_CHUNK, sizeof(FOOD_RECORD) )) == NULL )
		{
			printf ( "calloc food_array failed\n" );
			exit ( 1 );
		}
		FoodSize = FOOD_CHUNK;
	}
	else if ( FoodCount >= FoodSize )
	{
		FoodSize += FOOD_CHUNK;
		if (( FoodArray = realloc ( FoodArray, FoodSize * sizeof(FOOD_RECORD) )) == NULL )
		{
			printf ( "realloc food_array failed\n" );
			exit ( 1 );
		}
	}

	FoodArray[FoodCount].Fid     = ptr->xfid;
	FoodArray[FoodCount].Calorie = ptr->xfcalorie;
	FoodArray[FoodCount].Carb    = ptr->xfcarb;
	FoodArray[FoodCount].Protein = ptr->xfprotein;
	FoodArray[FoodCount].Fat     = ptr->xffat;
	FoodArray[FoodCount].Sodium  = ptr->xfsodium;
	FoodArray[FoodCount].Fiber   = ptr->xffiber;

	FoodCount++;

	return ( 0 );
}

void LoadFoods ()
{
#ifdef HAVE_DATABASE
	if ( Source == 'C' || Source == 'A' )
	{
		sprintf ( WhereClause, "Fcalorie > 0 and Fprotein > 0" );
		if ( Source == 'C' )
		{
			strcat ( WhereClause, " and Fstatus = 'A'" );
		}

		if ( LoadFoodCB ( WhereClause, NULL, &xfood, EachFood, 0 ) < 1 )
		{
			printf ( "Could not load foods\n" );
			exit ( 1 );
		}
	}
	else 
#endif
	if ( Source == 'F' )
	{
		FILE	*fp;
		char	xbuffer[1024];
		char	*tokens[15];
		int		tokcnt;

		if (( fp = fopen ( Filename, "r" )) == NULL )
		{
			printf ( "Can not open file %s\n", Filename );
			exit ( 1 );
		}

		while ( fgets ( xbuffer, sizeof(xbuffer), fp ) != NULL )
		{
			if (( tokcnt = GetTokensD ( xbuffer, "|\n\r", tokens, 15 )) < 11 )
			{
				continue;
			}

			if (( xfood.xfid = nsAtol ( tokens[0] )) == 0 )
			{
				continue;
			}

/*---------------------------------------------------------------------------
ID|name|FoodGroup|Calories|Carb|Protein|Fat|Sodium|Fiber|Weight|Serving|Length
168982|Blackberries Wild Raw (Alaska Native)|American Indian|81.64|15.45|1.32|1.68|9.42|5.02|157|1 cup|37
167633|Bread Kneel Down (Navajo)|American Indian|55.38|11.21|1.22|0.63|35.78|0.00|28.4|1 oz|25
---------------------------------------------------------------------------*/

			xfood.xfcalorie = nsAtof ( tokens[3] );
			xfood.xfcarb    = nsAtof ( tokens[4] );
			xfood.xfprotein = nsAtof ( tokens[5] );
			xfood.xffat     = nsAtof ( tokens[6] );
			xfood.xfsodium  = nsAtof ( tokens[7] );
			xfood.xffiber   = nsAtof ( tokens[8] );

			EachFood ( &xfood );
		}

		nsFclose ( fp );
	}
	else
	{
		printf ( "Unknown source %c\n", Source );
		exit ( 1 );
	}

#ifdef DEBUG
	for ( int xf = 0; xf < FoodCount; xf++ )
	{
		printf ( "%4d: %4ld\n", xf, FoodArray[xf].Fid );
	}
#endif

	if ( Verbose )
	{
		printf ( "Loaded %d foods\n", FoodCount );
	}
}
