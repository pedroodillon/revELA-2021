 
  
int EMG_sensor_1 = A0; // Pino para ler os dados do primeiro sensor
int EMG_sensor_2 = A1; // Pino para ler os dados do segundo sensor
int EMG_sensor_3 = A2; // Pino para ler os dados do terceiro sensor
int EMG_sensor_4 = A3; // Pino para ler os dados do quarto sensor

int PWM_MOTOR_1 = 3; // Pino para escrever no primeiro motor
int PWM_MOTOR_2 = 11; // Pino para escrever no primeiro motor
int PWM_MOTOR_3 = 10; // Pino para escrever no primeiro motor
int PWM_MOTOR_4 = 9; // Pino para escrever no primeiro motor
  
int  EMG_pure1 = 0; // Variável para armazenar os valores lidos do primeiro sensor 
int  EMG_pure2 = 0; // Variável para armazenar os valores lidos do primeiro sensor 
int  EMG_pure3 = 0; // Variável para armazenar os valores lidos do primeiro sensor 
int  EMG_pure4 = 0; // Variável para armazenar os valores lidos do primeiro sensor

long EMG_filter_1 = 0; // Variável para armazenar os valores filtrados do primeiro sensor
long EMG_filter_2 = 0;  // Variável para armazenar os valores filtrados no segundo sensor
long EMG_filter_3 = 0; // Variável para armazenar os valores filtrados no terceiro sensor
long EMG_filter_4 = 0; // Variável para armazenar os valores filtrados no quarto sensor

int PWM_8BITS = 0; // Variável para escrever no PWM do primeiro motor

// Parâmetros para a média móvel
int amostras = 50;  // Quantidade de amostras para realizar a média móvel 
int numbers[50];  // Vetor para guardar amostras do primeiro sensor
long moving_average(int EMG_filter); // Protótipo da função de média móvel


void setup() {
  Serial.begin(115200); // Iniciando a UART
}

void loop() {

  amostras = 50;
  PWM_8BITS = 0;

  EMG_pure1 = analogRead(EMG_sensor_1); // Lendo os dados do sensor
  EMG_filter_1 = moving_average(EMG_pure1);
  PWM_8BITS = (EMG_filter_1 >> 2);
  analogWrite(PWM_MOTOR_1, PWM_8BITS);

  amostras = 50;
  PWM_8BITS = 0;

  EMG_pure2 = analogRead(EMG_sensor_2); // Lendo os dados do sensor
  EMG_filter_2 = moving_average(EMG_pure2);
  PWM_8BITS = (EMG_filter_2 >> 2);
  analogWrite(PWM_MOTOR_2, PWM_8BITS);

  amostras = 50;
  PWM_8BITS = 0;

  EMG_pure3 = analogRead(EMG_sensor_3); // Lendo os dados do sensor
  EMG_filter_3 = moving_average(EMG_pure3);
  PWM_8BITS = (EMG_filter_3 >> 2);
  analogWrite(PWM_MOTOR_3, PWM_8BITS);

  amostras = 50;
  PWM_8BITS = 0;

  EMG_pure4 = analogRead(EMG_sensor_4); // Lendo os dados do sensor
  EMG_filter_4 = moving_average(EMG_pure4);
  PWM_8BITS = (EMG_filter_4 >> 4);
  analogWrite(PWM_MOTOR_4, PWM_8BITS);

  Serial.print(EMG_filter_1);   // Enviando os dados pela serial do sinal filtrado do primeiro sensor
  Serial.print(",");          // Caracter de divisão de dados
  Serial.print(EMG_filter_2); // Enviando os dados pela serial do sinal filtrado do segundo sensor
  Serial.print(",");
  Serial.print(EMG_filter_3);
  Serial.print(",");
  Serial.println(EMG_filter_4);

  //delay(100);
}

long moving_average(int EMG_pure)
{
  
  for(int i = amostras-1; i > 0; i-- )
  {
    numbers[i] = numbers[i-1];
  }  

  long average = 0;

  numbers[0] = EMG_pure;

  for(int i = 0; i < amostras; i++){
    average = average + numbers[i];
    }
/*
   for(int i = 0; i < amostras; i++)
   {
      numbers[i] = 0;
   }
*/   
  
  return (average/amostras);

}
