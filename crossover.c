
#include	"GenMealPlan.h"

void crossover ( POP_RECORD *Parent1, POP_RECORD *Parent2, POP_RECORD *Child1, POP_RECORD *Child2 )
{
	int		Minimum, xsite, ndx;

	if ( Parent1->MealCount < Parent2->MealCount )
	{
		Minimum = Parent1->MealCount;
	}
	else
	{
		Minimum = Parent2->MealCount;
	}

	if ( flip(pCross) == 1 )
	{
		xsite = random_range ( 1, Minimum - 1 );

		Parent1->SelectedCount++;
		Parent2->SelectedCount++;

		/*---------------------------------------------------------------------------
			parent1  aaaaaaaaaaa aaaaaaaaaaaaaaaaaaaaaaaaaa
			parent2  bbbbbbbbbbb bbbbbbbbbbbbbbbb
			child1   aaaaaaaaaaa bbbbbbbbbbbbbbbb
			child2   bbbbbbbbbbb aaaaaaaaaaaaaaaaaaaaaaaaaa

			parent1  aaaaaaaaaaa aaaaaaaaaaaaaaaa
			parent2  bbbbbbbbbbb bbbbbbbbbbbbbbbbbbbbbbbbbb
			child1   aaaaaaaaaaa bbbbbbbbbbbbbbbbbbbbbbbbbb
			child2   bbbbbbbbbbb aaaaaaaaaaaaaaaa
		---------------------------------------------------------------------------*/
		if ( Debug == DEBUG_CROSS )
		{
			printf ( "-- cross %d --\n", SameCrossCount+DiffCrossCount+1 );
			PrintIndividual ( Parent1, xsite );
			PrintIndividual ( Parent2, xsite );
		}
		for ( ndx = 0; ndx < xsite; ndx++ )
		{
			memcpy ( &Child1->MealArray[ndx], &Parent1->MealArray[ndx], sizeof(FOOD_RECORD) );
			memcpy ( &Child2->MealArray[ndx], &Parent2->MealArray[ndx], sizeof(FOOD_RECORD) );
		}

		Child1->MealCount = Parent2->MealCount;
		for ( ndx = xsite; ndx < Child1->MealCount; ndx++ )
		{
			memcpy ( &Child1->MealArray[ndx], &Parent2->MealArray[ndx], sizeof(FOOD_RECORD) );
		}

		Child2->MealCount = Parent1->MealCount;
		for ( ndx = xsite; ndx < Child2->MealCount; ndx++ )
		{
			memcpy ( &Child2->MealArray[ndx], &Parent1->MealArray[ndx], sizeof(FOOD_RECORD) );
		}
		if ( Debug == DEBUG_CROSS )
		{
			PrintIndividual ( Child1, xsite );
			PrintIndividual ( Child2, xsite );
		}
		if ( Child1->MealCount == Child2->MealCount )
		{
			SameCrossCount++;
		}
		else
		{
			DiffCrossCount++;
		}
	}
	else
	{
		//if ( Verbose )
		//{
		//	printf ( "No cross, meal sizes %d and %d\n", Parent1->MealCount, Parent2->MealCount );
		//}
		for ( ndx = 0; ndx < Parent1->MealCount; ndx++ )
		{
			memcpy ( &Child1->MealArray[ndx], &Parent1->MealArray[ndx], sizeof(FOOD_RECORD) );
		}
		Child1->MealCount = Parent1->MealCount;
		for ( ndx = 0; ndx < Parent2->MealCount; ndx++ )
		{
			memcpy ( &Child2->MealArray[ndx], &Parent2->MealArray[ndx], sizeof(FOOD_RECORD) );
		}
		Child2->MealCount = Parent2->MealCount;
		NoCrossCount++;
	}

	if ( flip(pMutation) == 1 )
	{
		int		xm = 0;

#ifdef MUTATE_BY_REMOVAL
		/*----------------------------------------------------------
			remove last food from each child
		----------------------------------------------------------*/
		if ( Child1->MealCount > MinFoods )
		{
			xsite = Child1->MealCount - 1;
			memset ( &Child1->MealArray[xsite], '\0', sizeof(FOOD_RECORD) );
			Child1->MealCount--;
			xm++;
		}
		if ( Child2->MealCount > MinFoods )
		{
			xsite = Child2->MealCount - 1;
			memset ( &Child2->MealArray[xsite], '\0', sizeof(FOOD_RECORD) );
			Child2->MealCount--;
			xm++;
		}
#endif

#define MUTATE_BY_NEW_FOOD
#ifdef MUTATE_BY_NEW_FOOD
		/*----------------------------------------------------------
			function InArray() used to make sure new food is not
			already in the individual chromosome
		----------------------------------------------------------*/
		int InArray ( FOOD_RECORD Array[], int Count, long Value )
		{
			for ( int xi = 0; xi < Count; xi++ )
			{
				if ( Array[xi].Fid == Value )
				{
					return ( 1 );
				}
			}
			return ( 0 );
		}

		do
		{
			ndx = random_range ( 0, FoodCount-1 );
		} while ( InArray ( Child1->MealArray, Child1->MealCount, FoodArray[ndx].Fid ) == 1 );

		if ( Debug == DEBUG_MUTATE )
		{
			printf ( "-- mutate %d --\n", MutateCount+1 );
			PrintIndividual ( Child1, 0 );
		}
		xsite = random_range ( 0, Child1->MealCount-1 );
		memcpy ( &Child1->MealArray[xsite], &FoodArray[ndx], sizeof(FOOD_RECORD) );
		if ( Debug == DEBUG_MUTATE )
		{
			PrintIndividual ( Child1, 0 );
		}

		do
		{
			ndx = random_range ( 0, FoodCount-1 );
		} while ( InArray ( Child2->MealArray, Child2->MealCount, FoodArray[ndx].Fid ) == 1 );

		if ( Debug == DEBUG_MUTATE )
		{
			PrintIndividual ( Child2, 0 );
		}
		xsite = random_range ( 0, Child2->MealCount-1 );
		memcpy ( &Child2->MealArray[xsite], &FoodArray[ndx], sizeof(FOOD_RECORD) );
		if ( Debug == DEBUG_MUTATE )
		{
			PrintIndividual ( Child2, 0 );
		}

		xm = 1;

#endif

		if ( xm )
		{
			MutateCount++;
		}
	}
}
