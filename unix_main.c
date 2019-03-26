//
//  unix_main.c
//  
//
//  Created by Zenny Chen on 2019/3/21.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "zenny_foundation/zenny_foundation_api.h"
#include "zenny_foundation/zf_sys/zf_directory.h"
#include "zenny_foundation/zf_sys/zf_sys.h"


static const char* MyGetDesc(struct ZFObject *obj)
{
    return obj->identifier == 1000 ? "MyObject" : "unknown";
}

static void MyDeallocMethod(struct ZFObject *obj)
{
    if(obj->identifier == 5000)
        puts("My customized object is deallocated!");
}

static void Test(void)
{
    struct ZFObject *obj = NULL;
    ZF_CREATE_OBJECT(obj);
    
    obj->data = 100;
    printf("tag = %tu, the class is: %s\n", obj->data, ZF_OBJECT_DESC(obj));
    ZF_RELEASE_OBJECT(obj);
    
    printf("Is it null object? %d\n", ZF_RETAIN_RET_OBJECT(NULL) == NULL);
    
    struct ZFSingleLinkTable *table = NULL;
    ZF_CREATE_SINGLE_LINK_TABLE(table);
    
    printf("The table class is: %s\n", ZF_OBJECT_DESC(table));
    
    let number = ZF_NUMBER((bool)true);
    struct ZFSingleLinkNode *node1 = NULL;
    ZF_CREATE_SINGLE_LINK_NODE(node1, (struct ZFObject*)number);
    ZF_RELEASE_OBJECT(number);
    printf("The node1 class is: %s\n", ZF_OBJECT_DESC(node1));
    
    ZF_CREATE_NUMBER(number, (union ZFNumberValueType)(uint8_t)2, ZF_NUMBER_ENCODING_UBYTE);
    struct ZFSingleLinkNode *node2 = NULL;
    ZF_CREATE_SINGLE_LINK_NODE(node2, (struct ZFObject*)number);
    ZF_RELEASE_OBJECT(number);
    
    ZFAppendSingleLinkNode(table, node1);
    ZFAppendSingleLinkNode(table, node2);
    
    ZF_RELEASE_OBJECT(node1);
    ZF_RELEASE_OBJECT(node2);
    
    printf("The length is: %zu\n", ZFGetSingleLinkTableLength(table));
    
    ZF_CREATE_OBJECT(obj);
    obj->identifier = 5000;
    obj->dealloc = MyDeallocMethod;
    obj->data = 101;
    struct ZFSingleLinkNode *node3 = NULL;
    ZF_CREATE_SINGLE_LINK_NODE(node3, obj);
    ZF_RELEASE_OBJECT(obj);
    
    ZFInsertSingleLinkNode(table, node3, 2);
    ZF_RELEASE_OBJECT(node3);
    
    printf("The length is: %zu\n", ZFGetSingleLinkTableLength(table));
    
    struct ZFSingleLinkNode *node4 = NULL;
    ZF_CREATE_SINGLE_LINK_NODE(node4, NULL);
    
    let index = ZFFindSingleLinkNode(table, node4);
    printf("node4 index is: %td\n", index);
    ZFRemoveSingleLinkNode(table, node4);
    
    ZF_RELEASE_OBJECT(node4);
    
    for(let iter = ZFSingleLinkNodeIteratorBegin(table); iter != NULL; iter = ZFSingleLinkNodeIteratorNext(iter))
    {
        let data = iter->data;
        if(data->identifier == ZENNY_NUMBER_IDENTIFIER)
        {
            char desc[64] = { };
            number = (struct ZFNumber*)data;
            ZFConvertNumberToUTF8String(number, desc);
            printf("The node number value is: %s\n", desc);
        }
        else
            printf("The node data is: %tu\n", iter->data->data);
    }
    
    ZFRemoveAllSingleLinkNodes(table);
    
    printf("The length is: %zu\n", ZFGetSingleLinkTableLength(table));
    
    ZF_RELEASE_OBJECT(table);
    
    ZF_CREATE_OBJECT(obj);
    obj->identifier = 1000;
    printf("obj class is: %s\n", ZFGetObjectDescription(obj, MyGetDesc));
    ZF_RELEASE_OBJECT(obj);
    
    number = ZF_NUMBER(u'你');
    char16_t u16Value = ZF_NUMBER_GET_VALUE(number, u16Value);
    printf("The UTF-16 value is: %.4X\n", u16Value);
    ZF_RELEASE_OBJECT(number);
    
    ZF_CREATE_NUMBER(number, (union ZFNumberValueType){.Z = 1024}, ZF_NUMBER_ENCODING_SIZE);
    size_t szValue = number->value.Z;
    printf("size value is: %zu\n", szValue);
    ZF_RELEASE_OBJECT(number);
}

