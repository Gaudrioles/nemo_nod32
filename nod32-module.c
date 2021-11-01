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

#include "nemo-nod32.h"

void nemo_module_initialize (GTypeModule*module)
{
	nemo_nod32_register_type (module);
}


void nemo_module_shutdown (void)
{

}


void nemo_module_list_types (const GType **types, int *num_types)
{
        static GType type_list[1];

	type_list[0] = NEMO_TYPE_NOD32;
	*types = type_list;
	*num_types = 1;
}