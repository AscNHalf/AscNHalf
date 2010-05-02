-- Add new columns --
ALTER TABLE `objectloot` CHANGE percentchance `difficulty0percentchance` float;
ALTER TABLE `objectloot` CHANGE heroicpercentchance `difficulty1percentchance` float;
ALTER TABLE `objectloot` ADD `difficulty2percentchance` float NOT NULL DEFAULT '0' after `difficulty1percentchance`;
ALTER TABLE `objectloot` ADD `difficulty3percentchance` float NOT NULL DEFAULT '0' after `difficulty2percentchance`;
ALTER TABLE `creatureloot` CHANGE percentchance `difficulty0percentchance` float;
ALTER TABLE `creatureloot` CHANGE heroicpercentchance `difficulty1percentchance` float;
ALTER TABLE `creatureloot` ADD `difficulty2percentchance` float NOT NULL DEFAULT '0' after `difficulty1percentchance`;
ALTER TABLE `creatureloot` ADD `difficulty3percentchance` float NOT NULL DEFAULT '0' after `difficulty2percentchance`;
ALTER TABLE `creatureloot_gathering` CHANGE percentchance `difficulty0percentchance` float;
ALTER TABLE `creatureloot_gathering` CHANGE heroicpercentchance `difficulty1percentchance` float;
ALTER TABLE `creatureloot_gathering` ADD `difficulty2percentchance` float NOT NULL DEFAULT '0' after `difficulty1percentchance`;
ALTER TABLE `creatureloot_gathering` ADD `difficulty3percentchance` float NOT NULL DEFAULT '0' after `difficulty2percentchance`;