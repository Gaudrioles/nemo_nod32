#ifndef NEMO_NOD32_H
#define NEMO_NOD32_H

#include <glib-object.h>

G_BEGIN_DECLS

#define NEMO_TYPE_NOD32  (nemo_nod32_get_type ())
#define NEMO_NOD32(o)    (G_TYPE_CHECK_INSTANCE_CAST ((o), NEMO_TYPE_NOD32, NemoNod32))
#define NEMO_IS_NOD32(o) (G_TYPE_CHECK_INSTANCE_TYPE ((o), NEMO_TYPE_NOD32))

typedef struct
{
    GObject __parent;
} NemoNod32;

typedef struct
{
	GObjectClass __parent;
} NemoNod32Class;

GType nemo_nod32_get_type      (void);
void  nemo_nod32_register_type (GTypeModule *module);

G_END_DECLS

#endif /* NEMO_NOD32_H */
