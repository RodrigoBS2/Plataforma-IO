#include <STM32FreeRTOS.h>
#include "timer_manager.h"
//#include "sensores_manager.h"
#include "sensorgy80.h"
#include <string>
using namespace std;


/* ------------------------------------ Variáveis ----------------------------------------------------------- */
// Estação base
String valor=""; // Irá receber o duty cycle
char Comando; // Irá receber o sentido do giro do motor
//Ponte H - pinos responsaveis para mudar o sentido do motor 
uint8_t IN1 = PA2;     // Sentido anti-horário
uint8_t IN2 = PA3;    // Sentido Horário
//Motor
uint8_t velocidade = PA1; // pino do ENA da ponte H - Pino que irá receber o sinal PWM 
uint8_t duty_cycle;
// Sensor gy-80: variaveis e objeto 
GY_80 Snr = GY_80(); // Objeto da classe GY_80 
double *dado; /* Essa variével ira receber os dados do sensor. Ela irá apontar par um vetor de tamanho 3.
                    Os 3 são para VECTOR_GYROSCOPE
                  */
bool print = false;
uint8_t LOOP = 0; 
//Declaração dos Timers
TIM_TypeDef *Instance2 = TIM2;  // Para a função de incremento do PWM
TIM_TypeDef *Instance3 = TIM3;  // Equação de controle
// Declaração do objeto para TIM2 e TMI3 para poder usar as funções do timer
HardwareTimer *MyTimer2 = new HardwareTimer(Instance2);
HardwareTimer *MyTimer3 = new HardwareTimer(Instance3);

/* ------------------------------------------------------------------------------------------------------------ */



/* ---------------------------------------- Comunicação serial ------------------------------------------------ */
// Comnunicação Serial com a VScode e computador
//                      RX    TX
HardwareSerial Serial1(PA10, PA9);
//                      RX    TX
HardwareSerial Serial3(PB11, PB10);   // VScode
/* ------------------------------------------------------------------------------------------------------------ */

/*------------------------------------- Definição das Tasks -------------------------------------*/ 
void Dados_do_sensor( void *pvParameters ); // Função para enviar dados do sensor BNO055
void Comandos_EB( void *pvParameters ); // Função para receber comandos da estação base
/*--------------------------------------------------------------------------------------------------*/


// Função para mudar o sentido do giro do motor
void sentido_giro(char x){
  // Sentido horário
  if(x == 'H'){
    digitalWrite(IN1,HIGH);
    digitalWrite(IN2,LOW);
    Serial1.println("Sentido horario");
    
  }
  // Sentido anti-horário
  if(x == 'A'){
    digitalWrite(IN1,LOW);
    digitalWrite(IN2,HIGH);
    Serial1.println("Sentido anti horario");
    
   
  }
}


/*-------------------------------------------------------- SETUP ----------------------------------------------------------------------*/ 
void setup() {
  Serial1.begin(115200); // taxa de transimissão para o IDE 
  Serial3.begin(9600); // Taxa de transmissão para a estação base (conexão bluetooth)
 
  // Inicializando o Sensor GY-80
  if(Snr.begin()== true){
    Serial1.println("Obtendo dados do sensor"); 
  }
  
  // Configuração dos pinos da ponte H
  pinMode(velocidade, OUTPUT);
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  // Ponte H inicialmente desligada
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,LOW);
    
  

  //Configurando a task Dados_do_sensor para rodar de maneira independente
   xTaskCreate(
    Dados_do_sensor
    ,  (const portCHAR *)"Dados_do_sensor"   // Nome
    ,  128  // This stack size can be checked & adjusted by reading the Stack Highwater
    ,  NULL
    ,  2  // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
    ,  NULL );

    xTaskCreate(
    Comandos_EB
    ,  (const portCHAR *)"Comandos_EB"   // Nome
    ,  128  // This stack size can be checked & adjusted by reading the Stack Highwater
    ,  NULL
    ,  2  // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
    ,  NULL );

  //Configurando PWM
  configurePWM(MyTimer2, 2, velocidade, 1000);
  resumeTimer(MyTimer2);

  
  // Rodando as tasks
  vTaskStartScheduler(); // Coloca esse comando por útlimo se não qualquer comando abaixo dele não será executado.

}

void loop() {
  // put your main code here, to run repeatedly:

}
/*------------------------------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------- Implementação das Task --------------------------------------------------- */
void Dados_do_sensor(void *pvParameters){
  (void) pvParameters;
  for (;;){ 
    Snr.update_GY_data();
    if(print == true){
      Snr.get_GY_data(&dado);
      //VECTOR_GYROSCOPE
      Serial3.println(*dado,1);dado = 1 + dado;
      Serial3.println(*dado,1);dado = 1 + dado;
      Serial3.println(*dado,1);dado = 1 + dado;
      // Final da informação
      Serial3.println("O");
      vTaskDelay( 1000 / portTICK_PERIOD_MS ); // wait for one second
      LOOP = LOOP + 1;
      if(LOOP == 10){
        print = false;
        LOOP = 0;
        stopPWM(MyTimer2, 2);
        //Finalização da seqûencia de informações
        Serial3.println("F");

      }
    }    
  }
}

void Comandos_EB( void *pvParameters ){
  (void) pvParameters;
  for(;;){
    /* Avaliando se a dados na serial enviados via bluetooth. 
    A mensagem recebida pela serial: o primeiro caractere diz 
    sobre o sentido do giro (H -> horário, A -> anti-horário) 
    e os caracteres restante definem o duty cycle. */
    if(Serial3.available()){    
      Comando = Serial3.read(); // Irá ler o sentido do motor
      Serial1.println(Comando);
      if(Comando == 'H' || Comando == 'A'){    
        valor = Serial3.readStringUntil('\r'); // Irá ler o valor do duty cycle
        duty_cycle = valor.toInt();
        // Avaliando o duty cycle:
        if(duty_cycle >= 0 && duty_cycle <= 100){    
          sentido_giro(Comando);
          Serial1.print("Duty Cycle: ");
          Serial1.println(duty_cycle);
          //Girando o motor. Seu duty cycle se da pela variável "duty_cycle" q varia de 0 a 100
          setPWM(MyTimer2, 2, duty_cycle);     
          print = true; // Irá permitir a transmissão dos dados do sensor via bluetooth na função Dados_do_sensor
        }
        else{    
          //Serial1.println("ERRO!Tente novamente.");
        }
      }
    }
  }
}
/*------------------------------------------------------------------------------------------------------*/