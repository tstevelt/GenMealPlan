/*----------------------------------------------------------------------------
	Program : obj_func.c
	Author  : Tom Stevelt
	Date    : 2023-2024
	Synopsis: GA objective function.
	Return  : 
----------------------------------------------------------------------------*/
// 	Copyright © 2023-2024 Tom Stevelt
// 	Tom Stevelt <tstevelt@silverhammersoftware.com>
// 	This software is free software; you can redistribute it and/or modify
// 	it under the terms of the MIT license. See LICENSE for details.

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

	RatioCalorie = fabs(MealCalorie - xmember.xmcalorie + FTD_Calorie) / (double)xmember.xmcalorie;
	RatioCarb    = fabs(MealCarb    - xmember.xmcarb    + FTD_Carb   ) / (double)xmember.xmcarb;
	RatioProtein = fabs(MealProtein - xmember.xmprotein + FTD_Protein) / (double)xmember.xmprotein;
	RatioFat     = fabs(MealFat     - xmember.xmfat     + FTD_Fat    ) / (double)xmember.xmfat;
	RatioSodium  = fabs(MealSodium  - xmember.xmsodium  + FTD_Sodium ) / (double)xmember.xmsodium;
	RatioFiber   = fabs(MealFiber   - xmember.xmfiber   + FTD_Fiber  ) / (double)xmember.xmfiber;

	rv = (RatioCalorie + RatioCarb + RatioProtein + RatioFat + RatioSodium + RatioFiber ) / 6.0;

	return ( rv );
}
