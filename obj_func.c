
#include	"GenMealPlan.h"

double obj_func ( POP_RECORD *ptr )
{
	double	MealCalorie, MealCarb, MealProtein, MealFat, MealSodium, MealFiber;
	double	RatioCalorie, RatioCarb, RatioProtein, RatioFat, RatioSodium, RatioFiber;
	double	rv = 0.0;

	MealCalorie = MealCarb = MealProtein = MealFat = MealSodium = MealFiber = 0.0;

	for ( int xf = 0; xf < ptr->MealCount; xf++ )
	{
		MealCalorie += ptr->MealArray[xf].Calorie;
		MealCarb    += ptr->MealArray[xf].Carb;
		MealProtein += ptr->MealArray[xf].Protein;
		MealFat     += ptr->MealArray[xf].Fat;
		MealSodium  += ptr->MealArray[xf].Sodium;
		MealFiber   += ptr->MealArray[xf].Fiber;
	}

	RatioCalorie = fabs(MealCalorie - xmember.xmcalorie) / (double)xmember.xmcalorie;
	RatioCarb    = fabs(MealCarb    - xmember.xmcarb   ) / (double)xmember.xmcarb;
	RatioProtein = fabs(MealProtein - xmember.xmprotein) / (double)xmember.xmprotein;
	RatioFat     = fabs(MealFat     - xmember.xmfat    ) / (double)xmember.xmfat;
	RatioSodium  = fabs(MealSodium  - xmember.xmsodium ) / (double)xmember.xmsodium;
	RatioFiber   = fabs(MealFiber   - xmember.xmfiber  ) / (double)xmember.xmfiber;

	rv = (RatioCalorie + RatioCarb + RatioProtein + RatioFat + RatioSodium + RatioFiber ) / 6.0;
	// rv = (RatioCalorie + RatioCarb + RatioProtein + RatioFat + RatioSodium + RatioFiber ) / ( ptr->MealCount );

	return ( rv );
}
