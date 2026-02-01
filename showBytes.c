//02/01/2026
//recreation of the show_bytes functions
//from ch2 of CS341 textbook
//showing bytes for an int, float, & void*
//Note: Thinkpad t14 gen1 = Little Endian
//EX 65530 in hex === 0x FA FF

#include <stdio.h>
typedef unsigned char* byte_pointer;

/* prints each byte of an object with 2 hex
values for each byte.*/
void show_bytes(const byte_pointer bytePtr, const size_t length) {
    for(size_t i = 0; i < length; i++) {
        printf("%X",bytePtr[i]);
        if(bytePtr[i] == 0) {
            printf("0");
        }
        printf(" ");
    }
    printf("\n");
}
//calls show_bytes using an int
void show_int(const int x) {
    printf("Int bytes as hex 0x: ");
    show_bytes((byte_pointer) &x, sizeof(int));
}
//calls show_bytes using a float
void show_float(const float x) {
    printf("Float bytes as hex 0x: ");
    show_bytes((byte_pointer) &x, sizeof(float));
}
//calls show_byte for an unspecified pointer
void show_pointer(const void* x) {
    printf("Pointer bytes as hex 0x: ");
    show_bytes((byte_pointer) &x, sizeof(void*));
}

int main() {
    int x = 65535;
    show_int(x);
    show_pointer(&x);
    float a = 65535.0;
    show_float(a);
    show_pointer(&a);
    return 0;
}

