When we pressed the button, the register would record the status of button and neopixel. Also, different keyboard input can control the serial output  
and neopixel. We can enter "r" "g" and "b" to control the neopixel, and when we enter "p" from keyboard, it would output the sequential recording in   serial. Each output record status in last 10 iterations of program(totally 2s).  
To realize this functionality, we used a struct array to reserve the status value, and update one element in array each iteration.
<img width="575" alt="recording" src="https://user-images.githubusercontent.com/64452307/202332740-5ef9912b-1418-436c-be1b-75205e2a74a5.png">
<img width="302" alt="serial" src="https://user-images.githubusercontent.com/64452307/202332768-c68bba46-12b1-413b-969f-7940941ed833.png">
![000eb06cf32b93771e6afca70942ddbe 00_00_00-00_00_30](https://user-images.githubusercontent.com/64452307/202336225-bc5fd49b-eb76-44c6-a663-7e485c907eb2.gif)  

