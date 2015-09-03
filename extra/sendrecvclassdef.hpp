// Simple definition of a class implementing Sendable and Receivable interfaces.
// This allows instances to be passed directly to socket send/receive methods.

#include <CpperoMQ/All.hpp>

#include <iostream>
#include <sstream>
#include <string>

class Employee : public CpperoMQ::Sendable
               , public CpperoMQ::Receivable
{
public:
    Employee()
        : mId(0)
        , mAge(0)
        , mName("Unknown")
    {
    }

    Employee(int id, int age, std::string name)
        : mId(id)
        , mAge(age)
        , mName(name)
    {
    }

    virtual bool send(const CpperoMQ::Socket& socket, const bool moreToSend) const override
    {
        using namespace CpperoMQ;

        std::ostringstream strStream;

        strStream << mId;
        OutgoingMessage idMsgPart(strStream.str().c_str());
        std::ostringstream().swap(strStream);
        if (!idMsgPart.send(socket, true))
            return false;

        strStream << mAge;
        OutgoingMessage ageMsgPart(strStream.str().c_str());
        std::ostringstream().swap(strStream);
        if (!ageMsgPart.send(socket, true))
            return false;

        OutgoingMessage nameMsgPart(mName.c_str());
        std::ostringstream().swap(strStream);
        if (!nameMsgPart.send(socket, moreToSend))
            return false;

        return true;
    }

    virtual bool receive(CpperoMQ::Socket& socket, bool& moreToReceive) override
    {
        using namespace CpperoMQ;

        std::stringstream strStream;

        IncomingMessage idMsgPart;
        if (!idMsgPart.receive(socket, moreToReceive) || !moreToReceive)
            return false;

        IncomingMessage ageMsgPart;
        if (!ageMsgPart.receive(socket, moreToReceive) || !moreToReceive)
            return false;

        IncomingMessage nameMsgPart;
        if (!nameMsgPart.receive(socket, moreToReceive))
            return false;

        strStream << std::string(idMsgPart.charData(), idMsgPart.size());
        strStream >> mId;
        std::stringstream().swap(strStream);

        strStream << std::string(ageMsgPart.charData(), ageMsgPart.size());
        strStream >> mAge;
        std::stringstream().swap(strStream);

        mName.assign(nameMsgPart.charData(), nameMsgPart.size());

        return true;
    }

    friend std::ostream& operator<<(std::ostream& stream, const Employee& e)
    {
        stream << e.mId << "," << e.mAge << "," << e.mName;
        return stream;
    }

private:
    int mId;
    int mAge;
    std::string mName;
};
