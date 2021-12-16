#include "Scale.h"

Scale::Scale(ScaleRootNote rootNode, ScaleMode mode)
{
    this->rootNode = rootNode;
    this->mode = mode;
};
Scale::~Scale(){

};
int Scale::getThird(int noteNumber)
{
    return noteNumber + 12;
};
int Scale::getFifth(int noteNumber)
{
    return noteNumber + 7;
};
int Scale::getSeventh(int noteNumber)
{
    return noteNumber + 12;
};
int Scale::getNineth(int noteNumber)
{
    return noteNumber + 12;
};
int Scale::getOctaveUp(int noteNumber)
{
    return noteNumber + 12;
};
int Scale::getOctaveDown(int noteNumber)
{
    return noteNumber - 12;
};
int Scale::getNoteOnScale(int noteNumber, bool filterNote)
{
    return noteNumber;
};

Chord Scale::getChord(int rootNote, int numberOfNotes, int numberOfInversions, bool addOctaveUp, bool addOctaveDown)
{
    Chord chord;
    switch (numberOfNotes)
    {

    case 2:
        chord = getDyad(rootNote);
        break;
    case 3:
        chord = getTriad(rootNote);
        break;
    case 4:
        chord = getTetrad(rootNote);
        break;
    case 5:
        chord = getPentad(rootNote);
        break;
    case 1:
    default:
        chord = Chord(rootNote);
        break;
    }

    if (numberOfInversions > 0)
    {
        chord.invert(numberOfInversions);
    }

    if (addOctaveUp)
    {
        chord.addNote(getOctaveUp(rootNode));
    }
    if (addOctaveDown)
    {
        chord.addNote(getOctaveDown(rootNode));
    }

    return chord;
}
Chord Scale::getDyad(int noteNumber)
{
    Chord chord = Chord(noteNumber);
    chord.addNote(getFifth(noteNumber));
    return chord;
};
Chord Scale::getTriad(int noteNumber)
{
    Chord chord = Chord(noteNumber);
    chord.addNote(getThird(noteNumber));
    chord.addNote(getFifth(noteNumber));
    return chord;
};
Chord Scale::getTetrad(int noteNumber)
{
    Chord chord = Chord(noteNumber);
    chord.addNote(getThird(noteNumber));
    chord.addNote(getFifth(noteNumber));
    chord.addNote(getSeventh(noteNumber));
    return chord;
};
Chord Scale::getPentad(int noteNumber)
{
    Chord chord = Chord(noteNumber);
    chord.addNote(getThird(noteNumber));
    chord.addNote(getFifth(noteNumber));
    chord.addNote(getSeventh(noteNumber));
    chord.addNote(getNineth(noteNumber));
    return chord;
};