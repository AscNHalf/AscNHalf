/* AscNHalf */

#ifndef _NODEVALUEACCESS_H
#define _NODEVALUEACCESS_H

namespace VMAP
{
    /**
    This is a helper Class to get access to SubModels or triangles when analyzing the BSP-Tree.
    */

    template<class TNode, class TValue> class NodeValueAccess
    {
        private:
            TNode const* iNodeArray;
            TValue const* iValueArray;

        public:
            inline NodeValueAccess() : iNodeArray(NULL), iValueArray(NULL) {}

            inline NodeValueAccess(TNode const* pNodeArray, TValue const* pValueArray) : iNodeArray(pNodeArray), iValueArray(pValueArray) {}
            inline TNode const* getNodePtr() const { return(iNodeArray); }
            inline TValue const* getValuePtr() const { return(iValueArray); }

            inline TNode const& getNode(unsigned int pPos) const { return(iNodeArray[pPos]); }
            inline void setNode(const TNode& pNode, unsigned int pPos) { iNodeArray[pPos] = pNode; }

            inline TValue const& getValue(unsigned int pPos) const { return(iValueArray[pPos]); }
            inline void setValue(const TValue& pValue, unsigned int pPos) { iValueArray[pPos] = pValue; }
    };
}
#endif
