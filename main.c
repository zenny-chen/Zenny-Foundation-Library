//
//  main.c
//  FoundationBasedAlgorithms
//

#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <uchar.h>
#include "zenny_foundation/zenny_foundation_api.h"
#include "zenny_foundation/zf_sys/zf_directory.h"

extern void AtomicsTest(void);

static const char* MyGetDesc(struct ZFObject *obj)
{
    return obj->identifier == 1000 ? "MyObject" : "unknown";
}

static void MyDeallocMethod(struct ZFObject *obj)
{
    if (obj->identifier == 5000)
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

	struct ZFNumber *number = NULL;
	ZF_CREATE_NUMBER(number, (union ZFNumberValueType) { .b = true }, ZF_NUMBER_ENCODING_BOOL);
    struct ZFSingleLinkNode *node1 = NULL;
    ZF_CREATE_SINGLE_LINK_NODE(node1, (struct ZFObject*)number);
    ZF_RELEASE_OBJECT(number);
    printf("The node1 class is: %s\n", ZF_OBJECT_DESC(node1));

	ZF_CREATE_NUMBER(number, (union ZFNumberValueType) {.A = 2}, ZF_NUMBER_ENCODING_UBYTE);
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

	ssize_t index = ZFFindSingleLinkNode(table, node4);
    printf("node4 index is: %td\n", index);
    ZFRemoveSingleLinkNode(table, node4);

    ZF_RELEASE_OBJECT(node4);

    for (struct ZFSingleLinkNode *iter = ZFSingleLinkNodeIteratorBegin(table); iter != NULL; iter = ZFSingleLinkNodeIteratorNext(iter))
    {
		struct ZFObject *data = iter->data;
        if (data->identifier == ZENNY_NUMBER_IDENTIFIER)
        {
            char desc[64] = { '\0' };
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

	ZF_CREATE_NUMBER(number, (union ZFNumberValueType) { .u = u'h' }, ZF_NUMBER_ENCODING_CHAR16);
	char16_t u16Value = number->value.u;
    printf("The UTF-16 value is: %.4X\n", u16Value);
    ZF_RELEASE_OBJECT(number);

    ZF_CREATE_NUMBER(number, (union ZFNumberValueType) { .Z = 1024 }, ZF_NUMBER_ENCODING_SIZE);
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
    void(*childDealloc)(struct ZFObject *obj);
};

static void MyDeallocParent(struct ZFObject *obj)
{
	struct Parent* parent = (struct Parent*)obj;
    if (parent->identifier != 0x1000)
        return;

    if (parent->childDealloc != NULL)
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
	struct Child* child = (struct Child*)obj;
    if (child->identifier != 0x1001)
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

static __declspec(noinline) void InheritageTest(void)
{
    struct Parent *parent = MyCreateParent();
    ZF_RELEASE_OBJECT(parent);

    struct Child *child = MyCreateChild();
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
    ZF_CREATE_NUMBER(num, (union ZFNumberValueType) { .i = -550 }, ZF_NUMBER_ENCODING_INT);
    ZF_RELEASE_OBJECT(num); // TEST

	ZF_CREATE_NUMBER(num, (union ZFNumberValueType) { .I = 90U }, ZF_NUMBER_ENCODING_UINT);

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
    while ((memInfo = zf_enumerate_registered_profile_item(memInfo)) != NULL)
    {
        printf("ptr identifier: `%s`, in function: `%s`, @line: %d, in file: `%s`, address: 0x%.16tX, size: %zu\n", memInfo->ptrID, memInfo->funcName, memInfo->lineNumber, memInfo->fileName, memInfo->ptr, memInfo->size);
    }

    printf("Memory leakes: %zu\n", zf_mem_profile_leaked_item_count());

    memInfo = NULL;
    while ((memInfo = zf_enumerate_leaked_profile_item(memInfo)) != NULL)
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

/* 
 从指定的UTF-8字符串获得系统默认字符集的可显字符串
 @param dst 用于存放目标系统默认字符集可显字符串的缓存
 @param pUTF8Str 指向一串UTF-8字符串
*/
void GetDefaultStringFromUTF8String(char dst[], const char *pUTF8Str)
{
	if (dst == NULL || pUTF8Str == NULL)
		return;

	const int utfStrLen = (int)strlen(pUTF8Str);
	if (utfStrLen == 0)
	{
		dst[0] = '\0';
		return;
	}

	// 先将UTF-8字符串转为UTF-16字符串
	const int wideStrLen = MultiByteToWideChar(CP_UTF8, 0, pUTF8Str, utfStrLen, NULL, 0);
	char16_t *wideChars = malloc(wideStrLen * sizeof(*wideChars));

	// 再将UTF-16字符串转为系统默认可显字符集的字符串
	MultiByteToWideChar(CP_UTF8, 0, pUTF8Str, utfStrLen, wideChars, wideStrLen);

	const int dstLen = WideCharToMultiByte(CP_ACP, 0, wideChars, wideStrLen, NULL, 0, NULL, NULL);
	WideCharToMultiByte(CP_ACP, 0, wideChars, wideStrLen, dst, dstLen, NULL, NULL);

	dst[dstLen] = '\0';

	free(wideChars);
}

/*
 从指定的UTF-16字符串获得相应的UTF-8字符串或系统默认字符集的可显字符串
 @param dst 存放目标字节字符串的缓存
 @param utf16Str 传入的原始UTF-16字符串
 @param useUTF8 指示是否转为UTF-8字符串。true指示使用UTF-8字符串，false则表示使用默认系统字符集的可显字符串。
*/
void GetByteStringFromUTF16String(char dst[], const char16_t *utf16Str, bool useUTF8)
{
	if (dst == NULL || utf16Str == NULL)
		return;

	const unsigned codePage = useUTF8 ? CP_UTF8 : CP_ACP;
	const int len = WideCharToMultiByte(codePage, 0, utf16Str, -1, NULL, 0, NULL, NULL);

	WideCharToMultiByte(codePage, 0, utf16Str, -1, dst, len, NULL, NULL);
	dst[len] = '\0';
}

static void SystemTest(void)
{
	const char *currDir = zf_get_current_exec_path();
#ifdef _WIN32

	char path[512];
	GetDefaultStringFromUTF8String(path, currDir);
	currDir = path;

#endif // _WIN32

	printf("The current directory is: %s\n", currDir);

	const char *dir = u8"C:/Users/zenny/Desktop/测试目录";
	if (zf_create_directory(dir))
		puts("The directory is created!");
}

int main(int argc, const char * argv[])
{
    // insert code here...

	const char16_t *sourceStr = u"你好，世界！Hello, world!";

	char dstStr[64] = { '\0' };
	GetByteStringFromUTF16String(dstStr, sourceStr, false);

	printf("The string code is: %04X\n", sourceStr[0]);
	printf("The string is: %s\n", dstStr);

	GetDefaultStringFromUTF8String(dstStr, u8"你");
	printf("The string is: %s\n", dstStr);

	const char *utf8Str = u8"你";
	size_t length = strlen(utf8Str);
	printf("The string code is: ");
	for (size_t i = 0; i < length; i++)
		printf("%02X", (uint8_t)utf8Str[i]);

	puts("");

    int array[] = { 1, 2, 3, 4, 5 };
    const ssize_t count = zf_countof(array);
    printf("The count of array is: %zd\n", count);

    printf("ptrdiff_t size: %zu, size_t size: %zu\n", sizeof(ptrdiff_t), sizeof(size_t));

    atomic_int aa;
    atomic_init(&aa, 10);
    atomic_store(&aa, 20);
    const int orgValue = atomic_fetch_add(&aa, 5);
    printf("orgValue = %d, current value = %d\n", orgValue, atomic_load(&aa));

    puts("Hello, World!\n\nInput 'exit' to exit the program; Otherwise to test...\n");
    
    bool willExit = false;

    char contents[1024];

    while (!willExit)
    {
        gets_s(contents, sizeof(contents));
        willExit = strcmp(contents, "exit") == 0;
        if (!willExit)
        {
            Test();
            puts("----------------");
            
			InheritageTest();
            puts("----------------");
            
			MemoryProfileTest();
            puts("----------------\n");

			SystemTest();
			puts("----------------\n");
        }
    }
    
    return 0;
}

