# PythonToExe
Simple Python to Exe using pyinstaller.

Source File should be generated automatically, if not hit the generate source file button.

Python file must be able to "pause"; if the python code consists only of code such as: print("hello world") it will run and close, 
you need to have some sort of input() or pause in the program for it to execute correctly. 

--------------------------------------
i.e:
works:
def function():
  print("Hello World")
  x = input("Run again?)
  if(x == "yes"):
    function()
  else:
    print("quiting")
    
does not work/closes out instantly:
  
def function():
  print("hello world")
  
--------------------------------------

Code is still in its infancy; window is primitive, interface is glitchy.

Known bugs:
  text manipulation within the setWindows
  #define bug in code
