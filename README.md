## Build for Android

Ensure you have all necessary environment variables in place:

```sh
export COCOS2DX_ROOT="/usr/local/lib/cocos2d-x"
export ANDROID_SDK_ROOT="/usr/local/lib/adt/sdk"
export NDK_ROOT="/usr/local/lib/ndk"
export NDK_TOOLCHAIN_VERSION="4.8"
```

Then build native libraries:

```sh
./build_native.py
```

Finally the project:

```sh
ant debug -Dsdk.dir=$ANDROID_SDK_ROOT
```

Run it against your emulator with:

```sh
emulator -avd nexus-19
adb install bin/Copong-debug.apk
```

## Build for iOS

Build the project with `xcodebuild`:

```sh
xcodebuild -target 'Copong iOS'
```

## Build for Mac

Build the project with `xcodebuild`:

```sh
xcodebuild -target 'Copong Mac'
```

## Build for Linux

First install dependencies:

```sh
cd cocos2d/build
./install-deps-linux.sh
```

Then build the project:

```sh
mkdir build
cd build
cmake ..
make -j4
```
