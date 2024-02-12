obj-$(CONFIG_HISI_HKADC) += adc/
obj-$(CONFIG_HISI_CCI_EXTRA)		+= cci_extra/
obj-$(CONFIG_HISI_CMDLINE_PARSE)	+= cmdline/
obj-$(CONFIG_HISILICON_PLATFORM_MAILBOX)	+= mailbox/
obj-$(CONFIG_HI6402_CODEC)			+= hi64xx/
obj-$(CONFIG_HI6403_CODEC)			+= hi64xx/
obj-$(CONFIG_HIFI_DSP_ONE_TRACK)		+= hifi_dsp/
obj-$(CONFIG_SOUND_TRIGGER)			+= soundtrigger/
obj-$(CONFIG_HIFI_MAILBOX)			+= hifi_mailbox/
obj-$(CONFIG_HISILICON_PLATFORM_MAINTAIN) += mntn/
obj-$(CONFIG_HISILICON_PLATFORM_KERNELDUMP) += memory_dump/
obj-$(CONFIG_HISILICON_PLATFORM_DDRC)   += ddrc/
obj-$(CONFIG_HISI_NOC)	+= noc/
obj-$(CONFIG_HISI_SYSCOUNTER) += hisi_syscounter/
obj-$(CONFIG_HISILICON_PLATFORM_SLIMBUS)+= slimbus/
obj-$(CONFIG_HI6402_HIFI_MISC) += hi64xx_dsp/

ifneq ($(strip $(CFG_HISI_OPENSOURCE)), true)
endif
obj-$(CONFIG_HISI_HISTAR_ISP) += isp/
obj-$(CONFIG_DRMDRIVER)                         += drmdriver/
obj-$(CONFIG_HI3XXX_EFUSE)                      += efuse/
obj-$(CONFIG_HISI_CMA)                          += hisi_cma/
obj-y                                           += tzdriver/
obj-$(CONFIG_HISI_LB)                           += hisi_lb/
obj-$(CONFIG_LOAD_IMAGE) += load_image/
obj-$(CONFIG_HISI_SECS_CTRL) += secs_power_ctrl/
obj-$(CONFIG_HISI_SR)                      += pm/
obj-$(CONFIG_HISI_GPUFREQ)                 += gpufreq/
ifneq ($(link_kernel),false)
ifneq (,$(findstring $(CONFIG_HISI_BALONG_MODEM),y m))
obj-y += modem/
endif
endif

obj-$(CONFIG_HISI_AXI) += axi/
obj-$(CONFIG_HISI_PERFHUB) += perfhub/
obj-$(CONFIG_HISI_TIMEKEEPER) += timekeeper/
