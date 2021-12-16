#include "Chord.h"

class Scale
{

public:
  Scale(ScaleRootNote rootNode, ScaleMode mode);
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
  ScaleRootNote rootNode;
  ScaleMode mode;
};