# E32-915T-20D
##### EBYTE E32-915T20D, SX1276 915MHz 100mW DIP Wireless Module

You can get this unit from Amazon but I am not recommending to get this unit at least for now because I do not have good confidence on this unit yet.

https://www.amazon.com/Gowoops-Wireless-Transmitter-Compatible-Microcomputer/dp/B07G7RZLTW/ref=sr_1_3?keywords=e32-915t20d&qid=1560654554&s=gateway&sr=8-3

I haven't yet thoroughly verified whether this unit is working or not but I am coding now ...

### Wiring Diagram:

|Arduino Nano            | E32-915T-20D |
|------------------------|--------------|
|D7                      |   M0 |
|D8                      |   M1 |
|D3                      |   TX (no resistor required, direct connection) |
|D2                      |   RX (no resistor required, direct connection) |
|A0                      |   AUX |
|5V                      |   VCC |
|GND                     |   GND |

### Reference:

1) E32-915T20D User Manual(PDF), http://www.ebyte.com/en/product-view-news.aspx?id=131
1) Osoyoo LoRa Tutorial — How to Use the Uart LoRa Module with Arduino
   http://osoyoo.com/2018/07/26/osoyoo-lora-tutorial-how-to-use-the-uart-lora-module-with-arduino/

2) Bob0505/E32-TTL-100
   https://github.com/Bob0505/E32-TTL-100
   
3) dinhquy94/E32-TTL-100
  https://github.com/dinhquy94/E32-TTL-100
