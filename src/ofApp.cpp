#include "ofApp.h"
#include <iostream>
#include <regex>

ofApp::ofApp()
{
    _midiIn.listInPorts();
    _midiOut.listOutPorts();
}

ofApp::ofApp(int port)
{
    // ofSetLogLevel(OF_LOG_VERBOSE);
    // _midiIn.setVerbose(true);
    _midiIn.addListener(this);
    _midiIn.openPort(port);
    ofLogNotice(_name) << "listening on port " << port;
}
ofApp::ofApp(std::string port)
{
    // ofSetLogLevel(OF_LOG_VERBOSE);
    // _midiIn.setVerbose(true);
    _midiIn.addListener(this);
    _midiIn.openVirtualPort(port);
    ofLogNotice(_name) << "listening on virtual port " << port;
}

ofApp::ofApp(int port, std::string message, bool interactive = false)
{
    if (interactive)
    {
    }
    else
    {
        ofExit(0);
    }
}
ofApp::ofApp(std::string virtualPort, std::string message, bool interactive = false)
{
    sendMessage(message);
    if (interactive)
    {
        ofLogNotice(_name) << "please enter a new message: type channel pitch velocity";
        getline(cin, message);
        sendMessage(message);
    }
    else
    {
        ofExit(0);
    }
}
void ofApp::~ofApp()
{
    _midiIn.closePort();
    _midiIn.removeListener(this);
}

void ofApp::update()
{
}
void ofApp::newMidiMessage(ofxMidiMessage &message)
{
    std::stringstream text;
    text << ofxMidiMessage::getStatusString(message.status);

    if (message.status < MIDI_SYSEX)
    {
        text << "chan: " << message.channel;
        if (message.status == MIDI_CONTROL_CHANGE)
        {
            text << "\tctl: " << message.control;
        }
        else if (message.status == MIDI_PROGRAM_CHANGE)
        {
            text << "\tctl: " << message.control;
        }
        else if (message.status == MIDI_PITCH_BEND)
        {
            text << "\tval: " << message.value;
        }
        else
        {
            text << "\tpitch: " << message.pitch;
            text << "\tvel: " << message.velocity;
        }
        text << " "; // pad for delta print
    }

    text << "delta: " << message.deltatime;
    ofLogNotice(_name) << text.str();
}
void ofApp::sendMessage(std::string message)
{
    auto parts = ofSplitString(message, " ");
    // TODO
}
