# JuceQtLearning

![demo.png](media%2Fdemo.png)

It's a small project where I practice how to use Qt/QML with a Juce plugin.
I refer to the [jucexqt](https://github.com/torarnv/jucexqt) project for embedding a QML view inside of a Juce
component.
Please refer to this repo for tweaking the Qt and building it
statically. [Here](https://gist.github.com/torarnv/7bbd31d9879c390071d5aa0e9a1f2af1) you can find the gist as well.

It's tested on Mac OS Monterey with Juce 7.0.7 and Qt 6.5.2.

## Building

`cmake -DCMAKE_PREFIX_PATH="~/install/juce;~/install/qt/6.5-static/qtbase"`

![demo.gif](media%2Fdemo.gif)