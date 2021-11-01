#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <glib-2.0/glib.h>

#include <string.h>
#include <gio/gio.h>
#include <libnemo-extension/nemo-column.h>
#include <libnemo-extension/nemo-column-provider.h>
#include <libnemo-extension/nemo-desktop-preferences.h>
#include <libnemo-extension/nemo-extension-types.h>
#include <libnemo-extension/nemo-file-info.h>
#include <libnemo-extension/nemo-info-provider.h>
#include <libnemo-extension/nemo-location-widget-provider.h>
#include <libnemo-extension/nemo-menu.h>
#include <libnemo-extension/nemo-menu-item.h>
#include <libnemo-extension/nemo-menu-provider.h>
#include <libnemo-extension/nemo-name-and-desc-provider.h>
#include <libnemo-extension/nemo-property-page.h>
#include <libnemo-extension/nemo-property-page-provider.h>
#include <libnemo-extension/nemo-simple-button.h>
#include <locale.h>
#include "nemo-nod32.h"


static GObjectClass *parent_class;


static void scan_to_callback (NemoMenuItem *item, gpointer user_data)
{
	GList *files, *scan;
	NemoFileInfo *file;
	GString *cmd;
	
	files = g_object_get_data (G_OBJECT (item), "files");
	file = files->data;

	for (scan = files; scan; scan = scan->next)
	{
		NemoFileInfo *file = scan->data;
		char *uri;

		uri = g_file_get_path(nemo_file_info_get_location(file));

		cmd = g_string_new ("sh");
		g_string_append_printf (cmd, " /opt/eset/esets/lib/esets_scan.sh %s", g_shell_quote (uri));
		g_free (uri);
	}
	
	g_spawn_command_line_async (cmd->str, NULL);

	g_string_free (cmd, TRUE);
	
	return;
}

static GList *nemo_nod32_get_file_items (NemoMenuProvider *provider, GtkWidget *window, GList *files)
{
	GList    *items = NULL;
	GList    *scan;

    NemoMenuItem *item;

	if (files == NULL)
		return NULL;

	for (scan = files; scan; scan = scan->next) 
    {
		NemoFileInfo *file = NEMO_FILE_INFO (scan->data);
		gchar *name;

		name = nemo_file_info_get_name (file);
		
		g_free (name);
	}
    
    item = nemo_menu_item_new ("Eset NOD32", "Analyser avec ESET NOD32 Antivirus", "ESET NOD32", "nod32");

	g_signal_connect (item, "activate", G_CALLBACK (scan_to_callback), provider);

	g_object_set_data_full (G_OBJECT (item), "files", nemo_file_info_list_copy (files), (GDestroyNotify) nemo_file_info_list_free);

	items = g_list_append (items, item);

	return items;
}


static void nemo_nod32_menu_provider_iface_init (NemoMenuProviderIface *iface)
{
	iface->get_file_items = nemo_nod32_get_file_items;
}


static void nemo_nod32_instance_init (NemoNod32 *nod32)
{
}


static void nemo_nod32_class_init (NemoNod32Class *class)
{
	parent_class = g_type_class_peek_parent (class);
}


static GType nod32_type = 0;


GType nemo_nod32_get_type (void)
{
	return nod32_type;
}


void nemo_nod32_register_type (GTypeModule *module)
{
	static const GTypeInfo info = {
		sizeof (NemoNod32Class),
		(GBaseInitFunc) NULL,
		(GBaseFinalizeFunc) NULL,
		(GClassInitFunc) nemo_nod32_class_init,
		NULL,
		NULL,
		sizeof (NemoNod32),
		0,
		(GInstanceInitFunc) nemo_nod32_instance_init,
	};

	static const GInterfaceInfo menu_provider_iface_info = {
		(GInterfaceInitFunc) nemo_nod32_menu_provider_iface_init,
		NULL,
		NULL
	};

	nod32_type = g_type_module_register_type (module,
					       G_TYPE_OBJECT,
					       "NemoNod32",
					       &info, 0);

	g_type_module_add_interface (module,
				     nod32_type,
				     NEMO_TYPE_MENU_PROVIDER,
				     &menu_provider_iface_info);
}
