ALTER TABLE `characters` ADD `customizable` int(3) NOT NULL DEFAULT '0' after `gender`,
ADD `xp_off` int(3) NOT NULL DEFAULT '0' after `level`;