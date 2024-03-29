#ifndef HISI_USB_OTG_TYPE_H
#define HISI_USB_OTG_TYPE_H
#include <linux/wakelock.h>
#include <linux/notifier.h>
#include <linux/hisi/usb/hisi_usb.h>
#include <linux/regulator/consumer.h>
#include <linux/clk.h>
#include <linux/platform_device.h>

/**
 * usb otg ahbif registers definations
 */
union usbotg2_ctrl0 {
	uint32_t reg;
	struct {
		uint32_t  idpullup_sel:1;  /* bit[0]    : ID???????????????????????????
							 0???????????????
							 1???????????? */
		uint32_t  idpullup:1;  /* bit[1]    : ID?????????????????? */
		uint32_t  acaenb_sel:1;  /* bit[2]    : ACA???????????????????????????
							 0????????????
							 1???????????? */
		uint32_t  acaenb:1;  /* bit[3]    : ACA???????????? */
		uint32_t  id_sel:2;  /* bit[4-5]  : ACA?????????????????????
							 00?????????????????????
							 01?????????PHY???iddig???
							 10?????????PHY???ACA?????????
							 ??????????????? */
		uint32_t  id:1;  /* bit[6]    : ?????????????????? */
		uint32_t  drvvbus_sel:1;  /* bit[7]    : ??????vbus???????????????
							 0?????????????????????
							 1?????????????????? */
		uint32_t  drvvbus:1;  /* bit[8]    : ??????vbus???????????? */
		uint32_t  vbusvalid_sel:1;  /* bit[9]    : ????????????vbusvalid?????????????????????
							 0?????????PHY?????????vbusvalid;
							 1??????????????????drvvbus?????? */
		uint32_t  sessvld_sel:1;  /* bit[10]   : ????????????sessvld?????????????????????
							 0?????????PHY?????????sessvld;
							 1?????????????????????sessvld */
		uint32_t  sessvld:1;  /* bit[11]   : session???????????? */
		uint32_t  dpdmpulldown_sel:1;  /* bit[12]   : PHY???DP/DM???????????????????????????
							 0?????????????????????dp/mpulldown???
							 1?????????????????????dp/mpulldown */
		uint32_t  dppulldown:1;  /* bit[13]   : ??????DP????????????????????? */
		uint32_t  dmpulldown:1;  /* bit[14]   : ??????DM????????????????????? */
		uint32_t  dbnce_fltr_bypass:1;  /* bit[15]   : ??????vbusvalid,avalid,bvalid,sessend???iddig?????????????????? */
		uint32_t  reserved:16; /* bit[16-31]: ????????? */
	} bits;
};

union usbotg2_ctrl1 {
	uint32_t reg;
	struct {
		uint32_t _scaledown_mode:2;
		uint32_t _reserved:30;
	} bits;
};

union usbotg2_ctrl2 {
	uint32_t reg;
	struct {
		uint32_t  commononn:1;  /* bit[0]    : PHY???COMMON?????????????????? */
		uint32_t  otgdisable:1;  /* bit[1]    : ??????PHY???OTG?????? */
		uint32_t  vbusvldsel:1;  /* bit[2]    : VBUS???????????????
						     0?????????PHY???????????????
						     1?????????????????? */
		uint32_t  vbusvldext:1;  /* bit[3]    : VBUS?????? */
		uint32_t  txbitstuffen:1;
		uint32_t  txbitstuffenh:1;
		uint32_t  fsxcvrowner:1;
		uint32_t  txenablen:1;
		uint32_t  fsdataext:1;  /* bit[8]    : ???????????????????????? */
		uint32_t  fsse0ext:1;  /* bit[9]    : ??????????????????SE0 */
		uint32_t  vatestenb:2;
		uint32_t  reserved:20; /* bit[12-31]: ????????? */
	} bits;
};

union usbotg2_ctrl3 {
	uint32_t reg;
	struct {
		uint32_t  comdistune:3;
		uint32_t  otgtune:3;
		uint32_t  sqrxtune:3;
		uint32_t  txfslstune:4;
		uint32_t  txpreempamptune:2;
		uint32_t  txpreemppulsetune:1;
		uint32_t  txrisetune:2;  /* bit[16-17]: ?????????????????????
							 11???-8.1%
							 10???-7.2%
							 01????????????
							 00???+5.4% */
		uint32_t  txvreftune:4;
		uint32_t  txhsxvtune:2;
		uint32_t  txrestune:2;
		uint32_t  vdatreftune:2;
		uint32_t  reserved:4;
	} bits;
};

