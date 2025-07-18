#ifndef HAVE_PCAT_COMMON_H
#define HAVE_PCAT_COMMON_H

#include <glib.h>

G_BEGIN_DECLS

typedef enum
{
    PCAT_MANAGER_POWER_SCHEDULE_ENABLE_YEAR = (1 << 0),
    PCAT_MANAGER_POWER_SCHEDULE_ENABLE_MONTH = (1 << 1),
    PCAT_MANAGER_POWER_SCHEDULE_ENABLE_DAY = (1 << 2),
    PCAT_MANAGER_POWER_SCHEDULE_ENABLE_HOUR = (1 << 3),
    PCAT_MANAGER_POWER_SCHEDULE_ENABLE_MINUTE = (1 << 4),
    PCAT_MANAGER_POWER_SCHEDULE_ENABLE_DOW = (1 << 5) /* Day of week */
}PCatManagerTimeEnableBits;

typedef enum
{
    PCAT_MANAGER_ROUTE_MODE_NONE,
    PCAT_MANAGER_ROUTE_MODE_UNKNOWN,
    PCAT_MANAGER_ROUTE_MODE_WIRED,
    PCAT_MANAGER_ROUTE_MODE_WIRELESS,
    PCAT_MANAGER_ROUTE_MODE_MOBILE,
    PCAT_MANAGER_ROUTE_MODE_VIRTUAL
}PCatManagerRouteMode;

typedef enum
{
    PCAT_MANAGER_MWAN_MODE_NONE,
    PCAT_MANAGER_MWAN_MODE_DEFAULT
}PCatManagerMWANMode;

typedef struct _PCatManagerMainConfigData
{
    gboolean valid;

    gboolean gn_force_distro;
    gchar *gn_force_power_usage;
    gboolean gn_check_mwan_policy;
    gboolean gn_check_connection;

    gsize gn_mwan_iface_table_size;
    gchar **gn_mwan_iface_table_name;
    gsize gn_mwan_iface_table_name_size;
    gchar **gn_mwan_iface_table_mode;
    gsize gn_mwan_iface_table_mode_size;

    gchar *hw_gpio_modem_power_chip;
    guint hw_gpio_modem_power_line;
    gboolean hw_gpio_modem_power_active_low;
    gchar *hw_gpio_modem_rf_kill_chip;
    guint hw_gpio_modem_rf_kill_line;
    gboolean hw_gpio_modem_rf_kill_active_low;
    gchar *hw_gpio_modem_reset_chip;
    guint hw_gpio_modem_reset_line;
    gboolean hw_gpio_modem_reset_active_low;

    gchar *pm_serial_device;
    guint pm_serial_baud;
    guint pm_auto_shutdown_voltage_general;
    guint pm_auto_shutdown_voltage_lte;
    guint pm_auto_shutdown_voltage_5g;

    guint pm_battery_discharge_table_general[11];
    guint pm_battery_discharge_table_lte[11];
    guint pm_battery_discharge_table_5g[11];
    guint pm_battery_charge_table[11];

    guint pm_led_high_voltage;
    guint pm_led_medium_voltage;
    guint pm_led_low_voltage;
    guint pm_led_work_low_voltage;
    guint pm_startup_voltage;
    guint pm_charger_limit_voltage;
    guint pm_charger_fast_voltage;
    guint pm_battery_full_threshold;

    gboolean debug_modem_external_exec_stdout_log;
    gboolean debug_output_log;
}PCatManagerMainConfigData;

typedef struct _PCatManagerPowerScheduleData
{
    gboolean enabled;
    gboolean action;
    guint8 enable_bits;
    gint16 year;
    guint8 month;
    guint8 day;
    guint8 hour;
    guint8 minute;
    guint8 dow_bits;
}PCatManagerPowerScheduleData;

typedef struct _PCatManagerUserConfigData
{
    gboolean valid;
    gboolean dirty;

    GPtrArray *power_schedule_data;
    gboolean charger_on_auto_start;
    guint charger_on_auto_start_timeout;

    gchar *modem_dial_apn;
    gchar *modem_dial_user;
    gchar *modem_dial_password;
    gchar *modem_dial_auth;
    gboolean modem_disable_ipv6;
    gboolean modem_disable_5g_fail_auto_reset;
    guint modem_5g_fail_timeout;
}PCatManagerUserConfigData;

PCatManagerMainConfigData *pcat_main_config_data_get();
PCatManagerUserConfigData *pcat_main_user_config_data_get();
void pcat_main_user_config_data_sync();
void pcat_main_request_shutdown(gboolean send_pmu_request);
PCatManagerRouteMode pcat_main_network_route_mode_get();
gboolean pcat_main_is_running_on_distro();

G_END_DECLS

#endif