// MARK: class inheritage demo

/// Parent inherits ZFObject and it is designed to be inheritable
struct Parent
{
    struct ZFObject obj;
    uint32_t identifier;
    int data;
    void (*childDealloc)(struct ZFObject *obj);
};

static void MyDeallocParent(struct ZFObject *obj)
{
    let parent = (struct Parent*)obj;
    if(parent->identifier != 0x1000)
        return;
    
    if(parent->childDealloc != NULL)
        parent->childDealloc(obj);
    
    puts("Parent deallocated!");
}

/// For inheritage, it is necessary to expose an init function
/// which can be used by subclasses.
void MyInitParent(struct Parent *parent)
{
    ZFInitObject(&parent->obj);
    parent->identifier = 0x1000;
    parent->obj.dealloc = MyDeallocParent;
    parent->data = 0;
    parent->childDealloc = NULL;
}

struct Parent * MyCreateParent(void)
{
    struct Parent *parent = malloc(sizeof(*parent));
    MyInitParent(parent);
    return parent;
}

/// Child inherits Parent
struct Child
{
    struct Parent obj;
    uint32_t identifier;
    int data;
};

static void MyDeallocChild(struct ZFObject *obj)
{
    let child = (struct Child*)obj;
    if(child->identifier != 0x1001)
        return;
    
    puts("Child deallocated!");
}

struct Child * MyCreateChild(void)
{
    struct Child *child = malloc(sizeof(*child));
    
    // Initialize child with MyInitParent
    MyInitParent(&child->obj);
    child->identifier = 0x1001;
    child->data = 1;
    child->obj.childDealloc = MyDeallocChild;
    return child;
}

static void InheritageTest(void)
{
    let parent = MyCreateParent();
    ZF_RELEASE_OBJECT(parent);
    
    let child = MyCreateChild();
    printf("Parent data is: %d, child data is: %d\n", child->obj.data, child->data);
    ZF_RELEASE_OBJECT(child);
}