union usbotg2_ctrl4 {
	uint32_t reg;
	struct {
		uint32_t  siddq:1;  /* bit[0]    : IDDQ?????? */
		uint32_t  vregbypass:1;  /* bit[1]    : Vreg18???????????????Scan??????????????????????????????
						     1???VDDH????????????1.8V??????
						     0???VDDH?????????3.3V?????? */
		uint32_t  loopbackenb:1;  /* bit[2]    : ????????????????????????????????????????????????????????? */
		uint32_t  bypasssel:1;  /* bit[3]    : ??????????????????bypass????????? */
		uint32_t  bypassdmen:1;  /* bit[4]    : DM bypass?????? */
		uint32_t  bypassdpen:1;  /* bit[5]    : DP bypass?????? */
		uint32_t  bypassdmdata:1;  /* bit[6]    : DM bypass?????? */
		uint32_t  bypassdpdata:1;  /* bit[7]    : DP bypass?????? */
		uint32_t  hsxcvrrextctl:1;  /* bit[8]    : HS????????????????????????????????????????????????????????? */
		uint32_t  retenablen:1;  /* bit[9]    : retion??????????????????1 */
		uint32_t  autorsmenb:1;  /* bit[10]   : ??????????????? */
		uint32_t  reserved:21; /* bit[11-31]: ????????? */
	} bits;
};

union usbotg2_ctrl5 {
	uint32_t reg;
	struct {
		uint32_t _refclksel:2;
		uint32_t _fsel:3;
		uint32_t _reserved:27;
	} bits;
};

union bc_ctrl0 {
	uint32_t reg;
	struct {
		uint32_t _chrg_det_en:1;
		uint32_t _reserved:31;
	} bits;
};
union bc_ctrl1 {
	uint32_t reg;
	struct {
		uint32_t _chrg_det_int_clr:1;
		uint32_t _reserved:31;
	} bits;
};
union bc_ctrl2 {
	uint32_t reg;
	struct {
		uint32_t _chrg_det_int_msk:1;
		uint32_t _reserved:31;
	} bits;
};
union bc_ctrl3 {
	uint32_t reg;
	struct {
		uint32_t  bc_mode:1;  /* bit[0]   : BC???????????? */
		uint32_t  reserved:31; /* bit[1-31]: ????????? */
	} bits;
};

union bc_ctrl4 {
	uint32_t reg;
	struct {
		uint32_t  bc_opmode:2;
		uint32_t  bc_xcvrselect:2;  /* bit[2-3]  : ??????????????? */
		uint32_t  bc_termselect:1;  /* bit[4]    : ???????????? */
		uint32_t  bc_txvalid:1;  /* bit[5]    : UTMI+???8bit?????????????????? */
		uint32_t  bc_txvalidh:1;  /* bit[6]    : UTMI+???8bit?????????????????? */
		uint32_t  bc_idpullup:1;  /* bit[7]    : ID?????????????????? */
		uint32_t  bc_dppulldown:1;  /* bit[8]    : DP?????????????????? */
		uint32_t  bc_dmpulldown:1;  /* bit[9]    : DM?????????????????? */
		uint32_t  bc_suspendm:1;  /* bit[10]   : suspend?????? */
		uint32_t  bc_sleepm:1;  /* bit[11]   : sleep?????? */
		uint32_t  reserved:20; /* bit[12-31]: ????????? */
	} bits;
};

union bc_ctrl5 {
	uint32_t reg;
	struct {
		uint32_t  bc_aca_en:1;  /* bit[0]   : ACA???????????? */
		uint32_t  bc_chrg_sel:1;  /* bit[1]   : ??????????????????????????? */
		uint32_t  bc_vdat_src_en:1;  /* bit[2]   : ?????????????????????????????? */
		uint32_t  bc_vdat_det_en:1;  /* bit[3]   : ?????????????????????????????? */
		uint32_t  bc_dcd_en:1;  /* bit[4]   : DCD???????????? */
		uint32_t  reserved:27; /* bit[5-31]: ????????? */
	} bits;
};

union bc_ctrl6 {
	uint32_t reg;
	struct {
		uint32_t _bc_chirp_int_clr:1;
		uint32_t _reserved:31;
	} bits;
};
union bc_ctrl7 {
	uint32_t reg;
	struct {
		uint32_t _bc_chirp_int_msk:1;
		uint32_t _reserved:31;
	} bits;
};
union bc_ctrl8 {
	uint32_t reg;
	struct {
		uint32_t _filter_len;
	} bits;
};
union bc_sts0 {
	uint32_t reg;
	struct {
		uint32_t _chrg_det_rawint:1;
		uint32_t _reserved:31;
	} bits;
};

