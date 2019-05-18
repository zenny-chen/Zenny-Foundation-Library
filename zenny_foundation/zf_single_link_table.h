//
//  zf_single_link_table.h
//  FoundationBasedAlgorithms
//
//  Created by Zenny Chen on 2018/5/28.
//  Copyright © 2018年 CodeLearning Studio. All rights reserved.
//

#ifndef zf_single_link_table_h
#define zf_single_link_table_h

#include "zenny_foundation.h"

/// The node of a single-link table
struct ZFSingleLinkNode
{
    struct ZFObject obj;
    
    /// A ZFObject object as the data content
    struct ZFObject *data;
    
    /// A pointer to the next link node
    struct ZFSingleLinkNode *link;
};

/// The single-link table class
struct ZFSingleLinkTable
{
    struct ZFObject obj;
    
    /// length of the single link table
    size_t length;
    
    struct ZFSingleLinkNode *link;
};

/// Create a single link table.
/// @param obj_id the object identifier
/// @return a single link table
#define ZF_CREATE_SINGLE_LINK_TABLE(obj_id)    {  ZF_MALLOC(obj_id, sizeof(*(obj_id))); ZFInitSingleLinkTable(obj_id); }

/// Create a single link node with a specified ZFObject object.
/// @param obj_id the object identifier
/// @param data a ZFObject instance as the data of the new single-link table node. This object will be retained.
/// @return a single link node
#define ZF_CREATE_SINGLE_LINK_NODE(obj_id, data)  { ZF_MALLOC(obj_id, sizeof(*(obj_id))); ZFInitSingleLinkNode((obj_id), (data)); }

/// Initialize a specified single link table.
/// @param table the specified single link table
extern void ZFInitSingleLinkTable(struct ZFSingleLinkTable *table);

/// Initialize a specified single link node.
/// @param node the specified single link node
/// @param data the data that will be attached to the node and it will be retained.
extern void ZFInitSingleLinkNode(struct ZFSingleLinkNode *node, struct ZFObject *data);

/// Get the length of a specified single link table.
/// @param table a specified single link table
/// @return the length of the table
extern size_t ZFGetSingleLinkTableLength(const struct ZFSingleLinkTable *table);

/// Append a link node to the last of the link table.
/// @note This function will retain the node instance
/// @param table a single link table reference
/// @param node a single link node
extern void ZFAppendSingleLinkNode(struct ZFSingleLinkTable *table, struct ZFSingleLinkNode *node);

/// Insert a node into a table at a specified index.
/// @note If index exceeds the range of the table, this function will act like ZennyAppendSingleLinkNode. This function will retain the node instance.
/// @param table a single link table
/// @param node a single link node
/// @param index the specified index, start from zero
extern void ZFInsertSingleLinkNode(struct ZFSingleLinkTable *table, struct ZFSingleLinkNode *node, size_t index);

/// Remove the specified link node from the specified table.
/// @note If the node is not found in the table, it will do nothing.
/// @param table the link table
/// @param node the link node
extern void ZFRemoveSingleLinkNode(struct ZFSingleLinkTable *table, struct ZFSingleLinkNode *node);

/// Remove the link node at the specified index from the table.
/// @note If the index exceeds the range of the table, it will do nothing.
/// @param table the link table
/// @param index the index at which the node will be removed
extern void ZFRemoveSingleLinkNodeAtIndex(struct ZFSingleLinkTable *table, size_t index);

/// Remove all the link nodes in the specified table.
/// @param table the specified table
extern void ZFRemoveAllSingleLinkNodes(struct ZFSingleLinkTable *table);

/// Get the link node at the specified index from the table.
/// @param table the specified table
/// @param index the specified index
/// @return If the index exceeds the range of the table, return NULL; Otherwise, return the link node.
extern struct ZFSingleLinkNode *ZFGetSingleLinkNodeAtIndex(struct ZFSingleLinkTable *table, size_t index);

/// Find the specified link node from the table.
/// @param table the specified table
/// @param node the specified link node
/// @return If the node is found in the table, return the index; Otherwise return -1.
extern ssize_t ZFFindSingleLinkNode(struct ZFSingleLinkTable *table, struct ZFSingleLinkNode *node);

/// Begin the iterator of the specified table.
/// @param table the specified single link table
/// @return the single link node iterator
extern struct ZFSingleLinkNode * ZFSingleLinkNodeIteratorBegin(struct ZFSingleLinkTable *table);

/// Get the next iterator of the specified iterator.
/// @param iter the specified iterator
/// @return the next iterator
extern struct ZFSingleLinkNode * ZFSingleLinkNodeIteratorNext(struct ZFSingleLinkNode *iter);

#endif /* zf_single_link_table_h */

