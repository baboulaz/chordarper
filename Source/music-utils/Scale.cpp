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

uint8_t Scale::getNoteDegree(uint8_t noteNumber)
{
    return (noteNumber - rootNote) % uint8_t(12);
}

uint8_t Scale::getNotePosition(uint8_t degree)
{
    auto vector = degrees.at(mode);
    std::vector<uint8_t>::iterator it = std::find(vector.begin(), vector.end(), degree);
    if (it != vector.end())
        return std::distance(vector.begin(), it);
    else
        return NOT_FOUND;
}

std::string Scale::getNoteName(uint8_t noteNumber)
{
    return notes[getNoteDegree(noteNumber)];
}

uint8_t Scale::getNote(uint8_t noteNumber, uint8_t noteDegree)
{
    uint8_t degree = getNoteDegree(noteNumber);
    uint8_t position = getNotePosition(degree);
    if (position == NOT_FOUND)
        return NOT_FOUND;
    uint8_t newPosition = (position + uint8_t(noteDegree)) % uint8_t(7);
    uint8_t start = degrees.at(mode)[position];
    uint8_t finish = degrees.at(mode)[newPosition];
    uint8_t newNote = noteNumber + (start > finish ? (12 - start) + finish : finish - start);
    return newNote < 128 ? newNote : NOT_FOUND;
}

uint8_t Scale::getThird(uint8_t noteNumber)
{
    return getNote(noteNumber, 2);
}
uint8_t Scale::getFifth(uint8_t noteNumber)
{
    return getNote(noteNumber, 4);
}
uint8_t Scale::getSeventh(uint8_t noteNumber)
{
    return getNote(noteNumber, 6);
}
uint8_t Scale::getNineth(uint8_t noteNumber)
{
    uint8_t newNote = getNote(noteNumber, 1) + 12;
    return newNote < 128 ? newNote : NOT_FOUND;
}
uint8_t Scale::getOctaveUp(uint8_t noteNumber)
{
    return noteNumber + 12 < 128 ? noteNumber + 12 : NOT_FOUND;
}
uint8_t Scale::getOctaveDown(uint8_t noteNumber)
{
    return noteNumber - 12 >= 0 ? noteNumber - 12 : NOT_FOUND;
}
uint8_t Scale::getNoteOnScale(uint8_t noteNumber, bool filterNote)
{
    uint8_t degree = getNoteDegree(noteNumber);
    uint8_t position = getNotePosition(degree);
    if (position == NOT_FOUND)
    {
        if (filterNote)
        {
            return NOT_FOUND;
        }
        else
        {
            uint8_t degreeCorrection = getNoteDegree(noteNumber - 1);
            uint8_t positionCorrection = getNotePosition(degreeCorrection);
            if (positionCorrection == NOT_FOUND)
            {
                return noteNumber - 1;
            }
            return NOT_FOUND;
        }
    }
    else
    {
        return noteNumber;
    }
}

Chord Scale::createChord(uint8_t firstNote, uint8_t numberOfNotes)
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

Chord Scale::getChord(uint8_t firstNote, uint8_t numberOfNotes, uint8_t numberOfInversions, bool addOctaveUp, bool addOctaveDown)
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
Chord Scale::getDyad(uint8_t noteNumber)
{
    Chord chord = Chord(noteNumber);
    chord.addNote(getFifth(noteNumber));
    return chord;
}
Chord Scale::getTriad(uint8_t noteNumber)
{
    Chord chord = Chord(noteNumber);
    chord.addNote(getThird(noteNumber));
    chord.addNote(getFifth(noteNumber));
    return chord;
}
Chord Scale::getTetrad(uint8_t noteNumber)
{
    Chord chord = Chord(noteNumber);
    chord.addNote(getThird(noteNumber));
    chord.addNote(getFifth(noteNumber));
    chord.addNote(getSeventh(noteNumber));
    return chord;
}
Chord Scale::getPentad(uint8_t noteNumber)
{
    Chord chord = Chord(noteNumber);
    chord.addNote(getThird(noteNumber));
    chord.addNote(getFifth(noteNumber));
    chord.addNote(getSeventh(noteNumber));
    chord.addNote(getNineth(noteNumber));
    return chord;
}