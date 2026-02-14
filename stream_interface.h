#ifndef STREAM_INTERFACE_H_
#define STREAM_INTERFACE_H_

class StreamInterface {
 public:
  virtual ~StreamInterface() = default;
  virtual bool Eof() const = 0;
  virtual char Next() = 0;
  virtual char Peek() = 0;
};

#endif  // STREAM_INTERFACE_H_
