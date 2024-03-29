/*
 *     Project: Remmina Plugin EXEC
 * Description: Remmina protocol plugin to execute an external process.
 *      Author: Fabio Castelli (Muflone) <muflone@muflone.com>
 *   Copyright: 2011-2023 Fabio Castelli (Muflone)
 *     License: GPL-2+
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of ERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "plugin_config.h"
#include <remmina/remmina_plugin.h>
#if GTK_VERSION == 3
  # include <gtk/gtkx.h>
#endif

static RemminaPluginService *remmina_plugin_service = NULL;

static void remmina_plugin_exec_init(RemminaProtocolWidget *gp)
{
  TRACE_CALL("remmina_plugin_exec_init");
  remmina_plugin_service->log_printf("[%s] Plugin init\n", PLUGIN_NAME);
}

static gboolean remmina_plugin_exec_open_connection(RemminaProtocolWidget *gp)
{
  TRACE_CALL("remmina_plugin_exec_open_connection");
  remmina_plugin_service->log_printf("[%s] Plugin open connection\n", PLUGIN_NAME);
  #define GET_PLUGIN_STRING(value) \
    g_strdup(remmina_plugin_service->file_get_string(remminafile, value))
  #define GET_PLUGIN_BOOLEAN(value) \
    remmina_plugin_service->file_get_int(remminafile, value, FALSE)

  RemminaFile *remminafile;
  gboolean ret;
  GError *error = NULL;
  gchar **output_fd = NULL;
  gchar **error_fd = NULL;
  gint *exit_status = NULL;

  remminafile = remmina_plugin_service->protocol_plugin_get_file(gp);

  if (GET_PLUGIN_BOOLEAN("synchronous"))
    ret = g_spawn_command_line_sync(GET_PLUGIN_STRING("server"),
      output_fd, error_fd, exit_status, &error);
  else
    ret = g_spawn_command_line_async(GET_PLUGIN_STRING("server"), &error);

  if (!ret)
    remmina_plugin_service->protocol_plugin_set_error(gp, "%s", error->message);

  return FALSE;
}

static gboolean remmina_plugin_exec_close_connection(RemminaProtocolWidget *gp)
{
  TRACE_CALL("remmina_plugin_exec_close_connection");
  remmina_plugin_service->log_printf("[%s] Plugin close connection\n", PLUGIN_NAME);
  remmina_plugin_service->protocol_plugin_emit_signal(gp, "disconnect");
  return FALSE;
}

/* Array of RemminaProtocolSetting for basic settings.
 * Each item is composed by:
 * a) RemminaProtocolSettingType for setting type
 * b) Setting name
 * c) Setting description
 * d) Compact disposition
 * e) Values for REMMINA_PROTOCOL_SETTING_TYPE_SELECT or REMMINA_PROTOCOL_SETTING_TYPE_COMBO
 * f) Unused pointer
 */
static const RemminaProtocolSetting remmina_plugin_exec_basic_settings[] =
{
  { REMMINA_PROTOCOL_SETTING_TYPE_TEXT, "server", N_("Startup program"), FALSE, NULL, NULL },
  { REMMINA_PROTOCOL_SETTING_TYPE_CHECK, "synchronous", N_("Synchronous open"), TRUE, NULL, NULL },
  { REMMINA_PROTOCOL_SETTING_TYPE_END, NULL, NULL, FALSE, NULL, NULL }
};

/* Protocol plugin definition and features */
static RemminaProtocolPlugin remmina_plugin =
{
  REMMINA_PLUGIN_TYPE_PROTOCOL,                 // Type
  PLUGIN_NAME,                                  // Name
  PLUGIN_DESCRIPTION,                           // Description
  GETTEXT_PACKAGE,                              // Translation domain
  PLUGIN_VERSION,                               // Version number
  PLUGIN_APPICON,                               // Icon for normal connection
  PLUGIN_APPICON,                               // Icon for SSH connection
  remmina_plugin_exec_basic_settings,           // Array for basic settings
  NULL,                                         // Array for advanced settings
  REMMINA_PROTOCOL_SSH_SETTING_NONE,            // SSH settings type
  NULL,                                         // Array for available features
  remmina_plugin_exec_init,                     // Plugin initialization
  remmina_plugin_exec_open_connection,          // Plugin open connection
  remmina_plugin_exec_close_connection,         // Plugin close connection
  NULL,                                         // Query for available features
  NULL,                                         // Call a feature
  NULL,                                         // Send a keystroke
  NULL                                          // Capture screenshot
};

G_MODULE_EXPORT gboolean remmina_plugin_entry(RemminaPluginService *service)
{
  TRACE_CALL("remmina-plugin-exec::remmina_plugin_entry");
  remmina_plugin_service = service;

  if (!service->register_plugin((RemminaPlugin *) &remmina_plugin))
  {
    return FALSE;
  }
  return TRUE;
}
