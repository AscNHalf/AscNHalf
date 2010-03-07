ALTER TABLE `creature_proto` ADD `powertype` int(11) NOT NULL DEFAULT '0' after `maxhealth`;
ALTER TABLE `creature_proto_heroic` ADD `powertype` int(11) NOT NULL DEFAULT '0' after `maxdmg`;
ALTER TABLE `creature_proto` CHANGE mana `power` int(10);
ALTER TABLE `creature_proto_heroic` CHANGE mana `power` int(10);