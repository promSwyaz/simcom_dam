#include <string.h>
#include <stdint.h>

size_t strlen(const char* str) {
	const char* end = str;
	while(*end++ != '\0');
	return (end - str) - 1;
}

void* memset(void* ptr, int value, size_t num) {
	value = value & 0xff;
	uint32_t mask = value << 24 | value << 16 | value << 8 | value;
	const size_t mult4 = num/4;
	for(size_t i=0; i<mult4; i++) {
		((uint32_t*)ptr)[i] = mask;
	}
	switch(num%4) {
		case 3:
			((uint8_t*)ptr)[num - 3] = mask;
			__attribute__((fallthrough));
		case 2:
			((uint8_t*)ptr)[num - 2] = mask;
			__attribute__((fallthrough));
		case 1:
			((uint8_t*)ptr)[num - 1] = mask;
			__attribute__((fallthrough));
		case 0:
			break;
	}
	return ptr;
}

void* memcpy(void* destination, const void* source, size_t num) {
	const size_t mult4 = num/4;
	for(size_t i=0; i<mult4; i++) {
		((uint32_t*)destination)[i] = ((uint32_t*)source)[i];
	}
	switch(num%4) {
		case 3:
			((uint8_t*)destination)[num - 3] = ((uint8_t*)source)[num - 3];
			__attribute__((fallthrough));
		case 2:
			((uint8_t*)destination)[num - 2] = ((uint8_t*)source)[num - 2];
			__attribute__((fallthrough));
		case 1:
			((uint8_t*)destination)[num - 1] = ((uint8_t*)source)[num - 1];
			__attribute__((fallthrough));
		case 0:
			break;
	}
	return destination;
}

int memcmp(const void* destination, const void* source, size_t num) {
	const size_t mult4 = num/4;
	for(size_t i=0; i<mult4; i++) {
		if(((uint32_t*)destination)[i] != ((uint32_t*)source)[i]) return ((uint32_t*)destination)[i] - ((uint32_t*)source)[i];
	}
	switch(num%4) {
		case 3:
			if(((uint8_t*)destination)[num - 3] != ((uint8_t*)source)[num - 3]) return (((uint8_t*)destination)[num - 3] - ((uint8_t*)source)[num - 3]);
			__attribute__((fallthrough));
		case 2:
			if(((uint8_t*)destination)[num - 2] != ((uint8_t*)source)[num - 2]) return (((uint8_t*)destination)[num - 2] - ((uint8_t*)source)[num - 2]);
			__attribute__((fallthrough));
		case 1:
			if(((uint8_t*)destination)[num - 1] != ((uint8_t*)source)[num - 1]) return (((uint8_t*)destination)[num - 1] - ((uint8_t*)source)[num - 1]);
			__attribute__((fallthrough));
		case 0:
			break;
	}
	return 0;
}

int strcmp(const char* str1, const char* str2) {
	while(*str1 != '\0' && *str1 == *str2) { str1++; str2++; }
	return *str1 - *str2;
}

char* strchr(const char* str, int c) {
	while(*str != '\0' && *str != c) str++;
	if(*str != c) return NULL;
	return (char*)str;
}