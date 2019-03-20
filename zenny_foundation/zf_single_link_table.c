//
//  zf_single_link_table.c
//  FoundationBasedAlgorithms
//
//  Created by Zenny Chen on 2018/5/28.
//  Copyright © 2018年 CodeLearning Studio. All rights reserved.
//

#include "zf_single_link_table.h"
#include <stdlib.h>

static void ZennyRecurDeleteNodes(struct ZFSingleLinkNode *node)
{
    if(node->link != NULL)
        ZennyRecurDeleteNodes(node->link);
    
    ZF_RELEASE_OBJECT(node);
}

static void ZennyDeallocSingleLinkTable(struct ZFObject *obj)
{
    if(obj == NULL || obj->identifier != ZENNY_SINGLE_LINK_TABLE_IDENTIFIER)
        return;
    
    struct ZFSingleLinkTable *table = (struct ZFSingleLinkTable*)obj;
    if(table->link == NULL)
        return;
    
    ZennyRecurDeleteNodes(table->link);
}

static void ZennyDeallocSingleLinkNode(struct ZFObject *obj)
{
    if(obj == NULL || obj->identifier != ZENNY_SINGLE_LINK_NODE_IDENTIFIER)
        return;
    
    struct ZFSingleLinkNode *node = (struct ZFSingleLinkNode*)obj;
    ZF_RELEASE_OBJECT(node->data);
}

void ZFInitSingleLinkTable(struct ZFSingleLinkTable *table)
{
    ZFInitObject(&table->obj);
    table->obj.identifier = ZENNY_SINGLE_LINK_TABLE_IDENTIFIER;
    table->obj.dealloc = ZennyDeallocSingleLinkTable;
    table->link = NULL;
}

void ZFInitSingleLinkNode(struct ZFSingleLinkNode *node, struct ZFObject *data)
{
    ZFInitObject(&node->obj);
    node->obj.identifier = ZENNY_SINGLE_LINK_NODE_IDENTIFIER;
    node->obj.dealloc = ZennyDeallocSingleLinkNode;
    node->data = ZF_RETAIN_RET_OBJECT(data);
    node->link = NULL;
}

size_t ZFGetSingleLinkTableLength(const struct ZFSingleLinkTable *table)
{
    if(table == NULL)
        return 0;
    
    const struct ZFSingleLinkNode *node = table->link;
    size_t length = 0;
    while(node != NULL)
    {
        node = node->link;
        length++;
    }
    return length;
}

void ZFAppendSingleLinkNode(struct ZFSingleLinkTable *table, struct ZFSingleLinkNode *node)
{
    if(table == NULL || node == NULL)
        return;
    
    if(table->link == NULL)
        table->link = node;
    else
    {
        struct ZFSingleLinkNode * pn = table->link;
        while(pn->link != NULL)
            pn = pn->link;
        
        pn->link = node;
    }
    
    node->link = NULL;
    ZF_RETAIN_OBJECT(node);
}

void ZFInsertSingleLinkNode(struct ZFSingleLinkTable *table, struct ZFSingleLinkNode *node, size_t index)
{
    if(table == NULL || node == NULL)
        return;
    
    if(index == 0)
    {
        struct ZFSingleLinkNode *nextNode = table->link;
        table->link = node;
        node->link = nextNode;
    }
    else
    {
        struct ZFSingleLinkNode *dstNode = table->link;
        for(size_t i = 1; i < index; i++)
        {
            struct ZFSingleLinkNode *nextNode = dstNode->link;
            if(nextNode == NULL)
                break;
            
            dstNode = nextNode;
        }
        struct ZFSingleLinkNode * nextNode = dstNode->link;
        dstNode->link = node;
        node->link = nextNode;
    }
    
    ZF_RETAIN_OBJECT(node);
}

void ZFRemoveSingleLinkNode(struct ZFSingleLinkTable *table, struct ZFSingleLinkNode *node)
{
    if(table == NULL || node == NULL)
        return;
    
    if(table->link == node)
    {
        table->link = node->link;
        ZF_RELEASE_OBJECT(node);
        return;
    }
    
    struct ZFSingleLinkNode *dstNode = table->link;
    while(dstNode->link != NULL)
    {
        if(dstNode->link == node)
            break;
        
        dstNode = dstNode->link;
    }
    
    if(dstNode->link == node)
    {
        dstNode->link = node->link;
        ZF_RELEASE_OBJECT(node);
    }
}

void ZFRemoveSingleLinkNodeAtIndex(struct ZFSingleLinkTable *table, size_t index)
{
    if(table == NULL)
        return;
    
    struct ZFSingleLinkNode *dstNode = NULL;
    
    if(index == 0)
    {
        dstNode = table->link;
        table->link = dstNode->link;
    }
    else
    {
        struct ZFSingleLinkNode *prevNode = table->link;
        for(size_t i = 1; i < index; i++)
        {
            prevNode = prevNode->link;
            if(prevNode == NULL)
                break;
        }
        if(prevNode != NULL && prevNode->link != NULL)
        {
            dstNode = prevNode->link;
            prevNode->link = dstNode->link;
        }
    }
    if(dstNode != NULL)
        ZF_RELEASE_OBJECT(dstNode);
}

void ZFRemoveAllSingleLinkNodes(struct ZFSingleLinkTable *table)
{
    if(table == NULL)
        return;
    
    if(table->link == NULL)
        return;
    
    ZennyRecurDeleteNodes(table->link);
    
    table->link = NULL;
}

struct ZFSingleLinkNode *ZFGetSingleLinkNodeAtIndex(struct ZFSingleLinkTable *table, size_t index)
{
    if(table == NULL)
        return NULL;
    
    struct ZFSingleLinkNode *node = table->link;
    for(size_t i = 0; i < index; i++)
    {
        if(node == NULL)
            return NULL;
        
        node = node->link;
    }
    
    return node;
}

ssize_t ZFFindSingleLinkNode(struct ZFSingleLinkTable *table, struct ZFSingleLinkNode *node)
{
    if(table == NULL || node == NULL)
        return -1;
    
    struct ZFSingleLinkNode *cmpNode = table->link;
    if(cmpNode == NULL)
        return -1;
    
    size_t index = 0;
    
    do
    {
        if(cmpNode == node)
            return index;
        
        cmpNode = cmpNode->link;
        index++;
    }
    while(cmpNode != NULL);
    
    return -1;
}

struct ZFSingleLinkNode *ZFSingleLinkNodeIteratorBegin(struct ZFSingleLinkTable *table)
{
    if(table == NULL)
        return NULL;
    
    return table->link;
}

struct ZFSingleLinkNode * ZFSingleLinkNodeIteratorNext(struct ZFSingleLinkNode *iter)
{
    if(iter == NULL)
        return NULL;
    
    return iter->link;
}

