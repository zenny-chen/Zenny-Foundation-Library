﻿//
//  main.c
//  FoundationBasedAlgorithms
//

#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <uchar.h>
#include "zenny_foundation/zenny_foundation_api.h"
#include "zenny_foundation/zf_sys/zf_sys.h"
#include "zenny_foundation/zf_sys/zf_directory.h"
#include "zenny_foundation/zf_sys/zf_atomic_opaque.h"
#include "zenny_foundation/zf_sys/zf_complex.h"

static const char* MyGetDesc(struct ZFObject* obj)
{
    return obj->identifier == 1000 ? "MyObject" : "unknown";
}

static void MyDeallocMethod(struct ZFObject* obj)
{
    if (obj->identifier == 5000)
        puts("My customized object is deallocated!");
}

static void Test(void)
{
    struct ZFObject* obj = NULL;
    ZF_CREATE_OBJECT(obj);

    obj->data = 100;
    printf("tag = %tu, the class is: %s\n", obj->data, ZF_OBJECT_DESC(obj));
    ZF_RELEASE_OBJECT(obj);

    printf("Is it null object? %d\n", ZF_RETAIN_RET_OBJECT(NULL) == NULL);

    struct ZFSingleLinkTable* table = NULL;
    ZF_CREATE_SINGLE_LINK_TABLE(table);

    printf("The table class is: %s\n", ZF_OBJECT_DESC(table));

    struct ZFNumber* number = NULL;
    ZF_CREATE_NUMBER(number, (union ZFNumberValueType) { .b = true }, ZF_NUMBER_ENCODING_BOOL);
    struct ZFSingleLinkNode* node1 = NULL;
    ZF_CREATE_SINGLE_LINK_NODE(node1, (struct ZFObject*)number);
    ZF_RELEASE_OBJECT(number);
    printf("The node1 class is: %s\n", ZF_OBJECT_DESC(node1));

    ZF_CREATE_NUMBER(number, (union ZFNumberValueType) { .A = 2 }, ZF_NUMBER_ENCODING_UBYTE);
    struct ZFSingleLinkNode* node2 = NULL;
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
    struct ZFSingleLinkNode* node3 = NULL;
    ZF_CREATE_SINGLE_LINK_NODE(node3, obj);
    ZF_RELEASE_OBJECT(obj);

    ZFInsertSingleLinkNode(table, node3, 2);
    ZF_RELEASE_OBJECT(node3);

    printf("The length is: %zu\n", ZFGetSingleLinkTableLength(table));

    struct ZFSingleLinkNode* node4 = NULL;
    ZF_CREATE_SINGLE_LINK_NODE(node4, NULL);

    ssize_t index = ZFFindSingleLinkNode(table, node4);
    printf("node4 index is: %td\n", index);
    ZFRemoveSingleLinkNode(table, node4);

    ZF_RELEASE_OBJECT(node4);

    for (struct ZFSingleLinkNode* iter = ZFSingleLinkNodeIteratorBegin(table); iter != NULL; iter = ZFSingleLinkNodeIteratorNext(iter))
    {
        struct ZFObject* data = iter->data;
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
    void(*childDealloc)(struct ZFObject* obj);
};

static void MyDeallocParent(struct ZFObject* obj)
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
void MyInitParent(struct Parent* parent)
{
    ZFInitObject(&parent->obj);
    parent->identifier = 0x1000;
    parent->obj.dealloc = MyDeallocParent;
    parent->data = 0;
    parent->childDealloc = NULL;
}

struct Parent* MyCreateParent(void)
{
    struct Parent* parent = malloc(sizeof(*parent));
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

static void MyDeallocChild(struct ZFObject* obj)
{
    struct Child* child = (struct Child*)obj;
    if (child->identifier != 0x1001)
        return;

    puts("Child deallocated!");
}

struct Child* MyCreateChild(void)
{
    struct Child* child = malloc(sizeof(*child));

    // Initialize child with MyInitParent
    MyInitParent(&child->obj);
    child->identifier = 0x1001;
    child->data = 1;
    child->obj.childDealloc = MyDeallocChild;
    return child;
}

static __declspec(noinline) void InheritageTest(void)
{
    struct Parent* parent = MyCreateParent();
    ZF_RELEASE_OBJECT(parent);

    struct Child* child = MyCreateChild();
    printf("Parent data is: %d, child data is: %d\n", child->obj.data, child->data);
    ZF_RELEASE_OBJECT(child);
}

static void MemoryProfileTest(void)
{
    struct ZFObject* obj = NULL;
    ZF_CREATE_OBJECT(obj);
    obj->data = 125;
    ZF_RELEASE_OBJECT(obj); // TEST

    ZF_CREATE_OBJECT(obj);
    obj->data = -100;

    struct ZFNumber* num = NULL;
    ZF_CREATE_NUMBER(num, (union ZFNumberValueType) { .n = -550 }, ZF_NUMBER_ENCODING_INT);
    ZF_RELEASE_OBJECT(num); // TEST

    ZF_CREATE_NUMBER(num, (union ZFNumberValueType) { .N = 90U }, ZF_NUMBER_ENCODING_UINT);

    void* mem = NULL;
    ZF_MALLOC(mem, 128);
    ZF_FREE(mem);   // TEST

    ZF_MALLOC(mem, 64);

    struct ZFSingleLinkTable* table = NULL;
    ZF_CREATE_SINGLE_LINK_TABLE(table);
    ZF_RELEASE_OBJECT(table);   // TEST

    ZF_CREATE_SINGLE_LINK_TABLE(table);

    struct ZFSingleLinkNode* node = NULL;
    ZF_CREATE_SINGLE_LINK_NODE(node, obj);
    ZF_RELEASE_OBJECT(obj);
    ZF_RELEASE_OBJECT(node);    // TEST

    ZF_CREATE_SINGLE_LINK_NODE(node, NULL);

    printf("Registered memory buffers: %zu\n", zf_mem_profile_registered_item_count());

    const struct ZFMemoryProfileInfo* memInfo = NULL;
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
 Get system default characters from UTf-8 string
 @param dst the buffer that stores the system default characters
 @param pUTF8Str the specified UTF-8 string
*/
static void GetDefaultStringFromUTF8String(char dst[], const char* pUTF8Str)
{
    if (dst == NULL || pUTF8Str == NULL)
        return;

    const int utfStrLen = (int)strlen(pUTF8Str);
    if (utfStrLen == 0)
    {
        dst[0] = '\0';
        return;
    }

    // Firstly, convert the UTF-8 string to UTF-16 string
    const int wideStrLen = MultiByteToWideChar(CP_UTF8, 0, pUTF8Str, utfStrLen, NULL, 0);
    char16_t* wideChars = malloc(wideStrLen * sizeof(*wideChars));

    // Then, convert the UTF-16 string to system default characters
    MultiByteToWideChar(CP_UTF8, 0, pUTF8Str, utfStrLen, wideChars, wideStrLen);

    const int dstLen = WideCharToMultiByte(CP_ACP, 0, wideChars, wideStrLen, NULL, 0, NULL, NULL);
    WideCharToMultiByte(CP_ACP, 0, wideChars, wideStrLen, dst, dstLen, NULL, NULL);

    dst[dstLen] = '\0';

    free(wideChars);
}

/*
 Get system default characters or UTF-8 string from the UTF-16 string
 @param dst the buffer that stores the destination characters
 @param utf16Str the specified UTF-16 string
 @param useUTF8 indicate whether to use UTF-8 or system default characters
*/
static void GetByteStringFromUTF16String(char dst[], const char16_t* utf16Str, bool useUTF8)
{
    if (dst == NULL || utf16Str == NULL)
        return;

    const unsigned codePage = useUTF8 ? CP_UTF8 : CP_ACP;
    const int len = WideCharToMultiByte(codePage, 0, utf16Str, -1, NULL, 0, NULL, NULL);

    WideCharToMultiByte(codePage, 0, utf16Str, -1, dst, len, NULL, NULL);
    dst[len] = '\0';
}

static void CharacterTest(void)
{
    const char16_t* utf16Str = u"你好，世界！こんにちは！Hello, world!";
    size_t length = zf_utf16_strlen(utf16Str);
    printf("The UTF-16 string length is: %zu\n", length);

    char utf8Buffer[128];
    length = zf_utf16str_to_utf8str(utf8Buffer, utf16Str);

    char dstStrBuffer[128];
    GetDefaultStringFromUTF8String(dstStrBuffer, utf8Buffer);
    printf("The converted UTF-8 string length is: %zu, contents are: %s\n", length, dstStrBuffer);

    length = zf_utf8_strlen_from_utf16str(utf16Str);
    printf("The length of UTF-8 string from the UTF-16 string is: %zu\n", length);

    length = zf_utf16str_to_utf8str(utf8Buffer, u"abc");
    printf("abc length: %zu, contents: %s\n", length, utf8Buffer);

    const char* utf8Str = u8"你好，世界！こんにちは！Hello, world!";
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
    char path[512];
    const char* currDir = zf_get_current_exec_path();

    GetDefaultStringFromUTF8String(path, currDir);
    currDir = path;

    printf("The current directory is: %s\n", currDir);

    const char* dir = u8"C:/Users/zenny/Desktop/测试目录";
    if (zf_create_directory(dir))
        puts("The directory is created!");

    zf_remove_directory(dir);
}

static void noreturn MyExit(void)
{
    exit(0);
}

static void ComplexTest(void)
{
    zf_float_complex a = ZF_FLOAT_COMPLEX(3.0f, 2.0f);
    zf_float_complex b = ZF_FLOAT_COMPLEX(2.0f, -1.0f);

    zf_float_complex c = zf_cmulf(a, b);
    c = zf_cdivf(c, b);

    printf("The complex number c is: %.1f + %.1fi\n", crealf(c), cimagf(c));

    zf_complex_real_part(c) += 1.0f;
    zf_complex_imag_part(c) -= 1.0f;
    printf("The complex number c is: %.1f + %.1fi\n", crealf(c), cimagf(c));
}

int main(int argc, const char* argv[])
{
    struct ZFOpaqueAtomicType flag = { 0 };
    if (!zf_opaque_atomic_flag_test_and_set(&flag))
        puts("Enter the critical section!");

    if (zf_opaque_atomic_flag_test_and_set(&flag))
        puts("Already in critical section!");

    zf_opaque_atomic_flag_clear(&flag);

    zf_lock_opaque(&flag);
    zf_unlock_opaque(&flag);

    volatile struct ZFOpaqueAtomicType atomInt = { 0 };
    unsigned value;
    zf_opaque_atomic_load(&atomInt, &value);
    printf("The value is: %d\n", value);

    zf_opaque_atomic_store(&atomInt, 2345678900U);
    zf_opaque_atomic_load(&atomInt, &value);
    printf("The value is: %u\n", value);

    ssize_t svalue = 98765432, dvalue;
    zf_opaque_atomic_store(&atomInt, svalue);
    zf_opaque_atomic_load(&atomInt, &svalue);
    printf("The value is: %td\n", svalue);

    svalue = zf_opaque_atomic_fetch_add(&atomInt, 12345678);
    zf_opaque_atomic_load(&atomInt, &dvalue);
    printf("original value = %td, value = %lld\n", svalue, (long long)dvalue);
    zf_opaque_atomic_load(&atomInt, &svalue);
    printf("After addition, value = %td\n", svalue);

    ptrdiff_t orgValue = zf_opaque_atomic_fetch_sub(&atomInt, 98765432);
    zf_opaque_atomic_load(&atomInt, &svalue);
    printf("Org value: %td, After subtraction, value = %td\n", orgValue, svalue);
    
    zf_opaque_atomic_store(&atomInt, 0xaaaaaaaaU);
    value = zf_opaque_atomic_fetch_or(&atomInt, 0x55555555U);
    printf("original value: %.8X, value = %.8X\n", value, zf_opaque_atomic_load_int(&atomInt));

    zf_opaque_atomic_store(&atomInt, 0xccccccccU);
    value = zf_opaque_atomic_fetch_xor(&atomInt, 0xaaaaaaaaU);
    printf("original value: %.8X, value = %.8X\n", value, zf_opaque_atomic_load_int(&atomInt));

    zf_opaque_atomic_store(&atomInt, 0xaaaaaaaaU);
    value = zf_opaque_atomic_fetch_and(&atomInt, 0x55555555U);
    printf("original value: %.8X, value = %.8X\n", value, zf_opaque_atomic_load_int(&atomInt));
    

    value = zf_opaque_atomic_exchange(&atomInt, 1);
    zf_opaque_atomic_load(&atomInt, &svalue);
    printf("original value is: %u, new value is: %zd\n", value, svalue);

    if (value >= 0)
        zf_opaque_atomic_load(&atomInt, &value);
    else
        puts("Wow!!");

    if (value > 0)
        zf_opaque_atomic_store(&atomInt, value);
    else
        puts("Oooof!!");

    if (zf_opaque_atomic_compare_exchange(&atomInt, &value, 100))
    {
        zf_opaque_atomic_load(&atomInt, &svalue);
        printf("OK!! value = %d, atomic = %td\n", value, svalue);
    }

    if (!zf_opaque_atomic_compare_exchange(&atomInt, &value, 0))
        puts("Not equal!");

    if (zf_opaque_atomic_compare_exchange(&atomInt, &svalue, 0))
        puts("Equal!");

    puts("\n--------\n");

    // insert code here...
    const char16_t* sourceStr = u"你好，世界！Hello, world!";

    char dstStr[64] = { '\0' };
    GetByteStringFromUTF16String(dstStr, sourceStr, false);

    const wchar_t wc = L'你';
    printf("wc size is: %zu\n", sizeof(wc));
    printf("wc alignment is: %zu\n", _Alignof(wchar_t));

    printf("The string code is: %04X\n", sourceStr[0]);
    printf("The string is: %s\n", dstStr);

    GetDefaultStringFromUTF8String(dstStr, u8"你");
    printf("The string is: %s\n", dstStr);

    const char* utf8Str = u8"你";
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
    const int orgVal = atomic_fetch_add(&aa, 5);
    printf("orgValue = %d, current value = %d\n", orgVal, atomic_load(&aa));

    puts("Hello, World!\n\nInput 'exit' to exit the program; Otherwise to test...\n");

    bool willExit = false;

    char contents[1024];

    while (!willExit)
    {
        zf_get_console_line(contents, sizeof(contents));
        willExit = strcmp(contents, "exit") == 0;
        if (!willExit)
        {
            Test();
            puts("----------------");

            InheritageTest();
            puts("----------------");

            MemoryProfileTest();
            puts("----------------\n");

            CharacterTest();
            puts("----------------\n");

            ComplexTest();

            puts("----------------\n");

            SystemTest();
            puts("----------------\n");
        }
    }

    MyExit();

    return 0;
}

