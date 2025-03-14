# 1Fish

I didn't create this esolang, I simply implemented it for fun.

[See syntax and information here](https://esolangs.org/wiki/1Fish).

# Samples
Hello World <br>
```"Hello, world!"r(o)``` <br>

["Truth machine"](https://esolangs.org/wiki/Truth-machine) <br>
```"Tell me the truth! (y/n):" r(o) i "y" = {"No, the truth!" r(o) 10 o 1 j} "Thank you." r(o)```

# To compile and run...
Clone the repo, create a "build" directory and change directory into it. Then run ``cmake ..`` and ``make -j``. <br> You can then run the executable ``1fish`` with an argument pointing to the file containing the code.