union bc_sts1 {
	uint32_t reg;
	struct {
		uint32_t _chrg_det_mskint:1;
		uint32_t _reserved:31;
	} bits;
};

union bc_sts2 {
	uint32_t reg;
	struct {
		uint32_t  bc_vbus_valid:1;  /* bit[0]    : vbus ?????? */
		uint32_t  bc_sess_valid:1;  /* bit[1]    : session ?????? */
		uint32_t  bc_fs_vplus:1;  /* bit[2]    : DP?????? */
		uint32_t  bc_fs_vminus:1;  /* bit[3]    : DM?????? */
		uint32_t  bc_chg_det:1;  /* bit[4]    : ??????????????? */
		uint32_t  bc_iddig:1;  /* bit[5]    : ID?????? */
		uint32_t  bc_rid_float:1;  /* bit[6]    : ACA???????????? */
		uint32_t  bc_rid_gnd:1;  /* bit[7]    : ACA???????????? */
		uint32_t  bc_rid_a:1;  /* bit[8]    : ACA???????????? */
		uint32_t  bc_rid_b:1;  /* bit[9]    : ACA???????????? */
		uint32_t  bc_rid_c:1;  /* bit[10]   : ACA???????????? */
		uint32_t  bc_chirp_on:1;  /* bit[11]   : chirp?????? */
		uint32_t  bc_linestate:2;  /* bit[12-13]: ?????????????????? */
		uint32_t  reserved:18; /* bit[14-31]: ????????? */
	} bits;
};

union bc_sts3 {
	uint32_t reg;
	struct {
		uint32_t _bc_rawint:1;
		uint32_t _reserved:31;
	} bits;
};

union bc_sts4 {
	uint32_t reg;
	struct {
		uint32_t _bc_mskint:1;
		uint32_t _reserved:31;
	} bits;
};

union usbotg2_ctrl6 {
	uint32_t reg;
	struct {
		uint32_t  testclk:1;  /* bit[0]    : ?????????????????????????????????????????????????????????????????? */
		uint32_t  testdataoutsel:1;  /* bit[1]    : ???????????????????????????
						      1???????????????????????????????????????
						      0????????????????????????????????????????????? */
		uint32_t  test_sel:1;  /* bit[2]    : ?????????????????????
						      1????????????SOC test????????????
						      0??????????????????????????? */
		uint32_t  reserved_0:1;  /* bit[3]    : ?????? */
		uint32_t  testaddr:4;  /* bit[4-7]  : ????????????????????? */
		uint32_t  testdatain:8;  /* bit[8-15] : ????????????????????? */
		uint32_t  test_mux:4;  /* bit[16-19]: ????????????????????? */
		uint32_t  reserved_1:12; /* bit[20-31]: ????????? */
	} bits;
};

union usbotg2_sts {
	uint32_t reg;
	struct {
		uint32_t  testdataout:4;  /* bit[0-3] : ????????????????????? */
		uint32_t  hssqyelch:1;  /* bit[4]   : HS squelch??????????????? */
		uint32_t  hsrxdat:1;  /* bit[5]   : HS???????????? */
		uint32_t  fslsrcv:1;  /* bit[6]   : ?????????????????????
						   1???D+?????????????????????D-
						   0???D-?????????????????????D+ */
		uint32_t  reserved:25; /* bit[7-31]: ????????? */
	} bits;
};

struct usb_ahbif_registers {
	union usbotg2_ctrl0     usbotg2_ctrl0;
	union usbotg2_ctrl1     usbotg2_ctrl1;
	union usbotg2_ctrl2     usbotg2_ctrl2;
	union usbotg2_ctrl3     usbotg2_ctrl3;
	union usbotg2_ctrl4     usbotg2_ctrl4;
	union usbotg2_ctrl5     usbotg2_ctrl5;
	union bc_ctrl0          bc_ctrl0;
	union bc_ctrl1          bc_ctrl1;
	union bc_ctrl2          bc_ctrl2;
	union bc_ctrl3          bc_ctrl3;
	union bc_ctrl4          bc_ctrl4;
	union bc_ctrl5          bc_ctrl5;
	union bc_ctrl6          bc_ctrl6;
	union bc_ctrl7          bc_ctrl7;
	union bc_ctrl8          bc_ctrl8;
	union bc_sts0           bc_sts0;
	union bc_sts1           bc_sts1;
	union bc_sts2           bc_sts2;
	union bc_sts3           bc_sts3;
	union bc_sts4           bc_sts4;
	union usbotg2_ctrl6     usbotg2_ctrl6;
	union usbotg2_sts       usbotg2_sts;
};

