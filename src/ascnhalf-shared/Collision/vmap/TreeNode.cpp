/* AscNHalf */

#include "TreeNode.h"

namespace VMAP
{

    TreeNode const* TreeNode::getChild(TreeNode const* pValueArray,int pNo) const
    {
        if(iChilds[pNo] != -1)
            return(&pValueArray[iChilds[pNo]]);
        else
            return(0);
    }

    //=================================================================
    //=================================================================
    //=================================================================
}
