  //Sensör pinlerimizi tanımlıyoruz: 
#define sensor_pin A0
#define buzzer_pin 8
int sensorValue=0;
int DepremKontrolu=0;
int flame=4;
int deprem=7;
// LED'imizin çıkış pinlerini tanımlıyoruz:
#define led_g 10
#define led 13
#define led_d 9

// LCD Ekrranımızı ayarlıyrouz.
#include <LiquidCrystal.h> 
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

 //gaz sensörünün ön ısıtma süresini tanımlıyoruz
#define preheat_time 5000
//Alarmın çalması için gerekli eşik değerini 600 olarak belirliyoruz.   
#define threshold 600

void setup()
{
  Serial.println("Started...");
//Alarm için kullanacağımız buzzer ve LED'leri çıkış olarak tanımlıyoruz
pinMode(buzzer_pin, OUTPUT);
pinMode(led_g, OUTPUT);
//Sensör değerini seri monitörden görebilmemiz için seri haberleşmeyi başlatıyoruz:
Serial.begin(9600);
//İlk 5sn boyunca sensörün ısınmasını bekliyoruz.
Serial.println("Sensor isitiliyor...");
digitalWrite(led_g, LOW);
delay(preheat_time);
digitalWrite(led_g, LOW);
delay(1000);
}

void loop()
{

  //Alve ve Deprem sınıflarımızı çalıştırıyoruz.
  alev();
  deprem_m();
//analogRead() fonksiyonu ile gaz sensörü değerini ölçüyoruz ve bir değişken içerisinde tutuyoruz:
int sensorValue = analogRead(sensor_pin);
//Sensör değeri belirlediğimiz eşik değerinden yüksek ise alarm() fonksiyonunu çağırıyoruz:
if (sensorValue >= threshold)
alarm(100);
//Alarmın çalmadığı durumda LED'in yanmamasını istiyoruz:
else
digitalWrite(led_g, LOW);
lcd.clear();

//Sensör değerini bilgisayarımızdan görebilmek için seri monitöre yazıyoruz:
Serial.println(sensorValue);
delay(1);
}

//Gaz Sensörü için alarm fonksiyonu yazıyoruz:
void alarm(unsigned int duration)
{
//Buzzer'ın 440Hz'te (la notası) ses üretmesini istiyoruz:
tone(buzzer_pin, 440);

digitalWrite(led_g, HIGH);
lcd.begin(16, 2);
lcd.print("Gaz kacagi");
delay(duration);
noTone(buzzer_pin);
digitalWrite(led_g, HIGH);
delay(duration);
}

// Alev Sensörü için bir sınıf oluşturuyoruz:
void alev()
{
  // Çıkış değerlerini girip seri haberleşmeyi başlatıyoruz:
  Serial.begin(9600);
  pinMode(flame,INPUT);
  pinMode(led,OUTPUT);
  pinMode(buzzer_pin,OUTPUT);
  Serial.println("Started...");
  //Sensörden okunan veriyi kontrol edip alarmı ayarlıyoruz.
  sensorValue=digitalRead(flame);
 Serial.println("Sensor Value= "+String(sensorValue));
 delay(200);
 if(sensorValue==0) {
  digitalWrite(buzzer_pin,HIGH);
  digitalWrite(led,HIGH);
  lcd.begin(16,2);
  lcd.write("Yangin");
  delay(700);   
  lcd.clear();
  digitalWrite(led,LOW);
  digitalWrite(buzzer_pin,LOW);
 }
  else {
  lcd.clear();

  }
  }

   // Deprem Sensörü için bir sınıf oluşturuyoruz:
  void deprem_m () 
  {
    // Çıkış değerlerini girip seri haberleşmeyi başlatıyoruz:
  Serial.begin(9600);
  pinMode(deprem,INPUT);
  pinMode(led_d,OUTPUT);
  pinMode(buzzer_pin,OUTPUT);

   //Sensörden okunan veriyi kontrol edip alarmı ayarlıyoruz.
  DepremKontrolu=digitalRead(deprem);
  Serial.println("Deprem  ="+String(DepremKontrolu));
  delay(200);
  if(DepremKontrolu==1) {
    digitalWrite(buzzer_pin, HIGH);
    digitalWrite(led_d, HIGH);
    lcd.begin(16,2);
    lcd.write("Deprem");
    delay(800);
    lcd.clear();
    digitalWrite(buzzer_pin, LOW);
    digitalWrite(led_d, LOW);
  }
  else {
    lcd.clear();


  }
    
  }
