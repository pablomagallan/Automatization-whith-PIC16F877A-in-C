#include <16F877A.H>
#include <stdio.h>
#use delay(clock=4M)                           // Clock usado 4MHz
#fuses XT,NOWDT            // (para 16F877A)


#use fast_io(a)                                // Optimiza manejo pines de E/S
#use fast_io(b)                                // Optimiza manejo pines de E/S
#use fast_IO(d)                                // Optimiza manejo pines de E/S

#include <lcd.c>                               // Driver para display LCD

//#define LCD_DATA_PORT getenv("SFR:PORTD")      //Se define puerto para el LCD

#byte PORTA = 5                                // Direccion de la puerta A
#byte PORTB = 6                                // Direccion de la puerta B
#byte TMR0  = 1

#bit           LED_ROJO = PORTB.0        // Salida LED 10mA, 2.2V
#bit  ELECVALV_LLENAR_F = PORTB.1        // Salida Electrobalbula agua fria
#bit  ELECVALV_LLENAR_C = PORTB.2        // Salida Electrobalbula agua caliente
#bit   ELECBOMBA_VACIAR = PORTB.3        // Salida electrobomba para vaciar
#bit              ENTER = PORTB.4        // Entrada tecla enter (LSB)
#bit               MODO = PORTB.5        // Entrada tecla modo
#bit   PRESOSTATO_LLENO = PORTB.6        // Entrada presostato nivel alto
#bit   PRESOSTATO_VACIO = PORTB.7        // Entrada presostato nivel bajo

#bit              MOTOR = PORTA.0
#bit            SPEAKER = PORTA.1

int a = 0;  // 20*aux = 1 seg.
int segundos = 0;
int minutos = 0;

#int_TIMER0

void TIMER0_isr (void) {  
   
   if (a == 20){
      a = 0;
      if (segundos == 59) {
      
         segundos = 0;
         minutos++;
         
      }
      else segundos++;
   
   }
   else a++;
   set_timer0 (0x3C); // 3C = 60
   
}

/////////////////////////////////////////////// FINAL //////////////////////////////////////////////////////

void final (){  // activacion del speaker al finalizar el programa seleccionado

   SPEAKER=1;
   delay_ms(700);
   SPEAKER=0;
   delay_ms(500);
   SPEAKER=1;
   delay_ms(700);
   SPEAKER=0;
   delay_ms(500);
   SPEAKER=1;
   delay_ms(700);
   SPEAKER=0;
   
}

/////////////////////////////////////////////// MODO1 ///////////////////////////////////////////////////////

void MODO1 () {

   minutos = segundos = a = 0;
   
   LED_ROJO = 0;
   ELECVALV_LLENAR_C = 1;
   
   lcd_gotoxy(1,1);
   lcd_putc("\fLLENANDO...");
   
   while (PRESOSTATO_LLENO == 1);
   
   ELECVALV_LLENAR_C = 0;
   MOTOR = 1;
   
   lcd_gotoxy(1,1);
   lcd_putc("\fLAVARROPAS LLENO");
   lcd_gotoxy(1,2);
   lcd_putc("LAVANDO...");
   
   // delay 30 minutos:
   setup_timer_0 ( RTCC_INTERNAL | RTCC_DIV_256 );
   set_timer0 (0x3C);
   enable_interrupts (INT_TIMER0);
   enable_interrupts (GLOBAL);
   while (minutos == 0);         // Cuando pasan 30 minutos sale del bucle inf.
   minutos = segundos = a = 0;
   
   MOTOR = 0;
   ELECBOMBA_VACIAR = 1;
   
   lcd_gotoxy(1,1);
   lcd_putc("\fLAVADO TERMINADO");
   lcd_gotoxy(1,2);
   lcd_putc("VACIANDO...");
   
   while (PRESOSTATO_VACIO == 0);
   
   ELECBOMBA_VACIAR = 0;
   ELECVALV_LLENAR_F = 1;
   
   lcd_gotoxy(1,1);
   lcd_putc("\fVACIADO LISTO");
   lcd_gotoxy(1,2);
   lcd_putc("LLENANDO...");
   
   while (PRESOSTATO_LLENO == 1);
   
   ELECVALV_LLENAR_F = 0;
   MOTOR = 1;
   
   lcd_gotoxy(1,1);
   lcd_putc("\fLAVARROPAS LLENO");
   lcd_gotoxy(1,2);
   lcd_putc("ENJUAGANDO...");
   
   // delay 10 minutos:
   set_timer0 (0x3C);
   enable_interrupts (INT_TIMER0);
   enable_interrupts (GLOBAL);
   while (minutos == 0);           // Cuando pasan 15 minutos sale del bucle inf.
   minutos = segundos = a = 0;
   
   MOTOR = 0;
   ELECBOMBA_VACIAR = 1;
   
   lcd_gotoxy(1,1);
   lcd_putc("\fENJUAGADO LISTO");
   lcd_gotoxy(1,2);
   lcd_putc("VACIANDO...");
   
   while (PRESOSTATO_VACIO == 0);
   delay_ms (10000);
   ELECBOMBA_VACIAR = 0;
   
}

