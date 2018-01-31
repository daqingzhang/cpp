#include <stdio.h>

void *xmemcpy(void *to, const void *from, unsigned int n);
void *xmemmove(void *to, const void *from, unsigned int n);

void *xmemmove(void *dst, const void *src, unsigned int n)
{
	char *pd;
	const char *ps;

	printf("dst=%p, src=%p, n=%d\n", dst, src, n);

	if ((src < dst) && (src + n > dst)) {
		pd = dst + n - 1;
		ps = src + n - 1;
		while(n--) {
			*pd-- = *ps--;
		}
	} else {
		pd = dst;
		ps = src;
		while(n--) {
			*pd++ = *ps++;
		}
	}
	return dst;
}

#if 0
void *xmemcpy(void *to, const void *from, unsigned int n)
{
	char *cto = to;
	const char *cfrom = from;

	while(n--)
		*cto++ = *cfrom++;
	return to;
}
#endif

#if 0
void *xmemcpy(void *to, const void *from, unsigned int n)
{
	void *xto = to;
	unsigned int temp;

	if (!n)
		return xto;
	if ((long)to & 0x1) {
		char *cto = to;
		const char *cfrom = from;

		*cto++ = *cfrom++;
		to = cto;
		from = cfrom;
		n--;
	}
	if ((n > 2) && ((long)to & 0x2)) {
		short *sto = to;
		const short *sfrom = from;

		*sto++ = *sfrom++;
		to = sto;
		from = sfrom;
		n -= 2;
	}
	temp = n >> 2;
	if (temp) {
		long *ito = to;
		const long *ifrom = from;

		for(;temp != 0;temp--)
			*ito++ = *ifrom++;
		to = ito;
		from = ifrom;
	}
	if (n & 2) {
		short *sto = to;
		const short *sfrom = from;

		*sto++ = *sfrom++;
		to = sto;
		from = sfrom;
	}
	if (n & 1) {
		char *cto = to;
		const char *cfrom = from;

		*cto++ = *cfrom++;
	}
	return xto;
}
#endif

typedef unsigned long ulong;

void *xmemcpy(void *to, const void *from, unsigned int n)
{
	unsigned long *lto = to;
	const unsigned long *lfrom = from;
	char *cto, *cfrom;

	if ((((ulong)to | (ulong)from) & (sizeof(*lto) - 1)) == 0) {
		while(n > sizeof(*lto)) {
			*lto++ = *lfrom++;
			n -= sizeof(*lto);
		}
	}

	cto = (char *)lto;
	cfrom = (char *)lfrom;
	while(n--)
		*cto++ = *cfrom++;

	return to;
}

#if 0
int xstrcmp(const char *s1, const char *s2)
{
	int res;

	while(1) {
		if ((res = *s1 - *s2++) != 0 || !*s1++)
			break;
	}
	return res;
}
#endif

void *xstrcpy(char *s1, const char *s2);
int xstrcmp(const char *s1, const char *s2);
int xstrlen(const char *s);

void *xstrcpy(char *s1, const char *s2)
{
	char *to = s1;

	do {
		*s1 = *s2++;
	} while (*s1++ != '\0');

	return to;
}

int xstrcmp(const char *s1, const char *s2)
{
	int res = 0;

	while((*s1 != '\0') || (*s2 != '\0')) {
		res = (*s1++) - (*s2++);
		if (res)
			break;
	}
	return res;
}

int xstrlen(const char *s)
{
	const char *ps = s;

	while(*ps != '\0')
		ps++;
	return (ps - s);
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////// Test ////////////////////////////////////////

#define TEST_BUF_LEN 50
unsigned char test_buf1[TEST_BUF_LEN];
unsigned char test_buf2[TEST_BUF_LEN];

int main(void)
{
	unsigned int i, len;
	unsigned char *dst = test_buf1;
	unsigned char *src = test_buf2;

	len = 32;
#if 1
	printf("strcmp = %d\n", xstrcmp("abc", "acd"));
	printf("strcmp = %d\n", xstrcmp("abc", "abcd"));
	printf("strcmp = %d\n", xstrcmp("abcd", "abc"));
	printf("strcmp = %d\n", xstrcmp("abcd", "abcd"));
#endif

#if 0

	for(i = 0;i < len; i++)
		test_buf2[i] = i;

	printf("before memmove:\n");
	for(i = 0;i < len; i++)
		printf("%p = %2x\n", test_buf2+i, test_buf2[i]);

	src = &test_buf2[0];
	dst = &test_buf2[2];
	xmemmove(dst, src, 5);

	printf("after memmove:\n");
	for(i = 0;i < len; i++)
		printf("%p = %2x\n", test_buf2+i, test_buf2[i]);

	for(i = 0;i < len; i++)
		test_buf2[i] = i;

	printf("before memmove:\n");
	for(i = 0;i < len; i++)
		printf("%p = %2x\n", test_buf2+i, test_buf2[i]);

	src = &test_buf2[2];
	dst = &test_buf2[0];
	xmemmove(dst, src, 5);

	printf("after memmove:\n");
	for(i = 0;i < len; i++)
		printf("%p = %2x\n", test_buf2+i, test_buf2[i]);

#endif

#if 0
	for(i = 0;i < len;i++) {
		dst[i] = 0;
		src[i] = i;
		printf("dst[%2x] = %2x, src[%2x] = %2x\n",
			i, dst[i], i, src[i]);
	}

	printf("\ndst = %lx, src = %lx\n", (long)dst, (long)src);
	xmemcpy((void *)dst, (void *)src, len);
	for(i = 0;i < len;i++)
		printf("dst[%2x] = %2x, src[%2x] = %2x\n",
			i, dst[i], i, src[i]);

	dst = (char *)((unsigned long)dst | 0x3);
	src = (char *)((unsigned long)src | 0x3);
	printf("\ndst = %lx, src = %lx\n", (long)dst, (long)src);
	xmemcpy((void *)dst, (void *)src, len);
	for(i = 0;i < len;i++)
		printf("dst[%2x] = %2x, src[%2x] = %2x\n",
			i, dst[i], i, src[i]);
#endif
	return 0;
}
