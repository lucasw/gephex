#ifndef INCLUDED_MIDIUTIL_H
#define INCLUDED_MIDIUTIL_H

#ifdef __cplusplus
extern "C"
{
#endif

#define MIDI_NOTE_OFF    0x80
#define MIDI_NOTE_ON     0x90
#define MIDI_AFTERTOUCH  0xa0
#define MIDI_CTRLCHANGE  0xb0
#define MIDI_PROGCHANGE  0xc0
#define MIDI_CHANNEL_AFTERTOUCH  0xd0
#define MIDI_PITCHBEND   0xe0
#define MIDI_SYSTEM      0xf0
#define MIDI_EOX         0xf7  /* end of SYSEX message */ 

  /**
   * Returns the number of data bytes of a midi message.
   * If status is a system exclusive message, -1 is returned.
   * Please note that any midi message might be interleaved by
   * one byte system realtime messages.
   * @param status the status byte of a midi message
   * @return the number of data bytes following the status byte,
   *           or -1 for a variable length message. If status
   *           is invalid, -2 is returned
   */
  int midi_length_of_message(unsigned char status);

  /**
   * Returns wether a byte is a midi status byte.
   * @param the byte that is tested
   * @return 1 if byte is a status byte, 0 if it is a data byte
   */
  int midi_is_status(unsigned char byte);

#ifdef __cplusplus
}
#endif
#endif
