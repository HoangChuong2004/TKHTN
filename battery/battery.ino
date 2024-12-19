#include <LiquidCrystal.h>
// Nút nhấn 0.5A
int button1 = 1;
//Nút nhấn 1A
int button2 = 2;
int button3 = 0;
 //led 0.5 A
int led1 = 11;
//led 1 A
int led2 = 12; 
LiquidCrystal LCD(9, 8, 6, 5, 4, 3);
double AcsOffset=2.47; 
double Sensibl=0.066; 
double courant=0;
double tension=0;
int Control = 7;
const float BAT_LOW = 3.0;    // define điện áp nhỏ nhất của pin lion
const float BAT_HIGH = 4.5;   // define điện áp lớn nhất của pin lion
const int MOSFET_Pin=10;      // chân mosfet

unsigned long previousMillis = 0; // thời gian sau 
unsigned long millisPassed = 0;  // thời gian hiện tại
float Capacity=0;     
float Resistor=2.2;   
float mA;

void setup() {
 
  pinMode(button1, INPUT_PULLUP);  
  pinMode(button2, INPUT_PULLUP); //Cài đặt chân D11 ở trạng thái đọc dữ liệu
  pinMode(button3, INPUT_PULLUP);
  pinMode(led1,OUTPUT);
  pinMode(led2,OUTPUT);// Cài đặt chân D2 dưới dạng OUTPUT
  pinMode(Control,OUTPUT);
  pinMode(A1,INPUT);
  //Hien thi khoi dong LCD
    LCD.begin(16,2);
    LCD.setCursor(0,0);
    LCD.print("Battery Capacity");
    LCD.setCursor(0,1);
    LCD.print("Tester Circuit");
    delay(1000);
    LCD.clear();
    LCD.setCursor(0,0);
    LCD.print("HAY CHON DONG!");
    delay(1000);
    LCD.clear();
}

