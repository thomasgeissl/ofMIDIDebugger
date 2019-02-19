#!/bin/sh
cd "$(dirname "$0")"
cd ..
make
cd scripts

mkdir ../../tmp
cd ../../tmp
rm -rf *
cp -R ../ofMIDIDebugger ofMIDIDebugger
zip -r ofMIDIDebugger_osx_version.zip ofMIDIDebugger
openssl dgst -sha256 ofMIDIDebugger_osx_version.zip
