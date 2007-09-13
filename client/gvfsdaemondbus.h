#ifndef __G_VFS_DAEMON_DBUS_H__
#define __G_VFS_DAEMON_DBUS_H__

#include <glib.h>
#include <dbus/dbus.h>
#include <gio/gcancellable.h>
#include <gio/gfileinfo.h>

G_BEGIN_DECLS

typedef void (*GVfsAsyncDBusCallback) (DBusMessage *reply,
				       DBusConnection *connection,
				       GError *io_error,
				       gpointer callback_data);
typedef void (*GetFdAsyncCallback)    (int fd,
				       gpointer callback_data);

void         _g_dbus_register_vfs_filter             (const char                 *obj_path,
						      DBusHandleMessageFunction   callback,
						      GObject                    *data);
void         _g_dbus_unregister_vfs_filter           (const char                 *obj_path);
GList *      _g_dbus_bus_list_names_with_prefix_sync (DBusConnection             *connection,
						      const char                 *prefix,
						      DBusError                  *error);
DBusConnection *_g_dbus_connection_get_sync          (const char                 *dbus_id,
						      GError                    **error);
int          _g_dbus_connection_get_fd_sync          (DBusConnection             *conn,
						      int                         fd_id);
void         _g_dbus_connection_get_fd_async         (DBusConnection             *connection,
						      int                         fd_id,
						      GetFdAsyncCallback          callback,
						      gpointer                    callback_data);
void         _g_vfs_daemon_call_async                (DBusMessage                *message,
						      GVfsAsyncDBusCallback       callback,
						      gpointer                    callback_data,
						      GCancellable               *cancellable);
DBusMessage *_g_vfs_daemon_call_sync                 (DBusMessage                *message,
						      DBusConnection            **connection_out,
						      GCancellable               *cancellable,
						      GError                    **error);
GFileInfo *  _g_dbus_get_file_info                   (DBusMessageIter            *iter,
						      GError                    **error);


G_END_DECLS

#endif /* __G_VFS_DAEMON_DBUS_H__ */
