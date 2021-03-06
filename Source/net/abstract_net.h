#pragma once

#include <vector>
#include <memory>
#include <string>

#include "../diablo.h"
#include "../storm/storm.h"

namespace net {

enum class provider_t {
  LOOPBACK,
  WEBSOCKET,
};

class abstract_net {
public:
  virtual void create(std::string name, std::string passwd, uint32_t difficulty) = 0;
  virtual void join(std::string name, std::string passwd) = 0;
  virtual void poll() {}

  virtual bool SNetReceiveMessage(int* sender, char** data, int* size) = 0;
  virtual bool SNetSendMessage(int dest, void* data, unsigned int size) = 0;
  virtual bool SNetReceiveTurns(char** data, DWORD* size, DWORD* status) = 0;
  virtual bool SNetSendTurn(char* data, unsigned int size) = 0;
  virtual int SNetGetProviderCaps(struct _SNETCAPS* caps) = 0;
  virtual bool SNetRegisterEventHandler(event_type evtype, SEVTHANDLER func) = 0;
  virtual bool SNetUnregisterEventHandler(event_type evtype, SEVTHANDLER func) = 0;
  virtual bool SNetLeaveGame(int type) = 0;
  virtual bool SNetDropPlayer(int playerid, DWORD flags) = 0;
  virtual bool SNetGetOwnerTurnsWaiting(DWORD* turns) = 0;
  virtual bool SNetGetTurnsInTransit(int* turns) = 0;
  virtual ~abstract_net();

  static std::unique_ptr<abstract_net> make_net(provider_t provider, const char* param);
};

} // namespace net
