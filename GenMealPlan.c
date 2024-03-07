/*----------------------------------------------------------------------------
	Program : GenMealPlan.c
	Author  : Silver Hammer Software LLC
	Author  : Tom Stevelt
	Date    : April 2023
	Synopsis: Find 10 to 30 foods for a day to meet user macros.
	Return  : 

	Copyright © 2023 Tom Stevelt and Silver Hammer Software LLC
	Tom Stevelt <tstevelt@silverhammersoftware.com>

	This software is free software; you can redistribute it and/or modify
	it under the terms of the MIT license. See LICENSE for details.

	Who	 Date		Modification
	--------------------------------------------------------------------
	tms	 05/01/2023	Added #define HAVE_DATABASE and released on github.
	tms	 03/07/2024 Also included in complete nutrition github release

----------------------------------------------------------------------------*/
// 	Copyright © 2023-2024 Tom Stevelt
// 	Tom Stevelt <tstevelt@silverhammersoftware.com>
// 	This software is free software; you can redistribute it and/or modify
// 	it under the terms of the MIT license. See LICENSE for details.
#define		MAIN
#include	"GenMealPlan.h"

int main ( int argc, char *argv[] )
{
	int			Parent1, Parent2, xp;
	POP_RECORD	*NewArray;
	double TotalCalorie, TotalCarb, TotalProtein, TotalFat, TotalSodium, TotalFiber;
	char	Title[80];

	getargs ( argc, argv );

#ifdef HAVE_DATABASE
	dbyConnect ( &MySql, "nutrition", "tms", 0, stderr );

	sprintf ( WhereClause, "Mid = %ld", xmember.xmid );
	if ( LoadMember ( WhereClause, &xmember, 0 ) != 1 )
	{
		printf ( "Unknown member %ld\n", xmember.xmid );
		exit ( 1 );
	}
	if ( FTD )
	{
		LoadFTD ();
	}
#endif

	LoadFoods ();

	StartTime = GetCurrentTime ( 0);

	initpop ();
	
	NewArray = calloc ( PopCount, sizeof(POP_RECORD) );

	for ( int xg = 0; xg < Generations; xg++ )
	{
		memset ( NewArray, '\0', PopCount * sizeof(POP_RECORD) );

		for ( xp = 0; xp < PopCount; xp++ )
		{
			PopArray[xp].SelectedCount = 0;
		}

		for ( xp = 0; xp < PopCount; xp += 2 )
		{
			select_parents ( &Parent1, &Parent2 );

			crossover ( &PopArray[Parent1], &PopArray[Parent2],
						&NewArray[xp     ], &NewArray[xp+1   ] );
		}

		if ( Debug == DEBUG_SELECTED )
		{
			int		TotalSelected = 0;
			printf ( "-- generation %d --\n", xg+1 );
			for ( xp = 0; xp < PopCount; xp++ )
			{
				printf ( "%4d %.4f selected %4d\n", xp+1, PopArray[xp].MealScore, PopArray[xp].SelectedCount );
				TotalSelected += PopArray[xp].SelectedCount;
			}
			printf ( "TotalSelected %d\n", TotalSelected );
		}

		for ( xp = 0; xp < PopCount; xp += 2 )
		{
			memcpy ( &PopArray[xp], &NewArray[xp], sizeof(POP_RECORD) );
		}

		for ( xp = 0; xp < PopCount; xp++ )
		{
			PopArray[xp].MealScore = obj_func ( &PopArray[xp] );
		}
		qsort ( PopArray, PopCount, sizeof(POP_RECORD), (int(*)()) cmpscore );
		
		PrintGeneration ( xg );
	}

	/*----------------------------------------------------------
		print recommended meal
	----------------------------------------------------------*/
	int xl = sprintf ( Title, "DAILY FOOD PLAN FOR %s", xmember.xmname );
	Spacer ( (92 - xl)/2 );
	printf ( "%s\n", Title );

	switch ( Source )
	{
		case 'C':
			Spacer ( (92 - xl)/2 );
			printf ( "SELECTED FROM COMMONLY USED FOODS\n\n" );
			break;
		case 'A':
			Spacer ( (92 - xl)/2 );
			printf ( "SELECTED FROM ALL FOODS IN DATABASE\n\n" );
			break;
		case 'F':
			Spacer ( (92 - xl)/2 );
			printf ( "SELECTED FROM CUSTOM FILE\n\n" );
			break;
	}

	printf ( "ID     DESCRIPTION                              SERVING     CALORIE     CARB  PROTEIN      FAT   SODIUM    FIBER\n" );

	TotalCalorie = TotalCarb = TotalProtein = TotalFat = TotalSodium = TotalFiber = 0;

#ifdef HAVE_DATABASE
	if ( FTD )
	{
		printf ( "%6.6s %-40.40s %-10.10s %8.2f %8.2f %8.2f %8.2f %8.2f %8.2f\n", 
			" ", FTD_Date, " ",
			FTD_Calorie, FTD_Carb, FTD_Protein, FTD_Fat, FTD_Sodium, FTD_Fiber );
	}
#endif

	for ( int xf = 0; xf < PopArray[0].MealCount; xf++ )
	{
		switch ( Source )
		{
			case 'C':
			case 'A':
				sprintf ( WhereClause, "Fid = %ld", PopArray[0].MealArray[xf].Fid );
#ifdef HAVE_DATABASE
				LoadFood ( WhereClause, &xfood, 0 );
#endif
				break;

			default:
				FindFood ( PopArray[0].MealArray[xf].Fid );
				break;
		}

		printf ( "%-6ld %-40.40s %-10.10s %8.2f %8.2f %8.2f %8.2f %8.2f %8.2f\n", 
					xfood.xfid, 
					xfood.xfname,
					xfood.xfserving, 
					xfood.xfcalorie,
					xfood.xfcarb,
					xfood.xfprotein,
					xfood.xffat,
					xfood.xfsodium,
					xfood.xffiber );

		TotalCalorie += xfood.xfcalorie;
		TotalCarb += xfood.xfcarb;
		TotalProtein += xfood.xfprotein;
		TotalFat += xfood.xffat;
		TotalSodium += xfood.xfsodium;
		TotalFiber += xfood.xffiber;
	}
	
printf ( "                                                           -------- -------- -------- -------- -------- --------\n" );

	printf ( "%6.6s %-40.40s %-10.10s %8.2f %8.2f %8.2f %8.2f %8.2f %8.2f\n", 
		" ", " ", "TOTAL",
		TotalCalorie + FTD_Calorie, 
		TotalCarb    + FTD_Carb, 
		TotalProtein + FTD_Protein, 
		TotalFat     + FTD_Fat, 
		TotalSodium  + FTD_Sodium, 
		TotalFiber   + FTD_Fiber );

	printf ( "%6.6s %-40.40s %-10.10s %8.2f %8.2f %8.2f %8.2f %8.2f %8.2f\n", 
		" ", " ", "TARGET",
		(double)xmember.xmcalorie, (double)xmember.xmcarb, (double)xmember.xmprotein, (double)xmember.xmfat, (double)xmember.xmsodium, (double)xmember.xmfiber );

#ifdef HAVE_DATABASE
	dbyClose ( &MySql );
#endif

	if ( Statistics )
	{
		EndTime = GetCurrentTime ( 0);

		printf ( "Input Foods    %d\n", FoodCount );
		printf ( "PopCount       %d\n", PopCount );
		printf ( "Prob Cross     %.2f\n", pCross );
		printf ( "SameCrossCount %d\n", SameCrossCount );
		printf ( "DiffCrossCount %d\n", DiffCrossCount );
		printf ( "NoCrossCount   %d\n", NoCrossCount );
		printf ( "Prob Mutation  %.2f\n", pMutation );;
		printf ( "MutateCount    %d\n", MutateCount );
		printf ( "Score          %.4f to %.4f diff %.4f\n", MinScore, MaxScore, MaxScore - MinScore );
		printf ( "Run Time       %.4f seconds %.0f op/sec\n", EndTime - StartTime, 
					(SameCrossCount + DiffCrossCount + MutateCount) / (EndTime - StartTime) );
		printf ( "Day Foods      %d\n", PopArray[0].MealCount );
	}

	return ( 0 );
}
