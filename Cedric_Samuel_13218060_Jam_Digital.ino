/*******************************************************
Project : Tugas Jam Digital
Nama    : Cedric Samuel 
NIM     : 13218060  
*******************************************************/

#include <TimerOne.h>
#define A 11
#define B 7
#define C 4 
#define D 0 
#define E 1
#define F 10
#define G 5

// Common Anode Pins 
#define CA1 12
#define CA2 9
#define CA3 8
#define CA4 6

// Interrupt pin
int pin_2=2;
int pin_3=3;

// Alarm pin
int pin_13=13;

const int segment[7] = {A,B,C,D,E,F,G};
int i; 

int arr_0[7] = {0,0,0,0,0,0,1};       //angka 0
int arr_1[7] = {1,0,0,1,1,1,1};       //angka 1
int arr_2[7] = {0,0,1,0,0,1,0};       //angka 2
int arr_3[7] = {0,0,0,0,1,1,0};       //angka 3
int arr_4[7] = {1,0,0,1,1,0,0};       //angka 4
int arr_5[7] = {0,1,0,0,1,0,0};       //angka 5
int arr_6[7] = {0,1,0,0,0,0,0};       //angka 6
int arr_7[7] = {0,0,0,1,1,1,1};       //angka 7
int arr_8[7] = {0,0,0,0,0,0,0};       //angka 8
int arr_9[7] = {0,0,0,0,1,0,0};       //angka 9

