#ifndef __G_VFS_JOB_READ_H__
#define __G_VFS_JOB_READ_H__

#include <gvfsjob.h>
#include <gvfsbackend.h>
#include <gvfsreadchannel.h>

G_BEGIN_DECLS

#define G_VFS_TYPE_JOB_READ         (g_vfs_job_read_get_type ())
#define G_VFS_JOB_READ(o)           (G_TYPE_CHECK_INSTANCE_CAST ((o), G_VFS_TYPE_JOB_READ, GVfsJobRead))
#define G_VFS_JOB_READ_CLASS(k)     (G_TYPE_CHECK_CLASS_CAST((k), G_VFS_TYPE_JOB_READ, GVfsJobReadClass))
#define G_VFS_IS_JOB_READ(o)        (G_TYPE_CHECK_INSTANCE_TYPE ((o), G_VFS_TYPE_JOB_READ))
#define G_VFS_IS_JOB_READ_CLASS(k)  (G_TYPE_CHECK_CLASS_TYPE ((k), G_VFS_TYPE_JOB_READ))
#define G_VFS_JOB_READ_GET_CLASS(o) (G_TYPE_INSTANCE_GET_CLASS ((o), G_VFS_TYPE_JOB_READ, GVfsJobReadClass))

typedef struct _GVfsJobReadClass   GVfsJobReadClass;

struct _GVfsJobRead
{
  GVfsJob parent_instance;

  GVfsReadChannel *channel;
  GVfsBackend *backend;
  GVfsBackendHandle handle;
  gsize bytes_requested;
  char *buffer;
  gsize data_count;
};

struct _GVfsJobReadClass
{
  GVfsJobClass parent_class;
};

GType g_vfs_job_read_get_type (void) G_GNUC_CONST;

GVfsJob *g_vfs_job_read_new        (GVfsReadChannel   *channel,
				    GVfsBackendHandle  handle,
				    gsize              bytes_requested,
				    GVfsBackend       *backend);
void     g_vfs_job_read_set_size   (GVfsJobRead       *job,
				    gsize              data_size);

G_END_DECLS

#endif /* __G_VFS_JOB_READ_H__ */
