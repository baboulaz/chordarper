#pragma once

#include <set>
#include <stdint.h>

const uint8_t NOT_FOUND = 255;

class Chord
{
public:
    Chord(int rootNote);
    ~Chord();
    void addNote(uint8_t note);
    void invert(uint8_t numberOfInversions);
    std::set<uint8_t> &getListOfNotes();

private:
    std::set<uint8_t> listOfNotes = std::set<uint8_t>();
};