#include <Adafruit_Sensor.h>
#include <FuzzyRule.h>
#include <FuzzyComposition.h>
#include <Fuzzy.h>
#include <FuzzyRuleConsequent.h>
#include <FuzzyOutput.h>
#include <FuzzyInput.h>
#include <FuzzyIO.h>
#include <FuzzySet.h>
#include <FuzzyRuleAntecedent.h>
#include <dht.h>
dht DHT int humidity;
int indicator;
int Light;
float temperature;
float output;
unsigned long timeNow;
unsigned long timeLast;
Fuzzy *fuzzy = new Fuzzy();
/*Creating fuzzification of soil FuzzySet* low_soil = new FuzzySet(0, 50, 50, 75);
 FuzzySet* normal_soil = new FuzzySet(50, 75, 75, 80);
  FuzzySet* high_soil = new FuzzySet(80, 90, 90, 100); 
  // creating fuzzification of Humidity FuzzySet* low_hum = new FuzzySet(0, 0, 0, 380); 
  FuzzySet* normal_hum = new FuzzySet(237, 380, 380, 712); 
  FuzzySet* high_hum = new FuzzySet(570, 712, 950, 950); 
  // Fuzzy output watering duration FuzzySet* low_dur = new FuzzySet(0, 0, 0, 0);
   FuzzySet* normal_dur = new FuzzySet(3, 5, 5, 7); FuzzySet* high_dur = new FuzzySet(0, 0, 0, 0);*/
void setup()
{
    Serial.begin(115200);
    pinMode(8, OUTPUT);
    FuzzyInput *soil_set1 = new FuzzyInput(1);
    soil_set1->addFuzzySet(low_soil);
    soil_set1->addFuzzySet(normal_soil);
    soil_set1->addFuzzySet(high_soil);
    fuzzy->addFuzzyInput(soil_set1);
    FuzzyInput *hum_set1 = new FuzzyInput(2);
    hum_set1->addFuzzySet(low_hum);
    hum_set1->addFuzzySet(normal_hum);
    hum_set1->addFuzzySet(high_hum);
    fuzzy->addFuzzyInput(hum_set1);
    FuzzyOutput *water_dur = new FuzzyOutput(1);
    water_dur->addFuzzySet(low_dur);
    water_dur->addFuzzySet(normal_dur);
    water_dur->addFuzzySet(high_dur);
    fuzzy->addFuzzyOutput(water_dur); //fuzzy rule FuzzyRuleConsequent* thenlow_dur = new FuzzyRuleConsequent(); thenlow_dur->addOutput(low_dur); FuzzyRuleConsequent* thennormal_dur = new FuzzyRuleConsequent(); thennormal_dur->addOutput(normal_dur); FuzzyRuleConsequent* thenhigh_dur = new FuzzyRuleConsequent(); thenhigh_dur->addOutput(high_dur); FuzzyRuleAntecedent* iflow_soilDanhigh_hum = new FuzzyRuleAntecedent(); iflow_soilDanhigh_hum->joinWithAND(low_soil, high_hum); FuzzyRule* fuzzyRule01 = new FuzzyRule(1, iflow_soilDanhigh_hum, thenlow_dur); fuzzy->addFuzzyRule(fuzzyRule01); FuzzyRuleAntecedent* iflow_soilnormal_hum = new FuzzyRuleAntecedent(); iflow_soilnormal_hum->joinWithAND(low_soil, normal_hum);
    10 FuzzyRule *fuzzyRule02 = new FuzzyRule(2, iflow_soilnormal_hum, thenlow_dur);
    fuzzy->addFuzzyRule(fuzzyRule02);
    FuzzyRuleAntecedent *iflow_soillow_hum = new FuzzyRuleAntecedent();
    iflow_soillow_hum->joinWithAND(low_soil, low_hum);
    FuzzyRule *fuzzyRule03 = new FuzzyRule(3, iflow_soillow_hum, thennormal_dur);
    fuzzy->addFuzzyRule(fuzzyRule03);
    FuzzyRuleAntecedent *ifnormal_soilhigh_hum = new FuzzyRuleAntecedent();
    ifnormal_soilhigh_hum->joinWithAND(normal_soil, high_hum);
    FuzzyRule *fuzzyRule04 = new FuzzyRule(4, ifnormal_soilhigh_hum, thenlow_dur);
    fuzzy->addFuzzyRule(fuzzyRule04);
    FuzzyRuleAntecedent *ifnormal_soilnormal_hum = new FuzzyRuleAntecedent();
    ifnormal_soilnormal_hum->joinWithAND(normal_soil, normal_hum);
    FuzzyRule *fuzzyRule05 = new FuzzyRule(5, ifnormal_soilnormal_hum, thennormal_dur);
    fuzzy->addFuzzyRule(fuzzyRule05);
    FuzzyRuleAntecedent *ifnormal_soillow_hum = new FuzzyRuleAntecedent();
    ifnormal_soillow_hum->joinWithAND(normal_soil, low_hum);
    FuzzyRule *fuzzyRule06 = new FuzzyRule(6, ifnormal_soillow_hum, thenhigh_dur);
    fuzzy->addFuzzyRule(fuzzyRule06);
    FuzzyRuleAntecedent *ifhigh_soilhigh_hum = new FuzzyRuleAntecedent();
    ifhigh_soilhigh_hum->joinWithAND(high_soil, high_hum);
    FuzzyRule *fuzzyRule07 = new FuzzyRule(7, ifhigh_soilhigh_hum, thennormal_dur);
    fuzzy->addFuzzyRule(fuzzyRule07);
    FuzzyRuleAntecedent *ifhigh_soilnormal_hum = new FuzzyRuleAntecedent();
    ifhigh_soilnormal_hum->joinWithAND(high_soil, normal_hum);
    FuzzyRule *fuzzyRule08 = new FuzzyRule(8, ifhigh_soilnormal_hum, thennormal_dur);
    fuzzy->addFuzzyRule(fuzzyRule08);
    FuzzyRuleAntecedent *ifhigh_soillow_hum = new FuzzyRuleAntecedent();
    ifhigh_soillow_hum->joinWithAND(high_soil, low_hum);
    FuzzyRule *fuzzyRule09 = new FuzzyRule(9, ifhigh_soillow_hum, thenhigh_dur);
    fuzzy->addFuzzyRule(fuzzyRule09);
    11
}
void loop()
{
    int soil_content = analogRead(A0);
    int dht_value = DHT.read11(A1);
    int humidity = DHT.humidity;
    int temperature = DHT.temperature;
    soil_content = map(soil_content, 1023, 140, 0, 100);
    char data[10];
    sprintf(data, "%d,%d,%d", soil_content, temperature, humidity);
    Serial.println(data);
    delay(6000);
    fuzzy->setInput(1, soil_content);
    fuzzy->setInput(2, 35);
    fuzzy->fuzzify();
    output = fuzzy->defuzzify(1);
    digitalWrite(8, HIGH);
    delay(1000);
    digitalWrite(8, LOW);
}