/////////////////////////////////////////////// MODO2 ///////////////////////////////////////////////////////        

void MODO2 () {

   minutos = segundos = a = 0;
   
   LED_ROJO = 0;
   ELECVALV_LLENAR_C = 1;
   
   lcd_gotoxy(1,1);
   lcd_putc("\fLLENANDO...");
   
   while (PRESOSTATO_LLENO == 1);
   
   ELECVALV_LLENAR_C = 0;
   MOTOR = 1;
   
   lcd_gotoxy(1,1);
   lcd_putc("\fLAVARROPAS LLENO");
   lcd_gotoxy(1,2);
   lcd_putc("LAVANDO...");
   
   // delay 15 minutos:
   set_timer0 (0x3C);
   enable_interrupts (INT_TIMER0);
   enable_interrupts (GLOBAL);
   while (minutos != 15);        // Cuando pasan 15 minutos sale del bucle inf.
   minutos = segundos = a = 0;
   
   MOTOR = 0;
   ELECBOMBA_VACIAR = 1;
   
   lcd_gotoxy(1,1);
   lcd_putc("\fLAVADO TERMINADO");
   lcd_gotoxy(1,2);
   lcd_putc("VACIANDO...");
   
   while (PRESOSTATO_VACIO == 0);
   
   ELECBOMBA_VACIAR = 0;
   ELECVALV_LLENAR_F = 1;
   
   lcd_gotoxy(1,1);
   lcd_putc("\fVACIADO LISTO");
   lcd_gotoxy(1,2);
   lcd_putc("LLENANDO...");
   
   while (PRESOSTATO_LLENO == 1);
   
   ELECVALV_LLENAR_F = 0;
   MOTOR = 1;
   
   lcd_gotoxy(1,1);
   lcd_putc("\fLAVARROPAS LLENO");
   lcd_gotoxy(1,2);
   lcd_putc("ENJUAGANDO...");
   
   // delay 10 minutos:
   set_timer0 (0x3C);
   enable_interrupts (INT_TIMER0);
   enable_interrupts (GLOBAL);
   while (minutos != 10);           // Cuando pasan 10 minutos sale del bucle inf.
   minutos = segundos = a = 0;
   
   MOTOR = 0;
   ELECBOMBA_VACIAR = 1;
   
   lcd_gotoxy(1,1);
   lcd_putc("\fENJUAGADO LISTO");
   lcd_gotoxy(1,2);
   lcd_putc("VACIANDO...");
   
   while (PRESOSTATO_VACIO == 0);
   delay_ms (10000);
   ELECBOMBA_VACIAR = 0;

}         

/////////////////////////////////////////////// MODO3 ///////////////////////////////////////////////////////

void MODO3 () {

   minutos = segundos = a = 0;
   
   LED_ROJO = 0;
   ELECVALV_LLENAR_F = 1;
   
   lcd_gotoxy(1,1);
   lcd_putc("\fLLENANDO...");
   
   while (PRESOSTATO_LLENO == 1);
   
   ELECVALV_LLENAR_F = 0;
   MOTOR = 1;
   
   lcd_gotoxy(1,1);
   lcd_putc("\fLAVARROPAS LLENO");
   lcd_gotoxy(1,2);
   lcd_putc("LAVANDO...");
   
   // delay 30 minutos
   set_timer0 (0x3C);
   enable_interrupts (INT_TIMER0);
   enable_interrupts (GLOBAL);
   while (minutos !=30 );           // Cuando pasan 30 minutos sale del bucle inf.
   minutos = segundos = a = 0;
   
   MOTOR = 0;
   ELECBOMBA_VACIAR = 1;
   
   lcd_gotoxy(1,1);
   lcd_putc("\fLAVADO TERMINADO");
   lcd_gotoxy(1,2);
   lcd_putc("VACIANDO...");
   
   while (PRESOSTATO_VACIO == 0);
   
   ELECBOMBA_VACIAR = 0;
   ELECVALV_LLENAR_F = 1;
   
   lcd_gotoxy(1,1);
   lcd_putc("\fVACIADO LISTO");
   lcd_gotoxy(1,2);
   lcd_putc("LLENANDO...");
   
   while (PRESOSTATO_LLENO == 1);
   
   ELECVALV_LLENAR_F = 0;
   MOTOR = 1;
   
   lcd_gotoxy(1,1);
   lcd_putc("\fLAVARROPAS LLENO");
   lcd_gotoxy(1,2);
   lcd_putc("ENJUAGANDO...");
   
   // delay 10 minutos
   set_timer0 (0x3C);
   enable_interrupts (INT_TIMER0);
   enable_interrupts (GLOBAL);
   while (minutos != 15);           // Cuando pasan 15 minutos sale del bucle inf.
   minutos = segundos = a = 0;
   
   MOTOR = 0;
   ELECBOMBA_VACIAR = 1;
   
   lcd_gotoxy(1,1);
   lcd_putc("\fENJUAGADO LISTO");
   lcd_gotoxy(1,2);
   lcd_putc("VACIANDO...");
   
   while (PRESOSTATO_VACIO == 0);
   delay_ms (10000);
   ELECBOMBA_VACIAR = 0;

}         
//////////////////////////////////////////////PROGRAMA PRINCIPAL///////////////////////////////////////////////

