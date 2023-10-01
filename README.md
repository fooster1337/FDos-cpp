# FDos-CPP - Lite version of FDos using cpp
This version only support method GET and POST<br>
For python version : <a href="https://github.com/fooster1337/FDos">FDos Python Version</a>

# Installation
For GCC (g++)<br>
<b>Important! : Make sure curl has been installed on you device</b><br>
curl installation you can read here : https://everything.curl.dev/get
```
clone this repository / download
git clone https://github.com/fooster1337/FDos-cpp
cd FDos-cpp
g++ fdos.cpp -o fdos -lcurl 
./fdos (for linux)
fdos.exe (for windows)
```

# Usage
```
For Linux / MacOS / Unix Based :
./fdos https://target.com <method>
Example : ./fdos https://target.com get // using GET method
For windows :
fdos.exe https://target.com <method>
Example : fdos.exe https://target.com get // using GET method
```

# Not important but you must read.
this simple DDos Tool does not yet support proxy/IP switching, it is preferable to use RDP/SSH/VPS. stay anonymous!


