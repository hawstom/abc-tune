#include <stdio.h>
#include <math.h>

const int FREQUENCY_A4 = 440;
const int TEMPO = 120;
const float DEFAULT_LENGTH = 0.125;
float note_frequency(char note[4]);
float note_fraction(int note_ordinal, int note_accidental);
long note_duration(float duration);

void main()
{
    float frequency;
    long duration;
    //frequency = note_frequency("A10");
    //frequency = note_frequency("A1+");
    //frequency = note_frequency("A1-");
    frequency = note_frequency("A1");
    printf("\nFrequency:\t\"%f\"", frequency);
    duration = note_duration(1);
    printf("\nDuration:\t\"%li\"", duration);
}

float note_frequency(char note[4]) 
{
    float frequency;
    double exponent;
    double exponent_offset = 4.75; // A4 is 9/12 octave above C4
    int note_ascii;
    int note_ordinal;
    int note_octave;
    int note_accidental;
    note_ascii = note[0];
    note_ordinal = note_ascii - 64;
    note_octave = note[1] - 48;
    note_accidental = (!note[2] || note[2] == 48) ? 0 : (note[2] == 43 ? 1 : -1);
    exponent = note_octave - exponent_offset + note_fraction(note_ordinal, note_accidental);
    frequency = (float) FREQUENCY_A4 * pow(2, exponent);
    printf("\nNote: \t\"%s\"\nLetter:\t\"%c\"\nNumber:\t\"%i\"\nOctave:\t\"%i\"\nAccidental:\t\"%i\"\nExponent:\t\"%f\"", note, note[0], note_ordinal, note_octave, note_accidental, exponent);
    printf("\nOrdinal:\t\"%i\"", note_ordinal);

    return frequency;
}

float note_fraction(int note_ordinal, int note_accidental)
{
    int half_steps;
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
    half_steps = half_steps + note_accidental;
    return half_steps / 12.0;
}


long note_duration(float note) 
{
    return (long) note * DEFAULT_LENGTH * 60000000 / TEMPO;
}
