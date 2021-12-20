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
*one-time action*
```
$ conan profile new ~/.conan/profiles/my-default --detect
```

#### Configure project dependencies
```
$ cd <proj_dir>
$ mkdir cmake-build-release && cd cmake-build-release
$ conan install .. -u -pr my-default --b missing -r conancenter
```
