#include <LiquidCrystal.h>

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

// keypad değişkenleri
uint16_t analog_deger_A0 = 0, onceki_buton_deger = 0, buton_deger = 0;
uint16_t ayarlara_giris_sayac = 0, ayarlardan_cikis_sayac = 0;
long onceki_zaman = 0, ayarlar_onceki_zaman = 0, arttirma_onceki_zaman = 0, azaltma_onceki_zaman = 0, besli_arttirma_onceki_zaman = 0;
bool ayarlar_sayfasi_aktif = false, yan_sayfaya_gecildi = false, loop_aktif = false;
uint8_t set_degeri = 0;
float debi_miktari = 3.7;
uint16_t motor_rpm = 456;

void setup() {
  lcd.begin(16, 2);
  for (int i = 0; i < 4; i++) {
    lcd.clear();
    delay(500);
    lcd.setCursor(0, 0);
    lcd.print("> LCD & KEYPAD <");
    lcd.setCursor(0, 1);
    lcd.print(" USER INTERFACE ");
    delay(500);
  }
}

void loop() {
  if (analogRead(A0) <= 1000 || loop_aktif == true) {
    loop_aktif = true;
    if (ayarlar_sayfasi_aktif == false) {
      if (millis() - onceki_zaman >= 155) {
        lcd.clear();
        onceki_zaman = millis();
      }
      lcd.setCursor(0, 0);
      lcd.print("SET   ");
      lcd.print("RPM   ");
      lcd.print("DEBI");

      lcd.setCursor(0, 1);
      lcd.print("%");
      lcd.print(set_degeri);
      lcd.setCursor(6, 1);
      lcd.print(motor_rpm);
      lcd.setCursor(12, 1);
      lcd.print(debi_miktari);
    }
    buton_deger = buton_secme();
    ayarlara_giris();
    ayarlar();
  }
}

uint16_t buton_secme() {
  analog_deger_A0 = analogRead(A0);
  // hangi butona basıldığını tespit et
  if (analog_deger_A0 >= 1015  && analog_deger_A0 <= 1025) {
    if ( ayarlar_sayfasi_aktif == false) {
      ayarlara_giris_sayac = 0;
    }
    if (ayarlar_sayfasi_aktif == false && yan_sayfaya_gecildi == false) {
      ayarlardan_cikis_sayac = 0;
    }
    return 1023;
  }
  else if (analog_deger_A0 >= 635  && analog_deger_A0 <= 645) {
    if ( ayarlar_sayfasi_aktif == false) {
      ayarlara_giris_sayac = ayarlara_giris_sayac + 1;
    }
    if (ayarlar_sayfasi_aktif == true && yan_sayfaya_gecildi == true) {
      ayarlardan_cikis_sayac = ayarlardan_cikis_sayac + 1;
    }
    return 640;
  }
  else if (analog_deger_A0 >= 405  && analog_deger_A0 <= 415) {
    if ( ayarlar_sayfasi_aktif == false) {
      ayarlara_giris_sayac = 0;
    }
    if (ayarlar_sayfasi_aktif == false && yan_sayfaya_gecildi == false) {
      ayarlardan_cikis_sayac = 0;
    }
    return 410;
  }
  else if (analog_deger_A0 >= 250  && analog_deger_A0 <= 260) {
    if ( ayarlar_sayfasi_aktif == false) {
      ayarlara_giris_sayac = 0;
    }
    if (ayarlar_sayfasi_aktif == false && yan_sayfaya_gecildi == false) {
      ayarlardan_cikis_sayac = 0;
    }
    return 255;
  }
  else if (analog_deger_A0 >= 95  && analog_deger_A0 <= 105) {
    if ( ayarlar_sayfasi_aktif == false) {
      ayarlara_giris_sayac = 0;
    }
    if (ayarlar_sayfasi_aktif == false && yan_sayfaya_gecildi == false) {
      ayarlardan_cikis_sayac = 0;
    }
    return 100;
  }
  else if (analog_deger_A0 >= 0  && analog_deger_A0 <= 5) {
    if ( ayarlar_sayfasi_aktif == false) {
      ayarlara_giris_sayac = 0;
    }
    if (ayarlar_sayfasi_aktif == false && yan_sayfaya_gecildi == false) {
      ayarlardan_cikis_sayac = 0;
    }
    return 0;
  }
}
void ayarlara_giris() {
  if (ayarlara_giris_sayac >= 111 && ayarlar_sayfasi_aktif == false) {
    lcd.clear();
    ayarlar_sayfasi_aktif = true;
    lcd.setCursor(0, 0);
    lcd.print("AYARLAR  SAYFASI");
    lcd.setCursor(0, 1);
    lcd.print(" YANA KAYDIR >> ");
  }
}
void ayarlar() {
  if (ayarlar_sayfasi_aktif == true) {
    if (buton_deger == 0 && yan_sayfaya_gecildi == false) {
      yan_sayfaya_gecildi = true;
    }
    if (yan_sayfaya_gecildi == true) {
      lcd.setCursor(0, 0);
      lcd.print("HEDEF HIZ DEGERI");
      lcd.setCursor(0, 1);
      lcd.print("%");
      lcd.print(set_degeri);
      if (buton_deger == 100) {
        if (millis() - arttirma_onceki_zaman >= 250 && set_degeri < 100) {
          set_degeri = set_degeri + 1;
          arttirma_onceki_zaman = millis();
        }
      }
      if (buton_deger == 255) {
        if (millis() - azaltma_onceki_zaman >= 250 && set_degeri > 0) {
          set_degeri = set_degeri - 1;
          azaltma_onceki_zaman = millis();
        }
      }
      if (buton_deger == 410) {
        set_degeri = 0;
      }
      if (buton_deger == 0) {
        if (millis() - besli_arttirma_onceki_zaman >= 333 && set_degeri < 94) {
          set_degeri = set_degeri + 5;
          besli_arttirma_onceki_zaman = millis();
        }
      }
      if (millis() - ayarlar_onceki_zaman >= 200) {
        lcd.clear();
        ayarlar_onceki_zaman = millis();
      }
      if (ayarlardan_cikis_sayac >= 111 && yan_sayfaya_gecildi == true && ayarlar_sayfasi_aktif == true) {
        yan_sayfaya_gecildi = false;
        ayarlar_sayfasi_aktif = false;
        ayarlara_giris_sayac = 0;
        ayarlardan_cikis_sayac = 0;
      }
    }
  }
}