#define usb_dbg(format, arg...)    \
	do {                 \
		printk(KERN_INFO "[USB][%s]"format, __func__, ##arg); \
	} while (0)
#define usb_err(format, arg...)    \
	do {                 \
		printk(KERN_ERR "[USB]"format, ##arg); \
	} while (0)

enum otg_dev_status {
	OTG_DEV_OFF = 0,
	OTG_DEV_DEVICE,
	OTG_DEV_HOST,
};

enum otg_hcd_status {
	HCD_OFF = 0,
	HCD_ON,
};

struct otg_dev;
struct usb_phy_ops {
	void (*init)(struct otg_dev *otg_device, int is_host_mode);
	void (*close)(struct otg_dev *otg_device);
	int (*enable_clk)(struct otg_dev *otg_device);
	void (*disable_clk)(struct otg_dev *otg_device);
	void (*check_voltage)(struct otg_dev *otg_device);
};

struct hiusb_event_queue {
	enum otg_dev_event_type *event;
	unsigned int num_event;
	unsigned int max_event;
	unsigned int enpos, depos;
	unsigned int overlay;
	unsigned int overlay_index;
};
#define MAX_EVENT_COUNT 16
#define EVENT_QUEUE_UNIT MAX_EVENT_COUNT

struct otg_dev {
	enum otg_dev_status status;
	enum otg_hcd_status hcd_status;
	enum otg_dev_event_type event;
	enum hisi_charger_type charger_type;
	enum hisi_charger_type fake_charger_type;

	unsigned gadget_initialized;
	bool dwc_otg_irq_enabled;

	struct lm_device    *lm_dev;
	struct platform_device *pdev;
	struct work_struct event_work;
	struct wake_lock wake_lock;
	struct mutex lock;
	spinlock_t event_lock;

	struct blocking_notifier_head charger_type_notifier;
	struct blocking_notifier_head otg_irq_notifier;

	void __iomem *pericrg_base;
	void __iomem *usb_ahbif_base;
	void __iomem *pctrl_reg_base;

	unsigned int is_regu_on;
	unsigned int host_eyePattern;
	unsigned int eyePattern;
	struct regulator_bulk_data otgdebugsubsys_regu;
	struct usb_phy_ops *usb_phy_ops;
	int fpga_usb_mode_gpio;
	int fpga_flag;
	int eventmask;

	struct clk *clk;
	struct clk *hclk_usb2otg;

	/* for bc again */
	int bc_again_flag;
	int bc_unknown_again_flag;
	unsigned int bc_again_delay_time;
	struct delayed_work bc_again_work;

	unsigned int vdp_src_enable;

	/* event queue for handle event */
	struct hiusb_event_queue event_queue;

	unsigned int need_disable_vdp;
	unsigned int check_voltage;
};

#ifdef CONFIG_PM
extern struct dev_pm_ops dwc_otg_dev_pm_ops;
#define dwc_otg_dev_pm_ops_p (&dwc_otg_dev_pm_ops)
#else
#define dwc_otg_dev_pm_ops_p NULL
#endif

int dwc_otg_hicommon_probe(struct otg_dev *dev_p);
int dwc_otg_hicommon_remove(struct otg_dev *dev_p);

static inline void register_usb_phy_ops(struct otg_dev *dev_p,
					struct usb_phy_ops *ops)
{
	dev_p->usb_phy_ops = ops;
}

static inline struct usb_phy_ops *get_usb_phy_ops(struct otg_dev *dev_p)
{
	return dev_p->usb_phy_ops;
}

/*
 * hisi usb bc
 */
#define BC_AGAIN_DELAY_TIME_1 200
#define BC_AGAIN_DELAY_TIME_2 8000
#define BC_AGAIN_ONCE	1
#define BC_AGAIN_TWICE	2
void notify_charger_type(struct otg_dev *dev_p);
void schdule_bc_again(struct otg_dev *dev_p);
void cancel_bc_again(struct otg_dev *dev_p, int sync);

#endif /* hisi_usb_otg_type.h */
