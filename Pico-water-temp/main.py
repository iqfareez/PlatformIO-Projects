from machine import Pin, I2C, ADC
from ssd1306 import SSD1306_I2C
from oled import Write, GFX
from oled.fonts import ubuntu_mono_15, ubuntu_condensed_15, ubuntu_20
import time
import onewire, ds18x20

WIDTH = 128
HEIGHT = 64
i2c = I2C(0, scl=Pin(17), sda=Pin(16), freq=40000)
oled = SSD1306_I2C(WIDTH, HEIGHT, i2c)

ds_pin = Pin(11)
ds_sensor = ds18x20.DS18X20(onewire.OneWire(ds_pin))
roms = ds_sensor.scan()
print("Found DS devices: ", roms)

led = Pin(22, Pin.OUT)

write15mono = Write(oled, ubuntu_mono_15)
write20 = Write(oled, ubuntu_20)
write15cond = Write(oled, ubuntu_condensed_15)

write15mono.text("Temperature: ", 0, 0)

oled.show()

while True:
    ds_sensor.convert_temp()
    time.sleep_ms(750)

    value = ds_sensor.read_temp(roms[0])
    rounded = round(value, 2)
    print(rounded)
    
    if value < 50 :
        led.value(1)
        write15cond.text("Ready to drink :)", 0, 45)
    else :
        led.value(0)
        write15cond.text("Careful! Still Hot", 0, 45)

    write20.text(str(rounded) + " *C ", 0, 18)  # extra space to remove ghost character
    time.sleep(.6)
    oled.show()
