///////////////////////////////////////////////////////////////////////////////////////
//Terms of use
///////////////////////////////////////////////////////////////////////////////////////
//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//THE SOFTWARE.

//Code written by Bhuvan Kumar
///////////////////////////////////////////////////////////////////////////////////////
#include<DS3231.h>
#include<Wire.h>
#include<LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);
DS3231 rtc;
bool century=false;
bool flag1,flag2;
unsigned long previousTime,currentTime;
const unsigned long delayTime=500;
int counter;
String getDOW()
{
  int x=rtc.getDoW();
  switch(x)
  {
    case 1:
    return "Mon";
    case 2:
    return "Tue";
    case 3:
    return "Wed";
    case 4:
    return "Thu";
    case 5:
    return "Fri";
    case 6:
    return "Sat";
    case 7:
    return "Sun";
    default:
    return "Error";
  }
}
void mainDisplay()
{
  currentTime=millis();
  if(currentTime-previousTime>=delayTime)
  {
    if(counter%2!=0)
    {
      lcd.setCursor(2,1);
      lcd.print(" ");
      lcd.setCursor(5,1);
      lcd.print(" ");
      previousTime=currentTime;
    }
    else
    {
      currentTime=millis();
      lcd.clear();
      if(rtc.getDate()<10)
      {
        lcd.print("0");
        lcd.print(rtc.getDate());
      }
      else
      lcd.print(rtc.getDate());
      lcd.print("-");
      if(rtc.getMonth(century)<10)
      {
        lcd.print("0");
        lcd.print(rtc.getMonth(century));
      }
      else
      lcd.print(rtc.getMonth(century));
      lcd.print("-");
      if(rtc.getYear()<10)
      {
        lcd.print("0");
        lcd.print(rtc.getYear());
      }
      else
      lcd.print(rtc.getYear());
      lcd.print("   ");
      lcd.print(getDOW());
      lcd.setCursor(11,1);
      lcd.print(rtc.getTemperature());
      lcd.setCursor(15,1);
      lcd.print("C");
      lcd.setCursor(0,1);
      if(rtc.getHour(flag1,flag2)<10)
      {
        lcd.print("0");
        lcd.print(rtc.getHour(flag1,flag2));
      }
      else
      lcd.print(rtc.getHour(flag1,flag2));
      lcd.setCursor(2,1);
      lcd.print(":");
      if(rtc.getMinute()<10)
      {
        lcd.print("0");
        lcd.print(rtc.getMinute());
      }
      else
      lcd.print(rtc.getMinute());
      lcd.setCursor(5,1);
      lcd.print(":");
      if(rtc.getSecond()<10)
      {
        lcd.print("0");
        lcd.print(rtc.getSecond());
      }
      else
      lcd.print(rtc.getSecond());
    }
    counter++;
    previousTime=currentTime;
  }
  delay(10);
}
void setup() {
  // put your setup code here, to run once:
  Wire.begin();
  rtc.setClockMode(false);
  lcd.init();
  lcd.backlight();
}

void loop() {
  // put your main code here, to run repeatedly:
  mainDisplay();
}