int main () {


   // Configuro Puertos:
   set_tris_a (0x00);  // configuro puerto A (SALIDA)
   set_tris_b (0xF0);  // configuro puerto B (SALIDA-ENTRADAS)

   // Configuro TIMER0:
   setup_timer_0 ( RTCC_INTERNAL | RTCC_DIV_256 );
   
   // Inicializo LCD:
   lcd_init();
   
   int ent=1,num_modo=0,m1=1,m2=2,m3=3;
   ELECVALV_LLENAR_C = 0;
   ELECVALV_LLENAR_F = 0;
   LED_ROJO = 1;                             //led apagado.
   lcd_gotoxy(1,1);
   lcd_putc("\fSELECCIONE MODO");
   
   while (1) {

      while (ent){
      
         if (ENTER == 1){
            
            if (MODO == 0){               // seleccion de modo
               
               while(MODO == 0);          // antirrebotes
               
               num_modo++; // se incrementa por cada pulsacion de la tecla seleccion de modo
              
               if(num_modo==4){
                  num_modo=1;
               } 
               
               if(num_modo==1){
                  lcd_gotoxy(1,1);
                  lcd_putc("\fMODO 1");
                  lcd_gotoxy(1,2);
                  lcd_putc("LAVADO NORMAL");
               }
               else {
                  if (num_modo==2){
                     lcd_gotoxy(1,1);
                     lcd_putc("\fMODO 2");
                     lcd_gotoxy(1,2);
                     lcd_putc("LAVADO RAPIDO");
                  }
                  else {                                 //modo=3
                     lcd_gotoxy(1,1);
                     lcd_putc("\fMODO 3");
                     lcd_gotoxy(1,2);
                     lcd_putc("LAVADO AGUA FRIA");
                  }
               }
            }
         }
         
         else{
            if(num_modo != 0){
               ent=0;
               a=num_modo;
            }
         }                     // bucle infinito: espera interrupcion
      }
      
      // se presiono la tecla ENTER
      
      if (num_modo == m1){
      
         MODO1();
      
         lcd_gotoxy(1,1);
         lcd_putc("\fLAVADO TERMINADO");
         lcd_gotoxy(1,2);
         lcd_putc("TENDER ROPA");
         LED_ROJO = 1;
         final();
         num_modo=0;
         ent=1;
         while (ent) {
            if (ENTER == 0){
               ent=0;
            }
         }
         ent=1;
         lcd_gotoxy(1,1);
         lcd_putc("\fSELECCIONE MODO");
      }
      
      if (num_modo==m2){
      
         MODO2();
      
         lcd_gotoxy(1,1);
         lcd_putc("\fLAVADO TERMINADO");
         lcd_gotoxy(1,2);
         lcd_putc("TENDER ROPA");
         LED_ROJO = 1;
         final();
         num_modo=0;
         ent=1;
         while (ent) {
            if (ENTER == 0){
               ent=0;
            }
         }
         ent=1;
         lcd_gotoxy(1,1);
         lcd_putc("\fSELECCIONE MODO");
      }
      
      if (num_modo==m3){
      
         MODO3();
      
         lcd_gotoxy(1,1);
         lcd_putc("\fLAVADO TERMINADO");
         lcd_gotoxy(1,2);
         lcd_putc("TENDER ROPA");
         LED_ROJO = 1;
         final();
         num_modo=0;
         ent=1;
         while (ent) {
            if (ENTER == 0){
               ent=0;
            }
         }
         ent=1;
         lcd_gotoxy(1,1);
         lcd_putc("\fSELECCIONE MODO");
      }
      
      ELECVALV_LLENAR_C = 0;
      ELECVALV_LLENAR_F = 0;
      
   }
   
}
