#include "simple_nv.h"
#include "osal_snv.h"

struct test
{
    int a;
};

void simpleNVInit()
{
    static struct test a;
    uint8_t ret = 0;
    ret = osal_snv_read(1, sizeof(struct test), &a);
    DEBUG_STRING("ret : ");
    DEBUG_NUMBER(ret);
    DEBUG_STRING("\r\n");
    DEBUG_STRING("a.a : ");
    DEBUG_NUMBER(a.a);
    DEBUG_STRING("\r\n");
    a.a = 10;
    ret = osal_snv_write(1, sizeof(struct test), &a);
    DEBUG_STRING("write ret : ");
    DEBUG_NUMBER(ret);
    DEBUG_STRING("\r\n");
    a.a = 0;
    ret = osal_snv_read(1, sizeof(struct test), &a);
    DEBUG_STRING("ret : ");
    DEBUG_NUMBER(ret);
    DEBUG_STRING("\r\n");
    DEBUG_STRING("a.a : ");
    DEBUG_NUMBER(a.a);
    DEBUG_STRING("\r\n");
}