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

ofApp::ofApp(int port, std::string message, bool interactive)
{
    _midiOut.openPort(port);
    sendMessage(message);
    if (interactive)
    {
        ofLogNotice(_name) << "please enter a new message: channel type pitch velocity";
        getline(cin, message);
        sendMessage(message);
    }
    else
    {
        ofExit(0);
    }
}
ofApp::ofApp(std::string virtualPort, std::string message, bool interactive)
{
    _midiOut.openVirtualPort(virtualPort);
    ofLogNotice(_name) << "sending messages on " << virtualPort;
    sendMessage(message);
    if (interactive)
    {
        ofLogNotice(_name) << "please enter a new message: channel type pitch velocity";
        getline(cin, message);
        sendMessage(message);
    }
    else
    {
        ofExit(0);
    }
}
ofApp::~ofApp()
{
    _midiIn.closePort();
    _midiIn.removeListener(this);
    _midiOut.closePort();
}

void ofApp::update()
{
}
void ofApp::newMidiMessage(ofxMidiMessage &message)
{
    std::stringstream text;
    text << ofxMidiMessage::getStatusString(message.status);
    text << " ";

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
    std::regex intRegex{R"(\d+)"};
    if (parts.size() < 3)
    {
        ofLogError(_name) << "invalid number of arguments, at least 3 are expected: " << message;
    }
    if (!std::regex_match(parts[0], intRegex))
    {
        ofLogError(_name) << "channel " << parts[0] << " is not of type int";
        return;
    }
    auto channel = ofToInt(parts[0]);
    auto type = parts[1];
    if (parts.size() == 3) // PC, PITCHBEND
    {
        auto value = ofToInt(parts[2]);
        if (type == "PC" || type == "PROGRAMCHANGE")
        {
            _midiOut.sendProgramChange(channel, value);
        }
        else if (type == "PITCHBEND")
        {
            _midiOut.sendPitchBend(channel, value);
        }
    }
    else if (parts.size() == 4) // NOTEON or NOTEOFF
    {
        auto pitch = ofToInt(parts[2]);
        auto velocity = ofToInt(parts[3]);
        if (type == "NOTEON")
        {
            _midiOut.sendNoteOn(channel, pitch, velocity);
        }
        else if (type == "NOTEOFF")
        {
            _midiOut.sendNoteOff(channel, pitch, velocity);
        }
        else if (type == "CC" || type == "CONTROLCHANGE")
        {
            _midiOut.sendControlChange(channel, pitch, velocity); // channel, control, value
        }
    }
}
