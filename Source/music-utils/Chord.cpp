#include "Chord.h"

Chord::Chord(int rootNote)
{
    listOfNotes.insert(rootNote);
}
Chord::~Chord()
{
}
void Chord::addNote(uint8_t note)
{
    if (note != NOT_FOUND)
        listOfNotes.insert(note);
}
void Chord::invert(uint8_t numberOfInversions)
{
    if (numberOfInversions > 0 && numberOfInversions < 4 && listOfNotes.size() >= 2)
    {
        for (int i = 0; i < numberOfInversions; i++)
        {
            uint8_t note = *listOfNotes.begin();
            if (note + 12 < 128)
            {
                listOfNotes.erase(listOfNotes.begin());
                listOfNotes.insert(note + 12);
            }
        }
    }
}
std::set<uint8_t> &Chord::getListOfNotes()
{
    return listOfNotes;
}