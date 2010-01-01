/* AscNHalf */

#include "ManagedModelContainer.h"

namespace VMAP
{

    ManagedModelContainer::ManagedModelContainer(void) : ModelContainer()
    {
        refCount = 0;
    }

    ManagedModelContainer::~ManagedModelContainer(void)
    {
    }

}
