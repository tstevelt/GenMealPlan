/*----------------------------------------------------------------------------
	Program : LoadFTD.c
	Author  : Tom Stevelt
	Date    : 2023-2024
	Synopsis: If running with "Finish the day", then load food already 
				entered for the day.
	Return  : 
----------------------------------------------------------------------------*/
// 	Copyright © 2023-2024 Tom Stevelt
// 	Tom Stevelt <tstevelt@silverhammersoftware.com>
// 	This software is free software; you can redistribute it and/or modify
// 	it under the terms of the MIT license. See LICENSE for details.

#include	"GenMealPlan.h"

void LoadFTD ()
{
	DBY_QUERY       *qry;
	long			Count;

	FTD_Calorie = FTD_Carb = FTD_Protein = FTD_Fat = FTD_Sodium = FTD_Fiber = 0.0;

	sprintf ( Statement, "select sum(HFserving*Fcalorie), sum(HFserving*Fcarb), sum(HFserving*Fprotein), sum(HFserving*Ffat), \
sum(HFserving*Fsodium), sum(HFserving*Ffiber), count(*) from food, history, histfood \
where Fid = HFfood  and Hid = HFhist \
and Hdate = '%s' \
and Hmember = %ld",
		FTD_Date, xmember.xmid );

#ifdef DEBUG
#define DEBUG
	printf ( Statement );
#endif

	qry = dbySelect ( "nutrition", &MySql, Statement, LogFileName );

	if ( qry == NULL )
	{
		printf ( "LoadFTD: dbySelect returned NULL for %s\n", FTD_Date );
		exit ( 1 );
	}

	if (( qry->EachRow = mysql_fetch_row ( qry->Result )) == NULL )
	{
		printf ( "LoadFTD: mysql_fetch_row returned NULL for %s\n", FTD_Date );
		exit ( 1 );
	}
	if (( Count = nsAtol ( qry->EachRow[6] )) == 0 )
	{
		printf ( "LoadFTD: no foods found for %s\n", FTD_Date );
		exit ( 1 );
	}

	FTD_Calorie = nsAtof(qry->EachRow[0]);
	FTD_Carb = nsAtof(qry->EachRow[1]);
	FTD_Protein = nsAtof(qry->EachRow[2]);
	FTD_Fat = nsAtof(qry->EachRow[3]);
	FTD_Sodium = nsAtof(qry->EachRow[4]);
	FTD_Fiber = nsAtof(qry->EachRow[5]);
}
