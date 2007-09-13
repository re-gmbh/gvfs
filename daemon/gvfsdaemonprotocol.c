#include <glib-object.h>
#include <dbus/dbus.h>
#include <gvfsdaemonprotocol.h>
#include <gdbusutils.h>

void
g_dbus_append_file_info (DBusMessageIter *iter,
			 GFileInfo *info)
{
  DBusMessageIter struct_iter, variant_iter, array_iter, inner_struct_iter;
  char **attributes;
  int i;

  attributes = g_file_info_list_attributes (info, NULL);

  if (!dbus_message_iter_open_container (iter,
					 DBUS_TYPE_STRUCT,
					 G_FILE_INFO_INNER_TYPE_AS_STRING,
					 &struct_iter))
    _g_dbus_oom ();


  if (!dbus_message_iter_open_container (&struct_iter,
					 DBUS_TYPE_ARRAY,
					 DBUS_STRUCT_BEGIN_CHAR_AS_STRING
					 DBUS_TYPE_STRING_AS_STRING	
					 DBUS_TYPE_VARIANT_AS_STRING	
					 DBUS_STRUCT_END_CHAR_AS_STRING,
					 &array_iter))
    _g_dbus_oom ();

  for (i = 0; attributes[i] != NULL; i++)
    {
      GFileAttributeType type;
      char *dbus_type;
      void *value;
      const char *str;
      guint32 v_uint32;
      gint32 v_int32;
      guint64 v_uint64;
      gint64 v_int64;

      type = g_file_info_get_attribute_type (info, attributes[i]);
      switch (type)
	{
	case G_FILE_ATTRIBUTE_TYPE_STRING:
	  dbus_type = DBUS_TYPE_STRING_AS_STRING;
	  str = g_file_info_get_attribute_string (info, attributes[i]);
	  value = &str;
	  break;
	case G_FILE_ATTRIBUTE_TYPE_BYTE_STRING:
	  dbus_type = DBUS_TYPE_ARRAY_AS_STRING DBUS_TYPE_BYTE_AS_STRING;
	  str = g_file_info_get_attribute_byte_string (info, attributes[i]);
	  value = &str;
	  break;
	case G_FILE_ATTRIBUTE_TYPE_UINT32:
	  dbus_type = DBUS_TYPE_UINT32_AS_STRING;
	  v_uint32 = g_file_info_get_attribute_uint32 (info, attributes[i]);
	  value = &v_uint32;
	  break;
	case G_FILE_ATTRIBUTE_TYPE_INT32:
	  dbus_type = DBUS_TYPE_INT32_AS_STRING;
	  v_int32 = g_file_info_get_attribute_int32 (info, attributes[i]);
	  value = &v_int32;
	  break;
	case G_FILE_ATTRIBUTE_TYPE_UINT64:
	  dbus_type = DBUS_TYPE_UINT64_AS_STRING;
	  v_uint64 = g_file_info_get_attribute_uint64 (info, attributes[i]);
	  value = &v_uint64;
	  break;
	case G_FILE_ATTRIBUTE_TYPE_INT64:
	  dbus_type = DBUS_TYPE_INT64_AS_STRING;
	  v_int64 = g_file_info_get_attribute_int64 (info, attributes[i]);
	  value = &v_int64;
	  break;
	default:
	  g_warning ("Invalid attribute type %s=%d, ignoring\n", attributes[i], type);
	  continue;
	}

      if (!dbus_message_iter_open_container (&array_iter,
					     DBUS_TYPE_STRUCT,
					     DBUS_TYPE_STRING_AS_STRING
					     DBUS_TYPE_VARIANT_AS_STRING,
					     &inner_struct_iter))
	_g_dbus_oom ();


      if (!dbus_message_iter_append_basic (&inner_struct_iter,
					   DBUS_TYPE_STRING,
					   &attributes[i]))
	_g_dbus_oom ();


      if (!dbus_message_iter_open_container (&inner_struct_iter,
					     DBUS_TYPE_VARIANT,
					     dbus_type,
					     &variant_iter))
	_g_dbus_oom ();

      if (dbus_type[0] == DBUS_TYPE_ARRAY)
	_g_dbus_message_iter_append_cstring (&variant_iter, *(char **)value);
      else
	{
	  if (!dbus_message_iter_append_basic (&variant_iter,
					       dbus_type[0], value))
	    _g_dbus_oom ();
	}
      
      if (!dbus_message_iter_close_container (&inner_struct_iter, &variant_iter))
	_g_dbus_oom ();
      
      if (!dbus_message_iter_close_container (&array_iter, &inner_struct_iter))
	_g_dbus_oom ();
    }

  g_strfreev (attributes);

  if (!dbus_message_iter_close_container (&struct_iter, &array_iter))
    _g_dbus_oom ();
      
  if (!dbus_message_iter_close_container (iter, &struct_iter))
    _g_dbus_oom ();
}
