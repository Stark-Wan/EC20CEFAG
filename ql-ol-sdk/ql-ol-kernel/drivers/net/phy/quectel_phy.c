/**
 * @file quectel_phy.c
 * @brief Quectel PHY driver.
 * 
 * @note
 */
/*=============================================================================
  Copyright (c) 2018 Quectel Wireless Solution, Co., Ltd.  All Rights Reserved.
  Quectel Wireless Solution Proprietary and Confidential.
=============================================================================*/

/*=====================================================================

                          EDIT HISTORY FOR MODULE
  
  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.
  
  WHEN             WHO         WHAT, WHERE, WHY
  ------------     -------     ----------------------------------------
  07/24/2018       Mike        Support dp83tc811s-q1(TI) PHY
=======================================================================*/

#include <linux/phy.h>
#include <linux/module.h>
#include <linux/string.h>
#include <linux/netdevice.h>
#include <linux/etherdevice.h>
#include <linux/module.h>
#include <linux/quectel_phy.h>

static unsigned phy_speed = SPEED_1000;
module_param(phy_speed, uint, 0644);
static unsigned phy_debug = 0;
module_param(phy_debug, uint, 0644);

#define quecphy_debug(phydev) do {					\
		if (phy_debug) {					\
			dev_info(&phydev->dev, "%s\n", __func__);	\
			quecphy_dump(phydev);				\
		}							\
	} while(0)

static void quecphy_dump(const struct phy_device *phydev)
{
	dev_info(&phydev->dev, "state=%d, link=%d, autoneg=%d, speed=%d, duplex=%d, pause=%d, asym_pause=%d",
		 phydev->state, phydev->link, phydev->autoneg,
		 phydev->speed, phydev->duplex, phydev->pause, phydev->asym_pause);
}

static ssize_t phy_state_show(struct device *dev, struct device_attribute *attr, char *buf)
{
	struct phy_device *phydev = to_phy_device(dev);
	return sprintf(buf, "0x%.8lx\n", (unsigned long)phydev->phy_id);
}
static DEVICE_ATTR_RO(phy_state);

int quecphy_config_aneg(struct phy_device *phydev)
{
	quecphy_debug(phydev);
    
	return 0;
}

static int quecphy_read_status(struct phy_device *phydev)
{
	//phy_state_machine() call me per 1 seconds
	int ret = 0;
    
	if (!phydev->link) {
		phydev->link = 1;
		phydev->speed = phy_speed;
		phydev->duplex = DUPLEX_FULL;
		phydev->autoneg = AUTONEG_DISABLE;
		phydev->pause = 0;
		phydev->asym_pause = 0;
	}

	quecphy_debug(phydev);
	return ret;
}

static int quecphy_aneg_done(struct phy_device *phydev)
{
	quecphy_debug(phydev);

	return BMSR_ANEGCOMPLETE;
}

static int quecphy_config_init(struct phy_device *phydev)
{
	quecphy_debug(phydev);
	return 0;
}

static int quecphy_soft_reset(struct phy_device *phydev)
{    
	quecphy_debug(phydev);
	if (phydev->phy_id != QUECTEL_PHY_ID)
		genphy_soft_reset(phydev);

	if (phydev->phy_id == BCM89820_PHY_ID) {
		phy_write(phydev, 0x00, 0x0200);  //0x0208~masterm,0x0200~slave
	} else if (phydev->phy_id == DP83TC811S_PHY_ID) {
		/* Link up PHY */
		phy_write(phydev, 0x01, 0x0065);

		/* Sets slave mode */
		phy_write(phydev, 0x0d, 0x0001);
		phy_write(phydev, 0x0e, 0x0834);
		phy_write(phydev, 0x0d, 0x4001);
		phy_write(phydev, 0x0e, 0x8000);
	} 
	return 0;
}


static int quecphy_match_phy_device(struct phy_device *phydev) {
	dev_info(&phydev->dev, "phy_id=0x%08x\n", phydev->phy_id);
    
	if (phydev->phy_id == BCM89820_PHY_ID || phydev->phy_id == DP83TC811S_PHY_ID)
		phy_speed = SPEED_100;

	return 1;
}

static int quecphy_probe(struct phy_device *phydev)
{
	device_create_file(&phydev->dev, &dev_attr_phy_state);
	return 0;
}

static void quecphy_remove(struct phy_device *phydev)
{
	return;
}

static struct phy_driver quecphy_driver = {
	.phy_id			= 0x12345678,
	.name			= "Quectel PHY",
	.phy_id_mask		= 0xffffffff,
	.match_phy_device       = quecphy_match_phy_device,
	.probe			= quecphy_probe,
	.soft_reset             = quecphy_soft_reset,
	.config_init		= quecphy_config_init,
	.features		= PHY_GBIT_FEATURES,
	.flags			= 0,
	.config_aneg		= quecphy_config_aneg,
	.read_status		= quecphy_read_status,
	.aneg_done		= quecphy_aneg_done,
	.remove			= quecphy_remove,
	.driver		        = { .owner = THIS_MODULE },
};

static int __init quecphy_init(void)
{
	return phy_driver_register(&quecphy_driver);
}

static void __exit quecphy_exit(void)
{
	phy_driver_unregister(&quecphy_driver);
}

module_init(quecphy_init);
module_exit(quecphy_exit);
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:quecphy");
