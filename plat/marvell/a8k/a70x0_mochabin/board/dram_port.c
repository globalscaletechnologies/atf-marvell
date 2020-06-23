/*
 * Copyright (C) 2018 Marvell International Ltd.
 *
 * SPDX-License-Identifier:     BSD-3-Clause
 * https://spdx.org/licenses
 */

#include <arch_helpers.h>
#include <debug.h>
#include <mv_ddr_if.h>
#include <plat_marvell.h>

/*
 * This struct provides the DRAM training code with
 * the appropriate board DRAM configuration
 */
#if defined(_DDR4_1CS_4G)
static struct mv_ddr_topology_map board_topology_map_4g = {
/* a70x0_mocha: 8Gb x4 devices of micron - MT40A1G8WE-083E IT */
	DEBUG_LEVEL_ERROR,
	0x1, /* active interfaces */
	/* cs_mask, mirror, dqs_swap, ck_swap X subphys */
	{ { { {0x1, 0x2, 0, 0},
	      {0x1, 0x2, 0, 0},
	      {0x1, 0x2, 0, 0},
	      {0x1, 0x2, 0, 0},
	      {0x1, 0x2, 0, 0},
	      {0x1, 0x2, 0, 0},
	      {0x1, 0x2, 0, 0},
	      {0x1, 0x2, 0, 0},
	      {0x1, 0x2, 0, 0} },
	   SPEED_BIN_DDR_2400R,		/* speed_bin */
	   MV_DDR_DEV_WIDTH_8BIT,	/* sdram device width */
	   MV_DDR_DIE_CAP_8GBIT,	/* die capacity */
	   MV_DDR_FREQ_SAR,		/* frequency */
	   0, 0,			/* cas_l, cas_wl */
	   MV_DDR_TEMP_LOW} },		/* temperature */
	BUS_MASK_32BIT,	/* subphys mask */
	MV_DDR_CFG_DEFAULT,		/* ddr configuration data source */
	{ {0} },			/* raw spd data */
	{0},				/* timing parameters */
	{	/* electrical configuration */
		{	/* memory electrical configuration */
			MV_DDR_RTT_NOM_PARK_RZQ_DISABLE,	/* rtt_nom */
			{
				MV_DDR_RTT_NOM_PARK_RZQ_DIV4, /* rtt_park 1cs */
				MV_DDR_RTT_NOM_PARK_RZQ_DIV1  /* rtt_park 2cs */
			},
			{
				MV_DDR_RTT_WR_DYN_ODT_OFF,	/* rtt_wr 1cs */
				MV_DDR_RTT_WR_RZQ_DIV2		/* rtt_wr 2cs */
			},
			MV_DDR_DIC_RZQ_DIV7	/* dic */
		},
		{	/* phy electrical configuration */
			MV_DDR_OHM_30,	/* data_drv_p */
			MV_DDR_OHM_30,	/* data_drv_n */
			MV_DDR_OHM_30,	/* ctrl_drv_p */
			MV_DDR_OHM_30,	/* ctrl_drv_n */
			{
				MV_DDR_OHM_60,	/* odt_p 1cs */
				MV_DDR_OHM_120	/* odt_p 2cs */
			},
			{
				MV_DDR_OHM_60,	/* odt_n 1cs */
				MV_DDR_OHM_120	/* odt_n 2cs */
			},
		},
		{	/* mac electrical configuration */
			MV_DDR_ODT_CFG_NORMAL,		/* odtcfg_pattern */
			MV_DDR_ODT_CFG_ALWAYS_ON,	/* odtcfg_write */
			MV_DDR_ODT_CFG_NORMAL,		/* odtcfg_read */
		},
	}
};
#endif

#if defined(_DDR4_2CS_8G)
static struct mv_ddr_topology_map board_topology_map_8g = {
/* a70x0_mocha: 8Gb x8 devices of micron - MT40A1G8WE-083E IT */
	DEBUG_LEVEL_ERROR,
	0x1, /* active interfaces */
	/* cs_mask, mirror, dqs_swap, ck_swap X subphys */
	{ { { {0x3, 0x2, 0, 0},
	      {0x3, 0x2, 0, 0},
	      {0x3, 0x2, 0, 0},
	      {0x3, 0x2, 0, 0},
	      {0x3, 0x2, 0, 0},
	      {0x3, 0x2, 0, 0},
	      {0x3, 0x2, 0, 0},
	      {0x3, 0x2, 0, 0},
	      {0x3, 0x2, 0, 0} },
	   SPEED_BIN_DDR_2400R,		/* speed_bin */
	   MV_DDR_DEV_WIDTH_8BIT,	/* sdram device width */
	   MV_DDR_DIE_CAP_8GBIT,	/* die capacity */
	   MV_DDR_FREQ_SAR,		/* frequency */
	   0, 0,			/* cas_l, cas_wl */
	   MV_DDR_TEMP_LOW} },		/* temperature */
	BUS_MASK_32BIT,	/* subphys mask */
	MV_DDR_CFG_DEFAULT,		/* ddr configuration data source */
	{ {0} },			/* raw spd data */
	{0},				/* timing parameters */
	{	/* electrical configuration */
		{	/* memory electrical configuration */
			MV_DDR_RTT_NOM_PARK_RZQ_DISABLE,	/* rtt_nom */
			{
				MV_DDR_RTT_NOM_PARK_RZQ_DIV4, /* rtt_park 1cs */
				MV_DDR_RTT_NOM_PARK_RZQ_DIV1  /* rtt_park 2cs */
			},
			{
				MV_DDR_RTT_WR_DYN_ODT_OFF,	/* rtt_wr 1cs */
				MV_DDR_RTT_WR_RZQ_DIV2		/* rtt_wr 2cs */
			},
			MV_DDR_DIC_RZQ_DIV7	/* dic */
		},
		{	/* phy electrical configuration */
			MV_DDR_OHM_30,	/* data_drv_p */
			MV_DDR_OHM_30,	/* data_drv_n */
			MV_DDR_OHM_30,	/* ctrl_drv_p */
			MV_DDR_OHM_30,	/* ctrl_drv_n */
			{
				MV_DDR_OHM_60,	/* odt_p 1cs */
				MV_DDR_OHM_120	/* odt_p 2cs */
			},
			{
				MV_DDR_OHM_60,	/* odt_n 1cs */
				MV_DDR_OHM_120	/* odt_n 2cs */
			},
		},
		{	/* mac electrical configuration */
			MV_DDR_ODT_CFG_NORMAL,		/* odtcfg_pattern */
			MV_DDR_ODT_CFG_ALWAYS_ON,	/* odtcfg_write */
			MV_DDR_ODT_CFG_NORMAL,		/* odtcfg_read */
		},
	}
};
#endif

