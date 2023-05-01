#include	"GenMealPlan.h"

int cmpscore ( POP_RECORD *a, POP_RECORD *b )
{
	if ( a->MealScore < b->MealScore )
	{
		return ( -1 );
	}
	if ( a->MealScore > b->MealScore )
	{
		return ( 1 );
	}
	return ( 0 );
}
