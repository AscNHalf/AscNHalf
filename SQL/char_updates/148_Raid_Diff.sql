ALTER TABLE `characters` ADD `raiddifficulty` int(10) NOT NULL DEFAULT '0' after `difficulty`;
ALTER TABLE `groups` ADD `raiddifficulty` int(10) NOT NULL DEFAULT '0' after `difficulty`;
ALTER TABLE `achievements` ADD `groupid` int(11) NOT NULL DEFAULT '0' after `completed`;