void setup() {
  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(C, OUTPUT);
  pinMode(D, OUTPUT);
  pinMode(E, OUTPUT);
  pinMode(F, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(CA1, OUTPUT);
  pinMode(CA2, OUTPUT);
  pinMode(CA3, OUTPUT);
  pinMode(CA4, OUTPUT);
  pinMode(pin_2, INPUT);
  pinMode(pin_3, INPUT);
  pinMode(pin_13, OUTPUT);
  Timer1.initialize(1000000); 
  Timer1.attachInterrupt(blink1);
  //ISR_PCINT - untuk tampilan mode 2 (display jam dan menit) 
  attachInterrupt(digitalPinToInterrupt(2), ISR_PCINT, HIGH);
  //ISR_stopwatch - untuk mode stopwatch
  attachInterrupt(digitalPinToInterrupt(3), ISR_stopwatch, HIGH);  
}

// fungsi print / display 7 segment
void display7seg (int number)
{
  if(number==0)
    {
      for(i=0;i<7;i++)
      {digitalWrite(segment[i],arr_0[i]);};
    }
  else if(number==1)
    {
      for(i=0;i<7;i++)
      {digitalWrite(segment[i],arr_1[i]);};
    }
  else if(number==2)
    {
      for(i=0;i<7;i++)
      {digitalWrite(segment[i],arr_2[i]);};
    }
  else if(number==3)
    {
      for(i=0;i<7;i++)
      {digitalWrite(segment[i],arr_3[i]);};
    }
  else if(number==4)
    {
      for(i=0;i<7;i++)
      {digitalWrite(segment[i],arr_4[i]);};
    }
  else if(number==5)
    {
      for(i=0;i<7;i++)
      {digitalWrite(segment[i],arr_5[i]);};
    }
  else if(number==6)
    {
      for(i=0;i<7;i++)
      {digitalWrite(segment[i],arr_6[i]);};
    }
  else if(number==7)
    {
      for(i=0;i<7;i++)
      {digitalWrite(segment[i],arr_7[i]);};
    }
  else if(number==8)
   {
      for(i=0;i<7;i++)
      {digitalWrite(segment[i],arr_8[i]);};
    }
  else if(number==9)
    {
      for(i=0;i<7;i++)
      {digitalWrite(segment[i],arr_9[i]);};
    }
}

long int counter=225810;      // counter merupakan variabel yang menyimpan waktu saat ini 
long int alarm=225820;        // alarm merupakan variabel yang menyimpan waktu kapan alarm akan berbunyi (alarm akan menyala)
long int stopwatch_counter=0; // stopwatch menampilkan menit dan detik
int mode=1;
int mode_stopwatch=0;
void blink1(void)
{ 
 counter=counter+1;
 stopwatch_counter=stopwatch_counter+1;
}

void loop() {
  int ratusan_ribu, puluhan_ribu, satuan_ribu, ratusan, puluhan, satuan;
  // digunakan tanda >= untuk mengatasi masalah ketika interupsi terjadi di detik ke-59
  //kasus menit-detik
  if((counter%100)>=60) 
    {counter = counter+40;};

  //kasus jam-menit
  if((counter%10000) >=6000) 
    {counter=counter+4000;};

  //kasus 23:59:59 ke 00:00:00
  if(counter>=240000) 
    {counter=0;};

  //kasus alarm 
  if(alarm==counter)
    {
      digitalWrite(pin_13, HIGH);
      delay(500);
      digitalWrite(pin_13, LOW);
      delay(500);
      digitalWrite(pin_13, HIGH);
      delay(500);
      digitalWrite(pin_13, LOW);
      delay(500);
    };  

  ratusan_ribu = (counter/100000);
  puluhan_ribu = ((counter%100000)/10000);
  satuan_ribu = ((counter%10000)/1000);
  ratusan = ((counter%1000)/100);
  puluhan = ((counter%100)/10);
  satuan = (counter%10);

 //display mode 2 (jam dan menit)
  if(mode==2)
  {   
 //display angka ratusan_ribu
 digitalWrite(CA1, HIGH);
 digitalWrite(CA2, LOW);
 digitalWrite(CA3, LOW);
 digitalWrite(CA4, LOW);
 display7seg(ratusan_ribu);
 delay(500);

//display angka puluhan_ribu
 digitalWrite(CA1, LOW);
 digitalWrite(CA2, HIGH);
 digitalWrite(CA3, LOW);
 digitalWrite(CA4, LOW);
 display7seg(puluhan_ribu);
 delay(500);

 //display angka satuan_ribu
 digitalWrite(CA1, LOW);
 digitalWrite(CA2, LOW);
 digitalWrite(CA3, HIGH);
 digitalWrite(CA4, LOW);
 display7seg(satuan_ribu);
 delay(500);

 //display angka ratusan
 digitalWrite(CA1, LOW);
 digitalWrite(CA2, LOW);
 digitalWrite(CA3, LOW);
 digitalWrite(CA4, HIGH);
 display7seg(ratusan);
 delay(500);
  mode=1;
  };

 //kasus stopwatch
 if(mode_stopwatch==1)
 {
  int ratusan_ribu_stopwatch, puluhan_ribu_stopwatch, satuan_ribu_stopwatch, ratusan_stopwatch, puluhan_stopwatch, satuan_stopwatch;
  //kasus menit-detik
  if((stopwatch_counter%100)>=60) 
    {stopwatch_counter = stopwatch_counter+40;};

  //kasus jam-menit
  if((stopwatch_counter%10000) >=6000) 
    {stopwatch_counter=stopwatch_counter+4000;};

  ratusan_ribu_stopwatch = (stopwatch_counter/100000);
  puluhan_ribu_stopwatch = ((stopwatch_counter%100000)/10000);
  satuan_ribu_stopwatch = ((stopwatch_counter%10000)/1000);
  ratusan_stopwatch = ((stopwatch_counter%1000)/100);
  puluhan_stopwatch = ((stopwatch_counter%100)/10);
  satuan_stopwatch = (stopwatch_counter%10);

 //display angka satuan_ribu_stopwatch
 digitalWrite(CA1, HIGH);
 digitalWrite(CA2, LOW);
 digitalWrite(CA3, LOW);
 digitalWrite(CA4, LOW);
 display7seg(satuan_ribu_stopwatch);
 delay(3);

 //display angka ratusan_stopwatch
 digitalWrite(CA1, LOW);
 digitalWrite(CA2, HIGH);
 digitalWrite(CA3, LOW);
 digitalWrite(CA4, LOW);
 display7seg(ratusan_stopwatch);
 delay(3);

//display angka puluhan_stopwatch
 digitalWrite(CA1, LOW);
 digitalWrite(CA2, LOW);
 digitalWrite(CA3, HIGH);
 digitalWrite(CA4, LOW);
 display7seg(puluhan_stopwatch);
 delay(3);

 //display angka satuan_stopwatch
 digitalWrite(CA1, LOW);
 digitalWrite(CA2, LOW);
 digitalWrite(CA3, LOW);
 digitalWrite(CA4, HIGH);
 display7seg(satuan_stopwatch);
 delay(3);  
 };

 if(mode_stopwatch==0){ 
 // display mode 1 (menit dan detik)
 //display angka satuan_ribu
 digitalWrite(CA1, HIGH);
 digitalWrite(CA2, LOW);
 digitalWrite(CA3, LOW);
 digitalWrite(CA4, LOW);
 display7seg(satuan_ribu);
 delay(3);

 //display angka ratusan
 digitalWrite(CA1, LOW);
 digitalWrite(CA2, HIGH);
 digitalWrite(CA3, LOW);
 digitalWrite(CA4, LOW);
 display7seg(ratusan);
 delay(3);

//display angka puluhan
 digitalWrite(CA1, LOW);
 digitalWrite(CA2, LOW);
 digitalWrite(CA3, HIGH);
 digitalWrite(CA4, LOW);
 display7seg(puluhan);
 delay(3);

 //display angka satuan
 digitalWrite(CA1, LOW);
 digitalWrite(CA2, LOW);
 digitalWrite(CA3, LOW);
 digitalWrite(CA4, HIGH);
 display7seg(satuan);
 delay(3);
 };
}

// ISR_PCINT berfungsi untuk mengubah mode tampilan (dari menit-detik menjadi jam-menit)
void ISR_PCINT() 
{
  if (mode == 1){
    mode = 2;
  } 
};

//ISR_stopwatch berfungsi untuk mengatur start dan stop dari mode stopwatch
void ISR_stopwatch() 
{
  if (mode_stopwatch==0){
    mode_stopwatch=1;
    stopwatch_counter=0;
  }
  else
     {mode_stopwatch=0;};
};
