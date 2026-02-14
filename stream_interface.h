#ifndef STREAM_INTERFACE_H_
#define STREAM_INTERFACE_H_

class StreamInterface {
 public:
  virtual ~StreamInterface() = default;

  // Return the line of the next character to be read from the stream.
  virtual int Line() const = 0;

  // Return the column of the next character to be read from the stream.
  virtual int Column() const = 0;

  // Return 'true' if the the end of the stream has been reached.
  virtual bool Eof() const = 0;

  // Return the next character from the stream, or \0 if at Eof, and
  // advance the stream pointer to the following character.
  virtual char Next() = 0;

  // Peek the next character from the stream, or \0 if at Eof. Does
  // not advance the stream pointer to the following character.
  virtual char Peek() = 0;
};

#endif  // STREAM_INTERFACE_H_
