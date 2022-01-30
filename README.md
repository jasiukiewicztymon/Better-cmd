# Better CMD

Create your own extensions and link them to the Better CMD to use them easier...

**If you want do a command proposition in Issues section**

### TO DO:

- [ ] Extension template cpp file
- [ ] Path file
- [ ] Variable system

### Instalation

Launch the exe file and don't worry about the other thing. The Better CMD will create all the folder it need itself

### Remade interface

A colorised interface what made the better CMD prettier 

![image](https://user-images.githubusercontent.com/73474137/151667668-ccae1076-ce1a-4919-94e6-d1196f2364bf.png)

### An integrade help for main extension

Found some help using **--help**

![image](https://user-images.githubusercontent.com/73474137/151667717-6d453b36-16ff-4686-8952-8365282ea338.png)

### Create an extention in the Better CMD style

Copy the *mainext.h* and *mainext.cpp* to your project and then include the *mainext.h*

```#include "mainext.h"```

Now you can use showHeader for a pretty input section... When your code is ready export it to exe and type this command in the Better CMD

```ext set [name] [path]```

Finnaly you can run your extention using this command:

```ext run [name]```

### Use built in command 

In the future I plan to made more command...

#### Compare files...

![image](https://user-images.githubusercontent.com/73474137/151668401-803a33c4-b010-4c12-bb12-d026456280c8.png)

#### Cat files...

![image](https://user-images.githubusercontent.com/73474137/151668463-f8025cfb-bb29-45d7-9bb5-a65be061497d.png)

### License 

MIT License

Copyright (c) 2022 titi_2115

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
