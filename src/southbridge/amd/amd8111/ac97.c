/*
 * This file is part of the coreboot project.
 *
 * (C) 2003 Linux Networx
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include <console/console.h>
#include <device/device.h>
#include <device/pci.h>
#include <device/pci_ids.h>
#include <device/pci_ops.h>
#include "amd8111.h"

static void lpci_set_subsystem(struct device *dev, unsigned vendor,
			       unsigned device)
{
	pci_write_config32(dev, 0x2c,
		((device & 0xffff) << 16) | (vendor & 0xffff));
}

static struct pci_operations lops_pci = {
	.set_subsystem = lpci_set_subsystem,
};

static struct device_operations ac97audio_ops  = {
	.read_resources   = pci_dev_read_resources,
	.set_resources    = pci_dev_set_resources,
	.enable_resources = pci_dev_enable_resources,
	.enable           = amd8111_enable,
	.init             = 0,
	.scan_bus         = 0,
	.ops_pci          = &lops_pci,
};

static const struct pci_driver ac97audio_driver __pci_driver = {
	.ops    = &ac97audio_ops,
	.vendor = PCI_VENDOR_ID_AMD,
	.device = 0x746D,
};


static struct device_operations ac97modem_ops  = {
	.read_resources   = pci_dev_read_resources,
	.set_resources    = pci_dev_set_resources,
	.enable_resources = pci_dev_enable_resources,
	.enable           = amd8111_enable,
	.init             = 0,
	.scan_bus         = 0,
	.ops_pci          = &lops_pci,
};

static const struct pci_driver ac97modem_driver __pci_driver = {
	.ops    = &ac97modem_ops,
	.vendor = PCI_VENDOR_ID_AMD,
	.device = 0x746E,
};
