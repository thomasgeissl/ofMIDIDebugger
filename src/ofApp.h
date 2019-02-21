#pragma once

#include "ofMain.h"
#include "ofxMidi.h"

class ofApp : public ofBaseApp, ofxMidiListener
{
public:
  ofApp();
  ofApp(int port);
  ofApp(std::string port);
  ofApp(int port, std::string message, bool interactive = false);
  ofApp(std::string virtualPort, std::string message, bool interactive = false);
  ~ofApp();
  void update();
  void newMidiMessage(ofxMidiMessage & message);
  void sendMessage(std::string message);
  
  std::string _name = "ofMIDIDebugger";
  ofxMidiIn _midiIn;
  ofxMidiOut _midiOut;
};
