-- 	Copyright © 2023-2024 Tom Stevelt
-- 	Tom Stevelt <tstevelt@silverhammersoftware.com>
-- 	This software is free software; you can redistribute it and/or modify
-- 	it under the terms of the MIT license. See LICENSE for details.
-- 
-- ID|name|FoodGroup|Calories|Carb|Protein|Fat|Sodium|Fiber|Weight|Serving|Length
--

select Fid, Fname, Fgroup, Fcalorie, Fcarb, Fprotein, Ffat, Fsodium, Ffiber, '1', Fserving, '10'
 from food
 where Fcalorie > 0 and Fprotein > 0 and Ffiber > 0 ;



