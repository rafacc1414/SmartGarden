#include <Wire.h>
#include <Adafruit_ADS1X15.h>

bool ads_read_all(Adafruit_ADS1115 *ads, int16_t *adc_outputs)
{

  if (adc_outputs == NULL || ads == NULL)
    return false;

  int16_t adc0, adc1, adc2, adc3;
 
  adc0 = ads->readADC_SingleEnded(0);
  adc1 = ads->readADC_SingleEnded(1);
  adc2 = ads->readADC_SingleEnded(2);
  adc3 = ads->readADC_SingleEnded(3);
  
  // Assign results
  adc_outputs[0] = adc0;
  adc_outputs[1] = adc1;
  adc_outputs[2] = adc2;
  adc_outputs[3] = adc3;

  return true;
}
