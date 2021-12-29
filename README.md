An effort to write a communication app.

## Env setup
### Configure conan

#### Install conan
Install:
```
$ pip install --user conan
```
Upgrade:
```
$ pip install -U --user conan
```

#### Configure profile
*This is a one-time action.*

If you need to use a different conan config, set a custom conan base directory via this variable:
```
export CONAN_USER_HOME=~/.my-conan
```

Generates default profile detecting GCC and sets old ABI:
```
$ conan profile new default --detect
```
Sets libcxx to C++11 ABI:
```
$ conan profile update settings.compiler.libcxx=libstdc++11 default
```

#### Configure project dependencies
```
$ cd <proj_dir>
$ mkdir cmake-build-release && cd cmake-build-release
$ conan install .. -u -pr default -b missing
```