#if defined(_DDR4_1CS_2G)
static struct mv_ddr_topology_map board_topology_map_2g = {
/* a70x0_mocha: 4Gb x4 devices of SAMSUNG - K4A4G085WF */
	DEBUG_LEVEL_ERROR,
	0x1, /* active interfaces */
	/* cs_mask, mirror, dqs_swap, ck_swap X subphys */
	{ { { {0x1, 0x2, 0, 0},
	      {0x1, 0x2, 0, 0},
	      {0x1, 0x2, 0, 0},
	      {0x1, 0x2, 0, 0},
	      {0x1, 0x2, 0, 0},
	      {0x1, 0x2, 0, 0},
	      {0x1, 0x2, 0, 0},
	      {0x1, 0x2, 0, 0},
	      {0x1, 0x2, 0, 0} },
	   SPEED_BIN_DDR_2400R,		/* speed_bin */
	   MV_DDR_DEV_WIDTH_8BIT,	/* sdram device width */
	   MV_DDR_DIE_CAP_4GBIT,	/* die capacity */
	   MV_DDR_FREQ_SAR,		/* frequency */
	   0, 0,			/* cas_l, cas_wl */
	   MV_DDR_TEMP_LOW} },		/* temperature */
	BUS_MASK_32BIT,	/* subphys mask */
	MV_DDR_CFG_DEFAULT,		/* ddr configuration data source */
	{ {0} },			/* raw spd data */
	{0},				/* timing parameters */
	{	/* electrical configuration */
		{	/* memory electrical configuration */
			MV_DDR_RTT_NOM_PARK_RZQ_DISABLE,	/* rtt_nom */
			{
				MV_DDR_RTT_NOM_PARK_RZQ_DIV4, /* rtt_park 1cs */
				MV_DDR_RTT_NOM_PARK_RZQ_DIV1  /* rtt_park 2cs */
			},
			{
				MV_DDR_RTT_WR_DYN_ODT_OFF,	/* rtt_wr 1cs */
				MV_DDR_RTT_WR_RZQ_DIV2		/* rtt_wr 2cs */
			},
			MV_DDR_DIC_RZQ_DIV7	/* dic */
		},
		{	/* phy electrical configuration */
			MV_DDR_OHM_30,	/* data_drv_p */
			MV_DDR_OHM_30,	/* data_drv_n */
			MV_DDR_OHM_30,	/* ctrl_drv_p */
			MV_DDR_OHM_30,	/* ctrl_drv_n */
			{
				MV_DDR_OHM_60,	/* odt_p 1cs */
				MV_DDR_OHM_120	/* odt_p 2cs */
			},
			{
				MV_DDR_OHM_60,	/* odt_n 1cs */
				MV_DDR_OHM_120	/* odt_n 2cs */
			},
		},
		{	/* mac electrical configuration */
			MV_DDR_ODT_CFG_NORMAL,		/* odtcfg_pattern */
			MV_DDR_ODT_CFG_ALWAYS_ON,	/* odtcfg_write */
			MV_DDR_ODT_CFG_NORMAL,		/* odtcfg_read */
		},
	}
};
#endif

struct mv_ddr_topology_map *mv_ddr_topology_map_get(void)
{
/* a70x0_mochabin board ddr supports 3 models (2G/1CS, 4G/1CS, 8G/2CS) */
#if defined(_DDR4_1CS_4G)
	return &board_topology_map_4g;
#elif defined(_DDR4_2CS_8G)
	return &board_topology_map_8g;
#elif defined(_DDR4_1CS_2G)
	return &board_topology_map_2g;
#else
	#error "unknown ddr topology"
#endif
}

/*
 * This function may modify the default DRAM parameters
 * based on information received from SPD or bootloader
 * configuration located on non volatile storage
 */
void plat_marvell_dram_update_topology(void)
{
}
