
#include <LiquidCrystal_I2C.h> // Libreria LCD_I2C


LiquidCrystal_I2C lcd(0x27,16,2); // si no te sale con esta direccion  puedes usar (0x3f,16,2) || (0x27,16,2)  ||(0x20,16,2) 
bool p=1;

void setup() {
  lcd.init();
  lcd.backlight();
  attachInterrupt(digitalPinToInterrupt(2), cambiarEstado, RISING);
  
}

void loop() { 
  if(p==1){
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("   Puto Profe"); 
      lcd.setCursor (0,1);
      lcd.print("Seminario de embebidos");
      delay(300);
    }
  if(p==0){
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("213605572"); 
      lcd.setCursor (0,1);
      lcd.print("OMAR BARUCH M L");
      delay(300);
    }
    
  
}


void cambiarEstado (){
  p = !p;
}
