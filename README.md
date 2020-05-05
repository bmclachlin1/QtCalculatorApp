# QtCalculatorApp

This is a calculator application I made using the Qt C++ GUI framework. Supports basic calculator functions and displays in scientific notation for large numbers

To deploy on windows 10, make sure you have the latest version of Qt downloaded. You can do this by going to https://qt.io/download and clicking on the Go Open Source button in the bottom right of the page (scroll down for this). After downloading qt, open the project file in Qt Creator and run it in release mode. After this, go to the windows search bar and type "Qt 5.12.6" click on it and in the command prompt cd to the /build/release directory from where you have the Qt project located. After this, you should be able to type in the command prompt "windeployqt Notepad.exe" which should configure the application for you. You also need to make sure all of the .dll files are included from Qt/5.12.6/mingw/bin in your release directory. After this you should be able to run the application by clicking on Notepad.exe from the release directory.

Refer to https://doc.qt.io/qt-5/windows-deployment.html for more info.

<img src="/imgs/calculator.JPG" width=100%>
