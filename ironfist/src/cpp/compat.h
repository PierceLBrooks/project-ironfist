
#ifndef COMPAT_H
#define COMPAT_H


extern "C" void* __cdecl op_new(unsigned int x) {
       return operator new(x);
}

extern "C" void __cdecl op_del(void* x) {
       operator delete(x);
}


int main() {
       _start();
       return 0;
}

#endif