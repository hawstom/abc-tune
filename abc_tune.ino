#include <stdio.h>
#include <math.h>

const int A4_FREQUENCY = 440;
const double A4_OFFSET = 4.75; // Octaves offset from C0 to A4, 9/12 octave above C4
const int BPM = 120; // Beats per minute
const float BPU = 1.0; // Beats per unit note
int note_accidental(char note[4]);
int note_octave(char note[4]);
float note_octave_fraction(char note[4]);
double note_exponent(char note[4]);
float note_frequency(char note[4]);
long note_duration(float duration);

void main()
{
    float frequency;
    long duration;
    char note[4] = "A1";
    float length = 1;
    //frequency = note_frequency("A10");
    //frequency = note_frequency("A1+");
    //frequency = note_frequency("A1-");
    printf("\nNote:\t\"%s\"", note);
    printf("\nLetter:\t\"%c\"", note[0]);
    printf("\nOctave:\t\"%i\"", note_octave(note));
    printf("\nAccidental:\t\"%i\"", note_accidental(note));
    printf("\nExponent:\t\"%f\"", note_exponent(note));
    printf("\nASCII:\t\"%i\"", note[0]);
    printf("\nFrequency:\t\"%f\"",note_frequency(note)); 
    printf("\nBeats per minute:\t\"%i\"", BPM);
    printf("\nBeats per unit note:\t\"%f\"", BPU);
    printf("\nNote length (unit lengths):\t\"%f\"", length);
    printf("\nNote duration (milliseconds):\t\"%li\"", note_duration(length));
    printf("\nI will now play Mary had a Little Lamb.");  
    play("E3",1);
    play("D3",1);
    play("C3",1);
    play("D3",1);
    play("E3",1);
    play("E3",1);
    play("E3",2);
    play("D3",1);
    play("D3",1);
    play("D3",2);
    play("E3",1);
    play("G3",1);
    play("G3",2);
}

int note_accidental(char note[4])
{
   return (!note[2] || note[2] == 48) ? 0 : (note[2] == 43 ? 1 : -1); 
}

int note_octave(char note[4])
{
    return note[1] - 48;
}

// Returns the fraction of an octave a note of the notation "A4", "A4+", "A4-" is above the C of its octave.
float note_octave_fraction(char note[4])
{
    int half_steps;
    int note_ascii = note[0];
    int note_ordinal = note_ascii - 64;
    switch(note_ordinal) {
      case 1 :
        half_steps = 9; // A
         break;
      case 2 :
        half_steps = 11; // B
         break;
      case 3 :
        half_steps = 0; // C
         break;
      case 4 :
        half_steps = 2; // D
         break;
      case 5 :
        half_steps = 4; // E
         break;
      case 6 :
        half_steps = 5; // F
         break;
      case 7 :
        half_steps = 7; // G
         break;
      default :
         printf("Invalid note letter\n" );
    }
    half_steps = half_steps + note_accidental(note);
    return half_steps / 12.0;
}

double note_exponent(char note[4])
{
    return note_octave(note) + note_octave_fraction(note) - A4_OFFSET;
}

float note_frequency(char note[4]) 
{
    return (float) A4_FREQUENCY * pow(2, note_exponent(note));
}

long note_duration(float note) 
{
    return (long) note * BPU * 60000 / BPM;
}

void play(char note[4], int length)
{
    printf("\nNote:\t\"%s\"",note); 
    printf("\tFrequency:\t\"%f\"",note_frequency(note)); 
    printf("\tDuration:\t\"%li\"", note_duration(length));  
}
