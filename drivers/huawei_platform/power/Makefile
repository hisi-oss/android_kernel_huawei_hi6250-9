obj-$(CONFIG_HUAWEI_CHARGER)	+= charger/
obj-$(CONFIG_HUAWEI_KSTATE)	+= hw_kstate/
obj-$(CONFIG_HUAWEI_SMPL)	+= smpl/
obj-$(CONFIG_HUAWEI_USB_SHORT_CIRCUIT_PROTECT)	+= usb_short_circuit_protect/
obj-$(CONFIG_HUAWEI_DSM)	+= power_dsm/
obj-$(CONFIG_HUAWEI_POWER_THERMALZONE)	+= power_thermalzone/
obj-$(CONFIG_HUAWEI_SOC_CONTROL) += hardware_monitor/

ifeq ($(HLTHERM_RUNTEST),true)
CFLAGS_KERNEL += -DCONFIG_HLTHERM_RUNTEST
endif

obj-$(CONFIG_DOZE_FILTER)	+= wifi_filter/
