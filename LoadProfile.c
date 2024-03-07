/*----------------------------------------------------------------------------
	Program : LoadProfile.c
	Author  : Tom Stevelt
	Date    : 2023-2024
	Synopsis: Load macro information from demo member's profile, if running 
				from command line (or crontab)
	Return  : 
----------------------------------------------------------------------------*/
// 	Copyright © 2023-2024 Tom Stevelt
// 	Tom Stevelt <tstevelt@silverhammersoftware.com>
// 	This software is free software; you can redistribute it and/or modify
// 	it under the terms of the MIT license. See LICENSE for details.

#include	"GenMealPlan.h"

void LoadProfile ( char *ProfileFilename )
{
	FILE	*fp;
	char	xbuffer[128];
	char	*tokens[4];
	int		tokcnt;

	/*---------------------------------------------------------------------------
		#
		#	sample member profile
		#	Calories should equal 4*(carb+protien) + 9*fat
		#
		ID		= 99
		Name	= George "Gym Rat" Smith
		Calorie	= 3500
		Carb	= 400
		Protein	= 250
		Fat		= 100
		Sodium	= 2500
		Fiber	= 35
	---------------------------------------------------------------------------*/

	if (( fp = fopen ( ProfileFilename, "r" )) == NULL )
	{
		printf ( "Cannot open profile filename %s for reading\n", ProfileFilename );
		exit ( 1 );
	}

	xmember.xmid = 1;
	nsStrcpy ( xmember.xmname, "Demo Member" );
	xmember.xmcalorie = 2500;
	xmember.xmcarb    = 305;	// 1200
	xmember.xmprotein = 140;	// 520
	xmember.xmfat     = 80;		// 720
	xmember.xmsodium  = 1500;
	xmember.xmfiber   = 30;

	while ( fgets ( xbuffer, sizeof(xbuffer), fp ) != NULL )
	{
		if ( xbuffer[0] == '#' )
		{
			continue;
		}

		if (( tokcnt = GetTokensD ( xbuffer, "=\t\n\r", tokens, 4 )) < 2 )
		{
			continue;
		}

		if ( nsStrcasecmp ( tokens[0], "ID" ) == 0 )
		{
			xmember.xmid = nsAtol ( tokens[1] );
		}
		else if ( nsStrcasecmp ( tokens[0], "Name" ) == 0 )
		{
			nsStrcpy ( xmember.xmname, tokens[1] );
		}
		else if ( nsStrcasecmp ( tokens[0], "Calorie" ) == 0 )
		{
			xmember.xmcalorie = nsAtof ( tokens[1] );
		}
		else if ( nsStrcasecmp ( tokens[0], "Carb" ) == 0 )
		{
			xmember.xmcarb = nsAtof ( tokens[1] );
		}
		else if ( nsStrcasecmp ( tokens[0], "Protein" ) == 0 )
		{
			xmember.xmprotein = nsAtof ( tokens[1] );
		}
		else if ( nsStrcasecmp ( tokens[0], "Fat" ) == 0 )
		{
			xmember.xmfat = nsAtof ( tokens[1] );
		}
		else if ( nsStrcasecmp ( tokens[0], "Sodium" ) == 0 )
		{
			xmember.xmsodium = nsAtof ( tokens[1] );
		}
		else if ( nsStrcasecmp ( tokens[0], "Fiber" ) == 0 )
		{
			xmember.xmfiber = nsAtof ( tokens[1] );
		}
	}

	if ( ChkMacroArithmetic ( xmember.xmcalorie, xmember.xmcarb, xmember.xmprotein, xmember.xmfat, 1.0 ) != 0 )
	{
		printf ( "Calories should equal 4*(carb+protien) + 9*fat\n" );
	}

	nsFclose ( fp );
}
