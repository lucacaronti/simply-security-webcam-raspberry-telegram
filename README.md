# simply-security-webcam-raspberry-telegram
Simply security webcam program made for raspberry pi with telegram notifications

# Installation
First we need to install opencv in our Raspberry.
In my case I used a Raspberry pi 3 b+.
I followed [this](https://linuxize.com/post/how-to-install-opencv-on-raspberry-pi/) post for installation.
In addiction I also had to install an other package:
```sh
$ sudo apt install libopencv-dev
```
Now we need to create a new telegram bot for notifications.
Follow [this](https://medium.com/@ManHay_Hong/how-to-create-a-telegram-bot-and-send-messages-with-python-4cf314d9fa3e) post to know how to set up a telegram bot and get bot chat ID and bot token.
Then:
```sh
$ pip3 install python-telegram-bot --user
$ git clone https://github.com/lucacaronti/simply-security-webcam-raspberry-telegram.git
$ cd simply-security-webcam-raspberry-telegram
$ make
```
At this point you need to open [sendTelegram.py](https://github.com/lucacaronti/simply-security-webcam-raspberry-telegram/master/sendTelegram.py) and put your bot token in line 3 and you bot chat id in line 4.
Now:
```sh
$ ./securityCamera
```
# Code description
The code is as simple as possible (but works). There is a moving average filter to eliminate noise. Then subtraction between frames is done. On the result an MSE (mean square error) is applied and if the frames are different it means that there has been a change and if the value is higher than a threshold an alarm is sent. If the program doesn't work very well, try changing the **MSE_threshold** variable.