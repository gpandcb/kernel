/*
 * Support for Intel Camera Imaging ISP subsystem.
 *
 * Copyright (c) 2010 - 2014 Intel Corporation. All Rights Reserved.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License version
 * 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 *
 */

#ifndef __INPUT_SYSTEM_GLOBAL_H_INCLUDED__
#define __INPUT_SYSTEM_GLOBAL_H_INCLUDED__

#define IS_INPUT_SYSTEM_VERSION_VERSION_2401

/* CSI reveiver has 3 ports. */
#define		N_CSI_PORTS (3)

#include "isys_dma.h"		/*	isys2401_dma_channel,
				 *	isys2401_dma_cfg_t
				 */

#include "ibuf_ctrl.h"		/*	ibuf_cfg_t,
				 *	ibuf_ctrl_cfg_t
				 */

#include "isys_stream2mmio.h"	/*	stream2mmio_cfg_t */

#include "csi_rx.h"		/*	csi_rx_frontend_cfg_t,
				 *	csi_rx_backend_cfg_t,
				 *	csi_rx_backend_lut_entry_t
				 */
#include "pixelgen.h"


#define INPUT_SYSTEM_N_STREAM_ID  6	/* maximum number of simultaneous
					virtual channels supported*/

typedef enum {
	INPUT_SYSTEM_ERR_NO_ERROR = 0,
	INPUT_SYSTEM_ERR_CREATE_CHANNEL_FAIL,
	INPUT_SYSTEM_ERR_CONFIGURE_CHANNEL_FAIL,
	INPUT_SYSTEM_ERR_OPEN_CHANNEL_FAIL,
	INPUT_SYSTEM_ERR_TRANSFER_FAIL,
	INPUT_SYSTEM_ERR_CREATE_INPUT_PORT_FAIL,
	INPUT_SYSTEM_ERR_CONFIGURE_INPUT_PORT_FAIL,
	INPUT_SYSTEM_ERR_OPEN_INPUT_PORT_FAIL,
	N_INPUT_SYSTEM_ERR
} input_system_err_t;

typedef enum {
	INPUT_SYSTEM_SOURCE_TYPE_UNDEFINED = 0,
	INPUT_SYSTEM_SOURCE_TYPE_SENSOR,
	INPUT_SYSTEM_SOURCE_TYPE_TPG,
	INPUT_SYSTEM_SOURCE_TYPE_PRBS,
	N_INPUT_SYSTEM_SOURCE_TYPE
} input_system_source_type_t;

typedef struct input_system_channel_s input_system_channel_t;
struct input_system_channel_s {
	stream2mmio_ID_t	stream2mmio_id;
	stream2mmio_sid_ID_t	stream2mmio_sid_id;

	ibuf_ctrl_ID_t		ibuf_ctrl_id;
	ib_buffer_t		ib_buffer;

	isys2401_dma_ID_t	dma_id;
	isys2401_dma_channel	dma_channel;
};

typedef struct input_system_channel_cfg_s input_system_channel_cfg_t;
struct input_system_channel_cfg_s {
	stream2mmio_cfg_t	stream2mmio_cfg;
	ibuf_ctrl_cfg_t		ibuf_ctrl_cfg;
	isys2401_dma_cfg_t	dma_cfg;
	isys2401_dma_port_cfg_t	dma_src_port_cfg;
	isys2401_dma_port_cfg_t	dma_dest_port_cfg;
};

typedef struct input_system_input_port_s input_system_input_port_t;
struct input_system_input_port_s {
	input_system_source_type_t	source_type;

	struct {
		csi_rx_frontend_ID_t		frontend_id;
		csi_rx_backend_ID_t		backend_id;
		csi_mipi_packet_type_t		packet_type;
		csi_rx_backend_lut_entry_t	backend_lut_entry;
	} csi_rx;

	struct {
		csi_mipi_packet_type_t		packet_type;
		csi_rx_backend_lut_entry_t	backend_lut_entry;
	} metadata;

	struct {
		pixelgen_ID_t			pixelgen_id;
	} pixelgen;
};

typedef struct input_system_input_port_cfg_s input_system_input_port_cfg_t;
struct input_system_input_port_cfg_s {
	struct {
		csi_rx_frontend_cfg_t	frontend_cfg;
		csi_rx_backend_cfg_t	backend_cfg;
		csi_rx_backend_cfg_t	md_backend_cfg;
	} csi_rx_cfg;

	struct {
		pixelgen_tpg_cfg_t	tpg_cfg;
		pixelgen_prbs_cfg_t	prbs_cfg;
	} pixelgen_cfg;
};

typedef struct input_system_cfg_s input_system_cfg_t;
struct input_system_cfg_s {
	input_system_input_port_ID_t	input_port_id;

	input_system_source_type_t	mode;

	bool online;
	bool raw_packed;
	int8_t linked_isys_stream_id;

	struct {
		bool	comp_enable;
		int32_t	active_lanes;
		int32_t	fmt_type;
		int32_t	ch_id;
		int32_t comp_predictor;
		int32_t comp_scheme;
	} csi_port_attr;

	pixelgen_tpg_cfg_t	tpg_port_attr;

	pixelgen_prbs_cfg_t prbs_port_attr;

	struct {
		int32_t align_req_in_bytes;
		int32_t bits_per_pixel;
		int32_t pixels_per_line;
		int32_t lines_per_frame;
	} input_port_resolution;

	struct {
		int32_t left_padding;
		int32_t max_isp_input_width;
	} output_port_attr;

	struct {
		bool    enable;
		int32_t fmt_type;
		int32_t align_req_in_bytes;
		int32_t bits_per_pixel;
		int32_t pixels_per_line;
		int32_t lines_per_frame;
	} metadata;
};

typedef struct virtual_input_system_stream_s virtual_input_system_stream_t;
struct virtual_input_system_stream_s {
	uint8_t enable_metadata;
	input_system_input_port_t	input_port;
	input_system_channel_t		channel;
	input_system_channel_t		md_channel; /* metadata channel */
	uint8_t online;
	int8_t linked_isys_stream_id;
	uint8_t valid;
};

typedef struct virtual_input_system_stream_cfg_s virtual_input_system_stream_cfg_t;
struct virtual_input_system_stream_cfg_s {
	uint8_t enable_metadata;
	input_system_input_port_cfg_t	input_port_cfg;
	input_system_channel_cfg_t	channel_cfg;
	input_system_channel_cfg_t	md_channel_cfg;
	uint8_t valid;
};

#define ISP_INPUT_BUF_START_ADDR	0
#define NUM_OF_INPUT_BUF		2
#define NUM_OF_LINES_PER_BUF		2
#define LINES_OF_ISP_INPUT_BUF		(NUM_OF_INPUT_BUF * NUM_OF_LINES_PER_BUF)
#define ISP_INPUT_BUF_STRIDE		SH_CSS_MAX_SENSOR_WIDTH


#endif /* __INPUT_SYSTEM_GLOBAL_H_INCLUDED__ */
