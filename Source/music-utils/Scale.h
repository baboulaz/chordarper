#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <iterator>
#include "Chord.h"

enum ScaleRootNote
{
  A,
  A_SHARP,
  B,
  C,
  C_SHARP,
  D,
  D_SHARP,
  E,
  F,
  F_SHARP,
  G,
  G_SHARP
};

enum ScaleMode
{
  Major,
  Minor,
  Lydian,
  Mixolydian,
  Dorian,
  Phrygian,
  Locrian
};

const std::vector<std::string> notes = {"C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"};

const std::map<const ScaleMode, const std::vector<int>> degrees = {
    {ScaleMode::Major, {0, 2, 4, 5, 7, 9, 11, 12}},
    {ScaleMode::Minor, {0, 2, 3, 5, 7, 8, 10, 12}},
    {ScaleMode::Lydian, {0, 2, 4, 6, 7, 9, 11, 12}},
    {ScaleMode::Mixolydian, {0, 2, 4, 5, 7, 9, 10, 12}},
    {ScaleMode::Dorian, {0, 2, 3, 5, 7, 9, 10, 12}},
    {ScaleMode::Phrygian, {0, 1, 3, 5, 7, 8, 10, 12}},
    {ScaleMode::Locrian, {0, 1, 3, 5, 6, 8, 10, 12}}};

class Scale
{

public:
  Scale(ScaleRootNote rootNote, ScaleMode mode);
  ~Scale();

  int getThird(int noteNumber);
  int getFifth(int noteNumber);
  int getSeventh(int noteNumber);
  int getNineth(int noteNumber);

  int getOctaveUp(int noteNumber);
  int getOctaveDown(int noteNumber);

  int getNoteOnScale(int noteNumber, bool filterNote);

  Chord getChord(int rootNote, int numberOfNotes, int numberOfInversions, bool addOctaveUp, bool addOctaveDown);

  Chord getDyad(int noteNumber);
  Chord getTriad(int noteNumber);
  Chord getTetrad(int noteNumber);
  Chord getPentad(int noteNumber);

private:
  Chord createChord(int rootNote, int numberOfNotes);
  std::string getNoteName(int noteNumber);

  ScaleRootNote rootNote;
  ScaleMode mode;
};