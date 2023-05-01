
#include	"GenMealPlan.h"

int FindFood ( long Fid )
{
	static int firstpass = 1;
	static FILE *fp;
	char	xbuffer[1024];
	char	*tokens[15];
	int		tokcnt;

	if ( firstpass == 1 )
	{
		firstpass = 0;

		if (( fp = fopen ( Filename, "r" )) == NULL )
		{
			printf ( "Can not open file %s\n", Filename );
			exit ( 1 );
		}
	}

	rewind ( fp );

	while ( fgets ( xbuffer, sizeof(xbuffer), fp ) != NULL )
	{
		if (( tokcnt = GetTokensD ( xbuffer, "|\n\r", tokens, 15 )) < 11 )
		{
			continue;
		}

		if (( xfood.xfid = nsAtol ( tokens[0] )) != Fid )
		{
			continue;
		}

/*---------------------------------------------------------------------------
ID|name|FoodGroup|Calories|Carb|Protein|Fat|Sodium|Fiber|Weight|Serving|Length
168982|Blackberries Wild Raw (Alaska Native)|American Indian|81.64|15.45|1.32|1.68|9.42|5.02|157|1 cup|37
167633|Bread Kneel Down (Navajo)|American Indian|55.38|11.21|1.22|0.63|35.78|0.00|28.4|1 oz|25
---------------------------------------------------------------------------*/

		snprintf ( xfood.xfname, sizeof(xfood.xfname), "%s",  tokens[1] );
		snprintf ( xfood.xfserving, sizeof(xfood.xfserving), "%s",  tokens[10] );
		xfood.xfcalorie = nsAtof ( tokens[3] );
		xfood.xfcarb    = nsAtof ( tokens[4] );
		xfood.xfprotein = nsAtof ( tokens[5] );
		xfood.xffat     = nsAtof ( tokens[6] );
		xfood.xfsodium  = nsAtof ( tokens[7] );
		xfood.xffiber   = nsAtof ( tokens[8] );

		break;
	}

	return ( 0 );
}
