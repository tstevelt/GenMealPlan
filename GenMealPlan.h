
#include	<stdio.h>
#include	<stdlib.h>
#include	<unistd.h>
#include	<string.h>
#include	<ctype.h>
#include	<sys/types.h>
#include	<sys/socket.h>
#include	<netinet/in.h>
#include	<netinet/tcp.h>
#include	<arpa/inet.h>
#include	<netdb.h>
#include	<signal.h>
#include	<time.h>
#include	<errno.h>
#include	<math.h>

#include	"shslib.h"

#ifdef		HAVE_DATABASE
#include   <mysql/mysql.h>
#include   <mysql/errmsg.h>
#include	"dbylib.h"
#endif

#define		MEMBER
#define		FOOD
#define		HISTORY
#define		HISTFOOD
#define		RECIPE
#define		RECFOOD
#include	"filenutri.h"
#include	"nutrilib.h"

typedef struct
{
	long	Fid;
	double	Calorie;
	double	Carb;
	double	Protein;
	double	Fat;
	double	Sodium;
	double	Fiber;
	double	Sort;
} FOOD_RECORD;

TYPE	FOOD_RECORD		*FoodArray;
TYPE	int				FoodCount;
TYPE	int				FoodSize;

typedef struct
{
	FOOD_RECORD		MealArray[MAXFOODS];
	int		MealCount;
	double	MealScore;
	int		SelectedCount;
} POP_RECORD;

TYPE	int				MinFoods;
TYPE	int				MaxFoods;

TYPE	POP_RECORD		*PopArray;
TYPE	int				PopCount;
TYPE	int				PopSize;

TYPE	int				Generations;
TYPE	int				MajorCount;
TYPE	double			pCross;
TYPE	double			pMutation;
TYPE	int				Statistics;
TYPE	int				Verbose;
TYPE	char			Source;
TYPE	char			*Filename;
#define		DEBUG_CROSS		'C'
#define		DEBUG_MUTATE	'M'
#define		DEBUG_SELECTED	'S'
TYPE	int				Debug;

/*----------------------------------------------------------
	stats
----------------------------------------------------------*/
TYPE	double			MinScore;
TYPE	double			MaxScore;
TYPE	int				SameCrossCount;
TYPE	int				DiffCrossCount;
TYPE	int				NoCrossCount;
TYPE	int				MutateCount;

/*----------------------------------------------------------
    mysql and dbylib stuff
----------------------------------------------------------*/
#ifdef HAVE_DATABASE
TYPE  MYSQL   MySql;
TYPE    DBY_OPTIONS DbyOptions;
#endif
TYPE    char        Statement[2048];
TYPE    char        StatementOne[2048];
TYPE    char        WhereClause[1024];
TYPE    char        OrderByClause[1024];

/*----------------------------------------------------------
:.,$d
:r! mkproto -p *.c
----------------------------------------------------------*/

/* cmpscore.c */
int cmpscore ( POP_RECORD *a , POP_RECORD *b );

/* crossover.c */
void crossover ( POP_RECORD *Parent1 , POP_RECORD *Parent2 , POP_RECORD *Child1 , POP_RECORD *Child2 );

/* FindFood.c */
int FindFood ( long Fid );

/* GenMealPlan.c */
int main ( int argc , char *argv []);

/* getargs.c */
void getargs ( int argc , char *argv []);

/* initpop.c */
void initpop ( void );

/* LoadFoods.c */
void LoadFoods ( void );

/* LoadProfile.c */
void LoadProfile ( char *ProfileFilename );

/* obj_func.c */
double obj_func ( POP_RECORD *ptr );

/* PrintFuncs.c */
void PrintIndividual ( POP_RECORD *Individual , int Marker );
void PrintGeneration ( int Generation );

/* select_parents.c */
void select_parents ( int *Parent1 , int *Parent2 );
