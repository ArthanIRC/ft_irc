#pragma once

#include "Command.hpp"

class ModeCommand : public Command {
  private:
    typedef void (ModeCommand::*modeExecutor)(bool oper, size_t& p);
    typedef std::map<char, modeExecutor> modeMap;

    std::string _target;
    std::string _mode;
    std::string _modeResult;
    std::string _paramResult;
    Channel* _channel;
    modeMap _modeExec;
    bool _isChan;

    static modeMap initMap() {
        modeMap m;
        m['b'] = &ModeCommand::banMode;
        m['B'] = &ModeCommand::botMode;
        m['l'] = &ModeCommand::limitMode;
        m['i'] = &ModeCommand::iModeDispatcher;
        m['k'] = &ModeCommand::keyMode;
        m['m'] = &ModeCommand::moderatedMode;
        m['n'] = &ModeCommand::noExternalMode;
        m['t'] = &ModeCommand::protectedTopicMode;
        m['o'] = &ModeCommand::operatorMode;
        m['v'] = &ModeCommand::voiceMode;
        return m;
    }

    std::string retrieveParam(std::vector<std::string>& param, size_t i);
    void addResult(bool oper, std::string mode, std::string param);
    void banMode(bool oper, size_t& p);
    void botMode(bool oper, size_t& p);
    void executeMode();
    void invisibleMode(bool oper, size_t& p);
    void inviteMode(bool oper, size_t& p);
    void keyMode(bool oper, size_t& p);
    void limitMode(bool oper, size_t& p);
    void moderatedMode(bool oper, size_t& p);
    void noExternalMode(bool oper, size_t& p);
    void operatorMode(bool oper, size_t& p);
    void protectedTopicMode(bool oper, size_t& p);
    void voiceMode(bool oper, size_t& p);
    void iModeDispatcher(bool oper, size_t& p);

  public:
    ModeCommand(std::string source, std::vector<std::string> params,
                Client* client);
    ~ModeCommand();

    void run();
};