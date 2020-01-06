from machine import Pin
power_pin = Pin("GP6", Pin.OUT)
power_pin(1)

dac_reset_pin = Pin("GP7", Pin.OUT)
dac_reset_pin(1)

green_led_pin = Pin("GP25", Pin.OUT)
green_led_pin(1)

blue_led_pin = Pin("GP24", Pin.OUT)
#blue_led_pin(1) #is always on - can't be switched

from machine import Timer
timer1 = Timer(1, mode=Timer.PWM, width=16)

timer1a = timer1.channel(Timer.A, freq=1000, duty_cycle=5000) #Green LED PWM 50%
timer1b = timer1.channel(Timer.B, freq=1000, duty_cycle=5000) #Red LED PWM 50% - doesn't work

from machine import SD
sd = SD(pins=('GP10', 'GP11', 'GP9')) #won't work Error 5 EIO - SD has no voltage?!