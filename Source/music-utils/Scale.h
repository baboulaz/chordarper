#pragma once

#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <iterator>
#include "Chord.h"

enum ScaleRootNote
{
  C = 0,
  C_SHARP,
  D,
  D_SHARP,
  E,
  F,
  F_SHARP,
  G,
  G_SHAR,
  A,
  A_SHARP,
  B
};

enum ScaleMode
{
  Major = 0,
  Minor,
  Lydian,
  Mixolydian,
  Dorian,
  Phrygian,
  Locrian
};

const std::vector<std::string> notes = {"C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"};

const std::map<const ScaleMode, const std::vector<uint8_t>> degrees = {
    {ScaleMode::Major, {0, 2, 4, 5, 7, 9, 11}},
    {ScaleMode::Minor, {0, 2, 3, 5, 7, 8, 10}},
    {ScaleMode::Lydian, {0, 2, 4, 6, 7, 9, 11}},
    {ScaleMode::Mixolydian, {0, 2, 4, 5, 7, 9, 10}},
    {ScaleMode::Dorian, {0, 2, 3, 5, 7, 9, 10}},
    {ScaleMode::Phrygian, {0, 1, 3, 5, 7, 8, 10}},
    {ScaleMode::Locrian, {0, 1, 3, 5, 6, 8, 10}}};

class Scale
{

public:
  Scale(ScaleRootNote rootNote, ScaleMode mode);
  ~Scale();

  uint8_t getThird(uint8_t noteNumber);
  uint8_t getFifth(uint8_t noteNumber);
  uint8_t getSeventh(uint8_t noteNumber);
  uint8_t getNineth(uint8_t noteNumber);

  uint8_t getOctaveUp(uint8_t noteNumber);
  uint8_t getOctaveDown(uint8_t noteNumber);

  uint8_t getNoteOnScale(uint8_t noteNumber, bool filterNote);

  Chord getChord(uint8_t rootNote, uint8_t numberOfNotes, uint8_t numberOfInversions, bool addOctaveUp, bool addOctaveDown);

  Chord getDyad(uint8_t noteNumber);
  Chord getTriad(uint8_t noteNumber);
  Chord getTetrad(uint8_t noteNumber);
  Chord getPentad(uint8_t noteNumber);

private:
  Chord createChord(uint8_t rootNote, uint8_t numberOfNotes);
  std::string getNoteName(uint8_t noteNumber);
  uint8_t getNoteDegree(uint8_t noteNumber);
  uint8_t getNotePosition(uint8_t degree);
  uint8_t getNote(uint8_t noteNumber, uint8_t degree);

  ScaleRootNote rootNote;
  ScaleMode mode;
};