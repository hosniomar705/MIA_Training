# Interface with rotary Encoder and get the number of counts from the train of impulse from A, and B signals
- We need to design a Software Practical Low Pass Filter (LPF) what is the proper cutoff frequency (fc) If WALL-E has Specs:
1. Encoder has 540 pulse per revolution
1. Track has three wheels only one motorized, with 40cm diameter, (The one that has encoder)
1. And Maximum speed of WALL-E 0.5 m/s

#### solution:
1. angular velocity = linear velocity(m/s)/radius(m) = .5/.2 = 2.5 rad/s
2. revolution per second = angular velocity/(2*pi) = 2.5/(2*pi) = .398 rev/s
3. pulses per sec = num of pulses per rev * revolution per second = 214.92 pulse/s
### cut-off freq >= 214.92
