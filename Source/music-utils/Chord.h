#include <set>



class Chord
{
public:
    Chord(int rootNote);
    ~Chord();
    void addNote(int note);
    void invert(int numberOfInversions);
    std::set<int>& getListOfNotes();

private:
    std::set<int> listOfNotes=std::set<int>();
};