static void MemoryProfileTest(void)
{
    struct ZFObject *obj = NULL;
    ZF_CREATE_OBJECT(obj);
    obj->data = 125;
    ZF_RELEASE_OBJECT(obj); // TEST
    
    ZF_CREATE_OBJECT(obj);
    obj->data = -100;
    
    struct ZFNumber *num = NULL;
    ZF_CREATE_NUMBER(num, (union ZFNumberValueType){.i = -550}, ZF_NUMBER_ENCODING_INT);
    ZF_RELEASE_OBJECT(num); // TEST
    
    ZF_CREATE_NUMBER(num, (union ZFNumberValueType)90U, ZF_NUMBER_ENCODING_UINT);
    
    void *mem = NULL;
    ZF_MALLOC(mem, 128);
    ZF_FREE(mem);   // TEST
    
    ZF_MALLOC(mem, 64);
    
    struct ZFSingleLinkTable *table = NULL;
    ZF_CREATE_SINGLE_LINK_TABLE(table);
    ZF_RELEASE_OBJECT(table);   // TEST
    
    ZF_CREATE_SINGLE_LINK_TABLE(table);
    
    struct ZFSingleLinkNode *node = NULL;
    ZF_CREATE_SINGLE_LINK_NODE(node, obj);
    ZF_RELEASE_OBJECT(obj);
    ZF_RELEASE_OBJECT(node);    // TEST
    
    ZF_CREATE_SINGLE_LINK_NODE(node, NULL);
    
    printf("Registered memory buffers: %zu\n", zf_mem_profile_registered_item_count());
    
    const struct ZFMemoryProfileInfo *memInfo = NULL;
    while((memInfo = zf_enumerate_registered_profile_item(memInfo)) != NULL)
    {
        printf("ptr identifier: `%s`, in function: `%s`, @line: %d, in file: `%s`, address: 0x%.16tX, size: %zu\n", memInfo->ptrID, memInfo->funcName, memInfo->lineNumber, memInfo->fileName, memInfo->ptr, memInfo->size);
    }
    
    printf("Memory leakes: %zu\n", zf_mem_profile_leaked_item_count());
    
    memInfo = NULL;
    while((memInfo = zf_enumerate_leaked_profile_item(memInfo)) != NULL)
    {
        printf("ptr identifier: `%s`, in function: `%s`, @line: %d, in file: `%s`, address: 0x%.16tX, size: %zu\n", memInfo->ptrID, memInfo->funcName, memInfo->lineNumber, memInfo->fileName, memInfo->ptr, memInfo->size);
    }
    
    ZF_FREE(mem);
    ZF_RELEASE_OBJECT(num);
    ZF_RELEASE_OBJECT(table);
    ZF_RELEASE_OBJECT(node);
    
    printf("Registered memory buffers: %zu\n", zf_mem_profile_registered_item_count());
    printf("Memory leakes: %zu\n", zf_mem_profile_leaked_item_count());
}

static void CharacterTest(void)
{
    const char16_t *utf16Str = u"你好，世界！こんにちは！Hello, world!";
    size_t length = zf_utf16_strlen(utf16Str);
    printf("The UTF-16 string length is: %zu\n", length);
    
    char utf8Buffer[128];
    length = zf_utf16str_to_utf8str(utf8Buffer, utf16Str);
    printf("The converted UTF-8 string length is: %zu, contents are: %s\n", length, utf8Buffer);
    
    length = zf_utf8_strlen_from_utf16str(utf16Str);
    printf("The length of UTF-8 string from the UTF-16 string is: %zu\n", length);
    
    length = zf_utf16str_to_utf8str(utf8Buffer, u"abc");
    printf("abc length: %zu, contents: %s\n", length, utf8Buffer);
    
    const char *utf8Str = u8"你好，世界！こんにちは！Hello, world!";
    char16_t utf16Buffer[128];
    length = zf_utf8str_to_utf16str(utf16Buffer, utf8Str);
    printf("The UTF-16 length is: %zu\n", length);
    
    length = zf_utf16_strlen_from_utf8str(utf8Str);
    printf("The length of the UTF-16 string from the UTF-8 string is: %zu\n", length);
    
    length = zf_utf8str_to_utf16str(utf16Buffer, u8"abc");
    printf("The UTF-16 length is: %zu\n", length);
}

static void SystemTest(void)
{
    let currDir = zf_get_current_exec_path();
    printf("Current executable path is: %s\n", currDir);
    
    let testDir = "/Users/zenny-chen/Downloads/test-dir";
    if(zf_create_directory(testDir))
        puts("`test-dir` has been created!");
    
    zf_remove_directory(testDir);
}

int main(int argc, const char* argv[])
{
    int array[] = { 1, 2, 3, 4, 5 };
    const ssize_t count = zf_countof(array);
    printf("The count of array is: %zd\n", count);
    
    puts("\nInput 'exit' to exit the program; Otherwise do the test!");
    
    do
    {
        char *contents = NULL;
        size_t len = 0;
        getline(&contents, &len, stdin);
        
        if(strcmp(contents, "exit\n") == 0)
            break;
        
        Test();
        
        puts("----------------\n");
        
        InheritageTest();
        
        puts("----------------\n");
        
        MemoryProfileTest();
        
        puts("----------------\n");
        
        CharacterTest();
        
        puts("----------------\n");
        
        SystemTest();
        
        puts("----------------\n");
    }
    while(true);
}

