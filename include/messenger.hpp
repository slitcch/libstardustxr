#include "message.hpp"
#include "scenegraph.hpp"

namespace StardustXR {

struct PendingMessage {
  uint8_t type;
  uint id;
};

class Messenger {
public:
  explicit Messenger(int readFD, int writeFD, Scenegraph *scenegraph);

  void sendSignal(const char *object, const char *method,
                  std::vector<uint8_t> &argumentsFlexBuffer);

  flexbuffers::Reference
  executeRemoteMethod(const char *object, const char *method,
                      std::vector<uint8_t> &argumentsFlexBuffer);

  void executeRemoteMethod(const char *object, const char *method,
                           std::vector<uint8_t> &argumentsFlexBuffer,
                           void (*asyncCallback)(flexbuffers::Reference));

  void sendMessage(uint8_t *buffer, uint size);

protected:
  flatbuffers::FlatBufferBuilder builder;

  std::vector<PendingMessage> pendingMessages;
  Scenegraph *scenegraph;

  uint generateMessageID();

private:
  int messageReadFD;
  int messageWriteFD;
};

} // namespace StardustXR