void loop() {
  double ValeurLue=analogRead(A0);
  tension=(ValeurLue*5.0/1023);
  courant=(tension-AcsOffset)/Sensibl;

 int adc;
 float Tam;
 unsigned long Dienap;
  adc = analogRead(A1);
    Tam = (5.0f/1023.0f)*(float)adc;
    Dienap = Tam;

    //LCD.setCursor(0,1);
    //LCD.print("Dienap=" + String(Tam) + "V"); 

  int buttonStatus1 = digitalRead(button1);//Đọc trạng thái button1
  int buttonStatus2 = digitalRead(button2);//Đọc trạng thái button2
  int pause = digitalRead(button3);
   int sensorValue_voltage_Cell = analogRead(A0);
   
 
  //Truong hop 1
  if (buttonStatus1 == LOW) { // Nếu mà button1 bị nhấn
    const int PWM_VALUE=75;        // giá trị pwm 50
    digitalWrite(led1,HIGH); // Đèn led1 sáng
    digitalWrite(led2,LOW);
    analogWrite(MOSFET_Pin, PWM_VALUE);
    // đọc tín hiệu tại chân A0
    int sensorValue_voltage_Cell = analogRead(A2);
    // chuyển sang số có giá trị từ 0 đến 1023 ứng với 0 đến 5V
    float voltage = sensorValue_voltage_Cell * (5.12 / 1023.0)*1.2;
    if(voltage > BAT_LOW && voltage < BAT_HIGH){
    LCD.setCursor(0, 0); // đưa con trỏ vào cột một hàng một
    LCD.print("Voltage: "); // hiển thị Voltage lên màn lcd
    LCD.print(voltage);   // hiển thị giá trị điện áp đọc được
    LCD.print("V");
    delay(100);
    int sensorValue_Shunt_Resistor= analogRead(A3);
    float voltage1= sensorValue_Shunt_Resistor *(5.00 / 1023.0);
    float current= voltage1/Resistor;
    LCD.setCursor(0, 1); //đưa con trỏ về cột 1 hang 2
    LCD.print("Current: ");
    LCD.print(current);
    LCD.print("A");
    }
     else if ( voltage > BAT_HIGH)
  {
    //digitalWrite(10, LOW);
    //digitalWrite(11, LOW);
    //digitalWrite(12, HIGH);
    digitalWrite(MOSFET_Pin, LOW);    // tắt mosfet
    LCD.clear();
    LCD.setCursor(4,0);
    LCD.print("WARNING");
    LCD.setCursor(2,1);
    LCD.print("HIGH VOLTAGE!!");
    //delay(2000);
    //LCD.clear();
  }
  else if(voltage < BAT_LOW)
  {
     ///digitalWrite(10, HIGH);
    // digitalWrite(11, LOW);
     //digitalWrite(12, LOW);
      digitalWrite(MOSFET_Pin, LOW);      // tắt mosfet 
      LCD.clear();
      LCD.setCursor(4,0);
      LCD.print("WARNING");
      LCD.setCursor(2,1);
      LCD.print("LOW VOLTAGE!!!");
      //delay(2000);
      //LCD.clear();
  }
    //Hien thi LCD
    
    //LCD.setCursor(0,0);
   // LCD.print("I=");
    //LCD.print(courant);
    //LCD.print("A");

    //LCD.setCursor(9,0);
    //LCD.print("35 do C"); 
    digitalWrite(Control,HIGH);
   
    //--------------
  }
  if (buttonStatus2 == LOW) { // Nếu mà button2 bị nhấn
    digitalWrite(led1,LOW); // Đèn led2 sáng
    digitalWrite(led2,HIGH);
        const int PWM_VALUE=115;        // giá trị pwm 50
    analogWrite(MOSFET_Pin, PWM_VALUE);
    // đọc tín hiệu tại chân A0
    int sensorValue_voltage_Cell = analogRead(A2);
    // chuyển sang số có giá trị từ 0 đến 1023 ứng với 0 đến 5V
    float voltage = sensorValue_voltage_Cell * (5.12 / 1023.0)*1.2;
    if(voltage > BAT_LOW && voltage < BAT_HIGH){
    LCD.setCursor(0, 0); // đưa con trỏ vào cột một hàng một
    LCD.print("Voltage: "); // hiển thị Voltage lên màn lcd
    LCD.print(voltage);   // hiển thị giá trị điện áp đọc được
    LCD.print("V");
    delay(100);
    int sensorValue_Shunt_Resistor= analogRead(A3);
    float voltage1= sensorValue_Shunt_Resistor *(5.00 / 1023.0);
    float current= voltage1/Resistor;
    LCD.setCursor(0, 1); //đưa con trỏ về cột 1 hang 2
    LCD.print("Current: ");
    LCD.print(current);
    LCD.print("A");
    }
   else if ( voltage > BAT_HIGH)
  {
    //digitalWrite(10, LOW);
    //digitalWrite(11, LOW);
    //digitalWrite(12, HIGH);
    digitalWrite(MOSFET_Pin, LOW);    // tắt mosfet
    LCD.clear();
    LCD.setCursor(4,0);
    LCD.print("WARNING");
    LCD.setCursor(2,1);
    LCD.print("HIGH VOLTAGE!!");
    //delay(2000);
    //LCD.clear();
  }
  else if(voltage < BAT_LOW)
  {
     ///digitalWrite(10, HIGH);
    // digitalWrite(11, LOW);
     //digitalWrite(12, LOW);
      digitalWrite(MOSFET_Pin, LOW);      // tắt mosfet 
      LCD.clear();
      LCD.setCursor(4,0);
      LCD.print("WARNING");
      LCD.setCursor(2,1);
      LCD.print("LOW VOLTAGE!!!");
      //delay(2000);
      //LCD.clear();
  }
  
    //Hien thi LCD
    //LCD.setCursor(0,0);
    //LCD.print("I=");
    //LCD.print(courant);
    //LCD.print("A");

    //LCD.setCursor(9,0);
    //LCD.print("32 do C"); 
    digitalWrite(Control,HIGH);
   
    //----------------
}
if (pause == LOW) { // Nếu mà button2 bị nhấn
    digitalWrite(led1,LOW); // Đèn led2 sáng
    digitalWrite(led2,LOW);
    digitalWrite(Control,LOW);
     LCD.clear();
     LCD.setCursor(2,0);
     LCD.print("DA DUNG SAC!!");
     digitalWrite(MOSFET_Pin, LOW);  
}
  }