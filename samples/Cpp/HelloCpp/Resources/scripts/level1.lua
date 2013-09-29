rows = 7;
cols = 7;
-----------------------------------------------
-- background --
----------------------------------------------
luaLoadBackground("backgrounds/backgroung_new.png");
------------------------------------------------
-- settings --
------------------------------------------------
luaSetBoardSettings(rows, cols, -1, -1, 2, 2);
-----------------------------------------------
-- grid -- 
------------------------------------------------
for row = 0, rows - 1 do
  for col = 0, cols - 1 do 
    luaPopulateTile(row,   col,       2, 	2);
  end	
end
-------------------------------------------------
-- game types --
--------------------------------------------------
-- honey --
luaPopulateTile(5,   5,       1, 	1);
luaPopulateTile(4,   5,       1, 	1);
luaPopulateTile(4,   4,       1, 	1);
-- flowers --
luaPopulateTile(0,   0,       1, 	2);
luaPopulateTile(3,   2,       1, 	2);
luaPopulateTile(2,   2,       1, 	2);

-- actors --
luaPopulateTile(3,   4,       0, 	1);

