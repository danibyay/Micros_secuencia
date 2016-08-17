#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */

unsigned char arreglo[] = {0x0E, 0x0D, 0x0B, 0x07}; //char para 8 bits

void delay_chafa(){
	unsigned int i;
	for(i=0; i<50000; i++){
		__RESET_WATCHDOG();
	}
}

void main(void) {
	unsigned char j = 0; //LAS VARIABLES SE TIENEN QUE DECLARAR ANTES DE CUALQUIER INSTRUCCION
  EnableInterrupts;
  /* include your code here */
  PTBDD =  0x0F; //del 0 al 3 son salidas, y del 4 al 7 son entradas
 
  for(;;) {
	  
		PTBD = arreglo[j];
		delay_chafa();
		if(PTBD_PTBD4 == 0){
			j++;
			if(j==4)
				j=0;
		}else{
			j--;
			if(j==255) //le dimos la vuelta al rango de 0 a 255 de los 8 bits de j
				j=3;
			
		}
	  /*PTBD = 0x0E; // 00001110 
	delay_chafa();
	PTBD = 0x0D;
	delay_chafa();
	PTBD = 0x0B;
	delay_chafa();
	PTBD = 0x07; 
	delay_chafa(); */
  } /* loop forever */
}
