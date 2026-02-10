# foo_jumptime

Foobar2000 component allowing you to jump to a specific time in the loaded track via a simple dialog.

## Requirements

- Visual Studio 2022+ Build Tools (or full VS)
- C++ ATL component (install via VS Installer: "C++ ATL for latest build tools")
- CMake 3.24+

## Building

```
git clone --recursive https://github.com/trypsynth/foo_jumptime
cd foo_jumptime
mkdir build
cd build
cmake ..
cmake --build . --config Release
```

Output: `Release/foo_jumptime.dll`

## Install

Copy `foo_jumptime.dll` to `%APPDATA%\foobar2000-v2\user-components-x64\foo_jumptime\`.

## Usage

1. Preferences > Keyboard Shortcuts
2. Search for "Jump to Time", and assign a key (e.g. Ctrl+J)
3. Play a track, hit the shortcut
4. Edit the time and press Enter

Accepts `H:MM:SS`, `M:SS`, or bare seconds Decimal fractions (e.g. `1:30.500`) are supported.
