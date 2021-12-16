#include "Chord.h"

Chord::Chord(int rootNote)
{
    listOfNotes.insert(rootNote);
}
Chord::~Chord(){
    
}
void Chord::addNote(int note)
{
    listOfNotes.insert(note);
}
void Chord::invert(int numberOfInversions) {
    if(numberOfInversions > 0 && numberOfInversions < 4 && listOfNotes.size() >= 2) {
        for(int i=0; i<numberOfInversions; i++) {
            int note = *listOfNotes.begin();
            if(note+12 <= 127) {
                listOfNotes.erase(listOfNotes.begin());
                listOfNotes.insert(note+12);
            }
        }
    }
}
std::set<int>& Chord::getListOfNotes()
{
    return listOfNotes;
}