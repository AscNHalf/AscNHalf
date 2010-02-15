-- minmoney and maxmoney = -1     <- no money drop
-- minmoney and maxmoney = 0      <- calculate money
-- minmoney -1 , maxmoney 0 	  <- no money drop
-- minmoney 0 , maxmoney -1       <- no money drop
-- minmoney > 0 and maxmoney > 0  <- moneydrop >= minmoney , moneydrop <= maxmoney  

ALTER TABLE `creature_proto` CHANGE money `minmoney` int(30); 
ALTER TABLE `creature_proto` add column `maxmoney` int(30)  DEFAULT '0' after `minmoney`;

-- apply this only one first time.. later databases should have this already set correct
-- UPDATE creature_proto SET maxmoney = minmoney;