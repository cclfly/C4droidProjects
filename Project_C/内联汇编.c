int main(void){
int var=0xAA;
__asm
(
"\
MOV    R5,#0xAA;\
MOV    R6,#0xBB;\
CMP    R1,#0;\
"
);
while(1);
}