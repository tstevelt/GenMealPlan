-- 
-- ID|name|FoodGroup|Calories|Carb|Protein|Fat|Sodium|Fiber|Weight|Serving|Length
--

select Fid, Fname, Fgroup, Fcalorie, Fcarb, Fprotein, Ffat, Fsodium, Ffiber, '1', Fserving, '10'
 from food
 where Fcalorie > 0 and Fprotein > 0 and Ffiber > 0 ;



