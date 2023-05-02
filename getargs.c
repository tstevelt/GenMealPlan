
#include	"GenMealPlan.h"

static void Usage ()
{
#ifdef		HAVE_DATABASE
	printf ( "USAGE: GenMealPlan -member ID -db {common|all} [options]\n" );
	printf ( "       GenMealPlan -member ID -file filename   [options]\n" );
#else
	printf ( "USAGE: GenMealPlanNoDb -member profile.file -file food.file [options]\n" );
#endif
	printf ( " -minfoods #     (default 10, min %d)\n", MINFOODS );
	printf ( " -maxfoods #     (default 18, max %d)\n", MAXFOODS );
	printf ( " -generations #  (default 100)\n" );
	printf ( " -pcross #.##    (default 0.995)\n" );
	printf ( " -pmutate #.##   (default 0.05)\n" );
	printf ( " -major #        (default 10) how many time to load each set\n" );
	printf ( " -v              verbose\n" );
	printf ( " -s              print statistics\n" );
	printf ( " -d #            debug 1=cross 2=mutate 3=selected\n" );
	exit ( 1 );
}

void getargs ( int argc, char *argv[] )
{
	xmember.xmid = 0;
	MinFoods = 10;
	MaxFoods = 18;
	Generations = 100;
	MajorCount = 10;
	pMutation = 0.05;
	pCross = 0.995;
	Verbose = 0;
	Source = '?';
	Filename = NULL;
	Debug = 0;

	for ( int xa = 1; xa < argc; xa++ )
	{
		if ( xa + 1 < argc && nsStrcmp ( argv[xa], "-member" ) == 0 )
		{
			xa++;
#ifdef HAVE_DATABASE
			xmember.xmid = nsAtol ( argv[xa] );
#else
			LoadProfile ( argv[xa] );
#endif
		}
#ifdef HAVE_DATABASE
		else if ( xa + 1 < argc && nsStrcmp ( argv[xa], "-db" ) == 0 )
		{
			xa++;
			if ( nsStrcmp ( argv[xa], "common" ) == 0 )
			{
				Source = 'C';
			}
			else if ( nsStrcmp ( argv[xa], "all" ) == 0 )
			{
				Source = 'A';
			}
			else
			{
				Usage ();
			}

		}
#endif
		else if ( xa + 1 < argc && nsStrcmp ( argv[xa], "-file" ) == 0 )
		{
			Source = 'F';
			xa++;
			Filename = argv[xa];
		}
		else if ( xa + 1 < argc && nsStrcmp ( argv[xa], "-minfoods" ) == 0 )
		{
			xa++;
			MinFoods = nsAtoi ( argv[xa] );
		}
		else if ( xa + 1 < argc && nsStrcmp ( argv[xa], "-maxfoods" ) == 0 )
		{
			xa++;
			MaxFoods = nsAtoi ( argv[xa] );
		}
		else if ( xa + 1 < argc && nsStrcmp ( argv[xa], "-generations" ) == 0 )
		{
			xa++;
			Generations = nsAtoi ( argv[xa] );
		}
		else if ( xa + 1 < argc && nsStrcmp ( argv[xa], "-major" ) == 0 )
		{
			xa++;
			MajorCount = nsAtoi ( argv[xa] );
		}
		else if ( xa + 1 < argc && nsStrcmp ( argv[xa], "-pcross" ) == 0 )
		{
			xa++;
			pCross = nsAtof ( argv[xa] );
		}
		else if ( xa + 1 < argc && nsStrcmp ( argv[xa], "-pmutate" ) == 0 )
		{
			xa++;
			pMutation = nsAtof ( argv[xa] );
		}
		else if ( xa + 1 < argc && nsStrcmp ( argv[xa], "-d" ) == 0 )
		{
			xa++;
			switch ( argv[xa][0] )
			{
				case '1':
					Debug = DEBUG_CROSS;
					break;
				case '2':
					Debug = DEBUG_MUTATE;
					break;
				case '3':
					Debug = DEBUG_SELECTED;
					break;
				default:
					Usage ();
			}
		}
		else if ( nsStrcmp ( argv[xa], "-s" ) == 0 )
		{
			Statistics = 1;
		}
		else if ( nsStrcmp ( argv[xa], "-v" ) == 0 )
		{
			Verbose = 1;
		}
		else
		{
			Usage ();
		}
	}
	if ( xmember.xmid == 0 || Source == '?' )
	{
		printf ( "Unknown member or source\n" );
		Usage ();
	}

	if ( MinFoods > MaxFoods || MinFoods < MINFOODS || MaxFoods > MAXFOODS )
	{
		printf ( "Bad minfoods %d or maxfoods %d\n", MinFoods, MaxFoods );
		Usage ();
	}
}
