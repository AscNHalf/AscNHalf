/* AscNHalf */

#include "BaseModel.h"

namespace VMAP
{
    //==========================================================

    void BaseModel::getMember(Array<TriangleBox>& pMembers)
    {
        for(unsigned int i=0; i<iNTriangles; i++)
        {
            pMembers.append(iTriangles[i]);
        }
    }

    //==========================================================
    BaseModel::BaseModel(unsigned int pNNodes, unsigned int  pNTriangles)
    {
        init(pNNodes, pNTriangles);
    };

    //==========================================================

    void BaseModel::init(unsigned int pNNodes, unsigned int  pNTriangles)
    {
        iNNodes = pNNodes;
        iNTriangles = pNTriangles;
        iTriangles = NULL;
        iTreeNodes = NULL;
        if(iNNodes >0) iTreeNodes = new TreeNode[iNNodes];
        if(iNTriangles >0) iTriangles = new TriangleBox[iNTriangles];
    }

    //==========================================================

    void BaseModel::free()
    {
        if(getTriangles() != 0) delete [] getTriangles(); setNTriangles(0);
        if(getTreeNodes() != 0) delete [] getTreeNodes(); setNNodes(0);
    }

}                                                           // VMAP
