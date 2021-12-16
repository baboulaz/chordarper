#include "Scale.h"

// std::string scalenotes(const std::string &rootnote, const std::string &scale)
// {
//     int root = std::distance(notes.begin(), std::find(notes.begin(), chromatic.end(), rootnote));
//     if (root >= chromatic.size())
//     {
//         return "";
//     }
//     std::stringstream ss;
//     for (int i : degrees.at(scale))
//     {
//         ss << chromatic[(root + i) % chromatic.size()] << " ";
//     }
//     return ss.str();
// }

Scale::Scale(ScaleRootNote rootNoteIn, ScaleMode modeIn)
{
    rootNote = rootNoteIn;
    mode = modeIn;
}
Scale::~Scale()
{
}

std::string Scale::getNoteName(int noteNumber)
{
    return notes[noteNumber % (int)12];
}

int Scale::getThird(int noteNumber)
{
    return noteNumber + 4;
}
int Scale::getFifth(int noteNumber)
{
    return noteNumber + 7;
}
int Scale::getSeventh(int noteNumber)
{
    return noteNumber + 9;
}
int Scale::getNineth(int noteNumber)
{
    return noteNumber + 13;
}
int Scale::getOctaveUp(int noteNumber)
{
    return noteNumber + 12;
}
int Scale::getOctaveDown(int noteNumber)
{
    return noteNumber - 12;
}
int Scale::getNoteOnScale(int noteNumber, bool filterNote)
{
    std::vector<int> scale = degrees.at(mode);

    if (std::find(scale.begin(), scale.end(), noteNumber % 12) != scale.end())
    {
        return noteNumber;
    }
    else
    {
        return -1;
    }
}

Chord Scale::createChord(int firstNote, int numberOfNotes)
{
    switch (numberOfNotes)
    {

    case 2:
        return getDyad(firstNote);
    case 3:
        return getTriad(firstNote);
    case 4:
        return getTetrad(firstNote);
    case 5:
        return getPentad(firstNote);
    case 1:
    default:
        return Chord(firstNote);
    }
}

Chord Scale::getChord(int firstNote, int numberOfNotes, int numberOfInversions, bool addOctaveUp, bool addOctaveDown)
{
    Chord chord = createChord(firstNote, numberOfNotes);

    if (numberOfInversions > 0)
    {
        chord.invert(numberOfInversions);
    }

    if (addOctaveUp)
    {
        chord.addNote(getOctaveUp(firstNote));
    }
    if (addOctaveDown)
    {
        chord.addNote(getOctaveDown(firstNote));
    }

    return chord;
}
Chord Scale::getDyad(int noteNumber)
{
    Chord chord = Chord(noteNumber);
    chord.addNote(getFifth(noteNumber));
    return chord;
}
Chord Scale::getTriad(int noteNumber)
{
    Chord chord = Chord(noteNumber);
    chord.addNote(getThird(noteNumber));
    chord.addNote(getFifth(noteNumber));
    return chord;
}
Chord Scale::getTetrad(int noteNumber)
{
    Chord chord = Chord(noteNumber);
    chord.addNote(getThird(noteNumber));
    chord.addNote(getFifth(noteNumber));
    chord.addNote(getSeventh(noteNumber));
    return chord;
}
Chord Scale::getPentad(int noteNumber)
{
    Chord chord = Chord(noteNumber);
    chord.addNote(getThird(noteNumber));
    chord.addNote(getFifth(noteNumber));
    chord.addNote(getSeventh(noteNumber));
    chord.addNote(getNineth(noteNumber));
    return chord;
}