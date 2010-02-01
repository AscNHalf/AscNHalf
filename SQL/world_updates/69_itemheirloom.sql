ALTER TABLE items ADD COLUMN isheirloom BOOL NOT NULL DEFAULT false AFTER ArmorDamageModifier;
ALTER TABLE items ADD COLUMN ScalingStatDistribution SMALLINT(6) NOT NULL DEFAULT 0 AFTER isheirloom;
ALTER TABLE items ADD COLUMN ScalingStatValue INT(6) NOT NULL DEFAULT 0 AFTER ScalingStatDistribution;