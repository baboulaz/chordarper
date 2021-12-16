#include <set>

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
  Pentatonic
};

class Chord
{
public:
    Chord();
    Chord(int rootNote);
    ~Chord();
    void addNote(int note);
    void invert(int numberOfInversions);
    std::set<int> getListOfNotes();

private:
    std::set<int> listOfNotes=std::set<int>();
};