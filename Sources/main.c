#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */

unsigned char arreglo[] = {0x0E, 0x0D, 0x0B, 0x07}; //char para 8 bits

void delay_medio_segundo(){
	SRTISC= 0b00000110 ; //timer, ver pag. 75 del manual
	//la bandera se prende en 512 ms
	do{
		__RESET_WATCHDOG();
	}while(SRTISC_RTIF == 0);
	SRTISC_RTIACK=1;
	SRTISC = 0b00000000; //detener el timer
}


void main(void) {
	unsigned char j = 0; //LAS VARIABLES SE TIENEN QUE DECLARAR ANTES DE CUALQUIER INSTRUCCION
  EnableInterrupts;
  /* include your code here */
  PTBDD =  0x0F; //del 0 al 3 son salidas, y del 4 al 7 son entradas
  PTAPE_PTAPE2 = 1;
 
  for(;;) {
	  
		PTBD = arreglo[j];
		delay_medio_segundo();
		if(PTAD_PTAD2 == 0){
			j++;
			if(j==4)
				j=0;
		}else{
			j--;
			if(j==255) //le dimos la vuelta al rango de 0 a 255 de los 8 bits de j
				j=3;
			
		}
  } /* loop forever */
}
