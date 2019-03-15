#include <18F4620.h>
#fuses HS, NOFCMEN, NOIESO, PUT, NOBROWNOUT, NOWDT
#fuses NOPBADEN, NOMCLR, STVREN, NOLVP, NODEBUG 
#use delay(clock=16000000)
#use fast_io(a)
#use fast_io(b)
#use fast_io(c)
#use fast_io(d)
#use fast_io(e)
#define __DEBUG_SERIAL__ //Si comentas esta linea se deshabilita el debug por serial y el PIN_C6 puede ser usado en forma digital I/O

#ifdef __DEBUG_SERIAL__
   #define TX_232        PIN_C6
   #use RS232(BAUD=9600, XMIT=TX_232, BITS=8,PARITY=N, STOP=1)
   #endif
void main (void){
   int contador=0;
   int8 numeroUno = 0;
   int8 numeroDos = 0;
   long res = 0;
   setup_oscillator(OSC_16MHZ); //Se incialisa el ocilador de 16MHZ
   set_tris_c(0xFF);
   set_tris_d(0xFF);
   set_tris_a(0xc0);
   set_tris_b(0x80);
   set_tris_e(0x07);
   while(true){
       numeroUno = input_c();
       numeroDos = input_d();
       if(input(PIN_E0)){
           res = numeroUno + numeroDos;
       }else{
           if(input(PIN_E1)){
               res = numeroUno - numeroDos;
           }else{
               if(input(PIN_E2)){
                   res = numeroUno * numeroDos;
               }else{
                    if(input(PIN_B7)){
                        if(numeroDos == 0){
                            for(contador=256;contador>=0;contador--){
                                output_a(contador);
                            }
                        }else{
                             res = numeroUno / numeroDos;
                         }
                    }
               }
           }
        }
       output_a(res);
       output_b(res>>6);

 }
}
