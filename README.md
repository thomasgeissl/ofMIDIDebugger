# ofMIDIDebugger
## Description
ofMIDIDebugger is command line tool to monitor and send MIDI messages.

## Installation
### OSX
On OSX you can install it via brew.

```
brew tap thomasgeissl/tools
brew install ofmididebugger
# brew upgrade ofmididebugger
```
This will download the most recent version of the MIDI debugger and add it to your search path.

### Building
And as always you can clone it to your apps directory and build it by running make.

## Usage
* list available MIDI in and out ports: ` ofMIDIDebugger -l `
* listen to incommig MIDI messages on port index 0: `ofMIDIDebugger -p 0`
* listen to incommig MIDI messages on a virtual port: `ofMIDIDebugger -v virtualMIDIPort`
* send a NOTEON of NOTEOFF message (channel NOTEON pitch velocity): `ofMIDIDebugger -v virtualMIDIPort -m "1 NOTEON 60 127"`
* send a CC message (channel CC control value): `ofMIDIDebugger -v virtualMIDIPort -m "1 CC 1 127"`
* send a PROGRAMCHANGE message (channel PROGRAMCHANGE control): `ofMIDIDebugger -v virtualMIDIPort -m "1 PROGRAMCHANGE 1"`
* send a PITCHBEND message (channel PITCHBEND value): `ofMIDIDebugger -v virtualMIDIPort -m "1 PITCHBEND 127"`
* TODO: sysex, aftertouch, polyaftertouch support

The following types are supported by now:
* NOTEON
* NOTEOFF
* CC
* PROGRAMCHANGE
* PITCHBEND

## License
This software is distributed under the [MIT License](https://en.wikipedia.org/wiki/MIT_License), please note that dependencies might be released differently.

Copyright (c) 2019 Thomas Geissl

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
